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

void Camera::move(const Vector3D &d)
{
    _center += d;
    Camera::update();
}


void Camera::rotate(const Vector3D &d)
{
    double f1 = _direction.x(), f2 = _direction.z(), x1, y1, z1;

    x1 = f1 * std::cos(d.y()) + f2 * std::cos(d.z());
    y1 = _direction.y();
    z1 = - f1 * std::sin(d.y()) + f2 * std::cos(d.y());

    f1 = y1;
    f2 = z1;

    _direction = Vector3D(x1, y1, z1);

    Camera::update();
}

