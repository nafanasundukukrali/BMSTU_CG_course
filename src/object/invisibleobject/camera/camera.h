#pragma once

#include "object/invisibleobject/invisibleobject.h"

class Camera: public InvisibleObject
{
public:
    Camera(const Vector3D &position, const Vector3D &look_at, const double k);

    Vector3D position() const;
    void position(const Vector3D &pos);
    Vector3D direction() const;
    void direction(const Vector3D &dir);
    void move(const Vector3D &d) override;
    void rotate(const Vector3D &d);
    Ray get_ray(const double u, const double v) const;
    virtual void update() override;
    virtual bool hit(const Ray &r, const double tmin, const double tmax, HitInfo &data) const override;
private:
    Vector3D _direction;
    double _k;
    Vector3D _dir_for_update;
    Vector3D _left_button;
    Vector3D _vertical;
    Vector3D _horizontal;
    Vector3D _up = {0, 0, 1};
};
