#pragma once

#include "core/window.h"

namespace aurora
{
    class Engine
    {
    public:
        static Engine &Instance();
        ~Engine() {}

        void Run();
        inline void Quit() { mIsRunning = false; }

    private:
        static Engine *sInstance;
        bool mIsRunning;
        core::Window mWindow;

        // Singleton
        Engine();
        bool Initialize();
        void Shutdown();
    };
}