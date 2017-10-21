#pragma once

namespace retro
{
    class Mesh;
    class ShaderProgram;

    /**
     * A drawable is an abstract class, which the Renderer uses for drawing objects.
     */
    class Drawable
    {
    public:
        virtual ~Drawable() = default;

        virtual Mesh& getMesh() = 0;
        virtual ShaderProgram& getShaderProgram() = 0;
    };
}
