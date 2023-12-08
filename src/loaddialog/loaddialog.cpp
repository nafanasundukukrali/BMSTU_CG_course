#include "loaddialog.h"

LoadDialog::LoadDialog(QObject *parent)
    : QDialog()
{
    setFixedSize(300, 300);
    QMovie *movie = new QMovie(LOADING_PATH);
    QLabel *processLabel = new QLabel(this);
    processLabel->setMovie(movie);
    movie->start();
}
