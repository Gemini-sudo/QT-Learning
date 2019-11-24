#include "widget.h"
#include <sstream>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_list = new QListWidget(this);
    m_list->setViewMode(QListView::IconMode);

    //m_list->setViewMode(QListView::ListMode);
    m_list->setIconSize(QSize(40,40));  //图标的大小
    m_list->setGridSize(QSize(50,50));  //每个单元格的大小

    m_add_btn = new QPushButton(this);
    m_add_btn->setText("add new item...");

    m_main_layout = new QVBoxLayout(this);
    m_main_layout->addWidget(m_list);
    m_main_layout->addWidget(m_add_btn);

    current_index = 0;

    setLayout(m_main_layout);

    connect(m_add_btn, SIGNAL(clicked()), this, SLOT(addNewItem()));
    connect(m_list, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(itemDoubleClicked(QListWidgetItem *)));
}

Widget::~Widget()
{
}

void Widget::addNewItem()
{
    std::ostringstream oss;
    oss << "item:" << current_index;

    QListWidgetItem* list_item = new QListWidgetItem();
    list_item->setText(QString::fromStdString(oss.str()));
    list_item->setIcon(QIcon(":/images/items.png"));

    m_list->addItem(list_item);

    current_index++;
}

void Widget::itemDoubleClicked(QListWidgetItem *item)
{
    qDebug() << "item:" << item->text();
    //qDebug() << "item:" << m_list->currentItem()->text();
}
