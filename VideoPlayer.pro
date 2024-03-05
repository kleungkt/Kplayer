QT       += core gui network winextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
# debug_and_release
# DEFINES+=QT_NO_DEBUG_OUTPUT # 禁止qDebug输出用的
RC_ICONS = UI/ico/favicon-128.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += OPENSSL_VERSION_MAJOR=3

SOURCES += \
    infoform.cpp \
    loginform.cpp \
    main.cpp \
    mediabase.cpp \
    mediamp4.cpp \
    messageform.cpp \
    qmediaplayer.cpp \
    qscreentop.cpp \
    qstatuscheck.cpp \
    recordfile.cpp \
    ssltool.cpp \
    vlchelper.cpp \
    widget.cpp

HEADERS += \
    infoform.h \
    loginform.h \
    mediabase.h \
    mediamp4.h \
    messageform.h \
    qmediaplayer.h \
    qscreentop.h \
    qstatuscheck.h \
    recordfile.h \
    ssltool.h \
    vlchelper.h \
    widget.h

FORMS += \
    infoform.ui \
    loginForm.ui \
    loginform.ui \
    messageform.ui \
    widget.ui

TRANSLATIONS += \
    VideoPlayer_zh_CN.ts

LIBS += -L$$PWD/'lib/'
win32:LIBS += -L'D:/Windows Kits/10/Lib/10.0.18362.0/um/x86/'
win32:LIBS += -llibvlccore -llibvlc  -lAdvApi32
win32:LIBS += -lws2_32 -lbcrypt -lgdi32
LIBS += -llibcrypto_static -llibssl_static

INCLUDEPATH += $$PWD/'include'
DEPENDPATH += $$PWD/'include'

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ui.qrc
