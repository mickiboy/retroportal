#include <glad/glad.h>
#include "MeshImpl_GL.h"

namespace retro
{
    MeshImpl_GL::MeshImpl_GL()
    {
        // Create a vertex array object
        glGenVertexArrays(1, &vao);

        // Create vertex buffer object and element buffer object (for the indices)
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
    }

    MeshImpl_GL::~MeshImpl_GL()
    {
        glDeleteBuffers(1, &ebo);
        glDeleteBuffers(1, &vbo);

        glDeleteVertexArrays(1, &vao);
    }

    void MeshImpl_GL::addVertex(Vertex& vertex)
    {
        vertices.push_back(vertex);
    }

    void MeshImpl_GL::addIndex(unsigned int index)
    {
        indices.push_back(index);
    }

    void MeshImpl_GL::build()
    {
        // Save the number of indices for the renderer
        indicesCount = indices.size();

        // Bind the vertex array object
        glBindVertexArray(vao);

        // Load the vertices into the vertex buffer object (on the GPU)
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        // Load the indices into the element buffer object (on the GPU)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        // Define the position attribute of the vertex
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), reinterpret_cast<void*>(0 * sizeof(float)));
        glEnableVertexAttribArray(0);

        // Define the index color attribute of the vertex
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Unbind the vertex array object
        glBindVertexArray(0);
    }
}
