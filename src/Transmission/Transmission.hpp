/*
** DEL PROJECT, 2026
** src/Transmission/Transmission
** File description:
** Transmission header file
*/

#include "../AudioTr.hpp"
#include <cstddef>
#include <vector>

#pragma once

/* @brief Transmission Class */
class Transmission
{
public:
    /**
     * @brief Send a message. R-Value reference.
     *
     * @param message    The message in a array of a bit, 0, 1.
     */
    void sendMessage(std::vector<char> &&message);

    /**
     * @brief Send a message. L-Value reference.
     *
     * @param message    The message in a array of a bit, 0, 1.
     */
    void sendMessage(std::vector<char> &message);

protected:
    /**
     * @brief Send a bit into the sound card using PortAudio.
     *
     * @param stream  The stream of PortAudio to send the data to
     * @param bit     The bit to send
     * @param phase   The phase of the sin wave
     */
    void sendBit(PaStream *stream, bool bit, double *phase);
};
