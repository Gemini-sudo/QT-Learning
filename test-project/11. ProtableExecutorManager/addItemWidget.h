#ifndef ADDITEMWIDGET_H
#define ADDITEMWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "qclickablelabel.h"
#include "QFileDialog"
#include "basicData.h"

class AddItemWidget : public QWidget
{
    Q_OBJECT

public:
    AddItemWidget(QWidget *parent = nullptr);
    ~AddItemWidget();

private slots:
    void get_exe_file();
    void get_icon_file();
    void get_result();

signals:
    void add_new_info(ExecutorInfo executor_info);

private:
    QLabel *exe_name_label;
    QLineEdit *exe_name_edit;
    QHBoxLayout *exe_name_layout;

    QLabel *exe_icon_label;
    QLineEdit *exe_icon_edit;
    QClickableLabel *exe_icon_choose;
    QHBoxLayout *exe_icon_layout;

    QLabel *exe_label;
    QLineEdit *exe_edit;
    QClickableLabel *exe_choose;
    QHBoxLayout *exe_layout;

    QClickableLabel *comfirm_label;
    QVBoxLayout *main_layout;
};

#endif // ADDITEMWIDGET_H
