#include <glad/glad.h>
#include <retro/Log.h>
#include "ShaderProgramImpl_GL.h"

namespace retro
{
    ShaderProgramImpl_GL::ShaderProgramImpl_GL(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
    {
        auto vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderCode);
        auto fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

        id = linkProgram(vertexShader, fragmentShader);

        // Shaders itself can be deleted after linking into a program
        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);
    }

    ShaderProgramImpl_GL::~ShaderProgramImpl_GL()
    {
        glDeleteProgram(id);
    }

    unsigned int ShaderProgramImpl_GL::compileShader(unsigned int type, const std::string& code)
    {
        // Allocate a shader
        auto shader = glCreateShader(type);

        // Convert the code to a C string
        auto codeAsCStr = code.c_str();

        // Apply the code and compile
        glShaderSource(shader, 1, &codeAsCStr, nullptr);
        glCompileShader(shader);

        GLint success;
        GLchar infoLog[1024];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        // Check status of the compilation
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            Log::error("Shader compilation failed: " + std::string(infoLog));
        }

        return shader;
    }

    unsigned int ShaderProgramImpl_GL::linkProgram(unsigned int vertexShader, unsigned int fragmentShader)
    {
        // Allocate a program
        auto program = glCreateProgram();

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);

        GLint success;
        GLchar infoLog[1024];
        glGetProgramiv(program, GL_LINK_STATUS, &success);

        // Check status of the linking
        if (!success) {
            glGetProgramInfoLog(program, 1024, nullptr, infoLog);
            Log::error("Shader program linking failed: " + std::string(infoLog));
        }

        return program;
    }
}
