#ifndef BANBEN_H
#define BANBEN_H

#include <QDialog>

namespace Ui {
class Banben;
}

class Banben : public QDialog
{
    Q_OBJECT

public:
    explicit Banben(QWidget *parent = 0);
    ~Banben();

private:
    Ui::Banben *ui;
};

#endif // BANBEN_H
