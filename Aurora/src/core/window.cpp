#include "core/window.h"
#include "engine.h"
#include "log.h"

#include "SDL2/SDL.h"

namespace aurora::core
{
    Window::Window() : mWindow(nullptr) {}
    Window::~Window()
    {
        if (mWindow)
        {
            Shutdown();
        }
    }

    bool Window::Create()
    {
        mWindow = SDL_CreateWindow("Aurora Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
        if(!mWindow)
        {
            AURORA_ERROR("\n Error creating window: {}", SDL_GetError());
            return false;
        }
        return true;
    }
    
    void Window::Shutdown()
    {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
    }

    void Window::PumpEvents()
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                Engine::Instance().Quit();
                break;
            
            default:
                break;
            }
        }
    }

} // namespace aurora::core
