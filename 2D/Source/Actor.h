#pragma once
#include "Model.h"
#include "Transform.h"
#include <memory>

class Actor
{
public:
	Actor(const Transform& transform, std::shared_ptr<Model> model) : m_transform{ transform }, m_model{ model } {}

	Transform& GetTransform() { return m_transform; }
	const Transform& GetTransform() const { return m_transform; }

	void Draw();

private:
	Transform m_transform;
	std::shared_ptr<Model> m_model;
};