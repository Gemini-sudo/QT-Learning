#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMenuBar>

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

private:
    QMenu *m_add_menu;
    QAction *m_add_action;

    QMenu *m_update_menu;
    QAction *m_update_action;

    QMenu *m_delete_menu;
    QAction *m_delete_action;
};
#endif // MAINWINDOW_H
