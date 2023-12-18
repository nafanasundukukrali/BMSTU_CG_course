#include "scenemanager.h"

SceneManager::SceneManager(std::shared_ptr<QPixmap> pixmap, const uint start_count)
{
    _scene = std::make_shared<Scene>(pixmap, start_count);
}

std::string SceneManager::add(uint _builder_i, bool _color, uint _letter, uint _number)
{
    try
    {
        _scene->add_model(_builder_i, _color, _letter, _number);
        _last_message = "";
    }
    catch (FigureOnDesk &ex)
    {
        _last_message = "Фигура уже есть на доске.";
    }
    catch (...)
    {
        throw;
    }

    return _last_message;
}

std::string SceneManager::del(uint _letter, uint _number)
{
    try
    {
        _scene->delete_model(_letter, _number);
        _last_message = "";
    }
    catch (NoFigureOnDesk &ex)
    {
        _last_message = "Фигуры нет на доске.";
    }
    catch (...)
    {
        throw;
    }

    return _last_message;
}

std::string SceneManager::draw()
{
    _scene->draw();
    _last_message = "";
    return _last_message;
}

std::string SceneManager::change_material_or_light_params(bool change_material, const Vector3D &reflection, const double &p, const Vector3D &color)
{
    if (change_material)
        _scene->change_reflect_and_shine_k(reflection, p);
    else
        _scene->change_light_source_color(color);

    _last_message = "";
    return _last_message;
}

std::string SceneManager::move_and_rotate(bool move_camera, bool rotate, const Vector3D &kd, const Vector3D& o)
{
    _last_message = "";

    if (move_camera && !rotate)
        _scene->move_camera(kd);
    else if (!move_camera && !rotate)
        _scene->move_lightsource(kd);
    else if (move_camera)
        _scene->rotate_camera(o);
    else
        _last_message = "Невозможно применить изменение к объектам.";

    return _last_message;
}
