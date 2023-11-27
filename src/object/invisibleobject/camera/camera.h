#pragma once

#include "object/invisibleobject/invisibleobject.h"

class Camera: public InvisibleObject
{
public:
    Camera(const Vector3D &position, const Vector3D &look_at, const double aspect_ratio);

    Vector3D position() const;
    void position(const Vector3D &pos);
    Vector3D direction() const;
    void direction(const Vector3D &dir);

    Ray get_ray(const double u, const double v) const;
    virtual void update() override;
    virtual bool hit(const Ray &r, const double tmin, const double tmax, HitInfo &data) const override;

private:
    Vector3D _direction;
    double _aspect_ratio;

    Vector3D _bottom_left;
    Vector3D _vertical;
    Vector3D _horizontal;
    Vector3D _up = {0, 0, 1};
};
