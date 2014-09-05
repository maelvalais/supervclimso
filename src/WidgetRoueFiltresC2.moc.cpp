/****************************************************************************
** RoueFiltresC2 meta object code from reading C++ file 'WidgetRoueFiltresC2.h'
**
** Created: Fri Sep 5 10:01:24 2014
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "WidgetRoueFiltresC2.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *RoueFiltresC2::className() const
{
    return "RoueFiltresC2";
}

QMetaObject *RoueFiltresC2::metaObj = 0;
static QMetaObjectCleanUp cleanUp_RoueFiltresC2( "RoueFiltresC2", &RoueFiltresC2::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString RoueFiltresC2::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "RoueFiltresC2", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString RoueFiltresC2::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "RoueFiltresC2", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* RoueFiltresC2::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"RoueFiltresC2", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_RoueFiltresC2.setMetaObject( metaObj );
    return metaObj;
}

void* RoueFiltresC2::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "RoueFiltresC2" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool RoueFiltresC2::qt_invoke( int _id, QUObject* _o )
{
    return QWidget::qt_invoke(_id,_o);
}

bool RoueFiltresC2::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool RoueFiltresC2::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool RoueFiltresC2::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
