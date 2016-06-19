#include "qt.h"
#include "ui_qt.h"
#include <QPixmap>
#include <QMovie>

QT::QT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QT)
{
    ui->setupUi(this);
    ui->
    QMovie *movie = new QMovie(":/phtotos/picture/P.gif");
    //ui->label->setPixmap(QPixmap("P.gif"));
    ui->label->setMovie(movie);
    movie->start();
}

QT::~QT()
{
    delete ui;
}
