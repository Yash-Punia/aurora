#pragma once

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


    private:
        // Forward declarations used here
        SDL_Window* mWindow;
        SDL_GLContext mGLContext;
    };
} // namespace aurora::core
