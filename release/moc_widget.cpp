/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[51];
    char stringdata0[700];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 10), // "update_pos"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 3), // "pos"
QT_MOC_LITERAL(4, 23, 4), // "open"
QT_MOC_LITERAL(5, 28, 3), // "url"
QT_MOC_LITERAL(6, 32, 4), // "play"
QT_MOC_LITERAL(7, 37, 5), // "pause"
QT_MOC_LITERAL(8, 43, 4), // "stop"
QT_MOC_LITERAL(9, 48, 11), // "close_media"
QT_MOC_LITERAL(10, 60, 4), // "seek"
QT_MOC_LITERAL(11, 65, 12), // "set_position"
QT_MOC_LITERAL(12, 78, 7), // "int64_t"
QT_MOC_LITERAL(13, 86, 4), // "hour"
QT_MOC_LITERAL(14, 91, 6), // "minute"
QT_MOC_LITERAL(15, 98, 6), // "second"
QT_MOC_LITERAL(16, 105, 11), // "millisecond"
QT_MOC_LITERAL(17, 117, 9), // "set_scale"
QT_MOC_LITERAL(18, 127, 5), // "scale"
QT_MOC_LITERAL(19, 133, 10), // "pick_frame"
QT_MOC_LITERAL(20, 144, 7), // "QImage&"
QT_MOC_LITERAL(21, 152, 5), // "frame"
QT_MOC_LITERAL(22, 158, 8), // "set_size"
QT_MOC_LITERAL(23, 167, 2), // "sz"
QT_MOC_LITERAL(24, 170, 6), // "volume"
QT_MOC_LITERAL(25, 177, 3), // "vol"
QT_MOC_LITERAL(26, 181, 7), // "silence"
QT_MOC_LITERAL(27, 189, 20), // "on_preButton_clicked"
QT_MOC_LITERAL(28, 210, 21), // "on_playButton_clicked"
QT_MOC_LITERAL(29, 232, 21), // "on_nextButton_clicked"
QT_MOC_LITERAL(30, 254, 23), // "on_volumeButton_clicked"
QT_MOC_LITERAL(31, 278, 21), // "on_timeButton_clicked"
QT_MOC_LITERAL(32, 300, 33), // "on_horizontalSlider_sliderPre..."
QT_MOC_LITERAL(33, 334, 34), // "on_horizontalSlider_sliderRel..."
QT_MOC_LITERAL(34, 369, 32), // "on_horizontalSlider_rangeChanged"
QT_MOC_LITERAL(35, 402, 3), // "min"
QT_MOC_LITERAL(36, 406, 3), // "max"
QT_MOC_LITERAL(37, 410, 32), // "on_horizontalSlider_valueChanged"
QT_MOC_LITERAL(38, 443, 5), // "value"
QT_MOC_LITERAL(39, 449, 17), // "on_media_position"
QT_MOC_LITERAL(40, 467, 21), // "on_media_media_status"
QT_MOC_LITERAL(41, 489, 26), // "QMediaPlayer::PlayerStatus"
QT_MOC_LITERAL(42, 516, 1), // "s"
QT_MOC_LITERAL(43, 518, 31), // "on_listWidget_itemDoubleClicked"
QT_MOC_LITERAL(44, 550, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(45, 567, 4), // "item"
QT_MOC_LITERAL(46, 572, 21), // "on_slowButton_clicked"
QT_MOC_LITERAL(47, 594, 21), // "on_fastButton_clicked"
QT_MOC_LITERAL(48, 616, 30), // "on_volumeSlider_sliderReleased"
QT_MOC_LITERAL(49, 647, 28), // "on_volumeSlider_valueChanged"
QT_MOC_LITERAL(50, 676, 23) // "on_showhideList_pressed"

    },
    "Widget\0update_pos\0\0pos\0open\0url\0play\0"
    "pause\0stop\0close_media\0seek\0set_position\0"
    "int64_t\0hour\0minute\0second\0millisecond\0"
    "set_scale\0scale\0pick_frame\0QImage&\0"
    "frame\0set_size\0sz\0volume\0vol\0silence\0"
    "on_preButton_clicked\0on_playButton_clicked\0"
    "on_nextButton_clicked\0on_volumeButton_clicked\0"
    "on_timeButton_clicked\0"
    "on_horizontalSlider_sliderPressed\0"
    "on_horizontalSlider_sliderReleased\0"
    "on_horizontalSlider_rangeChanged\0min\0"
    "max\0on_horizontalSlider_valueChanged\0"
    "value\0on_media_position\0on_media_media_status\0"
    "QMediaPlayer::PlayerStatus\0s\0"
    "on_listWidget_itemDoubleClicked\0"
    "QListWidgetItem*\0item\0on_slowButton_clicked\0"
    "on_fastButton_clicked\0"
    "on_volumeSlider_sliderReleased\0"
    "on_volumeSlider_valueChanged\0"
    "on_showhideList_pressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      31,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      14,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  169,    2, 0x06 /* Public */,
       4,    1,  172,    2, 0x06 /* Public */,
       6,    0,  175,    2, 0x06 /* Public */,
       7,    0,  176,    2, 0x06 /* Public */,
       8,    0,  177,    2, 0x06 /* Public */,
       9,    0,  178,    2, 0x06 /* Public */,
      10,    1,  179,    2, 0x06 /* Public */,
      11,    1,  182,    2, 0x06 /* Public */,
      11,    4,  185,    2, 0x06 /* Public */,
      17,    1,  194,    2, 0x06 /* Public */,
      19,    2,  197,    2, 0x06 /* Public */,
      22,    1,  202,    2, 0x06 /* Public */,
      24,    1,  205,    2, 0x06 /* Public */,
      26,    0,  208,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      27,    0,  209,    2, 0x09 /* Protected */,
      28,    0,  210,    2, 0x09 /* Protected */,
      29,    0,  211,    2, 0x09 /* Protected */,
      30,    0,  212,    2, 0x09 /* Protected */,
      31,    0,  213,    2, 0x09 /* Protected */,
      32,    0,  214,    2, 0x09 /* Protected */,
      33,    0,  215,    2, 0x09 /* Protected */,
      34,    2,  216,    2, 0x09 /* Protected */,
      37,    1,  221,    2, 0x09 /* Protected */,
      39,    1,  224,    2, 0x09 /* Protected */,
      40,    1,  227,    2, 0x09 /* Protected */,
      43,    1,  230,    2, 0x08 /* Private */,
      46,    0,  233,    2, 0x08 /* Private */,
      47,    0,  234,    2, 0x08 /* Private */,
      48,    0,  235,    2, 0x08 /* Private */,
      49,    1,  236,    2, 0x08 /* Private */,
      50,    0,  239,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::QUrl,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, 0x80000000 | 12,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   13,   14,   15,   16,
    QMetaType::Void, QMetaType::Float,   18,
    QMetaType::Void, 0x80000000 | 20, 0x80000000 | 12,   21,    3,
    QMetaType::Void, QMetaType::QSize,   23,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   35,   36,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, 0x80000000 | 41,   42,
    QMetaType::Void, 0x80000000 | 44,   45,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->update_pos((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->open((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 2: _t->play(); break;
        case 3: _t->pause(); break;
        case 4: _t->stop(); break;
        case 5: _t->close_media(); break;
        case 6: _t->seek((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->set_position((*reinterpret_cast< int64_t(*)>(_a[1]))); break;
        case 8: _t->set_position((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 9: _t->set_scale((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->pick_frame((*reinterpret_cast< QImage(*)>(_a[1])),(*reinterpret_cast< int64_t(*)>(_a[2]))); break;
        case 11: _t->set_size((*reinterpret_cast< const QSize(*)>(_a[1]))); break;
        case 12: _t->volume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->silence(); break;
        case 14: _t->on_preButton_clicked(); break;
        case 15: _t->on_playButton_clicked(); break;
        case 16: _t->on_nextButton_clicked(); break;
        case 17: _t->on_volumeButton_clicked(); break;
        case 18: _t->on_timeButton_clicked(); break;
        case 19: _t->on_horizontalSlider_sliderPressed(); break;
        case 20: _t->on_horizontalSlider_sliderReleased(); break;
        case 21: _t->on_horizontalSlider_rangeChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 22: _t->on_horizontalSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->on_media_position((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 24: _t->on_media_media_status((*reinterpret_cast< QMediaPlayer::PlayerStatus(*)>(_a[1]))); break;
        case 25: _t->on_listWidget_itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 26: _t->on_slowButton_clicked(); break;
        case 27: _t->on_fastButton_clicked(); break;
        case 28: _t->on_volumeSlider_sliderReleased(); break;
        case 29: _t->on_volumeSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->on_showhideList_pressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Widget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::update_pos)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Widget::*)(const QUrl & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::open)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Widget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::play)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Widget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::pause)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Widget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::stop)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Widget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::close_media)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Widget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::seek)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Widget::*)(int64_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::set_position)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Widget::*)(int , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::set_position)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (Widget::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::set_scale)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (Widget::*)(QImage & , int64_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::pick_frame)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (Widget::*)(const QSize & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::set_size)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (Widget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::volume)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (Widget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::silence)) {
                *result = 13;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Widget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Widget.data,
    qt_meta_data_Widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 31)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 31;
    }
    return _id;
}

// SIGNAL 0
void Widget::update_pos(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Widget::open(const QUrl & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Widget::play()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Widget::pause()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Widget::stop()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Widget::close_media()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Widget::seek(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Widget::set_position(int64_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Widget::set_position(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Widget::set_scale(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void Widget::pick_frame(QImage & _t1, int64_t _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void Widget::set_size(const QSize & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void Widget::volume(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void Widget::silence()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
