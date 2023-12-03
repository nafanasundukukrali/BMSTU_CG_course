#ifndef DRAWVISITOR_H
#define DRAWVISITOR_H

#include <cmath>
#include <visitor/basevisitor.h>
#include <drawer/basedrawer.h>
#include <QPixmap>
#include <factory/qtdrawerfactory/qtdrawerfactory.h>
#include <lightsource/lightsource.h>

class DrawVisitor: public BaseVisitor
{
public:
    DrawVisitor(std::shared_ptr<Camera> camera,
                std::shared_ptr<QPixmap> drawer,
                std::shared_ptr<LightSource> light_source,
                std::shared_ptr<Viewport> viewport);

//    DrawVisitor(const DrawVisitor &visitor) = default;
//    DrawVisitor &operator=(const DrawVisitor &visitor) = default;

    ~DrawVisitor() = default;

    void visit(std::shared_ptr<Composite> models_composite) override;
private:
    struct _get_nearest_surface_result
    {
        std::shared_ptr<Object> surface;
        float t;
    };

    struct _get_nearest_surface_result  _get_nearest_surface(ParametricLine &line);
    Intensity _ray_trace(ParametricLine &line, const int deep = 0);
    std::shared_ptr<Camera> _camera;
    std::unique_ptr<BaseDrawer> _drawer;
    std::shared_ptr<QPixmap> _pixmap;
    std::shared_ptr<LightSource> _light_source;
    std::shared_ptr<Viewport> _viewport;
    std::shared_ptr<Composite> _models;
};

#endif // DRAWVISITOR_H
