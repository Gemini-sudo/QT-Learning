#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDateTime>
#include <QLabel>
#include <QGridLayout>
#include <QTimer>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QLabel *m_show_label;
    QLabel *m_time_label;
    QGridLayout *m_main_layout;

private slots:
    void timer_func();
};
#endif // WIDGET_H
