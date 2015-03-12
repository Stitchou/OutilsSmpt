/****************************************************************************
** Meta object code from reading C++ file 'traitementthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../AffidSmtp/traitementthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'traitementthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TraitementThread_t {
    QByteArrayData data[9];
    char stringdata[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TraitementThread_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TraitementThread_t qt_meta_stringdata_TraitementThread = {
    {
QT_MOC_LITERAL(0, 0, 16), // "TraitementThread"
QT_MOC_LITERAL(1, 17, 21), // "sendTraitementEnCours"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 7), // "message"
QT_MOC_LITERAL(4, 48, 4), // "fini"
QT_MOC_LITERAL(5, 53, 10), // "readOutput"
QT_MOC_LITERAL(6, 64, 4), // "Mode"
QT_MOC_LITERAL(7, 69, 6), // "Lister"
QT_MOC_LITERAL(8, 76, 7) // "Envoyer"

    },
    "TraitementThread\0sendTraitementEnCours\0"
    "\0message\0fini\0readOutput\0Mode\0Lister\0"
    "Envoyer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TraitementThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       1,   34, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    0,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   33,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

 // enums: name, flags, count, data
       6, 0x0,    2,   38,

 // enum data: key, value
       7, uint(TraitementThread::Lister),
       8, uint(TraitementThread::Envoyer),

       0        // eod
};

void TraitementThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TraitementThread *_t = static_cast<TraitementThread *>(_o);
        switch (_id) {
        case 0: _t->sendTraitementEnCours((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->fini(); break;
        case 2: _t->readOutput(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TraitementThread::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TraitementThread::sendTraitementEnCours)) {
                *result = 0;
            }
        }
        {
            typedef void (TraitementThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TraitementThread::fini)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject TraitementThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_TraitementThread.data,
      qt_meta_data_TraitementThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TraitementThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TraitementThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TraitementThread.stringdata))
        return static_cast<void*>(const_cast< TraitementThread*>(this));
    return QThread::qt_metacast(_clname);
}

int TraitementThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void TraitementThread::sendTraitementEnCours(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TraitementThread::fini()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
