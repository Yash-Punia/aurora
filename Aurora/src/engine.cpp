#include "engine.h"
#include <iostream>
#include "sdl2/SDL.h"

namespace aurora
{
    bool Initialize()
    {
        bool ret = true;

        if(SDL_Init(SDL_INIT_EVERYTHING) < 0) 
        {
            std::cout << "Error initializing SDL2: " << SDL_GetError() << std::endl;
        }
        else
        {
            SDL_version version;
            SDL_VERSION(&version);
            std::cout << "SDL " << (int32_t)version.major << "." << (int32_t)version.minor << "." << (int32_t)version.patch << std::endl;
        }
        return ret;
    }

    void Shutdown()
    {
        SDL_Quit();
    }
}