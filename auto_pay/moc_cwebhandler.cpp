/****************************************************************************
** Meta object code from reading C++ file 'cwebhandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../auto_pay_demo_5.7/cwebhandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cwebhandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CWebHandler_t {
    QByteArrayData data[14];
    char stringdata0[127];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CWebHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CWebHandler_t qt_meta_stringdata_CWebHandler = {
    {
QT_MOC_LITERAL(0, 0, 11), // "CWebHandler"
QT_MOC_LITERAL(1, 12, 7), // "timeOut"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 10), // "urlChanged"
QT_MOC_LITERAL(4, 32, 5), // "QUrl&"
QT_MOC_LITERAL(5, 38, 3), // "url"
QT_MOC_LITERAL(6, 42, 11), // "loadStarted"
QT_MOC_LITERAL(7, 54, 8), // "loadDone"
QT_MOC_LITERAL(8, 63, 6), // "result"
QT_MOC_LITERAL(9, 70, 12), // "loadProgress"
QT_MOC_LITERAL(10, 83, 1), // "x"
QT_MOC_LITERAL(11, 85, 20), // "HttpResponseFinished"
QT_MOC_LITERAL(12, 106, 14), // "QNetworkReply*"
QT_MOC_LITERAL(13, 121, 5) // "reply"

    },
    "CWebHandler\0timeOut\0\0urlChanged\0QUrl&\0"
    "url\0loadStarted\0loadDone\0result\0"
    "loadProgress\0x\0HttpResponseFinished\0"
    "QNetworkReply*\0reply"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CWebHandler[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    1,   45,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    1,   49,    2, 0x0a /* Public */,
       9,    1,   52,    2, 0x0a /* Public */,
      11,    1,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, 0x80000000 | 12,   13,

       0        // eod
};

void CWebHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CWebHandler *_t = static_cast<CWebHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->timeOut(); break;
        case 1: _t->urlChanged((*reinterpret_cast< QUrl(*)>(_a[1]))); break;
        case 2: _t->loadStarted(); break;
        case 3: _t->loadDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->loadProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->HttpResponseFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject CWebHandler::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CWebHandler.data,
      qt_meta_data_CWebHandler,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CWebHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CWebHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CWebHandler.stringdata0))
        return static_cast<void*>(const_cast< CWebHandler*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CWebHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
