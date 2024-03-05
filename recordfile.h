#ifndef RECORDFILE_H
#define RECORDFILE_H
#include <QString>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonDocument>
#include "ssltool.h"

//Configuration and information logging file classes
class RecordFile
{
public:
    RecordFile(const QString& path);
    ~RecordFile();
    QJsonObject& config();
    bool save();
private:
    QJsonObject m_config;
    QString m_path;
    SslTool tool;
};

#endif // RECORDFILE_H
