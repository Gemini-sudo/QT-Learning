#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{
}

/*
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    //鼠标按住才有效果
    qDebug() << "mouseMoveEvent x:" << event->x() << ", y:" << event->y();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "mousePressEvent x:" << event->x() << ", y:" << event->y();
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "mouseReleaseEvent x:" << event->x() << ", y:" << event->y();
}
*/

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug() << "mouseDoubleClickEvent x:" << event->x() << ", y:" << event->y();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_pressed)
    {
        QPoint move_pos = event->globalPos() - m_current_pos; //鼠标的全局坐标，减去左上角的坐标，就是当前位置窗口左上角的坐标
        move(move_pos);
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(Qt::LeftButton == event->button())
    {
        m_current_pos = event->globalPos() - pos();  //这里记录的是 鼠标相对于窗口左上角的坐标
        m_pressed = true;
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;
    m_current_pos.setX(0);
    m_current_pos.setY(0);
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_W: qDebug() << "向前走10米"; break;
        case Qt::Key_A: qDebug() << "向左走10米"; break;
        case Qt::Key_D: qDebug() << "向右走10米"; break;
        case Qt::Key_S: qDebug() << "向后走10米"; break;
        case Qt::Key_Space: qDebug() << "跳跃"; break;
        case Qt::Key_Shift: qDebug() << "准备冲刺"; break;
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_W: qDebug() << "停止向前走"; break;
        case Qt::Key_A: qDebug() << "停止向左走"; break;
        case Qt::Key_D: qDebug() << "停止向右走"; break;
        case Qt::Key_S: qDebug() << "停止向后走"; break;
    }
}

