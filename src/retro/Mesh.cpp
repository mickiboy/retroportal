#include "impl/GL/MeshImpl_GL.h"

namespace retro
{
    Mesh::Mesh()
    {
        impl = std::make_shared<MeshImpl_GL>();
    }

    Mesh::~Mesh()
    {
        impl.reset();
    }

    template<typename T> T* Mesh::getImpl()
    {
        return static_cast<T*>(impl.get());
    }

    template MeshImpl_GL* Mesh::getImpl<MeshImpl_GL>();

    void Mesh::addVertex(Vertex& vertex)
    {
        impl->addVertex(vertex);
    }

    void Mesh::addIndex(unsigned int index)
    {
        impl->addIndex(index);
    }

    void Mesh::build()
    {
        impl->build();
    }
}
