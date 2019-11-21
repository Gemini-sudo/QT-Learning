#include "widget.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

#include "QSelfRectItem.h"
#include "QSelfEllipseItem.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    /*
    // 场景
    QGraphicsScene *scene = new QGraphicsScene;
    // 矩形项
    QGraphicsRectItem *item = new QGraphicsRectItem(100,100,50,50);
    // 项添加到场景
    scene->addItem(item);
    // 视图
    QGraphicsView *view = new QGraphicsView;
    // 视图关联场景
    view->setScene(scene);
    */

    setMaximumSize(QSize(800, 600));
    setMinimumSize(QSize(800, 600));

    QGraphicsScene *scene = new QGraphicsScene;

    QSelfRectItem *rect_item = new QSelfRectItem;
    scene->addItem(rect_item);

    QSelfEllipseItem *ellipse_item = new QSelfEllipseItem;
    scene->addItem(ellipse_item);

    QGraphicsView *view = new QGraphicsView;
    view->setScene(scene);

    m_main_layout = new QVBoxLayout;
    m_main_layout->addWidget(view);
    this->setLayout(m_main_layout);
}

Widget::~Widget()
{
}

