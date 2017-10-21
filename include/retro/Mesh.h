#pragma once

#include <memory>

namespace retro
{
    /**
     * Vertex structure with 2 attributes.
     *
     * Those attributes are: Position (3 elements, xyz) and Color (4 elements, rgba).
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
