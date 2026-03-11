/*
** DEL PROJECT, 2026
** src/AudioTr
** File description:
** AudioTR source main file
*/

#include "Transmission/Transmission.hpp"
#include "Utils/MessageConverter.hpp"
#include "AudioTr.hpp"
 
/**
 * @brief Start the program. This function is the first called.
 */
void AudioTr::startProgram(void)
{
    Transmission transmission;

    Pa_Initialize();
    transmission.sendMessage(MessageConverter::convertStringMessage("Hello World!"));
    Pa_Terminate();
    return;
}
