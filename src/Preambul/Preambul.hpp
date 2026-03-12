/*
** DEL PROJECT, 2026
** src/Preambul/Preambul
** File description:
** Preambul header file
*/

#include "../Transmission/Transmission.hpp"
#include "../Utils/SenderBit.hpp"
#include <portaudio.h>

#pragma once

/* @brief Preambul Class */
class Preambul
{
public:
    /**
     * @brief Send the preambul for the sync of the receipter.
     */
    void sendPreambul(void);
};
