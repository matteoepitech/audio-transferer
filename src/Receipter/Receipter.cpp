/*
** DEL PROJECT, 2026
** src/Receipter/Receipter
** File description:
** Receipter source file
*/

#include "../Utils/MessageConverter.hpp"
#include "Receipter.hpp"
#include <iostream>

/**
 * @brief Compute signal power at a specific frequency using Goertzel algorithm.
 *
 * @param samples     input audio buffer
 * @param N           number of samples
 * @param freq        frequency to detect
 *
 * @return power of that frequency in the buffer.
 */
float goertzel(const float* samples, std::size_t N, float freq)
{
    float s_prev = 0.0f;
    float s_prev2 = 0.0f;
    float normalized = freq / SAMPLE_RATE;
    float coeff = 2.0f * std::cos(2.0f * M_PI * normalized);

    for (std::size_t i = 0; i < N; i++) {
        float s = samples[i] + coeff * s_prev - s_prev2;
        s_prev2 = s_prev;
        s_prev = s;
    }
    return s_prev2 * s_prev2 + s_prev * s_prev - coeff * s_prev * s_prev2;
}

/**
 * @brief Listen using micro for a message.
 *
 * @return The message in bit 0 and 1.
 */
std::vector<bool> Receipter::listenMessage(void)
{
    const std::size_t samplesPerBit = SAMPLE_RATE * BIT_DURATION;
    std::size_t preambulCounter = 0;
    std::size_t endCounter = 0;
    PaStream *stream = nullptr;
    std::vector<bool> message;
    std::vector<float> buffer;

    buffer.reserve(samplesPerBit);
    Pa_OpenDefaultStream(&stream, 1, 0, paFloat32, SAMPLE_RATE, 256, NULL, NULL);
    Pa_StartStream(stream);
    std::cerr << "Listening message.. You will see output on stdout" << std::endl;
    while (true) {
        float b[256] = {0};

        Pa_ReadStream(stream, b, 256);
        buffer.insert(buffer.end(), b, b + 256);
        if (buffer.size() >= samplesPerBit) {
            float preambul = std::fabs(goertzel(buffer.data() + buffer.size() - samplesPerBit, samplesPerBit, FREQ_PREAMBUL));

            preambul /= (samplesPerBit * samplesPerBit);
            if (preambul > 5e-7) {
                preambulCounter++;
            } else if (preambulCounter > 80) {
                preambulCounter = 0;
                buffer.clear();
                std::cerr << "Synchronization done: Listening for message..." << std::endl;
                while (true) {
                    Pa_ReadStream(stream, b, 256);
                    buffer.insert(buffer.end(), b, b + 256);
                    if (endCounter > 100) {
                        std::cerr << std::endl << "End of the receiving." << std::endl;
                        break;
                    }
                    while (buffer.size() >= samplesPerBit) {
                        float p0 = std::fabs(goertzel(buffer.data(), samplesPerBit, FREQ_0));
                        float p1 = std::fabs(goertzel(buffer.data(), samplesPerBit, FREQ_1));
                        float power = p0 + p1;
                        float dominant = (p0 > p1) ? p0 : p1;
                        float weaker = (p0 > p1) ? p1 : p0;

                        if (power < 0.5f) {
                            buffer.erase(buffer.begin(), buffer.begin() + samplesPerBit);
                            endCounter++;
                            continue;
                        }
                        if (weaker > 1e-9f && (dominant / weaker) < 2.5f) {
                            buffer.erase(buffer.begin(), buffer.begin() + samplesPerBit);
                            endCounter++;
                            continue;
                        }
                        if (p0 > p1) {
                            message.push_back(0);
                            std::cerr << 0 << std::flush;
                        } else {
                            message.push_back(1);
                            std::cerr << 1 << std::flush;
                        }
                        endCounter = 0;
                        buffer.erase(buffer.begin(), buffer.begin() + samplesPerBit);
                    }
                }
                std::cerr << "Decoded message:" << std::endl;
                std::cout << MessageConverter::convertMessageString(message) << std::endl;
                message.clear();
                endCounter = 0;
            } else {
                preambulCounter = 0;
            }
        }
    }
    Pa_CloseStream(stream);
}
