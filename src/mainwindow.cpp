#include "mainwindow.h"
#include <QScreen>
#include <QDesktopWidget>
#include <QColor>
#include <QGraphicsPixmapItem>
//#include <drawer/qtdrawer.h>
//#include <utils/point/point.h>
//#include <utils/intensity/intensity.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_16->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    int width = this->frameGeometry().width();
    int height = this->frameGeometry().height();

    QDesktopWidget wid;

    int screenWidth = wid.screen()->width();
    int screenHeight = wid.screen()->height();

    this->setGeometry((screenWidth/2)-(width/2),(screenHeight/2)-(height/2),width,height);
    _add_select_position_variants();

   _scene = std::make_shared<QPixmap>(1000, 900);

   _facade = std::unique_ptr<Facade>(new Facade(_scene, 2));

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

    ui->listOfChessFigures->addItem("Король");
    ui->listOfChessFigures->addItem("Ферзь");
    ui->listOfChessFigures->addItem("Ладья");
    ui->listOfChessFigures->addItem("Слон");
    ui->listOfChessFigures->addItem("Конь");
    ui->listOfChessFigures->addItem("Пешка");

    return *this;
}

MainWindow::~MainWindow() {
    delete ui;
}



