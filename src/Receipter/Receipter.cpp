/*
** DEL PROJECT, 2026
** src/Receipter/Receipter
** File description:
** Receipter source file
*/

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
            float p0 = std::fabs(goertzel(buffer.data(), samplesPerBit, FREQ_0));
            float p1 = std::fabs(goertzel(buffer.data(), samplesPerBit, FREQ_1));
            float power = p0 + p1;
            float dominant = (p0 > p1) ? p0 : p1;
            float weaker = (p0 > p1) ? p1 : p0;

            if (power < 0.5f) {
                buffer.clear();
                continue;
            }
            if (weaker <= 1e-9f || (dominant / weaker) < 2.5f) {
                buffer.clear();
                continue;
            }
            if (p0 > p1) {
                message.push_back(0);
                std::cout << 0 << std::flush;
            } else {
                message.push_back(1);
                std::cout << 1 << std::flush;
            }
            buffer.clear();
        }
    }
    Pa_CloseStream(stream);
}
