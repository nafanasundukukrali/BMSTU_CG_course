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
//    int red = (intensity.r() > 255) ? 255 :(intensity.r());
//    red = red < 0 ? 0 : red;
//    int green = intensity.g() > 255 ? 255 : intensity.g();
//    green = green < 0 ? 0 : green;
//    int blue = intensity.b() > 255 ? 255 : intensity.b();
//    blue = blue < 0 ? 0 : blue;

//    if (red != green || green != blue || red != blue)
//        int t = 1;

    _painter->setPen(QColor(255 * intensity.r(), 255 * intensity.g(), 255 * intensity.b()));
    _painter->drawPoint(position.x(), position.y());
}
