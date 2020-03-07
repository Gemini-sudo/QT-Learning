#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QList>
#include "basicData.h"

#include <QListWidget>
#include <QHBoxLayout>
#include <QProcess>
#include <QPoint>
#include <QMouseEvent>

#include <QMenu>
#include <QContextMenuEvent>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QList<ExecutorInfo> executor_info_list, QWidget *parent = nullptr);
    ~Widget();


private:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    void contextMenuEvent(QContextMenuEvent *event);

    void show_executor_info();

    void start_progress(QString exe_path);

private slots:
    void launch_progress();  //菜单 -- 执行
    void erase_progress();  //菜单 -- 移除
    void launch_progress(QListWidgetItem *);
    void add_new_item(ExecutorInfo executor_info);

private:
    QPoint StartPos;

    QList<ExecutorInfo> m_executor_info_list;

    QListWidget *m_executor_infos;
    QProcess m_progress;

    QAction *m_execute_action;
    QAction *m_erase_action;
    QMenu *m_right_click_menu;
};
#endif // WIDGET_H
