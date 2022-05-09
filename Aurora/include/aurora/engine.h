#pragma once

#include "core/window.h"
#include "managers/logmanager.h"
#include "managers/rendermanager.h"

namespace aurora
{
    class App;
    class Engine
    {
    public:
        static Engine &Instance(); //Public access to get the reference of available instance of engine.
        ~Engine() {} 

        void Run(App* app);
        inline void Quit() { mIsRunning = false; }

        inline App& GetApp() { return *mApp; }
        inline core::Window& GetWindow() { return mWindow; }

        //Managers
        inline managers::RenderManager& GetRenderManager() { return mRenderManager; } 

    private:
        static Engine *sInstance; //Pointer to the only instance of Engine
        bool mIsRunning;
        bool mIsInitialized;
        core::Window mWindow;
        App* mApp;

        //Managers
        managers::LogManager mLogManager;
        managers::RenderManager mRenderManager;

        // Singleton
        Engine();
        bool Initialize();
        void Shutdown();
        void Update();
        void Render();
    };
}