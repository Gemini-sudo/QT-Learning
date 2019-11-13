#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QPushButton *m_vbox_btn1;
    QPushButton *m_vbox_btn2;
    QPushButton *m_vbox_btn3;
    QVBoxLayout *m_vbox_layout;

    QPushButton *m_hbox_btn1;
    QPushButton *m_hbox_btn2;
    QPushButton *m_hbox_btn3;
    QHBoxLayout *m_hbox_layout;

    QPushButton *m_grid_btn1;
    QPushButton *m_grid_btn2;
    QPushButton *m_grid_btn3;
    QGridLayout *m_grid_layout;

    QVBoxLayout *m_main_layout;
};
#endif // WIDGET_H
