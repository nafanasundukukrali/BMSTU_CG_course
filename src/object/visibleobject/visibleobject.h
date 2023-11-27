#pragma once

#include "object/object.h"

class VisibleObject: public Object
{
public:
    bool is_visible() override
    {
        return true;
    }
};
