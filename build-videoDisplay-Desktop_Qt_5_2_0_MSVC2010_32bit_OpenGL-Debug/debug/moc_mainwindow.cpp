/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../videoDisplay/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[23];
    char stringdata[371];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 13),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 12),
QT_MOC_LITERAL(4, 39, 9),
QT_MOC_LITERAL(5, 49, 4),
QT_MOC_LITERAL(6, 54, 5),
QT_MOC_LITERAL(7, 60, 11),
QT_MOC_LITERAL(8, 72, 21),
QT_MOC_LITERAL(9, 94, 21),
QT_MOC_LITERAL(10, 116, 23),
QT_MOC_LITERAL(11, 140, 20),
QT_MOC_LITERAL(12, 161, 19),
QT_MOC_LITERAL(13, 181, 26),
QT_MOC_LITERAL(14, 208, 28),
QT_MOC_LITERAL(15, 237, 28),
QT_MOC_LITERAL(16, 266, 27),
QT_MOC_LITERAL(17, 294, 18),
QT_MOC_LITERAL(18, 313, 21),
QT_MOC_LITERAL(19, 335, 8),
QT_MOC_LITERAL(20, 344, 9),
QT_MOC_LITERAL(21, 354, 7),
QT_MOC_LITERAL(22, 362, 7)
    },
    "MainWindow\0detectSuccess\0\0detectFailed\0"
    "startSend\0Mat&\0frame\0updateImage\0"
    "on_playButton_clicked\0on_stopButton_clicked\0"
    "on_selectButton_clicked\0on_transport_clicked\0"
    "on_stopSend_clicked\0on_openVideoButton_clicked\0"
    "on_StartDetectButton_clicked\0"
    "on_ApplyDetectButton_clicked\0"
    "on_stopDetectButton_clicked\0"
    "on_connect_clicked\0on_openRemote_clicked\0"
    "openFile\0updateFPS\0showAns\0revData\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  109,    2, 0x06,
       3,    0,  110,    2, 0x06,
       4,    1,  111,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       7,    0,  114,    2, 0x08,
       8,    0,  115,    2, 0x08,
       9,    0,  116,    2, 0x08,
      10,    0,  117,    2, 0x08,
      11,    0,  118,    2, 0x08,
      12,    0,  119,    2, 0x08,
      13,    0,  120,    2, 0x08,
      14,    0,  121,    2, 0x08,
      15,    0,  122,    2, 0x08,
      16,    0,  123,    2, 0x08,
      17,    0,  124,    2, 0x08,
      18,    0,  125,    2, 0x08,
      19,    0,  126,    2, 0x08,
      20,    0,  127,    2, 0x08,
      21,    0,  128,    2, 0x08,
      22,    0,  129,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->detectSuccess(); break;
        case 1: _t->detectFailed(); break;
        case 2: _t->startSend((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        case 3: _t->updateImage(); break;
        case 4: _t->on_playButton_clicked(); break;
        case 5: _t->on_stopButton_clicked(); break;
        case 6: _t->on_selectButton_clicked(); break;
        case 7: _t->on_transport_clicked(); break;
        case 8: _t->on_stopSend_clicked(); break;
        case 9: _t->on_openVideoButton_clicked(); break;
        case 10: _t->on_StartDetectButton_clicked(); break;
        case 11: _t->on_ApplyDetectButton_clicked(); break;
        case 12: _t->on_stopDetectButton_clicked(); break;
        case 13: _t->on_connect_clicked(); break;
        case 14: _t->on_openRemote_clicked(); break;
        case 15: _t->openFile(); break;
        case 16: _t->updateFPS(); break;
        case 17: _t->showAns(); break;
        case 18: _t->revData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::detectSuccess)) {
                *result = 0;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::detectFailed)) {
                *result = 1;
            }
        }
        {
            typedef void (MainWindow::*_t)(Mat & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::startSend)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::detectSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MainWindow::detectFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MainWindow::startSend(Mat & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
