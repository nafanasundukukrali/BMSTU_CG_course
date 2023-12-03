#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <managers/basemanager.h>
#include <scene/scene.h>

class SceneManager: public BaseManager
{
public:
    SceneManager(std::shared_ptr<QPixmap> pixmap);
    ~SceneManager() = default;
    explicit SceneManager(const SceneManager &);
    SceneManager(SceneManager &&) noexcept;

    void reset();
private:
    std::shared_ptr<Scene> _scene;
};

#endif // SCENEMANAGER_H
