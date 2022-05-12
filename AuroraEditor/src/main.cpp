#include <iostream>
#include "aurora/main.h"
#include "aurora/log.h"
#include "aurora/graphics/mesh.h"
#include "aurora/graphics/shader.h"
#include "aurora/graphics/framebuffer.h"
#include "aurora/input/mouse.h"
#include "aurora/input/joystick.h"
#include "aurora/input/keyboard.h"

#include "external/imgui/imgui.h"

using namespace aurora;

class Editor : public aurora::App
{
private:
    std::shared_ptr<graphics::Mesh> mMesh;
    std::shared_ptr<graphics::Shader> mShader;
    float xKeyOffset = 0.0f;
    float yKeyOffset = 0.0f;
    float keySpeed = 0.001f;

public:
    core::WindowProperties GetWindowProperties()
    {
        core::WindowProperties props;
        props.w = 800;
        props.h = 600;
        props.title = "Aurora Editor";

        // props.imguiProps.IsViewportEnabled = true;
        props.imguiProps.IsDockingEnabled = true;

        return props;  
    }

    void Initialize() override
    {
        AURORA_TRACE("Editor::Initialize()");
        float vertices[]{
            0.5f, 0.5f, 0.f,
            0.5f, -0.5f, 0.f,
            -0.5f, -0.5f, 0.f,
            -0.5f, 0.5f, 0.f};

        uint32_t elements[]{
            0, 3, 1,
            1, 3, 2};
        // std::shared_ptr<graphics::Mesh> mesh = std::make_shared<graphics::Mesh> (&vertices[0], 3, 3); //For vertex only
        mMesh = std::make_shared<graphics::Mesh>(&vertices[0], 4, 3, &elements[0], 6);

        // Test Shader
        const char *vertexShader = R"(
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

        const char *fragmentShader = R"(
                #version 410 core
                out vec4 outColor;
                in vec3 vpos;

                uniform vec3 color = vec3(0.0);
                uniform float blue = 0.5f;
                void main()
                {
                    outColor = vec4(vpos.xy, blue, 1.0);
                }
            )";

        mShader = std::make_shared<graphics::Shader>(vertexShader, fragmentShader);
        mShader->SetUniformFloat3("color", 1, 0, 0);
    }

    void Shutdown() override
    {
        AURORA_TRACE("Editor::Shutdown()");
    }

    void Render() override
    {
        // AURORA_TRACE("Editor::Render()");
        auto &rm = Engine::Instance().GetRenderManager();
        rm.Submit(AURORA_SUBMIT_RC(RenderMesh, mMesh, mShader));
        rm.Flush();
    }

    void ImguiRender() override
    {
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        if(ImGui::Begin("RectPosX"))
        {
            ImGui::DragFloat("Rect Pos X", &xKeyOffset, 0.01f);
        }
        
        ImGui::End();

        if(ImGui::Begin("RectPosY"))
        {
            ImGui::DragFloat("Rect Pos Y", &yKeyOffset, 0.01f);
        }
        ImGui::End();

        if(ImGui::Begin("GameView"))
        {
            if(ImGui::IsWindowHovered())
            {
                ImGui::CaptureMouseFromApp(false);
            }

            auto& window = Engine::Instance().GetWindow();

            ImVec2 size = { 100, 100};
            ImVec2 uv0 = { 0, 1 };
            ImVec2 uv1 = { 1, 0 };

            // void* is 64 bits pointer but we need to cast 32 bit int pointer
            ImGui::Image((void*)(intptr_t)window.GetFramebuffer()->GetTextureId(), size, uv0, uv1);
        }
        ImGui::End();
    }

    void Update() override
    {
        // AURORA_TRACE("Editor::Update()");

        int windowW = 0;
        int windowH = 0;
        Engine::Instance().GetWindow().GetSize(windowW, windowH);

        float xNormalized = (float)input::Mouse::X() / (float)windowW;
        float yNormalized = (float)(windowH - input::Mouse::Y()) / (float)windowH;

        // Use the above for smooth transition, this DX will use delta in x positions
        // float xNormalized = (float) input::Mouse::DX() / 100.f;
        // float yNormalized = (float) input::Mouse::DY() / 100.f;

        if (input::Keyboard::Key(AURORA_INPUT_KEY_LEFT))
        {
            xKeyOffset -= keySpeed;
        }
        if (input::Keyboard::Key(AURORA_INPUT_KEY_RIGHT))
        {
            xKeyOffset += keySpeed;
        }
        if (input::Keyboard::Key(AURORA_INPUT_KEY_UP))
        {
            yKeyOffset += keySpeed;
        }
        if (input::Keyboard::Key(AURORA_INPUT_KEY_DOWN))
        {
            yKeyOffset -= keySpeed;
        }

        if (input::Joystick::IsJoystickAvailable(0))
        {
            if (input::Joystick::GetButton(0, input::Joystick::Button::DPAD_Left))
            {
                xKeyOffset -= keySpeed;
            }
            if (input::Joystick::GetButton(0, input::Joystick::Button::DPAD_Right))
            {
                xKeyOffset += keySpeed;
            }
            if (input::Joystick::GetButton(0, input::Joystick::Button::DPAD_Up))
            {
                yKeyOffset += keySpeed;
            }
            if (input::Joystick::GetButton(0, input::Joystick::Button::DPAD_Down))
            {
                yKeyOffset -= keySpeed;
            }

            float blue = input::Joystick::GetAxis(0, input::Joystick::Axis::LeftTrigger);
            mShader->SetUniformFloat("blue", blue);
        }

        mShader->SetUniformFloat2("offset", xNormalized + xKeyOffset, yNormalized + yKeyOffset);
    }
};

aurora::App *CreateApp()
{
    return new Editor();
}