#include "qtdrawer.h"

QtDrawer::QtDrawer(std::shared_ptr<QPainter> painter)
{
    _painter = painter;
}

QtDrawer::QtDrawer(const QtDrawer &drawer)
{
    _painter = drawer._painter;
}

QtDrawer::QtDrawer(QtDrawer &&drawer) noexcept
{
    _painter = drawer._painter;
}

void QtDrawer::draw_pixel(const Vector3D &position, const Vector3D &intensity)
{
    int r  = 255 * intensity.r();
    int g = 255 * intensity.g();
    int b = 255 * intensity.b();

    _painter->setPen(QColor((r > 255 ? 255 : r),
                            (g > 255 ? 255 : g),
                            (b > 255 ? 255 : b)));
    _painter->drawPoint(position.x(), position.y());
}
