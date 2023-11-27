#pragma once

#include <memory>
#include <utility>

#include "object/visibleobject/visibleobject.h"

class Sphere : public VisibleObject
{
public:
    Sphere(Vector3D center, double radius, std::shared_ptr<Material> material)
    {
        _center = center;
        _radius = radius;
        _material = material;
        Sphere::update();
    }

    void update() override;
    bool hit(const Ray& r, const double t_min, const double t_max, HitInfo& data) const override;
private:
    double _radius;
};
