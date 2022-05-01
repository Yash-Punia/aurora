#pragma once

// Forward declarations
typedef union SDL_Event SDL_Event;
using SDL_GLContext = void*;

namespace aurora::core
{
    class ImguiWindow
    {
    public:
        ImguiWindow();
        ~ImguiWindow();

        // Basic operations
        void Create();
        void Shutdown();

        // Queues the events
        void HandleSDLEvent(SDL_Event& e);

        void BeginRender();
        void EndRender();
    };
} // namespace aurora::core
