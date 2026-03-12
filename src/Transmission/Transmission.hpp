/*
** DEL PROJECT, 2026
** src/Transmission/Transmission
** File description:
** Transmission header file
*/

#include "../Utils/SenderBit.hpp"
#include "../AudioTr.hpp"
#include <cstddef>
#include <vector>

#pragma once

/* @brief Transmission Class */
class Transmission
{
public:
    /**
     * @brief Send a message with preambul synchronization. R-Value reference.
     *
     * @param message    The message in a array of a bit, 0, 1.
     */
    void sendMessage(std::vector<char> &&message);

    /**
     * @brief Send a message with preambul synchronization. L-Value reference.
     *
     * @param message    The message in a array of a bit, 0, 1.
     */
    void sendMessage(std::vector<char> &message);

private:
    /**
     * @brief Send the preambul for the sync of the receipter.
     *
     * @param stream  The stream of PortAudio to send the data to
     * @param phase   The phase of the sin wave
     */
    void sendPreambul(PaStream *stream, double *phase);
};
