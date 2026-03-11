/*
** DEL PROJECT, 2026
** src/AudioTr
** File description:
** AudioTR source main file
*/

#include "Transfer/Transfer.hpp"
#include "Utils/MessageConverter.hpp"
#include "AudioTr.hpp"
 
/**
 * @brief Start the program. This function is the first called.
 */
void AudioTr::startProgram(void)
{
    Transfer transfer;

    Pa_Initialize();
    transfer.sendMessage(MessageConverter::convertStringMessage("Hello World!"));
    Pa_Terminate();
    return;
}
