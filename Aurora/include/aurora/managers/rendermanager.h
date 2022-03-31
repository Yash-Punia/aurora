#pragma once

#include "graphics/rendercommands.h"

#include <queue>
#include <memory>

namespace aurora::managers
{
    class RenderManager
    {
    public:
        RenderManager();
        ~RenderManager();

        void Initialize();
        void Shutdown();

        void Clear();
        void SetClearColour(float r, float g, float b, float a);
        void SetWireFrameMode(bool enabled);

        void Submit(std::unique_ptr<graphics::rendercommands::RenderCommand> rc);
        
        // Execute submitted RenderCommands int the order they were received.
        // We can extend the API if we need to mitigate performance impact
        void Flush();

    private:
        std::queue<std::unique_ptr<graphics::rendercommands::RenderCommand>> mRenderCommands; 
    };
}