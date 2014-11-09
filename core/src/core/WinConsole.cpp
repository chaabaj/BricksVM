#include <windows.h>
#include <iostream>
#include "core/WinConsole.hpp"

namespace bricksvm
{
    namespace core
    {
        std::ostream &WinConsole::success(std::string const &deviceName)
        {
            HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

            SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            std::cout << "[BricksVM:" << deviceName << "] : ";
            SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            return std::cout;
        }

        std::ostream &WinConsole::log(std::string const &deviceName)
        {
            HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

            SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            std::cout << "[BricksVM:" << deviceName << "] : ";
            SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            return std::cout;
        }

        std::ostream &WinConsole::error(std::string const &deviceName)
        {
            HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

            SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
            std::cout << "[BricksVM:" << deviceName << "] : ";
            SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            return std::cout;
        }
    }
}