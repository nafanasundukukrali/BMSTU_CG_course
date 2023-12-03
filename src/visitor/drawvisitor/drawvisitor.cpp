#include "drawvisitor.h"
#include <cmath>

DrawVisitor::DrawVisitor(std::shared_ptr<Camera> camera,
                         std::shared_ptr<QPixmap> pixmap,
                         std::shared_ptr<LightSource> light_source,
                         std::shared_ptr<Viewport> viewport)
{
    _camera = camera;
    _pixmap = pixmap;
    _light_source = light_source;
    _viewport = viewport;
}

void DrawVisitor::visit(std::shared_ptr<Composite> models_composite)
{
    _models = models_composite;

    std::shared_ptr<QPainter> painter = std::make_shared<QPainter>();
    painter->begin(_pixmap.get());

    _drawer = QtDrawerFactory().create_drawer(painter);

    Point camera_position = _camera->position();

    int x;
    int y = _viewport->height() / 2;
    int end_x = _viewport->width() / 2;
    int end_y = - _viewport->width() / 2;

    Intensity intensity, intensity_1;

    while (y >= end_y)
    {
        x = - _viewport->width() / 2;

        while (x <= end_x)
        {
            Point xy(x, y, 0);
            Point xy_1(x + _viewport->width() / 2,_viewport->width() / 2 - y, 0);

            xy = _viewport->convert_to_viewport_co_ords(xy);
            ParametricLine line(camera_position,  xy);

            intensity_1 = _ray_trace(line);

            intensity = intensity_1;

            _drawer->draw_pixel(xy_1, intensity);

            x += 1;
        }

        y -= 1;
    }
}

Intensity DrawVisitor::_ray_trace(ParametricLine &line, const int deep)
{
    struct _get_nearest_surface_result res = _get_nearest_surface(line);

    if (res.surface == nullptr)
        return Intensity();

    Intensity intensity, i_d, i_s, i_r;

    BaseSurface *surface = (BaseSurface*)(res.surface.get());

    Point p = line.get_point(res.t);
    Vertex to_light = Vertex(p, _light_source->position());
    ParametricLine from_p_to_source(p, to_light);

    struct _get_nearest_surface_result res_1 = _get_nearest_surface(from_p_to_source);

    if (res_1.surface != nullptr && res_1.t > 1e-2)
        return surface->intensity();

    Vertex normal (surface->get_normal_in_point(p));

    float alpha = normal.get_cos(to_light);

    if (surface->k_d() > 0 && alpha > 0)
        i_d = surface->k_d() * _light_source->intensity() * alpha;

    Vertex r;
    r = normal * 2 * normal.get_scal_mul(to_light) - to_light;

    if (surface->k_s() > 0)
    {
        float betha = normal.get_cos(r);

        i_s = surface->k_s() * _light_source->intensity() * std::pow(betha, 300);
    }

    if (surface->k_r() > 0 && deep < 2)
    {
        ParametricLine line_1(p, _light_source->position());
        line_1.D(r);
        i_r = _ray_trace(line_1, deep + 1) * surface->k_r();
    }

    return surface->intensity() * (1 - surface->k_r())+ i_d + i_s + i_r;
}

struct DrawVisitor::_get_nearest_surface_result DrawVisitor::_get_nearest_surface(ParametricLine &line)
{
    std::shared_ptr<Object> nearest_surface = nullptr;
    float t = -1;

    for (std::shared_ptr<Object> &it_model: *(_models.get()))
    {
        float t_2 = it_model->overall_size().get_crossing(line);

        if (t_2 < 0)
            continue;

        for (std::shared_ptr<Object> &it_surface: *(it_model.get()))
        {
            float t_1 = it_surface->get_parapmetric_line_crossing_value(line);

            if (it_surface->check_point_visibility(line.get_point(t_1)) && (t_1 > t))
            {
                t = t_1;
                nearest_surface = it_surface;
            }
        }
    }

    return {nearest_surface, t};
}
