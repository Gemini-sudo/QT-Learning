#include "widget.h"
#include <sstream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setMaximumSize(QSize(450, 380));
    setMinimumSize(QSize(450, 380));

    m_main_table = new QTableWidget(this);
    m_main_table->setColumnCount(4);
    m_main_table->setRowCount(10);

    QTableWidgetItem *first_widget_item = new QTableWidgetItem();
    first_widget_item->setText(tr("checkbox1"));
    QTableWidgetItem *second_widget_item = new QTableWidgetItem();
    second_widget_item->setText(tr("checkbox2"));
    QTableWidgetItem *third_widget_item = new QTableWidgetItem();
    third_widget_item->setText(tr("combobox"));
    QTableWidgetItem *forth_widget_item = new QTableWidgetItem();
    forth_widget_item->setText(tr("button"));
    m_main_table->setHorizontalHeaderItem(0, first_widget_item);
    m_main_table->setHorizontalHeaderItem(1, second_widget_item);
    m_main_table->setHorizontalHeaderItem(2, third_widget_item);
    m_main_table->setHorizontalHeaderItem(3, forth_widget_item);

    m_init_btn = new QPushButton(this);
    m_init_btn->setText("Add New Item...");

    m_content_btn = new QPushButton(this);
    m_content_btn->setText("Get All Content...");

    m_main_layout = new QVBoxLayout(this);
    m_main_layout->addWidget(m_main_table, 9);
    m_main_layout->addWidget(m_init_btn, 1);
    m_main_layout->addWidget(m_content_btn, 1);

    this->setLayout(m_main_layout);

    connect(m_init_btn, SIGNAL(clicked()), this, SLOT(addNewTableItem()));
    connect(m_content_btn, SIGNAL(clicked()), this, SLOT(get_all_content()));
}

Widget::~Widget()
{
}

void Widget::addNewTableItem()
{
    std::ostringstream oss;
    for(int i = 0; i < 10; ++i)
    {
        oss.str("");
        oss << i << " - 0";
        QString text1(oss.str().c_str());
        QCheckBox *check_box1 = new QCheckBox(this);
        check_box1->setText(text1);
        m_main_table->setCellWidget(i, 0, check_box1);

        oss.str("");
        oss << i << " - 1";
        QString text2(oss.str().c_str());
        QCheckBox *check_box2 = new QCheckBox(this);
        check_box2->setText(text2);
        m_main_table->setCellWidget(i, 1, check_box2);

        QComboBox *combo_box = new QComboBox(this);
        QStringList string_list;
        string_list << text1 << text2;
        combo_box->addItems(string_list);
        m_main_table->setCellWidget(i, 2, combo_box);

        QPushButton *tmp_btn = new QPushButton(this);
        oss.str("");
        oss << i << " - button";
        tmp_btn->setText(QString::fromStdString(oss.str()));
        m_main_table->setCellWidget(i, 3, tmp_btn);

        connect(check_box1, SIGNAL(stateChanged(int)), this, SLOT(get_column1_content(int)));
        connect(check_box2, SIGNAL(stateChanged(int)), this, SLOT(get_column2_content(int)));
        connect(combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(get_column3_content(int)));
        connect(tmp_btn, SIGNAL(clicked()), this, SLOT(get_column4_content()));
    }
}

void Widget::get_column1_content(int check_status)
{
    if(Qt::Checked == check_status)
    {
        int current_col = m_main_table->currentColumn();
        int current_row = m_main_table->currentRow();

        QCheckBox* check_box = (QCheckBox*)m_main_table->cellWidget(current_row, current_col);
        qDebug() << "column clicked. content:" << check_box->text();
    }
}

void Widget::get_column2_content(int check_status)
{
    if(Qt::Checked == check_status)
    {
        int current_col = m_main_table->currentColumn();
        int current_row = m_main_table->currentRow();

        QCheckBox* check_box = (QCheckBox*)m_main_table->cellWidget(current_row, current_col);
        qDebug() << "column clicked. content:" << check_box->text();
    }
}

void Widget::get_column3_content(int current_index)
{
    int current_col = m_main_table->currentColumn();
    int current_row = m_main_table->currentRow();

    QComboBox* combo_box = (QComboBox*)m_main_table->cellWidget(current_row, current_col);
    qDebug() << "column clicked. content:" << combo_box->currentText();
}

void Widget::get_column4_content()
{
    int current_col = m_main_table->currentColumn();
    int current_row = m_main_table->currentRow();

    qDebug() << "column clicked. row:" << current_row << ", col:" << current_col;
}

void Widget::get_all_content()
{
    //这里有两种做法，第一是每一个控件添加一个成员变量，到时候遍历成员变量即可；另一种就是实时获取控件的值，这里的代码采用了第二种做法
    QStringList list_string;
    for(int i = 0; i < 10; ++i)
    {
        QCheckBox* check_box1 = (QCheckBox*)m_main_table->cellWidget(i, 0);
        if(check_box1->isChecked())
        {
            list_string << tr("check:") + check_box1->text();
        }

        QCheckBox* check_box2 = (QCheckBox*)m_main_table->cellWidget(i, 1);
        if(check_box2->isChecked())
        {
            list_string << tr("check:") + check_box2->text();
        }

        QComboBox* combo_box = (QComboBox*)m_main_table->cellWidget(i, 2);
        list_string << tr("combo:") + combo_box->currentText();
    }

    qDebug() << "all-result:" << list_string;
}
