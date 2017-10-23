#pragma once

#include <memory>
#include <glm/glm.hpp>

namespace retro
{
    /**
     * Vertex structure with 3 attributes.
     *
     * Those attributes are: Position (3 elements, xyz), color (4 elements, rgba) and texture (2 elements, uv).
     */
    struct Vertex
    {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 texCoord;
    };

    /**
     * A mesh holds the data for drawing objects.
     */
    class Mesh
    {
    public:
        class Impl;

        Mesh();

        ~Mesh();

        /**
         * Returns the current implementation.
         */
        template<typename T> T* getImpl();

        void addVertex(Vertex& vertex);

        void addIndex(unsigned int index);

        /**
         * Must be called before drawing.
         */
        void build();

    private:
        std::shared_ptr<Impl> impl;

    public:
        class Impl
        {
        public:
            virtual ~Impl() = default;

            virtual void addVertex(Vertex& vertex) = 0;
            virtual void addIndex(unsigned int index) = 0;
            virtual void build() = 0;
        };
    };
}
