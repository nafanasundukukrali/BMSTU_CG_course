#pragma once

#include "utils/vector3d/vector3d.h"
#include <memory>

class Material;
class Object;

struct HitInfo
{
    double t;
    Vector3D hit_point;
    Vector3D normal;
    std::shared_ptr<const Material> material;
    std::shared_ptr<const Object> object;
};

class Ray
{
public:
    Ray() = default;
    Ray(const Vector3D& origin, const Vector3D& direction);

    Vector3D origin() const;
    Vector3D direction() const;
    Vector3D get_point_by_t(const double t) const;

private:
    Vector3D _origin;
    Vector3D _direction;
};
