#include "scenemanager.h"

SceneManager::SceneManager(std::shared_ptr<QPixmap> pixmap)
{
    _scene = std::make_shared<Scene>(pixmap);
}

void SceneManager::reset()
{
//    Viewport viewport(*std::move(_scene->get_viewport().get()));
//    _scene = std::make_shared<Scene>(viewport.get_pixmap());
}
