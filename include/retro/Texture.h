#pragma once

#include <memory>
#include <libretro.h>

namespace retro
{
    class Texture
    {
    public:
        class Impl;

        Texture();

        ~Texture();

        void setPixelFormat(retro_pixel_format format);

        void init(int width, int height);

        void update(const void* data, int width, int height, size_t pitch);

        /**
        * Returns the current implementation.
        */
        template<typename T> T* getImpl();

    private:
        std::shared_ptr<Impl> impl;

    public:
        class Impl
        {
        public:
            virtual ~Impl() = default;

            virtual void setPixelFormat(retro_pixel_format format) = 0;
            virtual void init(int width, int height) = 0;
            virtual void update(const void* data, int width, int height, size_t pitch) = 0;
        };
    };
}
