#pragma once

#include "object/object.h"

class InvisibleObject: public Object
{
public:
    bool is_visible() override
    {
        return false;
    }
};
