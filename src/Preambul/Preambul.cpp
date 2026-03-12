/*
** DEL PROJECT, 2026
** src/Preambul/Preambul
** File description:
** Preambul source file
*/

#include "Preambul.hpp"

/**
 * @brief Send the preambul for the sync of the receipter.
 */
void Preambul::sendPreambul(void)
{
    PaStream *stream = nullptr;
    double phase = 0;

    Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, SAMPLE_RATE, 256, NULL, NULL);
    Pa_StartStream(stream);
    for (int i = 0; i < 1 / BIT_DURATION; i++) {
        SenderBit::sendCustomFrequency(stream, FREQ_PREAMBUL, &phase);
    }
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
}
