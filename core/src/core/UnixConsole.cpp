#include <iostream>
#include "core/UnixConsole.hpp"

namespace bricksvm
{
    namespace core
    {
        std::string const UnixConsole::Red = "\033[30m";
        std::string const UnixConsole::Green = "\033[32m";
        std::string const UnixConsole::White = "\033[37m";
        std::string const UnixConsole::Blue = "\033[34m";

        std::ostream &UnixConsole::success(std::string const &deviceName)
        {
            std::cout << UnixConsole::Green << "[BricksVM:" << deviceName << "]";
            std::cout << UnixConsole::White;
            return std::cout;
        }

        std::ostream &UnixConsole::log(std::string const &deviceName)
        {
            std::cout << UnixConsole::Blue << "[BricksVM:" << deviceName << "]";
            std::cout << UnixConsole::White;
            return std::cout;
        }

        std::ostream &UnixConsole::error(std::string const &deviceName)
        {
            std::cout << UnixConsole::Red << "[BricksVM:" << deviceName << "]";
            std::cout << UnixConsole::White;
            return std::cout;
        }
    }
}