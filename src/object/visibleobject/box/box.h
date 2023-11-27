#pragma once

#include <memory>
#include <utility>

#include "object/visibleobject/visibleobject.h"

class Box : public VisibleObject
{
public:
    Box(Vector3D center, Vector3D dimensions, std::shared_ptr<Material> material)
    {
        _center = center;
        _material = material;
        _dimensions = dimensions;

        Box::update();
    }

    void update() override;
    bool hit(const Ray& r, const double tmin, const double tmax, HitInfo& data) const override;

private:
    Vector3D _dimensions;
};
