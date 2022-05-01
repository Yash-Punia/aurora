#pragma once

#include "imguiwindow.h"

// Forward declarations
struct SDL_Window;
using SDL_GLContext = void*;


namespace aurora::core
{
    class Window
    {
    public:
        Window();
        ~Window();

        // Basic operations
        bool Create();
        void Shutdown();

        // Queues the events
        void PumpEvents();

        void BeginRender();
        void EndRender();

        void GetSize(int& w, int& h);

        SDL_Window* GetSDLWindow() { return mWindow; }
        SDL_GLContext GetGLContext() { return mGLContext; }
    private:
        // Forward declarations used here
        SDL_Window* mWindow;
        SDL_GLContext mGLContext;
        ImguiWindow mImguiWindow;
    };
} // namespace aurora::core
