#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>

int static i = 0,k = 0,log = 0,wide = 0,num = 0;
namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    float x,y;

    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
protected:

    bool eventFilter(QObject *watched, QEvent *event1);

    void contextMenuEvent(QContextMenuEvent *);

    void mousePressEvent(QMouseEvent *event);

    void dragEnterEvent(QDragEnterEvent *event);

    void dragMoveEvent(QDragMoveEvent *event);

    void dropEvent(QDropEvent *event);

    void keyPressEvent(QKeyEvent *event);

    void Wrong();

private slots:
    void on_action_O_triggered();

    void on_action_D_triggered();

    void on_action_C_triggered();

    void on_action_7_triggered();

    void on_action_13_triggered();

    void on_action_X_2_triggered();

    void on_action_20_triggered();

    void on_action_22_triggered();

    void on_action_17_triggered();

    void on_action_2_triggered();

    void on_action_triggered();

    void on_action_QT_triggered();

    void on_action_P_triggered();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QPixmap pix;
};

#endif // MAINWINDOW_H
