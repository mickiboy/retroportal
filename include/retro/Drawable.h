#pragma once

namespace retro
{
    class Mesh;
    class ShaderProgram;
    class Texture;

    /**
     * A drawable is an abstract class, which the Renderer uses for drawing objects.
     */
    class Drawable
    {
    public:
        virtual ~Drawable() = default;

        virtual Mesh& getMesh() = 0;
        virtual ShaderProgram& getShaderProgram() = 0;
        virtual Texture& getTexture() = 0;
    };
}
