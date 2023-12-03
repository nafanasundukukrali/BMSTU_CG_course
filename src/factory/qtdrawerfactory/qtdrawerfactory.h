#ifndef QTDRAWERFACTORY_H
#define QTDRAWERFACTORY_H

#include <factory/abstractfactory.h>
#include <drawer/qtdrawer.h>
#include <QPainter>

class QtDrawerFactory : public AbstractFactory {
public:
    std::unique_ptr<BaseDrawer> create_drawer(std::shared_ptr<QPainter> value) override;
};

#endif // QTDRAWERFACTORY_H
