/*
** DEL PROJECT, 2026
** src/Transfer/Transfer
** File description:
** Transfer source file
*/

#include "Transfer.hpp"

/**
 * @brief Send a message. R-Value reference.
 *
 * @param message    The message in a array of a bit, 0, 1.
 */
void Transfer::sendMessage(std::vector<char> &&message)
{
    PaStream *stream = nullptr;
    double phase = 0;

    Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, SAMPLE_RATE, 256, NULL, NULL);
    Pa_StartStream(stream);
    for (int i = 0; i < message.size(); i++) {
        this->sendBit(stream, message.at(i), &phase);
    }
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
}

/**
 * @brief Send a message. L-Value reference.
 *
 * @param message    The message in a array of a bit, 0, 1.
 */
void Transfer::sendMessage(std::vector<char> &message)
{
    PaStream *stream = nullptr;
    double phase = 0;

    Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, SAMPLE_RATE, 256, NULL, NULL);
    Pa_StartStream(stream);
    for (int i = 0; i < message.size(); i++) {
        this->sendBit(stream, message.at(i), &phase);
    }
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
}

/**
 * @brief Send a bit into the sound card using PortAudio.
 *
 * @param stream  The stream of PortAudio to send the data to
 * @param bit     The bit to send
 * @param phase   The phase of the sin wave
 */
void Transfer::sendBit(PaStream *stream, bool bit, double *phase)
{
    int frames = SAMPLE_RATE * BIT_DURATION;
    std::float_t buffer[frames];
    double freq = bit ? FREQ_1 : FREQ_0;
    double nextPhase = 2.0 * M_PI * freq / SAMPLE_RATE;

    for (int i = 0; i < frames; i++) {
        buffer[i] = (std::float_t) (AMPLITUDE * sin(*phase));
        *phase += nextPhase;
        if (*phase > 2.0 * M_PI) {
            *phase -= 2.0 * M_PI;
        }
    }
    Pa_WriteStream(stream, buffer, frames);
}
