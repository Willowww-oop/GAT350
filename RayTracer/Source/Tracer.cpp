#include "Tracer.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Color.h"
#include "Material.h"
#include "Scene.h"


color3_t Tracer::Trace(Scene& scene, const ray_t& ray, float minDistance, float maxDistance, int depth)
{
	if (depth == 0) return color3_t{ 0 };
	
	raycastHit_t raycastHit;
	float closestDistance = maxDistance;
	bool isHit = false;

	for (auto& object : scene.m_objects)
	{
		if (object->Hit(ray, raycastHit, minDistance, closestDistance))
		{
			isHit = true;
			closestDistance = raycastHit.distance;


			//return object->GetMaterial().lock()->GetColor();
		}
	}

	if (isHit)
	{
		color3_t attentuation;
		ray_t scatter;
		if (raycastHit.material.lock()->Scatter(ray, raycastHit, attentuation, scatter))
		{
			return attentuation * Trace(scene, scatter, minDistance, maxDistance, depth - 1);
		}
		else
		{
			return raycastHit.material.lock()->GetEmissive();
		}
		//return raycastHit.material.lock()->GetColor();
	}

	color3_t color{ 0 };

	glm::vec3 direction = glm::normalize(ray.direction);
	float t = (direction.y + 1) * 0.5f;

	color = Lerp(scene.m_skyBottom, scene.m_skyTop, t);

	return color;
}