#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QDesktopServices>

#include "infoform.h"
#include "recordfile.h"


namespace Ui
{
    class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT
    friend class testVideoPlayer;
public:
    explicit LoginForm(QWidget* parent = nullptr);
    ~LoginForm();
    virtual bool eventFilter(QObject* watched, QEvent* event);
    virtual void timerEvent(QTimerEvent* event);
protected slots:
    void on_logoButton_released();
    //handler for pressing login button
    void on_remberPwd_stateChanged(int state);
    void slots_autoLoginCheck_stateChange(int state);
    void slots_login_request_finshed(QNetworkReply* reply);
signals:
    void login(const QString& nick, const QByteArray& head);
protected:
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
private:
    bool check_login(const QString& user, const QString& pwd);
    void load_config();
    //initialize and load config file
private:
    Ui::LoginForm* ui;
    QNetworkAccessManager* net;
    InfoForm info;
    RecordFile* record;
    int auto_login_id;
    QPoint position;
};

#endif // LOGINFORM_H
