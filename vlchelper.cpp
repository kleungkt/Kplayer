#include "vlchelper.h"
#include <functional>
#include <QDebug>
#include <QTime>
#include <QRandomGenerator>
#include <QImage>
//VLC playback progress callback
//Drag progress, play speed, stop playback
using namespace std;
using namespace std::placeholders;
void libvlc_log_callback(void* data, int level, const libvlc_log_t* ctx,
                         const char* fmt, va_list args)
{
    //qDebug() << "log level:" << level;
}
vlchelper::vlchelper(QWidget* widget)
    : m_logo(":/ico/UI/ico/128-128.png")
{
    const char* const args[] =
    {
        "--sub-filter=logo",
        "--sub-filter=marq"
    };
    qDebug() << __FUNCTION__ << ":" << __LINE__;
    m_instance = libvlc_new(2, args);
    if(m_instance != NULL)
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__;
        m_media = new vlcmedia(m_instance);
    }
    else
    {
        qDebug() << __FUNCTION__ << ":" << __LINE__;
        m_media = NULL;
        throw QString("Is the plugin not installed?!!");
    }
    libvlc_log_set(m_instance, libvlc_log_callback, this);
    m_player = NULL;
    m_hWnd = (HWND)widget->winId();
    winHeight = widget->frameGeometry().height();
    winWidth = widget->frameGeometry().width();
    m_widget = widget;
    qDebug() << "*winWidth:" << winWidth;
    qDebug() << "*winHeight:" << winHeight;
    m_isplaying = false;
    m_ispause = false;
    m_volume = 100;
}

vlchelper::~vlchelper()
{
    if(m_player != NULL)
    {
        stop();
        libvlc_media_player_set_hwnd(m_player, NULL);
        libvlc_media_player_release(m_player);
        m_player = NULL;
    }
    if(m_media != NULL)
    {
        m_media->free();
        m_media = NULL;
    }
    if(m_instance != NULL)
    {
        libvlc_release(m_instance);
        m_instance = NULL;
    }
}

int vlchelper::prepare(const QString& strPath)
{
    qDebug() << strPath;
    //m_media = libvlc_media_new_location(
    //              m_instance, strPath.toStdString().c_str());
    *m_media = strPath;
    if(m_media == NULL)
    {
        return -1;
    }
    if(m_player != NULL)
    {
        libvlc_media_player_release(m_player);
    }
    m_player = libvlc_media_player_new_from_media(*m_media);
    if(m_player == NULL)
    {
        return -2;
    }
    m_duration = libvlc_media_get_duration(*m_media);
    libvlc_media_player_set_hwnd(m_player, m_hWnd);
    libvlc_audio_set_volume(m_player, m_volume);
    libvlc_video_set_aspect_ratio(m_player, "16:9");
    if(text.size() > 0)
    {
        set_float_text();
    }
    m_ispause = false;//Initialize pause state
    m_isplaying = false;//Initialize play state
    m_issilence = false;//Initialize non-mute state
    if(m_widget->frameGeometry().height() != winHeight)
    {
        winHeight = m_widget->frameGeometry().height();
    }
    if(m_widget->frameGeometry().width() != winWidth)
    {
        winWidth = m_widget->frameGeometry().width();
    }
    qDebug() << "*winWidth:" << winWidth;
    qDebug() << "*winHeight:" << winHeight;
    return 0;
}

int vlchelper::play()
{
    if(m_player == NULL)
    {
        return -1;
    }
    if(m_ispause)//If paused, resume playback directly using play
    {
        int ret = libvlc_media_player_play(m_player);
        if(ret == 0)//If execution is successful, change the pause state
        {
            m_ispause = false;
            m_isplaying = true;
        }
        return ret;
    }
    if((m_player == NULL) ||//If no media is set or the media path is empty
            (m_media->path().size() <= 0))
    {
        m_ispause = false;
        m_isplaying = false;
        return -2;
    }
    m_isplaying = true;
    libvlc_video_set_mouse_input(m_player, 0); //Disable mouse interaction in VLC to facilitate Qt handling
    libvlc_video_set_key_input(m_player, 0); //Disable keyboard interaction in VLC to facilitate Qt handling
    libvlc_set_fullscreen(m_player, 1);
    return libvlc_media_player_play(m_player);
}
int vlchelper::pause()
{
    if(m_player == NULL)
    {
        return -1;
    }
    libvlc_media_player_pause(m_player);
    m_ispause = true;
    m_isplaying = false;
    return 0;
}
int vlchelper::stop()
{
    if(m_player != NULL)
    {
        libvlc_media_player_stop(m_player);
        m_isplaying = false;
        return 0;
    }
    return -1;
}
int vlchelper::volume(int vol)
{
    if(m_player == NULL)
    {
        return -1;
    }
    if(vol == -1)
    {
        return m_volume;
    }
    int ret = libvlc_audio_set_volume(m_player, vol);
    if(ret == 0)
    {
        m_volume = vol;
        return m_volume;
    }
    return ret;
}

int vlchelper::silence()
{
    if(m_player == NULL)
    {
        return -1;
    }
    if(m_issilence)
    {
        //Restore audio (unmute)
        libvlc_audio_set_mute(m_player, 0);
        m_issilence = false;
    }
    else
    {
        // or
        // Mute audio
        m_issilence = true;
        libvlc_audio_set_mute(m_player, 1);
    }
    return m_issilence;
}

bool vlchelper::isplaying()
{
    return m_isplaying;
}

bool vlchelper::ismute()
{
    if(m_player && m_isplaying)
    {
        return libvlc_audio_get_mute(m_player) == 1;
    }
    return false;
}

libvlc_time_t vlchelper::gettime()
{
    if(m_player == NULL)
    {
        return -1;
    }
    return libvlc_media_player_get_time(m_player);
}

libvlc_time_t vlchelper::getduration()
{
    if(m_media == NULL)
    {
        return -1;
    }
    if(m_duration == -1)
    {
        m_duration = libvlc_media_get_duration(*m_media);
    }
    return m_duration;
}

int vlchelper::settime(libvlc_time_t time)
{
    if(m_player == NULL)
    {
        return -1;
    }
    libvlc_media_player_set_time(m_player, time);
    return 0;
}

int vlchelper::set_play_rate(float rate)
{
    if(m_player == NULL)
    {
        return -1;
    }
    return libvlc_media_player_set_rate(m_player, rate);
}

float vlchelper::get_play_rate()
{
    if(m_player == NULL)
    {
        return -1.0;
    }
    return libvlc_media_player_get_rate(m_player);
}

void vlchelper::init_logo()
{
    //libvlc_video_set_logo_int(m_player, libvlc_logo_file, m_logo.handle());
    libvlc_video_set_logo_string(m_player, libvlc_logo_file, "128-128.png"); //logo filename
    libvlc_video_set_logo_int(m_player, libvlc_logo_x, 0); //Set the X coordinate of the logo
    //libvlc_video_set_logo_int(m_player, libvlc_logo_y, 0); // Set the Y coordinate of the logo
    libvlc_video_set_logo_int(m_player, libvlc_logo_delay, 100);//Set the interval between logo images in milliseconds (0 - 60000)
    libvlc_video_set_logo_int(m_player, libvlc_logo_repeat, -1); // Set the number of logo repeats (-1 for continuous, 0 to disable)
    libvlc_video_set_logo_int(m_player, libvlc_logo_opacity, 122);
    // Set the logo opacity (values between 0 for fully transparent and 255 for fully opaque)
    libvlc_video_set_logo_int(m_player, libvlc_logo_position, 5);
    //Set the logo position (combination of values like 1, 2, 4, 8, 5, 6, 9, 10)
    libvlc_video_set_logo_int(m_player, libvlc_logo_enable, 1); //Enable the logo (1 for enable, 0 for disable)
}

void vlchelper::init_text(const QString& text)
{
    this->text = text;
}

void vlchelper::update_logo()
{
    static int alpha = 0;
    //static int pos[] = {1, 5, 4, 6, 2, 10, 8, 9};
    int height = QRandomGenerator::global()->bounded(20, winHeight - 20);
    libvlc_video_set_logo_int(m_player, libvlc_logo_y, height); // Set the Y coordinate of the logo
    int width = QRandomGenerator::global()->bounded(20, winWidth - 20);
    libvlc_video_set_logo_int(m_player, libvlc_logo_x, width); //Set the X coordinate of the logo
    libvlc_video_set_logo_int(m_player, libvlc_logo_opacity, (alpha++) % 80 + 20); //Set the opacity of the logo with a changing value based on alpha
    //libvlc_video_set_logo_int(m_player, libvlc_logo_position, pos[alpha % 8]);
}

void vlchelper::update_text()
{
    static int alpha = 0;
    if(m_player)
    {
        int color = QRandomGenerator::global()->bounded(0x30, 0x60);//R
        color = color << 8 | QRandomGenerator::global()->bounded(0x30, 0x60);//G
        color = color << 8 | QRandomGenerator::global()->bounded(0x30, 0x60);//B
        libvlc_video_set_marquee_int(m_player, libvlc_marquee_Color, color);//Set the marquee color using the generated RGB color
        int x = QRandomGenerator::global()->bounded(20, winHeight - 20);//Random X position
        int y = QRandomGenerator::global()->bounded(20, winWidth - 20);// Random Y position
        libvlc_video_set_marquee_int(m_player, libvlc_marquee_X, x);//
        libvlc_video_set_marquee_int(m_player, libvlc_marquee_Y, y);
        //Generate random opacity with a changing value based on alpha
        libvlc_video_set_marquee_int(m_player, libvlc_marquee_Opacity, (alpha++ % 60) + 10);
    }
}

bool vlchelper::is_text_enable()
{
    if(m_player == NULL)
    {
        return false;
    }
    return libvlc_video_get_marquee_int(m_player, libvlc_marquee_Enable) == 1;
}

bool vlchelper::has_media_player()
{
    return m_player != NULL && (m_media != NULL);
}

void vlchelper::set_float_text()
{
    if(m_player)
    {
        libvlc_video_set_marquee_string(m_player, libvlc_marquee_Text, text.toStdString().c_str());
        libvlc_video_set_marquee_int(m_player, libvlc_marquee_Color, 0x404040);
        libvlc_video_set_marquee_int(m_player, libvlc_marquee_X, 0);
        libvlc_video_set_marquee_int(m_player, libvlc_marquee_Y, 0);
        libvlc_video_set_marquee_int(m_player, libvlc_marquee_Opacity, 100);
        //libvlc_video_set_marquee_int(m_player, libvlc_marquee_Timeout, 100);
        libvlc_video_set_marquee_int(m_player, libvlc_marquee_Position, 5);
        libvlc_video_set_marquee_int(m_player, libvlc_marquee_Size, 14);
        libvlc_video_set_marquee_int(m_player, libvlc_marquee_Enable, 1);
    }
}

bool vlchelper::is_logo_enable()
{
    if(m_player == NULL)
    {
        return false;
    }
    qDebug() << __FUNCTION__ << " logo enable:" << libvlc_video_get_logo_int(m_player, libvlc_logo_enable);
    return libvlc_video_get_logo_int(m_player, libvlc_logo_enable) == 1;
}

vlcmedia::vlcmedia(libvlc_instance_t* ins)
    : instance(ins)
{
    media = NULL;
    media_instance = new MediaMP4();
}

vlcmedia::~vlcmedia()
{
    if(media)
    {
        free();
    }
    if(media_instance)
    {
        delete media_instance;
        media_instance = NULL;
    }
}

int vlcmedia::open(void* thiz, void** infile, uint64_t* fsize)
{
    vlcmedia* _this = (vlcmedia*)thiz;
    return _this->open(infile, fsize);
}

ssize_t vlcmedia::read(void* thiz, uint8_t* buffer, size_t length)
{
    vlcmedia* _this = (vlcmedia*)thiz;
    return _this->read(buffer, length);
}

int vlcmedia::seek(void* thiz, uint64_t offset)
{
    vlcmedia* _this = (vlcmedia*)thiz;
    return _this->seek(offset);
}

void vlcmedia::close(void* thiz)
{
    vlcmedia* _this = (vlcmedia*)thiz;
    _this->close();
}

vlcmedia& vlcmedia::operator=(const QString& str)
{
    if(media)
    {
        free();
    }
    //libvlc_media_read_cb
    strPath = str;
    media = libvlc_media_new_callbacks(
                instance,
                &vlcmedia::open,
                &vlcmedia::read,
                &vlcmedia::seek,
                &vlcmedia::close,
                this);
    return *this;
}

void vlcmedia::free()
{
    if(media != NULL)
    {
        libvlc_media_release(media);
    }
}

QString vlcmedia::path()
{
    return strPath;
}

int vlcmedia::open(void** infile, uint64_t* fsize)
{
    //"file:///"
    if(media_instance)
    {
        *infile = this;
        int ret = media_instance->open(strPath, fsize);
        media_size = *fsize;
        return ret;
    }
    this->infile.open(strPath.toStdString().c_str() + 8, ios::binary | ios::in);
    this->infile.seekg(0, ios::end);
    *fsize = (uint64_t)this->infile.tellg();
    media_size = *fsize;
    this->infile.seekg(0);
    *infile = this;
    return 0;
}

ssize_t vlcmedia::read(uint8_t* buffer, size_t length)
{
    if(media_instance)
    {
        return media_instance->read(buffer, length);
    }
    //qDebug() << __FUNCTION__ << " length:" << length;
    uint64_t pos = (uint64_t)infile.tellg();
    //qDebug() << __FUNCTION__ << " positon:" << pos;
    if(media_size - pos < length)
    {
        length = media_size - pos;
    }
    infile.read((char*)buffer, length);
    return infile.gcount();
}

int vlcmedia::seek(uint64_t offset)
{
    if(media_instance)
    {
        return media_instance->seek(offset);
    }
    //qDebug() << __FUNCTION__ << ":" << offset;
    infile.clear();
    infile.seekg(offset);
    return 0;
}

void vlcmedia::close()
{
    if(media_instance)
    {
        return media_instance->close();
    }
    //qDebug() << __FUNCTION__;
    infile.close();
}

vlcmedia::operator libvlc_media_t* ()
{
    return media;
}
