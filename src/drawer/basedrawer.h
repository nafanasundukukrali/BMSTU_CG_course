#pragma once

#include <utils/vector3d/vector3d.h>

class BaseDrawer
{
public:
    virtual void draw_pixel(const Vector3D &position, const Vector3D &intensity) = 0;
};
