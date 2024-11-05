#pragma once
#include "material.h"
#include "Ray.h"
#include "Transform.h"

#include <memory>
class SceneObject
{
public:

	SceneObject() = default;
	SceneObject(const Transform& transform, std::shared_ptr<class Material> material) : 
		m_transform{ transform },
		m_material{ material } {}
	SceneObject(std::shared_ptr<class Material> material) : m_material{ material } {}

	virtual void Update() { }
	virtual bool Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance) = 0;

	std::weak_ptr<class Material> GetMaterial() { return m_material; }
	Transform& GetTransform() { return m_transform; }
	const Transform& GetTransform() const { return m_transform; }

	

protected:
	std::shared_ptr<class Material> m_material;
	Transform m_transform;

};