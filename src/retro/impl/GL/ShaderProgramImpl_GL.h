#pragma once

#include <retro/ShaderProgram.h>

namespace retro
{
    class ShaderProgramImpl_GL : public ShaderProgram::Impl
    {
    public:
        unsigned int id = 0;

        ShaderProgramImpl_GL(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
        virtual ~ShaderProgramImpl_GL();

    private:
        unsigned int compileShader(unsigned int type, const std::string& code);
        unsigned int linkProgram(unsigned int vertexShader, unsigned int fragmentShader);
    };
}
