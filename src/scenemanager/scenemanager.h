#pragma once

#include <scene/scene.h>

class SceneManager
{
public:
    SceneManager(std::shared_ptr<QPixmap> pixmap, const uint start_count);
    ~SceneManager() = default;
    explicit SceneManager(const SceneManager &);
    SceneManager(SceneManager &&) noexcept;

    std::string add(uint _builder_i, bool _color, uint _letter, uint _number);
    std::string draw();
    std::string del(uint _letter, uint _number);
    std::string change_material_or_light_params(bool change_material, const Vector3D &reflection,
                                                const double &p, const Vector3D &color);
    std::string move_and_rotate(bool move_camera, bool rotate, const Vector3D &kd, const Vector3D &o);
private:
    std::shared_ptr<Scene> _scene;
    std::string _last_message;
};
