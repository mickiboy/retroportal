#pragma once

#include <string>

namespace retro
{
    namespace ui
    {
        namespace shaders
        {
            namespace vertex
            {
                const std::string& positionColorTexture =
                    "#version 410 core\n"
                    ""
                    "layout (location = 0) in vec3 a_pos;"
                    "layout (location = 1) in vec4 a_color;"
                    "layout (location = 2) in vec2 a_texCoord;"
                    ""
                    "out vec4 v_color;"
                    "out vec2 v_texCoord;"
                    ""
                    "uniform mat4 u_model;"
                    "uniform mat4 u_view;"
                    "uniform mat4 u_projection;"
                    ""
                    "void main()"
                    "{"
                    "    gl_Position = u_projection * u_view * u_model * vec4(a_pos, 1.0);"
                    "    v_color = a_color;"
                    "    v_texCoord = a_texCoord;"
                    "}";
            }

            namespace fragment
            {
                const std::string& colorTexture =
                    "#version 410 core\n"
                    ""
                    "in vec4 v_color;"
                    "in vec2 v_texCoord;"
                    ""
                    "out vec4 f_fragColor;"
                    ""
                    "uniform sampler2D u_tex;"
                    ""
                    "void main()"
                    "{"
                    "    f_fragColor = texture(u_tex, v_texCoord) * v_color;"
                    "}";
            }
        }
    }
}
