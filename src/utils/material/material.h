#pragma once

#include "object/object.h"
#include "utils/ray/ray.h"

class Material
{
    friend class VisibleObject;
    friend class  BaseBuilder;
    friend class Model;
public:
    Material(const Vector3D &ambient, const Vector3D &diffuse, const Vector3D &reflective, const double &p = 0):
        _ambient(diffuse * ambient),
        _diffuse(diffuse),
        _reflective(reflective),
        _p(p)
    {};

    bool get_reflect_ray(const Ray& r, const HitInfo &data, Vector3D &k, Ray &reflect_ray, double &shine) const;
    Vector3D ambient() const;
    Vector3D diffuse() const;
    Vector3D reflective() const;
    double p() const;

private:
    Vector3D _ambient;
    Vector3D _diffuse;
    Vector3D _reflective;
    double _p;
};
