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
};
