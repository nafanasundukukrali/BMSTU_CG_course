#include "scene.h"

Scene::Scene(std::shared_ptr<QPixmap> pixmap, const uint count)
{
    _camera = std::make_shared<Camera>(Vector3D(250, 250, 250), Vector3D(1, 1, 1),
                                       static_cast<double>(pixmap->width()) / pixmap->height() /*static_cast<double>(1000) / 500*/);
    _light_source = std::make_shared<LightSource>(Vector3D(-500, -500, 500), Vector3D(1, 1, 1));

    _builders = {BishopBuilder(), KingBuilder(), KnightBuilder(), PawnBuilder(), QueenBuilder(), RookBuilder(),
                BishopBuilder(0), KingBuilder(0), KnightBuilder(), PawnBuilder(0), QueenBuilder(0), RookBuilder(0)};

    _pixmap = pixmap;

    _start_scene_generate(count);

    _draw();
}

void Scene::_convert_co_ords_from_dest_to_normal(double &letter, double &number)
{
    letter = letter * BASE_CELL_SIZE + delta;
    number = number * BASE_CELL_SIZE + delta;
}

void Scene::_move_by_cell_co_ords(std::shared_ptr<Model> model, uint letter, uint number)
{
    double l = letter, n = number;
    _convert_co_ords_from_dest_to_normal(l, n);
    Vector3D m = {Vector3D(l, n, 0)};
    model->move(m);
}

void Scene::_start_scene_generate(const size_t count)
{
    std::vector<std::shared_ptr<Object>> objects;
    std::mutex mutex_set[12];
    std::mutex desk_mutex;

    tbb::parallel_for(static_cast<std::size_t>(0), count, [&](std::size_t i)
    {
        uint id = rand() % 12;

        mutex_set[id].lock();
        _builders[id].build();
        std::shared_ptr<Model> model(_builders[id].get());
        mutex_set[id].unlock();
        uint x = i / 8, y = i % 8;
        _move_by_cell_co_ords(model, x, y);
        objects.emplace_back(model);
        desk_mutex.lock();
        _actual_figures[x][y] = 1;
        desk_mutex.unlock();
    });

    ChessDeskBuilder desk;
    desk.build();
    std::shared_ptr<Model> modeld(desk.get());
    objects.emplace_back(modeld);

    _models = std::make_shared<KDTree>(objects);
}

void Scene::delete_model(uint letter, uint number)
{
    if (!_actual_figures[letter][number])
        throw NoFigureOnDesk(__FILE__, __LINE__);

    double l = letter, n = number;
    _convert_co_ords_from_dest_to_normal(l, n);
    _models->delete_node(l-half, n-half, l+half, n+half);
    _actual_figures[letter][number] = false;
}

void Scene::add_model(uint builder_i, bool color, uint letter, uint number)
{
    if (_actual_figures[letter][number])
        throw FigureOnDesk(__FILE__, __LINE__);

    _builders[builder_i + (!color ? 6 : 0)].build();
    std::shared_ptr<Model> model6(_builders[builder_i + (!color ? 6 : 0)].get());
    _move_by_cell_co_ords(model6, letter, number);
    _models->insert_node(model6);
    _actual_figures[letter][number] = true;
}

void Scene::_draw()
{
    std::mutex pixmap_mutex;
    const int width = _pixmap->width(), height = _pixmap->height();
    const double d_width = double(width), d_height = double(height);
    std::shared_ptr<QPainter> painter = std::make_shared<QPainter>();
    painter->begin(_pixmap.get());
    std::unique_ptr<BaseDrawer> drawer = QtDrawerFactory().create_drawer(painter);
    std::mutex image_mutex;
    tbb::parallel_for(0, width * height, 1, [&](int index)
    {
        int j = index / width;
        int i = index % width;
        double i_r = double(i) / d_width;
        double j_r = double(j) / d_height;
        Ray ray = _camera->get_ray(i_r, j_r);
        Vector3D intensity{0, 0, 0};
        HitInfo data;
        intensity += ray_traice(ray, 0, data);
        image_mutex.lock();
        drawer->draw_pixel(Vector3D(i, height - j, 0), intensity);
        image_mutex.unlock();
    });
}

Vector3D Scene::ray_traice(const Ray &r, const int depth, HitInfo &data)
{
    Vector3D itensity(0.0f);

    if (_models->hit(r, 0.0f, MAXFLOAT, data))
    {
        const Ray sunray = _light_source->get_ray(data.hit_point);
        Vector3D sunlight = _light_source->intensity();
        HitInfo buffer_data;

        if (_models->hit(sunray, -1e-9f, MAXFLOAT, buffer_data))
            sunlight *= 0.5f;

        itensity += data.material->ambient() + data.material->diffuse() * sunlight;

        HitInfo buffer2_data;
        Vector3D reflection;
        Ray reflected_ray;

        data.material->get_reflect_ray(r, data, reflection, reflected_ray);

        if (depth < 5 && reflection.x() && reflection.y() && reflection.z())
            itensity += data.material->reflective() * ray_traice(reflected_ray, depth + 1, buffer2_data);
    }

    return itensity;
}
