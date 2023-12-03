#include "lightsource.h"

Vector3D LightSource::position() const
{
    return _position;
}

Vector3D LightSource::intensity() const
{
    return _intensity;
}

Ray LightSource::get_ray(const Vector3D &hit_point) const
{
    return Ray(hit_point, _position.normalized());
}

void LightSource::update()
{
    _position.normalize();
}

bool LightSource::hit(const Ray &r, const double t_min, const double t_max, HitInfo &data) const
{
    return false;
}

void LightSource::move(const Vector3D &d)
{
    _center += d;
    LightSource::update();
}
