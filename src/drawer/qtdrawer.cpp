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

void QtDrawer::draw_pixel(const Point &position, const Intensity &intensity) {
    int red = (intensity.red() > 255) ? 255 :(intensity.red());
    red = red < 0 ? 0 : red;
    int green = intensity.green() > 255 ? 255 : intensity.green();
    green = green < 0 ? 0 : green;
    int blue = intensity.blue() > 255 ? 255 : intensity.blue();
    blue = blue < 0 ? 0 : blue;

    if (red != green || green != blue || red != blue)
        int t = 1;

    _painter->setPen(QColor(red, green, blue));
    _painter->drawPoint(position.x(), position.y());
}
