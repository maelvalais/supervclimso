/****************************************************************************
** SoleilHeliographique meta object code from reading C++ file 'WidgetSoleilHeliographique.h'
**
** Created: Fri Sep 5 10:01:24 2014
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "WidgetSoleilHeliographique.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *SoleilHeliographique::className() const
{
    return "SoleilHeliographique";
}

QMetaObject *SoleilHeliographique::metaObj = 0;
static QMetaObjectCleanUp cleanUp_SoleilHeliographique( "SoleilHeliographique", &SoleilHeliographique::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString SoleilHeliographique::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "SoleilHeliographique", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString SoleilHeliographique::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "SoleilHeliographique", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* SoleilHeliographique::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"SoleilHeliographique", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_SoleilHeliographique.setMetaObject( metaObj );
    return metaObj;
}

void* SoleilHeliographique::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "SoleilHeliographique" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool SoleilHeliographique::qt_invoke( int _id, QUObject* _o )
{
    return QWidget::qt_invoke(_id,_o);
}

bool SoleilHeliographique::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool SoleilHeliographique::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool SoleilHeliographique::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
