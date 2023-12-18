#pragma once

#include <builder/basebuilder.h>

class RookBuilder: public BaseBuilder
{
public:
    RookBuilder(bool type = true, std::shared_ptr<Material> material = nullptr):
        BaseBuilder ("pawn", type, material) {};
    void build() override;
};
