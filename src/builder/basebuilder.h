#pragma once

#include "object/visibleobject/model/model.h"
#include "object/visibleobject/triangle/triangle.h"
#include "reader/stl_reader.h"


#ifndef MODELS_PATH
    #define MODELS_PATH "./models/"
#endif

#ifndef MODELS_FILE_TYPE
    #define MODELS_FILE_TYPE ".stl"
#endif

class BaseBuilder
{
public:
    BaseBuilder(std::string name, bool type = true, std::shared_ptr<Material> material = nullptr):
        _name(name)
    {
        if (material)
            _material = material;
        else if (type)
            _material = black;
        else
            _material = white;
    };

    virtual void build();
    std::shared_ptr<Model> get();
protected:
    std::string _name = "";
    std::shared_ptr<Model> _model;
    std::shared_ptr<Material> _material;
    std::shared_ptr<Material> black = std::make_shared<Material>(
        Vector3D(0.1),
        Vector3D(0.3,0.15,0.05),
        Vector3D(0.3),
        100
    );

    std::shared_ptr<Material> white = std::make_shared<Material>(
        Vector3D(0.1),
        Vector3D(0.8,0.6,0.48),
        Vector3D(0.3),
        100
    );
};
