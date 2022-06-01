#include "aurora/engine.h"
#include "aurora/main.h"
#include "aurora/input/keyboard.h"

#include "external/imgui/imgui.h"
#include "external/glm/glm.hpp"

#include "Factory.h"
#include <memory>

using namespace aurora;

class PongV1 : public App
{
private:
    std::shared_ptr<GameObject> mLeftPaddle, mRightPaddle;
    std::shared_ptr<Ball> mBall;
    int mLeftPaddleUp, mLeftPaddleDown, mRightPaddleUp, mRightPaddleDown;

    float mPaddleSpeed;

    float mLeftMaxY, mLeftMinY, mRightMaxY, mRightMinY, mBallMaxY, mBallMinY;

public:
    core::WindowProperties GetWindowProperties() override
    {
        core::WindowProperties props;
        props.w = 800;
        props.h = 600;

        return props;
    }

    void Initialize() override
    {
        mLeftPaddle = factory::CreatePaddle({-1.f, 0.f});
        mRightPaddle = factory::CreatePaddle({1.f, 0.f});
        mBall = factory::CreateBall({0.f, 0.f});
        glm::vec2 initialVelocity = {0.00001f, 0.001f};
        mBall->SetVelocity(initialVelocity);

        mLeftPaddleUp = AURORA_INPUT_KEY_W;
        mLeftPaddleDown = AURORA_INPUT_KEY_S;
        mRightPaddleUp = AURORA_INPUT_KEY_UP;
        mRightPaddleDown = AURORA_INPUT_KEY_DOWN;

        mLeftMaxY = 1 - mLeftPaddle->GetSize().y / 2;
        mLeftMinY = -1 + mLeftPaddle->GetSize().y / 2;
        mRightMaxY = 1 - mRightPaddle->GetSize().y / 2;
        mRightMinY = -1 + mRightPaddle->GetSize().y / 2;
        mBallMaxY = 1 - mBall->GetSize().y / 2;
        mBallMinY = -1 + mBall->GetSize().y / 2;

        mPaddleSpeed = 0.001f;
    }

    void Shutdown() override
    {
    }

    void Update() override
    {
        mLeftPaddle->Update();
        mRightPaddle->Update();
        mBall->Update();

        if(input::Keyboard::Key(mLeftPaddleUp) && mLeftPaddle->GetPos().y < mLeftMaxY)
        {
            mLeftPaddle->Move({0.f, mPaddleSpeed});
        }
        if(input::Keyboard::Key(mLeftPaddleDown) && mLeftPaddle->GetPos().y > mLeftMinY)
        {
            mLeftPaddle->Move({0.f, -mPaddleSpeed});
        }
        if(input::Keyboard::Key(mRightPaddleUp) && mRightPaddle->GetPos().y < mRightMaxY)
        {
            mRightPaddle->Move({0.f, mPaddleSpeed});
        }
        if(input::Keyboard::Key(mRightPaddleDown) && mRightPaddle->GetPos().y > mRightMinY)
        {
            mRightPaddle->Move({0.f, -mPaddleSpeed});
        }

        mBall->Move(mBall->GetVelocity());

        if(mBall->GetPos().y < mBallMinY || mBall->GetPos().y > mBallMaxY)
        {
            mBall->FlipVelY();
        }
    }

    void Render() override
    {
        mLeftPaddle->Render();
        mRightPaddle->Render();
        mBall->Render();
    }

    void ImguiRender() override
    {
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        if (ImGui::Begin("GameView"))
        {
            if (ImGui::IsWindowHovered())
            {
                ImGui::CaptureMouseFromApp(false);
            }

            auto &window = Engine::Instance().GetWindow();

            ImVec2 size = {750, 550};
            ImVec2 uv0 = {0, 1};
            ImVec2 uv1 = {1, 0};

            // void* is 64 bits pointer but we need to cast 32 bit int pointer
            ImGui::Image((void *)(intptr_t)window.GetFramebuffer()->GetTextureId(), size, uv0, uv1);
        }
        ImGui::End();
    }
};

App *CreateApp()
{
    return new PongV1();
}