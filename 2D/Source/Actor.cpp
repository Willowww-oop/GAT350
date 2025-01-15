#include "Actor.h"
#include "Shader.h"

void Actor::Draw()
{
	Shader::uniforms.model = m_transform.GetMatrix();
	m_model->Draw();
}
