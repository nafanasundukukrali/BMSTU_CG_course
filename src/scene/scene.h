#pragma once

#include "builder/pawn/pawn.h"
#include "builder/bishop/bishop.h"
#include "builder/king/king.h"
#include "builder/knight/knight.h"
#include "builder/queen/queen.h"
#include "builder/rook/rook.h"
#include "builder/chessdesk/chessdesk.h"
#include "object/invisibleobject/camera/camera.h"
#include "object/invisibleobject/kdtree/kdtree.h"

class Scene
{
 //   friend DrawVisitor;
public:
    Scene(std::shared_ptr<QPixmap> pixmap);
    ~Scene() = default;
    explicit Scene(const Scene &);
    Scene(Scene &&) noexcept;

    std::shared_ptr<Composite> get_models();
    std::shared_ptr<Camera> get_camera();
    std::shared_ptr<Viewport> get_viewport();
    std::shared_ptr<LightSource> get_light_source();
    void add_model(std::shared_ptr<BaseModel> new_model);
    void remove_model(const char letter_position, const int number_position)
    {
        // TODO
    };
private:
    std::shared_ptr<Camera> _camera;
    std::shared_ptr<LightSource> _light_source;
    std::shared_ptr<Viewport> _viewport;
    std::shared_ptr<Composite> _models;
};
