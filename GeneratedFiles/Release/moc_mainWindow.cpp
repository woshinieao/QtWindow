/****************************************************************************
** Meta object code from reading C++ file 'mainWindow.h'
**
** Created: Wed Oct 5 15:43:06 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_mainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   12,   11,   11, 0x0a,
      53,   47,   43,   11, 0x0a,
      79,   11,   11,   11, 0x0a,
      91,   11,   43,   11, 0x0a,
     107,   11,  102,   11, 0x0a,
     119,   11,  102,   11, 0x0a,
     130,   11,   43,   11, 0x0a,
     144,   11,   11,   11, 0x0a,
     161,   11,   11,   11, 0x0a,
     173,   11,   11,   11, 0x0a,
     186,   11,   11,   11, 0x0a,
     202,   11,   11,   11, 0x0a,
     215,   11,   11,   11, 0x0a,
     234,   11,   11,   11, 0x0a,
     249,   11,   11,   11, 0x0a,
     263,   11,   11,   11, 0x0a,
     284,  276,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_mainWindow[] = {
    "mainWindow\0\0curIdx\0choose_window_tpye(int)\0"
    "int\0index\0material_type_change(int)\0"
    "para_mode()\0set_para()\0bool\0save_para()\0"
    "del_para()\0cancel_para()\0calculate_mode()\0"
    "calculate()\0query_mode()\0query_history()\0"
    "query_data()\0query_data_clean()\0"
    "save_to_file()\0del_resualt()\0print_view()\0"
    "printer\0print(QPrinter*)\0"
};

void mainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        mainWindow *_t = static_cast<mainWindow *>(_o);
        switch (_id) {
        case 0: _t->choose_window_tpye((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: { int _r = _t->material_type_change((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 2: _t->para_mode(); break;
        case 3: { int _r = _t->set_para();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->save_para();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->del_para();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { int _r = _t->cancel_para();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 7: _t->calculate_mode(); break;
        case 8: _t->calculate(); break;
        case 9: _t->query_mode(); break;
        case 10: _t->query_history(); break;
        case 11: _t->query_data(); break;
        case 12: _t->query_data_clean(); break;
        case 13: _t->save_to_file(); break;
        case 14: _t->del_resualt(); break;
        case 15: _t->print_view(); break;
        case 16: _t->print((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData mainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject mainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_mainWindow,
      qt_meta_data_mainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &mainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *mainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *mainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mainWindow))
        return static_cast<void*>(const_cast< mainWindow*>(this));
    if (!strcmp(_clname, "Ui_MainWindow"))
        return static_cast< Ui_MainWindow*>(const_cast< mainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int mainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
