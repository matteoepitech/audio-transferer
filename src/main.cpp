/*
** DEL PROJECT, 2026
** src/main
** File description:
** Main file
*/

#include "AudioTr.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    AudioTr atr;

    try {
        atr.startProgram(argv[1], argv[2]);
    } catch (AudioException e) {
        std::cerr << "AudioTransfer Error: " << e.what() << std::endl;
        return 1;
    } catch (std::exception e) {
        std::cerr << "Unknown Error: " << e.what() << std::endl;
    }
    return 0;
}
