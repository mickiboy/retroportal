#include "impl/GL/TextureImpl_GL.h"

namespace retro
{
    Texture::Texture()
    {
        impl = std::make_shared<TextureImpl_GL>();
    }

    Texture::~Texture()
    {
        impl.reset();
    }

    template<typename T> T* Texture::getImpl()
    {
        return static_cast<T*>(impl.get());
    }

    template TextureImpl_GL* Texture::getImpl<TextureImpl_GL>();

    void Texture::setPixelFormat(retro_pixel_format format)
    {
        impl->setPixelFormat(format);
    }

    void Texture::init(int width, int height)
    {
        impl->init(width, height);
    }

    void Texture::update(const void* data, int width, int height, size_t pitch)
    {
        impl->update(data, width, height, pitch);
    }
}
