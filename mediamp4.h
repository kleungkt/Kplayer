#ifndef MEDIAMP4_H
#define MEDIAMP4_H
#include <mediabase.h>

class MediaMP4: public MediaBase
{
public:
    MediaMP4();
    virtual ~MediaMP4();
    virtual int open(const QUrl& url, uint64_t* fsize);
    virtual ssize_t read(uint8_t* buffer, size_t length);
    virtual int seek(uint64_t offset);
    virtual void close();
private:
    void decrypto(QByteArray& data, uint64_t position);
private:
    QByteArray key;
    QFile* file;
    uint16_t pos;
};

#endif // MEDIAMP4_H
