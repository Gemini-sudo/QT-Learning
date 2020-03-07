#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QList>

#include <QDomDocument>
#include <QFile>
#include <QDir>

#include "basicData.h"

#include <QDebug>

bool read_xml_file(const QString file_path, QList<ExecutorInfo>& executor_info_list);
bool write_xml_file(const QString file_path, const QList<ExecutorInfo>& executor_info_list);

#endif // COMMON_H
