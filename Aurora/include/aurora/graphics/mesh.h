#pragma once

#include <cstdint>

namespace aurora::graphics
{
    class Mesh
    {
    public:
        // Params: VertexArray(Dynamic), VertexCount, dimensions(sorting with depth)
        Mesh(float* vertexArray, uint64_t vertexCount, uint64_t dimensions);
        Mesh(float* vertexArray, uint64_t vertexCount, uint64_t dimensions, uint64_t* elementArray, uint64_t elementCount);
        ~Mesh();

        void Bind();
        void Unbind();

        inline uint64_t GetVertexCount() const { return mVertexCount; }
        inline uint64_t GetElementCount() const { return mElementCount; }

    private:
        uint64_t mVertexCount; //Vertex Count & element count
        uint64_t mElementCount;
        uint32_t mVao, mEbo; //Holds ID from openGL
        uint32_t mPositionVbo; //Info about what to bind, unbind, delete when distruct
    };
    
}