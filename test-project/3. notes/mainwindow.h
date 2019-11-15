#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include <QToolBar>
#include <QToolButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QString>
#include <string>

#include <QInputDialog>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void init_ui();

    QMenu *m_create_menu;
    QAction *m_open_action;
    QAction *m_create_action;
    QAction *m_save_action;
    QAction *m_save_as_action;

    QMenu *m_find_menu;
    QAction *m_find_action;

    QMenu *m_about_menu;
    QAction *m_about_action;

    QToolButton *m_open_btn;
    QToolButton *m_create_btn;
    QToolButton *m_save_btn;
    QToolButton *m_save_as_btn;
    QToolButton *m_find_btn;
    QToolButton *m_about_btn;

    QTextEdit *m_text_edit;
    QVBoxLayout *m_main_layout;
    QWidget *m_main_widget;

    QString m_file_path;

private slots:
    void open_file();
    void create_empty_file();
    void save_file();
    void save_as();
    void show_info();
    void find_text();
};
#endif // MAINWINDOW_H
