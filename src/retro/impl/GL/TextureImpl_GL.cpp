#include <glad/glad.h>
#include <retro/Log.h>
#include "TextureImpl_GL.h"

namespace retro
{
    TextureImpl_GL::TextureImpl_GL()
    {
        glGenTextures(1, &id);

        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    TextureImpl_GL::~TextureImpl_GL()
    {
        glDeleteTextures(1, &id);
    }

    void TextureImpl_GL::setPixelFormat(retro_pixel_format format)
    {
        switch (format) {
            case RETRO_PIXEL_FORMAT_0RGB1555:
                textureFormat = GL_UNSIGNED_SHORT_1_5_5_5_REV;
                break;

            case RETRO_PIXEL_FORMAT_XRGB8888:
                textureFormat = GL_UNSIGNED_INT;
                break;

            case RETRO_PIXEL_FORMAT_RGB565:
                textureFormat = GL_UNSIGNED_SHORT_5_6_5;
                break;
        }
    }

    void TextureImpl_GL::init(int width, int height)
    {
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, textureFormat, nullptr);
    }

    void TextureImpl_GL::update(const void* data, int width, int height, size_t pitch)
    {
        glPixelStorei(GL_UNPACK_ROW_LENGTH, pitch / 2);

        glBindTexture(GL_TEXTURE_2D, id);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, textureFormat, data);
    }
}
