#include "common.h"

bool read_xml_file(const QString file_path, QList<ExecutorInfo>& executor_info_list)
{
    QFile xml_file(file_path);
    if(!xml_file.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }

    QDomDocument xml_doc;
    if(!xml_doc.setContent(&xml_file))
    {
        return false;
    }

    QDomElement xml_element = xml_doc.documentElement();  //这里已经指向root节点
    QDomNode second_node = xml_element.firstChild();

    //后续优化
    while (!second_node.isNull())
    {
        ExecutorInfo exe_info;

        QDomNode third_node = second_node.firstChild();
        while(!third_node.isNull())
        {
            if(third_node.toElement().tagName() == "name")
            {
                exe_info.executorName = third_node.toElement().text();
            }
            else if(third_node.toElement().tagName() == "exepath" && QFile::exists(third_node.toElement().text()))
            {
                exe_info.executorPath = third_node.toElement().text();
            }

            third_node = third_node.nextSibling();
        }

        if(!exe_info.executorName.isEmpty() && !exe_info.executorPath.isEmpty())
        {
            executor_info_list.push_back(exe_info);
        }

        second_node = second_node.nextSibling();
    }

    return true;
}

bool write_xml_file(const QString file_path, const QList<ExecutorInfo>& executor_info_list)
{
    QString xml_content = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
    xml_content.append("<root>");
    foreach (ExecutorInfo exe_info, executor_info_list)
    {
        xml_content.append("<info>");
        xml_content.append("<name>").append(exe_info.executorName).append("</name>");
        xml_content.append("<exepath>").append(exe_info.executorPath).append("</exepath>");
        xml_content.append("</info>");
    }
    xml_content.append("</root>");

    QFile xml_file(file_path);
    if(!xml_file.open(QIODevice::WriteOnly | QFile::Text) && xml_file.exists())
    {
        return false;
    }

    xml_file.write(xml_content.toStdString().c_str());
    xml_file.close();
    return true;
}
