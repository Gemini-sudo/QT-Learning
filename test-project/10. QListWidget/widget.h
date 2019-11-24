#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QListWidget *m_list;
    QPushButton *m_add_btn;
    QVBoxLayout *m_main_layout;

    int current_index;

private slots:
    void addNewItem();
    void itemDoubleClicked(QListWidgetItem *item);
};
#endif // WIDGET_H
