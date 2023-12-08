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

    _last_message = "";
    return _last_message;
}
