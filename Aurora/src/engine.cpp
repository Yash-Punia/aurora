#include <iostream>
#include "engine.h"
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

        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) // Negative value in case of error
        {
            std::cout << "Error initializing SDL2: " << SDL_GetError() << std::endl;
        }
        else
        {
            SDL_version version;
            SDL_VERSION(&version);
            std::cout << "SDL " << (int32_t)version.major << "." << (int32_t)version.minor << "." << (int32_t)version.patch << std::endl;

            // Actually creating the window
            if (mWindow.Create())
            {
                ret = true;
                mIsRunning = true;
            }
        }

        if (!ret)
        {
            std::cout << "Engine Initialization failed. Shutting down." << std::endl;
            Shutdown();
        }

        return ret;
    }

    void Engine::Shutdown()
    {
        mWindow.Shutdown();
        SDL_Quit();
    }

    // Singleton
    Engine *Engine::sInstance = nullptr;

    Engine::Engine() : mIsRunning(false)
    {
    }

}