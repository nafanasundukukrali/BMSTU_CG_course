#pragma once

#include <QDialog>
#include <QMovie>
#include <QLabel>

#ifndef LOADING_PATH
    #define LOADING_PATH "./loadimage/load.gif"
#endif

class LoadDialog : public QDialog
{
public:
    explicit LoadDialog(QObject *parent = nullptr);
private:
};

