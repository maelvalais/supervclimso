/****************************************************************************
** RoueOuvertureCLIMSO meta object code from reading C++ file 'WidgetRoueOuvertureCLIMSO.h'
**
** Created: Thu Jul 24 14:28:57 2014
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "WidgetRoueOuvertureCLIMSO.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *RoueOuvertureCLIMSO::className() const
{
    return "RoueOuvertureCLIMSO";
}

QMetaObject *RoueOuvertureCLIMSO::metaObj = 0;
static QMetaObjectCleanUp cleanUp_RoueOuvertureCLIMSO( "RoueOuvertureCLIMSO", &RoueOuvertureCLIMSO::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString RoueOuvertureCLIMSO::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "RoueOuvertureCLIMSO", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString RoueOuvertureCLIMSO::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "RoueOuvertureCLIMSO", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* RoueOuvertureCLIMSO::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"RoueOuvertureCLIMSO", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_RoueOuvertureCLIMSO.setMetaObject( metaObj );
    return metaObj;
}

void* RoueOuvertureCLIMSO::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "RoueOuvertureCLIMSO" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool RoueOuvertureCLIMSO::qt_invoke( int _id, QUObject* _o )
{
    return QWidget::qt_invoke(_id,_o);
}

bool RoueOuvertureCLIMSO::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool RoueOuvertureCLIMSO::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool RoueOuvertureCLIMSO::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
