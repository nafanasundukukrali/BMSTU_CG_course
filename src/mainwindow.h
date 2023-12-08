#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./ui_mainwindow.h"

#include <QMainWindow>
#include <memory>
#include <QImage>
#include <QScreen>
#include <QWidget>
#include <QFutureWatcher>
#include <loaddialog/loaddialog.h>
#include <facade/facade.h>
#include <loaddialog/loaddialog.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const uint start_count, QWidget *parent = nullptr);
    ~MainWindow() override;
private slots:
    void _on_pushButtonAdd_clicked();
    void _on_pushButtonDelete_clicked();
    void _on_pushButtonApplySpector_clicked();
    void _on_pushButtonApplyCameraChanges_clicked() {};

private:
    MainWindow &_update_scene() { return *this; };

    MainWindow &_make_all_connects();
    MainWindow &_load_all_models() { return *this; };
    MainWindow &_add_color_variants();
    MainWindow &_add_select_position_variants();
    void _draw();
    bool _execute_with_wait(BaseCommand *command);

    Ui::MainWindow *ui;
    std::shared_ptr<QPixmap> _scene;
    std::unique_ptr<Facade> _facade;
};

#endif // MAINWINDOW_H
