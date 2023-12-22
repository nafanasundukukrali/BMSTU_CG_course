#include "mainwindow.h"

MainWindow::MainWindow(const uint start_count, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_16->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setWindowTitle("Visual Chess");

    int width = this->frameGeometry().width();
    int height = this->frameGeometry().height();

   this->setGeometry(0,0,1200,900);

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
    connect(ui->selectColorButton, &QPushButton::clicked, this, &MainWindow::_on_pushButtonSelectColor_clicked);
    connect(ui->cameraRadioButton, &QPushButton::clicked, this, &MainWindow::_on_camera_radio_button_clicked);
    connect(ui->sourceRadioButton, &QPushButton::clicked, this, &MainWindow::_on_intensity_radio_button_clicked);

    return *this;
}

void MainWindow::_on_pushButtonSelectColor_clicked()
{
    QString title = "Выбор интенсивности точечного источника света";
    QColor color = QColorDialog::getColor(last_color, this, title, QColorDialog::DontUseNativeDialog);

    if (color.isValid())
    {
        QPalette sample_palette;
        sample_palette.setColor(QPalette::Window, color);
        ui->colorLabel->setAutoFillBackground(true);
        ui->colorLabel->setPalette(sample_palette);
        last_color = color;
    }
}

void MainWindow::_on_camera_radio_button_clicked()
{
    ui->TabRotate->setEnabled(true);
}

void MainWindow::_on_intensity_radio_button_clicked()
{
    ui->tabWidgetMoveCamera->setCurrentIndex(0);
    ui->TabRotate->setDisabled(true);
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

    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::white);
    ui->colorLabel->setAutoFillBackground(true);
    ui->colorLabel->setPalette(sample_palette);
    last_color = Qt::white;
    ui->cameraRadioButton->setChecked(true);

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
    uint id = ui->listOfChessFigures->currentIndex().row();
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
   Vector3D ref = Vector3D(1.0f) - Vector3D(ui->refSpinBox_3->value());
   double p = ui->pSpinBox->value();
   bool current_material = ui->tabWidgetSpector->currentIndex() == 0;
   Vector3D intensity(double(last_color.red()) / 255,
                      double(last_color.green()) / 255,
                      double(last_color.blue()) / 255);

   ChangeLightSourceColorOrMaterialParamsScene *command = new ChangeLightSourceColorOrMaterialParamsScene(current_material, ref, p, intensity);

   if (_execute_with_wait(command))
       _draw();

   delete command;
}

void MainWindow::_on_pushButtonApplyCameraChanges_clicked()
{
    Vector3D kd(ui->dx->value(), ui->dy->value(), ui->dz->value());
    Vector3D o(double(ui->ox->value()) * M_PI / 180.0f,
               double(ui->oy->value()) * M_PI / 180.0f,
               double(ui->oz->value()) * M_PI / 180.0f);

    MoveAndRotateScene *command = new MoveAndRotateScene(ui->cameraRadioButton->isChecked(),
                                                         ui->tabWidgetMoveCamera->currentIndex() == 1,
                                                         kd, o);

    if (_execute_with_wait(command))
        _draw();

    delete command;
}

MainWindow::~MainWindow() {
    delete ui;
}



