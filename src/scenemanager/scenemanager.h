#pragma once

#include <scene/scene.h>

class SceneManager
{
public:
    SceneManager(std::shared_ptr<QPixmap> pixmap, const uint start_count);
    ~SceneManager() = default;
    explicit SceneManager(const SceneManager &);
    SceneManager(SceneManager &&) noexcept;

    void reset();
private:
    std::shared_ptr<Scene> _scene;
};
