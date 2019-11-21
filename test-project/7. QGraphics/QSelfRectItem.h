#ifndef QSELFRECTITEM_H
#define QSELFRECTITEM_H

#include <QGraphicsItem>
#include <QRectF>

class QSelfRectItem : public QGraphicsItem
{
public:
    QSelfRectItem();
    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QSELFRECTITEM_H
