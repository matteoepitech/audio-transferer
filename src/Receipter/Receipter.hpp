/*
** DEL PROJECT, 2026
** src/Receipter/Receipter
** File description:
** Receipter header file
*/

#include "../AudioTr.hpp"
#include <cstddef>
#include <vector>

#pragma once

/* @brief Receipter Class */
class Receipter
{
public:
    /**
     * @brief Listen using micro for a message.
     *
     * @return The message in bit 0 and 1.
     */
    std::vector<bool> listenMessage(void);
};
