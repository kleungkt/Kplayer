/****************************************************************************
** Meta object code from reading C++ file 'qmediaplayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../qmediaplayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qmediaplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QMediaPlayer_t {
    QByteArrayData data[31];
    char stringdata0[242];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QMediaPlayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QMediaPlayer_t qt_meta_stringdata_QMediaPlayer = {
    {
QT_MOC_LITERAL(0, 0, 12), // "QMediaPlayer"
QT_MOC_LITERAL(1, 13, 8), // "position"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 3), // "pos"
QT_MOC_LITERAL(4, 27, 12), // "media_status"
QT_MOC_LITERAL(5, 40, 26), // "QMediaPlayer::PlayerStatus"
QT_MOC_LITERAL(6, 67, 1), // "s"
QT_MOC_LITERAL(7, 69, 4), // "open"
QT_MOC_LITERAL(8, 74, 4), // "path"
QT_MOC_LITERAL(9, 79, 4), // "play"
QT_MOC_LITERAL(10, 84, 5), // "pause"
QT_MOC_LITERAL(11, 90, 4), // "stop"
QT_MOC_LITERAL(12, 95, 5), // "close"
QT_MOC_LITERAL(13, 101, 4), // "seek"
QT_MOC_LITERAL(14, 106, 12), // "set_position"
QT_MOC_LITERAL(15, 119, 7), // "int64_t"
QT_MOC_LITERAL(16, 127, 4), // "hour"
QT_MOC_LITERAL(17, 132, 6), // "minute"
QT_MOC_LITERAL(18, 139, 6), // "second"
QT_MOC_LITERAL(19, 146, 11), // "millisecond"
QT_MOC_LITERAL(20, 158, 9), // "set_scale"
QT_MOC_LITERAL(21, 168, 5), // "scale"
QT_MOC_LITERAL(22, 174, 10), // "pick_frame"
QT_MOC_LITERAL(23, 185, 7), // "QImage&"
QT_MOC_LITERAL(24, 193, 5), // "frame"
QT_MOC_LITERAL(25, 199, 8), // "set_size"
QT_MOC_LITERAL(26, 208, 2), // "sz"
QT_MOC_LITERAL(27, 211, 11), // "handleTimer"
QT_MOC_LITERAL(28, 223, 6), // "volume"
QT_MOC_LITERAL(29, 230, 3), // "vol"
QT_MOC_LITERAL(30, 234, 7) // "silence"

    },
    "QMediaPlayer\0position\0\0pos\0media_status\0"
    "QMediaPlayer::PlayerStatus\0s\0open\0"
    "path\0play\0pause\0stop\0close\0seek\0"
    "set_position\0int64_t\0hour\0minute\0"
    "second\0millisecond\0set_scale\0scale\0"
    "pick_frame\0QImage&\0frame\0set_size\0sz\0"
    "handleTimer\0volume\0vol\0silence"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QMediaPlayer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    1,   97,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,  100,    2, 0x0a /* Public */,
       9,    0,  103,    2, 0x0a /* Public */,
      10,    0,  104,    2, 0x0a /* Public */,
      11,    0,  105,    2, 0x0a /* Public */,
      12,    0,  106,    2, 0x0a /* Public */,
      13,    1,  107,    2, 0x0a /* Public */,
      14,    1,  110,    2, 0x0a /* Public */,
      14,    4,  113,    2, 0x0a /* Public */,
      20,    1,  122,    2, 0x0a /* Public */,
      22,    2,  125,    2, 0x0a /* Public */,
      25,    1,  130,    2, 0x0a /* Public */,
      27,    0,  133,    2, 0x08 /* Private */,
      28,    1,  134,    2, 0x08 /* Private */,
      30,    0,  137,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QUrl,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, 0x80000000 | 15,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   16,   17,   18,   19,
    QMetaType::Void, QMetaType::Float,   21,
    QMetaType::Void, 0x80000000 | 23, 0x80000000 | 15,   24,    3,
    QMetaType::Void, QMetaType::QSize,   26,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void,

       0        // eod
};

void QMediaPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QMediaPlayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->position((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->media_status((*reinterpret_cast< QMediaPlayer::PlayerStatus(*)>(_a[1]))); break;
        case 2: _t->open((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 3: _t->play(); break;
        case 4: _t->pause(); break;
        case 5: _t->stop(); break;
        case 6: _t->close(); break;
        case 7: _t->seek((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->set_position((*reinterpret_cast< int64_t(*)>(_a[1]))); break;
        case 9: _t->set_position((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 10: _t->set_scale((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->pick_frame((*reinterpret_cast< QImage(*)>(_a[1])),(*reinterpret_cast< int64_t(*)>(_a[2]))); break;
        case 12: _t->set_size((*reinterpret_cast< const QSize(*)>(_a[1]))); break;
        case 13: _t->handleTimer(); break;
        case 14: _t->volume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->silence(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QMediaPlayer::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMediaPlayer::position)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QMediaPlayer::*)(QMediaPlayer::PlayerStatus );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMediaPlayer::media_status)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QMediaPlayer::staticMetaObject = { {
    QMetaObject::SuperData::link<QLabel::staticMetaObject>(),
    qt_meta_stringdata_QMediaPlayer.data,
    qt_meta_data_QMediaPlayer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QMediaPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QMediaPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QMediaPlayer.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int QMediaPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void QMediaPlayer::position(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QMediaPlayer::media_status(QMediaPlayer::PlayerStatus _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
