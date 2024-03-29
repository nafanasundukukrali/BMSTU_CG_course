#pragma once

#include <command/basecommand.h>

class Facade {
public:
    Facade() = delete;
    Facade(std::shared_ptr<QPixmap> pixmap, const uint start_count):
        _manager(std::make_shared<SceneManager>(pixmap, start_count)) {};

    ~Facade() = default;

    std::string execute(BaseCommand *command);
private:
    std::shared_ptr<SceneManager> _manager;
};
