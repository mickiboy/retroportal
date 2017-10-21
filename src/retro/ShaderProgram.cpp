#include "impl/GL/ShaderProgramImpl_GL.h"

namespace retro
{
    ShaderProgram::ShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
    {
        impl = std::make_shared<ShaderProgramImpl_GL>(vertexShaderCode, fragmentShaderCode);
    }

    ShaderProgram::~ShaderProgram()
    {
        impl.reset();
    }

    template<typename T> T* ShaderProgram::getImpl()
    {
        return static_cast<T*>(impl.get());
    }

    template ShaderProgramImpl_GL* ShaderProgram::getImpl<ShaderProgramImpl_GL>();
}
