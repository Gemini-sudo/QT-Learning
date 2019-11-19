#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(400, 300);

    m_pixmap = new QPixmap(400, 300);
    m_pixmap->fill(Qt::white);

    m_current_point.setX(-1);
    m_current_point.setY(-1);

    m_last_point.setX(-1);
    m_last_point.setY(-1);

    m_tmp_point.setX(-1);
    m_tmp_point.setY(-1);

    m_clear_line = false;
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPen pen;
    pen.setWidth(5);

    if(m_clear_line)  //there are some bugs here.
    {
        QPainter painter(m_pixmap);
        pen.setColor(Qt::white);
        painter.setPen(pen);
        painter.drawLine(m_last_point, m_tmp_point);

        QPainter main_painter(this);
        main_painter.drawPixmap(0, 0, *m_pixmap);

        m_clear_line = false;
    }

    pen.setColor(QColor(0, 191, 255));

    QPainter painter(m_pixmap);
    painter.setPen(pen);
    painter.drawLine(m_last_point, m_current_point);

    QPainter main_painter(this);
    main_painter.drawPixmap(0, 0, *m_pixmap);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(m_last_point.x() == -1)
    {
        m_last_point.setX(event->x());
        m_last_point.setY(event->y());
    }

    if(event->x() > 400)
    {
        m_current_point.setX(400);
    }
    else
    {
        m_current_point.setX(event->x());
    }

    if(event->y() > 300)
    {
        m_current_point.setY(300);
    }
    else
    {
        m_current_point.setY(event->y());
    }

    this->repaint();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    m_tmp_point = m_current_point;

    if(event->x() > 400)
    {
        m_current_point.setX(400);
    }
    else
    {
        m_current_point.setX(event->x());
    }

    if(event->y() > 300)
    {
        m_current_point.setY(300);
    }
    else
    {
        m_current_point.setY(event->y());
    }

    m_clear_line = true;
    this->repaint();
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->x() > 400)
    {
        m_current_point.setX(400);
    }
    else
    {
        m_current_point.setX(event->x());
    }

    if(event->y() > 300)
    {
        m_current_point.setY(300);
    }
    else
    {
        m_current_point.setY(event->y());
    }

    this->repaint();

    m_last_point = m_current_point;
}
