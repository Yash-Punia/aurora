#pragma once

#include "aurora/graphics/mesh.h"
#include "aurora/graphics/shader.h"

#include "external/glm/glm.hpp"

#include <memory>

class GameObject
{
public:
    GameObject(std::shared_ptr<aurora::graphics::Mesh> mesh, std::shared_ptr<aurora::graphics::Shader> shader, const glm::vec2& pos, const glm::vec2& size)
        : mMesh(mesh)
        , mShader(shader)
        , mPos(pos)
        , mSize(size)
    {}

    void SetPos(const glm::vec2& pos) { mPos = pos; }
    void Move(const glm::vec2& by) { mPos += by; }

    const glm::vec2& GetPos() const { return mPos; }
    const glm::vec2& GetSize() const { return mSize; }

    void Update();
    void Render();

private:
    std::shared_ptr<aurora::graphics::Mesh> mMesh;
    std::shared_ptr<aurora::graphics::Shader> mShader;

    glm::vec2 mPos;
    glm::vec2 mSize;
};