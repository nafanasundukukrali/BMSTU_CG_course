#include "ray.h"

Ray::Ray(const Vector3D& origin, const Vector3D& direction)
{
    _origin = origin;
    _direction = direction;
}

Vector3D Ray::origin() const
{
    return _origin;
}

Vector3D Ray::direction() const
{
    return _direction;
}

Vector3D Ray::get_point_by_t(const double t) const
{
    return _origin + _direction * t;
}
