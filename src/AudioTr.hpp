/*
** DEL PROJECT, 2026
** src/AudioTr
** File description:
** AudioTR Header main file
*/

#include <portaudio.h>
#include <exception>
#include <string>

#pragma once

/* @brief The sample rate of the sound for the digital part */
constexpr std::size_t SAMPLE_RATE = 48000;
/* @brief The duration of a bit sound in second */
constexpr std::float_t BIT_DURATION = 0.05f;
/* @brief The amplitude of the sound, 0.5 will make the sound lower by 50% */
constexpr std::float_t AMPLITUDE = 0.5f;
/* @brief The bit 0 frequency used. The max is 24kHZ since the sample rate is 48kHZ */
constexpr std::float_t FREQ_0 = 18000.0f;
/* @brief The bit 1 frequency used. The max is 24kHZ since the sample rate is 48kHZ */
constexpr std::float_t FREQ_1 = FREQ_0 + 1500.0f;
/* @brief The preambul frequency used. The max is 24kHZ since the sample rate is 48kHZ */
constexpr std::float_t FREQ_PREAMBUL = FREQ_1 + 3000.0f;

/* @brief AudioTr Class */
class AudioTr
{
public:
    /**
     * @brief Start the program. This function is the first called.
     *
     * @param mode        The mode "-tx" for transmission and "-rx" for receipter
     * @param fileName    The file content to transmit in the ""-tx"" mode
     */
    void startProgram(char *mode, char *fileName);
};
    
/* @brief AudioException Class */
class AudioException : std::exception
{
    public:
        /**
         * @brief The constructor of the AudioException class.
         *
         * @param msg    The content of the error message
         */
        explicit AudioException(std::string msg) noexcept
        {
            this->_msg = msg;
        }

    public:
        /**
         * @brief Get the content of the exception.
         *
         * @return The content of the error.
         */
        const char *what(void) const noexcept override
        {
            return this->_msg.c_str();
        }

    private:
        /* @brief The content of the error */
        std::string _msg;
};
