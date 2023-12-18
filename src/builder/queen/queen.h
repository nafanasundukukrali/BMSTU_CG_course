#pragma once

#include <builder/basebuilder.h>

class QueenBuilder: public BaseBuilder
{
public:
    QueenBuilder(bool type = true, std::shared_ptr<Material> material = nullptr):
        BaseBuilder ("queen", type, material) {};
    void build() override;
};
