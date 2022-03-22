#include <iostream>

#include "engine.h"
#include "log.h"

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

    void Engine::Run()
    {
        if (Initialize())
        {
            while (mIsRunning) // Game Loop
            {
                mWindow.PumpEvents();
            }

            Shutdown();
        }
    }

    // private

    // Cross check initialization of engine
    bool Engine::Initialize()
    {
        bool ret = false;

        AURORA_ASSERT(!mIsInitialized, "Attempting to call Engine::Initialize more than once!");
        
        if(!mIsInitialized) {
            mLogManager.Initialize();

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

                // Actually creating the window
                if (mWindow.Create())
                {
                    ret = true;
                    mIsRunning = true;
                    mIsInitialized = true;
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

        //Managers - usually shut down in reverse order
        mLogManager.Shutdown();


        //Shutdown SDL
        mWindow.Shutdown();
        SDL_Quit();
    }

    // Singleton
    Engine *Engine::sInstance = nullptr;

    Engine::Engine() 
        : mIsRunning(false),
          mIsInitialized(false)
    {}

}