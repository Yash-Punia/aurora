#pragma once

#include "core/window.h"

//aurora namespace to look into it in other places
namespace aurora
{
    class Engine
    {
    public:
        static Engine &Instance(); //Public access to get the reference of available instance of engine.
        ~Engine() {} 

        void Run();
        inline void Quit() { mIsRunning = false; }

    private:
        static Engine *sInstance; //Pointer to the only instance of Engine
        bool mIsRunning;
        core::Window mWindow;

        // Singleton
        Engine();
        bool Initialize();
        void Shutdown();
    };
}