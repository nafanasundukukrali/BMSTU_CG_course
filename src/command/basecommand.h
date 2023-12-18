#pragma once

#include <scenemanager/scenemanager.h>
#include <memory>

class BaseCommand {
public:
    BaseCommand() = default;
    virtual ~BaseCommand() = default;

    void set_manager(const std::shared_ptr<SceneManager> &manager) {
         _scene_manager = manager;
    }

    virtual std::string execute() = 0;
protected:
    std::shared_ptr<SceneManager> _scene_manager = nullptr;
};
