#include "addItemWidget.h"
#include <QMessageBox>
AddItemWidget::AddItemWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowOpacity(0.8);
    setStyleSheet("background-color: #fffdf9;");

    setMaximumSize(QSize(400, 200));
    setMinimumSize(QSize(400, 200));
    setWindowTitle("添加应用程序");

    exe_name_label = new QLabel(this);
    exe_name_label->setText("应用程序名称：");
    exe_name_label->setStyleSheet("padding:0px;margin:0px;width:100px;height:40px;border-radius: 5px;background: #FFDEAD;color: #FFFFFF;");
    exe_name_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    exe_name_edit = new QLineEdit(this);
    exe_name_edit->setPlaceholderText("请在此处输入应用程序名称，不能为空");
    exe_name_edit->setStyleSheet("padding:0px;margin:0px;height:40px;border-radius: 5px;");

    exe_name_layout = new QHBoxLayout();
    exe_name_layout->addWidget(exe_name_label, 4);
    exe_name_layout->addWidget(exe_name_edit, 6);

    exe_icon_label = new QLabel(this);
    exe_icon_label->setText("应用程序图标：");
    exe_icon_label->setStyleSheet("padding:0px;margin:0px;width:100px;height:40px;border-radius: 5px;background: #FFDEAD;color: #FFFFFF;");
    exe_icon_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    exe_icon_edit = new QLineEdit(this);
    exe_icon_edit->setEnabled(false);
    exe_icon_edit->setStyleSheet("padding:0px;margin:0px;height:40px;border-radius: 5px;");
    exe_icon_edit->setPlaceholderText("请选择应用程序的图标文件");
    exe_icon_edit->setText(":/images/app.ico");

    exe_icon_choose = new QClickableLabel(this);
    exe_icon_choose->setText("...");
    exe_icon_choose->setStyleSheet("padding:0px;margin:0px;width:30px;height:40px;border-radius: 5px;background: #00BFFF;color: #FFFFFF;");
    exe_icon_choose->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    exe_icon_layout = new QHBoxLayout();
    exe_icon_layout->addWidget(exe_icon_label, 4);
    exe_icon_layout->addWidget(exe_icon_edit, 5);
    exe_icon_layout->addWidget(exe_icon_choose, 1);

    exe_label = new QLabel(this);
    exe_label->setText("应用程序文件：");
    exe_label->setStyleSheet("padding:0px;margin:0px;width:100px;height:40px;border-radius: 5px;background: #FFDEAD;color: #FFFFFF;");
    exe_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    exe_edit = new QLineEdit(this);
    exe_edit->setPlaceholderText("请选择应用程序文件");
    exe_edit->setEnabled(false);
    exe_edit->setStyleSheet("padding:0px;margin:0px;height:40px;border-radius: 5px;");

    exe_choose = new QClickableLabel(this);
    exe_choose->setText("...");
    exe_choose->setStyleSheet("padding:0px;margin:0px;width:40px;height:40px;border-radius: 5px;background: #00BFFF;color: #FFFFFF;");
    exe_choose->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    exe_layout = new QHBoxLayout();
    exe_layout->addWidget(exe_label, 4);
    exe_layout->addWidget(exe_edit, 5);
    exe_layout->addWidget(exe_choose, 1);

    comfirm_label = new QClickableLabel(this);
    comfirm_label->setText("确认");
    comfirm_label->setStyleSheet("padding:0px;margin:0px;width:400px;height:40px;border-radius: 5px;background: #00BFFF;color: #FFFFFF;");
    comfirm_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    main_layout = new QVBoxLayout();
    main_layout->addLayout(exe_name_layout, 1);
    main_layout->addLayout(exe_icon_layout, 1);
    main_layout->addLayout(exe_layout, 1);
    main_layout->addWidget(comfirm_label, 1);

    setLayout(main_layout);

    connect(exe_icon_choose, SIGNAL(clicked()), this, SLOT(get_icon_file()));
    connect(exe_choose, SIGNAL(clicked()), this, SLOT(get_exe_file()));
    connect(comfirm_label, SIGNAL(clicked()), this, SLOT(get_result()));
}

AddItemWidget::~AddItemWidget()
{

}

void AddItemWidget::get_exe_file()
{
    QString exe_file_path = QFileDialog::getOpenFileUrl(this, tr("请选择一个文件"), QDir::currentPath().append("\\"), tr("可执行文件(*.exe);;所有文件(*.*);;")).toLocalFile();
    if(!exe_file_path.isEmpty())
    {
        exe_edit->setText(exe_file_path);
    }
}

void AddItemWidget::get_icon_file()
{
    QString exe_file_path = QFileDialog::getOpenFileUrl(this, tr("请选择一个文件"), QDir::currentPath().append("\\"), tr("图标文件(*.png *.jpg *.ico);;所有文件(*.*);;")).toLocalFile();
    if(!exe_file_path.isEmpty())
    {
        exe_icon_edit->setText(exe_file_path);
    }
}

void AddItemWidget::get_result()
{
    QString exe_name = exe_name_edit->text();
    QString exe_path = exe_edit->text();
    QString icon_path = exe_icon_edit->text();
    if(!exe_path.isEmpty() && !exe_name.isEmpty() && !icon_path.isEmpty())
    {
        ExecutorInfo executor_info;
        executor_info.executorName = exe_name;
        executor_info.executorPath = exe_path;
        executor_info.iconPath = icon_path;

        emit add_new_info(executor_info);
        this->close();
    }
    else
    {
        QMessageBox::critical(this, "警告", "信息不全，请检查输入栏的信息");
    }
}
