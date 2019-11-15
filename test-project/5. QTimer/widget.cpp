#include "widget.h"
#include <QTime>
#include <sstream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_main_layout = new QGridLayout(this);

    m_show_label = new QLabel(this);
    m_show_label->setText(tr("ready to show..."));

    m_time_label = new QLabel(this);
    m_time_label->setText(tr("ready to show..."));

    m_main_layout->addWidget(m_show_label, 0, 0, 1, 1);
    m_main_layout->addWidget(m_time_label, 1, 0, 1, 1);
    setLayout(m_main_layout);

    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_func()));

    //随机数
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
}

Widget::~Widget()
{
}

void Widget::timer_func()
{
    m_show_label->setText(QDateTime::currentDateTime().toString("yyyy-mm-dd hh:MM:ss"));

    int rand = qrand() % 300;
    std::ostringstream oss;
    oss << "random number:" << rand;
    m_time_label->setText(QString::fromStdString(oss.str()));
}
