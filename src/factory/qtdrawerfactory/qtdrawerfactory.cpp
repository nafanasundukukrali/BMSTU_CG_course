#include "qtdrawerfactory.h"

std::unique_ptr<BaseDrawer> QtDrawerFactory::create_drawer(std::shared_ptr<QPainter> painter)
{
    return std::unique_ptr<BaseDrawer>(new QtDrawer(painter));
}
