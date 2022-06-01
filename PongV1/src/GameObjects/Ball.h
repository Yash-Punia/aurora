#pragma once

#include "GameObject.h"

class Ball : public GameObject
{

public:

    Ball(std::shared_ptr<aurora::graphics::Mesh> mesh, std::shared_ptr<aurora::graphics::Shader> shader, const glm::vec2& pos, const glm::vec2& size)
        : GameObject(mesh, shader, pos, size)
        , mVelocity(0.f)
    {}

    void SetVelocity(glm::vec2& vel) { mVelocity = vel; }
    const glm::vec2& GetVelocity() const { return mVelocity; }
    void FlipVelX() { mVelocity.x *= -1; }
    void FlipVelY() { mVelocity.y *= -1; }

private:
    glm::vec2 mVelocity;

};
