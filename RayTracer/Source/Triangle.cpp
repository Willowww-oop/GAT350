#include "Triangle.h"

bool Triangle::Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance)
{
    // set edges of the triangle
    glm::vec3 edge1 = m_v2 - m_v1;
    glm::vec3 edge2 = m_v3 - m_v1;

    // calculate perpendicular vector, determine how aligned the ray is with the triangle plane
    glm::vec3 pvec = Cross(ray.direction, edge2); 
    float determinant = Dot(pvec, edge1);

    // if determinant is less than 0 then ray is hitting back of triangle
    // if determinant is 0 then ray is parallel to triangle surface
    if ( determinant < 0 || approximately(0.0001f, determinant))
    {
        return false;
    }

    // inverse determinant
    float invDet = 1 / determinant;

    // create direction vector from the triangle first vertex to the ray origin
    glm::vec3 tvec = ray.origin - m_v1;
    // Calculate u parameter for barycentric coordinates
    float u = Dot(tvec, pvec) * invDet;
    // Check if u is outside the bounds of the triangle, no intersection
    if (u < 0 || u > 1)
    {
        return false;
    }

    // Calculate qvec, a vector perpendicular to both tvec and edge1, used to find the v parameter
    glm::vec3 qvec = glm::cross(tvec, edge1);
        // Calculate v parameter for barycentric coordinates
        float v = Dot(qvec, ray.direction) * invDet;
    // Check if v is outside the bounds or if u + v exceeds 1, no intersection
    if (v < 0 || (u + v) > 1)
    {
        return false;
    }

    // Calculate intersection distance and check range
    float t = Dot(edge2, qvec) * invDet;
    if (t >= minDistance && t <= maxDistance)
    {
        // set raycast hit
        raycastHit.distance = t;
        raycastHit.point = ray.At(t);
        raycastHit.normal = glm::normalize(glm::cross(edge1, edge2));
        raycastHit.material = GetMaterial();

        return true;
    }

    return false;
}