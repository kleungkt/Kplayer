#ifndef WIDGET_H
#define WIDGET_H
#include <windows.h>
#include <QWidget>
#include <QSlider>
#include <QDropEvent>
#include <QList>
#include <QListWidgetItem>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QRandomGenerator>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonDocument>
#include "vlchelper.h"
#include "ssltool.h"
#include "qmediaplayer.h" //user defined namespace
#include "infoform.h"
#include "messageform.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();
    virtual void timerEvent(QTimerEvent* event);
protected:
    void save_default_rect_info();
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);
    void handleTimeout(int nTimerID);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual bool eventFilter(QObject* watched, QEvent* event);
    virtual void keyPressEvent(QKeyEvent* event);
private:
    void setSlider(QSlider* slider, int nMin, int nMax, int nStep);
    //Set the slider properties
    void setTime(int hour, int minute, int seconds);
    void setTime(int64_t tm);
    //Set the current playback time
    void setTime2(int hour, int minute, int seconds);
    void setTime2(int64_t tm);
    void paintLine();
    void init_media();
signals:
    void update_pos(double pos);
    void open(const QUrl& url);
    void play();
    void pause();//Pause playback
    void stop();//Stop playback
    void close_media();//Close the media
    void seek(double pos);
    void set_position(int64_t pos);//Set playback position in milliseconds
    void set_position(//Set playback position in milliseconds
        int hour, int minute, int second, int millisecond
    );
    void set_scale(float scale);//Set playback speed
    //Get a frame at a specified position in milliseconds (for preview)
    void pick_frame(QImage& frame, int64_t pos);
    //Change playback window size
    void set_size(const QSize& sz);
    void volume(int vol);
    void silence();
public slots:
    void on_show(const QString& nick, const QByteArray& head);
    void slot_connect_clicked();//After-sales contact
protected slots:
    void on_preButton_clicked();
    void on_playButton_clicked();
    void on_nextButton_clicked();
    void on_volumeButton_clicked();
    void on_scaleButton_clicked();
    void on_horizontalSlider_sliderPressed();
    void on_horizontalSlider_sliderReleased();
    void on_horizontalSlider_rangeChanged(int min, int max);
    void on_horizontalSlider_valueChanged(int value);
    void on_media_position(double pos);
    void on_media_media_status(QMediaPlayer::PlayerStatus s);
    void slots_login_request_finshed(QNetworkReply* reply);
private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem* item);
    void on_volumeSlider_sliderReleased();
    void on_volumeSlider_valueChanged(int value);
    void on_showhideList_pressed();
    void on_closeButton_released();
    void on_fangdaButton_clicked();
    void on_fullscreenBtn_clicked();
    void on_stopButton_clicked();
    void on_time2_clicked();
    void on_time1_5_clicked();
    void on_time1_clicked();
    void on_time0_5_clicked();

    void on_miniButton_clicked();

private:
    void on_fastButton_clicked();
    void on_slowButton_clicked();
    bool keep_activity();
private:
    //different screen size controller
    class SizeHelper
    {
    public:
        SizeHelper(Widget* ui);
        ~SizeHelper();
        //Update when the size is adjusted
        void update(int nWidth, int nHeight);
        // Get the current mouse cursor type: 
        // 0 - Normal, 1 - Top-left, 2 - Top, 3 - Top-right, 
        // 4 - Right, 5 - Bottom-right, 6 - Bottom, 7 - Bottom-left, 8 - Left
        void modify_mouse_cousor(const QPoint& point);
        //Set to false to disable this feature (disabled when in full screen), true to enable (default is true)
        void set_enable(bool isable = true);
        int type()
        {
            return index;
        }
        void press(const QPoint& point);
        void move(const QPoint& point);
        void release();
        void init_size_info(QWidget* widget);
        void set_full_rect(const QString& name, const QRect& rect);
        void set_max_rect(const QString& name, const QRect& rect);
        void set_org_rect(const QString& name, const QRect& rect);
        void set_last_rect(const QString& name, const QRect& rect);
        void set_full_hide(const QString& name, bool is_hide = true);
        void set_max_hide(const QString& name, bool is_hide = true);
        void set_auto_hide(const QString& name, int hide_status = 1);
        void full_size();
        void org_size();
        void max_size();
        int  cur_status() const;
        void auto_hide(bool hidden = true);
    protected:
        struct SizeInfo
        {
            bool is_full_hide;// Full-screen hide
            bool is_max_hide;//Maximized hide
            int auto_hide_status;//Auto-hide status of the control in full-screen mode
            // 0: Do not hide, 1: Hide, 2: Do not participate (the control does not exist in full-screen mode)
            QRect org_rect;//Original size
            QRect max_rect;//Maximized size
            QRect full_rect;//Full-screen size
            QRect last_rect;//Last size
            QWidget* widget;//Control
            SizeInfo()
            {
                widget = NULL;
                is_full_hide = false;
                is_max_hide = false;
            }
        };
    protected:
        //窗口调整属性
        QRect size_rect[8];//8 regions that trigger mouse changes, used to change the overall window size
        bool isabled;//Default is true
        int curent_coursor;//Current cursor type, default is 0, indicating a normal cursor
        QCursor* cursors[9];//Cursors
        int index;//Currently effective cursor
        QPoint point;//Starting point when pressed
        bool pressed;//Pressed state
        Widget* ui;
        QMap<QString, SizeInfo> sub_item_size;
        int status;//Current screen status: 0 - Normal, 1 - Maximized, 2 - Full-screen
    };
private:
    Ui::Widget* ui;
    QList<QUrl> mediaList;
    //vlchelper* vlc;
    SslTool ssl_tool;
    int current_play;
    int timerID;
    int timesCount;
    int timesID;//倍Speed button timer
    int volumeSliderTimerID;
    int fullScreenTimerID;
    int keep_activity_timerID;
    int volumeCount;
    QPoint position;
    float rate;
    bool slider_pressed;
    qint16 tick;
    SizeHelper helper;
    InfoForm info;
    MessageForm* full_head;//Semi-transparent box at the top during full screen
    int screentopTimerID;
    QNetworkAccessManager* net;
    QString nick;//Nickname
};
#endif // WIDGET_H
