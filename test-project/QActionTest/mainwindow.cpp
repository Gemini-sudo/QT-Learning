#include "mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_add_menu = new QMenu(this);
    m_add_menu->setTitle(tr("新建"));
    //m_add_menu->setIcon(QIcon(tr(":/images/res/images/add.png")));  //文本 和 图标 二选一
    m_add_menu->setToolTip(tr("新建菜单哦"));

    m_add_action = new QAction(this);
    m_add_action->setText(tr("&New")); //这里顺带设置加速键 N
    m_add_action->setIcon(QIcon(tr(":/images/res/images/add.png")));
    //m_add_action->setToolTip(tr("新建菜单哦")); //这里设置没用，现实的还是Menu的提示菜单 菜单栏的提示信息基本没用
    m_add_action->setShortcut(QKeySequence(tr("ctrl+N")));

    m_add_menu->addAction(m_add_action);

    m_update_menu = new QMenu(this);
    m_update_menu->setTitle(tr("修改"));
    m_update_menu->setToolTip(tr("修改菜单哦"));

    m_update_action = new QAction(this);
    m_update_action->setText(tr("&Update")); //这里顺带设置加速键 U
    m_update_action->setIcon(QIcon(tr(":/images/res/images/edit.png")));
    m_update_action->setShortcut(QKeySequence(tr("ctrl+U")));

    m_update_menu->addAction(m_update_action);

    m_delete_menu = new QMenu(this);
    m_delete_menu->setTitle(tr("删除"));
    m_delete_menu->setToolTip(tr("删除菜单哦"));

    m_delete_action = new QAction(this);
    m_delete_action->setText(tr("&Delete"));
    m_delete_action->setIcon(QIcon(tr(":/images/res/images/delete.png")));
    m_delete_action->setShortcut(QKeySequence(tr("ctrl+D")));

    m_delete_menu->addAction(m_delete_action);

    this->menuBar()->addMenu(m_add_menu);
    this->menuBar()->addMenu(m_update_menu);
    this->menuBar()->addMenu(m_delete_menu);

    connect(m_add_action, SIGNAL(triggered()), this, SLOT(showAdd()));
    connect(m_update_action, SIGNAL(triggered()), this, SLOT(showUpdate()));
    connect(m_delete_action, SIGNAL(triggered()), this, SLOT(showDelete()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::showAdd()
{
    QMessageBox::StandardButton standardButton = QMessageBox::information(this, tr("新建"), tr("新建你妹啊"), QMessageBox::Yes | QMessageBox::No);
    if(QMessageBox::Yes == standardButton)
    {
        close();
    }
}

void MainWindow::showUpdate()
{
    QMessageBox::StandardButton standardButton = QMessageBox::information(this, tr("修改"), tr("修改你妹啊"), QMessageBox::Yes | QMessageBox::No);
    if(QMessageBox::Yes == standardButton)
    {
        close();
    }
}

void MainWindow::showDelete()
{
    QMessageBox::StandardButton standardButton = QMessageBox::information(this, tr("删除"), tr("删除你妹啊"), QMessageBox::Yes | QMessageBox::No);
    if(QMessageBox::Yes == standardButton)
    {
        close();
    }
}
