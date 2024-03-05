#include "mediamp4.h"
#include <QDebug>

MediaMP4::MediaMP4()
{
    // TODO: Handle plaintext here
    QFile f(":/ico/UI/ico/128-128.png");
    if (f.open(QFile::ReadOnly))
    {
        key = f.readAll();
        f.close();
    }
    file = NULL;
}

MediaMP4::~MediaMP4()
{
    if (file)
    {
        qDebug() << __FILE__ << "(" << __LINE__ << "):";
        file->close();
        delete file;
        qDebug() << __FILE__ << "(" << __LINE__ << "):";
    }
    key.clear();
}

// Success returns NoError
int MediaMP4::open(const QUrl& url, uint64_t* fsize)
{
    if (file)
    {
        file->close();
        delete file;
    }
    // file = new QFile(url.toString().replace("file:///", ""));
    // qDebug() << __FUNCTION__ << url.path().right(url.path().size() - 1);
    file = new QFile(url.path().right(url.path().size() - 1));
    if (file == NULL)
    {
        // qDebug() << __FUNCTION__ << "line:" << __LINE__;
        return QFile::FatalError;
    }
    if (file->error() != QFile::NoError)
    {
        qDebug() << __FUNCTION__ << "line:" << __LINE__;
        int ret = file->error();
        delete file;
        qDebug() << __FILE__ << "(" << __LINE__ << "):";
        file = NULL;
        return ret;
    }
    if (file->open(QFile::ReadOnly))
    {
        *fsize = file->size();
        pos = uint16_t(*fsize & 0xFFFF);
        // qDebug() << __FUNCTION__ << "pos:" << pos;
        return QFile::NoError;
    }
    return file->error();
}

ssize_t MediaMP4::read(uint8_t* buffer, size_t length)
{
    if (file == NULL)
    {
        qDebug() << __FUNCTION__ << "line:" << __LINE__;
        return QFile::FatalError;
    }
    auto position = file->pos();
    qint64 len = file->read((char*)buffer, length);
    // qDebug() << __FUNCTION__ << "len:" << len;
    // qDebug() << __FUNCTION__ << "length:" << length;
    // qDebug() << __FUNCTION__ << "position:" << position;
    if (len > 0)
    {
        for (qint64 i = 0; i < len; i++)
        {
            buffer[i] = buffer[i] ^ key.at((pos + position + i) % key.size());
        }/**/
        return len;
    }
    return QFile::ReadError;
}

int MediaMP4::seek(uint64_t offset)
{
    // qDebug() << __FUNCTION__ << "offset:" << offset;
    if (file == NULL)
    {
        return QFile::FatalError;
    }
    file->seek(offset);
    return file->error();
}

void MediaMP4::close()
{
    if (file)
    {
        file->close();
    }
}
