#include "widget.h"
#include "loginform.h"
#include <QApplication>
#include "vlchelper.h"
#include <QDebug>

int main(int argc, char* argv[])
{
    /*
    Program flow:
    from QApplication -> exec
    1. construct widget
    2. construct infoform
    3. hide widget
    4. create loginform
    5. RecordFIle.recordFile()
    6. loginform.show()
    7. loginform.connect()
    8. on_logoButton_release()
    9. QApplication.exec()
    10. loginForm.slots_lpgin_request_finished()
    11. loginForm.check_login()
    12. Widget.onshow()
    13. Widget.show()
    14. InfoForm.show()
    15. LoginForm.hide()
    16. RecordFile.config()
    17. RecordFile.save()
    */
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");
    //optimize for chinese code
    Widget w;
    LoginForm login;
    //widget and loginform is from QT, constructed from QApplication
    w.hide();
    login.show();
    //at first, show login form first
    login.connect(&login, SIGNAL(login(const QString&, const QByteArray&)),
                  &w, SLOT(on_show(const QString&, const QByteArray&)));
    qDebug() << __FILE__ << "(" << __LINE__ << "):";
    int ret = a.exec();
    qDebug() << __FILE__ << "(" << __LINE__ << "):";
    return ret;
}
