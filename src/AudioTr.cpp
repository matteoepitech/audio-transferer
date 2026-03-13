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
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * @brief Fill the file content stream with the content of the file.
 *
 * @param fileContent    The file stream to fill
 * @param fileName       The file name
 */
static void fillFileContent(std::stringstream &fileContent, char *fileName)
{
    std::ifstream fileStream;
    std::string fileLine;

    if (fileName == nullptr) {
        throw AudioException("No file passed as parameter");
    }
    fileStream.open(fileName);
    if (fileStream.is_open() == false) {
        throw AudioException("Cannot open that file");
    } 
    while (getline(fileStream, fileLine)) {
        fileContent << fileLine;
    }
}
 
/**
 * @brief Start the program. This function is the first called.
 *
 * @param mode        The mode "-tx" for transmission and "-rx" for receipter
 * @param fileName    The file content to transmit in the ""-tx"" mode
 */
void AudioTr::startProgram(char *mode, char *fileName)
{
    std::vector<bool> message;
    Transmission transmission;
    Receipter receipter;

    if (mode == nullptr) {
        throw AudioException("No mode specified. (-tx/-rx)");
    }
    Pa_Initialize();
    if (std::strcmp(mode, "-tx") == 0) {
        std::stringstream fileContent;

        fillFileContent(fileContent, fileName);
        transmission.sendMessage(MessageConverter::convertStringMessage(fileContent.str()));
    } else if (std::strcmp(mode, "-rx") == 0) {
        message = receipter.listenMessage();
        std::cerr << "Decoded message:" << std::endl;
        std::cout << MessageConverter::convertMessageString(message) << std::endl;
    } else {
        throw AudioException("Invalid mode: -rx/-tx");
    }
    Pa_Terminate();
    return;
}
