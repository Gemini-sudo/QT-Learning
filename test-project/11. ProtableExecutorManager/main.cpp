#include "widget.h"

#include <QDebug>
#include <QApplication>
#include <QString>

#include "basicData.h"
#include "common.h"

#include "addItemWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QList<ExecutorInfo> executor_info_list;
    read_xml_file(QDir::currentPath().append("/info.xml"), executor_info_list);

    Widget w(executor_info_list);
    w.show();

    return a.exec();
}
