#pragma once

#include <builder/basebuilder.h>

class KnightBuilder: public BaseBuilder
{
public:
    KnightBuilder(bool type = true, std::shared_ptr<Material> material = nullptr):
        BaseBuilder ("knight", type, material) {};
    void build() override;
};
