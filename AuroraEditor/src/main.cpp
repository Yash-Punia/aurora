#include <iostream>
#include "aurora/main.h"
#include "aurora/log.h"
#include "aurora/graphics/mesh.h"
#include "aurora/graphics/shader.h"
#include "aurora/input/mouse.h"
#include "aurora/input/joystick.h"
#include "aurora/input/keyboard.h"

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
        AURORA_TRACE("Editor::Render()");

        auto rc = std::make_unique<graphics::rendercommands::RenderMesh>(mMesh, mShader);
        Engine::Instance().GetRenderManager().Submit(std::move(rc));
        Engine::Instance().GetRenderManager().Flush();
    }

    void Update() override
    {
        AURORA_TRACE("Editor::Update()");

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