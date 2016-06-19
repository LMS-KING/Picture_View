#ifndef QT_H
#define QT_H

#include <QDialog>

namespace Ui {
class QT;
}

class QT : public QDialog
{
    Q_OBJECT

public:
    explicit QT(QWidget *parent = 0);
    ~QT();

private:
    Ui::QT *ui;
};

#endif // QT_H
