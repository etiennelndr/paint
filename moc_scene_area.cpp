/****************************************************************************
** Meta object code from reading C++ file 'scene_area.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Include/scene_area.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scene_area.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SceneArea[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      31,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SceneArea[] = {
    "SceneArea\0\0setCurrentTool(int)\0"
    "setCurrentStyle(int)\0"
};

void SceneArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SceneArea *_t = static_cast<SceneArea *>(_o);
        switch (_id) {
        case 0: _t->setCurrentTool((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setCurrentStyle((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SceneArea::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SceneArea::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_SceneArea,
      qt_meta_data_SceneArea, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SceneArea::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SceneArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SceneArea::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SceneArea))
        return static_cast<void*>(const_cast< SceneArea*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int SceneArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE