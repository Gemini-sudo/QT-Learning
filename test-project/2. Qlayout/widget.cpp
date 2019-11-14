#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setMaximumSize(QSize(600, 400));
    setMinimumSize(QSize(600, 400));

    //垂直布局 参杂了QGroupBox 每一个QGroupBox可以设置一种布局，正好用于展示
    m_vbox_btn1 = new QPushButton(this);
    m_vbox_btn1->setText(tr("vbox_btn1"));

    m_vbox_btn2 = new QPushButton(this);
    m_vbox_btn2->setText(tr("vbox_btn2"));

    m_vbox_btn3 = new QPushButton(this);
    m_vbox_btn3->setText(tr("vbox_btn3"));

    m_vbox_layout = new QVBoxLayout(this);
    m_vbox_layout->addWidget(m_vbox_btn1, 1, Qt::AlignLeft);
    m_vbox_layout->addWidget(m_vbox_btn2, 1, Qt::AlignRight);
    m_vbox_layout->addWidget(m_vbox_btn3, 1, Qt::AlignHCenter);

    QGroupBox *v_group_box = new QGroupBox(this);
    v_group_box->setLayout(m_vbox_layout);
    v_group_box->setTitle(tr("QHBoxLayout"));

    m_hbox_btn1 = new QPushButton(this);
    m_hbox_btn1->setText(tr("hbox_btn1"));

    m_hbox_btn2 = new QPushButton(this);
    m_hbox_btn2->setText(tr("hbox_btn2"));

    m_hbox_btn3 = new QPushButton(this);
    m_hbox_btn3->setText(tr("hbox_btn3"));

    m_hbox_layout = new QHBoxLayout(this);
    m_hbox_layout->addWidget(m_hbox_btn1, 1, Qt::AlignTop);
    m_hbox_layout->addWidget(m_hbox_btn2, 1, Qt::AlignBottom);
    m_hbox_layout->addWidget(m_hbox_btn3, 1, Qt::AlignVCenter);

    QGroupBox *h_group_box = new QGroupBox(this);
    h_group_box->setLayout(m_hbox_layout);
    h_group_box->setTitle(tr("QVBoxLayout"));

    m_grid_btn1 = new QPushButton(this);
    m_grid_btn1->setText(tr("grid_btn1"));

    m_grid_btn2 = new QPushButton(this);
    m_grid_btn2->setText(tr("grid_btn2"));

    m_grid_btn3 = new QPushButton(this);
    m_grid_btn3->setText(tr("grid_btn3"));

    m_grid_layout = new QGridLayout(this);
    m_grid_layout->addWidget(m_grid_btn1, 0, 0, 1, 1);
    m_grid_layout->addWidget(m_grid_btn2, 0, 1, 1, 1);
    m_grid_layout->addWidget(m_grid_btn3, 1, 0, 1, 2); //这里看清楚后面四个数据的含义，分别是起始的X, Y坐标，以及横跨的行数以及列数，算不清楚可以多写几遍就明白了

    QGroupBox *g_group_box = new QGroupBox(this);
    g_group_box->setLayout(m_grid_layout);
    g_group_box->setTitle(tr("QGridLayout"));

    m_main_layout = new QVBoxLayout(this);
    m_main_layout->addWidget(v_group_box);
    m_main_layout->addWidget(h_group_box);
    m_main_layout->addWidget(g_group_box);

    setLayout(m_main_layout);

    //按钮的事件未定义，有兴趣的可以自己实现按钮的点击事件
}

Widget::~Widget()
{
}

