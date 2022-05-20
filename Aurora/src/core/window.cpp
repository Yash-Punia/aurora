#include "core/window.h"
#include "engine.h"
#include "log.h"
#include "app.h"

#include "SDL2/SDL.h"
#include "glad/glad.h"

#include "input/mouse.h"
#include "input/keyboard.h"
#include "input/joystick.h"
#include "graphics/framebuffer.h"

namespace aurora::core
{
    WindowProperties::WindowProperties()
    {
        title = "Aurora Editor";
        x = SDL_WINDOWPOS_CENTERED;
        y = SDL_WINDOWPOS_CENTERED;
        w = 1920;
        h = 1080;
        wMin = 320;
        hMin = 180;
        flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
        clearColour = glm::vec3(
            0.263,
            0.224,
            0.51);
    }

    Window::Window() : mWindow(nullptr) {}
    Window::~Window()
    {
        if (mWindow)
        {
            Shutdown();
        }
    }

    bool Window::Create(const WindowProperties& props)
    {
        mWindow = SDL_CreateWindow(props.title.c_str(), props.x, props.y, props.w, props.h, props.flags);
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
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); 

        SDL_SetWindowMinimumSize(mWindow, props.wMin, props.hMin);

        mGLContext = SDL_GL_CreateContext(mWindow);
        if (mGLContext == nullptr)
        {
            AURORA_ERROR("Error creating OpenGL context: {}", SDL_GetError());
            return false;
        }

        // Mapping all the openGL functions to their respective function pointers
        gladLoadGLLoader(SDL_GL_GetProcAddress);

        // We don't need this anymore as we are manually rendering it 
        // onto the framebuffer first and not the window
        // Engine::Instance().GetRenderManager().SetClearColour(props.ccR, props.ccG, props.ccB, 1.f);

        mFramebuffer = std::make_shared<graphics::Framebuffer>(props.w, props.h);
        
        glm::vec4 cc { props.clearColour.r, props.clearColour.g, props.clearColour.b, 1.f };
        mFramebuffer->SetClearColour(cc);

        mImguiWindow.Create(props.imguiProps);

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
            mImguiWindow.HandleSDLEvent(e);
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
        if(!mImguiWindow.WantCaptureMouse()) 
        {
            aurora::input::Mouse::Update();
        }
        if(!mImguiWindow.WantCaptureKeyboard()) 
        {
            aurora::input::Keyboard::Update();
        }
        aurora::input::Joystick::Update();
    }

    void Window::BeginRender()
    {
        auto& rm = Engine::Instance().GetRenderManager();
        rm.Clear();
        rm.Submit( AURORA_SUBMIT_RC(PushFramebuffer, mFramebuffer) );
    }

    void Window::EndRender()
    {
        auto& rm = Engine::Instance().GetRenderManager();
        rm.Submit( AURORA_SUBMIT_RC(PopFramebuffer) );
        rm.Flush();
        //Embedding Imgui window inside window to render imgui first before buffer swap
        mImguiWindow.BeginRender();
        Engine::Instance().GetApp().ImguiRender();
        mImguiWindow.EndRender();

        // Actually needed to see, because it swaps the buffer
        SDL_GL_SwapWindow(mWindow);
    }

    glm::ivec2 Window::GetSize()
    {
        int w, h;
        SDL_GetWindowSize(mWindow, &w, &h);
        return glm::ivec2(w, h);
    }

} // namespace aurora::core
