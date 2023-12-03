#include "scenemanager.h"

SceneManager::SceneManager(std::shared_ptr<QPixmap> pixmap, const uint start_count)
{
    _scene = std::make_shared<Scene>(pixmap, start_count);
}
