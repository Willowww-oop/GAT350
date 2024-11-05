#include "Sphere.h"

bool Sphere::Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance)
{
    float t;
    if (!Raycast(ray, m_transform.position, m_radius * m_transform.scale.x, minDistance, maxDistance, t)) return false;

    raycastHit.distance = t;
    raycastHit.point = ray.At(t);
    raycastHit.normal = glm::normalize(raycastHit.point - m_transform.position);
    raycastHit.material = GetMaterial();

    return true;
}

bool Sphere::Raycast(const ray_t& ray, const glm::vec3& center, float radius, float minDistance, float maxDistance, float& t)
{
    // Vector from the ray origin to the center of the sphere

    glm::vec3 oc = ray.origin - center;

    // Coefficients for the quadratic equation
    // a = dot(ray direction, ray direction), which is the square of the length of the ray direction

    float a = glm::dot(ray.direction, ray.direction);

    // b = 2 * dot(ray direction, oc), where oc is the vector from the ray origin to the sphere center

    float b = 2 * glm::dot(ray.direction, oc);

    // c = dot(oc, oc) - radius^2, which accounts for the distance from the origin to the center minus the radius of the sphere

    float c = glm::dot(oc, oc) - (radius * radius);

    // Discriminant of the quadratic equation: b^2 - 4ac
    // This tells us how many real solutions (hits) exist:
    // If discriminant < 0, no real solutions (no intersection)
    // If discriminant = 0, one solution (the ray grazes the sphere)
    // If discriminant > 0, two solutions (the ray hits the sphere twice)

    float discriminant = (b * b) - (4 * a * c);

    if (discriminant >= 0)
    {
        t = (-b - sqrt(discriminant)) / (2 * a);
        if (t >= minDistance && t <= maxDistance)
        {
            return true;
        }

        t = (-b + sqrt(discriminant)) / (2 * a);
        if (t >= minDistance && t <= maxDistance)
        {
            return true;
        }
    }

    return false;
}
