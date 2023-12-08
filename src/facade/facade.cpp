#include "facade.h"

std::string Facade::execute(BaseCommand *command) {
    command->set_manager(_manager);
    return command->execute();
}
