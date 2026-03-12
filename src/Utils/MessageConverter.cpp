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
    
/**
 * @brief Convert the encoded bits in string way.
 *
 * @param std::vector<bool>  The message encoded in bits
 *
 * @return The final message in a string way.
 */
std::string MessageConverter::convertMessageString(const std::vector<bool> &message)
{
    std::string str;

    for (std::size_t i = 0; i + 7 < message.size(); i += 8) {
        char c = 0;

        c |= (static_cast<char>(message[i])) << 7;
        c |= (static_cast<char>(message[i + 1])) << 6;
        c |= (static_cast<char>(message[i + 2])) << 5;
        c |= (static_cast<char>(message[i + 3])) << 4;
        c |= (static_cast<char>(message[i + 4])) << 3;
        c |= (static_cast<char>(message[i + 5])) << 2;
        c |= (static_cast<char>(message[i + 6])) << 1;
        c |= (static_cast<char>(message[i + 7])) << 0;
        str.push_back(c);
    }
    return str;
}
