#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QPushButton>
#include <QVBoxLayout>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QTreeWidget *m_tree_widget;
    QPushButton *m_init_btn;
    QVBoxLayout *m_main_widget;

private slots:
    void tree_widget_init();
    void item_expanded_slot(QTreeWidgetItem *item);
    void item_clicked_slot(QTreeWidgetItem *item, int column);
};
#endif // WIDGET_H
