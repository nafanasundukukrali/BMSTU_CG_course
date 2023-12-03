#include "facade.h"

void Facade::execute(BaseCommand &command) {
    command.set_managers(_managers_holder);
    command.execute();
}
