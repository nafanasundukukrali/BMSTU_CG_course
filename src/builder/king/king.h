#pragma once

#include <builder/basebuilder.h>

class KingBuilder: public BaseBuilder
{
public:
    KingBuilder(bool type = true, std::shared_ptr<Material> material = nullptr):
        BaseBuilder ("king", type, material) {};
    void build() override;
};
