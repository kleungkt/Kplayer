#ifndef QMEDIAPLAYER_H
#define QMEDIAPLAYER_H

#include <QTimer>
#include <QLabel>
#include "vlchelper.h"

class QMediaPlayer : public QLabel
{
    Q_OBJECT
public:
    enum PlayerStatus
    {
        MP_NONE,            // MediaPlayer empty initial status
        MP_OPEN,
        MP_PLAY,
        MP_PAUSE,
        MP_STOP,
        MP_CLOSE,
        MP_DESTROY,
        MP_MEDIA_INIT_FAILED = -1,
        MP_OPERATOR_FAILED = -2,
        MP_TIMER_INIT_FAILED = -3,
        MP_MEDIA_LOAD_FAILED = -4,
    };

public:
    QMediaPlayer(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    explicit QMediaPlayer(const QString& text, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    virtual ~QMediaPlayer();

    PlayerStatus status() { return stat; }
    bool is_playing();
    bool is_paused();
    bool has_media_player();
    bool is_mute();         // Returns true if muted, otherwise false
    int64_t get_duration();
    int volume();

    // Set floating text
    void set_float_text(const QString& text);
    void set_title_text(const QString& title);

protected:
    // virtual void paintEvent(QPaintEvent* event);

public slots:
    void open(const QUrl& path);    // Open (local or network) media
    void play();                    // Play or resume
    void pause();                   // Pause
    void stop();                    // Stop playback
    void close();                   // Close media
    void seek(double pos);
    void set_position(int64_t pos); // Set playback position in milliseconds
    void set_position(int hour, int minute, int second, int millisecond); // Set playback position in HH:MM:SS:mmm format
    void set_scale(float scale);    // Set playback rate
    void pick_frame(QImage& frame, int64_t pos); // Get a frame image at the specified position (for preview)
    void set_size(const QSize& sz); // Change playback window size

private slots:
    void handleTimer();
    void volume(int vol);
    void silence(); // Toggle between mute and unmute

signals:
    // Emitted approximately every 500ms to notify external entities of playback progress
    void position(double pos);

    // Notify about status changes:
    // 0 - Empty, 1 - Open media, 2 - Play, 3 - Pause, 4 - Stop, 5 - Close, <0 - Error
    void media_status(QMediaPlayer::PlayerStatus s);

private:
    // Member initialization. Warning: Only use in the constructor once!
    void init_member();

private:
    QTimer* timer;
    vlchelper* vlc;
    QMediaPlayer::PlayerStatus stat;
    QMediaPlayer::PlayerStatus last;
};

#endif // QMEDIAPLAYER_H
