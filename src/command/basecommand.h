#ifndef BASECOMMAND_H
#define BASECOMMAND_H

#include <managers/managersholder.h>
#include <memory>

class BaseCommand {
public:
    BaseCommand() = default;
    virtual ~BaseCommand() = default;

    void set_managers(const std::shared_ptr<ManagersHolder> &managers_holder) {
        _managers_holder = managers_holder;
    }

    virtual void execute() = 0;
protected:
    std::shared_ptr<ManagersHolder> _managers_holder;
};

#endif // BASECOMMAND_H
