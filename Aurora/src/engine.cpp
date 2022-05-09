#include <iostream>

#include "engine.h"
#include "log.h"
#include "app.h"

#include "input/mouse.h"
#include "input/keyboard.h"
#include "input/joystick.h"

#include "sdl2/SDL.h"

namespace aurora
{
    // public
    Engine &Engine::Instance()
    {
        if (!sInstance)
        {
            sInstance = new Engine();
        }
        return *sInstance;
    }

    void Engine::Run(App *app)
    {
        mLogManager.Initialize();
        AURORA_ASSERT(!mApp, "Attempting to call Engine::Run when a valid App is already running!");
        if (mApp)
            return;
        mApp = app;
        if (Initialize())
        {
            // mRenderManager.SetWireFrameMode(false); // Make it true for only the line
            while (mIsRunning) // Game Loop
            {
                Update();
                Render();
            }

            Shutdown();
        }
    }

    // private
    void Engine::Update()
    {
        mWindow.PumpEvents();
        mApp->Update();
    }

    void Engine::Render()
    {
        mWindow.BeginRender();

        mApp->Render();

        mWindow.EndRender();
    }

    // Cross check initialization of engine
    bool Engine::Initialize()
    {
        bool ret = false;
        // AURORA_ASSERT(!mIsInitialized, "Attempting to call Engine::Initialize more than once!");

        if (!mIsInitialized)
        {

            AURORA_TRACE("AuroraEngine v{}.{}", 0, 1);

            if (SDL_Init(SDL_INIT_EVERYTHING) < 0) // Negative value in case of error
            {
                AURORA_ERROR("Error initializing SDL2: {}", SDL_GetError());
            }
            else
            {
                SDL_version version;
                SDL_VERSION(&version);
                AURORA_INFO("SDL v{}.{}.{}", (int32_t)version.major, (int32_t)version.minor, (int32_t)version.patch);

                core::WindowProperties props = mApp->GetWindowProperties();

                // Actually creating the window
                if (mWindow.Create(props))
                {
                    // Initialize Managers
                    mRenderManager.Initialize();

                    ret = true;
                    mIsRunning = true;
                    mIsInitialized = true;

                    // Initialize Input
                    input::Mouse::Initialize();
                    input::Keyboard::Initialize();

                    // Initialize Client
                    mApp->Initialize();
                }
            }

            if (!ret)
            {
                AURORA_ERROR("Engine Initialization failed. Shutting down. {}", SDL_GetError());
                Shutdown();
            }
        }

        return ret;
    }

    void Engine::Shutdown()
    {
        mIsRunning = false;
        mIsInitialized = false;

        // Shutdown Client app
        mApp->Shutdown();

        //Shutdown Inputs
        input::Joystick::Shutdown();

        // Shutdown Managers - usually shut down in reverse order
        mRenderManager.Shutdown();
        mLogManager.Shutdown();

        // Shutdown SDL
        mWindow.Shutdown();
        SDL_Quit();
    }

    // Singleton
    Engine *Engine::sInstance = nullptr;

    Engine::Engine()
        : mIsRunning(false),
          mIsInitialized(false),
          mApp(nullptr)
    {
    }

}