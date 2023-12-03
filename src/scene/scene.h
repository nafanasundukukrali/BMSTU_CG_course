#pragma once

#undef emit
#include "builder/pawn/pawn.h"
#include "builder/bishop/bishop.h"
#include "builder/king/king.h"
#include "builder/knight/knight.h"
#include "builder/queen/queen.h"
#include "builder/rook/rook.h"
#include "builder/chessdesk/chessdesk.h"
#include "object/invisibleobject/camera/camera.h"
#include "object/invisibleobject/kdtree/kdtree.h"
#include "object/invisibleobject/lightsource/lightsource.h"
#include <random>
#include "tbb/tbb.h"
#include <mutex>
#include "exceptionscene.h"
#define emit

#include <QPixmap>
#include <QPainter>
#include <factory/qtdrawerfactory/qtdrawerfactory.h>

class Scene
{
public:
    Scene(std::shared_ptr<QPixmap> pixmap, const uint count);
    ~Scene() = default;
    explicit Scene(const Scene &);
    Scene(Scene &&) noexcept;
    void delete_model(uint letter, uint number);
    void add_model(const uint builder_id, bool color, uint letter, uint number);
private:
    void _draw();
    Vector3D ray_traice(const Ray &r, const int depth, HitInfo &data);
    void _convert_co_ords_from_dest_to_normal(double &letter, double &number);
    void _move_by_cell_co_ords(std::shared_ptr<Model> model, uint letter, uint number);
    double delta = - BASE_CELL_SIZE * 4 + BASE_CELL_SIZE / 2;
    double half = BASE_CELL_SIZE;
    void _start_scene_generate(const size_t count);
    void _generate_random_figure();
    std::shared_ptr<Camera> _camera;
    std::shared_ptr<LightSource> _light_source;
    std::shared_ptr<KDTree> _models;
    std::vector<BaseBuilder> _builders;
    std::shared_ptr<QPixmap> _pixmap;
    std::vector<std::vector<bool>> _actual_figures = std::vector<std::vector<bool>>(8, std::vector<bool>(8, false));
};
