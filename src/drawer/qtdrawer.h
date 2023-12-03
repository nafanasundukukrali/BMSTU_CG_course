#pragma once

#include <drawer/basedrawer.h>
#include <QPainter>
#include <QPen>

class QtDrawer: public BaseDrawer
{
public:
    QtDrawer() = delete;
    explicit QtDrawer(std::shared_ptr<QPainter>);
    explicit QtDrawer(const QtDrawer &);
    QtDrawer(QtDrawer &&) noexcept;
    ~QtDrawer()
    {
        _painter->end();
    }

    void draw_pixel(const Vector3D &position, const Vector3D &intensity) override;
private:
    std::shared_ptr<QPainter> _painter;
};
