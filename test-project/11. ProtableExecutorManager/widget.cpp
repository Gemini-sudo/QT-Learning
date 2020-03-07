#include "widget.h"
#include <QDir>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QPalette>
#include <QSize>
#include <QBitmap>
#include <QPixmap>
#include <QIcon>

#include <QDebug>
#include "addItemWidget.h"
#include "common.h"

Widget::Widget(QList<ExecutorInfo> executor_info_list, QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("应用程序列表");
    setWindowOpacity(0.8);
    //如果image文件夹下面存在文件 就直接显示到界面 否则就显示为白色
    QDir dir;
    dir.setPath(dir.currentPath() + "/image/");
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QStringList image_list = dir.entryList();
    //TODO 其实这里还要过滤出图像文件的 但是文件格式繁多 暂时不处理
    if(!image_list.empty())
    {
        QPalette pa;
        QPixmap pixmap(dir.path() + "/" + image_list.at(0)); // 资源文件路径
        pixmap = pixmap.scaled(800, 600);
        pa.setBrush(this->backgroundRole(), QBrush(pixmap));
        this->setPalette(pa);

        setMaximumSize(QSize(pixmap.width(), pixmap.height()));
        setMinimumSize(QSize(pixmap.width(), pixmap.height()));
    }
    else
    {
        setStyleSheet("background-color: #fffdf9;");
        setMaximumSize(QSize(800, 600));
        setMinimumSize(QSize(800, 600));
    }

    m_executor_infos = new QListWidget(this);
    m_executor_infos->setViewMode(QListView::IconMode);
    m_executor_infos->setMovement(QListView::Static);
    m_executor_infos->setSpacing(20);
    m_executor_infos->setIconSize(QSize(80,80));  //图标的大小
    m_executor_infos->setGridSize(QSize(80,80));  //每个单元格的大小
    m_executor_infos->setStyleSheet("background-color:transparent;"); //控件不能要背景色

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setMargin(0);  //占满窗口
    layout->addWidget(m_executor_infos);
    setLayout(layout);

    //把文件信息设置到列表上
    m_executor_info_list = executor_info_list;
    show_executor_info();

    //右键菜单初始化
    m_execute_action = new QAction(QIcon(":/images/start.ico"), tr("运行应用"), this);
    m_erase_action = new QAction(QIcon(":/images/erase.ico"), tr("移除应用"), this);
    m_right_click_menu = new QMenu(tr("菜单"), this);
    m_right_click_menu->addAction(m_execute_action);
    m_right_click_menu->addAction(m_erase_action);

    this->connect(m_executor_infos, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(launch_progress(QListWidgetItem *)));
    this->connect(m_execute_action, SIGNAL(triggered()), this, SLOT(launch_progress()));
    this->connect(m_erase_action, SIGNAL(triggered()), this, SLOT(erase_progress()));
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint EndPos;
    if(event->buttons()==Qt::LeftButton)
    {
        EndPos = event->globalPos()- StartPos;
        this->move(EndPos);
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        //记录窗口此时的坐标
        StartPos = event->globalPos() - this->frameGeometry().topLeft();
    }
}

void Widget::contextMenuEvent(QContextMenuEvent *event)
{
    QListWidgetItem *item = m_executor_infos->currentItem();
    QString exe_path = item->data(Qt::UserRole).toString();
    if("add" != exe_path)
    {
        m_right_click_menu->exec(event->globalPos());
    }
}

Widget::~Widget()
{
}

void Widget::show_executor_info()
{
    m_executor_infos->clear();
    foreach(ExecutorInfo exe_info, m_executor_info_list)
    {
        QListWidgetItem* list_item = new QListWidgetItem();
        list_item->setText(exe_info.executorName);

        QPixmap pixmap(exe_info.iconPath);
        pixmap = pixmap.scaled(80, 65);
        list_item->setIcon(QIcon(pixmap));

        list_item->setData(Qt::UserRole, exe_info.executorPath);
        m_executor_infos->addItem(list_item);
    }

    QListWidgetItem* list_item = new QListWidgetItem();
    QPixmap pixmap(":/images/add.ico");
    pixmap = pixmap.scaled(80, 80);
    list_item->setIcon(QIcon(pixmap));
    list_item->setData(Qt::UserRole, "add");
    m_executor_infos->addItem(list_item);
}

void Widget::start_progress(QString exe_path)
{
    int path_type = 0;
    QList<QString> params;
    if(exe_path.indexOf("/") != -1)
    {
        params = exe_path.split("/");
        path_type = 1;
    }
    else if(exe_path.indexOf("\\") != -1)
    {
        params = exe_path.split("\\");
        path_type = 2;
    }
    else
    {
        return;
    }

    m_progress.setProgram(exe_path);

    QString workingDic;
    for(int i = 0; i < params.size() - 1; ++i)
    {
        if(path_type == 1)
        {
            workingDic.append(params.at(i)).append("/");
        }
        else
        {
            workingDic.append(params.at(i)).append("\\");
        }
    }
    m_progress.setWorkingDirectory(workingDic);
    m_progress.startDetached();
}

void Widget::launch_progress()
{
    QListWidgetItem *item = m_executor_infos->currentItem();
    QString exe_path = item->data(Qt::UserRole).toString();
    if("add" != exe_path)
    {
        start_progress(exe_path);
    }
}

void Widget::launch_progress(QListWidgetItem *item)
{
    QString exe_path = item->data(Qt::UserRole).toString();
    if("add" != exe_path)
    {
        start_progress(exe_path);
    }
    else
    {
        //弹出新窗口
        AddItemWidget* add_item_widget = new AddItemWidget();
        add_item_widget->setAttribute(Qt::WA_ShowModal, true);
        add_item_widget->show();
        connect(add_item_widget, SIGNAL(add_new_info(ExecutorInfo)), this, SLOT(add_new_item(ExecutorInfo)));
    }
}

void Widget::erase_progress()
{
    QList<ExecutorInfo> executor_info_list;

    QListWidgetItem *item = m_executor_infos->currentItem();
    QString exe_path = item->data(Qt::UserRole).toString();
    if("add" != exe_path)
    {
        foreach(ExecutorInfo executor, m_executor_info_list)
        {
            if(executor.executorPath != exe_path)
            {
                executor_info_list.push_back(executor);
            }
        }

        m_executor_info_list = executor_info_list;

        show_executor_info();
        write_xml_file(QDir::currentPath().append("/info.xml"), m_executor_info_list);
    }
}

void Widget::add_new_item(ExecutorInfo executor_info)
{
    m_executor_info_list.push_back(executor_info);
    show_executor_info();
    write_xml_file(QDir::currentPath().append("/info.xml"), m_executor_info_list);
}
