#include "managers/rendermanager.h"

#include "log.h"

#include "glad/glad.h"

namespace aurora::managers
{
    RenderManager::RenderManager() {}
    RenderManager::~RenderManager() {}
    void RenderManager::Initialize()
    {
        AURORA_INFO("OpenGL Info:\n  Vendor:\t{}\n  Renderer:\t{}\n  Version:\t{}",
            (const char*)glGetString(GL_VENDOR),
            (const char*)glGetString(GL_RENDERER),
            (const char*)glGetString(GL_VERSION))
        
        //Initialize OpenGL
        glEnable(GL_DEPTH_TEST); // Enable Depth in buffers
        glDepthFunc(GL_LEQUAL);  // If anything is further away, do not render it (Occlusion)

        glEnable(GL_BLEND); // Blend allows us to see through alpha (transparent objects)
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Sets the function for blend
        
        SetClearColour(0.263, 0.224, 0.51, 1); //Default color
    }

    void RenderManager::Shutdown()
    {
        while (mRenderCommands.size() > 0)
        {
            mRenderCommands.pop();
        }
    }

    void RenderManager::SetClearColour(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    void RenderManager::SetWireFrameMode(bool enabled)
    {
        if(enabled)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }

    void RenderManager::Submit(std::unique_ptr<graphics::rendercommands::RenderCommand> rc)
    {
        mRenderCommands.push(std::move(rc)); //move casts to rvalue reference {actually carries data and empties other site}
    }

    void RenderManager::Flush()
    {
        while(mRenderCommands.size() > 0)
        {
            auto rc = std::move(mRenderCommands.front());
            mRenderCommands.pop();

            rc->Execute();
        }
    }

    void RenderManager::Clear()
    {
        // AURORA_ASSERT(mRenderCommands.size() == 0, "Unflushed render commands in queue!");
        while (mRenderCommands.size() > 0)
        {
            mRenderCommands.pop();
        }

        // Clear the color of the screen // Clear any cache frame in depth
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}