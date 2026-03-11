/*
** DEL PROJECT, 2026
** src/AudioTr
** File description:
** AudioTR source main file
*/

#include "Transmission/Transmission.hpp"
#include "Utils/MessageConverter.hpp"
#include "Receipter/Receipter.hpp"
#include "AudioTr.hpp"
#include <iostream>
 
/**
 * @brief Start the program. This function is the first called.
 *
 * @param mode      The mode "-tx" for transmission and "-rx" for receipter
 */
void AudioTr::startProgram(char *mode)
{
    Transmission transmission;
    Receipter receipter;

    if (mode == nullptr) {
        throw AudioException("No mode specified. (-tx/-rx)");
    }
    Pa_Initialize();
    if (std::strcmp(mode, "-tx") == 0) {
        transmission.sendMessage(MessageConverter::convertStringMessage("Hello World!"));
    } else if (std::strcmp(mode, "-rx") == 0) {
        std::cout << receipter.listenMessage().size() <<  std::endl;
    } else {
        throw AudioException("Invalid mode: -rx/-tx");
    }
    Pa_Terminate();
    return;
}
