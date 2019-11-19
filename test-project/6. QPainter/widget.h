#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPixmap>
#include <QPainter>
#include <QPoint>
#include <QPen>
#include <QVector>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    QPixmap *m_pixmap;
    QPoint m_current_point;
    QPoint m_tmp_point;
    QPoint m_last_point;

    bool m_clear_line;
};
#endif // WIDGET_H
