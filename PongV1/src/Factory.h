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
                    outColor = vec4(vec3(0.0), 1.0);
                }
            )";

    static const char *BallFragmentShader = R"(
                #version 410 core
                out vec4 outColor;
                in vec3 pos;
                void main() 
                {
                    if(length(pos) > 0.5) discard;
                    outColor = vec4(vec3(0.0), 1.0);
                }
            )";

    static const char *BGFragmentShader = R"(
		        #version 410 core
		        out vec4 outColor;
		        in vec3 pos;
		        uniform float iTime = 0.0;
		        void main()
		        {
		        	vec3 Scale1 = vec3(15, 0.4, 0.975);
		        	vec3 Scale2 = vec3(25, 0.8, 0.5);
		        	vec3 Scale3 = vec3(75, 3.2, 0.8);        
		        	vec3 Color1 = vec3(1, 0.67256093, 0);
		        	vec3 Color2 = vec3(1, 0.7411765, 0);
		        	vec3 Color3 = vec3(1, 0.7411765, 0);     
		        	float position = length(pos);
		        	float f1 = sin(position * Scale1.x - iTime * Scale1.y);
		        	float f2 = sin(position * Scale2.x - iTime * Scale2.y);
		        	float f3 = sin(position * Scale3.x - iTime * Scale3.y);
   		        	vec3 col = vec3(1, 0.8078432, 0);
		        	if (f1 > Scale1.z) {
		        		col = Color1;
		        	}              
		        	else if (f2 > Scale2.z) {
		        		col = Color2;
		        	}
		        	else if (f3 > Scale3.z) {
    	        		col = Color3;
		        	}
		        	// Output to screen
		        	outColor = vec4(col,1.0);
		        }
			)";

    std::shared_ptr<GameObject> CreatePaddle(const glm::vec2 &pos)
    {
        auto mesh = std::make_shared<aurora::graphics::Mesh>(&Vertices[0], 4, 3, &Elements[0], 6);
        auto shader = std::make_shared<aurora::graphics::Shader>(VertexShader, FragmentShader);

        glm::vec2 size{0.1, 0.3};
        auto ret = std::make_shared<GameObject>(mesh, shader, pos, size);
        return ret;
    }

    std::shared_ptr<Ball> CreateBall(const glm::vec2 &pos)
    {
        auto mesh = std::make_shared<aurora::graphics::Mesh>(&Vertices[0], 4, 3, &Elements[0], 6);
        auto shader = std::make_shared<aurora::graphics::Shader>(VertexShader, BallFragmentShader);

        glm::vec2 size{0.075, 0.1};
        auto ret = std::make_shared<Ball>(mesh, shader, pos, size);
        return ret;
    }

    std::shared_ptr<GameObject> CreateBG()
	{
		auto mesh = std::make_shared<aurora::graphics::Mesh>(&Vertices[0], 4, 3, &Elements[0], 6);
		auto shader = std::make_shared<aurora::graphics::Shader>(VertexShader, BGFragmentShader);

		glm::vec2 pos{ 0.f ,0.f };
		glm::vec2 size{ 2.f, 2.f };
		auto ret = std::make_shared<GameObject>(mesh, shader, pos, size);
		return ret;
	}
}