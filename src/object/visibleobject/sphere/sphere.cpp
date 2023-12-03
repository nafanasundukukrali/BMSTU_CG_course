#include "sphere.h"

void Sphere::update()
{
    Vector3D buffer_min = _center - Vector3D(_radius);
    Vector3D buffer_max = _center + Vector3D(_radius);
    _boundingBox = BoundingBox(buffer_min, buffer_max);
}

bool Sphere::hit(const Ray& r, const double t_min, const double t_max, HitInfo& data) const
{
    Vector3D oc = r.origin() - _center;

    double a = r.direction().dot(r.direction());
    double b = oc.dot(r.direction());
    double c = oc.dot(oc) - _radius * _radius;
    double discriminant = b * b - a * c;

    if (discriminant <= 0.0f)
        return false;

    double inv_len = std::sqrt(discriminant) / a;
    double bdiva = b / a;

    double t = -bdiva - inv_len;

    if (t >= t_max || t <= t_min)
    {
        t = (-bdiva + inv_len);

        if (t >= t_max || t <= t_min)
            return false;
    }

    data.t = t;
    data.hit_point = r.get_point_by_t(t);
    data.normal = (data.hit_point - _center) / _radius;
    data.material = _material;
    data.object = shared_from_this();

    return true;
}

void Sphere::move(const Vector3D &d)
{
    for (size_t j = 0; j < 3; j++)
        _center[j] += d[j];

    Sphere::update();
}
