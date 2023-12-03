#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./ui_mainwindow.h"

#include <QMainWindow>
#include <memory>
#include <QImage>
#include <QScreen>
#include <QDesktopWidget>
#include <QWidget>

#include <facade/facade.h>
//#include <drawer/basedrawer.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
private slots:
    void _on_pushButtonAdd_clicked() {};
    void _on_pushButtonDelete_clicked() {};
    void _on_pushButtonApplySpector_clicked() {};
    void _on_pushButtonApplyCameraChanges_clicked() {};

    MainWindow &_update_scene() { return *this; };

    MainWindow &_make_all_connects();
    MainWindow &_load_all_models() { return *this; };
    MainWindow &_add_color_variants();
    MainWindow &_add_select_position_variants();
private:
    Ui::MainWindow *ui;
    std::shared_ptr<QPixmap> _scene;
    std::unique_ptr<Facade> _facade;
};

#endif // MAINWINDOW_H
