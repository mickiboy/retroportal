#pragma once

#include <string>

namespace retro
{
    namespace ui
    {
        const std::string& defaultVertexShader =
            "#version 410 core\n"
            ""
            "layout (location = 0) in vec3 a_pos;"
            "layout (location = 1) in vec4 a_color;"
            ""
            "out vec4 v_color;"
            ""
            "void main()"
            "{"
            "    gl_Position = vec4(a_pos, 1.0);"
            "    v_color = a_color;"
            "}";

        const std::string& defaultFragmentShader =
            "#version 410 core\n"
            ""
            "in vec4 v_color;"
            ""
            "out vec4 f_fragColor;"
            ""
            "void main()"
            "{"
            "    f_fragColor = v_color;"
            "}";
    }
}
