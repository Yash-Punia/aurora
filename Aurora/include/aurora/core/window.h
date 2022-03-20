#pragma once

struct SDL_Window;

namespace aurora::core
{
    class Window
    {
    public:
        Window();
        ~Window();

        bool Create();
        void Shutdown();

        // Queues the events
        void PumpEvents();


    private:
        SDL_Window* mWindow;
    };
} // namespace aurora::core