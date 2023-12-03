#include "scene.h"

Scene::Scene(std::shared_ptr<QPixmap> pixmap)
{
    _viewport = std::make_shared<Viewport>(pixmap->width(), pixmap->height());
    _camera = std::make_shared<Camera>(pixmap->width());
    _light_source = std::make_shared<LightSource>();
    _models = std::make_shared<Composite>();

    std::shared_ptr<PawnBuilder> builder = std::make_shared<PawnBuilder>();
    builder->build();

    std::shared_ptr<BaseModel> object = builder->get();

    _models->add(object);

    DrawVisitor visitor(_camera, pixmap, _light_source, _viewport);
    visitor.visit(_models);
}


std::shared_ptr<Composite> Scene::get_models()
{
    return _models;
}

std::shared_ptr<Camera> Scene::get_camera()
{
    return _camera;
}

std::shared_ptr<Viewport> Scene::get_viewport()
{
    return _viewport;
}

std::shared_ptr<LightSource> Scene::get_light_source()
{
    return _light_source;
}

void Scene::add_model(std::shared_ptr<BaseModel> new_model)
{
    _models->add(new_model);
    // TODO: add model by figure position
}

//void remove_model(const char letter_position, const int number_position);
