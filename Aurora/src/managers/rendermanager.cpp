#include "managers/rendermanager.h"

#include "engine.h"

#include "log.h"
#include "graphics/framebuffer.h"
#include "graphics/helpers.h"
#include "glad/glad.h"

namespace aurora::managers
{
    RenderManager::RenderManager() {}
    RenderManager::~RenderManager() {}
    void RenderManager::Initialize()
    {
        AURORA_INFO("OpenGL Info:\n  Vendor:\t{}\n  Renderer:\t{}\n  Version:\t{}",
                    (const char *)glGetString(GL_VENDOR),
                    (const char *)glGetString(GL_RENDERER),
                    (const char *)glGetString(GL_VERSION))

        // Initialize OpenGL
        glEnable(GL_DEPTH_TEST); // Enable Depth in buffers
        glDepthFunc(GL_LEQUAL);  // If anything is further away, do not render it (Occlusion)

        glEnable(GL_BLEND);                                // Blend allows us to see through alpha (transparent objects)
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Sets the function for blend

        SetClearColour(0.263, 0.224, 0.51, 1); // Default color
    }

    void RenderManager::Shutdown()
    {
        while (mRenderCommands.size() > 0)
        {
            mRenderCommands.pop();
        }
    }

    void RenderManager::SetViewport(int x, int y, int w, int h)
    {
        glViewport(x, y, w, h);
        AURORA_CHECK_GL_ERROR;
    }

    void RenderManager::SetClearColour(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        AURORA_CHECK_GL_ERROR;
    }

    void RenderManager::SetWireFrameMode(bool enabled)
    {
        if (enabled)
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
        mRenderCommands.push(std::move(rc)); // move casts to rvalue reference {actually carries data and empties other site}
    }

    void RenderManager::Flush()
    {
        while (mRenderCommands.size() > 0)
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

    void RenderManager::PushFramebuffer(std::shared_ptr<graphics::Framebuffer> framebuffer)
    {
        mFramebuffers.push(framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->GetFbo());
        uint32_t w, h;
        framebuffer->GetSize(w, h);
        SetViewport(0, 0, w, h);

        float r, g, b, a;
        framebuffer->GetClearColour(r, g, b, a);
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderManager::PopFramebuffer()
    {
        AURORA_ASSERT(mFramebuffers.size() == 0, "RenderManager::PopFramebuffer - empty stack");
        if (mFramebuffers.size() > 0)
        {
            mFramebuffers.pop();
            if (mFramebuffers.size() > 0)
            {
                auto nextFb = mFramebuffers.top();
                glBindFramebuffer(GL_FRAMEBUFFER, nextFb->GetFbo()); AURORA_CHECK_GL_ERROR;
                uint32_t w, h;
                nextFb->GetSize(w, h);
                SetViewport(0, 0, w, h);
            }
            else
            {
                glBindFramebuffer(GL_FRAMEBUFFER, 0); AURORA_CHECK_GL_ERROR;
                auto &window = Engine::Instance().GetWindow();
                int w, h;
                window.GetSize(w, h);
                SetViewport(0, 0, w, h);
            }
        }
    }

}