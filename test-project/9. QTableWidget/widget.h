#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>

#include <QString>
#include <QStringList>
#include <QDebug>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QTableWidget *m_main_table;

    QPushButton *m_init_btn;
    QPushButton *m_content_btn;
    QHBoxLayout *m_button_layout;

    QVBoxLayout *m_main_layout;

    int current_index = 0;

private slots:
    void addNewTableItem();
    void get_column1_content(int check_status);
    void get_column2_content(int check_status);
    void get_column3_content(int current_index);
    void get_column4_content();

    void get_all_content();
};
#endif // WIDGET_H
