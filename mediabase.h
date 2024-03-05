#ifndef MEDIABASE_H
#define MEDIABASE_H
#include <QFile>
#include <QUrl>

#ifndef SSIZE_T
    #define SSIZE_T
    typedef long long ssize_t;
#endif

class MediaBase
{
public:
    MediaBase();
    virtual ~MediaBase();
    virtual int open(const QUrl& url, uint64_t* fsize) = 0;
    virtual ssize_t read(uint8_t* buffer, size_t length) = 0;
    virtual int seek(uint64_t offset) = 0;
    virtual void close() = 0;
};

#endif // MEDIABASE_H
