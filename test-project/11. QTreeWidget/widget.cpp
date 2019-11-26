#include "widget.h"
#include <sstream>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_tree_widget = new QTreeWidget(this);
    QTreeWidgetItem *first_item = new QTreeWidgetItem();
    first_item->setText(0, tr("item 1"));
    QTreeWidgetItem *second_item = new QTreeWidgetItem();
    second_item->setText(0, tr("item 2"));
    QTreeWidgetItem *third_item = new QTreeWidgetItem();
    third_item->setText(0, tr("item 3"));
    QTreeWidgetItem *forth_item = new QTreeWidgetItem();
    forth_item->setText(0, tr("item 4"));

    QStringList strList;
    strList << "name" << "value";
    m_tree_widget->setHeaderLabels(strList);
    //m_tree_widget->setHeaderHidden(true);  //隐藏表头
    m_tree_widget->addTopLevelItem(first_item);
    m_tree_widget->addTopLevelItem(second_item);
    m_tree_widget->addTopLevelItem(third_item);
    m_tree_widget->addTopLevelItem(forth_item);

    m_init_btn = new QPushButton(this);
    m_init_btn->setText(tr("init tree"));

    m_main_widget = new QVBoxLayout(this);
    m_main_widget->addWidget(m_tree_widget);
    m_main_widget->addWidget(m_init_btn);

    setLayout(m_main_widget);

    connect(m_init_btn, SIGNAL(clicked()), this, SLOT(tree_widget_init()));
    connect(m_tree_widget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(item_clicked_slot(QTreeWidgetItem *, int)));
    connect(m_tree_widget, SIGNAL(itemExpanded(QTreeWidgetItem *)), this, SLOT(item_expanded_slot(QTreeWidgetItem *)));
}

Widget::~Widget()
{
}

void Widget::tree_widget_init()
{
    std::ostringstream oss;
    int nCount = m_tree_widget->topLevelItemCount();
    for(int i = 0; i < nCount; ++i)
    {
        QTreeWidgetItem *topWidgetItem = m_tree_widget->topLevelItem(i);
        for(int j = 0; j < i; ++j)
        {
            QTreeWidgetItem *childItem = new QTreeWidgetItem();
            oss.str("");
            oss << i << " - " << j;
            childItem->setText(0, oss.str().c_str());

            oss.str("");
            oss << i << " - " << j << " content...";
            childItem->setText(1, oss.str().c_str());

            topWidgetItem->addChild(childItem);
        }
    }
}

void Widget::item_expanded_slot(QTreeWidgetItem *item)
{
    qDebug() << item->text(0) << " expanded...";
}

void Widget::item_clicked_slot(QTreeWidgetItem *item, int column)
{
    QString strTmp;
    for(int i = 0; i <= column; ++i)
    {
        strTmp.append(item->text(i)).append(" - ");
    }

    qDebug() << strTmp;
}
