#pragma once

#include <memory>
#include <string>

namespace retro
{
    /**
     * An application holds a window and is able to poll platform events.
     */
    class Application
    {
    public:
        class Impl;

        /**
         * Creates a new window, which will be shown after the creation.
         *
         * @param int The width of the window
         * @param int The height of the window
         * @param const std::string& The title of the window
         */
        Application(int width, int height, const std::string& title);

        ~Application();

        /**
         * Returns the current implementation.
         */
        template<typename T> T* getImpl();

        void getSize(int* width, int* height);

        /**
         * Checks if the application is still running.
         */
        bool isRunning();

        /**
         * Polls new platform events.
         */
        void pollEvents();

    private:
        std::shared_ptr<Impl> impl;

    public:
        class Impl
        {
        public:
            virtual ~Impl() = default;

            virtual void getSize(int* width, int* height) = 0;
            virtual bool isRunning() = 0;
            virtual void pollEvents() = 0;
        };
    };
}
