#include "graphics/mesh.h"

#include "glad/glad.h"

namespace aurora::graphics
{
    Mesh::Mesh(float* vertexArray, uint64_t vertexCount, uint64_t dimensions)
        : mVertexCount(vertexCount)
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

    Mesh::~Mesh() 
    {
        glDeleteBuffers(1, &mPositionVbo); //Delete binded VBOs
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