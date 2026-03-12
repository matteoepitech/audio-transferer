/*
** DEL PROJECT, 2026
** src/Utils/SenderBit
** File description:
** SenderBit header file
*/

#include <portaudio.h>

#pragma once

/* @brief SenderBit Class */
class SenderBit
{
public:
    /**
     * @brief Send a bit into the sound card using PortAudio.
     *
     * @param stream  The stream of PortAudio to send the data to
     * @param bit     The bit to send
     * @param phase   The phase of the sin wave
     */
    static void sendBit(PaStream *stream, bool bit, double *phase);

    /**
     * @brief Send a sample with a custom frequency into the sound card using PortAudio.
     *
     * @param stream        The stream of PortAudio to send the data to
     * @param frequency     The frequency used
     * @param phase         The phase of the sin wave
     */
    static void sendCustomFrequency(PaStream *stream, double frequency, double *phase);
};
