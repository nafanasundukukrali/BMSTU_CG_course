#include "material.h"

bool Material::get_reflect_ray(const Ray& r, const HitInfo &data, Vector3D &ref_k, Ray &reflect_ray, double &shine) const
{
    reflect_ray = Ray(data.hit_point, data.normal.reflect(r.direction().normalized()));
    Vector3D norm_rr = reflect_ray.direction().normalized();
    Vector3D min_dir = -r.direction().normalized();
    shine = std::pow(norm_rr.dot(min_dir) / norm_rr.length() / min_dir.length(), _p);
    ref_k = _reflective;

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

double Material::p() const
{
    return _p;
}
