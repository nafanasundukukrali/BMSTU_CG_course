#ifndef QTDRAWER_H
#define QTDRAWER_H

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

    void draw_pixel(const Vector3D &position, const Intensity &intensity) override;
private:
    std::shared_ptr<QPainter> _painter;
};

#endif // QTDRAWER_H
