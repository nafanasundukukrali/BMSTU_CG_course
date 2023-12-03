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

void QtDrawer::draw_pixel(const Vector3D &position, const Vector3D &intensity) {
    _painter->setPen(QColor(int(255 * intensity.r()) % 256,
                            int(255 * intensity.g()) % 256,
                            int(255 * intensity.b()) % 256));
    _painter->drawPoint(position.x(), position.y());
}
