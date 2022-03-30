#include <iostream>

#include "engine.h"
#include "log.h"

#include "graphics/mesh.h"
#include "graphics/shader.h"

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
            // Test Mesh
            // Triangle
            // float vertices[]
            // {
            //     -0.5f, -0.5f, 0.f,
            //      0.f,   0.5f, 0.f,
            //      0.5f, -0.5f, 0.f
            // };
            float vertices[]
            {
                 0.5f,  0.5f, 0.f,
                 0.5f, -0.5f, 0.f,
                -0.5f, -0.5f, 0.f,
                -0.5f,  0.5f, 0.f
            };

            uint64_t elements[]
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
                void main()
                {
                    vpos = position + vec3(0.5, 0.5, 0);
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

            // const char* fragmentShader = R"(
            //     #version 410 core
            //     out vec4 outColor;
            //     void main()
            //     {
            //         outColor = vec4(1.0);
            //     }
            // )";

            std::shared_ptr<graphics::Shader> shader = std::make_shared<graphics::Shader> (vertexShader, fragmentShader);
            shader->SetUniformFloat3("color", 1, 0, 0);

            // mRenderManager.SetWireFrameMode(false); // Make it true for only the line

            while (mIsRunning) // Game Loop
            {
                mWindow.PumpEvents();

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