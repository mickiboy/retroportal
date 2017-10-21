#include <iostream>
#include "LogImpl_ANSI.h"

#ifdef _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

namespace retro
{
    LogImpl_ANSI::LogImpl_ANSI()
    {
        // Sigh... Windows, why?
#ifdef _WIN32
        // Get a handle of the current console
        auto consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

        // Get the mode of the current console
        DWORD consoleMode = 0;
        GetConsoleMode(consoleHandle, &consoleMode);

        // Enable ANSI escape sequences
        consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(consoleHandle, consoleMode);
#endif
    }

    void LogImpl_ANSI::log(LogType type, const std::string& timeAsString, const std::string& message)
    {
        std::string colorSequence;
        std::string typeAsString;

        switch (type) {
            case LogType::Debug:
                typeAsString = "[Debug]";
                break;

            case LogType::Warning:
                colorSequence = "\x1b[33m";
                typeAsString = "[Warning]";
                break;

            case LogType::Error:
                colorSequence = "\x1b[31m";
                typeAsString = "[Error]";
                break;
        }

        std::cout << colorSequence << timeAsString << ' ' << typeAsString << ' ' << message << "\x1b[0m\n";
    }
}
