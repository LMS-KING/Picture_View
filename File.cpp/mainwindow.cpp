#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "banben.h"
#include "qt.h"
#include <QFileDialog>
#include <QErrorMessage>
#include <QLabel>
#include <QDebug>       //输出测试，如：qDebug()<<i;

#include <QPalette>     //调色板类（改变部件背景，字体颜色头文件）
#include <QColor>

#include <QUrl>                    //图片拖放头文件
#include <QList>
#include <QtGui/QPixmap>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QDropEvent>
#include <QMimeData>

#include <QCursor>              //右键菜单头文件
#include <QMenu>
#include <QAction>

#include <QMouseEvent>          //窗体内拖动图片头文件
#include <QPainter>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QPixmap>

#include <QKeyEvent>            //键盘事件头文件
#include <QWheelEvent>

QString Image[1000] = {};
QStringList fileNames;
QMatrix leftmatrix,rightmatrix;
QStringList::Iterator j;
QString path;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)              //构造函数
{
    ui->setupUi(this);

    setWindowOpacity(0.5);          //窗体透明度

    ui->label->installEventFilter(this);
    ui->label->setAcceptDrops(true); // [[1]]: 使label可接受拖放操作

    ui->statusBar->showMessage(tr("欢迎使用本款图片查看器!"),5000);        //临时标签

    QLabel * label = new QLabel(this);                          //永久标签
    label->setFrameStyle(QFrame::Box|QFrame::Sunken);
    label->setText("www.Limaoshuai.com");
    ui->statusBar->addPermanentWidget(label);

    //setMouseTracking(true);        //鼠标跟踪

    ui->pushButton->installEventFilter(this);       //为部件添加事件过滤器
    ui->pushButton_2->installEventFilter(this);
    ui->pushButton_3->installEventFilter(this);
    ui->pushButton_4->installEventFilter(this);
    ui->pushButton_5->installEventFilter(this);
    ui->pushButton_6->installEventFilter(this);

    /*QPalette pal = ui->pushButton->palette();          //改变pushButton字体为红色
    pal.setColor(QPalette::ButtonText,QColor(255,0,0));
    ui->pushButton->setPalette(pal);*/

    //信号与槽
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(on_action_22_triggered()));   //上一张
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(on_action_20_triggered())); //下一张
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(on_action_7_triggered()));  //放大
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(on_action_13_triggered())); //缩小
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(on_action_17_triggered())); //右旋转
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(on_action_2_triggered()));  //左旋转
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)          //拖放图片
{
    //屏蔽方向键控制焦点
    if(watched == ui->pushButton || watched == ui->pushButton_2 || watched == ui->pushButton_3 ||
            watched == ui->pushButton_4 || watched == ui->pushButton_5 ||
            watched == ui->pushButton_6 )
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvnet = static_cast<QKeyEvent*>(event);
            if(keyEvnet->key() == Qt::Key_Up || keyEvnet->key() == Qt::Key_Down ||
                    keyEvnet->key() == Qt::Key_Left || keyEvnet->key() == Qt::Key_Right)
            {
                return true;
            }
        }
    }

    //图片拖动
    if (watched == ui->label)
    {
        if (event->type() == QEvent::DragEnter)
        {
            // 当拖放时鼠标进入label时, label接受拖放的动作
            QDragEnterEvent *dee = dynamic_cast<QDragEnterEvent *>(event);
            dee->acceptProposedAction();
            return true;
            }
        else if (event->type() == QEvent::Drop)
        {
            // 当放操作发生后, 取得拖放的数据
             QDropEvent *de = dynamic_cast<QDropEvent *>(event);
             QList<QUrl> urls = de->mimeData()->urls();

             if (urls.isEmpty())
             {
                 return true;
             }
            path = urls.first().toLocalFile();

            // 在label上显示拖放的图片
             QImage image(path); // QImage对I/O优化过, QPixmap对显示优化
             pix.load(path);
             log = pix.width();
             wide = pix.height();
             if (!image.isNull())
             {
                 image = image.scaled(ui->label->size(),
                                         Qt::KeepAspectRatio,
                                         Qt::SmoothTransformation);
                 ui->label->setPixmap(QPixmap::fromImage(image));
                 ui->label->setAlignment(Qt::AlignCenter);      //显示在label中间
                 num++;   //记录label中已有图片
                }

                return true;
            }
        }
    return QWidget::eventFilter(watched, event);
}

void MainWindow::contextMenuEvent(QContextMenuEvent *)          //右键菜单
{
    QCursor cur=this->cursor();
    QMenu *menu=new QMenu(ui->label);

    QAction *open = menu->addAction(tr("打开"));
    QAction *del = menu->addAction(tr("删除"));
    QAction *big = menu->addAction(tr("放大"));
    QAction *smal = menu->addAction(tr("缩小"));
    QAction *shang = menu->addAction(tr("上一张"));
    QAction *next = menu->addAction(tr("下一张"));
    QAction *left = menu->addAction(tr("左旋转"));
    QAction *right = menu->addAction(tr("右旋转"));

    connect(open,SIGNAL(triggered(bool)),this,SLOT(on_action_O_triggered()));       //打开
    connect(del,SIGNAL(triggered(bool)),this,SLOT(on_action_D_triggered()));        //删除
    connect(big,SIGNAL(triggered(bool)),this,SLOT(on_action_7_triggered()));        //放大
    connect(smal,SIGNAL(triggered(bool)),this,SLOT(on_action_13_triggered()));      //缩小
    connect(shang,SIGNAL(triggered(bool)),this,SLOT(on_action_22_triggered()));     //上一张
    connect(next,SIGNAL(triggered(bool)),this,SLOT(on_action_20_triggered()));      //下一张
    connect(left,SIGNAL(triggered(bool)),this,SLOT(on_action_2_triggered()));       //左旋转
    connect(right,SIGNAL(triggered(bool)),this,SLOT(on_action_17_triggered()));     //右旋转

    menu->exec(cur.pos());
}

//以下四个事件实现图片随鼠标移动
void MainWindow::mousePressEvent(QMouseEvent *event)        //鼠标按下事件
{
    if(event->button() == Qt::LeftButton)
    {
        //第一步，获取图片。将鼠标位置的部件强制转换为QLabel型
        QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
        if(!child->inherits("QLabel"))
            return;
        QPixmap pixmap = *child->pixmap();

        //第二步，自定义MIME类型
        QByteArray itemData;
        QDataStream dataStream(&itemData,QIODevice::WriteOnly);
        //将图片信息，位置信息保存到字节数组中
        dataStream<<pixmap<<QPoint(event->pos() - child->pos());

        //第三步，将数据放入QMimeData中
        QMimeData *mimeData = new QMimeData;
        mimeData->setData("myImage/jpg",itemData);

        //第四步，将QMimelda中的数据放进QDrag
        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap);
        drag->setHotSpot(event->pos() - child->pos());

        //第五步，给原图加阴影
        QPixmap tempPixmap = pixmap;
        QPainter painter;               //绘图
        painter.begin(&tempPixmap);
        //添加透明淡黑色阴影
        painter.fillRect(pixmap.rect(),QColor(127,127,127,127));
        painter.end();
        child->setPixmap(tempPixmap);
        setAcceptDrops(true);
        QLabel *label = new QLabel(this);
        label->setPixmap(pix);
        label->resize(pix.size());


        //第六步，执行拖动操作
        if(drag->exec(Qt::CopyAction | Qt::MoveAction,Qt::CopyAction) == Qt::MoveAction)
            child->close();
        else
        {
            child->show();
            child->setPixmap(pixmap);
        }
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)    //拖动进入事件
{
    if(event->mimeData()->hasFormat("myImage/jpg"))
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
        event->ignore();
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event)       //拖动事件
{
    if(event->mimeData()->hasFormat("myImage/jpg"))
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
        event->ignore();
}

void MainWindow::dropEvent(QDropEvent *event)       //放下事件
{
    if(event->mimeData()->hasFormat("myImage/jpg"))
    {
        QByteArray itemData = event->mimeData()->data("myImage/jpg");
        QDataStream dataStream(&itemData,QIODevice::ReadOnly);
        QPixmap pixmap;
        QPoint offset;
        dataStream>>pixmap>>offset; //使用数据流将字节数据读到QPixmap，QPoint变量中
        //新建标签，为其添加图片，并根据图片大小设置标签大小
        QLabel *newLabel = new QLabel(this);
        newLabel->setPixmap(pixmap);
        newLabel->resize(pixmap.size());

        ui->label = newLabel;       //其他所有操作只针对ui->label

        //是图片移动到放下的位置，不设置会默认显示在（0，0）
        newLabel->move(event->pos() - offset);
        newLabel->show();
        newLabel->setAttribute(Qt::WA_DeleteOnClose);
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
        event->ignore();
}

void MainWindow::Wrong()        //错误提示
{
    QErrorMessage *dialog = new QErrorMessage(this);
    dialog->setWindowTitle("ERROR");
    dialog->showMessage("亲,当前没有图片哦!");
    return;
}

MainWindow::~MainWindow()       //菜单栏功能
{
    delete ui;
}

void MainWindow::on_action_O_triggered()        //打开
{
    fileNames = QFileDialog::getOpenFileNames(this,"picture",
                                               "F:",tr("图片文件(*gif *jpg *png)"));
    for(j = fileNames.begin();j < fileNames.end();j++)
    {
        Image[i] = *j;
        i++;
    }

    QString fileName = Image[0];
    pix.load(fileName);
    log = pix.width();
    wide = pix.height();
   // pix = pix.scaled(851,491);
    ui->label->setPixmap(pix);
    ui->label->setAlignment(Qt::AlignCenter);      //显示在label中间
    ui->label->resize(pix.width(),pix.height());
    num++;   //记录label中已有图片

}

void MainWindow::on_action_D_triggered()        //删除
{
    ui->label->clear();
}

void MainWindow::on_action_C_triggered()        //复制
{

}

void MainWindow::on_action_P_triggered()        //粘贴
{

}

void MainWindow::on_action_7_triggered()        //放大
{
    if(num == 0)
    {
        MainWindow::Wrong();
        return;
    }
       x = pix.height();
       y = pix.width();
       pix = pix.scaled(x * 1.2,y * 1.2,Qt::KeepAspectRatioByExpanding);
       ui->label->setPixmap(pix);
       ui->label->setAlignment(Qt::AlignCenter);      //显示在label中间
       ui->label->resize(pix.width(),pix.height());
}

void MainWindow::on_action_13_triggered()        //缩小
{
    if(num == 0)
    {
        MainWindow::Wrong();
        return;
    }
    x = pix.height();
    y = pix.width();
    if(x <= wide || y <= log)
    {
        QErrorMessage *dialog = new QErrorMessage(this);
        dialog->setWindowTitle("ATTENTION");
        dialog->showMessage("亲,已经是原图了,再小会影响像素啦!");
        return;
    }
    pix= pix.scaled(x/1.2,y/1.2,Qt::KeepAspectRatio);
    ui->label->setPixmap(pix);
    ui->label->setAlignment(Qt::AlignCenter);      //显示在label中间
    ui->label->resize(pix.width(),pix.height());
}

void MainWindow::on_action_20_triggered()        //下一张
{
    if(num == 0)
    {
        MainWindow::Wrong();
        return;
    }
    if(k >= i - 1)
    {
        QErrorMessage *dialog = new QErrorMessage(this);
        dialog->setWindowTitle("ERROR");
        dialog->showMessage("亲,已经是最后一张图片了!");
        return;
    }
    ui->label->clear();
    pix.load(Image[++k]);
   // pix = pix.scaled(851,491);
    ui->label->setPixmap(pix);
    ui->label->setAlignment(Qt::AlignCenter);      //显示在label中间
    ui->label->resize(pix.width(),pix.height());
}

void MainWindow::on_action_22_triggered()        //上一张
{
    if(num == 0)
    {
        MainWindow::Wrong();
        return;
    }
    if(k <= 0)
    {
        QErrorMessage *dialog = new QErrorMessage(this);
        dialog->setWindowTitle("ERROR");
        dialog->showMessage("亲,已经是第一张图片了!");
        return;
    }
    ui->label->clear();
    pix.load(Image[--k]);
   // pix = pix.scaled(851,491);
    ui->label->setPixmap(pix);
    ui->label->setAlignment(Qt::AlignCenter);      //显示在label中间
    ui->label->resize(pix.width(),pix.height());
}

void MainWindow::on_action_17_triggered()        //右旋转
{
    if(num == 0)
    {
        MainWindow::Wrong();
        return;
    }
    rightmatrix.rotate(90);
    ui->label->setPixmap(pix.transformed(rightmatrix,Qt::SmoothTransformation));
}

/*void MainWindow::Dialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.translate(50,50); //让图片的中心作为旋转的中心
    painter.rotate(90); //顺时针旋转90度
    painter.translate(-50,-50); //使原点复原
    painter.drawPixmap(0,0,100,100,pix);
}*/

void MainWindow::on_action_2_triggered()         //左旋转
{
    if(num == 0)
    {
        MainWindow::Wrong();
        return;
    }
    rightmatrix.rotate(-90);
    ui->label->setPixmap(pix.transformed(rightmatrix,Qt::SmoothTransformation));
}

void MainWindow::on_action_triggered()           //版本信息
{
    Banben *ban = new Banben(this);
    ban->setWindowTitle("版本信息");
    ban->setModal(true);
    ban->show();
}

void MainWindow::on_action_QT_triggered()        //关于QT
{
    QT *qt = new QT(this);
    qt->setWindowTitle("关于QT");
    qt ->setModal(true);
    qt->show();
}

void MainWindow::on_action_X_2_triggered()       //退出
{
    this->close();
}

void MainWindow::keyPressEvent(QKeyEvent *event)        //键盘事件
{
    switch(event->key())
    {
        case Qt::Key_W:MainWindow::on_action_7_triggered();break;          //上键放大

        case Qt::Key_S:MainWindow::on_action_13_triggered();break;       //下键缩小

        case Qt::Key_A:MainWindow::on_action_22_triggered();break;        //左键上一张

        case Qt::Key_D:MainWindow::on_action_20_triggered();break;       //右键下一张

        defult:break;
    }
}
