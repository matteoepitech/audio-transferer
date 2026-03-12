/*
** DEL PROJECT, 2026
** src/Transmission/Transmission
** File description:
** Transmission source file
*/

#include "Transmission.hpp"

/**
 * @brief Send a message. R-Value reference.
 *
 * @param message    The message in a array of a bit, 0, 1.
 */
void Transmission::sendMessage(std::vector<char> &&message)
{
    PaStream *stream = nullptr;
    double phase = 0;

    Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, SAMPLE_RATE, 256, NULL, NULL);
    Pa_StartStream(stream);
    for (int i = 0; i < message.size(); i++) {
        SenderBit::sendBit(stream, message.at(i), &phase);
    }
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
}

/**
 * @brief Send a message. L-Value reference.
 *
 * @param message    The message in a array of a bit, 0, 1.
 */
void Transmission::sendMessage(std::vector<char> &message)
{
    PaStream *stream = nullptr;
    double phase = 0;

    Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, SAMPLE_RATE, 256, NULL, NULL);
    Pa_StartStream(stream);
    for (int i = 0; i < message.size(); i++) {
        SenderBit::sendBit(stream, message.at(i), &phase);
    }
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
}
