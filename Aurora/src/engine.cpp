#include <iostream>

#include "engine.h"
#include "log.h"

#include "graphics/mesh.h"
#include "graphics/shader.h"

#include "input/mouse.h"
#include "input/keyboard.h"

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
            float vertices[]
            {
                 0.5f,  0.5f, 0.f,
                 0.5f, -0.5f, 0.f,
                -0.5f, -0.5f, 0.f,
                -0.5f,  0.5f, 0.f
            };

            uint32_t elements[]
            {
                0, 3, 1,
                1, 3, 2
            };
            // std::shared_ptr<graphics::Mesh> mesh = std::make_shared<graphics::Mesh> (&vertices[0], 3, 3); //For vertex only 
            std::shared_ptr<graphics::Mesh> mesh = std::make_shared<graphics::Mesh> (&vertices[0], 4, 3, &elements[0], 6);

            //Test Shader
            const char* vertexShader = R"(
                #version 410 core
                layout (location = 0) in vec3 position;
                out vec3 vpos;
                uniform vec2 offset = vec2(0.5);
                void main()
                {
                    vpos = position + vec3(offset, 0);
                    gl_Position = vec4(position, 1.0);
                }
            )";

          const char* fragmentShader = R"(
                #version 410 core
                out vec4 outColor;
                in vec3 vpos;

                uniform vec3 color = vec3(0.0);
                void main()
                {
                    outColor = vec4(vpos, 1.0);
                }
            )";

            std::shared_ptr<graphics::Shader> shader = std::make_shared<graphics::Shader> (vertexShader, fragmentShader);
            shader->SetUniformFloat3("color", 1, 0, 0);

            // mRenderManager.SetWireFrameMode(false); // Make it true for only the line

            float xKeyOffset = 0.0f;
            float yKeyOffset = 0.0f;
            float keySpeed = 0.001f;

            while (mIsRunning) // Game Loop
            {
                mWindow.PumpEvents();

                // AURORA_TRACE("X: {}, Y: {}, {}{}{}{}{}", input::Mouse::X(), input::Mouse::Y(), 
                //     input::Mouse::Button(AURORA_INPUT_MOUSE_LEFT),
                //     input::Mouse::Button(AURORA_INPUT_MOUSE_MIDDLE),
                //     input::Mouse::Button(AURORA_INPUT_MOUSE_RIGHT),
                //     input::Mouse::Button(AURORA_INPUT_MOUSE_X1),
                //     input::Mouse::Button(AURORA_INPUT_MOUSE_X2));

                int windowW = 0;
                int windowH = 0;
                GetWindow().GetSize(windowW, windowH);

                float xNormalized = (float) input::Mouse::X() / (float) windowW;
                float yNormalized = (float) (windowH - input::Mouse::Y()) / (float) windowH;

                // Use the above for smooth transition, this DX will use delta in x positions
                // float xNormalized = (float) input::Mouse::DX() / 100.f;
                // float yNormalized = (float) input::Mouse::DY() / 100.f;

                if(input::Keyboard::Key(AURORA_INPUT_KEY_LEFT))  { xKeyOffset -= keySpeed; }
                if(input::Keyboard::Key(AURORA_INPUT_KEY_RIGHT)) { xKeyOffset += keySpeed; }
                if(input::Keyboard::Key(AURORA_INPUT_KEY_UP))    { yKeyOffset += keySpeed; }
                if(input::Keyboard::Key(AURORA_INPUT_KEY_DOWN))  { yKeyOffset -= keySpeed; }

                shader->SetUniformFloat2("offset", xNormalized + xKeyOffset, yNormalized + yKeyOffset);

                mWindow.BeginRender();

                auto rc = std::make_unique<graphics::rendercommands::RenderMesh>(mesh, shader);
                mRenderManager.Submit(std::move(rc));
                mRenderManager.Flush();

                mWindow.EndRender();
            }

            Shutdown();
        }
    }

    // private

    // Cross check initialization of engine
    bool Engine::Initialize()
    {
        bool ret = false;
        // AURORA_ASSERT(!mIsInitialized, "Attempting to call Engine::Initialize more than once!");
        
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
                    // Initialize Managers
                    mRenderManager.Initialize();

                    ret = true;
                    mIsRunning = true;
                    mIsInitialized = true;

                    // Initialize Input
                    input::Mouse::Initialize();
                    input::Keyboard::Initialize();
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

        // Shutdown Managers - usually shut down in reverse order
        mRenderManager.Shutdown();
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