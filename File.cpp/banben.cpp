#include "banben.h"
#include "ui_banben.h"
#include <QPixmap>

Banben::Banben(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Banben)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap(":/phtotos/picture/pi.jpg"));
}

Banben::~Banben()
{
    delete ui;
}
