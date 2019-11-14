#include "mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QUrl>
#include <QFile>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    init_ui();
}

MainWindow::~MainWindow()
{
}

void MainWindow::init_ui()
{
    setMaximumSize(QSize(1366, 768));
    setMinimumSize(QSize(1366, 768));
    //菜单栏 后面提取函数
    m_create_menu = new QMenu();
    m_create_menu->setTitle(tr("文件(&N)"));
    m_create_menu->setToolTip(tr("文档操作"));

    m_open_action = new QAction();
    m_open_action->setText(tr("打开文档(&N)"));
    m_open_action->setShortcut(QKeySequence(tr("ctrl+O")));
    m_open_action->setIcon(QIcon(tr(":/res/res/images/open.png")));
    m_create_menu->addAction(m_open_action);

    m_create_action = new QAction();
    m_create_action->setText(tr("新建空文档(&N)"));
    m_create_action->setShortcut(QKeySequence(tr("ctrl+N")));
    m_create_action->setIcon(QIcon(tr(":/res/res/images/create.png")));
    m_create_menu->addAction(m_create_action);

    m_save_action = new QAction();
    m_save_action->setText(tr("保存当前文档(&S)"));
    m_save_action->setShortcut(QKeySequence(tr("ctrl+S")));
    m_save_action->setIcon(QIcon(tr(":/res/res/images/save.png")));
    m_create_menu->addAction(m_save_action);
    this->menuBar()->addMenu(m_create_menu);

    m_about_menu = new QMenu();
    m_about_menu->setTitle(tr("关于(&I)"));
    m_about_menu->setToolTip(tr("关于本软件的相关解释权"));

    m_about_action = new QAction();
    m_about_action->setText(tr("关于本软件(&I)"));
    m_about_action->setShortcut(QKeySequence(tr("ctrl+I")));
    m_about_action->setIcon(QIcon(tr(":/res/res/images/about.png")));
    m_about_menu->addAction(m_about_action);
    this->menuBar()->addMenu(m_about_menu);

    //工具栏
    m_open_btn = new QToolButton();
    m_open_btn->setIcon(QIcon(tr(":/res/res/images/open.png")));
    m_open_btn->setText(tr("打开"));
    m_open_btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    m_create_btn = new QToolButton();
    m_create_btn->setIcon(QIcon(tr(":/res/res/images/create.png")));
    m_create_btn->setText(tr("新建"));
    m_create_btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    m_save_btn = new QToolButton();
    m_save_btn->setIcon(QIcon(tr(":/res/res/images/save.png")));
    m_save_btn->setText(tr("保存"));
    m_save_btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    m_about_btn = new QToolButton();
    m_about_btn->setIcon(QIcon(tr(":/res/res/images/about.png")));
    m_about_btn->setText(tr("关于"));
    m_about_btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    QToolBar *p_tool_bar = this->addToolBar("toolbar");
    p_tool_bar->addWidget(m_create_btn);
    p_tool_bar->addSeparator();
    p_tool_bar->addWidget(m_open_btn);
    p_tool_bar->addSeparator();
    p_tool_bar->addWidget(m_save_btn);
    p_tool_bar->addSeparator();
    p_tool_bar->addWidget(m_about_btn);

    //文本编辑框
    m_main_widget = new QWidget(this);  //mainwindow 添加控件是通过QWidget来添加的
    m_main_layout = new QVBoxLayout(this);
    m_text_edit = new QPlainTextEdit(this);
    m_main_layout->addWidget(m_text_edit);
    m_main_widget->setLayout(m_main_layout);
    setCentralWidget(m_main_widget);

    connect(m_open_action, SIGNAL(triggered()), this, SLOT(open_file()));
    connect(m_create_action, SIGNAL(triggered()), this, SLOT(create_empty_file()));
    connect(m_save_action, SIGNAL(triggered()), this, SLOT(save_file()));
    connect(m_about_action, SIGNAL(triggered()), this, SLOT(show_info()));
    connect(m_open_btn, SIGNAL(clicked()), this, SLOT(open_file()));
    connect(m_create_btn, SIGNAL(clicked()), this, SLOT(create_empty_file()));
    connect(m_save_btn, SIGNAL(clicked()), this, SLOT(save_file()));
    connect(m_about_btn, SIGNAL(clicked()), this, SLOT(show_info()));
}

void MainWindow::open_file()
{
    QString self_filter = "文件文件(*.txt);;C++文件(*.h & *.cpp);;HTML文件(*.html & *.css & *.js);;所有文件(*.*);;";
    m_file_path = QFileDialog::getOpenFileUrl(this, tr("打开文件"), QUrl(QDir::currentPath()), self_filter).toLocalFile();
    if(!m_file_path.isEmpty())
    {
        QFile local_file(m_file_path);
        local_file.open(QIODevice::ReadOnly | QIODevice::Text);
        std::string tmp = local_file.readLine().toStdString();
        while (!tmp.empty())
        {
            m_text_edit->appendPlainText(QString::fromStdString(tmp));
            tmp = local_file.readLine().toStdString();
        }
    }
}

void MainWindow::create_empty_file()
{
    bool ignore_modify = true;
    if(!m_text_edit->toPlainText().isEmpty())
    {
        QMessageBox::StandardButton selected_btn = QMessageBox::critical(this, tr("警告"), tr("当前工作区域存在文本，是否舍弃？"), QMessageBox::Yes | QMessageBox::No);
        if(QMessageBox::No == selected_btn)
        {
            ignore_modify = false;
        }
    }

    if(ignore_modify)
    {
        m_text_edit->clear();
        m_file_path.clear();
    }
}

void MainWindow::save_file()
{
    if(m_file_path.isEmpty())
    {
        QString self_filter = "文件文件(*.txt);;C++文件(*.h & *.cpp);;HTML文件(*.html & *.css & *.js);;所有文件(*.*);;";
        m_file_path = QFileDialog::getSaveFileUrl(this, tr("保存文件"), QUrl(QDir::currentPath()), self_filter).toLocalFile();
    }

    QFile local_file(m_file_path);
    local_file.open(QIODevice::WriteOnly);
    QString file_content = m_text_edit->toPlainText();
    local_file.write(file_content.toStdString().c_str(), file_content.toStdString().size());
}

void MainWindow::show_info()
{
    QMessageBox::critical(this, tr("提示"), tr("本软件由JimLee督导开发. \n如有侵权，请打死他 或者 它..."), QMessageBox::Yes);
}
