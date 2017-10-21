#pragma once

#include <memory>
#include <string>

namespace retro
{
    /**
     * A shader programm is a link between vertex and fragment shader.
     */
    class ShaderProgram
    {
    public:
        class Impl;

        ShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);

        ~ShaderProgram();

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
        };
    };
}
