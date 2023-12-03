#ifndef MANAGERSHOLDER_H
#define MANAGERSHOLDER_H

#include "scenemanager/scenemanager.h"

class ManagersHolder
{
public:
    ManagersHolder() = delete;
    ~ManagersHolder() = default;
    ManagersHolder(std::shared_ptr<QPixmap> pixmap):
        _scene_manager(new SceneManager(pixmap))
    {};

//    const std::shared_ptr<DrawManager> &draw_manager() {
//        return draw_manager_;
//    }
//    const std::shared_ptr<SceneManager> &scene_manager() {
//        return scene_manager_;
//    };
//    const std::shared_ptr<TransformManager> &transform_manager() {
//        return transform_manager_;
//    }
//    const std::shared_ptr<SceneLoadModerator> &scene_load_moderator() {
//        return scene_load_moderator_;
//    };
private:
//    std::shared_ptr<DrawManager> draw_manager_;
      std::shared_ptr<SceneManager> _scene_manager;
//    std::shared_ptr<TransformManager> transform_manager_;
//    std::shared_ptr<SceneLoadModerator> scene_load_moderator_;
};

#endif // MANAGERSHOLDER_H
