#pragma once

#include "utils/ray/ray.h"
#include "utils/boundingbox/boundingbox.h"
#include "utils/material/material.h"

class Object: public std::enable_shared_from_this<Object>
{
public:
    virtual void update() = 0;
    virtual bool is_visible() = 0;
    virtual bool hit(const Ray &r, const double tmin, const double tmax, HitInfo &data) const = 0;

    BoundingBox boundingBox() const
    {
        return _boundingBox;
    }

    Vector3D center() const
    {
        return _center;
    }

protected:
    BoundingBox _boundingBox;
    Vector3D _center;
    std::shared_ptr<Material> _material;
};
