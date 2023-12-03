#ifndef BASEDRAWER_H
#define BASEDRAWER_H

#include <utils/point/point.h>
#include <utils/intensity/intensity.h>

class BaseDrawer
{
public:
    virtual void draw_pixel(const Vector3D &position, const Intensity &intensity) = 0;
};

#endif // BASEDRAWER_H
