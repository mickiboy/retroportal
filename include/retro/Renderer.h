#pragma once

#include <memory>

namespace retro
{
    class Application;
    class Drawable;

    /**
     * A class for drawing objects to the screen.
     */
    class Renderer
    {
    public:
        class Impl;

        Renderer(Application& app);

        ~Renderer();

        /**
         * Returns the current implementation.
         */
        template<typename T> T* getImpl();

        /**
         * Clears the entire screen with black color.
         */
        void clear();

        /**
         * Draws an object, which inherits from Drawable.
         */
        void draw(Drawable& drawable);

        /**
         * Shows all drawn objects.
         */
        void swapBuffers();

    private:
        std::shared_ptr<Impl> impl;

    public:
        class Impl
        {
        public:
            virtual ~Impl() = default;

            virtual void clear() = 0;
            virtual void draw(Drawable& drawable) = 0;
            virtual void swapBuffers() = 0;
        };
    };
}
