#include "object/invisibleobject/camera/camera.h"

Camera::Camera(const Vector3D &position, const Vector3D &look_at, const double aspect_ratio):
    _direction(look_at),
    _aspect_ratio(aspect_ratio)
{
    _center = position;
    Camera::update();
}

Vector3D Camera::position() const
{
    return _center;
}

void Camera::position(const Vector3D &pos)
{
    _center = pos;
    Camera::update();
}

Vector3D Camera::direction() const
{
    return _direction;
}

void Camera::direction(const Vector3D &dir)
{
    _direction = dir;
    Camera::update();
}

Ray Camera::get_ray(const double u, const double v) const
{
    return Ray(_center, (_bottom_left + u * _horizontal + v * _vertical).normalized());
}

void Camera::update()
{
    double height = std::tan(60 * M_PI / 180 / 2) * 2;
    double width = height * _aspect_ratio;
    Vector3D dir = (_direction - _center).normalized();
    _horizontal = (dir.cross(_up)).normalized();
    _vertical = _horizontal.cross(dir);

    _horizontal = _horizontal * width;
    _vertical = _vertical * height;

    _bottom_left = dir - (_vertical + _horizontal) / 2.0f;
}

bool Camera::hit(const Ray &r, const double tmin, const double tmax, HitInfo &data) const
{
    return false;
}
