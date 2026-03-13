/*
** DEL PROJECT, 2026
** src/Transmission/Transmission
** File description:
** Transmission source file
*/

#include "Transmission.hpp"
#include <iostream>
#include <iomanip>

/**
 * @brief Print a progress bar in the terminal.
 *
 * @param percent Progress percentage (0.0 → 100.0)
 */
static void printProgressBar(float percent)
{
    const int barWidth = 50;
    int pos = static_cast<int>(barWidth * percent);

    std::cout << "\033[1F";
    std::cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) {
            std::cout << "=";
        } else if (i == pos) {
            std::cout << ">";
        } else {
            std::cout << " ";
        }
    }
    std::cout << "] ";
    std::cout << std::fixed << std::setprecision(2) << percent * 100 << " %" << std::endl;
}

/**
 * @brief Send a silence gap for clean transition between preambul and data.
 *
 * @param stream  The stream of PortAudio to send the data to
 */
void Transmission::sendSilence(PaStream *stream)
{
    int frames = SAMPLE_RATE * BIT_DURATION;
    std::float_t buffer[frames];

    std::fill(buffer, buffer + frames, 0.0f);
    for (int i = 0; i < 3; i++) {
        Pa_WriteStream(stream, buffer, frames);
    }
}

/**
 * @brief Send the preambul for the sync of the receipter.
 *
 * @param stream  The stream of PortAudio to send the data to
 * @param phase   The phase of the sin wave
 */
void Transmission::sendPreambul(PaStream *stream, double *phase)
{
    for (int i = 0; i < (int) (1.0 / BIT_DURATION); i++) {
        SenderBit::sendCustomFrequency(stream, FREQ_PREAMBUL, phase);
    }
}

/**
 * @brief Send a message with preambul synchronization. R-Value reference.
 *
 * @param message    The message in a array of a bit, 0, 1.
 */
void Transmission::sendMessage(std::vector<char> &&message)
{
    PaStream *stream = nullptr;
    double phase = 0;

    Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, SAMPLE_RATE, 256, NULL, NULL);
    Pa_StartStream(stream);
    sendPreambul(stream, &phase);
    sendSilence(stream);
    phase = 0;
    for (std::size_t i = 0; i < message.size(); i++) {
        printProgressBar(static_cast<std::float_t>(static_cast<std::float_t>(i) / (message.size() - 1)));
        SenderBit::sendBit(stream, message.at(i), &phase);
    }
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
}

/**
 * @brief Send a message with preambul synchronization. L-Value reference.
 *
 * @param message    The message in a array of a bit, 0, 1.
 */
void Transmission::sendMessage(std::vector<char> &message)
{
    PaStream *stream = nullptr;
    double phase = 0;

    Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, SAMPLE_RATE, 256, NULL, NULL);
    Pa_StartStream(stream);
    sendPreambul(stream, &phase);
    sendSilence(stream);
    phase = 0;
    for (std::size_t i = 0; i < message.size(); i++) {
        printProgressBar(static_cast<std::float_t>(static_cast<std::float_t>(i) / (message.size() - 1)));
        SenderBit::sendBit(stream, message.at(i), &phase);
    }
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
}
