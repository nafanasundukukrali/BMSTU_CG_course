#pragma once

#include "object/object.h"
#include "utils/ray/ray.h"

class Material
{
public:
    Material(const Vector3D &diffuse, const Vector3D &reflective):
        _ambient(diffuse * 0.1f),
        _diffuse(diffuse),
        _reflective(reflective)
    {};

    bool get_reflect_ray(const Ray& r, const HitInfo &data, Vector3D &k, Ray &reflect_ray) const;
    Vector3D ambient() const;
    Vector3D diffuse() const;
    Vector3D reflective() const;
private:
    Vector3D _ambient;
    Vector3D _diffuse;
    Vector3D _reflective;
};
