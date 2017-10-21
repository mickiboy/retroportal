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
        auto textureImpl = drawable.getTexture().getImpl<TextureImpl_GL>();

        glBindTexture(GL_TEXTURE_2D, textureImpl->id);

        // Bind the shader program
        glUseProgram(shaderProgramImpl->id);

        glm::mat4 model(1.0f);
        auto modelLoc = glGetUniformLocation(shaderProgramImpl->id, "u_model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glm::mat4 view(1.0f);
        auto viewLoc = glGetUniformLocation(shaderProgramImpl->id, "u_view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 projection(1.0f);
        projection = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, 0.0f, 1.0f);
        auto projectionLoc = glGetUniformLocation(shaderProgramImpl->id, "u_projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

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
