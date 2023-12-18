#include "object/invisibleobject/camera/camera.h"

Camera::Camera(const Vector3D &position, const Vector3D &look_at, const double k):
    _direction(look_at),
    _k(k)
{
    _center = position;
    _dir_for_update = (_direction - _center).normalized();
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
    return Ray(_center, (_left_button + u * _horizontal + v * _vertical).normalized());
}

void Camera::update()
{
    double height = std::tan(60 * M_PI / 180 / 2) * 2;
    double width = height * _k;
    _horizontal = (_dir_for_update.cross(_up)).normalized();
    _vertical = _horizontal.cross(_dir_for_update);

    _horizontal *= width;
    _vertical *= height;

    _left_button = _dir_for_update - (_vertical + _horizontal) / 2.0f;
}

bool Camera::hit(const Ray &r, const double tmin, const double tmax, HitInfo &data) const
{
    return false;
}

void Camera::move(const Vector3D &d)
{
    _center += d;
}

void Camera::rotate(const Vector3D &d)
{

//    _dir_for_update = Vector3D(1, 1, 1);
    double cosX = std::cos(d[0]);
    double sinX = std::sin(d[0]);
    double cosY = std::cos(d[1]);
    double sinY = std::sin(d[1]);
    double cosZ = std::cos(d[2]);
    double sinZ = std::sin(d[2]);

    // Apply rotation around X axis
    double newDirY = cosX * _direction.y() - sinX * _direction.z();
    double newDirZ = sinX * _direction.y() + cosX * _direction.z();

    _direction.normalize();
    _direction[1] = newDirY;
    _direction[2] = newDirZ;

    // Apply rotation around Y axis
    double newDirX = cosY * _direction.x() + sinY * _direction.z();
    newDirZ = -sinY * _direction.x() + cosY * _direction.z();

    _direction[0] = newDirX;
    _direction[2] = newDirZ;

    // Apply rotation around Z axis
    newDirX = cosZ * _direction.x() - sinZ * _direction.y();
    newDirY = sinZ * _direction.x() + cosZ * _direction.y();

    _direction[0] = newDirX;
    _direction[1] = newDirY;

    _direction.normalize();

    // Apply rotation around X axis
    newDirY = cosX * _dir_for_update.y() - sinX * _dir_for_update.z();
    newDirZ = sinX * _dir_for_update.y() + cosX * _dir_for_update.z();

    _dir_for_update.normalize();
    _dir_for_update[1] = newDirY;
    _dir_for_update[2] = newDirZ;

    // Apply rotation around Y axis
    newDirX = cosY * _dir_for_update.x() + sinY * _dir_for_update.z();
    newDirZ = -sinY * _dir_for_update.x() + cosY * _dir_for_update.z();

    _dir_for_update[0] = newDirX;
    _dir_for_update[2] = newDirZ;

    // Apply rotation around Z axis
    newDirX = cosZ * _dir_for_update.x() - sinZ * _dir_for_update.y();
    newDirY = sinZ * _dir_for_update.x() + cosZ * _dir_for_update.y();

    _dir_for_update[0] = newDirX;
    _dir_for_update[1] = newDirY;

    _dir_for_update.normalize();

    // Update remaining vectors based on the new direction
    Camera::update();
}

