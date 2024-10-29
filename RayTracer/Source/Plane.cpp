#include "Plane.h"

bool Plane::Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance)
{
    // check dot product of ray direction and plane normal, if result is 0 then ray direction if parallel to plane so it never hits plane
    // the dot product is 0 if the two vectors are perpendicular (90 degrees)
    float denominator = dot(ray.direction, m_normal);
    if (approximately(denominator, 0.0f))
    {
        return false; // ray direction and plane parallel, no intersection
    }

    // get t (distance) along ray direction to hit point
    float t = dot(m_center - ray.origin, m_normal) / denominator;
    if (t < 0)
    {
        return false; // plane behind ray's origin, no intersection
    }

    if (t <= minDistance || t >= maxDistance) return false;

    raycastHit.distance = t;
    raycastHit.normal = glm::normalize(m_normal);
    raycastHit.point = ray.At(t);
    raycastHit.material = GetMaterial();

    return true;
}