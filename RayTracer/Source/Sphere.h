#pragma once
#include "SceneObject.h"
#include <glm/glm.hpp>
#include "Ray.h"

class Sphere : public SceneObject
{
public:
	Sphere() = default;
	Sphere(const glm::vec3& center, float radius, std::shared_ptr<Material> material) :
		SceneObject{ material }, m_center{ center }, m_radius{ radius } {}
	bool Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance) override;
private:

	glm::vec3 m_center{ 0 };
	float m_radius{ 0 };


};