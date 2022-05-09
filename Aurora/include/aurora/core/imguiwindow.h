#pragma once

// Forward declarations
typedef union SDL_Event SDL_Event;
using SDL_GLContext = void*;

namespace aurora::core
{
    struct ImguiWindowProperties
    {
        bool MoveFromTitleBarOnly = true;
        bool IsDockingEnabled = false;
        bool IsViewportEnabled = false;
    };

    class ImguiWindow
    {
    public:
        ImguiWindow();
        ~ImguiWindow();

        // Basic operations
        void Create(const ImguiWindowProperties& props);
        void Shutdown();

        // Queues the events
        void HandleSDLEvent(SDL_Event& e);

        bool WantCaptureMouse();
        bool WantCaptureKeyboard();

        void BeginRender();
        void EndRender();
    };
} // namespace aurora::core
