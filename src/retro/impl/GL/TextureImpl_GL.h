#pragma once

#include <retro/Texture.h>

namespace retro
{
    class TextureImpl_GL : public Texture::Impl
    {
    public:
        unsigned int id = 0;

        TextureImpl_GL();
        virtual ~TextureImpl_GL();

        void setPixelFormat(retro_pixel_format format) override;
        void init(int width, int height) override;
        void update(const void* data, int width, int height, size_t pitch) override;

    private:
        unsigned int textureFormat = 0;
    };
}
