#pragma once

#include "object/object.h"

class VisibleObject: public Object
{
public:
    bool is_visible() override
    {
        return true;
    }

    virtual void material(const Vector3D &ref, const double &p) override
    {
        _material->_reflective = ref;
        _material->_p = p;
    }
};
