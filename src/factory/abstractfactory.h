#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H

#include <drawer/basedrawer.h>
#include <memory>
#include <QPainter>

class AbstractFactory
{
public:
    AbstractFactory() = default;
    virtual std::unique_ptr<BaseDrawer> create_drawer(std::shared_ptr<QPainter>) = 0;
};

#endif // ABSTRACTFACTORY_H
