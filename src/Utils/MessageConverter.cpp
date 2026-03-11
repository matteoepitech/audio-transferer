/*
** DEL PROJECT, 2026
** src/Utils/MessageConverter
** File description:
** MessageConverter source file
*/

#include "MessageConverter.hpp"

/**
 * @brief Convert the string into a vector of bit (bool).
 *
 * @param str    The string to convert
 *
 * @return The message in a allocated memory space array.
 */
std::vector<char> MessageConverter::convertStringMessage(std::string str)
{
    std::size_t sizeMessage = str.length() * 8;
    std::vector<char> message;

    message.reserve(sizeMessage);
    for (char c : str) {
        message.push_back(c >> 7 & 0b1);
        message.push_back(c >> 6 & 0b1);
        message.push_back(c >> 5 & 0b1);
        message.push_back(c >> 4 & 0b1);
        message.push_back(c >> 3 & 0b1);
        message.push_back(c >> 2 & 0b1);
        message.push_back(c >> 1 & 0b1);
        message.push_back(c >> 0 & 0b1);
    }
    return message;
}
