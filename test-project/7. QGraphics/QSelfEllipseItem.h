#ifndef QSELFELLIPSEITEM_H
#define QSELFELLIPSEITEM_H
#include <QGraphicsItem>
#include <QRectF>

class QSelfEllipseItem : public QGraphicsItem
{
public:
    QSelfEllipseItem();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    bool dragOver = false;

    QColor m_drag_color;
};

#endif // QSELFELLIPSEITEM_H
