/*
** DEL PROJECT, 2026
** src/Transmission/Transmission
** File description:
** Transmission source file
*/

#include "Transmission.hpp"

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
    for (std::size_t i = 0; i < message.size(); i++) {
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
    for (std::size_t i = 0; i < message.size(); i++) {
        SenderBit::sendBit(stream, message.at(i), &phase);
    }
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
}
