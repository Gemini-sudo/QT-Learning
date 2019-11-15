#include "mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QUrl>
#include <QFile>
#include <QMessageBox>
#include <QTextDocument>
#include <QTextBlock>
#include <QDebug>

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
    m_open_action->setIcon(QIcon(tr(":/res/res/images/open.png")));
    m_create_menu->addAction(m_open_action);

    m_create_action = new QAction();
    m_create_action->setText(tr("新建空文档(&N)"));
    m_create_action->setIcon(QIcon(tr(":/res/res/images/create.png")));
    m_create_menu->addAction(m_create_action);

    m_save_action = new QAction();
    m_save_action->setText(tr("保存当前文档(&S)"));
    m_save_action->setIcon(QIcon(tr(":/res/res/images/save.png")));
    m_create_menu->addAction(m_save_action);

    m_save_as_action = new QAction();
    m_save_as_action->setText(tr("另存为(&P)"));
    m_save_as_action->setIcon(QIcon(tr(":/res/res/images/save_as.png")));
    m_create_menu->addAction(m_save_as_action);
    this->menuBar()->addMenu(m_create_menu);

    m_find_menu = new QMenu();
    m_find_menu->setTitle(tr("查找(&F)"));
    m_find_menu->setToolTip(tr("查找字符串"));

    m_find_action = new QAction();
    m_find_action->setText(tr("查找(&F)"));
    m_find_action->setShortcut(QKeySequence(tr("ctrl+F")));
    m_find_action->setIcon(QIcon(tr(":/res/res/images/find.png")));
    m_find_menu->addAction(m_find_action);
    this->menuBar()->addMenu(m_find_menu);

    m_about_menu = new QMenu();
    m_about_menu->setTitle(tr("关于(&I)"));
    m_about_menu->setToolTip(tr("关于本软件的相关解释权"));

    m_about_action = new QAction();
    m_about_action->setText(tr("关于本软件(&I)"));
    m_about_action->setIcon(QIcon(tr(":/res/res/images/about.png")));
    m_about_menu->addAction(m_about_action);
    this->menuBar()->addMenu(m_about_menu);

    //工具栏
    m_open_btn = new QToolButton();
    m_open_btn->setIcon(QIcon(tr(":/res/res/images/open.png")));
    m_open_btn->setText(tr("打开"));
    m_open_btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_open_btn->setShortcut(QKeySequence(tr("ctrl+O")));

    m_create_btn = new QToolButton();
    m_create_btn->setIcon(QIcon(tr(":/res/res/images/create.png")));
    m_create_btn->setText(tr("新建"));
    m_create_btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_create_btn->setShortcut(QKeySequence(tr("ctrl+N")));

    m_save_btn = new QToolButton();
    m_save_btn->setIcon(QIcon(tr(":/res/res/images/save.png")));
    m_save_btn->setText(tr("保存"));
    m_save_btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_save_btn->setShortcut(QKeySequence(tr("ctrl+S")));

    m_save_as_btn = new QToolButton();
    m_save_as_btn->setIcon(QIcon(tr(":/res/res/images/save_as.png")));
    m_save_as_btn->setText(tr("另存为"));
    m_save_as_btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_save_as_btn->setShortcut(QKeySequence(tr("ctrl+P")));

    m_find_btn = new QToolButton();
    m_find_btn->setIcon(QIcon(tr(":/res/res/images/find.png")));
    m_find_btn->setText(tr("查找"));
    m_find_btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_find_btn->setShortcut(QKeySequence(tr("ctrl+L")));

    m_about_btn = new QToolButton();
    m_about_btn->setIcon(QIcon(tr(":/res/res/images/about.png")));
    m_about_btn->setText(tr("关于"));
    m_about_btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_about_btn->setShortcut(QKeySequence(tr("ctrl+I")));

    QToolBar *p_tool_bar = this->addToolBar("toolbar");
    p_tool_bar->addWidget(m_create_btn);
    p_tool_bar->addSeparator();
    p_tool_bar->addWidget(m_open_btn);
    p_tool_bar->addSeparator();
    p_tool_bar->addWidget(m_save_btn);
    p_tool_bar->addWidget(m_save_as_btn);
    p_tool_bar->addSeparator();
    p_tool_bar->addWidget(m_find_btn);
    p_tool_bar->addSeparator();
    p_tool_bar->addWidget(m_about_btn);

    //文本编辑框
    m_main_widget = new QWidget(this);  //mainwindow 添加控件是通过QWidget来添加的
    m_main_layout = new QVBoxLayout(this);
    m_text_edit = new QTextEdit(this);
    m_text_edit->setFont(QFont(tr("comsolas"), 12, 5));
    m_main_layout->addWidget(m_text_edit);
    m_main_widget->setLayout(m_main_layout);
    setCentralWidget(m_main_widget);

    connect(m_open_action, SIGNAL(triggered()), this, SLOT(open_file()));
    connect(m_create_action, SIGNAL(triggered()), this, SLOT(create_empty_file()));
    connect(m_save_action, SIGNAL(triggered()), this, SLOT(save_file()));
    connect(m_save_as_action, SIGNAL(triggered()), this, SLOT(save_as()));
    connect(m_find_action, SIGNAL(triggered()), this, SLOT(find_text()));
    connect(m_about_action, SIGNAL(triggered()), this, SLOT(show_info()));
    connect(m_open_btn, SIGNAL(clicked()), this, SLOT(open_file()));
    connect(m_create_btn, SIGNAL(clicked()), this, SLOT(create_empty_file()));
    connect(m_save_btn, SIGNAL(clicked()), this, SLOT(save_file()));
    connect(m_save_as_btn, SIGNAL(clicked()), this, SLOT(save_as()));
    connect(m_find_btn, SIGNAL(clicked()), this, SLOT(find_text()));
    connect(m_about_btn, SIGNAL(clicked()), this, SLOT(show_info()));
}

void MainWindow::open_file()
{
    QString self_filter = "文件文件(*.txt);;C++文件(*.h & *.cpp);;HTML文件(*.html & *.css & *.js);;所有文件(*.*);;";
    m_file_path = QFileDialog::getOpenFileUrl(this, tr("打开文件"), QUrl(QDir::currentPath()), self_filter).toLocalFile();
    if(!m_file_path.isEmpty())
    {
        m_text_edit->clear();
        QFile local_file(m_file_path);
        local_file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString line_text;
        std::string tmp = local_file.readLine(1024).toStdString();
        while (!tmp.empty())
        {
            line_text += QString::fromStdString(tmp);
            if(tmp.find("\0") != -1)
            {
                m_text_edit->append(line_text);
                tmp = local_file.readLine(1024).toStdString();
                line_text.clear();
            }
        }
        m_text_edit->append(line_text);
        local_file.close();
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
    QString file_content = m_text_edit->toPlainText();
    qDebug() << "file_content:" << file_content;
    if(!file_content.isEmpty())
    {
        if(m_file_path.isEmpty())
        {
            QString self_filter = "文件文件(*.txt);;C++文件(*.h & *.cpp);;HTML文件(*.html & *.css & *.js);;所有文件(*.*);;";
            m_file_path = QFileDialog::getSaveFileUrl(this, tr("保存文件"), QUrl(tr("")), self_filter).toLocalFile();
        }

        QFile local_file(m_file_path);
        local_file.open(QIODevice::WriteOnly);
        local_file.write(file_content.toStdString().c_str(), file_content.toStdString().size());
    }
}

void MainWindow::save_as()
{
    QString file_content = m_text_edit->toPlainText();
    qDebug() << "file_content:" << file_content;
    if(!file_content.isEmpty())
    {
        QString self_filter = "文件文件(*.txt);;C++文件(*.h & *.cpp);;HTML文件(*.html & *.css & *.js);;所有文件(*.*);;";
        m_file_path = QFileDialog::getSaveFileUrl(this, tr("保存文件"), QUrl(QUrl(tr(""))), self_filter).toLocalFile();
        QFile local_file(m_file_path);
        local_file.open(QIODevice::WriteOnly);
        local_file.write(file_content.toStdString().c_str(), file_content.toStdString().size());
    }
}

void MainWindow::find_text()
{
    //功能复杂的话，可以采用QWidget，然后用信号和槽的机制来得到用户的输入
    if(!m_text_edit->toPlainText().isEmpty())
    {
        bool ok = false;
        QString user_input = QInputDialog::getText(this, tr("查找"), tr("请输入查找的字符"), QLineEdit::Normal, tr(""), &ok);
        if(ok)
        {
            QString standard_message = "<span style=\"color:blue\">" + user_input + "</span>";
            QTextDocument *text_document = m_text_edit->document();
            QString dest_message = "<html>";

            int nCount = text_document->blockCount();
            for(int i = 0; i < nCount; ++i)
            {
                QString line_text = text_document->findBlock(i).text();

                int dest_index = 0;
                dest_index = line_text.indexOf(user_input, dest_index);
                while (-1 != dest_index)
                {
                    line_text.replace(dest_index, user_input.size(), standard_message);
                    dest_index += standard_message.size();
                    dest_index = line_text.indexOf(user_input, dest_index);
                }

                if(i != (nCount - 1))
                {
                    dest_message += line_text + "<br>";
                }
                else
                {
                    dest_message += line_text;
                }
            }
            dest_message += "</html>";

            m_text_edit->clear();
            m_text_edit->append(dest_message);
        }
    }
}

void MainWindow::show_info()
{
    QMessageBox::critical(this, tr("提示"), tr("本软件由JimLee督导开发. \n如有侵权，请打死他 或者 它..."), QMessageBox::Yes);
}
