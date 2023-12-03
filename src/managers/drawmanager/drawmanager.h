#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <scene/scene.h>

class DrawManager
{
public:
    void draw(const std::shared_ptr<Scene> &scene);
};

#endif // DRAWMANAGER_H
