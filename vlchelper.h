#ifndef VLCHELPER_H
#define VLCHELPER_H

#ifndef SSIZE_T
    #define SSIZE_T
    typedef long long ssize_t;
#endif

#include "vlc/vlc.h"
#include <QString>
#include <QWidget>
#include <fstream>
#include <mediamp4.h>

class vlcmedia
{
public:
    vlcmedia(libvlc_instance_t* instance);
    ~vlcmedia();
    static int open(void* thiz, void** infile, uint64_t* fsize);
    static ssize_t read(void* thiz, uint8_t* buffer, size_t length);
    static int seek(void* thiz, uint64_t offset);
    static void close(void* thiz);
    vlcmedia& operator=(const QString& str);
    operator libvlc_media_t* ();
    void free();
    QString path();
private:
    int open(void** infile, uint64_t* fsize);
    ssize_t read(uint8_t* buffer, size_t length);
    int seek(uint64_t offset);
    void close();
private:
    QString strPath;
    libvlc_media_t* media;
    std::ifstream infile;
    libvlc_instance_t* instance;
    uint64_t media_size;
    MediaBase* media_instance;
};

class vlchelper
{
public:
    vlchelper(QWidget* widget);
    ~vlchelper();
    int prepare(const QString& strPath = "");
    int play();
    int pause();
    int stop();
    int volume(int vol = -1);
    int silence();
    bool isplaying();
    bool ispause() const
    {
        return m_ispause;
    }
    bool ismute();
    libvlc_time_t gettime();  // Returns the playback time in milliseconds
    libvlc_time_t getduration();  // Gets the total duration of the current media playback (in milliseconds)
    int settime(libvlc_time_t time);
    int set_play_rate(float rate);
    float get_play_rate();
    void init_logo();
    void update_logo();
    bool is_logo_enable();
    void init_text(const QString& text);
    void update_text();
    bool is_text_enable();
    bool has_media_player();  // Checks if there is any media currently playing
private:
    void set_float_text();
private:
    libvlc_instance_t* m_instance;
    libvlc_media_player_t* m_player;
    HWND m_hWnd;
    int winHeight;
    int winWidth;
    bool m_isplaying;
    bool m_ispause;
    bool m_issilence;
    int m_volume;
    libvlc_time_t m_duration;  // Current media playback total duration (milliseconds)
    vlcmedia* m_media;
    QFile m_logo;
    QString text;
    QWidget* m_widget;
};

#endif // VLCHELPER_H
