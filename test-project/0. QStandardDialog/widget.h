#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QInputDialog>

#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QPushButton *m_open_file;
    QLineEdit *m_line_edit;
    QHBoxLayout *m_open_file_layout;

    QPushButton *m_open_files;
    QLineEdit *m_line_edits;
    QHBoxLayout *m_open_files_layout;

    QPushButton *m_exist_dir;
    QLineEdit *m_exist_dir_edit;
    QHBoxLayout *m_exist_dir_layout;

    QPushButton *m_save_dir;
    QLineEdit *m_save_edit;
    QHBoxLayout *m_save_layout;

    QVBoxLayout *m_dialog_layout;

    QPushButton *m_color_btn;
    QPushButton *m_font_btn;
    QLineEdit *m_color_edit;
    QHBoxLayout *m_item_layout;
    QVBoxLayout *m_font_layout;

    QPushButton *m_input_btn;
    QLineEdit *m_input_edit;
    QHBoxLayout *m_input_layout;

    QVBoxLayout *m_main_layout;

private slots:
    void get_open_file();
    void get_open_files();
    void get_exist_dir();
    void save_file();

    void choose_color();
    void choose_font();

    void get_input();
};
#endif // WIDGET_H
