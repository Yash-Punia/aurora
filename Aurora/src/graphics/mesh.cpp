#include "graphics/mesh.h"

#include "glad/glad.h"

#include <cstdint>

namespace aurora::graphics
{
    Mesh::Mesh(float* vertexArray, uint64_t vertexCount, uint64_t dimensions)
        : mVertexCount(vertexCount)
        , mEbo(0)
        , mElementCount(0)
    {
        //NOTE: VAO doesn't actually store the data but has reference to VBO
        glGenVertexArrays(1, &mVao); //Generates the VAO(number, reference to storage)
        glBindVertexArray(mVao); //Binds the VAO {Makes the new array active}
        
        glGenBuffers(1, &mPositionVbo); //Generates VBO(number, reference to storage)
        glBindBuffer(GL_ARRAY_BUFFER, mPositionVbo); //Allows to use buffer of type gl_array_buffer
        glBufferData(GL_ARRAY_BUFFER, vertexCount * dimensions * sizeof(float), vertexArray, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0); //Enables attribute passing to shader(index: 0)
        //Decribes shader how to interpret VAO (index, #component per vertex, type, normalize?, size between 2 consecutive vertices in interleaving data {x, y, (r, g, b)}, offset)
        glVertexAttribPointer(0, dimensions, GL_FLOAT, GL_FALSE, 0, 0);
        glDisableVertexAttribArray(0); //Disable VAO after rendering
        glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind the buffer to free it

        glBindVertexArray(0); //Unbind just to be sure there's no other VAO active
    }

     Mesh::Mesh(float* vertexArray, uint64_t vertexCount, uint64_t dimensions, uint32_t* elementArray, uint64_t elementCount)
        : Mesh(vertexArray, vertexCount, dimensions)
    {
        mElementCount = elementCount;

        glBindVertexArray(mVao);
        
        glGenBuffers(1, &mEbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementCount * sizeof(uint32_t), elementArray, GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    Mesh::~Mesh() 
    {
        glDeleteBuffers(1, &mPositionVbo); //Delete binded VBOs
        if(mEbo != 0) 
        {
            glDeleteBuffers(1, &mEbo);
        }
        glDeleteVertexArrays(1, &mVao); //Delete VAO
    }

    void Mesh::Bind() 
    {
        glBindVertexArray(mVao);
        glEnableVertexAttribArray(0); //Enable attrib attribute so that mesh has access
    }

    void Mesh::Unbind() 
    {
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
    }
}