#include <glad/glad.h>
#include <retro/Drawable.h>
#include "../GLFW/ApplicationImpl_GLFW.h"
#include "MeshImpl_GL.h"
#include "RendererImpl_GL.h"
#include "ShaderProgramImpl_GL.h"

namespace retro
{
    RendererImpl_GL::RendererImpl_GL(Application& app) : app(app)
    {
        // Set black as a clearing color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    void RendererImpl_GL::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void RendererImpl_GL::draw(Drawable& drawable)
    {
        // Get the implementations of the mesh and the shader program
        auto meshImpl = drawable.getMesh().getImpl<MeshImpl_GL>();
        auto shaderProgramImpl = drawable.getShaderProgram().getImpl<ShaderProgramImpl_GL>();

        // Bind the shader program
        glUseProgram(shaderProgramImpl->id);

        // Draw the object
        glBindVertexArray(meshImpl->vao);
        glDrawElements(GL_TRIANGLES, meshImpl->indicesCount, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }

    void RendererImpl_GL::swapBuffers()
    {
        app.getImpl<ApplicationImpl_GLFW>()->swapBuffers();
    }
}
