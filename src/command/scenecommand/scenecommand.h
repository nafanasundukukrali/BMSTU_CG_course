#ifndef SCENECOMMAND_H
#define SCENECOMMAND_H


#include <command/basecommand.h>

class SceneCommand: public BaseCommand {};

//class ClearScene : public SceneCommand {
//public:
//    explicit ClearScene(const std::shared_ptr<BaseDrawer> &drawer)
//        : drawer_(drawer) {
//    }

//    void execute() override {
//        drawer_->clear_scene();
//    }

//private:
//    std::shared_ptr<BaseDrawer> drawer_;
//};

class DrawScene : public SceneCommand {
public:
    void execute() override {
//        auto &scene = managers_->scene_manager()->get_scene();
//        managers_->draw_manager()->set_drawer(drawer_);
//        managers_->draw_manager()->set_camera(managers_->scene_manager()->get_camera());
//        managers_->draw_manager()->draw_scene(scene);
    }
};

class ResetScene : public SceneCommand {
public:
    void execute() override {
//        auto &scene = managers_->scene_manager()->get_scene();
//        managers_->draw_manager()->set_drawer(drawer_);
//        managers_->draw_manager()->set_camera(managers_->scene_manager()->get_camera());
//        managers_->draw_manager()->draw_scene(scene);
    }
};


#endif // SCENECOMMAND_H
