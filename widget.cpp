#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QEvent>
#include <QMimeData>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QPainter>
#include <QToolTip>
#include "qstatuscheck.h"
#include <QCryptographicHash>
#include <QDesktopWidget>
extern const char* MD5_KEY; //no extern C, so only cpp is allowed
extern const char* HOST;
extern bool LOGIN_STATUS;
//check_thread + login_status to detect hacking
//use other threads to detect, doesn't affect the main 
QStatusCheck check_thread[32];
#ifdef WIN32 //can put into main
#pragma comment(lib, "User32.lib") //add libraries for WIN32, User32 for encryption
#pragma comment(lib, "libvlccore.lib") //for video player, used in vlchelper.h
#pragma comment(lib, "libvlc.lib")
#endif

//TODO:Add signals to trigger the entire process
const char* PAUSE_STYLESHEET =
        "QPushButton#playButton{"
        "border-image: url(:/ui/button/white/UI/white/);"
        "background-color: transparent;}"
        "QPushButton#playButton:hover{"
        "border-image: url(:/ui/button/blue/UI/blue/);}"
        "QPushButton#playButton:pressed{"
        "border-image: url(:/ui/button/gray/UI/gray/);}";
const char* PLAY_STYLESHEET =
        "QPushButton#playButton{"
        "border-image: url(:/ui/button/blue/UI/blue/start_playing.png);"
        "background-color: transparent;}"
        "QPushButton#playButton:hover{"
        "border-image: url(:/ui/button/gray/UI/gray/start_playing.png);}"
        "QPushButton#playButton:pressed{"
        "border-image: url(:/ui/button/white/UI/white/start_playing.png);}";
//change UI in different p
//Button style when the list is displayed
const char* LIST_SHOW =
        "QPushButton{border-image: url(:/UI/images/);}"
        "QPushButton:hover{border-image: url(:/UI/images/);}"
        "QPushButton:pressed{border-image: url(:/UI/images/);}";
//Button style when the list is hidden
const char* LIST_HIDE =
        "QPushButton{border-image: url(:/UI/images/);}"
        "QPushButton:hover{border-image: url(:/UI/images/);}"
        "QPushButton:pressed{border-image: url(:/UI/images/);}";

//Style for the currently playing file when normal
const char* CURRENT_PLAY_NORMAL =
        "background-color: rgba(255, 255, 255, 0);\nfont: 10pt \"黑体\";"
        "\ncolor: rgb(255, 255, 255);";

const char* CURRENT_PLAY_FULL =
        "background-image: url(:/UI/images/);"
        "background-color: transparent;"
        "\nfont: 20pt \"黑体\";\ncolor: rgb(255, 255, 255);";

//Style for the currently playing file when full
const char* SCREEN_RESTORE_STYLE =
        "QPushButton{border-image: url(:/UI/images/);}\n"
        "QPushButton:hover{border-image:url(:/UI/images/);}\n"
        "QPushButton:pressed{border-image: url(:/UI/images/);}";

const char* SCREEN_MAX_STYLE =
        "QPushButton{border-image: url(:/UI/images/);}\n"
        "QPushButton:hover{border-image:url(:/UI/images/);}\n"
        "QPushButton:pressed{border-image: url(:/UI/images/);}";

#define FLOAT_TYPE (Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint)

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , helper(this)
{
    slider_pressed = false;
    rate = 1.0f;
    ui->setupUi(this);
    //No system border
    this->setWindowFlag(Qt::FramelessWindowHint);
    //Receive file drag and drop
    this->setAcceptDrops(true);
    //Currently not playing any video
    current_play = -1;
    //record the index of the current playing video
    //Button background is transparent
    ui->preButton->setAttribute(Qt::WA_TranslucentBackground, true);
    //only single selection is allowed
    ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->horizontalSlider->setRange(0, 1000);
    ui->horizontalSlider->setValue(0);
    //connect(ui->horizontalSlider, SIGNAL(sliderPressed()),
    //        this, SLOT(on_horizontalSlider_sliderPressed()));
    //connect(ui->horizontalSlider, SIGNAL(sliderReleased()),
    //        this, SLOT(on_horizontalSlider_sliderReleased()));
    //we used the QT controller instead
    //timerID = startTimer(500);//用于刷新进度的
    //Set event filters, we are interested in volume and window events
    ui->volumeButton->installEventFilter(this);
    ui->volumeSlider->installEventFilter(this);
    ui->listWidget->installEventFilter(this);
    ui->scaleButton->installEventFilter(this);//Playback speed button
    ui->horizontalSlider->installEventFilter(this);
    installEventFilter(this);
    //Volume control initialization
    ui->volumeSlider->setVisible(false);
    ui->volumeSlider->setRange(0, 100);
    //Transparent top subtitle layer
    ui->screentop->setHidden(true);
    //Playback speed
    ui->time0_5->setVisible(false);
    ui->time1->setVisible(false);
    ui->time1_5->setVisible(false);
    ui->time2->setVisible(false);
    volumeSliderTimerID = -1;
    timesID = -1;
    timesCount = 0;
    //for speed control
    fullScreenTimerID = -1;
    volumeCount = 0;//for counting time to show volume adjusting panel
    setTime(0, 0, 0);
    setTime2(0, 0, 0);//current time and max time
    QDesktopWidget* desktop = QApplication::desktop();
    int currentScreenWidth = QApplication::desktop()->width();
    int currentScreenHeight = QApplication::desktop()->height();//for full screen
    if(desktop->screenCount() > 1)
    {
        //Get the size of the primary display when multiple displays are present
        currentScreenWidth = desktop->screenGeometry(0).width();
        currentScreenHeight = desktop->screenGeometry(0).height();
    }
    //if screen size smaller than 800 * 600 then set as 800 * 600 
    if(currentScreenWidth > 800 && currentScreenHeight > 600)
    {
        setMaximumSize(currentScreenWidth, currentScreenHeight);
    }
    else
    {
        setMaximumSize(800, 600);
    }
    init_media();
    info.setWindowFlag(Qt::FramelessWindowHint);
    info.setWindowModality(Qt::ApplicationModal);
    connect(&info, SIGNAL(button_clicked()),
            this, SLOT(slot_connect_clicked()));
    //info window for VIP access
    QSize sz = size();
    info.move((sz.width() - info.width()) / 2, (sz.height() - info.height()) / 2);
    ui->curplay->setText(u8"");
    //ui->curplay->setAttribute(Qt::WA_TranslucentBackground);
    //ui->curplay->setWindowOpacity(0.5);
    //Window size controller
    helper.update(width(), height());
    //Set minimum and maximum window sizes (minimum is 800x600, maximum is the screen size)
    setMinimumSize(800, 600);
    save_default_rect_info();
    full_head = new MessageForm();
    full_head->setWindowFlags(FLOAT_TYPE);
    full_head->full_size();
    full_head->move(0, 0);
    //full_head->show();
    //full_head->setHidden(false);
    screentopTimerID = startTimer(50);
    keep_activity_timerID = startTimer(300000);
    net = new QNetworkAccessManager(this);
    connect(net, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slots_login_request_finshed(QNetworkReply*)));
    connect(this, SIGNAL(update_pos(double)), ui->media, SLOT(seek(double)));
}

Widget::~Widget()
{
    killTimer(keep_activity_timerID);
    delete net;
    delete ui;
    delete full_head;
}

void Widget::timerEvent(QTimerEvent* event)
{
    if(event->timerId() == keep_activity_timerID)
    {
        check_thread[GetTickCount()%32].start();
        //TODO:can also keep alive for server here
    }
    else if(event->timerId() == timesID) //1s 
    //for speed control panel
    //timesId set as 200ms, so ~1s trigger the following if clause
    {
        timesCount++;
        if(timesCount > 5)
        {
            timesCount = 0;
            ui->time0_5->setVisible(false);
            ui->time1->setVisible(false);
            ui->time1_5->setVisible(false);
            ui->time2->setVisible(false);
            killTimer(timesID);
            timesID = -1;
            //qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
        }
        //qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):" << timesCount;
    }
    else if(event->timerId() == volumeSliderTimerID)
    {
        volumeCount++;
        if(volumeCount > 5)//When the timer expires, automatically destroy it
        {
            volumeCount = 0;
            ui->volumeSlider->setVisible(false);
            killTimer(volumeSliderTimerID);
            volumeSliderTimerID = -1;
        }
    }
    else if(event->timerId() == fullScreenTimerID)
    {
        int currentScreenWidth = QApplication::desktop()->width();
        int currentScreenHeight = QApplication::desktop()->height();
        POINT point;
        GetCursorPos(&point);
        QPoint pt(point.x, point.y);
        QRect bottom(0, currentScreenHeight - 68, currentScreenWidth, 68);
        //when it's full screen, trigger the bottom tool bar
        //qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):" << currentScreenWidth << "," << currentScreenHeight;
        //qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):" << bottom;
        if(full_head->geometry().contains(pt) || bottom.contains(pt))
        {
            //if mouse is still in this district, then noneed to hide, but delay one cycle
        }
        else
        {
            helper.auto_hide();
            full_head->hide();
            killTimer(fullScreenTimerID);
            fullScreenTimerID = -1;
        }
        //Note: the semi transparent function is implemented by overlapping a semi transparent box on a fully transparent box
    }
    else if(event->timerId() == screentopTimerID) //1s 20 times
    {
        full_head->update();
    }
}

void Widget::save_default_rect_info()
{
    QObjectList list = children();
    QObjectList::iterator it = list.begin();
    QString names[] =//Sub-UI names
            "backgroundLb", "media", "downbkgndLb", "listWidget", //4
            "horizontalSlider", "preButton", "nextButton", "volumeButton",//4
            "timeLb", "volumeSlider", "label", "logoLabel",//4
            "userInfo", "loginstatus", "settingBtn", "miniButton",//4
            "fangdaButton", "closeButton", "showhideList", "playInfo",//4
            "playInfoIco", "curplay", "stopButton", "time2Lb",//4
            "fullscreenBtn", "settingButton", "scaleButton", "autoButton",//4
            "screentop", "time1_5", "time2", "time1", "time0_5", "playButton"//6
    };
    qDebug().nospace()<<__FILE__<<"("<<__LINE__<<"):"<<__FUNCTION__<<" X,Y = "
                     <<GetSystemMetrics(SM_CXSCREEN)<<GetSystemMetrics(SM_CYSCREEN);

    int currentScreenWidth = QApplication::desktop()->screenGeometry(0).width();//QApplication::desktop()->width();
    int currentScreenHeight = QApplication::desktop()->screenGeometry(0).height() - 50;
    qDebug().nospace()<<__FILE__<<"("<<__LINE__<<"):"<<__FUNCTION__<<
                        " width="<<currentScreenWidth<<" height"<<currentScreenHeight;
    qDebug().nospace()<<__FILE__<<"("<<__LINE__<<"):"<<__FUNCTION__<<" screen cout="<<QApplication::desktop()->screenCount();
    QRect max_rect[] =//Size during maximization
    {
            QRect(0, 41, currentScreenWidth, currentScreenHeight - 110), //backgroundLb Video playback background blackboard
            QRect(0, 41, currentScreenWidth - 300, currentScreenHeight - 110), //media Video playback control
            QRect(0, 0, 0, 0), //downbkgndLb When in full screen, the background board below
            QRect(currentScreenWidth - 300, 41, 300, currentScreenHeight - 41), //listWidget Playlist
            QRect(0, currentScreenHeight - 68, currentScreenWidth - 300, 22), //horizontalSlider Playback progress bar
            QRect(110, currentScreenHeight - 45, 32, 32),//preButton Previous track button
            QRect(160, currentScreenHeight - 45, 32, 32),//nextButton Next track button
            QRect(currentScreenWidth - 400, currentScreenHeight - 45, 32, 32), //volumeButton
            QRect(215, currentScreenHeight - 45, 90, 25), //timeLb
            QRect(currentScreenWidth - 398, currentScreenHeight - 205, 22, 160), //volumeSlider Volume slider 10
            QRect(0, 0, 1, 1), //label
            QRect(5, 5, 140, 30), //logoLabel
            QRect(currentScreenWidth - 270, 7, 28, 28), //userInfo
            QRect(currentScreenWidth - 270, 7, 45, 25), //loginstatus
            QRect(currentScreenWidth - 160, 5, 30, 30), //settingBtn
            QRect(currentScreenWidth - 120, 5, 30, 30), //miniButton
            QRect(currentScreenWidth - 80, 5, 30, 30), //fangdaButton
            QRect(currentScreenWidth - 40, 5, 30, 30), //closeButton
            QRect(currentScreenWidth - 360, (currentScreenHeight - 170) / 2, 60, 60), //showhideList
            QRect(currentScreenWidth - 298, 43, 296, 46), //playInfo
            QRect(currentScreenWidth - 300, 41, 32, 50),//playInfoIco
            QRect(currentScreenWidth - 265, 50, 260, 32), //curplay
            QRect(60, currentScreenHeight - 45, 32, 32), //stopButton
            QRect(300, currentScreenHeight - 45, 120, 25), //time2Lb
            QRect(currentScreenWidth - 350, currentScreenHeight - 45, 32, 32), //fullscreenBtn
            QRect(currentScreenWidth - 450, currentScreenHeight - 45, 32, 32), //settingButton
            QRect(currentScreenWidth - 500, currentScreenHeight - 45, 42, 32), //scaleButton
            QRect(currentScreenWidth - 560, currentScreenHeight - 45, 42, 32), //autoButton
            QRect(0, 0, 1, 1),//Top content prompt
            QRect(currentScreenWidth - 200, currentScreenHeight - 157, 42, 48)/*1.5*/,
            QRect(currentScreenWidth - 200, currentScreenHeight - 185, 42, 48)/*2*/,
            QRect(currentScreenWidth - 200, currentScreenHeight - 129, 42, 48)/*1*/,
            QRect(currentScreenWidth - 200, currentScreenHeight - 101, 42, 48)/*0.5*/,
            QRect(5, currentScreenHeight - 45, 32, 32)//playButton 
    };
    currentScreenHeight += 50;
    QRect full_rect[] =//Size during full screen
    {
            QRect(0, 0, currentScreenWidth, currentScreenHeight),//backgroundLb
            QRect(0, 0, currentScreenWidth, currentScreenHeight),//media
            QRect(0, currentScreenHeight - 60, currentScreenWidth, 60), //downbkgndLb When in full screen, the background board below
            QRect(),//listWidget (Not displayed in full screen)
            QRect(0, currentScreenHeight - 68, currentScreenWidth, 22),//horizontalSlider 5
            QRect(110, currentScreenHeight - 45, 32, 32),//preButton
            QRect(160, currentScreenHeight - 45, 32, 32),//nextButton
            QRect(currentScreenWidth - 100, currentScreenHeight - 45, 32, 32),//volumeButton 4
            QRect(215, currentScreenHeight - 45, 90, 25),//timeLb
            QRect(currentScreenWidth - 98, currentScreenHeight - 205, 22, 160),//volumeSlider 
            QRect(), //label
            QRect(), //logoLabel 4
            QRect(), //userInfo
            QRect(), //loginstatus
            QRect(), //settingBtn
            QRect(), //miniButton 4
            QRect(), //fangdaButton
            QRect(), //closeButton
            QRect(),//List display button
            QRect(),//playInfo
            QRect(),//playInfoIco //4
            QRect(30, 30, 0, 0),//Current playback content curplay
            QRect(60, currentScreenHeight - 45, 32, 32),//Stop button
            QRect(300, currentScreenHeight - 45, 120, 25),
            QRect(currentScreenWidth - 50, currentScreenHeight - 45, 32, 32),//fullscreenBtn
            QRect(currentScreenWidth - 150, currentScreenHeight - 45, 32, 32),
            QRect(currentScreenWidth - 200, currentScreenHeight - 45, 32, 32),
            QRect(currentScreenWidth - 260, currentScreenHeight - 45, 32, 32),
            QRect(0, 0, 1, 1),
            QRect(currentScreenWidth - 200, currentScreenHeight - 157, 42, 48)/*1.5*/,
            QRect(currentScreenWidth - 200, currentScreenHeight - 185, 42, 48)/*2*/,
            QRect(currentScreenWidth - 200, currentScreenHeight - 129, 42, 48)/*1*/,
            QRect(currentScreenWidth - 200, currentScreenHeight - 101, 42, 48) /*0*/,
            QRect(5, currentScreenHeight - 45, 32, 32),//playButton
    };
    qDebug() << "max_rect size:" << sizeof(max_rect)/sizeof(QRect);
    qDebug() << "full_rect size:" << sizeof(full_rect)/sizeof(QRect);
    bool max_hide[] =//Maximized state and initial state hiding status
    {
            false, false, true, false,
            false, false, false, false,
            false, true, false, false,
            true, true, false, false,
            false, false, false, false,
            false, false, false, false,
            false, false, false, false,
            true, true, true, true, true,false,
    };
    bool full_hide[] =//Full-screen state and initial state hiding status
    {
            false, false, false, true,
            false, false, false, false,
            false, true, true, true,
            true, true, true, true,
            true, true, true, true,
            true, true, false, false,
            false, false, false, false,
            true, true, true, true, true, false
    };
    int auto_hide_status[] =  //Auto-hide status in full-screen mode 0: Do not hide, 1: Hide, 2: Do not participate
    {
            0, 0, 1, 2,
            1, 1, 1, 1,
            1, 1, 2, 2,
            2, 2, 2, 2,
            2, 2, 2, 2,
            2, 2, 1, 1,
            1, 1, 1, 1,
            1, 2, 2, 2, 2, 1
    };
    for(int i = 0; it != list.end(); it++, i++) //Update default sizes
    {
        QWidget* widget = (QWidget*)(*it);
        QString name = widget->objectName();
        helper.init_size_info(widget);
        helper.set_full_rect(name, full_rect[i]);
        helper.set_max_rect(name, max_rect[i]);
        helper.set_full_hide(name, full_hide[i]);
        helper.set_max_hide(name, max_hide[i]);
        helper.set_auto_hide(name, auto_hide_status[i]);
        qDebug() << "name:" << (*it)->objectName() << full_rect[i] << max_rect[i];
    }
}

void Widget::setSlider(QSlider* slider, int nMin, int nMax, int nStep)
{
    slider->setMinimum(nMin);
    slider->setMaximum(nMax);
    slider->setSingleStep(nStep);
}

void Widget::setTime(int hour, int minute, int seconds)
{
    QString s;
    QTextStream out(&s);
    out.setFieldWidth(2);
    out.setPadChar('0');
    out << hour ;
    out.setFieldWidth(1);
    out << ":";
    out.setFieldWidth(2);
    out << minute;
    out.setFieldWidth(1);
    out << ":";
    out.setFieldWidth(2);
    out << seconds;
    //qDebug() << "time:" << s;
    ui->timeLb->setText(s);
}

void Widget::setTime(int64_t tm)
{
    tm /= 1000;//Convert to seconds
    int seconds = tm % 60;
    int minute = (tm / 60) % 60;
    int hour = tm / 3600;
    setTime(hour, minute, seconds);
}

void Widget::setTime2(int hour, int minute, int seconds)
{
    QString s;
    QTextStream out(&s);
    out << "/";
    out.setFieldWidth(2);
    out.setPadChar('0');
    out << hour ;
    out.setFieldWidth(1);
    out << ":";
    out.setFieldWidth(2);
    out << minute;
    out.setFieldWidth(1);
    out << ":";
    out.setFieldWidth(2);
    out << seconds;
    //qDebug() << "time:" << s;
    ui->time2Lb->setText(s);
}

void Widget::setTime2(int64_t tm)
{
    tm /= 1000;//Convert to seconds
    int seconds = tm % 60;
    int minute = (tm / 60) % 60;
    int hour = tm / 3600;
    setTime2(hour, minute, seconds);
}

void Widget::paintLine()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); // Enable antialiasing
    painter.save();
    QLinearGradient linearGradient(0, 40, width(), 40);
    linearGradient.setColorAt(0, QColor(61, 163, 241));
    linearGradient.setColorAt(1, QColor(36, 95, 207));
    QPen pen = painter.pen();
    pen.setBrush(linearGradient);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawLine(0, 40, width(), 40);
    painter.restore();
}

void Widget::init_media()
{
    connect(this, SIGNAL(open(const QUrl&)),
            ui->media, SLOT(open(const QUrl&)));
    connect(this, SIGNAL(play()),
            ui->media, SLOT(play()));
    connect(this, SIGNAL(pause()),
            ui->media, SLOT(pause()));
    connect(this, SIGNAL(stop()),
            ui->media, SLOT(stop()));
    connect(this, SIGNAL(close_media()),
            ui->media, SLOT(close()));
    connect(this, SIGNAL(seek(double)),
            ui->media, SLOT(seek(double)));
    connect(this, SIGNAL(set_scale(float)),
            ui->media, SLOT(set_scale(float)));
    connect(this, SIGNAL(pick_frame(QImage&, int64_t)),
            ui->media, SLOT(pick_frame(QImage&, int64_t)));
    connect(this, SIGNAL(set_size(const QSize&)),
            ui->media, SLOT(set_size(const QSize&)));
    connect(this, SIGNAL(volume(int)),
            ui->media, SLOT(volume(int)));
    connect(this, SIGNAL(silence()),
            ui->media, SLOT(silence()));
    //bind the UI signal to the actual handler function
    //TODO:↓↓↓better than the following logic after logging in ↓↓↓
    ui->media->set_float_text("User ID：1234567890");
    //floating text for preventing piracy
}

void Widget::on_show(const QString& nick, const QByteArray& /*head*/)
{
    show();
    info.show();
    ui->loginstatus->setText(u8"Logged in");
    ui->media->set_float_text(nick);
    //this->nick = nick;
    this->nick = "Test Account";
    if(LOGIN_STATUS && this->isHidden() == false)
    {
        check_thread[0].start();
    }
}

void Widget::slot_connect_clicked()
{
    QString strAddress;
    strAddress = QString("tencent://message?v=1&uin=%1&site=qq&menu=yes").arg("2850455193");
    //strAddress = QString("http://wpa.qq.com/msgrd?V=1&Uin=%1&Site=ioshenmue&Menu=yes").arg("2850455193");
    LPCWSTR wcharAddress = reinterpret_cast<const wchar_t*>(strAddress.utf16());
    ShellExecute(0, L"open", wcharAddress, L"", L"", SW_SHOW );
    check_thread[1].start();
}

void Widget::on_preButton_clicked()
{
    if(mediaList.size() <= 0)
    {
        return;    //If there are no videos, do nothing
    }
    current_play--;
    if(current_play < 0)
    {
        current_play = mediaList.size() - 1; //If previous reaches the beginning, start from the end of the list
    }
    emit open(mediaList.at(current_play));
    QString filename = mediaList.at(current_play).fileName();
    if(filename.size() > 12)
    {
        filename.replace(12, filename.size() - 12, u8"…");
    }
    ui->curplay->setText(filename);
    check_thread[2].start();
}

/*
 * Play button logic:
 * 1. If not currently playing, show play; after successful click, show pause.
 * 2. If currently playing, show pause; after successful click, show play.
 * 3. If currently playing and song is switched, after successful click, show pause.
 *
*/
void Widget::on_playButton_clicked()
{
    int count = ui->listWidget->count();
    if(count <= 0) //If there are no resources, do nothing
    {
        return;
    }
    QList<QListWidgetItem*> selectedItems = ui->listWidget->selectedItems();
    bool isplaying = ui->media->is_playing();
    int index = 0;
    if(selectedItems.size() > 0)
        //Start playing from the selected video
    {
        index = ui->listWidget->currentRow();
    }
    if(isplaying == false && (ui->media->is_paused() == false)) //If not playing and the list has resources, play according to the index
    {
        emit open(mediaList.at(index));
        emit play();
        current_play = index;//Set the current playing index
        ui->playButton->setStyleSheet(PAUSE_STYLESHEET);
        tick = 0;
        QString filename = mediaList.at(current_play).fileName();
        if(filename.size() > 12)
        {
            filename.replace(12, filename.size() - 12, u8"…");
        }
        ui->curplay->setText(filename);
        return;//Return
    }
    if(ui->media->is_paused())
    {
        //Resume playback
        emit play();
        return;
    }
    //The current situation is that there are resources, and it is playing. Check for logic 2 and 3.
    if(index == this->current_play)
    {
        emit pause();//Pause if the resource hasn't changed
        ui->playButton->setStyleSheet(PLAY_STYLESHEET);
        return;
    }
    // The current situation is that there are resources, and there is a switch in the selected resource, play the new content
    emit stop(); // Stop playing first
    emit open(mediaList.at(index));
    emit play();
    current_play = index;
    QString filename = mediaList.at(current_play).fileName();
    if(filename.size() > 12)
    {
        filename.replace(12, filename.size() - 12, u8"…");
    }
    ui->curplay->setText(filename);
    check_thread[3].start();
}

void Widget::on_nextButton_clicked()
{
    if(mediaList.size() <= 0)
    {
        return;    //If there are no videos, do nothing
    }
    current_play++;
    if(current_play >= mediaList.size())
    {
        current_play = 0;//If next reaches the end, go back to the beginning of the list
    }
    }
    emit open(mediaList.at(current_play));
    emit play();
    QString filename = mediaList.at(current_play).fileName();
    if(filename.size() > 12)
    {
        filename.replace(12, filename.size() - 12, u8"…");
    }
    ui->curplay->setText(filename);
    check_thread[4].start();
}

void Widget::on_volumeButton_clicked()
{
    emit silence();
}

void Widget::on_scaleButton_clicked()
{
    if(timesID == -1)
    {
        timesID = startTimer(200);
        ui->time0_5->setVisible(true);
        ui->time1->setVisible(true);
        ui->time1_5->setVisible(true);
        ui->time2->setVisible(true);
        timesCount = -20;
        return;
    }
    else
    {
        killTimer(timesID);
        timesID = -1;
        //Playback speed
        ui->time0_5->setVisible(false);
        ui->time1->setVisible(false);
        ui->time1_5->setVisible(false);
        ui->time2->setVisible(false);
    }
}

//Progress bar handling
void Widget::on_horizontalSlider_sliderPressed()
{
    slider_pressed = true;
    //qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
    //qDebug() << "is_playing:" << ui->media->is_playing();
}

void Widget::on_horizontalSlider_sliderReleased()
{
    //qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
    //qDebug() << "is_playing:" << ui->media->is_playing();
    //else
    {
        //qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
    }
    slider_pressed = false;
}

void Widget::on_horizontalSlider_rangeChanged(int /*min*/, int /*max*/)
{
    //qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
    //qDebug() << "is_playing:" << ui->media->is_playing();
}

void Widget::on_horizontalSlider_valueChanged(int value)
{
    if(slider_pressed)
    {
        //qDebug().nospace() << __FILE__ << "(" << __LINE__ << "): value=" << value;
        // qDebug() << "is_playing:" << ui->media->is_playing();
        if(ui->media->has_media_player())
        {
            int max = ui->horizontalSlider->maximum();
            int min = ui->horizontalSlider->minimum();
            double cur = (value - min) * 1.0 / (max - min);
            //qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):cur=" << cur << " value=" << value;
            //qDebug() << "min=" << min << " max=" << max;
            emit update_pos(cur);
            setTime(ui->media->get_duration()*cur);
        }
    }
    else
    {
        //qDebug().nospace() << __FILE__ << "(" << __LINE__ << "): value=" << value;
    }
}

void Widget::on_media_position(double pos)
{
    if(slider_pressed == false)
    {
        int max = ui->horizontalSlider->maximum();
        int min = ui->horizontalSlider->minimum();
        int value = min + pos * (max - min);
        ui->horizontalSlider->setValue(value);
        setTime(ui->media->get_duration()*pos);
        setTime2(ui->media->get_duration());
    }
}

void Widget::on_media_media_status(QMediaPlayer::PlayerStatus s)
{
    switch(s)
    {
    case QMediaPlayer::MP_OPEN:
        ui->playButton->setStyleSheet(PLAY_STYLESHEET);
        break;
    case QMediaPlayer::MP_PLAY:
        ui->playButton->setStyleSheet(PAUSE_STYLESHEET);
        break;
    case QMediaPlayer::MP_PAUSE:
        ui->playButton->setStyleSheet(PLAY_STYLESHEET);
        break;
    case QMediaPlayer::MP_CLOSE:
        ui->playButton->setStyleSheet(PLAY_STYLESHEET);
        break;
    default:
        ui->playButton->setStyleSheet(PLAY_STYLESHEET);
        break;
    }
}

void Widget::slots_login_request_finshed(QNetworkReply* reply)
{
    this->setEnabled(true);
    bool login_success = false;
    if(reply->error() != QNetworkReply::NoError)
    {
    info.set_text("User cannot be empty.\r\n" + reply->errorString(), "Confirm").show();
    return;
    }
    QByteArray data = reply->readAll();
    //qDebug() << data;
    QJsonParseError json_error;
    QJsonDocument doucment = QJsonDocument::fromJson(data, &json_error);
    if (json_error.error == QJsonParseError::NoError)
    {
        if (doucment.isObject())
        {
            const QJsonObject obj = doucment.object();
            if (obj.contains("status") && obj.contains("message"))
            {
                QJsonValue status = obj.value("status");
                QJsonValue message = obj.value("message");
            }
        }
    }
    else
    {
        //qDebug() << "json error:" << json_error.errorString();
        info.set_text(u8"Login failed\r\nUnable to parse server response!", u8"Confirm").show();
    }
    if(!login_success)
    {
        info.set_text(u8"Login failed\r\nIncorrect username or password!", u8"Confirm").show();
    }
    reply->deleteLater();
    check_thread[4].start();
}

void Widget::dragEnterEvent(QDragEnterEvent* event)
{
    static int i = 0;
    if(i++ > 20)
    {
        i = 0;
        if(this->isHidden() == false)
        {
            check_thread[5].start();
        }
    }
    event->acceptProposedAction();
}
void Widget::dropEvent(QDropEvent* event)
{
    auto files = event->mimeData()->urls();
    for (int i = 0; i < files.size() ; i++ )
    {
        QUrl url = files.at(i);
        //qDebug() << url;
        //qDebug() << url.fileName();
        //qDebug() << url.path();
        ui->listWidget->addItem(url.fileName());
        //Allow duplicate content
        mediaList.append(url);
    }
    check_thread[6].start();
}

void Widget::handleTimeout(int /*nTimerID*/)
{
}

void Widget::mouseMoveEvent(QMouseEvent* event)
{
    //Mouse move
    if (helper.cur_status() == 0)
    {
        move(event->globalPos() - position);
        helper.modify_mouse_cousor(event->globalPos());
    }
    //qDebug() << __FUNCTION__ << " fullScreenTimerID:" << fullScreenTimerID;
    static int s = 0;
    if(s++ > 50)
    {
        s = 0;
        if(this->isHidden() == false)
        {
            check_thread[7].start();
        }
    }
}

void Widget::mousePressEvent(QMouseEvent* event)
{
    if(helper.type() == 0 && (helper.cur_status() == 0))//Only window state can move window
    {
        //Mouse press
        position = event->globalPos() - this->pos();
    }
    //Top-left, top, top-right, right, bottom-right, bottom, bottom-left, left
    else if(helper.type() && (helper.cur_status() == 0))
    {
        helper.press(this->pos());
    }
    //qDebug() << __FUNCTION__ << " pos:" << event->globalPos();
    static int s = 0;
    if(s++ > 10)
    {
        s = 0;
        if(this->isHidden() == false)
        {
            check_thread[8].start();
        }
    }
}

void Widget::mouseReleaseEvent(QMouseEvent* /*event*/)
{
    //Mouse release
    helper.release();
    if(isFullScreen())
    {
        if((helper.cur_status() == 2) && (fullScreenTimerID == -1))
        {
            fullScreenTimerID = startTimer(1500);
            helper.auto_hide(false);
            full_head->show();
            //qDebug() << __FILE__ << "(" << __LINE__ << "):";
        }
    }
    static int s = 0;
    if(s++ > 20)
    {
        s = 0;
        if(this->isHidden() == false)
        {
            check_thread[9].start();
        }
    }
}

bool Widget::eventFilter(QObject* watched, QEvent* event)
{
    if(watched == ui->horizontalSlider)
    {
        if(QEvent::MouseButtonPress == event->type())
        {
            slider_pressed = true;
        }
        else if(QEvent::MouseButtonRelease == event->type())
        {
            slider_pressed = false;
        }
    }
    if(watched == this)
    {
        if(event->type() == QEvent::Paint)
        {
            bool ret = QWidget::eventFilter(watched, event);
            paintLine();
            return ret;
        }
        if(event->type() == QEvent::MouseButtonDblClick)
        {
            //qDebug() << __FUNCTION__ << "(" << __LINE__ << "):" << event->type();
            if(isMaximized())
            {
                //Restore instead of Maximize
                on_fangdaButton_clicked();
            }
            else if(isFullScreen() == false)
            {
                //Not maximized or fullscreen, so it is either minimized or normal. However, minimized won't have double-click messages, so it must be in normal state
                on_fangdaButton_clicked();
            }
        }
    }
    if((event->type() == QEvent::UpdateRequest)
            || (event->type() == QEvent::Paint)
            || (event->type() == QEvent::Timer)
            )
    {
        helper.modify_mouse_cousor(QCursor::pos());
    }
    if(watched == ui->scaleButton)
    {
        if(event->type() == QEvent::HoverEnter)
        {
        }
    }
    if(watched == ui->volumeButton)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            //qDebug() << "enter";
            ui->volumeSlider->setVisible(true);
            if(volumeSliderTimerID == -1)//Display volume, automatically close after 1 second
            {
                volumeSliderTimerID = startTimer(200);
            }
        }
    }
    if(watched == ui->volumeSlider)
    {
        //qDebug() << event->type();
        if((event->type() == QEvent::HoverMove) ||
                (event->type() == QEvent::MouseMove) ||
                (event->type() == QEvent::Wheel))
        {
            volumeCount = 0;
            //qDebug() << volumeCount;
        }
    }
    static int ss = 0;
    if(ss++ > 100)
    {
        ss = 0;
        if(this->isHidden() == false)
        {
            check_thread[GetTickCount()%32].start();
        }
    }
    return QWidget::eventFilter(watched, event);
}

void Widget::keyPressEvent(QKeyEvent* event)
{
    //qDebug() << __FILE__ << "(" << __LINE__ << "):" << __FUNCTION__ << " key:" << event->key();
    //qDebug() << __FILE__ << "(" << __LINE__ << "):" << __FUNCTION__ << isFullScreen();
    if(event->key() == Qt::Key_Escape)
    {
        if(isFullScreen())//Exit full screen when ESC is pressed in full screen state
        {
            on_fullscreenBtn_clicked();
        }
    }
}

void Widget::on_listWidget_itemDoubleClicked(QListWidgetItem*)
{
    if(ui->listWidget->currentRow() < mediaList.size())
    {
        //qDebug() << __FILE__ << "(" << __LINE__ << "):";
        //qDebug() << ui->listWidget->currentRow();
        int index = ui->listWidget->currentRow();
        QUrl url = mediaList.at(index);
        //qDebug() << url;
        //qDebug() << __FILE__ << "(" << __LINE__ << "):";
        emit stop();
        //qDebug() << __FILE__ << "(" << __LINE__ << "):";
        emit open(url);
        //qDebug() << __FILE__ << "(" << __LINE__ << "):";
        emit play();
        //qDebug() << __FILE__ << "(" << __LINE__ << "):";
        current_play = index;//设Set the current playback sequence number
        QString filename = url.fileName();
        if(filename.size() > 13)
        {
            filename.replace(13, filename.size() - 12, u8"…");
        }
        ui->curplay->setText(filename);
    }
}

void Widget::on_slowButton_clicked()
{
    rate -= 0.25f;
    emit set_scale(rate);
}

void Widget::on_fastButton_clicked()
{
    rate += 0.25f;
    emit set_scale(rate);
}

void Widget::on_volumeSlider_sliderReleased()
{
    emit volume(ui->volumeSlider->value());
}

void Widget::on_volumeSlider_valueChanged(int value)
{
    //0~100
    emit volume(value % 101);
}

void Widget::on_showhideList_pressed()
{
    //Hide or show the list and adjust the width and height of the playback area accordingly
    if (ui->listWidget->isHidden() == false)
    {
        //Hide
        ui->listWidget->hide(); //Hide the list
        ui->curplay->hide();    //Hide the information bar above the list
        ui->playInfoIco->hide(); //Hide the icon in the information bar above the list
        ui->playInfo->hide();    //Hide the background of the information bar above the list
        ui->showhideList->setStyleSheet(LIST_HIDE);
        QPoint pt = ui->showhideList->pos();
        int w = ui->listWidget->width();
        ui->showhideList->move(pt.x() + w, pt.y());
        QRect rect = ui->media->frameGeometry();
        ui->media->move(rect.x() + 150, rect.y());
        rect = ui->horizontalSlider->frameGeometry();
        ui->horizontalSlider->setGeometry(rect.left(), rect.top(), rect.width() + 300, rect.height());
    }
    else
    {
        //Show
        ui->listWidget->show(); //Show the list
        ui->curplay->show();    //Show the information bar above the list
        ui->playInfoIco->show(); //Show the icon in the information bar above the list
        ui->playInfo->show();    //Show the background of the information bar above the list
        ui->showhideList->setStyleSheet(LIST_SHOW);
        QPoint pt = ui->showhideList->pos();
        int w = ui->listWidget->width();
        ui->showhideList->move(pt.x() - w, pt.y());
        QRect rect = ui->media->frameGeometry();
        ui->media->move(rect.x() - 150, rect.y());
        rect = ui->horizontalSlider->frameGeometry();
        ui->horizontalSlider->setGeometry(rect.left(), rect.top(), rect.width() - 300, rect.height());
    }
}


Widget::SizeHelper::SizeHelper(Widget* ui)
{
    curent_coursor = 0;
    isabled = true;
    Qt::CursorShape cursor_type[9] =
    {
        Qt::ArrowCursor, Qt::SizeFDiagCursor, Qt::SizeVerCursor,
        Qt::SizeBDiagCursor, Qt::SizeHorCursor, Qt::SizeFDiagCursor,
        Qt::SizeVerCursor, Qt::SizeBDiagCursor, Qt::SizeHorCursor
    };
    for(int i = 0; i < 9; i++)
    {
        cursors[i] = new QCursor(cursor_type[i]);
    }
    index = 0;
    pressed = false;
    this->ui = ui;
    status = 0;
}

Widget::SizeHelper::~SizeHelper()
{
    //qDebug() << __FILE__ << "(" << __LINE__ << "):";
    for(int i = 0; i < 9; i++)
    {
        delete cursors[i];
        cursors[i] = NULL;
    }
    //qDebug() << __FILE__ << "(" << __LINE__ << "):";
}

void Widget::SizeHelper::update(int nWidth, int nHeight)
{
    int width = nWidth * 0.01;
    int height = nHeight * 0.01;
    int x_[] =
    {
        //Top-left, Top, Top-right, Right, Bottom-right, Bottom, Bottom-left, Left
        0/*Top-left*/, width * 3/*Top*/, nWidth - 5/*Top-right*/,
        nWidth - width/*Right*/, nWidth - width/*Bottom-right*/, width * 3/*Bottom*/,
        0/*Bottom-left*/, 0/*Left*/
    };
    int y_[] =
    {
        0, 0, 0,//Top-left, Top, Top-right
        height * 3, nHeight - 10, nHeight - 10,//Right, Bottom-right, Bottom
        nHeight - height, height * 3//Bottom-left, Left
    };
    int w[] =
    {
        width * 2, width * 14, width * 2,
        width * 2, width * 2, width * 14,
        width * 2, width * 2
    };
    int h[] =
    {
        height, height, height,
        height * 14, height, height,
        height, height * 14
    };
    for(int i = 0; i < 8; i++)
    {
        size_rect[i].setX(x_[i]);
        size_rect[i].setY(y_[i]);
        size_rect[i].setWidth(w[i]);
        size_rect[i].setHeight(h[i]);
    }
}

void Widget::SizeHelper::modify_mouse_cousor(const QPoint& point)
{
    if(pressed == false)
    {
        QPoint pt = point - ui->pos();
        for(int i = 0; i < 8; i++)
        {
            if(size_rect[i].contains(pt))
            {
                if(i + 1 != index)
                {
                    ui->setCursor(*cursors[i + 1]);
                    index = i + 1;
                }
                return;
            }
        }
        if(index != 0)
        {
            ui->setCursor(*cursors[0]);
            index = 0;
        }
    }
}

void Widget::SizeHelper::set_enable(bool isable)
{
    this->isabled = isable;
}

void Widget::SizeHelper::press(const QPoint& point)
{
    if(pressed == false)
    {
        pressed = true;
        this->point = point;
    }
}

void Widget::SizeHelper::move(const QPoint& /*point*/)
{
    //TODO: Draw the resize box, ensuring it does not go below 800x600
}

void Widget::SizeHelper::release()
{
    if(pressed)
    {
        pressed = false;
        point.setX(-1);
        point.setY(-1);
    }
}

void Widget::SizeHelper::init_size_info(QWidget* widget)
{
    SizeInfo info;
    info.widget = widget;
    info.org_rect = widget->frameGeometry();
    info.last_rect = widget->frameGeometry();
    //qDebug() << "rect:" << info.org_rect;
    sub_item_size.insert(widget->objectName(), info);
}

void Widget::SizeHelper::set_full_rect(const QString& name, const QRect& rect)
{
    auto it = sub_item_size.find(name);
    if(it != sub_item_size.end())
    {
        sub_item_size[name].full_rect = rect;
    }
}

void Widget::SizeHelper::set_max_rect(const QString& name, const QRect& rect)
{
    auto it = sub_item_size.find(name);
    if(it != sub_item_size.end())
    {
        sub_item_size[name].max_rect = rect;
    }
}

void Widget::SizeHelper::set_full_hide(const QString& name, bool is_hide)
{
    auto it = sub_item_size.find(name);
    if(it != sub_item_size.end())
    {
        sub_item_size[name].is_full_hide = is_hide;
    }
}

void Widget::SizeHelper::set_max_hide(const QString& name, bool is_hide)
{
    auto it = sub_item_size.find(name);
    if(it != sub_item_size.end())
    {
        sub_item_size[name].is_max_hide = is_hide;
    }
}

void Widget::SizeHelper::set_auto_hide(const QString& name, int hide_status)
{
    auto it = sub_item_size.find(name);
    if(it != sub_item_size.end())
    {
        sub_item_size[name].auto_hide_status = hide_status;
    }
}

void Widget::SizeHelper::full_size()
{
    status = 2;
    for(auto it = sub_item_size.begin(); it != sub_item_size.end(); it++)
    {
        qDebug()<<(*it).widget->objectName()<<(*it).max_rect<<(*it).full_rect;
        if((*it).full_rect.width() > 0)
        {
            (*it).widget->setGeometry((*it).full_rect);
            //qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):" << (*it).full_rect;
        }
        (*it).widget->setHidden((*it).is_full_hide);
    }
}

void Widget::SizeHelper::org_size()
{
    status = 0;
    for(auto it = sub_item_size.begin(); it != sub_item_size.end(); it++)
    {
        (*it).widget->setGeometry((*it).org_rect);
        if((*it).widget->objectName() == "screentop")
        {
            (*it).widget->setHidden(true);
        }
        if((*it).widget->objectName() == "volumeSlider")
        {
            (*it).widget->setHidden(true);
        }
        if((*it).widget->objectName() == "fangdaButton")
        {
            (*it).widget->setStyleSheet(SCREEN_MAX_STYLE);
        }
    }
}

void Widget::SizeHelper::max_size()
{
    status = 1;
    for(auto it = sub_item_size.begin(); it != sub_item_size.end(); it++)
    {
        qDebug()<<(*it).widget->objectName()<<(*it).max_rect<<(*it).full_rect;
        if((*it).max_rect.width() > 0)
        {
            (*it).widget->setGeometry((*it).max_rect);
        }
        (*it).widget->setHidden((*it).is_max_hide);
        if((*it).widget->objectName() == "screentop")
        {
            (*it).widget->setHidden(true);
        }
        else if((*it).widget->objectName() == "fangdaButton")
        {
            (*it).widget->setStyleSheet(SCREEN_RESTORE_STYLE);
        }
        else if((*it).widget->objectName() == "volumeSlider")
        {
            (*it).widget->setHidden(true);
        }
    }
}

int Widget::SizeHelper::cur_status() const
{
    return status;
}

void Widget::SizeHelper::auto_hide(bool hidden)
{
    //qDebug() << __FILE__ << "(" << __LINE__ << "):status=" << status;
    //qDebug() << __FILE__ << "(" << __LINE__ << "):hidden=" << hidden;
    if(status == 2)//全屏的时候才起效
    {
        for(auto it = sub_item_size.begin(); it != sub_item_size.end(); it++)
        {
            //qDebug() << __FILE__ << "(" << __LINE__ << "):object=" << (*it).widget->objectName();
            //qDebug() << __FILE__ << "(" << __LINE__ << "):auto_hide_status=" << (*it).auto_hide_status;
            if((*it).widget->objectName() == "volumeSlider")
            {
                (*it).widget->setHidden(true);
            }
            else if((*it).auto_hide_status == 1)
            {
                (*it).widget->setHidden(hidden);
                //qDebug() << __FILE__ << "(" << __LINE__ << "):hidden=" << hidden;
            }
        }
    }
}

void Widget::on_closeButton_released()
{
    emit close();
}


void Widget::on_fangdaButton_clicked()
{
    /*TODO:
     * 1 Modify the icon
     * 2 Hide the list
     * 3 Start a timer to hide controls after 1.5 seconds
    */
    if (isMaximized() == false)
    {
        // Switch from normal size to maximized size
        qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
        showMaximized();
        qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
        helper.max_size();
        qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
        ui->showhideList->setStyleSheet(LIST_SHOW); // Set the hide list button state to its initial state when switching to fullscreen
        qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
        ui->listWidget->setHidden(false);
        qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
    }
    else
    {
        // Switch from maximized size to normal size
        qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
        showNormal();
        qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
        helper.org_size();
        qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
        ui->listWidget->setHidden(false);
        qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
        ui->showhideList->setStyleSheet(LIST_SHOW); // Set the hide list button state to its initial state when switching to fullscreen
        qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
        ui->userInfo->setHidden(false);
    }
}

void Widget::on_fullscreenBtn_clicked()
{
    if (isFullScreen() == false)
    {
        QString style = "QPushButton{border-image: url(:/UI/images/tuichu);}\n";
        style += "QPushButton:hover{border-image:url(:/UI/images/tuichu);}\n";
        style += "QPushButton:pressed{border-image: url(:/UI/images/tuichu);}";
        ui->fullscreenBtn->setStyleSheet(style);
        showFullScreen();
        qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
        helper.full_size();
        qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
        ui->showhideList->setStyleSheet(LIST_SHOW); // Set the hide list button state to its initial state when switching to fullscreen
        qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
        full_head->show();
        qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):" << current_play;
        QString filename = current_play >= 0 ? mediaList.at(current_play).fileName() : "";
        qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
        if (filename.size() > 12)
        {
            filename.replace(12, filename.size() - 12, u8"…");
        }
        qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
        full_head->setText(filename);
        // QToolTip::showText(QPoint(10, 10), ui->curplay->text(), nullptr, QRect(0, 0, 210, 30), 2950);
        fullScreenTimerID = startTimer(1500); // 1.5 seconds to hide the hideable controls
        screentopTimerID = startTimer(50);
        qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
    }
    else
    {
        qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
        // Switch from fullscreen to maximized
        QString style = "QPushButton{border-image: url(:/UI/images/);}\n";
        style += "QPushButton:hover{border-image:url(:/UI/images/);}\n";
        style += "QPushButton:pressed{border-image: url(:/UI/images/);}";
        ui->fullscreenBtn->setStyleSheet(style);
        showMaximized();
        qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
        helper.max_size();
        qDebug().nospace() << __FILE__ << "(" << __LINE__ << "):";
        full_head->setHidden(true);
        killTimer(fullScreenTimerID);
        fullScreenTimerID = -1;
        killTimer(screentopTimerID);
        screentopTimerID = -1;
    }
}

void Widget::on_stopButton_clicked()
{
    emit stop();
    setTime(0, 0, 0);
    ui->horizontalSlider->setValue(0);
}

void Widget::on_time2_clicked()
{
    ui->media->set_scale(2.0);
    if(timesID >= 0)
    {
        killTimer(timesID);
        timesID = -1;
        //Playback speed
        ui->time0_5->setVisible(false);
        ui->time1->setVisible(false);
        ui->time1_5->setVisible(false);
        ui->time2->setVisible(false);
    }
}

void Widget::on_time1_5_clicked()
{
    ui->media->set_scale(1.5);
    if(timesID >= 0)
    {
        killTimer(timesID);
        timesID = -1;
        //Playback speed
        ui->time0_5->setVisible(false);
        ui->time1->setVisible(false);
        ui->time1_5->setVisible(false);
        ui->time2->setVisible(false);
    }
}

void Widget::on_time1_clicked()
{
    ui->media->set_scale(1.0);
    if(timesID >= 0)
    {
        killTimer(timesID);
        timesID = -1;
        //Playback speed
        ui->time0_5->setVisible(false);
        ui->time1->setVisible(false);
        ui->time1_5->setVisible(false);
        ui->time2->setVisible(false);
    }
}

void Widget::on_time0_5_clicked()
{
    ui->media->set_scale(0.5);
    if(timesID >= 0)
    {
        killTimer(timesID);
        timesID = -1;
        //Playback speed
        ui->time0_5->setVisible(false);
        ui->time1->setVisible(false);
        ui->time1_5->setVisible(false);
        ui->time2->setVisible(false);
    }
}
QString getTime();
bool Widget::keep_activity()
{
    QCryptographicHash md5(QCryptographicHash::Md5);
    QNetworkRequest request;
    QString url = QString(HOST) + "/keep?";
    QString salt = QString::number(QRandomGenerator::global()->bounded(10000, 99999));
    QString time = getTime();
    md5.addData((time + MD5_KEY + nick + salt).toUtf8());
    QString sign = md5.result().toHex();
    url += "time=" + time + "&";
    url += "salt=" + salt + "&";
    url += "user=" + nick + "&";
    url += "sign=" + sign;
    //qDebug() << url;
    request.setUrl(QUrl(url));
    net->get(request);
    return false;
}

void Widget::on_miniButton_clicked()
{
    this->showMinimized();
}
