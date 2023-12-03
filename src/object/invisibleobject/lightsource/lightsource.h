#pragma once

#include "object/invisibleobject/invisibleobject.h"

#include "object/invisibleobject/invisibleobject.h"

class LightSource: public InvisibleObject
{
public:
    LightSource(const Vector3D &position, const Vector3D &intensity):
        _intensity(intensity),
        _position(position)
    {}

    Vector3D position() const;
    Vector3D intensity() const;

    Ray get_ray(const Vector3D &hit_point) const;
    virtual void update() override;
    virtual bool hit(const Ray &r, const double tmin, const double tmax, HitInfo &data) const override;
    void move(const Vector3D &d) override;

private:
    Vector3D _position;
    Vector3D _intensity;
};
