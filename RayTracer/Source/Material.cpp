#include "Material.h"
#include "Random.h"

bool Lambertian::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scatter)
{
    scatter.origin = raycastHit.point;
    scatter.direction = raycastHit.normal + randomOnUnitSphere();

    attenuation = m_albedo;

    return true;
}
