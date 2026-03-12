/*
** DEL PROJECT, 2026
** src/Utils/SenderBit
** File description:
** SenderBit source file
*/

#include "../Transmission/Transmission.hpp"
#include "SenderBit.hpp"

/**
 * @brief Send a bit into the sound card using PortAudio.
 *
 * @param stream  The stream of PortAudio to send the data to
 * @param bit     The bit to send
 * @param phase   The phase of the sin wave
 */
void SenderBit::sendBit(PaStream *stream, bool bit, double *phase)
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

/**
 * @brief Send a sample with a custom frequency into the sound card using PortAudio.
 *
 * @param stream        The stream of PortAudio to send the data to
 * @param frequency     The frequency used
 * @param phase         The phase of the sin wave
 */
void SenderBit::sendCustomFrequency(PaStream *stream, double frequency, double *phase)
{
    int frames = SAMPLE_RATE * BIT_DURATION;
    std::float_t buffer[frames];
    double nextPhase = 2.0 * M_PI * frequency / SAMPLE_RATE;

    for (int i = 0; i < frames; i++) {
        buffer[i] = (std::float_t) (AMPLITUDE * sin(*phase));
        *phase += nextPhase;
        if (*phase > 2.0 * M_PI) {
            *phase -= 2.0 * M_PI;
        }
    }
    Pa_WriteStream(stream, buffer, frames);
}

