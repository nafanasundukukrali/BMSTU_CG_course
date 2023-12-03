#include "box.h"

void Box::update()
{
    Vector3D min = _center - _dimensions / 2.0;
    Vector3D max = _center + _dimensions / 2.0;
    _boundingBox = BoundingBox(min, max);
}

bool Box::hit(const Ray& r, const double t_min, const double t_max, HitInfo& data) const
{
    double tmin, tmax, tymin, tymax, tzmin, tzmax;
    bool init = false;
    int buffer_sign[3];
    Vector3D buffer_bounds[2] = {_boundingBox.min(), _boundingBox.max()};

    if (r.direction().length() == 0)
        throw "Impossible to check interseck.";

    Vector3D r_invdir = 1.0f / r.direction();

    for (size_t  i = 0; i < 3; i++)
        buffer_sign[i] = r_invdir[i] < 0 ? 1 : 0;


    for (size_t i = 0; i < 3; i++)
    {
        double buffer_tmin = (buffer_bounds[buffer_sign[i]][i] - r.origin()[i]) * r_invdir[i];
        double buffer_tmax = (buffer_bounds[1 - buffer_sign[i]][i] - r.origin()[i]) * r_invdir[i];

        if (!init)
        {
            init = true;
            tmin = buffer_tmin;
            tmax = buffer_tmax;
        }
        else
        {
            if ((tmin > buffer_tmax) || (buffer_tmin > tmax))
                return false;

            if (buffer_tmin > tmin)
                tmin = buffer_tmin;

            if (buffer_tmax < tmax)
                tmax = buffer_tmax;
        }
    }

    double t = tmin;

    if (t < 1e-9)
    {
        t = tmax;

        if (t < 1e-9)
            return false;
    }

    if (t > t_max || t < t_min)
        return false;

    data.t = t;
    data.hit_point = r.get_point_by_t(t);
    data.material = _material;
    data.object = shared_from_this();

    const Vector3D direction = data.hit_point - _center;
    const Vector3D normal;

    if (std::abs(direction[0]) > std::abs(direction[1]) && std::abs(direction[0]) > std::abs(direction[2]))
        data.normal = Vector3D(direction[0], 0, 0) / _dimensions;
    else if (std::abs(direction[1]) > std::abs(direction[2]))
        data.normal = Vector3D(0, direction[1], 0) / _dimensions;
    else
        data.normal = Vector3D(0, 0, direction[2]) / _dimensions;

    return true;
}

void Box::move(const Vector3D &d)
{
    for (size_t j = 0; j < 3; j++)
        _center[j] += d[j];

    Box::update();
}
