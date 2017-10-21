#pragma once

#include <chrono>
#include <memory>
#include <string>

namespace retro
{
    /**
     * Three different types of logging are sufficient.
     */
    enum class LogType
    {
        Debug, Warning, Error
    };

    /**
     * A static class for logging purposes. Prints messages directly to the console.
     */
    class Log
    {
    public:
        class Impl;

        /**
         * Initializes an implementation of a logger. Should be the first call in the main function.
         */
        static void init();

        /**
         * Shuts the current implementation of the logger down. Should be the last call in the main function.
         */
        static void shutdown();

        /**
         * Prints a debug message to the console.
         *
         * @param const std::string& The message to print
         */
        static void debug(const std::string& message);

        /**
         * Prints a warning message to the console.
         *
         * @param const std::string& The message to print
         */
        static void warning(const std::string& message);

        /**
         * Prints an error message to the console.
         *
         * @param const std::string& The message to print
         */
        static void error(const std::string& message);

        /**
         * Prints a message to the console.
         *
         * @param LogType The type of the message
         * @param const std::string& The message to print
         */
        static void log(LogType type, const std::string& message);

    private:
        static std::shared_ptr<Impl> impl;
        static std::chrono::high_resolution_clock::time_point startTime;

        Log() = default;

    public:
        class Impl
        {
        public:
            virtual ~Impl() = default;

            virtual void log(LogType type, const std::string& timeAsString, const std::string& message) = 0;
        };
    };
}
