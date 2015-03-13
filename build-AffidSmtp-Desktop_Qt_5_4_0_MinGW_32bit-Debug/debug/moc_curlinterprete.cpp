/****************************************************************************
** Meta object code from reading C++ file 'curlinterprete.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../AffidSmtp/curl/curlinterprete.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'curlinterprete.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CurlInterprete_t {
    QByteArrayData data[10];
    char stringdata[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CurlInterprete_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CurlInterprete_t qt_meta_stringdata_CurlInterprete = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CurlInterprete"
QT_MOC_LITERAL(1, 15, 19), // "terminerProgression"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 14), // "recevoirParams"
QT_MOC_LITERAL(4, 51, 4), // "a_to"
QT_MOC_LITERAL(5, 56, 9), // "a_subject"
QT_MOC_LITERAL(6, 66, 6), // "a_body"
QT_MOC_LITERAL(7, 73, 5), // "piece"
QT_MOC_LITERAL(8, 79, 13), // "afficheErreur"
QT_MOC_LITERAL(9, 93, 3) // "msg"

    },
    "CurlInterprete\0terminerProgression\0\0"
    "recevoirParams\0a_to\0a_subject\0a_body\0"
    "piece\0afficheErreur\0msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CurlInterprete[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    4,   30,    2, 0x08 /* Private */,
       8,    1,   39,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    4,    5,    6,    7,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void CurlInterprete::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CurlInterprete *_t = static_cast<CurlInterprete *>(_o);
        switch (_id) {
        case 0: _t->terminerProgression(); break;
        case 1: _t->recevoirParams((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 2: _t->afficheErreur((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject CurlInterprete::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CurlInterprete.data,
      qt_meta_data_CurlInterprete,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CurlInterprete::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CurlInterprete::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CurlInterprete.stringdata))
        return static_cast<void*>(const_cast< CurlInterprete*>(this));
    return QObject::qt_metacast(_clname);
}

int CurlInterprete::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
