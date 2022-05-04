#include "core/window.h"
#include "engine.h"
#include "log.h"

#include "SDL2/SDL.h"
#include "glad/glad.h"
#include "input/mouse.h"
#include "input/keyboard.h"
#include "input/joystick.h"

#include "imgui/imgui.h"

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
        if (!mWindow)
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

        mImguiWindow.Create();

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
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                Engine::Instance().Quit();
                break;

            case SDL_CONTROLLERDEVICEADDED:
                input::Joystick::OnJoystickConnected(e.cdevice);
                break;

            case SDL_CONTROLLERDEVICEREMOVED:
                input::Joystick::OnJoystickDisconnected(e.cdevice);
                break;
            
            default:
                break;
            }
        }

        // Update input
        aurora::input::Mouse::Update();
        aurora::input::Keyboard::Update();
        aurora::input::Joystick::Update();
        mImguiWindow.HandleSDLEvent(e);
    }

    void Window::BeginRender()
    {
        Engine::Instance().GetRenderManager().Clear();
    }

    void Window::EndRender()
    {
        //Embedding Imgui window inside window to render imgui first before buffer swap
        mImguiWindow.BeginRender();
        ImGui::ShowDemoWindow();
        mImguiWindow.EndRender();

        // Actually needed to see, because it swaps the buffer
        SDL_GL_SwapWindow(mWindow);
    }

    void Window::GetSize(int &w, int &h)
    {
        SDL_GetWindowSize(mWindow, &w, &h);
    }

} // namespace aurora::core
