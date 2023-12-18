#pragma once

#include <builder/basebuilder.h>

class PawnBuilder: public BaseBuilder
{
public:
    PawnBuilder(bool type = true, std::shared_ptr<Material> material = nullptr):
        BaseBuilder ("pawn", type, material) {};

    void build() override;
};
