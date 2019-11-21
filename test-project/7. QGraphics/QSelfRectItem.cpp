#include "QSelfRectItem.h"
#include <QPainter>
#include <QCursor>
#include <QDrag>
#include <QMimeData>
#include <QGraphicsSceneMouseEvent>
#include <QWidget>

QSelfRectItem::QSelfRectItem()
{
    setToolTip("QSelfRectItem...");
    setCursor(Qt::SizeAllCursor);
}

QRectF rect_trans_point(int x, int y, int width, int height)
{
    //there is a self function to transform point, and there seems some problems with Qt point transform function
    return QRectF(x - 400, y - 300, width, height);
}

QRectF QSelfRectItem::boundingRect() const
{
    //这里构建一个需要绘图的矩形区域  经测试得知 坐标原点在窗口正中心
    return rect_trans_point(0, 0, 100, 100);
}

void QSelfRectItem::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *option,
                          QWidget *widget)
{
    //在已构建的区域里绘制图像
    painter->setBrush(Qt::blue);
    painter->drawRect(rect_trans_point(0, 0, 100, 100));
}

void QSelfRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //为event所在窗口部件新建拖动对象
    QDrag *drag = new QDrag(event->widget());
    //新建QMimeData对象，它用来存储拖动的数据
    QMimeData *mime = new QMimeData;
    //关联
    drag->setMimeData(mime);
    //放入颜色数据
    mime->setColorData(QColor(Qt::blue));

    //新建QPixmap对象，它用来重新绘制圆形，在拖动时显示
    //拖动时跟随的小图像
    QPixmap pix(21,21);
    pix.fill(Qt::blue);
    QPainter painter(&pix);
    paint(&painter, 0, 0);
    drag->setPixmap(pix);

    //我们让指针指向圆形的(10,10)点
    drag->setHotSpot(QPoint(10, 10));
    //开始拖动
    drag->exec();
    //改变光标形状
    setCursor(Qt::OpenHandCursor);
}

void QSelfRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::ClosedHandCursor);
}

void QSelfRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::OpenHandCursor);    //改变光标形状
}
