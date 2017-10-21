#pragma once

#include <memory>

namespace retro
{
    /**
     * Vertex structure with 3 attributes.
     *
     * Those attributes are: Position (3 elements, xyz), color (4 elements, rgba) and texture (2 elements, uv).
     */
    struct Vertex
    {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float a = 0.0f;

        float u = 0.0f;
        float v = 0.0f;
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
