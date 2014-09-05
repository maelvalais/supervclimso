/****************************************************************************
** DialogFenetreFicheObservation meta object code from reading C++ file 'supervclimso.h'
**
** Created: Fri Sep 5 15:26:50 2014
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "supervclimso.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *DialogFenetreFicheObservation::className() const
{
    return "DialogFenetreFicheObservation";
}

QMetaObject *DialogFenetreFicheObservation::metaObj = 0;
static QMetaObjectCleanUp cleanUp_DialogFenetreFicheObservation( "DialogFenetreFicheObservation", &DialogFenetreFicheObservation::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString DialogFenetreFicheObservation::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "DialogFenetreFicheObservation", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString DialogFenetreFicheObservation::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "DialogFenetreFicheObservation", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* DialogFenetreFicheObservation::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"SlotBoutonAjouter", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "SlotBoutonAjouter()", &slot_0, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"DialogFenetreFicheObservation", parentObject,
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_DialogFenetreFicheObservation.setMetaObject( metaObj );
    return metaObj;
}

void* DialogFenetreFicheObservation::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "DialogFenetreFicheObservation" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool DialogFenetreFicheObservation::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: SlotBoutonAjouter(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool DialogFenetreFicheObservation::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool DialogFenetreFicheObservation::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool DialogFenetreFicheObservation::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES


const char *SupervCLIMSO::className() const
{
    return "SupervCLIMSO";
}

QMetaObject *SupervCLIMSO::metaObj = 0;
static QMetaObjectCleanUp cleanUp_SupervCLIMSO( "SupervCLIMSO", &SupervCLIMSO::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString SupervCLIMSO::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "SupervCLIMSO", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString SupervCLIMSO::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "SupervCLIMSO", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* SupervCLIMSO::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = KMainWindow::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "event", &static_QUType_ptr, "QPaintEvent", QUParameter::In }
    };
    static const QUMethod slot_0 = {"paintEvent", 1, param_slot_0 };
    static const QUMethod slot_1 = {"SlotPulsar1s", 0, 0 };
    static const QUMethod slot_2 = {"SlotBoutonInitialisationAxes", 0, 0 };
    static const QUMethod slot_3 = {"SlotBoutonConsignes", 0, 0 };
    static const QUMethod slot_4 = {"SlotBoutonModePointage", 0, 0 };
    static const QUMethod slot_5 = {"SlotBoutonModePLU", 0, 0 };
    static const QUMethod slot_6 = {"SlotBoutonModeCalibration", 0, 0 };
    static const QUMethod slot_7 = {"SlotBoutonModeObservation", 0, 0 };
    static const QUMethod slot_8 = {"SlotBouton10747", 0, 0 };
    static const QUMethod slot_9 = {"SlotBouton10770", 0, 0 };
    static const QUMethod slot_10 = {"SlotBouton10798", 0, 0 };
    static const QUMethod slot_11 = {"SlotBouton10830", 0, 0 };
    static const QUParameter param_slot_12[] = {
	{ "value", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_12 = {"SlotSpinBoxDeltaXC2", 1, param_slot_12 };
    static const QUParameter param_slot_13[] = {
	{ "value", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_13 = {"SlotSpinBoxDeltaYC2", 1, param_slot_13 };
    static const QUMethod slot_14 = {"SlotBoutonPoseImageC1", 0, 0 };
    static const QUMethod slot_15 = {"SlotBoutonPoseImageC2", 0, 0 };
    static const QUMethod slot_16 = {"SlotBoutonPoseImageL1", 0, 0 };
    static const QUMethod slot_17 = {"SlotBoutonPoseImageL2", 0, 0 };
    static const QUMethod slot_18 = {"SlotBoutonPoseBiasC1", 0, 0 };
    static const QUMethod slot_19 = {"SlotBoutonPoseBiasC2", 0, 0 };
    static const QUMethod slot_20 = {"SlotBoutonPoseBiasL1", 0, 0 };
    static const QUMethod slot_21 = {"SlotBoutonPoseBiasL2", 0, 0 };
    static const QUMethod slot_22 = {"SlotBoutonPoseDarkC1", 0, 0 };
    static const QUMethod slot_23 = {"SlotBoutonPoseDarkC2", 0, 0 };
    static const QUMethod slot_24 = {"SlotBoutonPoseDarkL1", 0, 0 };
    static const QUMethod slot_25 = {"SlotBoutonPoseDarkL2", 0, 0 };
    static const QUMethod slot_26 = {"SlotBoutonEtatC1", 0, 0 };
    static const QUMethod slot_27 = {"SlotBoutonEtatC2", 0, 0 };
    static const QUMethod slot_28 = {"SlotBoutonEtatL1", 0, 0 };
    static const QUMethod slot_29 = {"SlotBoutonEtatL2", 0, 0 };
    static const QUMethod slot_30 = {"SlotBoutonPosesBias", 0, 0 };
    static const QUMethod slot_31 = {"SlotBoutonPosesDark", 0, 0 };
    static const QUMethod slot_32 = {"SlotBoutonSequencePosesImages", 0, 0 };
    static const QUMethod slot_33 = {"SlotBoutonSuppressionDerImgC1", 0, 0 };
    static const QUMethod slot_34 = {"SlotBoutonSuppressionDerImgC2", 0, 0 };
    static const QUMethod slot_35 = {"SlotBoutonSuppressionDerImgL1", 0, 0 };
    static const QUMethod slot_36 = {"SlotBoutonSuppressionDerImgL2", 0, 0 };
    static const QUMethod slot_37 = {"SlotBoutonTransfertBASS2000C1", 0, 0 };
    static const QUMethod slot_38 = {"SlotBoutonTransfertBASS2000C2", 0, 0 };
    static const QUMethod slot_39 = {"SlotBoutonTransfertBASS2000L1", 0, 0 };
    static const QUMethod slot_40 = {"SlotBoutonTransfertBASS2000L2", 0, 0 };
    static const QUMethod slot_41 = {"SlotCBAcqAutoC1", 0, 0 };
    static const QUMethod slot_42 = {"SlotCBAcqAutoC2", 0, 0 };
    static const QUMethod slot_43 = {"SlotCBAcqAutoL1", 0, 0 };
    static const QUMethod slot_44 = {"SlotCBAcqAutoL2", 0, 0 };
    static const QUMethod slot_45 = {"SlotCBCompoSeqAcqC1", 0, 0 };
    static const QUMethod slot_46 = {"SlotCBCompoSeqAcqC2_10747", 0, 0 };
    static const QUMethod slot_47 = {"SlotCBCompoSeqAcqC2_10770", 0, 0 };
    static const QUMethod slot_48 = {"SlotCBCompoSeqAcqC2_10798", 0, 0 };
    static const QUMethod slot_49 = {"SlotCBCompoSeqAcqC2_10830", 0, 0 };
    static const QUMethod slot_50 = {"SlotCBCompoSeqAcqL1S", 0, 0 };
    static const QUMethod slot_51 = {"SlotCBCompoSeqAcqL1C", 0, 0 };
    static const QUMethod slot_52 = {"SlotCBCompoSeqAcqL2S", 0, 0 };
    static const QUMethod slot_53 = {"SlotCBCompoSeqAcqL2C", 0, 0 };
    static const QUMethod slot_54 = {"SlotBoutonModeIC_0", 0, 0 };
    static const QUMethod slot_55 = {"SlotBoutonModeDiapo_0", 0, 0 };
    static const QUMethod slot_56 = {"SlotBoutonEchLin_0", 0, 0 };
    static const QUMethod slot_57 = {"SlotBoutonEchLog_0", 0, 0 };
    static const QUMethod slot_58 = {"SlotBoutonPalNB_0", 0, 0 };
    static const QUMethod slot_59 = {"SlotBoutonPalHalpha_0", 0, 0 };
    static const QUMethod slot_60 = {"SlotBoutonPalNoirOrangeBlanc_0", 0, 0 };
    static const QUMethod slot_61 = {"SlotBoutonPalNoirVertBlanc_0", 0, 0 };
    static const QUMethod slot_62 = {"SlotBoutonPalNoirBleuBlanc_0", 0, 0 };
    static const QUMethod slot_63 = {"SlotBoutonZ0_0", 0, 0 };
    static const QUMethod slot_64 = {"SlotBoutonZ1_0", 0, 0 };
    static const QUMethod slot_65 = {"SlotBoutonZ2_0", 0, 0 };
    static const QUMethod slot_66 = {"SlotBoutonZ3_0", 0, 0 };
    static const QUMethod slot_67 = {"SlotBoutonZ4_0", 0, 0 };
    static const QUMethod slot_68 = {"SlotBoutonZ5_0", 0, 0 };
    static const QUMethod slot_69 = {"SlotBoutonZ6_0", 0, 0 };
    static const QUMethod slot_70 = {"SlotBoutonZ7_0", 0, 0 };
    static const QUMethod slot_71 = {"SlotBoutonZ8_0", 0, 0 };
    static const QUMethod slot_72 = {"SlotBoutonZ9_0", 0, 0 };
    static const QUParameter param_slot_73[] = {
	{ "value", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_73 = {"SlotSpinBoxCSB_0", 1, param_slot_73 };
    static const QUParameter param_slot_74[] = {
	{ "value", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_74 = {"SlotSpinBoxCSH_0", 1, param_slot_74 };
    static const QUParameter param_slot_75[] = {
	{ "value", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_75 = {"SlotSpinBoxCPuiLUT_0", 1, param_slot_75 };
    static const QUMethod slot_76 = {"SlotBoutonModeIC_1", 0, 0 };
    static const QUMethod slot_77 = {"SlotBoutonModeDiapo_1", 0, 0 };
    static const QUMethod slot_78 = {"SlotBoutonEchLin_1", 0, 0 };
    static const QUMethod slot_79 = {"SlotBoutonEchLog_1", 0, 0 };
    static const QUMethod slot_80 = {"SlotBoutonPalNB_1", 0, 0 };
    static const QUMethod slot_81 = {"SlotBoutonPalHalpha_1", 0, 0 };
    static const QUMethod slot_82 = {"SlotBoutonPalNoirOrangeBlanc_1", 0, 0 };
    static const QUMethod slot_83 = {"SlotBoutonPalNoirVertBlanc_1", 0, 0 };
    static const QUMethod slot_84 = {"SlotBoutonPalNoirBleuBlanc_1", 0, 0 };
    static const QUMethod slot_85 = {"SlotBoutonZ0_1", 0, 0 };
    static const QUMethod slot_86 = {"SlotBoutonZ1_1", 0, 0 };
    static const QUMethod slot_87 = {"SlotBoutonZ2_1", 0, 0 };
    static const QUMethod slot_88 = {"SlotBoutonZ3_1", 0, 0 };
    static const QUMethod slot_89 = {"SlotBoutonZ4_1", 0, 0 };
    static const QUMethod slot_90 = {"SlotBoutonZ5_1", 0, 0 };
    static const QUMethod slot_91 = {"SlotBoutonZ6_1", 0, 0 };
    static const QUMethod slot_92 = {"SlotBoutonZ7_1", 0, 0 };
    static const QUMethod slot_93 = {"SlotBoutonZ8_1", 0, 0 };
    static const QUMethod slot_94 = {"SlotBoutonZ9_1", 0, 0 };
    static const QUParameter param_slot_95[] = {
	{ "value", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_95 = {"SlotSpinBoxCSB_1", 1, param_slot_95 };
    static const QUParameter param_slot_96[] = {
	{ "value", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_96 = {"SlotSpinBoxCSH_1", 1, param_slot_96 };
    static const QUParameter param_slot_97[] = {
	{ "value", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_97 = {"SlotSpinBoxCPuiLUT_1", 1, param_slot_97 };
    static const QUMethod slot_98 = {"SlotBoutonModeIC_2", 0, 0 };
    static const QUMethod slot_99 = {"SlotBoutonModeDiapo_2", 0, 0 };
    static const QUMethod slot_100 = {"SlotBoutonEchLin_2", 0, 0 };
    static const QUMethod slot_101 = {"SlotBoutonEchLog_2", 0, 0 };
    static const QUMethod slot_102 = {"SlotBoutonPalNB_2", 0, 0 };
    static const QUMethod slot_103 = {"SlotBoutonPalHalpha_2", 0, 0 };
    static const QUMethod slot_104 = {"SlotBoutonPalNoirOrangeBlanc_2", 0, 0 };
    static const QUMethod slot_105 = {"SlotBoutonPalNoirVertBlanc_2", 0, 0 };
    static const QUMethod slot_106 = {"SlotBoutonPalNoirBleuBlanc_2", 0, 0 };
    static const QUMethod slot_107 = {"SlotBoutonZ0_2", 0, 0 };
    static const QUMethod slot_108 = {"SlotBoutonZ1_2", 0, 0 };
    static const QUMethod slot_109 = {"SlotBoutonZ2_2", 0, 0 };
    static const QUMethod slot_110 = {"SlotBoutonZ3_2", 0, 0 };
    static const QUMethod slot_111 = {"SlotBoutonZ4_2", 0, 0 };
    static const QUMethod slot_112 = {"SlotBoutonZ5_2", 0, 0 };
    static const QUMethod slot_113 = {"SlotBoutonZ6_2", 0, 0 };
    static const QUMethod slot_114 = {"SlotBoutonZ7_2", 0, 0 };
    static const QUMethod slot_115 = {"SlotBoutonZ8_2", 0, 0 };
    static const QUMethod slot_116 = {"SlotBoutonZ9_2", 0, 0 };
    static const QUParameter param_slot_117[] = {
	{ "value", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_117 = {"SlotSpinBoxCSB_2", 1, param_slot_117 };
    static const QUParameter param_slot_118[] = {
	{ "value", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_118 = {"SlotSpinBoxCSH_2", 1, param_slot_118 };
    static const QUParameter param_slot_119[] = {
	{ "value", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_119 = {"SlotSpinBoxCPuiLUT_2", 1, param_slot_119 };
    static const QUMethod slot_120 = {"SlotBoutonModeIC_3", 0, 0 };
    static const QUMethod slot_121 = {"SlotBoutonModeDiapo_3", 0, 0 };
    static const QUMethod slot_122 = {"SlotBoutonEchLin_3", 0, 0 };
    static const QUMethod slot_123 = {"SlotBoutonEchLog_3", 0, 0 };
    static const QUMethod slot_124 = {"SlotBoutonPalNB_3", 0, 0 };
    static const QUMethod slot_125 = {"SlotBoutonPalHalpha_3", 0, 0 };
    static const QUMethod slot_126 = {"SlotBoutonPalNoirOrangeBlanc_3", 0, 0 };
    static const QUMethod slot_127 = {"SlotBoutonPalNoirVertBlanc_3", 0, 0 };
    static const QUMethod slot_128 = {"SlotBoutonPalNoirBleuBlanc_3", 0, 0 };
    static const QUMethod slot_129 = {"SlotBoutonZ0_3", 0, 0 };
    static const QUMethod slot_130 = {"SlotBoutonZ1_3", 0, 0 };
    static const QUMethod slot_131 = {"SlotBoutonZ2_3", 0, 0 };
    static const QUMethod slot_132 = {"SlotBoutonZ3_3", 0, 0 };
    static const QUMethod slot_133 = {"SlotBoutonZ4_3", 0, 0 };
    static const QUMethod slot_134 = {"SlotBoutonZ5_3", 0, 0 };
    static const QUMethod slot_135 = {"SlotBoutonZ6_3", 0, 0 };
    static const QUMethod slot_136 = {"SlotBoutonZ7_3", 0, 0 };
    static const QUMethod slot_137 = {"SlotBoutonZ8_3", 0, 0 };
    static const QUMethod slot_138 = {"SlotBoutonZ9_3", 0, 0 };
    static const QUParameter param_slot_139[] = {
	{ "value", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_139 = {"SlotSpinBoxCSB_3", 1, param_slot_139 };
    static const QUParameter param_slot_140[] = {
	{ "value", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_140 = {"SlotSpinBoxCSH_3", 1, param_slot_140 };
    static const QUParameter param_slot_141[] = {
	{ "value", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_141 = {"SlotSpinBoxCPuiLUT_3", 1, param_slot_141 };
    static const QUMethod slot_142 = {"SlotBoutonPubliC1_0", 0, 0 };
    static const QUMethod slot_143 = {"SlotBoutonPubliC1_1", 0, 0 };
    static const QUMethod slot_144 = {"SlotBoutonPubliC1_2", 0, 0 };
    static const QUMethod slot_145 = {"SlotBoutonPubliC1_3", 0, 0 };
    static const QUMethod slot_146 = {"SlotBoutonPubliC2_0", 0, 0 };
    static const QUMethod slot_147 = {"SlotBoutonPubliC2_1", 0, 0 };
    static const QUMethod slot_148 = {"SlotBoutonPubliC2_2", 0, 0 };
    static const QUMethod slot_149 = {"SlotBoutonPubliC2_3", 0, 0 };
    static const QUMethod slot_150 = {"SlotBoutonPubliC2_4", 0, 0 };
    static const QUMethod slot_151 = {"SlotBoutonPubliC2_5", 0, 0 };
    static const QUMethod slot_152 = {"SlotBoutonPubliC2_6", 0, 0 };
    static const QUMethod slot_153 = {"SlotBoutonPubliC2_7", 0, 0 };
    static const QUMethod slot_154 = {"SlotBoutonPubliC2_8", 0, 0 };
    static const QUMethod slot_155 = {"SlotBoutonPubliC2_9", 0, 0 };
    static const QUMethod slot_156 = {"SlotBoutonPubliC2_10", 0, 0 };
    static const QUMethod slot_157 = {"SlotBoutonPubliC2_11", 0, 0 };
    static const QUMethod slot_158 = {"SlotBoutonPubliL1_0", 0, 0 };
    static const QUMethod slot_159 = {"SlotBoutonPubliL1_1", 0, 0 };
    static const QUMethod slot_160 = {"SlotBoutonPubliL1_2", 0, 0 };
    static const QUMethod slot_161 = {"SlotBoutonPubliL1_3", 0, 0 };
    static const QUMethod slot_162 = {"SlotBoutonPubliL2_0", 0, 0 };
    static const QUMethod slot_163 = {"SlotBoutonPubliL2_1", 0, 0 };
    static const QUMethod slot_164 = {"SlotBoutonPubliL2_2", 0, 0 };
    static const QUMethod slot_165 = {"SlotBoutonPubliL2_3", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "paintEvent(QPaintEvent*)", &slot_0, QMetaData::Protected },
	{ "SlotPulsar1s()", &slot_1, QMetaData::Protected },
	{ "SlotBoutonInitialisationAxes()", &slot_2, QMetaData::Public },
	{ "SlotBoutonConsignes()", &slot_3, QMetaData::Public },
	{ "SlotBoutonModePointage()", &slot_4, QMetaData::Public },
	{ "SlotBoutonModePLU()", &slot_5, QMetaData::Public },
	{ "SlotBoutonModeCalibration()", &slot_6, QMetaData::Public },
	{ "SlotBoutonModeObservation()", &slot_7, QMetaData::Public },
	{ "SlotBouton10747()", &slot_8, QMetaData::Public },
	{ "SlotBouton10770()", &slot_9, QMetaData::Public },
	{ "SlotBouton10798()", &slot_10, QMetaData::Public },
	{ "SlotBouton10830()", &slot_11, QMetaData::Public },
	{ "SlotSpinBoxDeltaXC2(int)", &slot_12, QMetaData::Public },
	{ "SlotSpinBoxDeltaYC2(int)", &slot_13, QMetaData::Public },
	{ "SlotBoutonPoseImageC1()", &slot_14, QMetaData::Public },
	{ "SlotBoutonPoseImageC2()", &slot_15, QMetaData::Public },
	{ "SlotBoutonPoseImageL1()", &slot_16, QMetaData::Public },
	{ "SlotBoutonPoseImageL2()", &slot_17, QMetaData::Public },
	{ "SlotBoutonPoseBiasC1()", &slot_18, QMetaData::Public },
	{ "SlotBoutonPoseBiasC2()", &slot_19, QMetaData::Public },
	{ "SlotBoutonPoseBiasL1()", &slot_20, QMetaData::Public },
	{ "SlotBoutonPoseBiasL2()", &slot_21, QMetaData::Public },
	{ "SlotBoutonPoseDarkC1()", &slot_22, QMetaData::Public },
	{ "SlotBoutonPoseDarkC2()", &slot_23, QMetaData::Public },
	{ "SlotBoutonPoseDarkL1()", &slot_24, QMetaData::Public },
	{ "SlotBoutonPoseDarkL2()", &slot_25, QMetaData::Public },
	{ "SlotBoutonEtatC1()", &slot_26, QMetaData::Public },
	{ "SlotBoutonEtatC2()", &slot_27, QMetaData::Public },
	{ "SlotBoutonEtatL1()", &slot_28, QMetaData::Public },
	{ "SlotBoutonEtatL2()", &slot_29, QMetaData::Public },
	{ "SlotBoutonPosesBias()", &slot_30, QMetaData::Public },
	{ "SlotBoutonPosesDark()", &slot_31, QMetaData::Public },
	{ "SlotBoutonSequencePosesImages()", &slot_32, QMetaData::Public },
	{ "SlotBoutonSuppressionDerImgC1()", &slot_33, QMetaData::Public },
	{ "SlotBoutonSuppressionDerImgC2()", &slot_34, QMetaData::Public },
	{ "SlotBoutonSuppressionDerImgL1()", &slot_35, QMetaData::Public },
	{ "SlotBoutonSuppressionDerImgL2()", &slot_36, QMetaData::Public },
	{ "SlotBoutonTransfertBASS2000C1()", &slot_37, QMetaData::Public },
	{ "SlotBoutonTransfertBASS2000C2()", &slot_38, QMetaData::Public },
	{ "SlotBoutonTransfertBASS2000L1()", &slot_39, QMetaData::Public },
	{ "SlotBoutonTransfertBASS2000L2()", &slot_40, QMetaData::Public },
	{ "SlotCBAcqAutoC1()", &slot_41, QMetaData::Public },
	{ "SlotCBAcqAutoC2()", &slot_42, QMetaData::Public },
	{ "SlotCBAcqAutoL1()", &slot_43, QMetaData::Public },
	{ "SlotCBAcqAutoL2()", &slot_44, QMetaData::Public },
	{ "SlotCBCompoSeqAcqC1()", &slot_45, QMetaData::Public },
	{ "SlotCBCompoSeqAcqC2_10747()", &slot_46, QMetaData::Public },
	{ "SlotCBCompoSeqAcqC2_10770()", &slot_47, QMetaData::Public },
	{ "SlotCBCompoSeqAcqC2_10798()", &slot_48, QMetaData::Public },
	{ "SlotCBCompoSeqAcqC2_10830()", &slot_49, QMetaData::Public },
	{ "SlotCBCompoSeqAcqL1S()", &slot_50, QMetaData::Public },
	{ "SlotCBCompoSeqAcqL1C()", &slot_51, QMetaData::Public },
	{ "SlotCBCompoSeqAcqL2S()", &slot_52, QMetaData::Public },
	{ "SlotCBCompoSeqAcqL2C()", &slot_53, QMetaData::Public },
	{ "SlotBoutonModeIC_0()", &slot_54, QMetaData::Public },
	{ "SlotBoutonModeDiapo_0()", &slot_55, QMetaData::Public },
	{ "SlotBoutonEchLin_0()", &slot_56, QMetaData::Public },
	{ "SlotBoutonEchLog_0()", &slot_57, QMetaData::Public },
	{ "SlotBoutonPalNB_0()", &slot_58, QMetaData::Public },
	{ "SlotBoutonPalHalpha_0()", &slot_59, QMetaData::Public },
	{ "SlotBoutonPalNoirOrangeBlanc_0()", &slot_60, QMetaData::Public },
	{ "SlotBoutonPalNoirVertBlanc_0()", &slot_61, QMetaData::Public },
	{ "SlotBoutonPalNoirBleuBlanc_0()", &slot_62, QMetaData::Public },
	{ "SlotBoutonZ0_0()", &slot_63, QMetaData::Public },
	{ "SlotBoutonZ1_0()", &slot_64, QMetaData::Public },
	{ "SlotBoutonZ2_0()", &slot_65, QMetaData::Public },
	{ "SlotBoutonZ3_0()", &slot_66, QMetaData::Public },
	{ "SlotBoutonZ4_0()", &slot_67, QMetaData::Public },
	{ "SlotBoutonZ5_0()", &slot_68, QMetaData::Public },
	{ "SlotBoutonZ6_0()", &slot_69, QMetaData::Public },
	{ "SlotBoutonZ7_0()", &slot_70, QMetaData::Public },
	{ "SlotBoutonZ8_0()", &slot_71, QMetaData::Public },
	{ "SlotBoutonZ9_0()", &slot_72, QMetaData::Public },
	{ "SlotSpinBoxCSB_0(int)", &slot_73, QMetaData::Public },
	{ "SlotSpinBoxCSH_0(int)", &slot_74, QMetaData::Public },
	{ "SlotSpinBoxCPuiLUT_0(int)", &slot_75, QMetaData::Public },
	{ "SlotBoutonModeIC_1()", &slot_76, QMetaData::Public },
	{ "SlotBoutonModeDiapo_1()", &slot_77, QMetaData::Public },
	{ "SlotBoutonEchLin_1()", &slot_78, QMetaData::Public },
	{ "SlotBoutonEchLog_1()", &slot_79, QMetaData::Public },
	{ "SlotBoutonPalNB_1()", &slot_80, QMetaData::Public },
	{ "SlotBoutonPalHalpha_1()", &slot_81, QMetaData::Public },
	{ "SlotBoutonPalNoirOrangeBlanc_1()", &slot_82, QMetaData::Public },
	{ "SlotBoutonPalNoirVertBlanc_1()", &slot_83, QMetaData::Public },
	{ "SlotBoutonPalNoirBleuBlanc_1()", &slot_84, QMetaData::Public },
	{ "SlotBoutonZ0_1()", &slot_85, QMetaData::Public },
	{ "SlotBoutonZ1_1()", &slot_86, QMetaData::Public },
	{ "SlotBoutonZ2_1()", &slot_87, QMetaData::Public },
	{ "SlotBoutonZ3_1()", &slot_88, QMetaData::Public },
	{ "SlotBoutonZ4_1()", &slot_89, QMetaData::Public },
	{ "SlotBoutonZ5_1()", &slot_90, QMetaData::Public },
	{ "SlotBoutonZ6_1()", &slot_91, QMetaData::Public },
	{ "SlotBoutonZ7_1()", &slot_92, QMetaData::Public },
	{ "SlotBoutonZ8_1()", &slot_93, QMetaData::Public },
	{ "SlotBoutonZ9_1()", &slot_94, QMetaData::Public },
	{ "SlotSpinBoxCSB_1(int)", &slot_95, QMetaData::Public },
	{ "SlotSpinBoxCSH_1(int)", &slot_96, QMetaData::Public },
	{ "SlotSpinBoxCPuiLUT_1(int)", &slot_97, QMetaData::Public },
	{ "SlotBoutonModeIC_2()", &slot_98, QMetaData::Public },
	{ "SlotBoutonModeDiapo_2()", &slot_99, QMetaData::Public },
	{ "SlotBoutonEchLin_2()", &slot_100, QMetaData::Public },
	{ "SlotBoutonEchLog_2()", &slot_101, QMetaData::Public },
	{ "SlotBoutonPalNB_2()", &slot_102, QMetaData::Public },
	{ "SlotBoutonPalHalpha_2()", &slot_103, QMetaData::Public },
	{ "SlotBoutonPalNoirOrangeBlanc_2()", &slot_104, QMetaData::Public },
	{ "SlotBoutonPalNoirVertBlanc_2()", &slot_105, QMetaData::Public },
	{ "SlotBoutonPalNoirBleuBlanc_2()", &slot_106, QMetaData::Public },
	{ "SlotBoutonZ0_2()", &slot_107, QMetaData::Public },
	{ "SlotBoutonZ1_2()", &slot_108, QMetaData::Public },
	{ "SlotBoutonZ2_2()", &slot_109, QMetaData::Public },
	{ "SlotBoutonZ3_2()", &slot_110, QMetaData::Public },
	{ "SlotBoutonZ4_2()", &slot_111, QMetaData::Public },
	{ "SlotBoutonZ5_2()", &slot_112, QMetaData::Public },
	{ "SlotBoutonZ6_2()", &slot_113, QMetaData::Public },
	{ "SlotBoutonZ7_2()", &slot_114, QMetaData::Public },
	{ "SlotBoutonZ8_2()", &slot_115, QMetaData::Public },
	{ "SlotBoutonZ9_2()", &slot_116, QMetaData::Public },
	{ "SlotSpinBoxCSB_2(int)", &slot_117, QMetaData::Public },
	{ "SlotSpinBoxCSH_2(int)", &slot_118, QMetaData::Public },
	{ "SlotSpinBoxCPuiLUT_2(int)", &slot_119, QMetaData::Public },
	{ "SlotBoutonModeIC_3()", &slot_120, QMetaData::Public },
	{ "SlotBoutonModeDiapo_3()", &slot_121, QMetaData::Public },
	{ "SlotBoutonEchLin_3()", &slot_122, QMetaData::Public },
	{ "SlotBoutonEchLog_3()", &slot_123, QMetaData::Public },
	{ "SlotBoutonPalNB_3()", &slot_124, QMetaData::Public },
	{ "SlotBoutonPalHalpha_3()", &slot_125, QMetaData::Public },
	{ "SlotBoutonPalNoirOrangeBlanc_3()", &slot_126, QMetaData::Public },
	{ "SlotBoutonPalNoirVertBlanc_3()", &slot_127, QMetaData::Public },
	{ "SlotBoutonPalNoirBleuBlanc_3()", &slot_128, QMetaData::Public },
	{ "SlotBoutonZ0_3()", &slot_129, QMetaData::Public },
	{ "SlotBoutonZ1_3()", &slot_130, QMetaData::Public },
	{ "SlotBoutonZ2_3()", &slot_131, QMetaData::Public },
	{ "SlotBoutonZ3_3()", &slot_132, QMetaData::Public },
	{ "SlotBoutonZ4_3()", &slot_133, QMetaData::Public },
	{ "SlotBoutonZ5_3()", &slot_134, QMetaData::Public },
	{ "SlotBoutonZ6_3()", &slot_135, QMetaData::Public },
	{ "SlotBoutonZ7_3()", &slot_136, QMetaData::Public },
	{ "SlotBoutonZ8_3()", &slot_137, QMetaData::Public },
	{ "SlotBoutonZ9_3()", &slot_138, QMetaData::Public },
	{ "SlotSpinBoxCSB_3(int)", &slot_139, QMetaData::Public },
	{ "SlotSpinBoxCSH_3(int)", &slot_140, QMetaData::Public },
	{ "SlotSpinBoxCPuiLUT_3(int)", &slot_141, QMetaData::Public },
	{ "SlotBoutonPubliC1_0()", &slot_142, QMetaData::Public },
	{ "SlotBoutonPubliC1_1()", &slot_143, QMetaData::Public },
	{ "SlotBoutonPubliC1_2()", &slot_144, QMetaData::Public },
	{ "SlotBoutonPubliC1_3()", &slot_145, QMetaData::Public },
	{ "SlotBoutonPubliC2_0()", &slot_146, QMetaData::Public },
	{ "SlotBoutonPubliC2_1()", &slot_147, QMetaData::Public },
	{ "SlotBoutonPubliC2_2()", &slot_148, QMetaData::Public },
	{ "SlotBoutonPubliC2_3()", &slot_149, QMetaData::Public },
	{ "SlotBoutonPubliC2_4()", &slot_150, QMetaData::Public },
	{ "SlotBoutonPubliC2_5()", &slot_151, QMetaData::Public },
	{ "SlotBoutonPubliC2_6()", &slot_152, QMetaData::Public },
	{ "SlotBoutonPubliC2_7()", &slot_153, QMetaData::Public },
	{ "SlotBoutonPubliC2_8()", &slot_154, QMetaData::Public },
	{ "SlotBoutonPubliC2_9()", &slot_155, QMetaData::Public },
	{ "SlotBoutonPubliC2_10()", &slot_156, QMetaData::Public },
	{ "SlotBoutonPubliC2_11()", &slot_157, QMetaData::Public },
	{ "SlotBoutonPubliL1_0()", &slot_158, QMetaData::Public },
	{ "SlotBoutonPubliL1_1()", &slot_159, QMetaData::Public },
	{ "SlotBoutonPubliL1_2()", &slot_160, QMetaData::Public },
	{ "SlotBoutonPubliL1_3()", &slot_161, QMetaData::Public },
	{ "SlotBoutonPubliL2_0()", &slot_162, QMetaData::Public },
	{ "SlotBoutonPubliL2_1()", &slot_163, QMetaData::Public },
	{ "SlotBoutonPubliL2_2()", &slot_164, QMetaData::Public },
	{ "SlotBoutonPubliL2_3()", &slot_165, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"SupervCLIMSO", parentObject,
	slot_tbl, 166,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_SupervCLIMSO.setMetaObject( metaObj );
    return metaObj;
}

void* SupervCLIMSO::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "SupervCLIMSO" ) )
	return this;
    return KMainWindow::qt_cast( clname );
}

bool SupervCLIMSO::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: paintEvent((QPaintEvent*)static_QUType_ptr.get(_o+1)); break;
    case 1: SlotPulsar1s(); break;
    case 2: SlotBoutonInitialisationAxes(); break;
    case 3: SlotBoutonConsignes(); break;
    case 4: SlotBoutonModePointage(); break;
    case 5: SlotBoutonModePLU(); break;
    case 6: SlotBoutonModeCalibration(); break;
    case 7: SlotBoutonModeObservation(); break;
    case 8: SlotBouton10747(); break;
    case 9: SlotBouton10770(); break;
    case 10: SlotBouton10798(); break;
    case 11: SlotBouton10830(); break;
    case 12: SlotSpinBoxDeltaXC2((int)static_QUType_int.get(_o+1)); break;
    case 13: SlotSpinBoxDeltaYC2((int)static_QUType_int.get(_o+1)); break;
    case 14: SlotBoutonPoseImageC1(); break;
    case 15: SlotBoutonPoseImageC2(); break;
    case 16: SlotBoutonPoseImageL1(); break;
    case 17: SlotBoutonPoseImageL2(); break;
    case 18: SlotBoutonPoseBiasC1(); break;
    case 19: SlotBoutonPoseBiasC2(); break;
    case 20: SlotBoutonPoseBiasL1(); break;
    case 21: SlotBoutonPoseBiasL2(); break;
    case 22: SlotBoutonPoseDarkC1(); break;
    case 23: SlotBoutonPoseDarkC2(); break;
    case 24: SlotBoutonPoseDarkL1(); break;
    case 25: SlotBoutonPoseDarkL2(); break;
    case 26: SlotBoutonEtatC1(); break;
    case 27: SlotBoutonEtatC2(); break;
    case 28: SlotBoutonEtatL1(); break;
    case 29: SlotBoutonEtatL2(); break;
    case 30: SlotBoutonPosesBias(); break;
    case 31: SlotBoutonPosesDark(); break;
    case 32: SlotBoutonSequencePosesImages(); break;
    case 33: SlotBoutonSuppressionDerImgC1(); break;
    case 34: SlotBoutonSuppressionDerImgC2(); break;
    case 35: SlotBoutonSuppressionDerImgL1(); break;
    case 36: SlotBoutonSuppressionDerImgL2(); break;
    case 37: SlotBoutonTransfertBASS2000C1(); break;
    case 38: SlotBoutonTransfertBASS2000C2(); break;
    case 39: SlotBoutonTransfertBASS2000L1(); break;
    case 40: SlotBoutonTransfertBASS2000L2(); break;
    case 41: SlotCBAcqAutoC1(); break;
    case 42: SlotCBAcqAutoC2(); break;
    case 43: SlotCBAcqAutoL1(); break;
    case 44: SlotCBAcqAutoL2(); break;
    case 45: SlotCBCompoSeqAcqC1(); break;
    case 46: SlotCBCompoSeqAcqC2_10747(); break;
    case 47: SlotCBCompoSeqAcqC2_10770(); break;
    case 48: SlotCBCompoSeqAcqC2_10798(); break;
    case 49: SlotCBCompoSeqAcqC2_10830(); break;
    case 50: SlotCBCompoSeqAcqL1S(); break;
    case 51: SlotCBCompoSeqAcqL1C(); break;
    case 52: SlotCBCompoSeqAcqL2S(); break;
    case 53: SlotCBCompoSeqAcqL2C(); break;
    case 54: SlotBoutonModeIC_0(); break;
    case 55: SlotBoutonModeDiapo_0(); break;
    case 56: SlotBoutonEchLin_0(); break;
    case 57: SlotBoutonEchLog_0(); break;
    case 58: SlotBoutonPalNB_0(); break;
    case 59: SlotBoutonPalHalpha_0(); break;
    case 60: SlotBoutonPalNoirOrangeBlanc_0(); break;
    case 61: SlotBoutonPalNoirVertBlanc_0(); break;
    case 62: SlotBoutonPalNoirBleuBlanc_0(); break;
    case 63: SlotBoutonZ0_0(); break;
    case 64: SlotBoutonZ1_0(); break;
    case 65: SlotBoutonZ2_0(); break;
    case 66: SlotBoutonZ3_0(); break;
    case 67: SlotBoutonZ4_0(); break;
    case 68: SlotBoutonZ5_0(); break;
    case 69: SlotBoutonZ6_0(); break;
    case 70: SlotBoutonZ7_0(); break;
    case 71: SlotBoutonZ8_0(); break;
    case 72: SlotBoutonZ9_0(); break;
    case 73: SlotSpinBoxCSB_0((int)static_QUType_int.get(_o+1)); break;
    case 74: SlotSpinBoxCSH_0((int)static_QUType_int.get(_o+1)); break;
    case 75: SlotSpinBoxCPuiLUT_0((int)static_QUType_int.get(_o+1)); break;
    case 76: SlotBoutonModeIC_1(); break;
    case 77: SlotBoutonModeDiapo_1(); break;
    case 78: SlotBoutonEchLin_1(); break;
    case 79: SlotBoutonEchLog_1(); break;
    case 80: SlotBoutonPalNB_1(); break;
    case 81: SlotBoutonPalHalpha_1(); break;
    case 82: SlotBoutonPalNoirOrangeBlanc_1(); break;
    case 83: SlotBoutonPalNoirVertBlanc_1(); break;
    case 84: SlotBoutonPalNoirBleuBlanc_1(); break;
    case 85: SlotBoutonZ0_1(); break;
    case 86: SlotBoutonZ1_1(); break;
    case 87: SlotBoutonZ2_1(); break;
    case 88: SlotBoutonZ3_1(); break;
    case 89: SlotBoutonZ4_1(); break;
    case 90: SlotBoutonZ5_1(); break;
    case 91: SlotBoutonZ6_1(); break;
    case 92: SlotBoutonZ7_1(); break;
    case 93: SlotBoutonZ8_1(); break;
    case 94: SlotBoutonZ9_1(); break;
    case 95: SlotSpinBoxCSB_1((int)static_QUType_int.get(_o+1)); break;
    case 96: SlotSpinBoxCSH_1((int)static_QUType_int.get(_o+1)); break;
    case 97: SlotSpinBoxCPuiLUT_1((int)static_QUType_int.get(_o+1)); break;
    case 98: SlotBoutonModeIC_2(); break;
    case 99: SlotBoutonModeDiapo_2(); break;
    case 100: SlotBoutonEchLin_2(); break;
    case 101: SlotBoutonEchLog_2(); break;
    case 102: SlotBoutonPalNB_2(); break;
    case 103: SlotBoutonPalHalpha_2(); break;
    case 104: SlotBoutonPalNoirOrangeBlanc_2(); break;
    case 105: SlotBoutonPalNoirVertBlanc_2(); break;
    case 106: SlotBoutonPalNoirBleuBlanc_2(); break;
    case 107: SlotBoutonZ0_2(); break;
    case 108: SlotBoutonZ1_2(); break;
    case 109: SlotBoutonZ2_2(); break;
    case 110: SlotBoutonZ3_2(); break;
    case 111: SlotBoutonZ4_2(); break;
    case 112: SlotBoutonZ5_2(); break;
    case 113: SlotBoutonZ6_2(); break;
    case 114: SlotBoutonZ7_2(); break;
    case 115: SlotBoutonZ8_2(); break;
    case 116: SlotBoutonZ9_2(); break;
    case 117: SlotSpinBoxCSB_2((int)static_QUType_int.get(_o+1)); break;
    case 118: SlotSpinBoxCSH_2((int)static_QUType_int.get(_o+1)); break;
    case 119: SlotSpinBoxCPuiLUT_2((int)static_QUType_int.get(_o+1)); break;
    case 120: SlotBoutonModeIC_3(); break;
    case 121: SlotBoutonModeDiapo_3(); break;
    case 122: SlotBoutonEchLin_3(); break;
    case 123: SlotBoutonEchLog_3(); break;
    case 124: SlotBoutonPalNB_3(); break;
    case 125: SlotBoutonPalHalpha_3(); break;
    case 126: SlotBoutonPalNoirOrangeBlanc_3(); break;
    case 127: SlotBoutonPalNoirVertBlanc_3(); break;
    case 128: SlotBoutonPalNoirBleuBlanc_3(); break;
    case 129: SlotBoutonZ0_3(); break;
    case 130: SlotBoutonZ1_3(); break;
    case 131: SlotBoutonZ2_3(); break;
    case 132: SlotBoutonZ3_3(); break;
    case 133: SlotBoutonZ4_3(); break;
    case 134: SlotBoutonZ5_3(); break;
    case 135: SlotBoutonZ6_3(); break;
    case 136: SlotBoutonZ7_3(); break;
    case 137: SlotBoutonZ8_3(); break;
    case 138: SlotBoutonZ9_3(); break;
    case 139: SlotSpinBoxCSB_3((int)static_QUType_int.get(_o+1)); break;
    case 140: SlotSpinBoxCSH_3((int)static_QUType_int.get(_o+1)); break;
    case 141: SlotSpinBoxCPuiLUT_3((int)static_QUType_int.get(_o+1)); break;
    case 142: SlotBoutonPubliC1_0(); break;
    case 143: SlotBoutonPubliC1_1(); break;
    case 144: SlotBoutonPubliC1_2(); break;
    case 145: SlotBoutonPubliC1_3(); break;
    case 146: SlotBoutonPubliC2_0(); break;
    case 147: SlotBoutonPubliC2_1(); break;
    case 148: SlotBoutonPubliC2_2(); break;
    case 149: SlotBoutonPubliC2_3(); break;
    case 150: SlotBoutonPubliC2_4(); break;
    case 151: SlotBoutonPubliC2_5(); break;
    case 152: SlotBoutonPubliC2_6(); break;
    case 153: SlotBoutonPubliC2_7(); break;
    case 154: SlotBoutonPubliC2_8(); break;
    case 155: SlotBoutonPubliC2_9(); break;
    case 156: SlotBoutonPubliC2_10(); break;
    case 157: SlotBoutonPubliC2_11(); break;
    case 158: SlotBoutonPubliL1_0(); break;
    case 159: SlotBoutonPubliL1_1(); break;
    case 160: SlotBoutonPubliL1_2(); break;
    case 161: SlotBoutonPubliL1_3(); break;
    case 162: SlotBoutonPubliL2_0(); break;
    case 163: SlotBoutonPubliL2_1(); break;
    case 164: SlotBoutonPubliL2_2(); break;
    case 165: SlotBoutonPubliL2_3(); break;
    default:
	return KMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool SupervCLIMSO::qt_emit( int _id, QUObject* _o )
{
    return KMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool SupervCLIMSO::qt_property( int id, int f, QVariant* v)
{
    return KMainWindow::qt_property( id, f, v);
}

bool SupervCLIMSO::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
