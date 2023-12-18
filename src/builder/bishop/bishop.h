#pragma once

#include <builder/basebuilder.h>

class BishopBuilder: public BaseBuilder
{
public:
    BishopBuilder(bool type = true, std::shared_ptr<Material> material = nullptr):
        BaseBuilder ("bishop", type, material) {};
    void build() override;
};
