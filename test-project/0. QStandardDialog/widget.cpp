#include "widget.h"
#include <QDir>
#include <QFont>
#include <sstream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_open_file = new QPushButton;
    m_open_file->setText("打开文件    ");

    m_line_edit = new QLineEdit;
    m_line_edit->setEnabled(false);

    m_open_file_layout = new QHBoxLayout;
    m_open_file_layout->addWidget(m_open_file, 1, Qt::AlignLeft);
    m_open_file_layout->addWidget(m_line_edit, 2, Qt::AlignRight);

    m_open_files = new QPushButton;
    m_open_files->setText("打开一组文件");

    m_line_edits = new QLineEdit;
    m_line_edits->setEnabled(false);

    m_open_files_layout = new QHBoxLayout;
    m_open_files_layout->addWidget(m_open_files, 1, Qt::AlignLeft);
    m_open_files_layout->addWidget(m_line_edits, 2, Qt::AlignRight);

    m_exist_dir = new QPushButton;
    m_exist_dir->setText("打开已有目录");

    m_exist_dir_edit = new QLineEdit;
    m_exist_dir_edit->setEnabled(false);

    m_exist_dir_layout = new QHBoxLayout;
    m_exist_dir_layout->addWidget(m_exist_dir, 1, Qt::AlignLeft);
    m_exist_dir_layout->addWidget(m_exist_dir_edit, 2, Qt::AlignRight);

    m_save_dir = new QPushButton;
    m_save_dir->setText("保存文件到  ");

    m_save_edit = new QLineEdit;
    m_save_edit->setEnabled(false);

    m_save_layout = new QHBoxLayout;
    m_save_layout->addWidget(m_save_dir, 1, Qt::AlignLeft);
    m_save_layout->addWidget(m_save_edit, 2, Qt::AlignRight);

    m_dialog_layout = new QVBoxLayout;
    m_dialog_layout->addLayout(m_open_file_layout, 1);
    m_dialog_layout->addLayout(m_open_files_layout, 1);
    m_dialog_layout->addLayout(m_exist_dir_layout, 1);
    m_dialog_layout->addLayout(m_save_layout, 1);

    QGroupBox* file_dlg_box = new QGroupBox;
    file_dlg_box->setLayout(m_dialog_layout);
    file_dlg_box->setTitle("FileDialog");

    m_color_btn = new QPushButton;
    m_color_btn->setText("请选择颜色  ");

    m_font_btn = new QPushButton;
    m_font_btn->setText("请选择字体  ");

    m_item_layout = new QHBoxLayout;
    m_item_layout->addWidget(m_color_btn, 1, Qt::AlignLeft);
    m_item_layout->addWidget(m_font_btn, 1, Qt::AlignRight);

    m_color_edit = new QLineEdit;
    m_color_edit->setEnabled(false);

    m_font_layout = new QVBoxLayout;
    m_font_layout->addLayout(m_item_layout);
    m_font_layout->addWidget(m_color_edit);

    QGroupBox* color_dlg_box = new QGroupBox;
    color_dlg_box->setTitle("ColorDialog");
    color_dlg_box->setLayout(m_font_layout);

    m_input_btn = new QPushButton;
    m_input_btn->setText("  获取输入  ");

    m_input_edit = new QLineEdit;
    m_input_edit->setEnabled(false);

    m_input_layout = new QHBoxLayout;
    m_input_layout->addWidget(m_input_btn, 1, Qt::AlignLeft);
    m_input_layout->addWidget(m_input_edit, 2, Qt::AlignRight);

    QGroupBox* input_dlg_box = new QGroupBox;
    input_dlg_box->setTitle("InputDialog");
    input_dlg_box->setLayout(m_input_layout);

    m_main_layout = new QVBoxLayout;
    m_main_layout->addWidget(file_dlg_box);
    m_main_layout->addWidget(color_dlg_box);
    m_main_layout->addWidget(input_dlg_box);

    setLayout(m_main_layout);

    connect(m_open_file, SIGNAL(clicked()), this, SLOT(get_open_file()));
    connect(m_open_files, SIGNAL(clicked()), this, SLOT(get_open_files()));
    connect(m_exist_dir, SIGNAL(clicked()), this, SLOT(get_exist_dir()));
    connect(m_save_dir, SIGNAL(clicked()), this, SLOT(save_file()));
    connect(m_color_btn, SIGNAL(clicked()), this, SLOT(choose_color()));
    connect(m_font_btn, SIGNAL(clicked()), this, SLOT(choose_font()));
    connect(m_input_btn, SIGNAL(clicked()), this, SLOT(get_input()));
};

Widget::~Widget()
{
}

void Widget::get_open_file()
{
    QString current_path = QDir::currentPath();
    QString dlgTitle = "打开文件";
    QString filter="文本文件(*.txt);;图片文件(*.jpg *.gif *.png);;所有文件(*.*);;";
    QString strFileUrl = QFileDialog::getOpenFileUrl(this, dlgTitle, current_path, filter).toLocalFile();
    m_line_edit->setText(strFileUrl);
}

void Widget::get_open_files()
{
    QString current_path = QDir::currentPath();
    QString dlgTitle = "打开文件";
    QString filter="文本文件(*.txt);;图片文件(*.jpg *.gif *.png);;所有文件(*.*);;";
    QList<QUrl> url_list = QFileDialog::getOpenFileUrls(this, dlgTitle, current_path, filter);

    QString strFileUrl;
    for(int i = 0; i < url_list.size(); ++i)
    {
        strFileUrl += url_list[i].toLocalFile() + ";";
    }

    m_line_edits->setText(strFileUrl);
}

void Widget::get_exist_dir()
{
    QUrl url("D:\\software\\Qt5_13\\");
    QString dlgTitle = "打开文件";
    QString dirPath = QFileDialog::getExistingDirectoryUrl(this, dlgTitle, url, QFileDialog::ShowDirsOnly).toLocalFile();
    m_exist_dir_edit->setText(dirPath);
}

void Widget::save_file()
{
    QUrl url("D:\\software\\Qt5_13\\");
    QString dlgTitle = "保存文件";
    QString filter="文本文件(*.txt);;h文件(*.h);;C++文件(.cpp);;所有文件(*.*);;";
    QString filePath = QFileDialog::getSaveFileUrl(this, dlgTitle, url, filter).toLocalFile();
    m_save_edit->setText(filePath);
}

void Widget::choose_color()
{
    QPalette palette_init = m_color_edit->palette();
    QColor color_init = palette_init.color(QPalette::Text);
    QColor current_color = QColorDialog::getColor(color_init, this, "选择颜色");
    if(current_color.isValid())
    {
        int red, green, blue;
        current_color.getRgb(&red, &green, &blue);

        std::ostringstream oss;
        oss << "R:" << red << ", G:" << green << ", B:" << blue;

        QString tmp(oss.str().c_str());
        m_color_edit->setText(tmp);

        palette_init.setColor(QPalette::Text, current_color);
        m_color_edit->setPalette(palette_init);
    }
}

void Widget::choose_font()
{
    bool ok = false;
    QFont font_init = m_color_edit->font();
    QFont current_font = QFontDialog::getFont(&ok, font_init);
    if(ok)
    {
        m_color_edit->setFont(current_font);
    }
}

void Widget::get_input()
{
    bool ok = false;
    QString dlgTitle="输入文字对话框";
    QString txtLabel="请输入文件名";
    QString defaultInput="新建文件.txt";
    QString strText = QInputDialog::getText(this, dlgTitle, txtLabel, QLineEdit::Normal, defaultInput, &ok);
    if(ok)
    {
        m_input_edit->setText(strText);
    }
}
