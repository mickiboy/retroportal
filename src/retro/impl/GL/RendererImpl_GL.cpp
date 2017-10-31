#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <retro/Drawable.h>
#include "../GLFW/ApplicationImpl_GLFW.h"
#include "MeshImpl_GL.h"
#include "RendererImpl_GL.h"
#include "ShaderProgramImpl_GL.h"
#include "TextureImpl_GL.h"

namespace retro
{
    RendererImpl_GL::RendererImpl_GL(Application& app) : app(app)
    {
        int width;
        int height;
        app.getSize(&width, &height);

        // Set black as a clearing color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // Set the viewport to the client size of the window
        glViewport(0, 0, width, height);

        model = glm::mat4(1.0f);
        view = glm::mat4(1.0f);
        projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, 0.0f, 1.0f);
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
        auto textureImpl = drawable.getTexture().getImpl<TextureImpl_GL>();

        if (textureImpl->id != 0) {
            glBindTexture(GL_TEXTURE_2D, textureImpl->id);
        }

        // Bind the shader program
        glUseProgram(shaderProgramImpl->id);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgramImpl->id, "u_model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramImpl->id, "u_view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramImpl->id, "u_projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // Draw the object
        glBindVertexArray(meshImpl->vao);
        glDrawElements(GL_TRIANGLES, meshImpl->indicesCount, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }

    void RendererImpl_GL::swapBuffers()
    {
        app.getImpl<ApplicationImpl_GLFW>()->swapBuffers();
    }

    void RendererImpl_GL::receiveEvent(const events::Resize& e)
    {
        glViewport(0, 0, e.width, e.height);

        projection = glm::ortho(0.0f, static_cast<float>(e.width), static_cast<float>(e.height), 0.0f, 0.0f, 1.0f);
    }
}
