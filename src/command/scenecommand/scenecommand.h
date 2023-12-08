#pragma once

#include <command/basecommand.h>
#include <stdlib.h>

class AddModelToScene: public BaseCommand
{
public:
    AddModelToScene(uint builder_i, bool color, uint letter, uint number):
        _builder_i(builder_i),
        _color(color),
        _letter(letter),
        _number(number)
    {};

    std::string execute()
    {
        return _scene_manager->add(_builder_i, _color, _letter, _number);
    }

private:
    uint _builder_i;
    bool _color;
    uint _letter;
    uint _number;
};

class DrawScene: public BaseCommand
{
public:
    DrawScene()
    {};

    std::string execute()
    {
        return _scene_manager->draw();
    }
};


class DeleteModelFromScene: public BaseCommand
{
public:
    DeleteModelFromScene(uint letter, uint number):
        _letter(letter),
        _number(number)
    {};

    std::string execute()
    {
        return _scene_manager->del(_letter, _number);
    }

private:
    uint _letter;
    uint _number;
};

class ChangeLightSourceColorOrMaterialParamsScene: public BaseCommand
{
public:
    ChangeLightSourceColorOrMaterialParamsScene(bool change_material, const Vector3D &reflection, const double &p, const Vector3D &color):
        _change_material(change_material),
        _reflection(reflection),
        _p(p),
        _color(color)
    {};

    std::string execute()
    {
        return _scene_manager->change_material_or_light_params(_change_material, _reflection, _p, _color);
    }

private:
    bool _change_material;
    Vector3D _reflection;
    double _p;
    Vector3D _color;
};


