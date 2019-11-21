#include "QSelfEllipseItem.h"
#include <QPainter>
#include <QCursor>
#include <QMimeData>
#include <QGraphicsSceneDragDropEvent>
#include <QVariant>

QSelfEllipseItem::QSelfEllipseItem()
{
    setToolTip("QSelfEllipseItem...");
    setCursor(Qt::PointingHandCursor);
    setFlag(QGraphicsItem::ItemIsFocusable);  //图形项可获得焦点
    setFlag(QGraphicsItem::ItemIsMovable);    //

    setAcceptDrops(true);  //设置接收拖放
}

QRectF ellipse_trans_point(int x, int y, int width, int height)
{
    //there is a self function to transform point, and there seems some problems with Qt point transform function
    return QRectF(x - 400, y - 300, width, height);
}

QRectF QSelfEllipseItem::boundingRect() const
{
    return ellipse_trans_point(400, 300, 200, 150);
}

void QSelfEllipseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    //不需要转换坐标原点
    dragOver ? painter->setBrush(m_drag_color) : painter->setBrush(Qt::red);
    painter->drawEllipse(ellipse_trans_point(400, 300, 200, 150));
}

void QSelfEllipseItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if(event->mimeData()->hasColor()) //如果拖动的数据中有颜色数据，便接收
    {
       event->setAccepted(true);
       dragOver = true;
       update();
    }
    else
    {
        event->setAccepted(false);
    }
}

void QSelfEllipseItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    dragOver = false;
    update();
}

void QSelfEllipseItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    dragOver = false;
    if(event->mimeData()->hasColor())
    {
        //我们通过类型转换来获得颜色
         m_drag_color = qvariant_cast<QColor>(event->mimeData()->colorData());
    }

    update();
}

void QSelfEllipseItem::keyPressEvent(QKeyEvent *event)
{
    moveBy(0, 10);  //相对现在的位置移动
}

void QSelfEllipseItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    moveBy(10, 0);
}
