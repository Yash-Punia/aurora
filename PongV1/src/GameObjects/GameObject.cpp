#include "GameObject.h"

#include "aurora/engine.h"
#include "external/glm/gtc/matrix_transform.hpp"

void GameObject::Update()
{
	static int frames = 0;
	mShader->SetUniformFloat("iTime", frames * 0.01f);
	frames++;
}

void GameObject::Render()
{
    glm::mat4 model = glm::mat4(1.f);
    model = glm::translate(model, { mPos.x, mPos.y, 0.f });
    model = glm::scale(model, { mSize.x, mSize.y, 1.f });
    mShader->SetUniformMat4("model", model);

    aurora::Engine::Instance().GetRenderManager().Submit(AURORA_SUBMIT_RC(RenderMesh, mMesh, mShader));
}