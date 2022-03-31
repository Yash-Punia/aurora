#include "log.h"

#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "graphics/rendercommands.h"

#include "glad/glad.h"

namespace aurora::graphics::rendercommands
{
    void RenderMesh::Execute()
    {
        //Returns weak pointer and nullptr if its already cleared
        std::shared_ptr<Mesh> mesh = mMesh.lock();
        std::shared_ptr<Shader> shader = mShader.lock();

        if(mesh && shader) 
        {
            mesh->Bind();
            shader->Bind();

            if(mesh->GetElementCount() > 0)
            {
                glDrawElements(GL_TRIANGLES, mesh->GetElementCount(), GL_UNSIGNED_INT, 0);
            }
            else
            {
                //Draw the actual data present in VBO(mode, first node, # of vertices)
                glDrawArrays(GL_TRIANGLE_STRIP, 0, mesh->GetVertexCount());
            }

            mesh->Unbind();
            shader->Unbind();
        }
        else 
        {
            AURORA_WARN("Attempting to execute RenderMesh with invalid data");
        }
    }
}