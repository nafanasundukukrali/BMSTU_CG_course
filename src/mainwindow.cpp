#include "mainwindow.h"
#include <QScreen>
#include <QColor>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QProgressDialog>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <command/scenecommand/scenecommand.h>

MainWindow::MainWindow(const uint start_count, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_16->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setWindowTitle("Visual Chess");

    int width = this->frameGeometry().width();
    int height = this->frameGeometry().height();

//    QDesktopWidget wid;

//    int screenWidth = wid.screen()->width();
//    int screenHeight = wid.screen()->height();

//    this->setGeometry((screenWidth/2)-(width/2),(screenHeight/2)-(height/2),width,height);
   this->setGeometry(0,0,1200,90);

   _scene = std::make_shared<QPixmap>(1000, 900);

   _facade = std::unique_ptr<Facade>(new Facade(_scene, start_count));
   _add_select_position_variants();
   _make_all_connects();

    ui->label_16->setPixmap(*_scene);
}

MainWindow &MainWindow::_make_all_connects()
{
    connect(ui->pushButtonAdd, &QPushButton::clicked, this, &MainWindow::_on_pushButtonAdd_clicked);
    connect(ui->pushButtonDelete, &QPushButton::clicked, this, &MainWindow::_on_pushButtonDelete_clicked);
    connect(ui->pushButtonApplyCameraChanges, &QPushButton::clicked, this, &MainWindow::_on_pushButtonApplyCameraChanges_clicked);
    connect(ui->pushButtonApplySpector, &QPushButton::clicked, this, &MainWindow::_on_pushButtonApplySpector_clicked);

    return *this;
}

MainWindow &MainWindow::_add_color_variants()
{
    ui->colorFigureSelector->addItem("Чёрный");
    ui->colorFigureSelector->addItem("Белый");
    return *this;
}

MainWindow &MainWindow::_add_select_position_variants()
{
    char letters[] = "ABCDEFGH";
    char numbers[] = "12345678";

    for (int i = 0; i < 8; i++)
    {
        ui->addPositionLetterSelector->addItem(QString(letters[i]));
        ui->addPositionNumberSelector->addItem(QString(numbers[i]));
        ui->deleteLetterSelector->addItem(QString(letters[i]));
        ui->deleteNumberSelector->addItem(QString(numbers[i]));
    }

    ui->colorFigureSelector->addItem("Чёрный");
    ui->colorFigureSelector->addItem("Белый");

    ui->listOfChessFigures->addItem("Слон");
    ui->listOfChessFigures->addItem("Король");
    ui->listOfChessFigures->addItem("Конь");
    ui->listOfChessFigures->addItem("Пешка");
    ui->listOfChessFigures->addItem("Ферзь");
    ui->listOfChessFigures->addItem("Ладья");

    ui->listOfChessFigures->setCurrentRow(0);
    ui->colorFigureSelector->setCurrentIndex(0);
    ui->addPositionLetterSelector->setCurrentIndex(0);
    ui->addPositionLetterSelector->setCurrentIndex(0);

    return *this;
}

void MainWindow::_draw()
{
    DrawScene *draw = new DrawScene();
    _execute_with_wait(draw);
    delete draw;
    ui->label_16->setPixmap(*_scene);
}


bool MainWindow::_execute_with_wait(BaseCommand *command)
{
    QFutureWatcher<std::string> watcher;
    LoadDialog dialog;
    connect(&watcher, SIGNAL(finished()), &dialog, SLOT(close()));
    QFuture runner = QtConcurrent::run(&Facade::execute, *_facade.get(), command);
    watcher.setFuture(runner);
    dialog.exec();
    watcher.waitForFinished();

    if (runner.result() != "")
    {
        QMessageBox messageBox(this);
        messageBox.critical(0, "Ошибка", runner.result().c_str());

        return false;
    }

    return true;
}

void MainWindow::_on_pushButtonAdd_clicked()
{
    uint id = ui->listOfChessFigures->currentIndex().column();
    uint color = ui->colorFigureSelector->currentIndex();
    uint x = ui->addPositionLetterSelector->currentIndex();
    uint y = ui->addPositionNumberSelector->currentIndex();

    AddModelToScene *command = new AddModelToScene(id, !color, x, y);

    if (_execute_with_wait(command))
        _draw();

    delete command;
}

void MainWindow::_on_pushButtonDelete_clicked()
{
    uint x = ui->deleteLetterSelector->currentIndex();
    uint y = ui->deleteNumberSelector->currentIndex();

    DeleteModelFromScene *command = new DeleteModelFromScene(x, y);

    if (_execute_with_wait(command))
        _draw();

    delete command;
}

void MainWindow::_on_pushButtonApplySpector_clicked()
{
   Vector3D ref = Vector3D(ui->refSpinBox_3->value());
   double p = ui->pSpinBox->value();
   bool current_material = ui->tabWidgetSpector->currentIndex() == 0;

   ChangeLightSourceColorOrMaterialParamsScene *command = new ChangeLightSourceColorOrMaterialParamsScene(current_material, ref, p, Vector3D());

   if (_execute_with_wait(command))
       _draw();

   delete command;
}

MainWindow::~MainWindow() {
    delete ui;
}



