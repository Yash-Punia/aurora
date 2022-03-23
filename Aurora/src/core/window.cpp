#include "core/window.h"
#include "engine.h"
#include "log.h"

#include "SDL2/SDL.h"
#include "glad/glad.h"

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
        mWindow = SDL_CreateWindow("Aurora Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        if(!mWindow)
        {
            AURORA_ERROR("\n Error creating window: {}", SDL_GetError());
            return false;
        }

        // Initializing OpenGL with SDL
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // To reduce flickering

        SDL_SetWindowMinimumSize(mWindow, 200, 200);

        mGLContext = SDL_GL_CreateContext(mWindow);
        if (mGLContext == nullptr)
        {
            AURORA_ERROR("Error creating OpenGL context: {}", SDL_GetError());
            return false;
        }

        // Mapping all the openGL functions to their respective function pointers
        gladLoadGLLoader(SDL_GL_GetProcAddress);

        // TODO: Move this to a renderer initialization
        glEnable(GL_DEPTH_TEST); // Enable Depth in buffers
        glDepthFunc(GL_LEQUAL);  // If anything is further away, do not render it (Occlusion)

        glEnable(GL_BLEND); // Blend allows us to see through alpha (transparent objects)
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Sets the function for blend

        // violet color
        glClearColor(0.263, 0.224, 0.51, 1);

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

    void Window::BeginRender()
    {
        // Clear the color of the screen // Clear any cache frame in depth
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::EndRender()
    {
        // Actually needed to see, because it swaps the buffer 
        SDL_GL_SwapWindow(mWindow);
    }

} // namespace aurora::core
