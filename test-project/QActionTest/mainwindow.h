#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMenuBar>

#include <QToolBar>
#include <QToolButton>

#include <QStatusBar>
#include <QLabel>
#include <QProgressBar>

#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showAdd();
    void showUpdate();
    void showDelete();
    void addProgress();

private:
    //菜单栏
    QMenu *m_add_menu;
    QAction *m_add_action;

    QMenu *m_update_menu;
    QAction *m_update_action;

    QMenu *m_delete_menu;
    QAction *m_delete_action;

    //工具栏
    QToolBar *m_tool_bar;
    QToolButton *m_add_btn;
    QToolButton *m_update_btn;
    QToolButton *m_delete_btn;

    //状态栏
    QStatusBar *m_status_bar;
    QLabel *m_left_label;
    QProgressBar *m_progress_bar;
    QLabel *m_right_label;
    QTimer *m_timer;

};
#endif // MAINWINDOW_H
