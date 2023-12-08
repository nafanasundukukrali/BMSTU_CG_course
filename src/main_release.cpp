#include "mainwindow.h"

#include <QApplication>
#include <QDialog>
#include <QInputDialog>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    bool ok = false;
    int start_count = QInputDialog::getInt(nullptr,
                              QString::fromUtf8("Инициализация сцены"),
                              QString::fromUtf8("Введите изначальное количество шахматных фигур на доске:"),
                              5, 0, 64, 1, &ok);
    if (ok)
    {
        MainWindow w(start_count);
        w.show();

        return a.exec();
    }

    a.exit();
}
