#include "Actor.h"
#include "VertexShader.h"

void Actor::Draw()
{
	VertexShader::uniforms.model = m_transform.GetMatrix();
	m_model->Draw();
}
