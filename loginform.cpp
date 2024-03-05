#include "loginform.h"
#include "ui_loginform.h"
#include "widget.h"
#include <time.h>
#include <QPixmap>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QCryptographicHash>
//y%dcunyd6x202lmfm9=-y7#bd-w(ro4*(9u$0i-3#$txwbkzg$
const char* MD5_KEY = "*&^%$#@b.v+h-b*g/h@n!h#n$d^ssx,.kl<kl";
//const char* HOST = "http://192.168.0.152:8000";
//const char* HOST = "http://code.kplayer.com:9530";
const char* HOST = "http://127.0.0.1:19527";
bool LOGIN_STATUS = false;

LoginForm::LoginForm(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::LoginForm),
    auto_login_id(-1)//定时器id
{
    record = new RecordFile("kplayer.dat");
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    //no header bar window
    ui->nameEdit->setPlaceholderText(u8"Username/Phone/Email"); //placeholder for account
    ui->nameEdit->setFrame(false);
    ui->nameEdit->installEventFilter(this);
    ui->pwdEdit->setPlaceholderText(u8"Enter Password");
    ui->pwdEdit->setFrame(false);
    ui->pwdEdit->setEchoMode(QLineEdit::Password);
    ui->pwdEdit->installEventFilter(this);
    ui->forget->installEventFilter(this);
    net = new QNetworkAccessManager(this);
    connect(net, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slots_login_request_finshed(QNetworkReply*)));
    //bind the network response and the handler function for login request finished
    info.setWindowFlag(Qt::FramelessWindowHint);
    info.setWindowModality(Qt::ApplicationModal);
    //set as application modal, allowing to drag around the screen
    QSize sz = size();
    info.move((sz.width() - info.width()) / 2, (sz.height() - info.height()) / 2);
    load_config();
}

LoginForm::~LoginForm()
{
    //qDebug() << __FILE__ << "(" << __LINE__ << "):";
    delete record;
    delete ui;
    delete net;
    //qDebug() << __FILE__ << "(" << __LINE__ << "):";
}

bool LoginForm::eventFilter(QObject* watched, QEvent* event)
{
    if(ui->pwdEdit == watched)
    {
        if(event->type() == QEvent::FocusIn) //control the behaviour of hovering
        {
            ui->pwdEdit->setStyleSheet("color: rgb(251, 251, 251);background-color: transparent;");
        }
        else if(event->type() == QEvent::FocusOut)
        {
            if(ui->pwdEdit->text().size() == 0) //see if there is input existing
            {
                ui->pwdEdit->setStyleSheet("color: rgb(71, 75, 94);background-color: transparent;");
            }
        }
    }
    else if(ui->nameEdit == watched)
    {
        if(event->type() == QEvent::FocusIn)
        {
            ui->nameEdit->setStyleSheet("color: rgb(251, 251, 251);background-color: transparent;");
        }
        else if(event->type() == QEvent::FocusOut)
        {
            if(ui->nameEdit->text().size() == 0)
            {
                ui->nameEdit->setStyleSheet("color: rgb(71, 75, 94);background-color: transparent;");
            }
        }
    }
    if((ui->forget == watched) && (event->type() == QEvent::MouseButtonPress))
    {
        //qDebug() << __FILE__ << "(" << __LINE__ << "):";
        QDesktopServices::openUrl(QUrl(QString(HOST) + "/forget"));
    }
    return QWidget::eventFilter(watched, event);
}

void LoginForm::timerEvent(QTimerEvent* event)
{
    if(event->timerId() == auto_login_id)
    {
        killTimer(auto_login_id);
        QJsonObject& root = record->config();
        QString user = root["user"].toString();
        QString pwd = root["password"].toString();
        check_login(user, pwd);
    }
}

void LoginForm::on_logoButton_released()
{
    if(ui->logoButton->text() == u8"Cancel Auto Login")
    {
        killTimer(auto_login_id);
        auto_login_id = -1;
        ui->logoButton->setText(u8"Login");
    }
    else
    {
        QString user = ui->nameEdit->text();
        //check validility of username
        if(user.size() == 0 || user == u8"Username/Phone/Email")
        {
            info.set_text(u8"User cannot be empty\r\nPlease enter a username", "Confirm").show();
            ui->nameEdit->setFocus();
            return;
        }
        //check validility of password
        QString pwd = ui->pwdEdit->text();
        if(pwd.size() == 0 || pwd == u8"Enter Password")
        {
            info.set_text(u8"Password cannot be empty\r\nPlease enter a password", "Confirm").show();
            ui->pwdEdit->setFocus();
            return;
        }
        check_login(user, pwd);
    }
}

void LoginForm::on_remberPwd_stateChanged(int state)
{
    //remember password changes
    //qDebug() << __FILE__ << "(" << __LINE__ << "):";
    record->config()["remember"] = state == Qt::Checked;
    if(state == Qt::Checked)
    {
        //qDebug() << __FILE__ << "(" << __LINE__ << "):";
    }
    else
    {
        //ui->autoLoginCheck->setChecked(false);//close remember password, then cancel auto login
        //qDebug() << __FILE__ << "(" << __LINE__ << "):";
    }
}

void LoginForm::slots_autoLoginCheck_stateChange(int state)
{
    //qDebug() << __FILE__ << "(" << __LINE__ << "):";
    record->config()["auto"] = state == Qt::Checked;
    if(state == Qt::Checked)
    {
        record->config()["remember"] = true;
        ui->remberPwd->setChecked(true);//auto login will enable remember password
        //ui->remberPwd->setCheckable(false);//prohibit modifying state
        //qDebug() << __FILE__ << "(" << __LINE__ << "):";
    }
    else
    {
        ui->remberPwd->setCheckable(true);//enable modifying state
        //qDebug() << __FILE__ << "(" << __LINE__ << "):";
    }
    //qDebug() << __FILE__ << "(" << __LINE__ << "):";
}

void LoginForm::slots_login_request_finshed(QNetworkReply* reply)
{
    this->setEnabled(true);
    bool login_success = false;
    if(reply->error() != QNetworkReply::NoError)
    {
        info.set_text(u8"登录发生错误\r\n" + reply->errorString(), u8"确认").show();
        return;
    }
    QByteArray data = reply->readAll();
    qDebug() << data;
    QJsonParseError json_error;
    QJsonDocument doucment = QJsonDocument::fromJson(data, &json_error);
    qDebug() << "json error = "<<json_error.error;
    if (json_error.error == QJsonParseError::NoError)
    {
        if (doucment.isObject())
        {
            const QJsonObject obj = doucment.object();
            if (obj.contains("status") && obj.contains("message"))
            {
                QJsonValue status = obj.value("status");
                QJsonValue message = obj.value("message");
                if(status.toInt(-1) == 0) //login successful
                {
                    //TODO:token needs to be saved and passed to widget for maintaining online status
                    LOGIN_STATUS = status.toInt(-1) == 0;
                    LOGIN_STATUS = status.toInt(-1) == 0;
                    emit login(record->config()["user"].toString(), QByteArray());
                    //this signal will be sent to main.cpp, binded with show()
                    hide();
                    login_success = true;
                    char tm[64] = "";
                    time_t t;
                    time(&t);
                    strftime(tm, sizeof(tm), "%Y-%m-%d %H:%M:%S", localtime(&t));
                    record->config()["date"] = QString(tm);//update login time
                    record->save();
                }
            }
        }
    }
    else
    {
        //qDebug() << "json error:" << json_error.errorString();
        info.set_text(u8"Login failed\r\nUnable to parse server response!", "Confirm").show();
    }
    if(!login_success)
    {
        info.set_text(u8"Login failed\r\nIncorrect username or password!", "Confirm").show();
    }
    reply->deleteLater();
}

QString getTime()
{
    time_t t = 0;
    time (&t);
    return QString::number(t);
}

bool LoginForm::check_login(const QString& user, const QString& pwd)
{
    QCryptographicHash md5(QCryptographicHash::Md5);
    QNetworkRequest request;
    QString url = QString(HOST) + "/login?"; //HOST = server ip
    QString salt = QString::number(QRandomGenerator::global()->bounded(10000, 99999));
    QString time = getTime();
    qDebug().nospace()<< __FILE__ << "(" << __LINE__ << "):" <<time + MD5_KEY + pwd + salt;
    md5.addData((time + MD5_KEY + pwd + salt).toUtf8());
    QString sign = md5.result().toHex();
    url += "time=" + time + "&";
    url += "salt=" + salt + "&"; //salt is a noise to prevent hacker
    url += "user=" + user + "&";
    url += "sign=" + sign;
    //Note: We can't send password as plain text to server, so we need to use md5_key + password + salt + time  to compute MD5_key
    //qDebug() << url;
    request.setUrl(QUrl(url));
    record->config()["password"] = ui->pwdEdit->text();
    record->config()["user"] = ui->nameEdit->text();
    this->setEnabled(false); //when checking login, disable the UI button
    net->get(request);
    return true;
    // following is the version without connecting to internet
    /*
    LOGIN_STATUS = true;
    emit login(record->config()["user"].toString(), QByteArray());
    hide();
    char tm[64] = "";
    time_t t;
    ::time(&t);
    strftime(tm, sizeof(tm), "%Y-%m-%d %H:%M:%S", localtime(&t));
    record->config()["date"] = QString(tm);//update login time
    record->save();
    return false;*/
}

void LoginForm::load_config()
{
    connect(ui->autoLoginCheck, SIGNAL(stateChanged(int)),
            this, SLOT(slots_autoLoginCheck_stateChange(int)));
    QJsonObject& root = record->config();
    //from either default config or manually set config
    ui->remberPwd->setChecked(root["remember"].toBool());
    ui->autoLoginCheck->setChecked(root["auto"].toBool());
    QString user = root["user"].toString();
    QString pwd = root["password"].toString();
    ui->nameEdit->setText(user);
    ui->pwdEdit->setText(pwd);
    //set values on the UI
    qDebug() << "auto:" << root["auto"].toBool();
    qDebug() << "remember:" << root["remember"].toBool();
    if(root["auto"].toBool()) //if autologin is turn on then check username and password
    {
        qDebug() << __FILE__ << "(" << __LINE__ << "):user=" << user;
        qDebug() << __FILE__ << "(" << __LINE__ << "):pwd=" << pwd;
        if(user.size() > 0 && pwd.size() > 0)
        {
            ui->logoButton->setText(u8"取消自动登录");
            auto_login_id = startTimer(3000);//allow 3 seconds for user to end login process
        }
    }
}

void LoginForm::mouseMoveEvent(QMouseEvent* event)
{
    move(event->globalPos() - position);
}

void LoginForm::mousePressEvent(QMouseEvent* event)
{
    position = event->globalPos() - this->pos(); //calculate the relative position, use vector addition to perform movement
}

void LoginForm::mouseReleaseEvent(QMouseEvent* /*event*/)
{
}
//for UI: note that the color for login button is linear gradient, specify the x1,y1,x2,y2 and the RGB we can achieve the effect