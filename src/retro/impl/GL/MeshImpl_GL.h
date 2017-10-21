#pragma once

#include <vector>
#include <retro/Mesh.h>

namespace retro
{
    class MeshImpl_GL : public Mesh::Impl
    {
    public:
        unsigned int vao = 0;
        int indicesCount = 0;

        MeshImpl_GL();
        virtual ~MeshImpl_GL();

        void addVertex(Vertex& vertex) override;
        void addIndex(unsigned int index) override;
        void build() override;

    private:
        unsigned int vbo = 0;
        unsigned int ebo = 0;

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
    };
}
