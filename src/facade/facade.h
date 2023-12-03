#ifndef FACADE_H
#define FACADE_H

#include <managers/managersholder.h>
#include <command/basecommand.h>

class Facade {
public:
    Facade() = delete;
    Facade(std::shared_ptr<QPixmap> pixmap):
        _managers_holder(std::make_shared<ManagersHolder>(pixmap)) {};

    ~Facade() = default;

    void execute(BaseCommand &command);

private:
    std::shared_ptr<ManagersHolder> _managers_holder;
};

#endif // FACADE_H
