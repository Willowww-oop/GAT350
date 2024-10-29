#pragma once
#include "SceneObject.h"

class Plane : public SceneObject
{
public:
	Plane() = default;
	Plane(const glm::vec3& center, const glm::vec3& normal, std::shared_ptr<Material> material) :
		SceneObject(material),
		m_center{ center },
		m_normal{ normal }
	{
	}

	bool Hit(const ray_t& ray, raycastHit_t&, float minDistance, float maxDistance) override;

private:
	glm::vec3 m_center{ 0 };
	glm::vec3 m_normal{ 0 };

};