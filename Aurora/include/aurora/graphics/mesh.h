#pragma once

#include <cstdint>

namespace aurora::graphics
{
    class Mesh
    {
    public:
        // Params: VertexArray(Dynamic), VertexCount, dimensions(sorting with depth)
        Mesh(float* vertexArray, uint64_t vertexCount, uint64_t dimensions);
        ~Mesh();

        void Bind();
        void Unbind();

        inline uint32_t GetVertexCount() const { return mVertexCount; }

    private:
        uint32_t mVertexCount; //Vertex Count
        uint32_t mVao; //Holds ID from openGL
        uint32_t mPositionVbo; //Info about what to bind, unbind, delete when distruct
    };
    
}