#pragma once

#include <builder/basebuilder.h>
#include <object/visibleobject/box/box.h>

#ifndef BASE_CELL_SIZE
    #define BASE_CELL_SIZE 39
#endif

class ChessDeskBuilder: public BaseBuilder
{
public:
    ChessDeskBuilder(): BaseBuilder ("chessdesk") {};
    void build() override;
private:
    std::shared_ptr<Material> blackcell = std::make_shared<Material>(
        Vector3D(0.1),
        Vector3D(0.3,0.15,0.05),
        Vector3D(0)
    );

    std::shared_ptr<Material> whitecell = std::make_shared<Material>(
        Vector3D(0.1),
        Vector3D(0.8,0.6,0.48),
        Vector3D(0)
    );
};
