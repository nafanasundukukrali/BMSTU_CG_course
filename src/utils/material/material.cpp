#include "material.h"

bool Material::get_reflect_ray(const Ray& r, const HitInfo &data, Vector3D &k, Ray &reflect_ray) const
{
    reflect_ray = Ray(data.hit_point, data.normal.reflect(r.direction().normalized()));
    k = _reflective;

    return true;
}

Vector3D Material::ambient() const
{
    return _ambient;
}

Vector3D Material::diffuse() const
{
    return _diffuse;
}

Vector3D Material::reflective() const
{
    return _reflective;
}
