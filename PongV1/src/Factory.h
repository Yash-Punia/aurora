#pragma once

#include "aurora/graphics/mesh.h"
#include "aurora/graphics/shader.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Ball.h"

#include "external/glm/glm.hpp"

#include <memory>

namespace factory
{
    static float Vertices[]{
        0.5f, 0.5f, 0.f,
        0.5f, -0.5f, 0.f,
        -0.5f, -0.5f, 0.f,
        -0.5f, 0.5f, 0.f};

    static uint32_t Elements[]{
        0, 3, 1,
        1, 3, 2};

    // Test Shader
    static const char *VertexShader = R"(
                #version 410 core
                layout (location = 0) in vec3 position;
                out vec3 pos;
                uniform mat4 model = mat4(1.0);
                void main()
                {
                    pos = position;
                    gl_Position = model * vec4(position, 1.0);
                }
            )";

    static const char *FragmentShader = R"(
                #version 410 core
                out vec4 outColor;

                void main() 
                {
                    outColor = vec4(1.0);
                }
            )";

    static const char *BallFragmentShader = R"(
                #version 410 core
                out vec4 outColor;
                in vec3 pos;
                void main() 
                {
                    if(length(pos) > 0.5) discard;
                    outColor = vec4(1.0);
                }
            )";
    
    std::shared_ptr<GameObject> CreatePaddle(const glm::vec2& pos)
    {
        auto mesh = std::make_shared<aurora::graphics::Mesh>(&Vertices[0], 4, 3, &Elements[0], 6);
        auto shader = std::make_shared<aurora::graphics::Shader>(VertexShader, FragmentShader);


        glm::vec2 size{0.1, 0.3};
        auto ret = std::make_shared<GameObject>(mesh, shader, pos, size);
        return ret;
    }

    std::shared_ptr<Ball> CreateBall(const glm::vec2& pos)
    {
        auto mesh = std::make_shared<aurora::graphics::Mesh>(&Vertices[0], 4, 3, &Elements[0], 6);
        auto shader = std::make_shared<aurora::graphics::Shader>(VertexShader, BallFragmentShader);


        glm::vec2 size{0.075, 0.1};
        auto ret = std::make_shared<Ball>(mesh, shader, pos, size);
        return ret;
    }
}