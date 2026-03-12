/*
** DEL PROJECT, 2026
** src/Utils/MessageConverter
** File description:
** MessageConverter header file
*/

#include <string>
#include <vector>

#pragma once

/* @brief MessageConverter Class */
class MessageConverter
{
public:
    /**
     * @brief Convert the string into a vector of bit (bool).
     *
     * @param str    The string to convert
     *
     * @return The message in a allocated memory space array.
     */
    static std::vector<char> convertStringMessage(std::string str);

    /**
     * @brief Convert the encoded bits in string way.
     *
     * @param std::vector<bool>  The message encoded in bits
     *
     * @return The final message in a string way.
     */
    static std::string convertMessageString(const std::vector<bool> &message);
};
