#pragma once

#include "../graphics/rendercommands.h"

#include "external/glm/glm.hpp"

#include <queue>
#include <stack>
#include <memory>

#define AURORA_SUBMIT_RC(type, ...) std::move(std::make_unique<aurora::graphics::rendercommands::type>(__VA_ARGS__))

namespace aurora::managers
{
    class RenderManager
    {
        friend class graphics::rendercommands::PushFramebuffer;
        friend class graphics::rendercommands::PopFramebuffer;

    public:
        RenderManager();
        ~RenderManager();

        void Initialize();
        void Shutdown();

        void Clear();
        void SetClearColour(const glm::vec4 cc);
        void SetWireFrameMode(bool enabled);
        void SetViewport(const glm::ivec4 dimensions);
        void Submit(std::unique_ptr<graphics::rendercommands::RenderCommand> rc);
        
        // Execute submitted RenderCommands int the order they were received.
        // We can extend the API if we need to mitigate performance impact
        void Flush();



    private:
        std::queue<std::unique_ptr<graphics::rendercommands::RenderCommand>> mRenderCommands; 
        std::stack<std::shared_ptr<graphics::Framebuffer>> mFramebuffers;

        void PushFramebuffer(std::shared_ptr<graphics::Framebuffer> framebuffer);
        void PopFramebuffer();
    };
}