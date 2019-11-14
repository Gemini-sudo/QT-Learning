#include "mainwindow.h"
#include <QMessageBox>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMaximumSize(QSize(600, 400));
    setMinimumSize(QSize(600, 400));

    //菜单栏的使用，重复的有点多，只是为了加强认识
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

    //工具栏的使用
    m_add_btn = new QToolButton(this);
    m_add_btn->setIcon(QIcon(tr(":/images/res/images/add.png")));
    m_add_btn->setText(tr("添加"));
    m_add_btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    m_update_btn = new QToolButton(this);
    m_update_btn->setIcon(QIcon(tr(":/images/res/images/edit.png")));
    m_update_btn->setText(tr("修改"));
    m_update_btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    m_delete_btn = new QToolButton(this);
    m_delete_btn->setIcon(QIcon(tr(":/images/res/images/delete.png")));
    m_delete_btn->setText(tr("删除"));
    m_delete_btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    m_tool_bar = addToolBar("toolBar");  //这里调的是窗口的函数，直接就返回了这个toolbar对象
    m_tool_bar->addWidget(m_add_btn);
    m_tool_bar->addWidget(m_update_btn);
    m_tool_bar->addWidget(m_delete_btn);
    m_tool_bar->addSeparator();  //分割线

    //可以直接添加action
    m_tool_bar->addAction(m_add_action);
    m_tool_bar->addAction(m_update_action);
    m_tool_bar->addAction(m_delete_action);

    //状态栏的使用
    m_status_bar = statusBar();

    m_left_label = new QLabel(tr("欢迎使用XXX控件"));
    m_status_bar->addWidget(m_left_label);  //左侧

    m_progress_bar = new QProgressBar(this);
    m_progress_bar->setRange(0, 100);
    m_progress_bar->setValue(0);
    m_status_bar->addPermanentWidget(m_progress_bar);

    m_right_label = new QLabel(this);
    QDateTime date_time = QDateTime::currentDateTime();
    m_right_label->setText(date_time.toString(tr("yyyy-MM-dd hh:mm:ss")));
    m_status_bar->addPermanentWidget(m_right_label);  //右侧

    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    m_timer->start();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(addProgress()));

    connect(m_add_action, SIGNAL(triggered()), this, SLOT(showAdd()));
    connect(m_update_action, SIGNAL(triggered()), this, SLOT(showUpdate()));
    connect(m_delete_action, SIGNAL(triggered()), this, SLOT(showDelete()));
    connect(m_add_btn, SIGNAL(clicked()), this, SLOT(showAdd()));
    connect(m_update_btn, SIGNAL(clicked()), this, SLOT(showUpdate()));
    connect(m_delete_btn, SIGNAL(clicked()), this, SLOT(showDelete()));
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

void MainWindow::addProgress()
{
    int value = (m_progress_bar->value() + 1) % 100;
    m_progress_bar->setValue(value);

    QDateTime date_time = QDateTime::currentDateTime();
    m_right_label->setText(date_time.toString(tr("yyyy-MM-dd hh:mm:ss")));
}
