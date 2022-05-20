#pragma once

#include "imguiwindow.h"
#include "../graphics/framebuffer.h"

#include <string>
#include <memory>

#include "external/glm/glm.hpp"

namespace aurora::graphics
{
    class Framebuffer;
}

// Forward declarations
struct SDL_Window;
using SDL_GLContext = void*;

namespace aurora::core
{
    struct WindowProperties
    {
        std::string title;
        int x, y, w, h;
        int wMin, hMin;
        int flags;
        glm::vec3 clearColour;
        ImguiWindowProperties imguiProps;

        WindowProperties();
    };

    class Window
    {
    public:
        Window();
        ~Window();

        // Basic operations
        bool Create(const WindowProperties& props);
        void Shutdown();

        // Queues the events
        void PumpEvents();

        void BeginRender();
        void EndRender();

        glm::ivec2 GetSize();

        inline SDL_Window* GetSDLWindow() { return mWindow; }
        inline SDL_GLContext GetGLContext() { return mGLContext; }
        inline graphics::Framebuffer* GetFramebuffer() { return mFramebuffer.get(); }
    private:
        // Forward declarations used here
        SDL_Window* mWindow;
        SDL_GLContext mGLContext;
        ImguiWindow mImguiWindow;
        std::shared_ptr<graphics::Framebuffer> mFramebuffer;
    };
} // namespace aurora::core
