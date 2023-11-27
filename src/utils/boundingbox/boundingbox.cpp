#include "boundingbox.h"

Vector3D BoundingBox::min() const
{
    return _min;
}

Vector3D BoundingBox::max() const
{
    return _max;
}

void BoundingBox::expand(const BoundingBox &box)
{
    for (size_t i = 0; i < 3; i++)
    {
        _min[i] = std::min(_min[i], box._min[i]);
        _max[i] = std::max(_max[i], box._max[i]);
    }
}

bool BoundingBox::validate_intersect(const Ray &r) const
{
    double tmin, tmax;
    bool init = false;
    int buffer_sign[3];
    Vector3D buffer_bounds[2] = {_min, _max};

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

    if (t < 0)
    {
        t = tmax;

        if (t < 0)
            return false;
    }

    return true;
}
