/* MODULE DE LA CLASSE DE LA FENETRE PRINCIPALE DE L'APPLICATION SupervCLIMSO

   LOGICIEL DE SUPERVISION DE L'INSTRUMENT CLIMSO

  (C)David.Romeuf@univ-lyon1.fr 26/10/2006 par David Romeuf
*/

#ifndef
#define VERSION_SANS_PLATINES true
#endif

// Inclusion C
//
#include <cfitsio/fitsio.h> // XXX L'instal standard de cfitsio par yum met les headers dans cfitsio/
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h> // XXX MAELVALAIS: pour sleep()

// Inclusions C++
//
#include <iostream>
#include <new>
#include <memory>
#include <valarray>

using namespace std;

// Inclusions KDE et Qt
//
#include <kapplication.h>
#include <kmainwindow.h>
#include <klocale.h>

#include <qapplication.h>

#include <qcstring.h>
#include <qdatetime.h>
#include <qdir.h>
#include <qdialog.h>
#include <qinputdialog.h>
#include <qfile.h>
#include <qlabel.h>
#include <qmessagebox.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <qstatusbar.h>
#include <qstring.h>
#include <qtextstream.h>
#include <qtimer.h>


// Inclusions SupervCLIMSO
//
#include "supervclimso.h"

// Inclusions RobOA
//
#include "ListesCommandesReponsesRobOA.h"

// Inclusions CamerOA
//
#include "ListesCommandesReponsesCamerOA.h"
#include "trameimagecameroa.h"

// Inclusions TerminOA
//
#include "ListesCommandesReponsesTerminOA.h"
#include "trameimageterminoa.h"
#define MIN_CSB		0
#define MAX_CSB		65535
#define MIN_CSH		0
#define MAX_CSH		65535
#define MIN_CPUILUT	20
#define MAX_CPUILUT	200


// Correspondance indice - nom de l'instrument affiche dans les logs
//
QString InstrumentCLIMSO[NB_CAMEROA]=
{
	"C1",
	"C2",
	"L1",
	"L2"
};

// Correspondance indice - nom de l'axe
//
QString Axe[NB_AXES]=
{
	"Roue ouverture",
	"Roue filtre C2",
	"Platine X",
	"Platine Y"
};

// Les positions correspondantes aux enumerations en degres dans le repere REEL DEFINIT PAR CONVENTION
//
double PositionsModeOuvertureCLIMSO[]=
{
	0.0,
	-32.72727272727272727,		// Mode Pointage
	-130.9090909090909091,		// Mode Calibration
	-163.6363636363636364,		// Mode PLU
	0.0,						// Mode Observation
	0.0
};

// Les positions correspondantes aux enumerations en degres dans le repere REEL DEFINIT PAR CONVENTION
//
double PositionsFiltresC2CLIMSO[]=
{
	0.0,
	0.0,						// Filtre 10747
	60.0,						// Filtre 10770
	120.0,						// Filtre 10798
	180.0,						// Filtre 10830
	0.0
};

// Inclusion des icons dans le code : ATTENTION: ils doivent etre declares en "static const char *" (const important)
//  pour ne pas generer des warnings de compilation avec gcc
//
#include <IconC1Actif.xpm>
#include <IconC1Inactif.xpm>
#include <IconC2Actif.xpm>
#include <IconC2Inactif.xpm>
#include <IconConsignes-Actif.xpm>
#include <IconConsignes-Inactif.xpm>
#include <IconFiltreC2-10747-Actif.xpm>
#include <IconFiltreC2-10747-Inactif.xpm>
#include <IconFiltreC2-10770-Actif.xpm>
#include <IconFiltreC2-10770-Inactif.xpm>
#include <IconFiltreC2-10798-Actif.xpm>
#include <IconFiltreC2-10798-Inactif.xpm>
#include <IconFiltreC2-10830-Actif.xpm>
#include <IconFiltreC2-10830-Inactif.xpm>
#include <IconL1Actif.xpm>
#include <IconL1Inactif.xpm>
#include <IconL2Actif.xpm>
#include <IconL2Inactif.xpm>
#include <IconModeCalibrationActif.xpm>
#include <IconModeCalibrationInactif.xpm>
#include <IconModeInitialisationActif.xpm>
#include <IconModeInitialisationInactif.xpm>
#include <IconModeObservationActif.xpm>
#include <IconModeObservationInactif.xpm>
#include <IconModePLUActif.xpm>
#include <IconModePLUInactif.xpm>
#include <IconModePointageActif.xpm>
#include <IconModePointageInactif.xpm>
#include <IconPoseBias.xpm>
#include <IconPoseDark.xpm>
#include <IconPoseImage.xpm>
#include <IconPosesBias.xpm>
#include <IconPosesDark.xpm>
#include <IconAcquisitionsPosesImages.xpm>
#include <LogoCLIMSO.xpm>
#include <IconSupprDerImgC1.xpm>
#include <IconSupprDerImgC2.xpm>
#include <IconSupprDerImgL1.xpm>
#include <IconSupprDerImgL2.xpm>
#include <IconTransfertBASS2000C1.xpm>
#include <IconTransfertBASS2000C2.xpm>
#include <IconTransfertBASS2000L1.xpm>
#include <IconTransfertBASS2000L2.xpm>

#include <IconEchLin.xpm>
#include <IconEchLog.xpm>
#include <IconModeIC.xpm>
#include <IconModeDiaporama.xpm>
#include <IconPaletteHalpha.xpm>
#include <IconPaletteNB.xpm>
#include <IconPaletteNoirBleuBlanc.xpm>
#include <IconPaletteNoirOrangeBlanc.xpm>
#include <IconPaletteNoirVertBlanc.xpm>
#include <IconZoneZ0.xpm>
#include <IconZoneZ1.xpm>
#include <IconZoneZ2.xpm>
#include <IconZoneZ3.xpm>
#include <IconZoneZ4.xpm>
#include <IconZoneZ5.xpm>
#include <IconZoneZ6.xpm>
#include <IconZoneZ7.xpm>
#include <IconZoneZ8.xpm>
#include <IconZoneZ9.xpm>

#define PAS_GRADUATION_TEXTE_SOLEIL_HELIOGRAPHIQUE	20

// La designation des labels des sondes de temperature
//
QString DesignationSondeTemperature[]=
{
	" Ambiante coupole",
	" Caisson informatique 1",
	" Caisson informatique 2",
	" Caisson filtre Coro1",
	" Caisson O3 Coro1",
	" Caisson occulteur Coro2",
	" Caisson filtres Coro2",
	" Caisson O3 Coro2"
};

// La designation des labels des consignes en lien avec les definitions de supervclimso.h : CONSIGNE_????
//
QString DesignationConsignes[]=
{
	"CamerOA C1: Temps de pose pour image de centrage en s ______________________________________________________",
	"CamerOA C1: Temps de pose pour image couronne en s",
	"CamerOA C1: Temps de pose pour image de PLU en s",
	"CamerOA C1: Température matrice CCD en degrés Celsius",
	"CamerOA C1: Vitesse ventilateur (1 à 3)",

	"CamerOA C2: Temps de pose pour image de centrage avec filtre 10830 nm en s__________________________________",
	"CamerOA C2: Temps de pose pour image couronne avec filtre 10747 nm en s",
	"CamerOA C2: Temps de pose pour image couronne avec filtre 10770 nm en s",
	"CamerOA C2: Temps de pose pour image couronne avec filtre 10798 nm en s",
	"CamerOA C2: Temps de pose pour image couronne avec filtre 10830 nm en s",
	"CamerOA C2: Temps de pose pour image de PLU avec filtre 10747 nm en s",
	"CamerOA C2: Temps de pose pour image de PLU avec filtre 10770 nm en s",
	"CamerOA C2: Temps de pose pour image de PLU avec filtre 10798 nm en s",
	"CamerOA C2: Temps de pose pour image de PLU avec filtre 10830 nm en s",
	"CamerOA C2: Température matrice CCD en degrés Celsius",
	"CamerOA C2: Vitesse ventilateur (1 à 3)",

	"CamerOA L1: Temps de pose pour image de centrage en s ______________________________________________________",
	"CamerOA L1: Temps de pose pour image surface en s",
	"CamerOA L1: Temps de pose pour image couronne en s",
	"CamerOA L1: Temps de pose pour image de PLU en s",
	"CamerOA L1: Température matrice CCD en degrés Celsius",
	"CamerOA L1: Vitesse ventilateur (1 à 3)",

	"CamerOA L2: Temps de pose pour image de centrage en s ______________________________________________________",
	"CamerOA L2: Temps de pose pour image surface en s",
	"CamerOA L2: Temps de pose pour image couronne en s",
	"CamerOA L2: Temps de pose pour image de PLU en s",
	"CamerOA L2: Température matrice CCD en degrés Celsius",
	"CamerOA L2: Vitesse ventilateur (1 à 3)",

	"Caisson informatique: Alerte inférieure température en °C __________________________________________________",
	"Caisson informatique: Alerte supérieure température en °C",

	"Caisson filtre C1: Alerte inférieure température en °C _____________________________________________________",
	"Caisson filtre C1: Alerte supérieure température en °C",

	"Caisson filtres C2: Alerte inférieure température en °C ____________________________________________________",
	"Caisson filtres C2: Alerte supérieure température en °C"
};

// La designation des types d'acquisition
//
QString DesignationTypesAcq[]=
{
	"C1_C",
	"C2_10830",
	"C2_10747",
	"C2_10770",
	"C2_10798",
	"L1_S",
	"L1_C",
	"L2_S",
	"L2_C"
};

// Les semaphores pour synchroniser les processus legers
//
extern QSemaphore SemaphoreSyncLancementThreadSupervCLIMSO;	// Synchronisation du lancement des threads de SupervCLIMSO

QMutex MutexEnvChaineBIO_CamerOA[NB_CAMEROA];				// Mutex lors de l'utilisation des fonctions EnvoyerChaineBIO() pour les processus
QMutex MutexEnvChaineBIO_TerminOA[NB_TERMINOA];
QMutex MutexEnvChaineBIO_RobOA;

//-----------------------------------------------------------------------------------------------------------------------------------

// Objet de visualisation des images de centrage des CamerOA
//
// Il herite de QDialog pour pouvoir surcharger l'evenement closeEvent(). En effet, le bouton de fermeture de la fenetre QDialog
//  depend du WindowsManager X et pas du QWidget donc il faut surcharger closeEvent et ignorer le signal close().
// La seule autre solution serait de creer la fenetre dialogue avec le drapeau Qt::WStyle_NoBorder mais la fenetre n'a plus de bords
//  du windows manager et n'est plus deplacable, n'a plus de titre...
//
DialogFenetreCamerOA::DialogFenetreCamerOA(QWidget *parent,const char *name,bool modal,WFlags f) : QDialog(parent,name,modal,f)
{
}

// Surcharge de closeEvent()
//
void DialogFenetreCamerOA::closeEvent(QCloseEvent *e)
{
	e->ignore();	// On ignore le signal pour ne pas pouvoir fermer la fenetre
}

//-----------------------------------------------------------------------------------------------------------------------------------

// Objet de visualisation des temperatures
//
// Il herite de QDialog pour pouvoir surcharger l'evenement closeEvent(). En effet, le bouton de fermeture de la fenetre QDialog
//  depend du WindowsManager X et pas du QWidget donc il faut surcharger closeEvent et ignorer le signal close().
// La seule autre solution serait de creer la fenetre dialogue avec le drapeau Qt::WStyle_NoBorder mais la fenetre n'a plus de bords
//  du windows manager et n'est plus deplacable, n'a plus de titre...
//
DialogFenetreTemperatures::DialogFenetreTemperatures(QWidget *parent,const char *name,bool modal,WFlags f) : QDialog(parent,name,modal,f)
{
}

// Surcharge de closeEvent()
//
void DialogFenetreTemperatures::closeEvent(QCloseEvent *e)
{
	e->ignore();	// On ignore le signal pour ne pas pouvoir fermer la fenetre
}

//-----------------------------------------------------------------------------------------------------------------------------------

// Objet de controle des TerminOA de visualisation
//
// Il herite de QDialog pour pouvoir surcharger l'evenement closeEvent(). En effet, le bouton de fermeture de la fenetre QDialog
//  depend du WindowsManager X et pas du QWidget donc il faut surcharger closeEvent et ignorer le signal close().
// La seule autre solution serait de creer la fenetre dialogue avec le drapeau Qt::WStyle_NoBorder mais la fenetre n'a plus de bords
//  du windows manager et n'est plus deplacable, n'a plus de titre...
//
DialogFenetreCtrlTerminOA::DialogFenetreCtrlTerminOA(QWidget *parent,const char *name,bool modal,WFlags f) : QDialog(parent,name,modal,f)
{
}

// Surcharge de closeEvent()
//
void DialogFenetreCtrlTerminOA::closeEvent(QCloseEvent *e)
{
	e->ignore();	// On ignore le signal pour ne pas pouvoir fermer la fenetre
}

//-----------------------------------------------------------------------------------------------------------------------------------

// Objet de la fiche d'observation de CLIMSO
//
// Il herite de QDialog pour pouvoir surcharger l'evenement closeEvent(). En effet, le bouton de fermeture de la fenetre QDialog
//  depend du WindowsManager X et pas du QWidget donc il faut surcharger closeEvent et ignorer le signal close().
// La seule autre solution serait de creer la fenetre dialogue avec le drapeau Qt::WStyle_NoBorder mais la fenetre n'a plus de bords
//  du windows manager et n'est plus deplacable, n'a plus de titre...
//
DialogFenetreFicheObservation::DialogFenetreFicheObservation(QWidget *parent,const char *name,bool modal,WFlags f) : QDialog(parent,name,modal,f)
{
	// Boite de rangement vertical dans la fenetre de la fiche d'observation
	//
	if( (BRVFenetreFicheObservation=new (std::nothrow) QVBox(this,"SupervCLIMSO-QVBox-BRVFenetreFicheObservation")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QVBox:BRVFenetreFicheObservation de la fenetre FenetreFicheObservation." << std::endl;
	}
	BRVFenetreFicheObservation->setMinimumSize(TAILLE_X_FICHE_OBS_RECOMMANDEE,TAILLE_Y_FICHE_OBS_RECOMMANDEE);

	// Boite de rangement horizontal du widget d'affichage de la fiche d'observation
	//
	if( (BRHFenetreFicheObservation1=new (std::nothrow) QHBox(BRVFenetreFicheObservation,"SupervCLIMSO-QHBox-BRHFenetreFicheObservation1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BRHFenetreFicheObservation1 de la fenetre FenetreFicheObservation." << std::endl;
	}

	// Boite de rangement horizontal du widget d'affichage de la ligne de saisie de la fiche d'observation
	//
	if( (BRHFenetreFicheObservation2=new (std::nothrow) QHBox(BRVFenetreFicheObservation,"SupervCLIMSO-QHBox-BRHFenetreFicheObservation2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BRHFenetreFicheObservation2 de la fenetre FenetreFicheObservation." << std::endl;
	}

	// Widget d'affichage de la fiche d'observation
	//
	if( (FicheObservation=new (std::nothrow) QTextEdit(BRHFenetreFicheObservation1,"SupervCLIMSO-QTextEdit-FicheObservation")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QTextEdit:FicheObservation de la fenetre FenetreFicheObservation." << std::endl;
	}
	FicheObservation->setReadOnly(TRUE);
	FicheObservation->setPaper(QBrush(COULEUR_FOND_FICHE_OBS));

	// Widget de la ligne de saisie de la fiche d'observation
	//
	if( (EditFicheObservation=new (std::nothrow) QLineEdit(BRHFenetreFicheObservation2,"SupervCLIMSO-QLineEdit-EditFicheObservation")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLineEdit-EditFicheObservation de la fenetre FenetreFicheObservation." << std::endl;
	}
	EditFicheObservation->setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed));
	EditFicheObservation->setFixedHeight(TAILLE_Y_BOUTON_AJOUT_FICHE_OBS);
	EditFicheObservation->setBackgroundColor(COULEUR_FOND_EDIT_FICHE_OBS);

	// Bouton d'ajout de la ligne saisie dans la fiche d'observation
	//
	if( (BoutonAjouterFicheObservation=new (std::nothrow) QPushButton(BRHFenetreFicheObservation2,"SupervCLIMSO-QPushButton-BoutonAjouterFicheObservation")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton-BoutonAjouterFicheObservation de la fenetre FenetreFicheObservation." << std::endl;
	}
	BoutonAjouterFicheObservation->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	BoutonAjouterFicheObservation->setMinimumSize(TAILLE_X_BOUTON_AJOUT_FICHE_OBS,TAILLE_Y_BOUTON_AJOUT_FICHE_OBS);
	BoutonAjouterFicheObservation->setMaximumSize(TAILLE_X_BOUTON_AJOUT_FICHE_OBS,TAILLE_Y_BOUTON_AJOUT_FICHE_OBS);
	BoutonAjouterFicheObservation->setText("Ajouter");

	// Connexion du bouton d'ajout avec son slot
	//
	connect(BoutonAjouterFicheObservation,SIGNAL(clicked()),this,SLOT(SlotBoutonAjouter()));
}

// Surcharge de closeEvent()
//
void DialogFenetreFicheObservation::closeEvent(QCloseEvent *e)
{
	e->ignore();	// On ignore le signal pour ne pas pouvoir fermer la fenetre
}

// Surcharge de la fonction de slot paintEvent heritee du QWidget
//
void DialogFenetreFicheObservation::paintEvent(QPaintEvent *event)
{
	QPaintEvent *e;
	e=event;

	// On redimensionne la boite de rangement vertical
	//
	// Note : 	On redimensionne uniquement la QVBox qui contient les widgets enfants de la fenetre pour que la QVBox s'etende sur toute la surface de la fenetre porteuse
	//			Il suffit de contraindre correctement les DIMENSIONS (setSizePolicy) de la ligne d'edition et du bouton d'ajout pour que les autres widgets s'adaptent
	//			 aux nouvelles dimensions.
	//
	BRVFenetreFicheObservation->resize(this->size());
}


// Slot du bouton de demande d'ajout de la ligne saisie dans la fiche d'observation
//
void DialogFenetreFicheObservation::SlotBoutonAjouter(void)
{
	if( EditFicheObservation->text().length() != 0 )
	{
		// On recupere la date et l'heure courante UT du systeme
		//
		QDateTime DateHeureUT=QDateTime::currentDateTime(Qt::UTC);

		// Composition de la ligne qui sera ajoutee dans la fiche d'observation
		//
		QString LigneFichier=DateHeureUT.toString("hh:mm:ss")+" > "+EditFicheObservation->text()+"\n";
		QString LigneWidget=DateHeureUT.toString("hh:mm:ss")+" > <B>"+EditFicheObservation->text()+"</B>\n";

		// Insertion de la ligne a la fin de la fiche d'observation
		//
		FicheObservation->append(LigneWidget);

		// Sauvegarde de la ligne dans le fichier de la fiche d'observation
		//
		FluxFichierFicheObservation << LigneFichier;

		// On peut effacer la ligne saisie
		//
		EditFicheObservation->clear();
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------


// Constructeur de la classe de la fenetre principale de l'application SupervCLIMSO
//
// KMainWindow est un widget de haut niveau qui permet de gerer la geometrie de la fenetre principale et des widgets enfants 
//
SupervCLIMSO::SupervCLIMSO(QString p_chemRepSuperviseur,KApplication *p_appli) : KMainWindow(0,"SupervCLIMSO-KMainWindow")
{
	int i;	// Variable indice

	// set the shell's ui resource file
	//setXMLFile("supervclimsoui.rc");
	
	// On recupere la date et l'heure courante UT du systeme
	//
	QDateTime DateHeureUT=QDateTime::currentDateTime(Qt::UTC);

	// Initialisation des variables
	//
	CheminRepSuperviseur=p_chemRepSuperviseur;
	appli=p_appli;
	MotDePasseConsignes=false;
	aMotDePasseConsignes=-1;
	AxesInitialises=false;
	aAxesInitialises=-1;	// une valeur impossible pour provoquer la detection de changement de la valeur par MAJEtatBoutonsFP()
	C1Actif=false;
	aC1Actif=-1;
	C2Actif=false;
	aC2Actif=-1;
	L1Actif=false;
	aL1Actif=-1;
	L2Actif=false;
	aL2Actif=-1;

	ModeObservation=ModeRO_NonInitialise;
	aModeObservation=ModeRO_SansMode;

	FiltreC2=FiltreC2_NonInitialise;
	aFiltreC2=FiltreC2_SansFiltre;

	for( i=0; i < NB_CONSIGNES; i++ )
	{
		aEditConsignes[i]=CONSIGNE_EDIT_NON_INIT;			// jamais examinee et valeur de consigne non saisissable en entree
		ConsignesDansUniteEntiere[i]=0;
	}
	CaissonInfoLinf=CONSIGNE_TEMPERATURE_MINI;
	CaissonInfoLsup=CONSIGNE_TEMPERATURE_MAXI;
	FiltreC1Linf=CONSIGNE_TEMPERATURE_MINI;
	FiltreC1Lsup=CONSIGNE_TEMPERATURE_MAXI;
	FiltresC2Linf=CONSIGNE_TEMPERATURE_MINI;
	FiltresC2Lsup=CONSIGNE_TEMPERATURE_MAXI;

	for( i=0; i < NB_AXES; i++ )
	{
		AxeIndexTrouve[i]=false;
		AxePositionReposTrouvee[i]=false;
		PosAxeMicropasMoteur[i]=POSITION_AXE_MICROPAS_NON_CONNUE;
		PosAxeDegres[i]=POSITION_AXE_DEGRES_NON_CONNUE;
	}
	AxeRechIndexEnCours=AXE_NON_RECHERCHE;
	
	for( i=0; i < NB_CAMEROA; i++ )
	{
		PLCommandeCamerOA[i]=NULL;
		PLDonneesCamerOA[i]=NULL;
		PoseEnCours[i]=false;
		ConsignesCamerOAInitialisees[i]=false;
		ListeNomFichDerImg[i].clear();
		DateHeureDerImg[i].setTime_t(0);
		TemperatureCamerOA[i]=TEMPERATURE_NON_CONNUE;
	}

	for( i=0; i < NB_TERMINOA; i++ )
	{
		ConsignesTerminOAInitialisees[i]=false;
	}

	for( i=0; i < NB_SONDES_TEMPERATURE; i++ )
	{
		AlerteFenetreTemperatures[i]=false;
	}

	// Copie des commandes et reponses dans l'objet pour etre thread safe (bogues avec QString en inter processus)
	//
	for( i=0; i < NB_CMD_CLIENT_ROBOA; i++ ) CmdClientRobOA[i]=ListeCmdClientROBOA[i];
	CmdRobOAPosAxes=CmdClientRobOA[ROBOA_CMD_POSAXESPASENC]+"\n";
	for( i=0; i < NB_CMD_CLIENT_TERMINOA; i++ ) CmdClientTerminOA[i]=ListeCmdClientTerminOA[i];
	for( i=0; i < NB_CMD_CLIENT_CAMEROA; i++ ) CmdClientCamerOA[i]=ListeCmdClientCamerOA[i];
	CmdCamerOATempCCD=CmdClientCamerOA[CAMEROA_CMD_TEMPCCD]+"\n";
	CmdCamerOAPuiPeltier=CmdClientCamerOA[CAMEROA_CMD_PUIPELTIER]+"\n";
	CmdCamerOAPoseBias=CmdClientCamerOA[CAMEROA_CMD_POSEIBIAS]+"\n";

	// Le chemin vers le repertoire de stockage des donnees acquises
	//
	CheminStockageDonnees="/dataCLIMSO/"+DateHeureUT.toString("yyyy-MM-dd");

	if( !QDir(CheminStockageDonnees).exists() )
	{
		QDir Repertoire;

		if( Repertoire.mkdir(CheminStockageDonnees,TRUE) == FALSE )
		{
			std::cerr << "ERREUR: SupervCLIMSO: Impossible de creer le repertoire de stockage des donnees acquises." << std::endl;
			appli->exit(-1);
		}

		if( chmod(CheminStockageDonnees.ascii(),S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH) == -1 )
		{
			std::cerr << "ERREUR: SupervCLIMSO: Impossible de modifier les droits du repertoire de stockage des donnees acquises." << std::endl;
			appli->exit(-1);
		}
	}

	// Initialisation des coordonnees heliographiques
	//
	CalcAstro.CoordonneesHeliographiquesCentreDisqueSolaire(JJ(DateHeureUT),&Po,&Lo,&Bo);


	// Widgets de la fenetre principale ------------------------------------------------------------------------------------------------

	// Creation du widget de la boite de rangement vertical de la fenetre principale
	//
	if( (BoiteRangementVertical=new (std::nothrow) QVBox(this,"SupervCLIMSO-KMainWindow-BoiteRangementVertical")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QVBox:BoiteRangementVertical de la fenetre principale KMainWindow." << std::endl;
	}


	// ---- les boites de rangement horizontal


	// Creation de la boite de rangement horizontal 1 de la boite de rangement vertical de la fenetre principale
	//
	// Cette boite contiendra les boutons des commandes de base
	//
	if( (BoiteRangementHorizontal1=new (std::nothrow) QHBox(BoiteRangementVertical,"SupervCLIMSO-BoiteRangementVertical-BoiteRangementHorizontal1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BoiteRangementHorizontal1 de la boite de rangement vertical de la fenetre principale." << std::endl;
	}
	BoiteRangementHorizontal1->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum));

	// Creation de la boite de rangement vertical 1a de la boite de rangement horizontal 1 de la fenetre principale
	//
	if( (BoiteRangementVertical1a=new (std::nothrow) QVBox(BoiteRangementHorizontal1,"SupervCLIMSO-BoiteRangementHorizontal1-BoiteRangementVertical1a")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QVBox:BoiteRangementVertical1a de la boite de rangement vertical de la fenetre principale." << std::endl;
	}
	BoiteRangementVertical1a->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Maximum));

	// Bouton de demande d'initialisation des axes de CLIMSO
	//
	if( (BoutonInitialisationAxes=new (std::nothrow) QPushButton(BoiteRangementVertical1a,"SupervCLIMSO-BoiteRangementVertical1a-BoutonInitialisationAxes")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonInitialisationAxes de la boite de rangement vertical 1a de la fenetre principale." << std::endl;
	}
	BoutonInitialisationAxes->setPixmap(QPixmap(IconModeInitialisationInactif_xpm));
	BoutonInitialisationAxes->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(BoutonInitialisationAxes,QString::fromLocal8Bit("Démarrer la procédure de recherche des index des axes (top 0) de CLIMSO (Roue ouverture, filtres, platine XY)"));

	//
	// Creation des palettes des QPushButton a partir des couleurs par defaut du bouton BoutonInitialisationAxes
	//

	// La palette verdatre lorsqu'une fonction est accessible en cliquant
	//
	PaletteBoutonVerdatre=BoutonInitialisationAxes->palette();	// On part de la palette du widget QPushButton:BoutonInitialisationAxes
	PaletteBoutonVerdatre.setColor(QPalette::Active,QColorGroup::Button,QColor(78,205,78));		// Fond du bouton actif au repos 
	PaletteBoutonVerdatre.setColor(QPalette::Active,QColorGroup::Midlight,QColor(135,255,135));	// Fond du bouton actif au survol souris
	PaletteBoutonVerdatre.setColor(QPalette::Inactive,QColorGroup::Button,QColor(78,205,78));	// Fond du bouton inactif au repos 
	PaletteBoutonVerdatre.setColor(QPalette::Inactive,QColorGroup::Midlight,QColor(78,205,78));	// Fond du bouton inactif au survol souris

	// La palette orangee lorsqu'une fonction est accessible en cliquant
	//
	PaletteBoutonOrangee=BoutonInitialisationAxes->palette();	// On part de la palette du widget QPushButton:BoutonInitialisationAxes
	PaletteBoutonOrangee.setColor(QPalette::Active,QColorGroup::Button,QColor(219,155,0));		// Fond du bouton actif au repos
	PaletteBoutonOrangee.setColor(QPalette::Active,QColorGroup::Midlight,QColor(255,180,0));	// Fond du bouton actif au survol souris
	PaletteBoutonOrangee.setColor(QPalette::Inactive,QColorGroup::Button,QColor(219,155,0));	// Fond du bouton inactif au repos
	PaletteBoutonOrangee.setColor(QPalette::Inactive,QColorGroup::Midlight,QColor(219,155,0));	// Fond du bouton inactif au survol souris

	// Bouton de demande d'acces au tableau des consignes de CLIMSO
	//
	if( (BoutonConsignes=new (std::nothrow) QPushButton(BoiteRangementVertical1a,"SupervCLIMSO-BoiteRangementVertical1a-BoutonConsignes")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonConsignes de la boite de rangement vertical 1a de la fenetre principale." << std::endl;
	}
	BoutonConsignes->setPixmap(QPixmap(IconConsignesInactif_xpm));
	BoutonConsignes->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(BoutonConsignes,QString::fromLocal8Bit("Accès aux consignes des instruments de CLIMSO (temps de pose, température, vitesse ventilateur...)"));

	// Affichage des logs
	//
	if( (Logs=new (std::nothrow) QTextEdit(BoiteRangementHorizontal1,"SupervCLIMSO-BoiteRangementHorizontal1-Logs")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QTextEdit:Logs de la boite de rangement horizontal 1 de la fenetre principale." << std::endl;
	}
	Logs->setTextFormat(Qt::LogText);
//	Logs->setFixedHeight(BoutonInitialisationAxes->height()+BoutonConsignes->height());
	Logs->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,QSizePolicy::Fixed));


	// Creation de la boite de rangement horizontal 2 de la boite de rangement vertical de la fenetre principale
	//
	// Cette boite contiendra les logos et les representations de la roue d'ouverture et roue a filtres
	//
	if( (BoiteRangementHorizontal2=new (std::nothrow) QHBox(BoiteRangementVertical,"SupervCLIMSO-BoiteRangementVertical-BoiteRangementHorizontal2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BoiteRangementHorizontal2 de la boite de rangement vertical de la fenetre principale." << std::endl;
	}
	BoiteRangementHorizontal2->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum));

	// Le QLabel:pixmap du logo de CLIMSO
	//
	if( (LogoCLIMSO=new (std::nothrow) QLabel(BoiteRangementHorizontal2,"SupervCLIMSO-BoiteRangementHorizontal2-LogoCLIMSO")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLabel:LogoCLIMSO de la boite de rangement horizontal 2 de la fenetre principale." << std::endl;
	}
	LogoCLIMSO->setPixmap(QPixmap(LogoCLIMSO_xpm));
	LogoCLIMSO->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(LogoCLIMSO,QString::fromLocal8Bit("le Christian Latouche IMageur SOlaire qui réalise des CLichets Multiples du SOleil"));

	// La representation graphique du Soleil en coordonnees heliographiques
	//
	if( (GraphiqueSoleil=new (std::nothrow) SoleilHeliographique(BoiteRangementHorizontal2,"SupervCLIMSO-BoiteRangementHorizontal2-GraphiqueSoleil")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget SoleilHeliographique:GraphiqueSoleil de la boite de rangement horizontal 2 de la fenetre principale." << std::endl;
	}
	GraphiqueSoleil->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum));
	GraphiqueSoleil->ParametresHeliographiques(Po,Lo,Bo);
	GraphiqueSoleil->ParametragePasGradLoTexte(PAS_GRADUATION_TEXTE_SOLEIL_HELIOGRAPHIQUE);
	GraphiqueSoleil->ParametragePasGradBoTexte(PAS_GRADUATION_TEXTE_SOLEIL_HELIOGRAPHIQUE);
	GraphiqueSoleil->ParametragePasGradPTexte(PAS_GRADUATION_TEXTE_SOLEIL_HELIOGRAPHIQUE);
	QToolTip::add(GraphiqueSoleil,QString::fromLocal8Bit("Une représentation graphique du repère héliographique à cette date et heure d'observation"));

	// La representation graphique de la roue d'ouverture de CLIMSO
	//
	if( (GraphRoueOuverture=new (std::nothrow) RoueOuvertureCLIMSO(BoiteRangementHorizontal2,"SupervCLIMSO-BoiteRangementHorizontal2-GraphRoueOuverture")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget RoueOuvertureCLIMSO:GraphRoueOuverture de la boite de rangement horizontal 2 de la fenetre principale." << std::endl;
	}
	GraphRoueOuverture->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum));
//	GraphRoueOuverture->ParametresHeliographiques(Po,Lo,Bo);
	QToolTip::add(GraphRoueOuverture,QString::fromLocal8Bit("Représentation graphique de la position actuelle de la roue d'ouverture de CLIMSO (roue PLU, CAL, obturateur...)"));

	// La representation graphique de la roue a filtres de l'instrument C2 de CLIMSO
	//
	if( (GraphRoueFiltresC2=new (std::nothrow) RoueFiltresC2(BoiteRangementHorizontal2,"SupervCLIMSO-BoiteRangementHorizontal2-GraphRoueFiltresC2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget RoueFiltesC2:GraphRoueFiltresC2 de la boite de rangement horizontal 2 de la fenetre principale." << std::endl;
	}
	GraphRoueFiltresC2->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum));
//	GraphRoueOuverture->ParametresHeliographiques(Po,Lo,Bo);
	QToolTip::add(GraphRoueFiltresC2,QString::fromLocal8Bit("Représentation graphique de la position actuelle de la roue à filtres de l'instrument C2 de CLIMSO"));


	// Creation de la boite de rangement horizontal 3 de la boite de rangement vertical de la fenetre principale
	//
	// Cette boite contiendra les widgets du mode d'observation courant de CLIMSO
	//
	if( (BoiteRangementHorizontal3=new (std::nothrow) QHBox(BoiteRangementVertical,"SupervCLIMSO-BoiteRangementVertical-BoiteRangementHorizontal3")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BoiteRangementHorizontal3 de la boite de rangement vertical de la fenetre principale." << std::endl;
	}
	BoiteRangementHorizontal3->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum));

	// Bouton de demande de passage de CLIMSO en mode PLU
	//
	if( (BoutonModePLU=new (std::nothrow) QPushButton(BoiteRangementHorizontal3,"SupervCLIMSO-BoiteRangementHorizontal3-BoutonModePLU")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonModePLU de la boite de rangement horizontal 3 de la fenetre principale." << std::endl;
	}
	BoutonModePLU->setPixmap(QPixmap(IconModePLUInactif_xpm));
	BoutonModePLU->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(BoutonModePLU,QString::fromLocal8Bit("Tourner la roue d'ouverture de CLIMSO jusqu'à la position P.L.U (verre dépoli devant les instruments)"));

	// Bouton de demande de passage de CLIMSO en mode calibration
	//
	if( (BoutonModeCalibration=new (std::nothrow) QPushButton(BoiteRangementHorizontal3,"SupervCLIMSO-BoiteRangementHorizontal3-BoutonModeCalibration")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonModeCalibration de la boite de rangement horizontal 3 de la fenetre principale." << std::endl;
	}
	BoutonModeCalibration->setPixmap(QPixmap(IconModeCalibrationInactif_xpm));
	BoutonModeCalibration->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(BoutonModeCalibration,QString::fromLocal8Bit("Tourner la roue d'ouverture de CLIMSO jusqu'à la position Calibration (verre densité devant les instruments)"));

	// Bouton de demande de passage de CLIMSO en mode pointage
	//
	if( (BoutonModePointage=new (std::nothrow) QPushButton(BoiteRangementHorizontal3,"SupervCLIMSO-BoiteRangementHorizontal3-BoutonModePointage")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonModePointage de la boite de rangement horizontal 3 de la fenetre principale." << std::endl;
	}
	BoutonModePointage->setPixmap(QPixmap(IconModePointageInactif_xpm));
	BoutonModePointage->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(BoutonModePointage,QString::fromLocal8Bit("Tourner la roue d'ouverture de CLIMSO jusqu'à la position Pointage (masque 4 petites ouvertures pour eviter la chauffe)"));

	// Bouton de demande de passage de CLIMSO en mode observation
	//
	if( (BoutonModeObservation=new (std::nothrow) QPushButton(BoiteRangementHorizontal3,"SupervCLIMSO-BoiteRangementHorizontal3-BoutonModeObservation")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonModeObservation de la boite de rangement horizontal 3 de la fenetre principale." << std::endl;
	}
	BoutonModeObservation->setPixmap(QPixmap(IconModeObservationInactif_xpm));
	BoutonModeObservation->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(BoutonModeObservation,QString::fromLocal8Bit("Tourner la roue d'ouverture de CLIMSO jusqu'à la position Observation (pleine ouverture)"));


	// Creation de la boite de rangement horizontal 4 de la boite de rangement vertical de la fenetre principale
	//
	// Cette boite contiendra les boutons des positions des filtres de C2
	//
	if( (BoiteRangementHorizontal4=new (std::nothrow) QHBox(BoiteRangementVertical,"SupervCLIMSO-BoiteRangementVertical-BoiteRangementHorizontal4")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BoiteRangementHorizontal4 de la boite de rangement vertical de la fenetre principale." << std::endl;
	}
	BoiteRangementHorizontal1->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum));

	// Bouton de demande de filtre C2 10747 nm
	//
	if( (Bouton10747=new (std::nothrow) QPushButton(BoiteRangementHorizontal4,"SupervCLIMSO-BoiteRangementHorizontal4-Bouton10747")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:Bouton10747 de la boite de rangement horizontal 4 de la fenetre principale." << std::endl;
	}
	Bouton10747->setPixmap(QPixmap(IconFiltreC2_10747_Inactif_xpm));
	Bouton10747->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(Bouton10747,QString::fromLocal8Bit("Tourner la roue à filtre de C2 jusqu'au filtre FeXIII 10747 nm"));

	// Bouton de demande de filtre C2 10770 nm
	//
	if( (Bouton10770=new (std::nothrow) QPushButton(BoiteRangementHorizontal4,"SupervCLIMSO-BoiteRangementHorizontal4-Bouton10770")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:Bouton10770 de la boite de rangement horizontal 4 de la fenetre principale." << std::endl;
	}
	Bouton10770->setPixmap(QPixmap(IconFiltreC2_10770_Inactif_xpm));
	Bouton10770->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(Bouton10770,QString::fromLocal8Bit("Tourner la roue à filtre de C2 jusqu'au filtre continuum FeXIII 10770 nm"));

	// Bouton de demande de filtre C2 10798 nm
	//
	if( (Bouton10798=new (std::nothrow) QPushButton(BoiteRangementHorizontal4,"SupervCLIMSO-BoiteRangementHorizontal4-Bouton10798")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:Bouton10798 de la boite de rangement horizontal 4 de la fenetre principale." << std::endl;
	}
	Bouton10798->setPixmap(QPixmap(IconFiltreC2_10798_Inactif_xpm));
	Bouton10798->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(Bouton10798,QString::fromLocal8Bit("Tourner la roue à filtre de C2 jusqu'au filtre FeXIII 10798 nm"));

	// Bouton de demande de filtre C2 10830 nm
	//
	if( (Bouton10830=new (std::nothrow) QPushButton(BoiteRangementHorizontal4,"SupervCLIMSO-BoiteRangementHorizontal4-Bouton10830")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:Bouton10830 de la boite de rangement horizontal 4 de la fenetre principale." << std::endl;
	}
	Bouton10830->setPixmap(QPixmap(IconFiltreC2_10830_Inactif_xpm));
	Bouton10830->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(Bouton10830,QString::fromLocal8Bit("Tourner la roue à filtre de C2 jusqu'au filtre HeI 10830 nm"));


	// Creation de la boite de rangement horizontal 5 de la boite de rangement vertical de la fenetre principale
	//
	// Cette boite contiendra les consignes pour l'observation
	//
	if( (BoiteRangementHorizontal5=new (std::nothrow) QHBox(BoiteRangementVertical,"SupervCLIMSO-BoiteRangementVertical-BoiteRangementHorizontal5")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BoiteRangementHorizontal5 de la boite de rangement vertical de la fenetre principale." << std::endl;
	}
	BoiteRangementHorizontal5->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum));

	for( i=0; i < AXE_PLATINE_X; i++ )
	{
		// Le label nom de l'axe
		//
		if( (LabelAxe[i]=new (std::nothrow) QLabel(BoiteRangementHorizontal5,QString("SupervCLIMSO-BoiteRangementHorizontal5-LabelAxe[%1]").arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLabel:LabelAxe[" << i << "] de la boite de rangement horizontal 5 de la fenetre principale." << std::endl;
		}
		LabelAxe[i]->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
		LabelAxe[i]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

		switch( i )
		{
			case AXE_ROUE_OUVERTURE:
				LabelAxe[i]->setFixedSize(TAILLE_X_LABEL_AXECODEUR,TAILLE_Y_LABEL_AXECODEUR);
				LabelAxe[i]->setText("Roue Ouverture:");
				break;
			case AXE_ROUE_FILTREC2:
				LabelAxe[i]->setFixedSize(TAILLE_X_LABEL_AXECODEUR,TAILLE_Y_LABEL_AXECODEUR);
				LabelAxe[i]->setText("Roue filtre C2:");
				break;
		}

		// LCD d'affichage de la position en points quadratures codeur
		//
		if( (LCDAxeCodeur[i]=new (std::nothrow) QLCDNumber(BoiteRangementHorizontal5,QString("SupervCLIMSO-BoiteRangementHorizontal5-LCDAxeCodeur[%1]").arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLCDNumber:LCDAxeCodeur[" << i << "] de la boite de rangement horizontal 5 de la fenetre principale." << std::endl;
		}
		LCDAxeCodeur[i]->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
		LCDAxeCodeur[i]->setFixedSize(TAILLE_X_LCD_AXECODEUR,TAILLE_Y_LCD_AXECODEUR);
		LCDAxeCodeur[i]->setSegmentStyle(QLCDNumber::Flat);
		LCDAxeCodeur[i]->display("");

		switch( i )
		{
			case AXE_ROUE_OUVERTURE:
				QToolTip::add(LCDAxeCodeur[i],QString::fromLocal8Bit("Position angulaire de la roue d'ouverture en incréments quadrature codeur"));
				break;

			case AXE_ROUE_FILTREC2:
				QToolTip::add(LCDAxeCodeur[i],QString::fromLocal8Bit("Position angulaire de la roue à filtre de C2 en incréments quadrature codeur"));
				break;
		}
	}

	for( i=AXE_PLATINE_X; i < NB_AXES; i++ )
	{
		// LCD d'affichage de la position en points quadratures codeur
		//
		if( (LCDAxeCodeur[i]=new (std::nothrow) QLCDNumber(BoiteRangementHorizontal5,QString("SupervCLIMSO-BoiteRangementHorizontal5-LCDAxeCodeur[%1]").arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLCDNumber:LCDAxeCodeur[" << i << "] de la boite de rangement horizontal 5 de la fenetre principale." << std::endl;
		}
		LCDAxeCodeur[i]->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
		LCDAxeCodeur[i]->setFixedSize(TAILLE_X_LCD_AXECODEUR,TAILLE_Y_LCD_AXECODEUR);
		LCDAxeCodeur[i]->setSegmentStyle(QLCDNumber::Flat);
		LCDAxeCodeur[i]->display("");

		switch( i )
		{
			case AXE_PLATINE_X:
				LCDAxeCodeur[i]->setNumDigits(8);
				LCDAxeCodeur[i]->setFixedSize(TAILLE_X_LCD_AXECODEUR_PLATINE,TAILLE_Y_LCD_AXECODEUR);
				QToolTip::add(LCDAxeCodeur[i],QString::fromLocal8Bit("Position de la platine X en incréments quadrature codeur"));

				// Creation du widget d'entree SpinBox de la consigne de decalage en x de C2
				//
				if( (SpinBoxDeltaXC2=new (std::nothrow) QSpinBox(VALMIN_DELTA_X_C2,VALMAX_DELTA_X_C2,VALINC_DELTA_X_C2,BoiteRangementHorizontal5,"SupervCLIMSO-BoiteRangementHorizontal5-SpinBoxDeltaXC2")) == NULL )
				{
					std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QSpinBox:SpinBoxDeltaXC2 de la boite de rangement horizontal 5 de la fenetre principale." << std::endl;
				}
				SpinBoxDeltaXC2->setPrefix("pX ");
				SpinBoxDeltaXC2->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
				SpinBoxDeltaXC2->setFixedSize(TAILLE_X_SPINBOX_AXECODEUR_PLATINE,TAILLE_Y_SPINBOX_AXECODEUR);
				SpinBoxDeltaXC2->setMinValue(VALMIN_DELTA_X_C2);
				SpinBoxDeltaXC2->setMaxValue(VALMAX_DELTA_X_C2);
				SpinBoxDeltaXC2->setLineStep(VALINC_DELTA_X_C2);
				SpinBoxDeltaXC2->setValue(0);
				SpinBoxDeltaXC2->setEnabled(false);
				QToolTip::add(SpinBoxDeltaXC2,QString::fromLocal8Bit("Changer le décalage angulaire sur l'ascension droite entre C1 et C2"));
				break;

			case AXE_PLATINE_Y:
				LCDAxeCodeur[i]->setNumDigits(8);
				LCDAxeCodeur[i]->setFixedSize(TAILLE_X_LCD_AXECODEUR_PLATINE,TAILLE_Y_LCD_AXECODEUR);
				QToolTip::add(LCDAxeCodeur[i],QString::fromLocal8Bit("Position de la platine Y en incréments quadrature codeur"));

				// Creation du widget d'entree SpinBox de la consigne de decalage en y de C2
				//
				if( (SpinBoxDeltaYC2=new (std::nothrow) QSpinBox(VALMIN_DELTA_Y_C2,VALMAX_DELTA_Y_C2,VALINC_DELTA_Y_C2,BoiteRangementHorizontal5,"SupervCLIMSO-BoiteRangementHorizontal5-SpinBoxDeltaYC2")) == NULL )
				{
					std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QSpinBox:SpinBoxDeltaYC2 de la boite de rangement horizontal 5 de la fenetre principale." << std::endl;
				}
				SpinBoxDeltaYC2->setPrefix("pY ");
				SpinBoxDeltaYC2->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
				SpinBoxDeltaYC2->setFixedSize(TAILLE_X_SPINBOX_AXECODEUR_PLATINE,TAILLE_Y_SPINBOX_AXECODEUR);
				SpinBoxDeltaYC2->setMinValue(VALMIN_DELTA_Y_C2);
				SpinBoxDeltaYC2->setMaxValue(VALMAX_DELTA_Y_C2);
				SpinBoxDeltaYC2->setLineStep(VALINC_DELTA_Y_C2);
				SpinBoxDeltaYC2->setValue(0);
				SpinBoxDeltaYC2->setEnabled(false);
				QToolTip::add(SpinBoxDeltaYC2,QString::fromLocal8Bit("Changer le décalage angulaire sur la déclinaison entre C1 et C2"));
				break;
		}

		// Le label nom de l'axe
		//
		if( (LabelAxe[i]=new (std::nothrow) QLabel(BoiteRangementHorizontal5,QString("SupervCLIMSO-BoiteRangementHorizontal5-LabelAxe[%1]").arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLabel:LabelAxe[" << i << "] de la boite de rangement horizontal 5 de la fenetre principale." << std::endl;
		}
		LabelAxe[i]->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
		LabelAxe[i]->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

		switch( i )
		{
			case AXE_PLATINE_X:
				LabelAxe[i]->setFixedSize(TAILLE_X_LABEL_AXECODEUR_PLATINE,TAILLE_Y_LABEL_AXECODEUR);
				LabelAxe[i]->setText("X  ");
				break;
			case AXE_PLATINE_Y:
				LabelAxe[i]->setFixedSize(TAILLE_X_LABEL_AXECODEUR_PLATINE,TAILLE_Y_LABEL_AXECODEUR);
				LabelAxe[i]->setText("Y  ");
				break;
		}

	}


	// Creation de la boite de rangement horizontal 6 de la boite de rangement vertical de la fenetre principale
	//
	// Cette boite contiendra les widgets de demande des sequences et des poses
	//
	if( (BoiteRangementHorizontal6=new (std::nothrow) QHBox(BoiteRangementVertical,"SupervCLIMSO-BoiteRangementVertical-BoiteRangementHorizontal6")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BoiteRangementHorizontal6 de la boite de rangement vertical de la fenetre principale." << std::endl;
	}
	BoiteRangementHorizontal6->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum));

	// 6a contient les poses unitaires
	//
	if( (BoiteRangementHorizontal6a=new (std::nothrow) QHBox(BoiteRangementHorizontal6,"SupervCLIMSO-BoiteRangementHorizontal6-BoiteRangementHorizontal6a")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BoiteRangementHorizontal6a de la boite de rangement horizontal 6 de la fenetre principale." << std::endl;
	}
	BoiteRangementHorizontal6a->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));

	if( (BoiteRangementVertical6a=new (std::nothrow) QVBox(BoiteRangementHorizontal6a,"SupervCLIMSO-BoiteRangementHorizontal6a-BoiteRangementVertical6a")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QVBox:BoiteRangementVertical6a de la boite de rangement horizontal 6a de la fenetre principale." << std::endl;
	}
	BoiteRangementVertical6a->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));

	if( (BoiteRangementHorizontal6aa=new (std::nothrow) QHBox(BoiteRangementVertical6a,"SupervCLIMSO-BoiteRangementVertical6a-BoiteRangementHorizontal6aa")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BoiteRangementHorizontal6aa de la boite de rangement vertical 6a." << std::endl;
	}
	BoiteRangementHorizontal6aa->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));

	if( (BoiteRangementHorizontal6ab=new (std::nothrow) QHBox(BoiteRangementVertical6a,"SupervCLIMSO-BoiteRangementVertical6a-BoiteRangementHorizontal6ab")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BoiteRangementHorizontal6ab de la boite de rangement vertical 6a." << std::endl;
	}
	BoiteRangementHorizontal6ab->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));

	if( (BoiteRangementHorizontal6ac=new (std::nothrow) QHBox(BoiteRangementVertical6a,"SupervCLIMSO-BoiteRangementVertical6a-BoiteRangementHorizontal6ac")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BoiteRangementHorizontal6ac de la boite de rangement vertical 6a." << std::endl;
	}
	BoiteRangementHorizontal6ac->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));

	if( (BoiteRangementHorizontal6ad=new (std::nothrow) QHBox(BoiteRangementVertical6a,"SupervCLIMSO-BoiteRangementVertical6a-BoiteRangementHorizontal6ad")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BoiteRangementHorizontal6ad de la boite de rangement vertical 6a." << std::endl;
	}
	BoiteRangementHorizontal6ad->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));


	// Bouton etat C1
	//
	if( (BoutonEtatC1=new (std::nothrow) QPushButton(BoiteRangementHorizontal6aa,"SupervCLIMSO-BoiteRangementHorizontal6aa-BoutonEtatC1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonEtatC1 de la boite de rangement horizontal 6aa." << std::endl;
	}
	BoutonEtatC1->setPixmap(QPixmap(IconC1Inactif_xpm));
	BoutonEtatC1->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(BoutonEtatC1,QString::fromLocal8Bit("Démarrer ou Arrêter le Coronographe C1 h-alpha de CLIMSO (CamerOA+TerminOA)"));

	// Bouton etat C2
	//
	if( (BoutonEtatC2=new (std::nothrow) QPushButton(BoiteRangementHorizontal6ab,"SupervCLIMSO-BoiteRangementHorizontal6ab-BoutonEtatC2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonEtatC2 de la boite de rangement horizontal 6ab." << std::endl;
	}
	BoutonEtatC2->setPixmap(QPixmap(IconC2Inactif_xpm));
	BoutonEtatC2->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(BoutonEtatC2,QString::fromLocal8Bit("Démarrer ou Arrêter le Coronographe C2 infrarouge de CLIMSO (CamerOA+TerminOA)"));

	// Bouton etat L1
	//
	if( (BoutonEtatL1=new (std::nothrow) QPushButton(BoiteRangementHorizontal6ac,"SupervCLIMSO-BoiteRangementHorizontal6ac-BoutonEtatL1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonEtatL1 de la boite de rangement horizontal 6ac." << std::endl;
	}
	BoutonEtatL1->setPixmap(QPixmap(IconL1Inactif_xpm));
	BoutonEtatL1->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(BoutonEtatL1,QString::fromLocal8Bit("Démarrer ou Arrêter la lunette SolarMax 90 h-alpha 0.5A de CLIMSO (CamerOA+TerminOA)"));

	// Bouton etat L2
	//
	if( (BoutonEtatL2=new (std::nothrow) QPushButton(BoiteRangementHorizontal6ad,"SupervCLIMSO-BoiteRangementHorizontal6ad-BoutonEtatL2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonEtatL2 de la boite de rangement horizontal 6ad." << std::endl;
	}
	BoutonEtatL2->setPixmap(QPixmap(IconL2Inactif_xpm));
	BoutonEtatL2->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(BoutonEtatL2,QString::fromLocal8Bit("Démarrer ou Arrêter la lunette SolarMax 90 CaK 2.2A de CLIMSO (CamerOA+TerminOA)"));

	// Boite de rangement vertical pour l'affichage des mesures physiques (temperature, puissance peltier) pour C1
	//
	if( (BRVMPCamerOAC1=new (std::nothrow) QVBox(BoiteRangementHorizontal6aa,"SupervCLIMSO-BoiteRangementHorizontal6aa-BRVMPCamerOAC1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QVBox:BRVMPCamerOAC1 de la boite de rangement horizontal 6aa." << std::endl;
	}

	// Boite de rangement vertical pour l'affichage des mesures physiques (temperature, puissance peltier) pour C2
	//
	if( (BRVMPCamerOAC2=new (std::nothrow) QVBox(BoiteRangementHorizontal6ab,"SupervCLIMSO-BoiteRangementHorizontal6aa-BRVMPCamerOAC2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QVBox:BRVMPCamerOAC2 de la boite de rangement horizontal 6aa." << std::endl;
	}

	// Boite de rangement vertical pour l'affichage des mesures physiques (temperature, puissance peltier) pour L1
	//
	if( (BRVMPCamerOAL1=new (std::nothrow) QVBox(BoiteRangementHorizontal6ac,"SupervCLIMSO-BoiteRangementHorizontal6aa-BRVMPCamerOAL1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QVBox:BRVMPCamerOAL1 de la boite de rangement horizontal 6aa." << std::endl;
	}

	// Boite de rangement vertical pour l'affichage des mesures physiques (temperature, puissance peltier) pour L2
	//
	if( (BRVMPCamerOAL2=new (std::nothrow) QVBox(BoiteRangementHorizontal6ad,"SupervCLIMSO-BoiteRangementHorizontal6aa-BRVMPCamerOAL2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QVBox:BRVMPCamerOAL2 de la boite de rangement horizontal 6aa." << std::endl;
	}

	// LCD d'affichage de la temperature de CamerOA C1
	//
	if( (LCDTempCamerOAC1=new (std::nothrow) QLCDNumber(BRVMPCamerOAC1,"SupervCLIMSO-BRVMPCamerOAC1-LCDTempCamerOAC1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLCDNumber:LCDTempCamerOAC1 de la boite de rangement vertical BRVMPCamerOAC1." << std::endl;
	}
	LCDTempCamerOAC1->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	LCDTempCamerOAC1->setFixedSize(TAILLE_X_LCD_MPCAMEROA,TAILLE_Y_LCD_MPCAMEROA);
	LCDTempCamerOAC1->setSmallDecimalPoint(false);
	LCDTempCamerOAC1->setSegmentStyle(QLCDNumber::Flat);
//	LCDTempCamerOAC1->setNumDigits(NB_DIGITS_LCD_TEMP_CAMEROA);
	LCDTempCamerOAC1->display("");
	QToolTip::add(LCDTempCamerOAC1,QString::fromLocal8Bit("Température de la matrice CCD de la caméra de C1 en °C"));

	// LCD d'affichage de la puissance peltier de CamerOA C1
	//
	if( (LCDPuiCamerOAC1=new (std::nothrow) QLCDNumber(BRVMPCamerOAC1,"SupervCLIMSO-BRVMPCamerOAC1-LCDPuiCamerOAC1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLCDNumber:LCDPuiCamerOAC1 de la boite de rangement vertical BRVMPCamerOAC1." << std::endl;
	}
	LCDPuiCamerOAC1->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	LCDPuiCamerOAC1->setFixedSize(TAILLE_X_LCD_MPCAMEROA,TAILLE_Y_LCD_MPCAMEROA);
	LCDPuiCamerOAC1->setSmallDecimalPoint(false);
	LCDPuiCamerOAC1->setSegmentStyle(QLCDNumber::Flat);
//	LCDPuiCamerOAC1->setNumDigits(NB_DIGITS_LCD_PUIPELTIER_CAMEROA);
	LCDPuiCamerOAC1->display("");
	QToolTip::add(LCDPuiCamerOAC1,QString::fromLocal8Bit("Puissance électrique d'alimentation des modules Peltier de la caméra de C1 (en % maxi)"));

	// LCD d'affichage de la temperature de CamerOA C2
	//
	if( (LCDTempCamerOAC2=new (std::nothrow) QLCDNumber(BRVMPCamerOAC2,"SupervCLIMSO-BRVMPCamerOAC2-LCDTempCamerOAC2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLCDNumber:LCDTempCamerOAC2 de la boite de rangement vertical BRVMPCamerOAC2." << std::endl;
	}
	LCDTempCamerOAC2->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	LCDTempCamerOAC2->setFixedSize(TAILLE_X_LCD_MPCAMEROA,TAILLE_Y_LCD_MPCAMEROA);
	LCDTempCamerOAC2->setSmallDecimalPoint(false);
	LCDTempCamerOAC2->setSegmentStyle(QLCDNumber::Flat);
//	LCDTempCamerOAC2->setNumDigits(NB_DIGITS_LCD_TEMP_CAMEROA);
	LCDTempCamerOAC2->display("");
	QToolTip::add(LCDTempCamerOAC2,QString::fromLocal8Bit("Température de la matrice CCD de la caméra de C2 en °C"));

	// LCD d'affichage de la puissance peltier de CamerOA C2
	//
	if( (LCDPuiCamerOAC2=new (std::nothrow) QLCDNumber(BRVMPCamerOAC2,"SupervCLIMSO-BRVMPCamerOAC2-LCDPuiCamerOAC2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLCDNumber:LCDPuiCamerOAC2 de la boite de rangement vertical BRVMPCamerOAC2." << std::endl;
	}
	LCDPuiCamerOAC2->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	LCDPuiCamerOAC2->setFixedSize(TAILLE_X_LCD_MPCAMEROA,TAILLE_Y_LCD_MPCAMEROA);
	LCDPuiCamerOAC2->setSmallDecimalPoint(false);
	LCDPuiCamerOAC2->setSegmentStyle(QLCDNumber::Flat);
//	LCDPuiCamerOAC2->setNumDigits(NB_DIGITS_LCD_PUIPELTIER_CAMEROA);
	LCDPuiCamerOAC2->display("");
	QToolTip::add(LCDPuiCamerOAC2,QString::fromLocal8Bit("Puissance électrique d'alimentation des modules Peltier de la caméra de C2 (en % maxi)"));

	// LCD d'affichage de la temperature de CamerOA L1
	//
	if( (LCDTempCamerOAL1=new (std::nothrow) QLCDNumber(BRVMPCamerOAL1,"SupervCLIMSO-BRVMPCamerOAL1-LCDTempCamerOAL1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLCDNumber:LCDTempCamerOAL1 de la boite de rangement vertical BRVMPCamerOAL1." << std::endl;
	}
	LCDTempCamerOAL1->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	LCDTempCamerOAL1->setFixedSize(TAILLE_X_LCD_MPCAMEROA,TAILLE_Y_LCD_MPCAMEROA);
	LCDTempCamerOAL1->setSmallDecimalPoint(false);
	LCDTempCamerOAL1->setSegmentStyle(QLCDNumber::Flat);
//	LCDTempCamerOAL1->setNumDigits(NB_DIGITS_LCD_TEMP_CAMEROA);
	LCDTempCamerOAL1->display("");
	QToolTip::add(LCDTempCamerOAL1,QString::fromLocal8Bit("Température de la matrice CCD de la caméra de L1 en °C"));

	// LCD d'affichage de la puissance peltier de CamerOA L1
	//
	if( (LCDPuiCamerOAL1=new (std::nothrow) QLCDNumber(BRVMPCamerOAL1,"SupervCLIMSO-BRVMPCamerOAL1-LCDPuiCamerOAL1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLCDNumber:LCDPuiCamerOAL1 de la boite de rangement vertical BRVMPCamerOAL1." << std::endl;
	}
	LCDPuiCamerOAL1->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	LCDPuiCamerOAL1->setFixedSize(TAILLE_X_LCD_MPCAMEROA,TAILLE_Y_LCD_MPCAMEROA);
	LCDPuiCamerOAL1->setSmallDecimalPoint(false);
	LCDPuiCamerOAL1->setSegmentStyle(QLCDNumber::Flat);
//	LCDPuiCamerOAL1->setNumDigits(NB_DIGITS_LCD_PUIPELTIER_CAMEROA);
	LCDPuiCamerOAL1->display("");
	QToolTip::add(LCDPuiCamerOAL1,QString::fromLocal8Bit("Puissance électrique d'alimentation des modules Peltier de la caméra de L1 (en % maxi)"));


	// LCD d'affichage de la temperature de CamerOA L2
	//
	if( (LCDTempCamerOAL2=new (std::nothrow) QLCDNumber(BRVMPCamerOAL2,"SupervCLIMSO-BRVMPCamerOAL2-LCDTempCamerOAL2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLCDNumber:LCDTempCamerOAL2 de la boite de rangement vertical BRVMPCamerOAL2." << std::endl;
	}
	LCDTempCamerOAL2->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	LCDTempCamerOAL2->setFixedSize(TAILLE_X_LCD_MPCAMEROA,TAILLE_Y_LCD_MPCAMEROA);
	LCDTempCamerOAL2->setSmallDecimalPoint(false);
	LCDTempCamerOAL2->setSegmentStyle(QLCDNumber::Flat);
//	LCDTempCamerOAL2->setNumDigits(NB_DIGITS_LCD_TEMP_CAMEROA);
	LCDTempCamerOAL2->display("");
	QToolTip::add(LCDTempCamerOAL2,QString::fromLocal8Bit("Température de la matrice CCD de la caméra de L2 en °C"));

	// LCD d'affichage de la puissance peltier de CamerOA L2
	//
	if( (LCDPuiCamerOAL2=new (std::nothrow) QLCDNumber(BRVMPCamerOAL2,"SupervCLIMSO-BRVMPCamerOAL2-LCDPuiCamerOAL2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLCDNumber:LCDPuiCamerOAL2 de la boite de rangement vertical BRVMPCamerOAL2." << std::endl;
	}
	LCDPuiCamerOAL2->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	LCDPuiCamerOAL2->setFixedSize(TAILLE_X_LCD_MPCAMEROA,TAILLE_Y_LCD_MPCAMEROA);
	LCDPuiCamerOAL2->setSmallDecimalPoint(false);
	LCDPuiCamerOAL2->setSegmentStyle(QLCDNumber::Flat);
//	LCDPuiCamerOAL2->setNumDigits(NB_DIGITS_LCD_PUIPELTIER_CAMEROA);
	LCDPuiCamerOAL2->display("");
	QToolTip::add(LCDPuiCamerOAL2,QString::fromLocal8Bit("Puissance électrique d'alimentation des modules Peltier de la caméra de L2 (en % maxi)"));

	// Bouton de demande de pose bias C1
	//
	if( (BoutonPoseBiasC1=new (std::nothrow) QPushButton(BoiteRangementHorizontal6aa,"SupervCLIMSO-BoiteRangementHorizontal6aa-BoutonPoseBiasC1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonPoseBiasC1 de la boite de rangement horizontal 6aa." << std::endl;
	}
	BoutonPoseBiasC1->setPixmap(QPixmap(IconPoseBias_xpm));
	BoutonPoseBiasC1->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(BoutonPoseBiasC1,QString::fromLocal8Bit("Déclencher une pose de type image de base (signal d'offset) sur la caméra de C1"));

	// Bouton de demande de pose bias C2
	//
	if( (BoutonPoseBiasC2=new (std::nothrow) QPushButton(BoiteRangementHorizontal6ab,"SupervCLIMSO-BoiteRangementHorizontal6ab-BoutonPoseBiasC2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonPoseBiasC2 de la boite de rangement horizontal 6ab." << std::endl;
	}
	BoutonPoseBiasC2->setPixmap(QPixmap(IconPoseBias_xpm));
	BoutonPoseBiasC2->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(BoutonPoseBiasC2,QString::fromLocal8Bit("Déclencher une pose de type image de base (signal d'offset) sur la caméra de C2"));

	// Bouton de demande de pose bias L1
	//
	if( (BoutonPoseBiasL1=new (std::nothrow) QPushButton(BoiteRangementHorizontal6ac,"SupervCLIMSO-BoiteRangementHorizontal6ac-BoutonPoseBiasL1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonPoseBiasL1 de la boite de rangement horizontal 6ac." << std::endl;
	}
	BoutonPoseBiasL1->setPixmap(QPixmap(IconPoseBias_xpm));
	BoutonPoseBiasL1->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(BoutonPoseBiasL1,QString::fromLocal8Bit("Déclencher une pose de type image de base (signal d'offset) sur la caméra de L1"));

	// Bouton de demande de pose bias L2
	//
	if( (BoutonPoseBiasL2=new (std::nothrow) QPushButton(BoiteRangementHorizontal6ad,"SupervCLIMSO-BoiteRangementHorizontal6ad-BoutonPoseBiasL2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonPoseBiasL2 de la boite de rangement horizontal 6ad." << std::endl;
	}
	BoutonPoseBiasL2->setPixmap(QPixmap(IconPoseBias_xpm));
	BoutonPoseBiasL2->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(BoutonPoseBiasL2,QString::fromLocal8Bit("Déclencher une pose de type image de base (signal d'offset) sur la caméra de L2"));

	// Bouton de demande de pose dark C1
	//
	if( (BoutonPoseDarkC1=new (std::nothrow) QPushButton(BoiteRangementHorizontal6aa,"SupervCLIMSO-BoiteRangementHorizontal6aa-BoutonPoseDarkC1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonPoseDarkC1 de la boite de rangement horizontal 6aa." << std::endl;
	}
	BoutonPoseDarkC1->setPixmap(QPixmap(IconPoseDark_xpm));
	BoutonPoseDarkC1->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(BoutonPoseDarkC1,QString::fromLocal8Bit("Déclencher une pose de type courant d'obscurité (DARK) sur la caméra de C1"));

	// Bouton de demande de pose dark C2
	//
	if( (BoutonPoseDarkC2=new (std::nothrow) QPushButton(BoiteRangementHorizontal6ab,"SupervCLIMSO-BoiteRangementHorizontal6ab-BoutonPoseDarkC2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonPoseDarkC2 de la boite de rangement horizontal 6ab." << std::endl;
	}
	BoutonPoseDarkC2->setPixmap(QPixmap(IconPoseDark_xpm));
	BoutonPoseDarkC2->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(BoutonPoseDarkC2,QString::fromLocal8Bit("Déclencher une pose de type courant d'obscurité (DARK) sur la caméra de C2"));

	// Bouton de demande de pose dark L1
	//
	if( (BoutonPoseDarkL1=new (std::nothrow) QPushButton(BoiteRangementHorizontal6ac,"SupervCLIMSO-BoiteRangementHorizontal6ac-BoutonPoseDarkL1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonPoseDarkL1 de la boite de rangement horizontal 6ac." << std::endl;
	}
	BoutonPoseDarkL1->setPixmap(QPixmap(IconPoseDark_xpm));
	BoutonPoseDarkL1->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(BoutonPoseDarkL1,QString::fromLocal8Bit("Déclencher une pose de type courant d'obscurité (DARK) sur la caméra de L1"));

	// Bouton de demande de pose bias L2
	//
	if( (BoutonPoseDarkL2=new (std::nothrow) QPushButton(BoiteRangementHorizontal6ad,"SupervCLIMSO-BoiteRangementHorizontal6ad-BoutonPoseDarkL2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonPoseDarkL2 de la boite de rangement horizontal 6ad." << std::endl;
	}
	BoutonPoseDarkL2->setPixmap(QPixmap(IconPoseDark_xpm));
	BoutonPoseDarkL2->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(BoutonPoseDarkL2,QString::fromLocal8Bit("Déclencher une pose de type courant d'obscurité (DARK) sur la caméra de L2"));

	// Bouton de demande de pose image C1
	//
	if( (BoutonPoseImageC1=new (std::nothrow) QPushButton(BoiteRangementHorizontal6aa,"SupervCLIMSO-BoiteRangementHorizontal6aa-BoutonPoseImageC1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonPoseImageC1 de la boite de rangement horizontal 6aa." << std::endl;
	}
	BoutonPoseImageC1->setPixmap(QPixmap(IconPoseImage_xpm));
	BoutonPoseImageC1->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(BoutonPoseImageC1,QString::fromLocal8Bit("Déclencher une pose de type PLU ou image (selon la position roue d'ouverture) sur la caméra de C1"));

	// Bouton de demande de pose image C2
	//
	if( (BoutonPoseImageC2=new (std::nothrow) QPushButton(BoiteRangementHorizontal6ab,"SupervCLIMSO-BoiteRangementHorizontal6ab-BoutonPoseImageC2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonPoseImageC2 de la boite de rangement horizontal 6ab." << std::endl;
	}
	BoutonPoseImageC2->setPixmap(QPixmap(IconPoseImage_xpm));
	BoutonPoseImageC2->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(BoutonPoseImageC2,QString::fromLocal8Bit("Déclencher une pose de type PLU ou image (selon la position roue d'ouverture) sur la caméra de C2"));

	// Bouton de demande de pose image L1
	//
	if( (BoutonPoseImageL1=new (std::nothrow) QPushButton(BoiteRangementHorizontal6ac,"SupervCLIMSO-BoiteRangementHorizontal6ac-BoutonPoseImageL1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonPoseImageL1 de la boite de rangement horizontal 6ac." << std::endl;
	}
	BoutonPoseImageL1->setPixmap(QPixmap(IconPoseImage_xpm));
	BoutonPoseImageL1->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(BoutonPoseImageL1,QString::fromLocal8Bit("Déclencher une pose de type PLU ou image (selon la position roue d'ouverture) sur la caméra de L1"));

	// Bouton de demande de pose image L2
	//
	if( (BoutonPoseImageL2=new (std::nothrow) QPushButton(BoiteRangementHorizontal6ad,"SupervCLIMSO-BoiteRangementHorizontal6ad-BoutonPoseImageL2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonPoseImageL2 de la boite de rangement horizontal 6ad." << std::endl;
	}
	BoutonPoseImageL2->setPixmap(QPixmap(IconPoseImage_xpm));
	BoutonPoseImageL2->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	QToolTip::add(BoutonPoseImageL2,QString::fromLocal8Bit("Déclencher une pose de type PLU ou image (selon la position roue d'ouverture) sur la caméra de L2"));


	// 6b contient les poses et sequences globales
	//
	if( (BoiteRangementHorizontal6b=new (std::nothrow) QHBox(BoiteRangementHorizontal6,"SupervCLIMSO-BoiteRangementHorizontal6-BoiteRangementHorizontal6b")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BoiteRangementHorizontal6b de la boite de rangement horizontal 6 de la fenetre principale." << std::endl;
	}
	BoiteRangementHorizontal6b->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));

	// Bouton de demande de poses Bias
	//
	if( (BoutonPosesBias=new (std::nothrow) QPushButton(BoiteRangementHorizontal6b,"SupervCLIMSO-BoiteRangementHorizontal6b-BoutonPosesBias")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonPosesBias de la boite de rangement horizontal 6b." << std::endl;
	}
	BoutonPosesBias->setPixmap(QPixmap(IconPosesBias_xpm));
	BoutonPosesBias->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	BoutonPosesBias->setFixedWidth(138);
	QToolTip::add(BoutonPosesBias,QString::fromLocal8Bit("Déclencher des poses de type image de base (signal d'offset) sur TOUS LES INSTRUMENTS de CLIMSO"));

	// Bouton de demande de poses Dark
	//
	if( (BoutonPosesDark=new (std::nothrow) QPushButton(BoiteRangementHorizontal6b,"SupervCLIMSO-BoiteRangementHorizontal6b-BoutonPosesDark")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonPosesDark de la boite de rangement horizontal 6b." << std::endl;
	}
	BoutonPosesDark->setPixmap(QPixmap(IconPosesDark_xpm));
	BoutonPosesDark->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	BoutonPosesDark->setFixedWidth(138);
	QToolTip::add(BoutonPosesDark,QString::fromLocal8Bit("Déclencher des poses de type courant d'obscurité (DARK) sur TOUS LES INSTRUMENTS de CLIMSO"));

	// Bouton de demande de sequence de poses images
	//
	if( (BoutonSequencePosesImages=new (std::nothrow) QPushButton(BoiteRangementHorizontal6b,"SupervCLIMSO-BoiteRangementHorizontal6b-BoutonSequencePosesImages")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonSequencePosesImages de la boite de rangement horizontal 6b." << std::endl;
	}
	BoutonSequencePosesImages->setPixmap(QPixmap(IconAcquisitionsPosesImages_xpm));
	BoutonSequencePosesImages->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	BoutonSequencePosesImages->setFixedWidth(270);
	QToolTip::add(BoutonSequencePosesImages,QString::fromLocal8Bit("Déclencher des poses de type PLU ou liste d'acquisitons d'images (selon la position roue d'ouverture) sur TOUS LES INSTRUMENTS de CLIMSO"));


	// Creation de la boite de rangement horizontal 7 de la boite de rangement vertical de la fenetre principale
	//
	// Cette boite contiendra les widgets de conditions des sequences d'acquisition des images
	//
	if( (BoiteRangementHorizontal7=new (std::nothrow) QHBox(BoiteRangementVertical,"SupervCLIMSO-BoiteRangementVertical-BoiteRangementHorizontal7")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BoiteRangementHorizontal7 de la boite de rangement vertical de la fenetre principale." << std::endl;
	}
	BoiteRangementHorizontal7->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum));

	// Label d'affichage de la designation des checkboxs d'acquisition automatique des instruments
	//
	if( (LabelCBAcqAuto=new (std::nothrow) QLabel(BoiteRangementHorizontal7,"SupervCLIMSO-BoiteRangementHorizontal7-LabelCBAcqAuto")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLabel:LabelCBAcqAuto de la boite de rangement horizontal 7." << std::endl;
	}
	LabelCBAcqAuto->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
	LabelCBAcqAuto->setPaletteBackgroundColor(COULEUR_LABEL_ACQUISITION);
	LabelCBAcqAuto->setText(QString::fromLocal8Bit(" Acquisition auto:"));

	// Les checkboxs d'acquisition automatique de chaque instrument
	//
	for( i=0; i < NB_CAMEROA; i++ )
	{
		if( (CBAcqAuto[i]=new (std::nothrow) QCheckBox(BoiteRangementHorizontal7,QString("SupervCLIMSO-BoiteRangementHorizontal7-CBAcqAuto[%1]").arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QCheckBox:CBAcqAuto[" << i << "] de la boite de rangement horizontal 7." << std::endl;
		}
		CBAcqAuto[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		CBAcqAuto[i]->setText(QString::fromLocal8Bit(InstrumentCLIMSO[i]));
		CBAcqAuto[i]->setDown(false);
		CBAcqAuto[i]->setChecked(false);

		switch( i )
		{
			case CAMEROA_C1:
				QToolTip::add(CBAcqAuto[i],QString::fromLocal8Bit("C1 en mode d'acquisition automatique ou en mode d'acquisition manuelle"));
				break;
			case CAMEROA_C2:
				QToolTip::add(CBAcqAuto[i],QString::fromLocal8Bit("C2 en mode d'acquisition automatique ou en mode d'acquisition manuelle"));
				break;
			case CAMEROA_L1:
				QToolTip::add(CBAcqAuto[i],QString::fromLocal8Bit("L1 en mode d'acquisition automatique ou en mode d'acquisition manuelle"));
				break;
			case CAMEROA_L2:
				QToolTip::add(CBAcqAuto[i],QString::fromLocal8Bit("L2 en mode d'acquisition automatique ou en mode d'acquisition manuelle"));
				break;
		}
	}

	// Label d'affichage de la designation des sequences d'acquisition pour chaque instrument
	//
	if( (LabelCompoSeqAcq=new (std::nothrow) QLabel(BoiteRangementHorizontal7,"SupervCLIMSO-BoiteRangementHorizontal7-LabelCompoSeqAcq")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLabel:LabelCompoSeqAcq de la boite de rangement horizontal 7." << std::endl;
	}
	LabelCompoSeqAcq->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
	LabelCompoSeqAcq->setPaletteBackgroundColor(COULEUR_LABEL_ACQUISITION);
	LabelCompoSeqAcq->setText(QString::fromLocal8Bit("   Composition acquisitions:"));

	// Les checkboxs de la composition des sequences d'acquisition
	//
	for( i=0; i < NB_TYPES_ACQUISITIONS; i++ )
	{
		if( (CBCompoSeqAcq[i]=new (std::nothrow) QCheckBox(BoiteRangementHorizontal7,QString("SupervCLIMSO-BoiteRangementHorizontal7-CBCompoSeqAcq[%1]").arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QCheckBox:CBCompoSeqAcq[" << i << "] de la boite de rangement horizontal 7." << std::endl;
		}
		CBCompoSeqAcq[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		CBCompoSeqAcq[i]->setText(QString::fromLocal8Bit(DesignationTypesAcq[i]));
		CBCompoSeqAcq[i]->setDown(false);
		CBCompoSeqAcq[i]->setChecked(true);
		QToolTip::add(CBCompoSeqAcq[i],QString::fromLocal8Bit("Ajouter ce type de pose dans la liste des acquisitions"));
	}

	// On invalide certaines expositions dans la liste de la serie des aquisitions
	//
	CBCompoSeqAcq[ACQUISITION_C2_10747]->setChecked(false);
	CBCompoSeqAcq[ACQUISITION_C2_10770]->setChecked(false);
	CBCompoSeqAcq[ACQUISITION_C2_10798]->setChecked(false);
	CBCompoSeqAcq[ACQUISITION_L1_COUR]->setChecked(false);
	CBCompoSeqAcq[ACQUISITION_L2_COUR]->setChecked(false);

	// Creation de la boite de rangement horizontal 8 de la boite de rangement vertical de la fenetre principale
	//
	// Cette boite contiendra les widgets de suppression des dernieres images sur le disque dur et les boutons de transfert vers BASS2000
	//
	if( (BoiteRangementHorizontal8=new (std::nothrow) QHBox(BoiteRangementVertical,"SupervCLIMSO-BoiteRangementVertical-BoiteRangementHorizontal8")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BoiteRangementHorizontal8 de la boite de rangement vertical de la fenetre principale." << std::endl;
	}
	BoiteRangementHorizontal8->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum));

	// Label d'affichage du temps passe depuis la derniere image acquise par C1
	//
	if( (TempsDepuisDerImgC1=new (std::nothrow) QLabel(BoiteRangementHorizontal8,"SupervCLIMSO-BoiteRangementHorizontal8-TempsDepuisDerImgC1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLabel:TempsDepuisDerImgC1 de la boite de rangement horizontal 8." << std::endl;
	}
	TempsDepuisDerImgC1->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
	TempsDepuisDerImgC1->setMinimumSize(TAILLE_X_LABEL_TEMPS_ECOULE_DER_IMG+1,TAILLE_Y_LABEL_TEMPS_ECOULE_DER_IMG);
	TempsDepuisDerImgC1->setMaximumSize(TAILLE_X_LABEL_TEMPS_ECOULE_DER_IMG+1,TAILLE_Y_LABEL_TEMPS_ECOULE_DER_IMG);
	TempsDepuisDerImgC1->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	TempsDepuisDerImgC1->setText(QString::fromLocal8Bit("aucune image"));
	QToolTip::add(TempsDepuisDerImgC1,QString::fromLocal8Bit("Heure d'acquisition de la dernière pose de C1 > Temps écoulé depuis la dernière pose de C1"));

	// Bouton de demande de suppression de la derniere image acquise par C1
	//
	if( (BoutonSuppressionDerImgC1=new (std::nothrow) QPushButton(BoiteRangementHorizontal8,"SupervCLIMSO-BoiteRangementHorizontal8-BoutonSuppressionDerImgC1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonSuppressionDerImgC1 de la boite de rangement horizontal 8." << std::endl;
	}
	BoutonSuppressionDerImgC1->setPixmap(QPixmap(IconSupprDerImgC1_xpm));
	BoutonSuppressionDerImgC1->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	BoutonSuppressionDerImgC1->setFixedWidth(TAILLE_X_BOUTONS_SUPPR_ET_BASS);
	BoutonSuppressionDerImgC1->setPalette(PaletteBoutonOrangee);
	QToolTip::add(BoutonSuppressionDerImgC1,QString::fromLocal8Bit("Supprimer la dernière image acquise avec C1"));

	// Label d'affichage du temps passe depuis la derniere image acquise par C2
	//
	if( (TempsDepuisDerImgC2=new (std::nothrow) QLabel(BoiteRangementHorizontal8,"SupervCLIMSO-BoiteRangementHorizontal8-TempsDepuisDerImgC2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLabel:TempsDepuisDerImgC2 de la boite de rangement horizontal 8." << std::endl;
	}
	TempsDepuisDerImgC2->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
	TempsDepuisDerImgC2->setMinimumSize(TAILLE_X_LABEL_TEMPS_ECOULE_DER_IMG,TAILLE_Y_LABEL_TEMPS_ECOULE_DER_IMG);
	TempsDepuisDerImgC2->setMaximumSize(TAILLE_X_LABEL_TEMPS_ECOULE_DER_IMG,TAILLE_Y_LABEL_TEMPS_ECOULE_DER_IMG);
	TempsDepuisDerImgC2->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	TempsDepuisDerImgC2->setText(QString::fromLocal8Bit("aucune image"));
	QToolTip::add(TempsDepuisDerImgC2,QString::fromLocal8Bit("Heure d'acquisition de la dernière pose de C2 > Temps écoulé depuis la dernière pose de C2"));

	// Bouton de demande de suppression de la derniere image acquise par C2
	//
	if( (BoutonSuppressionDerImgC2=new (std::nothrow) QPushButton(BoiteRangementHorizontal8,"SupervCLIMSO-BoiteRangementHorizontal8-BoutonSuppressionDerImgC2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonSuppressionDerImgC2 de la boite de rangement horizontal 8." << std::endl;
	}
	BoutonSuppressionDerImgC2->setPixmap(QPixmap(IconSupprDerImgC2_xpm));
	BoutonSuppressionDerImgC2->setFixedWidth(TAILLE_X_BOUTONS_SUPPR_ET_BASS);
	BoutonSuppressionDerImgC2->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	BoutonSuppressionDerImgC2->setPalette(PaletteBoutonOrangee);
	QToolTip::add(BoutonSuppressionDerImgC2,QString::fromLocal8Bit("Supprimer la dernière image acquise avec C2"));

	// Label d'affichage du temps passe depuis la derniere image acquise par L1
	//
	if( (TempsDepuisDerImgL1=new (std::nothrow) QLabel(BoiteRangementHorizontal8,"SupervCLIMSO-BoiteRangementHorizontal8-TempsDepuisDerImgL1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLabel:TempsDepuisDerImgL1 de la boite de rangement horizontal 8." << std::endl;
	}
	TempsDepuisDerImgL1->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
	TempsDepuisDerImgL1->setMinimumSize(TAILLE_X_LABEL_TEMPS_ECOULE_DER_IMG,TAILLE_Y_LABEL_TEMPS_ECOULE_DER_IMG);
	TempsDepuisDerImgL1->setMaximumSize(TAILLE_X_LABEL_TEMPS_ECOULE_DER_IMG,TAILLE_Y_LABEL_TEMPS_ECOULE_DER_IMG);
	TempsDepuisDerImgL1->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	TempsDepuisDerImgL1->setText(QString::fromLocal8Bit("aucune image"));
	QToolTip::add(TempsDepuisDerImgL1,QString::fromLocal8Bit("Heure d'acquisition de la dernière pose de L1 > Temps écoulé depuis la dernière pose de L1"));

	// Bouton de demande de suppression de la derniere image acquise par L1
	//
	if( (BoutonSuppressionDerImgL1=new (std::nothrow) QPushButton(BoiteRangementHorizontal8,"SupervCLIMSO-BoiteRangementHorizontal8-BoutonSuppressionDerImgL1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonSuppressionDerImgL1 de la boite de rangement horizontal 8." << std::endl;
	}
	BoutonSuppressionDerImgL1->setPixmap(QPixmap(IconSupprDerImgL1_xpm));
	BoutonSuppressionDerImgL1->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	BoutonSuppressionDerImgL1->setFixedWidth(TAILLE_X_BOUTONS_SUPPR_ET_BASS);
	BoutonSuppressionDerImgL1->setPalette(PaletteBoutonOrangee);
	QToolTip::add(BoutonSuppressionDerImgL1,QString::fromLocal8Bit("Supprimer la dernière image acquise avec L1"));

	// Label d'affichage du temps passe depuis la derniere image acquise par L2
	//
	if( (TempsDepuisDerImgL2=new (std::nothrow) QLabel(BoiteRangementHorizontal8,"SupervCLIMSO-BoiteRangementHorizontal8-TempsDepuisDerImgL2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLabel:TempsDepuisDerImgL2 de la boite de rangement horizontal 8." << std::endl;
	}
	TempsDepuisDerImgL2->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
	TempsDepuisDerImgL2->setMinimumSize(TAILLE_X_LABEL_TEMPS_ECOULE_DER_IMG,TAILLE_Y_LABEL_TEMPS_ECOULE_DER_IMG);
	TempsDepuisDerImgL2->setMaximumSize(TAILLE_X_LABEL_TEMPS_ECOULE_DER_IMG,TAILLE_Y_LABEL_TEMPS_ECOULE_DER_IMG);
	TempsDepuisDerImgL2->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	TempsDepuisDerImgL2->setText(QString::fromLocal8Bit("aucune image"));
	QToolTip::add(TempsDepuisDerImgL2,QString::fromLocal8Bit("Heure d'acquisition de la dernière pose de L2 > Temps écoulé depuis la dernière pose de L2"));

	// Bouton de demande de suppression de la derniere image acquise par L2
	//
	if( (BoutonSuppressionDerImgL2=new (std::nothrow) QPushButton(BoiteRangementHorizontal8,"SupervCLIMSO-BoiteRangementHorizontal8-BoutonSuppressionDerImgL2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonSuppressionDerImgL2 de la boite de rangement horizontal 8." << std::endl;
	}
	BoutonSuppressionDerImgL2->setPixmap(QPixmap(IconSupprDerImgL2_xpm));
	BoutonSuppressionDerImgL2->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	BoutonSuppressionDerImgL2->setFixedWidth(TAILLE_X_BOUTONS_SUPPR_ET_BASS);
	BoutonSuppressionDerImgL2->setPalette(PaletteBoutonOrangee);
	QToolTip::add(BoutonSuppressionDerImgL2,QString::fromLocal8Bit("Supprimer la dernière image acquise avec L2"));

	// Bouton de demande de transfert de la derniere image acquise par C1
	//
	if( (BoutonTransfertBASS2000C1=new (std::nothrow) QPushButton(BoiteRangementHorizontal8,"SupervCLIMSO-BoiteRangementHorizontal8-BoutonTransfertBASS2000C1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonTransfertBASS2000C1 de la boite de rangement horizontal 8." << std::endl;
	}
	BoutonTransfertBASS2000C1->setPixmap(QPixmap(IconTransfertBASS2000C1_xpm));
	BoutonTransfertBASS2000C1->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	BoutonTransfertBASS2000C1->setFixedWidth(TAILLE_X_BOUTONS_SUPPR_ET_BASS);
	BoutonTransfertBASS2000C1->setPalette(PaletteBoutonOrangee);
	QToolTip::add(BoutonTransfertBASS2000C1,QString::fromLocal8Bit("Transférer et publier la dernière acquisition de C1 sur BASS2000"));

	// Bouton de demande de transfert de la derniere image acquise par C2
	//
	if( (BoutonTransfertBASS2000C2=new (std::nothrow) QPushButton(BoiteRangementHorizontal8,"SupervCLIMSO-BoiteRangementHorizontal8-BoutonTransfertBASS2000C2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonTransfertBASS2000C2 de la boite de rangement horizontal 8." << std::endl;
	}
	BoutonTransfertBASS2000C2->setPixmap(QPixmap(IconTransfertBASS2000C2_xpm));
	BoutonTransfertBASS2000C2->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	BoutonTransfertBASS2000C2->setFixedWidth(TAILLE_X_BOUTONS_SUPPR_ET_BASS);
	BoutonTransfertBASS2000C2->setPalette(PaletteBoutonOrangee);
	QToolTip::add(BoutonTransfertBASS2000C2,QString::fromLocal8Bit("Transférer et publier la dernière acquisition de C2 sur BASS2000"));

	// Bouton de demande de transfert de la derniere image acquise par L1
	//
	if( (BoutonTransfertBASS2000L1=new (std::nothrow) QPushButton(BoiteRangementHorizontal8,"SupervCLIMSO-BoiteRangementHorizontal8-BoutonTransfertBASS2000L1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonTransfertBASS2000L1 de la boite de rangement horizontal 8." << std::endl;
	}
	BoutonTransfertBASS2000L1->setPixmap(QPixmap(IconTransfertBASS2000L1_xpm));
	BoutonTransfertBASS2000L1->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	BoutonTransfertBASS2000L1->setFixedWidth(TAILLE_X_BOUTONS_SUPPR_ET_BASS);
	BoutonTransfertBASS2000L1->setPalette(PaletteBoutonOrangee);
	QToolTip::add(BoutonTransfertBASS2000L1,QString::fromLocal8Bit("Transférer et publier la dernière acquisition de L1 sur BASS2000"));

	// Bouton de demande de transfert de la derniere image acquise par L2
	//
	if( (BoutonTransfertBASS2000L2=new (std::nothrow) QPushButton(BoiteRangementHorizontal8,"SupervCLIMSO-BoiteRangementHorizontal8-BoutonTransfertBASS2000L2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonTransfertBASS2000L2 de la boite de rangement horizontal 8." << std::endl;
	}
	BoutonTransfertBASS2000L2->setPixmap(QPixmap(IconTransfertBASS2000L2_xpm));
	BoutonTransfertBASS2000L2->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
	BoutonTransfertBASS2000L2->setFixedWidth(TAILLE_X_BOUTONS_SUPPR_ET_BASS);
	BoutonTransfertBASS2000L2->setPalette(PaletteBoutonOrangee);
	QToolTip::add(BoutonTransfertBASS2000L2,QString::fromLocal8Bit("Transférer et publier la dernière acquisition de L2 sur BASS2000"));


	// Creation du widget de barre horizontale pour presenter des informations de status
	//
	if( (BarreStatus=new (std::nothrow) QStatusBar(BoiteRangementVertical,"SupervCLIMSO-BoiteRangementVertical-BarreStatus")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QStatusBar:BarreStatus de la fenetre principale KMainWindow." << std::endl;
	}
	
	// La barre de status a une dimension verticale fixe (celle de sa creation)
	//
	BarreStatus->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed));

	// Creation du widget label d'affichage de l'heure UT ajoute a la barre de status
	//
	if( (LabelHeureUTBarreStatus=new (std::nothrow) QLabel("0000-00-00 00:00:00 UT",this,"SupervCLIMSO-KMainWindow-LabelHeureUTBarreStatus")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLabel:LabelHeureUTBarreStatus de la barre de status de la fenetre principale KMainWindow." << std::endl;
	}
	LabelHeureUTBarreStatus->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));


	// On ajoute les widgets a la barre de status
	//
	BarreStatus->addWidget(LabelHeureUTBarreStatus,0,TRUE);


	// Creation du timer de pulsation de la seconde de temps
	//
	if( (Pulsar1s=new (std::nothrow) QTimer(this,"SupervCLIMSO-KMainWindow-Pulsar1s")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le timer QTimer:Pulsar1s de la fenetre principale KMainWindow." << std::endl;
	}
	
	// Connexion du signal timeout() envoye par le timer au slot SlotPulsar1s() de l'objet
	//
	connect(Pulsar1s,SIGNAL(timeout()),this,SLOT(SlotPulsar1s()));

	// Connexion des boutons de la fenetre principale avec leur slot
	//
	connect(BoutonInitialisationAxes,SIGNAL(clicked()),this,SLOT(SlotBoutonInitialisationAxes()));
	connect(BoutonConsignes,SIGNAL(clicked()),this,SLOT(SlotBoutonConsignes()));
	connect(BoutonModePointage,SIGNAL(clicked()),this,SLOT(SlotBoutonModePointage()));
	connect(BoutonModePLU,SIGNAL(clicked()),this,SLOT(SlotBoutonModePLU()));
	connect(BoutonModeCalibration,SIGNAL(clicked()),this,SLOT(SlotBoutonModeCalibration()));
	connect(BoutonModeObservation,SIGNAL(clicked()),this,SLOT(SlotBoutonModeObservation()));
	connect(Bouton10747,SIGNAL(clicked()),this,SLOT(SlotBouton10747()));
	connect(Bouton10770,SIGNAL(clicked()),this,SLOT(SlotBouton10770()));
	connect(Bouton10798,SIGNAL(clicked()),this,SLOT(SlotBouton10798()));
	connect(Bouton10830,SIGNAL(clicked()),this,SLOT(SlotBouton10830()));
	connect(SpinBoxDeltaXC2,SIGNAL(valueChanged(int)),this,SLOT(SlotSpinBoxDeltaXC2(int)));
	connect(SpinBoxDeltaYC2,SIGNAL(valueChanged(int)),this,SLOT(SlotSpinBoxDeltaYC2(int)));
	connect(BoutonPoseImageC1,SIGNAL(clicked()),this,SLOT(SlotBoutonPoseImageC1()));
	connect(BoutonPoseImageC2,SIGNAL(clicked()),this,SLOT(SlotBoutonPoseImageC2()));
	connect(BoutonPoseImageL1,SIGNAL(clicked()),this,SLOT(SlotBoutonPoseImageL1()));
	connect(BoutonPoseImageL2,SIGNAL(clicked()),this,SLOT(SlotBoutonPoseImageL2()));
	connect(BoutonPoseBiasC1,SIGNAL(clicked()),this,SLOT(SlotBoutonPoseBiasC1()));
	connect(BoutonPoseBiasC2,SIGNAL(clicked()),this,SLOT(SlotBoutonPoseBiasC2()));
	connect(BoutonPoseBiasL1,SIGNAL(clicked()),this,SLOT(SlotBoutonPoseBiasL1()));
	connect(BoutonPoseBiasL2,SIGNAL(clicked()),this,SLOT(SlotBoutonPoseBiasL2()));
	connect(BoutonPoseDarkC1,SIGNAL(clicked()),this,SLOT(SlotBoutonPoseDarkC1()));
	connect(BoutonPoseDarkC2,SIGNAL(clicked()),this,SLOT(SlotBoutonPoseDarkC2()));
	connect(BoutonPoseDarkL1,SIGNAL(clicked()),this,SLOT(SlotBoutonPoseDarkL1()));
	connect(BoutonPoseDarkL2,SIGNAL(clicked()),this,SLOT(SlotBoutonPoseDarkL2()));
	connect(BoutonEtatC1,SIGNAL(clicked()),this,SLOT(SlotBoutonEtatC1()));
	connect(BoutonEtatC2,SIGNAL(clicked()),this,SLOT(SlotBoutonEtatC2()));
	connect(BoutonEtatL1,SIGNAL(clicked()),this,SLOT(SlotBoutonEtatL1()));
	connect(BoutonEtatL2,SIGNAL(clicked()),this,SLOT(SlotBoutonEtatL2()));
	connect(BoutonPosesBias,SIGNAL(clicked()),this,SLOT(SlotBoutonPosesBias()));
	connect(BoutonPosesDark,SIGNAL(clicked()),this,SLOT(SlotBoutonPosesDark()));
	connect(BoutonSequencePosesImages,SIGNAL(clicked()),this,SLOT(SlotBoutonSequencePosesImages()));
	connect(BoutonSuppressionDerImgC1,SIGNAL(clicked()),this,SLOT(SlotBoutonSuppressionDerImgC1()));
	connect(BoutonSuppressionDerImgC2,SIGNAL(clicked()),this,SLOT(SlotBoutonSuppressionDerImgC2()));
	connect(BoutonSuppressionDerImgL1,SIGNAL(clicked()),this,SLOT(SlotBoutonSuppressionDerImgL1()));
	connect(BoutonSuppressionDerImgL2,SIGNAL(clicked()),this,SLOT(SlotBoutonSuppressionDerImgL2()));
	connect(BoutonTransfertBASS2000C1,SIGNAL(clicked()),this,SLOT(SlotBoutonTransfertBASS2000C1()));
	connect(BoutonTransfertBASS2000C2,SIGNAL(clicked()),this,SLOT(SlotBoutonTransfertBASS2000C2()));
	connect(BoutonTransfertBASS2000L1,SIGNAL(clicked()),this,SLOT(SlotBoutonTransfertBASS2000L1()));
	connect(BoutonTransfertBASS2000L2,SIGNAL(clicked()),this,SLOT(SlotBoutonTransfertBASS2000L2()));
	connect(CBAcqAuto[CAMEROA_C1],SIGNAL(pressed()),this,SLOT(SlotCBAcqAutoC1()));
	connect(CBAcqAuto[CAMEROA_C2],SIGNAL(pressed()),this,SLOT(SlotCBAcqAutoC2()));
	connect(CBAcqAuto[CAMEROA_L1],SIGNAL(pressed()),this,SLOT(SlotCBAcqAutoL1()));
	connect(CBAcqAuto[CAMEROA_L2],SIGNAL(pressed()),this,SLOT(SlotCBAcqAutoL2()));
	connect(CBCompoSeqAcq[ACQUISITION_C1_COUR],SIGNAL(pressed()),this,SLOT(SlotCBCompoSeqAcqC1()));
	connect(CBCompoSeqAcq[ACQUISITION_C2_10747],SIGNAL(pressed()),this,SLOT(SlotCBCompoSeqAcqC2_10747()));
	connect(CBCompoSeqAcq[ACQUISITION_C2_10770],SIGNAL(pressed()),this,SLOT(SlotCBCompoSeqAcqC2_10770()));
	connect(CBCompoSeqAcq[ACQUISITION_C2_10798],SIGNAL(pressed()),this,SLOT(SlotCBCompoSeqAcqC2_10798()));
	connect(CBCompoSeqAcq[ACQUISITION_C2_10830],SIGNAL(pressed()),this,SLOT(SlotCBCompoSeqAcqC2_10830()));
	connect(CBCompoSeqAcq[ACQUISITION_L1_SURF],SIGNAL(pressed()),this,SLOT(SlotCBCompoSeqAcqL1S()));
	connect(CBCompoSeqAcq[ACQUISITION_L1_COUR],SIGNAL(pressed()),this,SLOT(SlotCBCompoSeqAcqL1C()));
	connect(CBCompoSeqAcq[ACQUISITION_L2_SURF],SIGNAL(pressed()),this,SLOT(SlotCBCompoSeqAcqL2S()));
	connect(CBCompoSeqAcq[ACQUISITION_L2_COUR],SIGNAL(pressed()),this,SLOT(SlotCBCompoSeqAcqL2C()));

	// XXX On désactive certains éléments pour ne pas affecter la roue à filtre
	//Bouton10798->setEnabled(false);
	//Bouton10770->setEnabled(false);
	//Bouton10747->setEnabled(false);
	
	// XXX On désactive les platines X et Y
	//SpinBoxDeltaXC2->setEnabled(false);
	//SpinBoxDeltaYC2->setEnabled(false);

	// Demarrage du timer
	//
	Pulsar1s->start(1000,FALSE);


	// Widgets de la fenetre de saisie des consignes ----------------------------------------------------------------------------------

	// La fenetre de saisie des consignes en mode modeless (independante de la fenetre principale de l'application, non bloquante
	//  sur les entrees (non modale))
	//
	// On n'utilise pas une QMainWindow ou une QDockWindow car il n'y a pas besoin de menu, barre d'outils, ancre, barre de status...
	//
	if( (FenetreConsignes=new (std::nothrow) QDialog(this,"SupervCLIMSO-QDialog-FenetreConsignes",FALSE,Qt::WType_TopLevel | Qt::WStyle_Customize | Qt::WStyle_DialogBorder)) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QDialog:FenetreConsignes de la fenetre principale KMainWindow." << std::endl;
	}
	FenetreConsignes->setCaption(QString::fromLocal8Bit("SupervCLIMSO : Saisie des consignes"));
	FenetreConsignes->setMinimumSize(TAILLE_X_LABEL_CONSIGNE+TAILLE_X_EDIT_CONSIGNE,TAILLE_Y_LABEL_CONSIGNE*NB_CONSIGNES);
	FenetreConsignes->setMaximumSize(TAILLE_X_LABEL_CONSIGNE+TAILLE_X_EDIT_CONSIGNE,TAILLE_Y_LABEL_CONSIGNE*NB_CONSIGNES);

	// Boite de rangement vertical dans la fenetre de saisie des consignes
	//
	if( (BRVFenetreConsignes=new (std::nothrow) QVBox(FenetreConsignes,"SupervCLIMSO-QVBox-BRVFenetreConsignes")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QVBox:BRVFenetreConsignes de la fenetre FenetreCamerOA." << std::endl;
	}
	BRVFenetreConsignes->setMinimumSize(TAILLE_X_LABEL_CONSIGNE+TAILLE_X_EDIT_CONSIGNE,TAILLE_Y_LABEL_CONSIGNE*NB_CONSIGNES);
	BRVFenetreConsignes->setMaximumSize(TAILLE_X_LABEL_CONSIGNE+TAILLE_X_EDIT_CONSIGNE,TAILLE_Y_LABEL_CONSIGNE*NB_CONSIGNES);

	// Boite de rangement horizontal de chaque consigne
	//
	for( i=0; i < NB_CONSIGNES; i++ )
	{
		if( (BRHFenetreConsignes[i]=new (std::nothrow) QHBox(BRVFenetreConsignes,QString("SupervCLIMSO-QHBox-BRHFenetreConsignes[%1]").arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BRHFenetreConsignes[" << i << "] de la fenetre FenetreConsignes." << std::endl;
		}
		BRHFenetreConsignes[i]->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
		BRHFenetreConsignes[i]->setMinimumSize(TAILLE_X_LABEL_CONSIGNE+TAILLE_X_EDIT_CONSIGNE,TAILLE_Y_LABEL_CONSIGNE);
		BRHFenetreConsignes[i]->setMaximumSize(TAILLE_X_LABEL_CONSIGNE+TAILLE_X_EDIT_CONSIGNE,TAILLE_Y_LABEL_CONSIGNE);

		// Creation du label de la consigne
		//
		if( (LabelConsigne[i]=new (std::nothrow) QLabel(BRHFenetreConsignes[i],QString("SupervCLIMSO-BRHFenetreConsignes[%1]-LabelConsigne[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLabel:LabelConsigne[" << i << "] de BRHFenetreConsignes[" << i << "]." << std::endl;
		}
		LabelConsigne[i]->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
		LabelConsigne[i]->setMinimumSize(TAILLE_X_LABEL_CONSIGNE,TAILLE_Y_LABEL_CONSIGNE);
		LabelConsigne[i]->setMaximumSize(TAILLE_X_LABEL_CONSIGNE,TAILLE_Y_LABEL_CONSIGNE);
		if( i % 2 == 0 ) LabelConsigne[i]->setPaletteBackgroundColor(COULEUR_LIGNE_CONSIGNE_0); else LabelConsigne[i]->setPaletteBackgroundColor(COULEUR_LIGNE_CONSIGNE_1);
		LabelConsigne[i]->setText(QString::fromLocal8Bit(DesignationConsignes[i]));

		// Creation de la ligne d'edition de la consigne
		//
		if( (EditConsigne[i]=new (std::nothrow) QLineEdit(BRHFenetreConsignes[i],QString("SupervCLIMSO-BRHFenetreConsignes[%1]-EditConsigne[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLineEdit:EditConsigne[" << i << "] de BRHFenetreConsignes[" << i << "]." << std::endl;
		}
		EditConsigne[i]->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
		EditConsigne[i]->setMinimumSize(TAILLE_X_EDIT_CONSIGNE,TAILLE_Y_LABEL_CONSIGNE);
		EditConsigne[i]->setMaximumSize(TAILLE_X_EDIT_CONSIGNE,TAILLE_Y_LABEL_CONSIGNE);

		// On fixe les conditions d'edition
		//
		// IL FAUDRAIT REIMPLEMENTER QDoubleValidator::validate() POUR ETRE PLUS STRICT A LA SAISIE
		//
		switch( i )
		{
			case CONSIGNE_C1_IMG_TP_CENTRAGE:
			case CONSIGNE_C1_IMG_TP_COUR:
			case CONSIGNE_C1_IMG_TP_PLU:
			case CONSIGNE_C2_IMG_TP_CENTRAGE_10830:
			case CONSIGNE_C2_IMG_TP_COUR_10747:
			case CONSIGNE_C2_IMG_TP_COUR_10770:
			case CONSIGNE_C2_IMG_TP_COUR_10798:
			case CONSIGNE_C2_IMG_TP_COUR_10830:
			case CONSIGNE_C2_PLU_TP_10747:
			case CONSIGNE_C2_PLU_TP_10770:
			case CONSIGNE_C2_PLU_TP_10798:
			case CONSIGNE_C2_PLU_TP_10830:
			case CONSIGNE_L1_IMG_TP_CENTRAGE:
			case CONSIGNE_L1_IMG_TP_SURF:
			case CONSIGNE_L1_IMG_TP_COUR:
			case CONSIGNE_L1_IMG_TP_PLU:
			case CONSIGNE_L2_IMG_TP_CENTRAGE:
			case CONSIGNE_L2_IMG_TP_SURF:
			case CONSIGNE_L2_IMG_TP_COUR:
			case CONSIGNE_L2_IMG_TP_PLU:
				// Consignes de temps de pose
				//
				if( (ValideurConsigne[i]=new (std::nothrow) QDoubleValidator(CONSIGNE_TEMPS_POSE_MINI,CONSIGNE_TEMPS_POSE_MAXI,4,EditConsigne[i],QString("SupervCLIMSO-EditConsigne[%1]-ValideurConsigne[%2]").arg(i).arg(i))) == NULL )
				{
					std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QDoubleValidator:ValideurConsigne[" << i << "] de EditConsigne[" << i << "]." << std::endl;
				}
				break;

			case CONSIGNE_C1_TCCD:
			case CONSIGNE_C2_TCCD:
			case CONSIGNE_L1_TCCD:
			case CONSIGNE_L2_TCCD:
			case CONSIGNE_CAISSON_INFO_ALERTE_INF:
			case CONSIGNE_CAISSON_INFO_ALERTE_SUP:
			case CONSIGNE_CAISSON_FILTREC1_ALERTE_INF:
			case CONSIGNE_CAISSON_FILTREC1_ALERTE_SUP:
			case CONSIGNE_CAISSON_FILTREC2_ALERTE_INF:
			case CONSIGNE_CAISSON_FILTREC2_ALERTE_SUP:
				// Consignes de temperature
				//
				if( (ValideurConsigne[i]=new (std::nothrow) QDoubleValidator(CONSIGNE_TEMPERATURE_MINI,CONSIGNE_TEMPERATURE_MAXI,1,EditConsigne[i],QString("SupervCLIMSO-EditConsigne[%1]-ValideurConsigne[%2]").arg(i).arg(i))) == NULL )
				{
					std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QDoubleValidator:ValideurConsigne[" << i << "] de EditConsigne[" << i << "]." << std::endl;
				}
				break;

			case CONSIGNE_C1_VENTILATEUR:
			case CONSIGNE_C2_VENTILATEUR:
			case CONSIGNE_L1_VENTILATEUR:
			case CONSIGNE_L2_VENTILATEUR:
				// Consignes de vitesse de ventilateur
				//
				if( (ValideurConsigne[i]=new (std::nothrow) QDoubleValidator(CONSIGNE_VENTILATEUR_MINI,CONSIGNE_VENTILATEUR_MAXI,1,EditConsigne[i],QString("SupervCLIMSO-EditConsigne[%1]-ValideurConsigne[%2]").arg(i).arg(i))) == NULL )
				{
					std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QDoubleValidator:ValideurConsigne[" << i << "] de EditConsigne[" << i << "]." << std::endl;
				}
				break;
		}
		EditConsigne[i]->setValidator(ValideurConsigne[i]);
	}


	// Widgets de la fenetre de la fiche d'observation de CLIMSO ----------------------------------------------------------------------

	// La fenetre de la fiche d'observation en mode modeless (independante de la fenetre principale de l'application, non bloquante
	//  sur les entrees (non modale))
	//
	// On n'utilise pas une QMainWindow ou une QDockWindow car il n'y a pas besoin de menu, barre d'outils, ancre, barre de status...
	//
	// On rend le bouton Fermer la fenetre inactif en surchargeant la methode closeEvent()
	//
	if( (FenetreFicheObservation=new (std::nothrow) DialogFenetreFicheObservation(this,"SupervCLIMSO-QDialog-FenetreFicheObservation",FALSE,Qt::WType_TopLevel | Qt::WStyle_Customize | Qt::WStyle_DialogBorder)) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QDialog:FenetreFicheObservation de la fenetre principale KMainWindow." << std::endl;
	}
	FenetreFicheObservation->setCaption(QString::fromLocal8Bit("SupervCLIMSO : Fiche d'observation journalière"));
	FenetreFicheObservation->setMinimumSize(TAILLE_X_FICHE_OBS_RECOMMANDEE,TAILLE_Y_FICHE_OBS_RECOMMANDEE);
	FenetreFicheObservation->setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred));


	// Widgets de la fenetre de visualisation des CamerOA -----------------------------------------------------------------------------

	// La fenetre de visualisation des CamerOA en mode modeless (independante de la fenetre principale de l'application, non bloquante
	//  sur les entrees (non modale))
	//
	// On n'utilise pas une QMainWindow ou une QDockWindow car il n'y a pas besoin de menu, barre d'outils, ancre, barre de status...
	//
	// On rend le bouton Fermer la fenetre inactif en surchargeant la methode closeEvent()
	//
	if( (FenetreCamerOA=new (std::nothrow) DialogFenetreCamerOA(this,"SupervCLIMSO-QDialog-FenetreCamerOA",FALSE,Qt::WType_TopLevel | Qt::WStyle_Customize | Qt::WStyle_DialogBorder)) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QDialog:FenetreCamerOA de la fenetre principale KMainWindow." << std::endl;
	}
	FenetreCamerOA->setCaption(QString::fromLocal8Bit("SupervCLIMSO : Supervision des images de centrage des cameras"));
	FenetreCamerOA->setMinimumSize(TAILLE_X_OBJPOSECENTRAGE_RECOMMANDEE*2,TAILLE_Y_OBJPOSECENTRAGE_RECOMMANDEE*2);
	FenetreCamerOA->setMaximumSize(TAILLE_X_OBJPOSECENTRAGE_RECOMMANDEE*2,TAILLE_Y_OBJPOSECENTRAGE_RECOMMANDEE*2);

	// Boite de rangement vertical dans la fenetre de visualisation des CamerOA
	//
	if( (BRVFenetreCamerOA=new (std::nothrow) QVBox(FenetreCamerOA,"SupervCLIMSO-QVBox-BRVFenetreCamerOA")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QVBox:BRVFenetreCamerOA de la fenetre FenetreCamerOA." << std::endl;
	}
	BRVFenetreCamerOA->setMinimumSize(TAILLE_X_OBJPOSECENTRAGE_RECOMMANDEE*2,TAILLE_Y_OBJPOSECENTRAGE_RECOMMANDEE*2);
	BRVFenetreCamerOA->setMaximumSize(TAILLE_X_OBJPOSECENTRAGE_RECOMMANDEE*2,TAILLE_Y_OBJPOSECENTRAGE_RECOMMANDEE*2);

	// Boite de rangement horizontal de C2 et L2 dans la fenetre de visualisation des CamerOA
	//
	if( (BRHCFenetreCamerOA=new (std::nothrow) QHBox(BRVFenetreCamerOA,"SupervCLIMSO-QHBox-BRHCFenetreCamerOA")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BRHCFenetreCamerOA de la fenetre FenetreCamerOA." << std::endl;
	}
	BRHCFenetreCamerOA->setMinimumSize(TAILLE_X_OBJPOSECENTRAGE_RECOMMANDEE*2,TAILLE_Y_OBJPOSECENTRAGE_RECOMMANDEE);
	BRHCFenetreCamerOA->setMaximumSize(TAILLE_X_OBJPOSECENTRAGE_RECOMMANDEE*2,TAILLE_Y_OBJPOSECENTRAGE_RECOMMANDEE);

	// Boite de rangement horizontal de C1 et L1 dans la fenetre de visualisation des CamerOA
	//
	if( (BRHLFenetreCamerOA=new (std::nothrow) QHBox(BRVFenetreCamerOA,"SupervCLIMSO-QHBox-BRHLFenetreCamerOA")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BRHLFenetreCamerOA de la fenetre FenetreCamerOA." << std::endl;
	}
	BRHLFenetreCamerOA->setMinimumSize(TAILLE_X_OBJPOSECENTRAGE_RECOMMANDEE*2,TAILLE_Y_OBJPOSECENTRAGE_RECOMMANDEE);
	BRHLFenetreCamerOA->setMaximumSize(TAILLE_X_OBJPOSECENTRAGE_RECOMMANDEE*2,TAILLE_Y_OBJPOSECENTRAGE_RECOMMANDEE);

	// Objet de visualisation d'une pose de centrage pour le C2 de CLIMSO
	//
	if( (VisuC2=new (std::nothrow) ObjPoseCentrage(BRHCFenetreCamerOA,"SupervCLIMSO-ObjPoseCentrage-VisuC2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget ObjPoseCentrage:VisuC2 de la fenetre FenetreCamerOA." << std::endl;
	}
	VisuC2->NePasEffacerAvantPaintEvent();
	VisuC2->FixeMaxRouge(MAX_COMPOSANTES_RVB_OBJ_CENTRAGE);
	VisuC2->FixeMaxVert(MAX_COMPOSANTES_RVB_OBJ_CENTRAGE);
	VisuC2->FixeMaxBleu(MAX_COMPOSANTES_RVB_OBJ_CENTRAGE);
	VisuC2->TypePalette(NoirEtBlanc);
	VisuC2->setMinimumSize(TAILLE_X_OBJPOSECENTRAGE_RECOMMANDEE,TAILLE_Y_OBJPOSECENTRAGE_RECOMMANDEE);
	VisuC2->setMaximumSize(TAILLE_X_OBJPOSECENTRAGE_RECOMMANDEE,TAILLE_Y_OBJPOSECENTRAGE_RECOMMANDEE);
	VisuC2->ParamAmplificationProfilH(MIN_MATRICE_AMP_PROF,MIN_LARG_ZA_PROF,MIN_AMPLI_PROF);
	VisuC2->ParamAmplificationProfilV(MIN_MATRICE_AMP_PROF,MIN_LARG_ZA_PROF,MIN_AMPLI_PROF);
	QToolTip::add(VisuC2,QString::fromLocal8Bit("Retour image et coupe photométrique centrale de la caméra de C2 coronographe infrarouge"));

	// Objet de visualisation d'une pose de centrage pour la L2 de CLIMSO
	//
	if( (VisuL2=new (std::nothrow) ObjPoseCentrage(BRHCFenetreCamerOA,"SupervCLIMSO-ObjPoseCentrage-VisuL2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget ObjPoseCentrage:VisuL2 de la fenetre FenetreCamerOA." << std::endl;
	}
	VisuL2->NePasEffacerAvantPaintEvent();
	VisuL2->FixeMaxRouge(MAX_COMPOSANTES_RVB_OBJ_CENTRAGE);
	VisuL2->FixeMaxVert(MAX_COMPOSANTES_RVB_OBJ_CENTRAGE);
	VisuL2->FixeMaxBleu(MAX_COMPOSANTES_RVB_OBJ_CENTRAGE);
	VisuL2->TypePalette(NoirEtBlanc);
	VisuL2->setMinimumSize(TAILLE_X_OBJPOSECENTRAGE_RECOMMANDEE,TAILLE_Y_OBJPOSECENTRAGE_RECOMMANDEE);
	VisuL2->setMaximumSize(TAILLE_X_OBJPOSECENTRAGE_RECOMMANDEE,TAILLE_Y_OBJPOSECENTRAGE_RECOMMANDEE);
	VisuL2->ParamAmplificationProfilH(MIN_MATRICE_AMP_PROF,MIN_LARG_ZA_PROF,MIN_AMPLI_PROF);
	VisuL2->ParamAmplificationProfilV(MIN_MATRICE_AMP_PROF,MIN_LARG_ZA_PROF,MIN_AMPLI_PROF);
	QToolTip::add(VisuL2,QString::fromLocal8Bit("Retour image et coupe photométrique centrale de la caméra de L2 lunette Coronado CaK 2.2A"));

	// Objet de visualisation d'une pose de centrage pour le C1 de CLIMSO
	//
	if( (VisuC1=new (std::nothrow) ObjPoseCentrage(BRHLFenetreCamerOA,"SupervCLIMSO-ObjPoseCentrage-VisuC1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget ObjPoseCentrage:VisuC1 de la fenetre FenetreCamerOA." << std::endl;
	}
	VisuC1->NePasEffacerAvantPaintEvent();
	VisuC1->FixeMaxRouge(MAX_COMPOSANTES_RVB_OBJ_CENTRAGE);
	VisuC1->FixeMaxVert(MAX_COMPOSANTES_RVB_OBJ_CENTRAGE);
	VisuC1->FixeMaxBleu(MAX_COMPOSANTES_RVB_OBJ_CENTRAGE);
	VisuC1->TypePalette(NoirEtBlanc);
	VisuC1->setMinimumSize(TAILLE_X_OBJPOSECENTRAGE_RECOMMANDEE,TAILLE_Y_OBJPOSECENTRAGE_RECOMMANDEE);
	VisuC1->setMaximumSize(TAILLE_X_OBJPOSECENTRAGE_RECOMMANDEE,TAILLE_Y_OBJPOSECENTRAGE_RECOMMANDEE);
	VisuC1->ParamAmplificationProfilH(MIN_MATRICE_AMP_PROF,MIN_LARG_ZA_PROF,MIN_AMPLI_PROF);
	VisuC1->ParamAmplificationProfilV(MIN_MATRICE_AMP_PROF,MIN_LARG_ZA_PROF,MIN_AMPLI_PROF);
	QToolTip::add(VisuC1,QString::fromLocal8Bit("Retour image et coupe photométrique centrale de la caméra de C1 coronographe h-alpha"));


	// Objet de visualisation d'une pose de centrage pour la L1 de CLIMSO
	//
	if( (VisuL1=new (std::nothrow) ObjPoseCentrage(BRHLFenetreCamerOA,"SupervCLIMSO-ObjPoseCentrage-VisuL1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget ObjPoseCentrage:VisuL1 de la fenetre FenetreCamerOA." << std::endl;
	}
	VisuL1->NePasEffacerAvantPaintEvent();
	VisuL1->FixeMaxRouge(MAX_COMPOSANTES_RVB_OBJ_CENTRAGE);
	VisuL1->FixeMaxVert(MAX_COMPOSANTES_RVB_OBJ_CENTRAGE);
	VisuL1->FixeMaxBleu(MAX_COMPOSANTES_RVB_OBJ_CENTRAGE);
	VisuL1->TypePalette(NoirEtBlanc);
	VisuL1->setMinimumSize(TAILLE_X_OBJPOSECENTRAGE_RECOMMANDEE,TAILLE_Y_OBJPOSECENTRAGE_RECOMMANDEE);
	VisuL1->setMaximumSize(TAILLE_X_OBJPOSECENTRAGE_RECOMMANDEE,TAILLE_Y_OBJPOSECENTRAGE_RECOMMANDEE);
	VisuL1->ParamAmplificationProfilH(MIN_MATRICE_AMP_PROF,MIN_LARG_ZA_PROF,MIN_AMPLI_PROF);
	VisuL1->ParamAmplificationProfilV(MIN_MATRICE_AMP_PROF,MIN_LARG_ZA_PROF,MIN_AMPLI_PROF);
	QToolTip::add(VisuL1,QString::fromLocal8Bit("Retour image et coupe photométrique centrale de la caméra de L1 lunette Coronado h-alpha 0.5A"));



	// Widgets de la fenetre de visualisation des temperatures -----------------------------------------------------------------------------

	// La fenetre de visualisation des temperatures en mode modeless (independante de la fenetre principale de l'application, non bloquante
	//  sur les entrees (non modale))
	//
	// On n'utilise pas une QMainWindow ou une QDockWindow car il n'y a pas besoin de menu, barre d'outils, ancre, barre de status...
	//
	// On rend le bouton Fermer la fenetre inactif en surchargeant la methode closeEvent()
	//
	if( (FenetreTemperatures=new (std::nothrow) DialogFenetreTemperatures(this,"SupervCLIMSO-QDialog-FenetreTemperatures",FALSE,Qt::WType_TopLevel | Qt::WStyle_Customize | Qt::WStyle_DialogBorder)) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QDialog:FenetreTemperatures de la fenetre principale KMainWindow." << std::endl;
	}
	FenetreTemperatures->setCaption(QString::fromLocal8Bit("SupervCLIMSO : Températures °C"));
	FenetreTemperatures->setMinimumSize(TAILLE_X_LABEL_TEMPERATURES+TAILLE_X_LCD_TEMPERATURES,TAILLE_Y_LCD_TEMPERATURES*8);
	FenetreTemperatures->setMaximumSize(TAILLE_X_LABEL_TEMPERATURES+TAILLE_X_LCD_TEMPERATURES,TAILLE_Y_LCD_TEMPERATURES*8);

	// Boite de rangement vertical dans la fenetre de visualisation des temperatures
	//
	if( (BRVFenetreTemperatures=new (std::nothrow) QVBox(FenetreTemperatures,"SupervCLIMSO-QVBox-BRVFenetreTemperatures")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QVBox:BRVFenetreTemperatures de la fenetre FenetreTemperatures." << std::endl;
	}
	BRVFenetreTemperatures->setMinimumSize(TAILLE_X_LABEL_TEMPERATURES+TAILLE_X_LCD_TEMPERATURES,TAILLE_Y_LCD_TEMPERATURES*8);
	BRVFenetreTemperatures->setMaximumSize(TAILLE_X_LABEL_TEMPERATURES+TAILLE_X_LCD_TEMPERATURES,TAILLE_Y_LCD_TEMPERATURES*8);

	// Boite de rangement horizontal de chaque sonde de temperature
	//
	for( i=0; i < NB_SONDES_TEMPERATURE; i++ )
	{
		if( (BRHFenetreTemperatures[i]=new (std::nothrow) QHBox(BRVFenetreTemperatures,QString("SupervCLIMSO-QHBox-BRHFenetreTemperatures[%1]").arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BRHFenetreTemperatures[" << i << "] de la fenetre FenetreTemperatures." << std::endl;
		}
		BRHFenetreTemperatures[i]->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
		BRHFenetreTemperatures[i]->setMinimumSize(TAILLE_X_LABEL_TEMPERATURES+TAILLE_X_LCD_TEMPERATURES,TAILLE_Y_LCD_TEMPERATURES);
		BRHFenetreTemperatures[i]->setMaximumSize(TAILLE_X_LABEL_TEMPERATURES+TAILLE_X_LCD_TEMPERATURES,TAILLE_Y_LCD_TEMPERATURES);

		// Creation de son label d'affichage de la designation de la temperature
		//
		if( (LabelTemperatures[i]=new (std::nothrow) QLabel(BRHFenetreTemperatures[i],QString("SupervCLIMSO-BRHFenetreTemperatures[%1]-LabelTemperatures[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLabel:LabelTemperatures[" << i << "] de BRHFenetreTemperatures[" << i << "]." << std::endl;
		}
		LabelTemperatures[i]->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
		LabelTemperatures[i]->setMinimumSize(TAILLE_X_LABEL_TEMPERATURES,TAILLE_Y_LCD_TEMPERATURES);
		LabelTemperatures[i]->setMaximumSize(TAILLE_X_LABEL_TEMPERATURES,TAILLE_Y_LCD_TEMPERATURES);
		LabelTemperatures[i]->setText(QString::fromLocal8Bit(DesignationSondeTemperature[i]));
		LabelTemperatures[i]->setPaletteBackgroundColor(COULEUR_LIGNE_TEMP_SONDE_OK);

		// Creation de son afficheur LCD
		//
		if( (LCDTemperatures[i]=new (std::nothrow) QLCDNumber(BRHFenetreTemperatures[i],QString("SupervCLIMSO-BRHFenetreTemperatures[%1]-LCDTemperatures[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLCDNumber:LCDTemperatures[" << i << "] de BRHFenetreTemperatures[" << i << "]." << std::endl;
		}
		LCDTemperatures[i]->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
		LCDTemperatures[i]->setFixedSize(TAILLE_X_LCD_TEMPERATURES,TAILLE_Y_LCD_TEMPERATURES);
		LCDTemperatures[i]->setSmallDecimalPoint(false);
		LCDTemperatures[i]->setSegmentStyle(QLCDNumber::Flat);
		LCDTemperatures[i]->display("-");
	}


	// Widgets de la fenetre de controle des TerminOA -----------------------------------------------------------------------------

	// La fenetre de controle des TerminOA en mode modeless (independante de la fenetre principale de l'application, non bloquante
	//  sur les entrees (non modale))
	//
	// On n'utilise pas une QMainWindow ou une QDockWindow car il n'y a pas besoin de menu, barre d'outils, ancre, barre de status...
	//
	// On rend le bouton Fermer la fenetre inactif en surchargeant la methode closeEvent()
	//
	if( (FenetreCtrlTerminOA=new (std::nothrow) DialogFenetreCtrlTerminOA(this,"SupervCLIMSO-QDialog-FenetreCtrlTerminOA",FALSE,Qt::WType_TopLevel | Qt::WStyle_Customize | Qt::WStyle_DialogBorder)) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QDialog:FenetreCtrlTerminOA de la fenetre principale KMainWindow." << std::endl;
	}
	FenetreCtrlTerminOA->setCaption(QString::fromLocal8Bit("SupervCLIMSO : Contrôle TerminOA"));
	FenetreCtrlTerminOA->setMinimumSize(TAILLE_X_LABEL_CTRL_TERMINOA+19*TAILLE_X_ICON_CTRL_TERMINOA+2*TAILLE_X_SPINBOX_SEUIL_CTRL_TERMINOA+TAILLE_X_SPINBOX_PUILUT_CTRL_TERMINOA,TAILLE_Y_QHBOX_CTRL_TERMINOA*NB_TERMINOA);
	FenetreCtrlTerminOA->setMaximumSize(TAILLE_X_LABEL_CTRL_TERMINOA+19*TAILLE_X_ICON_CTRL_TERMINOA+2*TAILLE_X_SPINBOX_SEUIL_CTRL_TERMINOA+TAILLE_X_SPINBOX_PUILUT_CTRL_TERMINOA,TAILLE_Y_QHBOX_CTRL_TERMINOA*NB_TERMINOA);

	// Boite de rangement vertical dans la fenetre de controle des TerminOA
	//
	if( (BRVFenetreCtrlTerminOA=new (std::nothrow) QVBox(FenetreCtrlTerminOA,"SupervCLIMSO-QVBox-BRVFenetreCtrlTerminOA")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QVBox:BRVFenetreCtrlTerminOA de la fenetre FenetreCtrlTerminOA." << std::endl;
	}
	BRVFenetreCtrlTerminOA->setMinimumSize(TAILLE_X_LABEL_CTRL_TERMINOA+19*TAILLE_X_ICON_CTRL_TERMINOA+2*TAILLE_X_SPINBOX_SEUIL_CTRL_TERMINOA+TAILLE_X_SPINBOX_PUILUT_CTRL_TERMINOA,TAILLE_Y_QHBOX_CTRL_TERMINOA*NB_TERMINOA);
	BRVFenetreCtrlTerminOA->setMaximumSize(TAILLE_X_LABEL_CTRL_TERMINOA+19*TAILLE_X_ICON_CTRL_TERMINOA+2*TAILLE_X_SPINBOX_SEUIL_CTRL_TERMINOA+TAILLE_X_SPINBOX_PUILUT_CTRL_TERMINOA,TAILLE_Y_QHBOX_CTRL_TERMINOA*NB_TERMINOA);

	// Boite de rangement horizontal de chaque TerminOA controle
	//
	for( i=0; i < NB_TERMINOA; i++ )
	{
		if( (BRHFenetreCtrlTerminOA[i]=new (std::nothrow) QHBox(BRVFenetreCtrlTerminOA,QString("SupervCLIMSO-QHBox-BRHFenetreCtrlTerminOA[%1]").arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BRHFenetreCtrlTerminOA[" << i << "] de la fenetre FenetreCtrlTerminOA." << std::endl;
		}
		BRHFenetreCtrlTerminOA[i]->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
		BRHFenetreCtrlTerminOA[i]->setMinimumSize(TAILLE_X_LABEL_CTRL_TERMINOA+19*TAILLE_X_ICON_CTRL_TERMINOA+2*TAILLE_X_SPINBOX_SEUIL_CTRL_TERMINOA+TAILLE_X_SPINBOX_PUILUT_CTRL_TERMINOA,TAILLE_Y_QHBOX_CTRL_TERMINOA);
		BRHFenetreCtrlTerminOA[i]->setMaximumSize(TAILLE_X_LABEL_CTRL_TERMINOA+19*TAILLE_X_ICON_CTRL_TERMINOA+2*TAILLE_X_SPINBOX_SEUIL_CTRL_TERMINOA+TAILLE_X_SPINBOX_PUILUT_CTRL_TERMINOA,TAILLE_Y_QHBOX_CTRL_TERMINOA);

		// Creation de son label d'affichage de la designation du TerminOA controle
		//
		if( (LabelTerminOA[i]=new (std::nothrow) QLabel(BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-LabelTerminOA[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLabel:LabelTerminOA[" << i << "] de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		LabelTerminOA[i]->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
		LabelTerminOA[i]->setMinimumSize(TAILLE_X_LABEL_CTRL_TERMINOA,TAILLE_Y_QHBOX_CTRL_TERMINOA);
		LabelTerminOA[i]->setMaximumSize(TAILLE_X_LABEL_CTRL_TERMINOA,TAILLE_Y_QHBOX_CTRL_TERMINOA);
		LabelTerminOA[i]->setText(QString::fromLocal8Bit(InstrumentCLIMSO[i]));
		switch( i )
		{
			case CAMEROA_C1:	QToolTip::add(LabelTerminOA[i],QString::fromLocal8Bit("Boutons de contrôle du terminal de visualisation des images produites par C1"));	break;
			case CAMEROA_C2:	QToolTip::add(LabelTerminOA[i],QString::fromLocal8Bit("Boutons de contrôle du terminal de visualisation des images produites par C2"));	break;
			case CAMEROA_L1:	QToolTip::add(LabelTerminOA[i],QString::fromLocal8Bit("Boutons de contrôle du terminal de visualisation des images produites par L1"));	break;
			case CAMEROA_L2:	QToolTip::add(LabelTerminOA[i],QString::fromLocal8Bit("Boutons de contrôle du terminal de visualisation des images produites par L2"));	break;
		}

		// Creation du widget bouton poussoir de passage en mode affichage image courante
		//
		if( (BoutonModeIC[i]=new (std::nothrow) QPushButton(QIconSet(QPixmap(IconModeIC_xpm),QIconSet::Automatic),"",BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-BoutonModeIC[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonModeIC[" << i << "] de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		BoutonModeIC[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonModeIC[i]->setMaximumSize(TAILLE_X_ICON_CTRL_TERMINOA,TAILLE_Y_ICON_CTRL_TERMINOA);
		QToolTip::add(BoutonModeIC[i],QString::fromLocal8Bit("Basculer le terminal de visualisation en mode visualisation de l'image courante"));

		// Creation du widget d'entree SpinBox de la consigne du seuil bas
		//
		if( (SpinBoxCSB[i]=new (std::nothrow) QSpinBox(MIN_CSB,MAX_CSB,100,BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-SpinBoxCSB[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QSpinBox:SpinBoxCSB[" << i << " de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		SpinBoxCSB[i]->setPrefix("b");
		SpinBoxCSB[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		SpinBoxCSB[i]->setMaximumSize(TAILLE_X_SPINBOX_SEUIL_CTRL_TERMINOA,TAILLE_Y_ICON_CTRL_TERMINOA);
		QToolTip::add(SpinBoxCSB[i],QString::fromLocal8Bit("Fixer la consigne de seuil bas de visualisation sur le terminal de visualisation (en ADU)"));

		// Creation du widget d'entree SpinBox de la consigne du seuil haut
		//
		if( (SpinBoxCSH[i]=new (std::nothrow) QSpinBox(MIN_CSH,MAX_CSH,1000,BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-SpinBoxCSH[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QSpinBox:SpinBoxCSH[" << i << " de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		SpinBoxCSH[i]->setPrefix("h");
		SpinBoxCSH[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		SpinBoxCSH[i]->setMaximumSize(TAILLE_X_SPINBOX_SEUIL_CTRL_TERMINOA,TAILLE_Y_ICON_CTRL_TERMINOA);
		QToolTip::add(SpinBoxCSH[i],QString::fromLocal8Bit("Fixer la consigne de seuil haut de visualisation sur le terminal de visualisation (en ADU)"));

		// Creation du widget d'entree SpinBox de la consigne de la puissance de la LUT de visualisation
		//
		if( (SpinBoxCPuiLUT[i]=new (std::nothrow) QSpinBox(MIN_CPUILUT,MAX_CPUILUT,5,BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-SpinBoxPuiLUT[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QSpinBox:SpinBoxPuiLUT[" << i << " de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		SpinBoxCPuiLUT[i]->setPrefix("^");
		SpinBoxCPuiLUT[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		SpinBoxCPuiLUT[i]->setMaximumSize(TAILLE_X_SPINBOX_PUILUT_CTRL_TERMINOA,TAILLE_Y_ICON_CTRL_TERMINOA);
		QToolTip::add(SpinBoxCPuiLUT[i],QString::fromLocal8Bit("Fixer la forme de la Look Up Table de visualisation en x^n sur le terminal de visualisation (n en centièmes: linéaire: n=100 pour x^1, log: n=50 pour x^0.5 ...)"));

		// Creation du widget bouton poussoir de passage en zone de representation Z0
		//
		if( (BoutonZ0[i]=new (std::nothrow) QPushButton(QIconSet(QPixmap(IconZoneZ0_xpm),QIconSet::Automatic),"",BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-BoutonZ0[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonZ0[" << i << "] de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		BoutonZ0[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonZ0[i]->setMaximumSize(TAILLE_X_ICON_CTRL_TERMINOA,TAILLE_Y_ICON_CTRL_TERMINOA);
		QToolTip::add(BoutonZ0[i],QString::fromLocal8Bit("Basculer le terminal en mode de visualisation pleine image courante"));

		// Creation du widget bouton poussoir de passage en zone de representation Z1
		//
		if( (BoutonZ1[i]=new (std::nothrow) QPushButton(QIconSet(QPixmap(IconZoneZ1_xpm),QIconSet::Automatic),"",BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-BoutonZ1[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonZ1[" << i << "] de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		BoutonZ1[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonZ1[i]->setMaximumSize(TAILLE_X_ICON_CTRL_TERMINOA,TAILLE_Y_ICON_CTRL_TERMINOA);
		QToolTip::add(BoutonZ1[i],QString::fromLocal8Bit("Basculer le terminal en visualisation du tier supérieur gauche de l'image courante"));

		// Creation du widget bouton poussoir de passage en zone de representation Z2
		//
		if( (BoutonZ2[i]=new (std::nothrow) QPushButton(QIconSet(QPixmap(IconZoneZ2_xpm),QIconSet::Automatic),"",BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-BoutonZ2[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonZ2[" << i << "] de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		BoutonZ2[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonZ2[i]->setMaximumSize(TAILLE_X_ICON_CTRL_TERMINOA,TAILLE_Y_ICON_CTRL_TERMINOA);
		QToolTip::add(BoutonZ2[i],QString::fromLocal8Bit("Basculer le terminal en visualisation du tier supérieur de l'image courante"));

		// Creation du widget bouton poussoir de passage en zone de representation Z3
		//
		if( (BoutonZ3[i]=new (std::nothrow) QPushButton(QIconSet(QPixmap(IconZoneZ3_xpm),QIconSet::Automatic),"",BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-BoutonZ3[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonZ3[" << i << "] de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		BoutonZ3[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonZ3[i]->setMaximumSize(TAILLE_X_ICON_CTRL_TERMINOA,TAILLE_Y_ICON_CTRL_TERMINOA);
		QToolTip::add(BoutonZ3[i],QString::fromLocal8Bit("Basculer le terminal en visualisation du tier supérieur droit de l'image courante"));

		// Creation du widget bouton poussoir de passage en zone de representation Z4
		//
		if( (BoutonZ4[i]=new (std::nothrow) QPushButton(QIconSet(QPixmap(IconZoneZ4_xpm),QIconSet::Automatic),"",BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-BoutonZ4[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonZ4[" << i << "] de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		BoutonZ4[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonZ4[i]->setMaximumSize(TAILLE_X_ICON_CTRL_TERMINOA,TAILLE_Y_ICON_CTRL_TERMINOA);
		QToolTip::add(BoutonZ4[i],QString::fromLocal8Bit("Basculer le terminal en visualisation du tier centre gauche de l'image courante"));

		// Creation du widget bouton poussoir de passage en zone de representation Z5
		//
		if( (BoutonZ5[i]=new (std::nothrow) QPushButton(QIconSet(QPixmap(IconZoneZ5_xpm),QIconSet::Automatic),"",BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-BoutonZ5[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonZ5[" << i << "] de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		BoutonZ5[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonZ5[i]->setMaximumSize(TAILLE_X_ICON_CTRL_TERMINOA,TAILLE_Y_ICON_CTRL_TERMINOA);
		QToolTip::add(BoutonZ5[i],QString::fromLocal8Bit("Basculer le terminal en visualisation du tier central de l'image courante"));

		// Creation du widget bouton poussoir de passage en zone de representation Z6
		//
		if( (BoutonZ6[i]=new (std::nothrow) QPushButton(QIconSet(QPixmap(IconZoneZ6_xpm),QIconSet::Automatic),"",BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-BoutonZ6[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonZ6[" << i << "] de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		BoutonZ6[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonZ6[i]->setMaximumSize(TAILLE_X_ICON_CTRL_TERMINOA,TAILLE_Y_ICON_CTRL_TERMINOA);
		QToolTip::add(BoutonZ6[i],QString::fromLocal8Bit("Basculer le terminal en visualisation du tier centre droit de l'image courante"));

		// Creation du widget bouton poussoir de passage en zone de representation Z7
		//
		if( (BoutonZ7[i]=new (std::nothrow) QPushButton(QIconSet(QPixmap(IconZoneZ7_xpm),QIconSet::Automatic),"",BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-BoutonZ7[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonZ7[" << i << "] de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		BoutonZ7[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonZ7[i]->setMaximumSize(TAILLE_X_ICON_CTRL_TERMINOA,TAILLE_Y_ICON_CTRL_TERMINOA);
		QToolTip::add(BoutonZ7[i],QString::fromLocal8Bit("Basculer le terminal en visualisation du tier inférieur gauche de l'image courante"));

		// Creation du widget bouton poussoir de passage en zone de representation Z8
		//
		if( (BoutonZ8[i]=new (std::nothrow) QPushButton(QIconSet(QPixmap(IconZoneZ8_xpm),QIconSet::Automatic),"",BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-BoutonZ8[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonZ8[" << i << "] de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		BoutonZ8[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonZ8[i]->setMaximumSize(TAILLE_X_ICON_CTRL_TERMINOA,TAILLE_Y_ICON_CTRL_TERMINOA);
		QToolTip::add(BoutonZ8[i],QString::fromLocal8Bit("Basculer le terminal en visualisation du tier inférieur de l'image courante"));

		// Creation du widget bouton poussoir de passage en zone de representation Z9
		//
		if( (BoutonZ9[i]=new (std::nothrow) QPushButton(QIconSet(QPixmap(IconZoneZ9_xpm),QIconSet::Automatic),"",BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-BoutonZ9[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonZ9[" << i << "] de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		BoutonZ9[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonZ9[i]->setMaximumSize(TAILLE_X_ICON_CTRL_TERMINOA,TAILLE_Y_ICON_CTRL_TERMINOA);
		QToolTip::add(BoutonZ9[i],QString::fromLocal8Bit("Basculer le terminal en visualisation du tier inférieur droit de l'image courante"));

		// Creation du widget bouton poussoir de passage en palette de representation noir et blanc
		//
		if( (BoutonPalNB[i]=new (std::nothrow) QPushButton(QIconSet(QPixmap(IconPaletteNB_xpm),QIconSet::Automatic),"",BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-BoutonPalNB[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonPalNB[" << i << "] de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		BoutonPalNB[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonPalNB[i]->setMaximumSize(TAILLE_X_ICON_CTRL_TERMINOA,TAILLE_Y_ICON_CTRL_TERMINOA);
		QToolTip::add(BoutonPalNB[i],QString::fromLocal8Bit("Basculer la visualisation de l'image courante sur le terminal en palette Noir et Blanc"));

		// Creation du widget bouton poussoir de passage en palette de representation h-alpha
		//
		if( (BoutonPalHalpha[i]=new (std::nothrow) QPushButton(QIconSet(QPixmap(IconPaletteHalpha_xpm),QIconSet::Automatic),"",BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-BoutonPalHalpha[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonPalHalpha[" << i << "] de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		BoutonPalHalpha[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonPalHalpha[i]->setMaximumSize(TAILLE_X_ICON_CTRL_TERMINOA,TAILLE_Y_ICON_CTRL_TERMINOA);
		QToolTip::add(BoutonPalHalpha[i],QString::fromLocal8Bit("Basculer la visualisation de l'image courante sur le terminal en palette couleur rosée simulant h-alpha"));

		// Creation du widget bouton poussoir de passage en palette de representation noir-orange-blanc
		//
		if( (BoutonPalNoirOrangeBlanc[i]=new (std::nothrow) QPushButton(QIconSet(QPixmap(IconPaletteNoirOrangeBlanc_xpm),QIconSet::Automatic),"",BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-BoutonPalNoirOrangeBlanc[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonPalNoirOrangeBlanc[" << i << "] de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		BoutonPalNoirOrangeBlanc[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonPalNoirOrangeBlanc[i]->setMaximumSize(TAILLE_X_ICON_CTRL_TERMINOA,TAILLE_Y_ICON_CTRL_TERMINOA);
		QToolTip::add(BoutonPalNoirOrangeBlanc[i],QString::fromLocal8Bit("Basculer la visualisation de l'image courante sur le terminal en palette couleur orangée"));

		// Creation du widget bouton poussoir de passage en palette de representation noir-vert-blanc
		//
		if( (BoutonPalNoirVertBlanc[i]=new (std::nothrow) QPushButton(QIconSet(QPixmap(IconPaletteNoirVertBlanc_xpm),QIconSet::Automatic),"",BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-BoutonPalNoirVertBlanc[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonPalNoirVertBlanc[" << i << "] de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		BoutonPalNoirVertBlanc[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonPalNoirVertBlanc[i]->setMaximumSize(TAILLE_X_ICON_CTRL_TERMINOA,TAILLE_Y_ICON_CTRL_TERMINOA);
		QToolTip::add(BoutonPalNoirVertBlanc[i],QString::fromLocal8Bit("Basculer la visualisation de l'image courante sur le terminal en palette couleur verdâtre"));

		// Creation du widget bouton poussoir de passage en palette de representation noir-bleu-blanc
		//
		if( (BoutonPalNoirBleuBlanc[i]=new (std::nothrow) QPushButton(QIconSet(QPixmap(IconPaletteNoirBleuBlanc_xpm),QIconSet::Automatic),"",BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-BoutonPalNoirBleuBlanc[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonPalNoirBleuBlanc[" << i << "] de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		BoutonPalNoirBleuBlanc[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonPalNoirBleuBlanc[i]->setMaximumSize(TAILLE_X_ICON_CTRL_TERMINOA,TAILLE_Y_ICON_CTRL_TERMINOA);
		QToolTip::add(BoutonPalNoirBleuBlanc[i],QString::fromLocal8Bit("Basculer la visualisation de l'image courante sur le terminal en palette couleur bleutée"));

		// Creation du widget bouton poussoir de passage en echelle de representation de l'histogramme lineaire
		//
		if( (BoutonEchLin[i]=new (std::nothrow) QPushButton(QIconSet(QPixmap(IconEchLin_xpm),QIconSet::Automatic),"",BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-BoutonEchLin[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonEchLin[" << i << "] de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		BoutonEchLin[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonEchLin[i]->setMaximumSize(TAILLE_X_ICON_CTRL_TERMINOA,TAILLE_Y_ICON_CTRL_TERMINOA);
		QToolTip::add(BoutonEchLin[i],QString::fromLocal8Bit("Basculer la représentation graphique de l'histogramme de l'image courante sur le terminal dans une échelle linéaire"));

		// Creation du widget bouton poussoir de passage en echelle de representation de l'histogramme logarithmique
		//
		if( (BoutonEchLog[i]=new (std::nothrow) QPushButton(QIconSet(QPixmap(IconEchLog_xpm),QIconSet::Automatic),"",BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-BoutonEchLog[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonEchLog[" << i << "] de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		BoutonEchLog[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonEchLog[i]->setMaximumSize(TAILLE_X_ICON_CTRL_TERMINOA,TAILLE_Y_ICON_CTRL_TERMINOA);
		QToolTip::add(BoutonEchLog[i],QString::fromLocal8Bit("Basculer la représentation graphique de l'histogramme de l'image courante sur le terminal dans une échelle logarithmique"));

		// Creation du widget bouton poussoir de passage en mode diaporama
		//
		if( (BoutonModeDiapo[i]=new (std::nothrow) QPushButton(QIconSet(QPixmap(IconModeDiaporama_xpm),QIconSet::Automatic),"",BRHFenetreCtrlTerminOA[i],QString("SupervCLIMSO-BRHFenetreCtrlTerminOA[%1]-BoutonModeDiapo[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonModeDiapo[" << i << "] de BRHFenetreCtrlTerminOA[" << i << "]." << std::endl;
		}
		BoutonModeDiapo[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonModeDiapo[i]->setMaximumSize(TAILLE_X_ICON_CTRL_TERMINOA,TAILLE_Y_ICON_CTRL_TERMINOA);
		QToolTip::add(BoutonModeDiapo[i],QString::fromLocal8Bit("Basculer le terminal TerminOA dans le mode économiseur d'écran"));
	}


	// Widgets de la fenetre de publication BASS2000 des dernieres images de C1 ------------------------------------------------------------

	// La fenetre de publication en mode modeless (independante de la fenetre principale de l'application, non bloquante
	//  sur les entrees (non modale))
	//
	// On n'utilise pas une QMainWindow ou une QDockWindow car il n'y a pas besoin de menu, barre d'outils, ancre, barre de status...
	//
	if( (FenetrePubliC1=new (std::nothrow) QDialog(this,"SupervCLIMSO-QDialog-FenetrePubliC1",FALSE,Qt::WType_TopLevel | Qt::WStyle_Customize | Qt::WStyle_DialogBorder)) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QDialog:FenetrePubliC1 de la fenetre principale KMainWindow." << std::endl;
	}
	FenetrePubliC1->setCaption(QString::fromLocal8Bit("SupervCLIMSO : Publication BASS2000 images de C1"));
	FenetrePubliC1->setMinimumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE*NB_IMG_PUB_C1);
	FenetrePubliC1->setMaximumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE*NB_IMG_PUB_C1);

	NbImgPubliablesC1=0;	// Pour l'instant aucune image publiable

	// Boite de rangement vertical dans la fenetre de publication BASS2000 des dernieres images de C1
	//
	if( (BRVFenetrePubliC1=new (std::nothrow) QVBox(FenetrePubliC1,"SupervCLIMSO-QVBox-BRVFenetrePubliC1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QVBox:BRVFenetrePubliC1 de la fenetre FenetrePubliC1." << std::endl;
	}
	BRVFenetrePubliC1->setMinimumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE*NB_IMG_PUB_C1);
	BRVFenetrePubliC1->setMaximumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE*NB_IMG_PUB_C1);

	// Boite de rangement horizontal de chaque image publiable
	//
	for( i=0; i < NB_IMG_PUB_C1; i++ )
	{
		if( (BRHFenetrePubliC1[i]=new (std::nothrow) QHBox(BRVFenetrePubliC1,QString("SupervCLIMSO-QHBox-BRHFenetrePubliC1[%1]").arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BRHFenetrePubliC1[" << i << "] de la fenetre ." << std::endl;
		}
		BRHFenetrePubliC1[i]->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
		BRHFenetrePubliC1[i]->setMinimumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);
		BRHFenetrePubliC1[i]->setMaximumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);

		// Creation de son label d'affichage du nom du fichier
		//
		if( (LabelFenetrePubliC1[i]=new (std::nothrow) QLabel(BRHFenetrePubliC1[i],QString("SupervCLIMSO-BRHFenetrePubliC1[%1]-LabelFenetrePubliC1[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLabel:LabelFenetrePubliC1[" << i << "] de BRHFenetrePubliC1[" << i << "]." << std::endl;
		}
		LabelFenetrePubliC1[i]->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
		LabelFenetrePubliC1[i]->setMinimumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);
		LabelFenetrePubliC1[i]->setMaximumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);
		LabelFenetrePubliC1[i]->setText(QString::fromLocal8Bit(""));
		if( (i % 2) == 0 ) LabelFenetrePubliC1[i]->setPaletteBackgroundColor(COULEUR_LIGNE_IMG_PUB_0); else LabelFenetrePubliC1[i]->setPaletteBackgroundColor(COULEUR_LIGNE_IMG_PUB_1);

		// Creation du bouton poussoir de publication du fichier
		//
		if( (BoutonFenetrePubliC1[i]=new (std::nothrow) QPushButton(BRHFenetrePubliC1[i],QString("SupervCLIMSO-BRHFenetrePubliC1[%1]-BoutonFenetrePubliC1[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonFenetrePubliC1[" << i << "] de BRHFenetrePubliC1[" << i << "]." << std::endl;
		}
		BoutonFenetrePubliC1[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonFenetrePubliC1[i]->setMinimumSize(TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);
		BoutonFenetrePubliC1[i]->setMaximumSize(TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);
		BoutonFenetrePubliC1[i]->setText(QString::fromLocal8Bit("Publier"));

		// Le nom des fichiers
		//
		FichiersPubliC1[i].reserve(TAILLE_MINI_CHAINE);
		FichiersPubliC1[i]="";
	}


	// Widgets de la fenetre de publication BASS2000 des dernieres images de C2 ------------------------------------------------------------

	// La fenetre de publication en mode modeless (independante de la fenetre principale de l'application, non bloquante
	//  sur les entrees (non modale))
	//
	// On n'utilise pas une QMainWindow ou une QDockWindow car il n'y a pas besoin de menu, barre d'outils, ancre, barre de status...
	//
	if( (FenetrePubliC2=new (std::nothrow) QDialog(this,"SupervCLIMSO-QDialog-FenetrePubliC2",FALSE,Qt::WType_TopLevel | Qt::WStyle_Customize | Qt::WStyle_DialogBorder)) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QDialog:FenetrePubliC2 de la fenetre principale KMainWindow." << std::endl;
	}
	FenetrePubliC2->setCaption(QString::fromLocal8Bit("SupervCLIMSO : Publication BASS2000 images de C2"));
	FenetrePubliC2->setMinimumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE*NB_IMG_PUB_C2);
	FenetrePubliC2->setMaximumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE*NB_IMG_PUB_C2);

	NbImgPubliablesC2=0;	// Pour l'instant aucune image publiable

	// Boite de rangement vertical dans la fenetre de publication BASS2000 des dernieres images de C2
	//
	if( (BRVFenetrePubliC2=new (std::nothrow) QVBox(FenetrePubliC2,"SupervCLIMSO-QVBox-BRVFenetrePubliC2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QVBox:BRVFenetrePubliC2 de la fenetre FenetrePubliC2." << std::endl;
	}
	BRVFenetrePubliC2->setMinimumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE*NB_IMG_PUB_C2);
	BRVFenetrePubliC2->setMaximumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE*NB_IMG_PUB_C2);

	// Boite de rangement horizontal de chaque image publiable
	//
	for( i=0; i < NB_IMG_PUB_C2; i++ )
	{
		if( (BRHFenetrePubliC2[i]=new (std::nothrow) QHBox(BRVFenetrePubliC2,QString("SupervCLIMSO-QHBox-BRHFenetrePubliC2[%1]").arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BRHFenetrePubliC2[" << i << "] de la fenetre ." << std::endl;
		}
		BRHFenetrePubliC2[i]->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
		BRHFenetrePubliC2[i]->setMinimumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);
		BRHFenetrePubliC2[i]->setMaximumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);

		// Creation de son label d'affichage du nom du fichier
		//
		if( (LabelFenetrePubliC2[i]=new (std::nothrow) QLabel(BRHFenetrePubliC2[i],QString("SupervCLIMSO-BRHFenetrePubliC2[%1]-LabelFenetrePubliC2[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLabel:LabelFenetrePubliC2[" << i << "] de BRHFenetrePubliC2[" << i << "]." << std::endl;
		}
		LabelFenetrePubliC2[i]->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
		LabelFenetrePubliC2[i]->setMinimumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);
		LabelFenetrePubliC2[i]->setMaximumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);
		LabelFenetrePubliC2[i]->setText(QString::fromLocal8Bit(""));
		if( (i % 2) == 0 ) LabelFenetrePubliC2[i]->setPaletteBackgroundColor(COULEUR_LIGNE_IMG_PUB_0); else LabelFenetrePubliC2[i]->setPaletteBackgroundColor(COULEUR_LIGNE_IMG_PUB_1);

		// Creation du bouton poussoir de publication du fichier
		//
		if( (BoutonFenetrePubliC2[i]=new (std::nothrow) QPushButton(BRHFenetrePubliC2[i],QString("SupervCLIMSO-BRHFenetrePubliC2[%1]-BoutonFenetrePubliC2[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonFenetrePubliC2[" << i << "] de BRHFenetrePubliC2[" << i << "]." << std::endl;
		}
		BoutonFenetrePubliC2[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonFenetrePubliC2[i]->setMinimumSize(TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);
		BoutonFenetrePubliC2[i]->setMaximumSize(TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);
		BoutonFenetrePubliC2[i]->setText(QString::fromLocal8Bit("Publier"));

		// Le nom des fichiers
		//
		FichiersPubliC2[i].reserve(TAILLE_MINI_CHAINE);
		FichiersPubliC2[i]="";
	}


	// Widgets de la fenetre de publication BASS2000 des dernieres images de L1 ------------------------------------------------------------

	// La fenetre de publication en mode modeless (independante de la fenetre principale de l'application, non bloquante
	//  sur les entrees (non modale))
	//
	// On n'utilise pas une QMainWindow ou une QDockWindow car il n'y a pas besoin de menu, barre d'outils, ancre, barre de status...
	//
	if( (FenetrePubliL1=new (std::nothrow) QDialog(this,"SupervCLIMSO-QDialog-FenetrePubliL1",FALSE,Qt::WType_TopLevel | Qt::WStyle_Customize | Qt::WStyle_DialogBorder)) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QDialog:FenetrePubliL1 de la fenetre principale KMainWindow." << std::endl;
	}
	FenetrePubliL1->setCaption(QString::fromLocal8Bit("SupervCLIMSO : Publication BASS2000 images de L1"));
	FenetrePubliL1->setMinimumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE*NB_IMG_PUB_L1);
	FenetrePubliL1->setMaximumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE*NB_IMG_PUB_L1);

	NbImgPubliablesL1=0;	// Pour l'instant aucune image publiable

	// Boite de rangement vertical dans la fenetre de publication BASS2000 des dernieres images de L1
	//
	if( (BRVFenetrePubliL1=new (std::nothrow) QVBox(FenetrePubliL1,"SupervCLIMSO-QVBox-BRVFenetrePubliL1")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QVBox:BRVFenetrePubliL1 de la fenetre FenetrePubliL1." << std::endl;
	}
	BRVFenetrePubliL1->setMinimumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE*NB_IMG_PUB_L1);
	BRVFenetrePubliL1->setMaximumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE*NB_IMG_PUB_L1);

	// Boite de rangement horizontal de chaque image publiable
	//
	for( i=0; i < NB_IMG_PUB_L1; i++ )
	{
		if( (BRHFenetrePubliL1[i]=new (std::nothrow) QHBox(BRVFenetrePubliL1,QString("SupervCLIMSO-QHBox-BRHFenetrePubliL1[%1]").arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BRHFenetrePubliL1[" << i << "] de la fenetre ." << std::endl;
		}
		BRHFenetrePubliL1[i]->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
		BRHFenetrePubliL1[i]->setMinimumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);
		BRHFenetrePubliL1[i]->setMaximumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);

		// Creation de son label d'affichage du nom du fichier
		//
		if( (LabelFenetrePubliL1[i]=new (std::nothrow) QLabel(BRHFenetrePubliL1[i],QString("SupervCLIMSO-BRHFenetrePubliL1[%1]-LabelFenetrePubliL1[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLabel:LabelFenetrePubliL1[" << i << "] de BRHFenetrePubliL1[" << i << "]." << std::endl;
		}
		LabelFenetrePubliL1[i]->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
		LabelFenetrePubliL1[i]->setMinimumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);
		LabelFenetrePubliL1[i]->setMaximumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);
		LabelFenetrePubliL1[i]->setText(QString::fromLocal8Bit(""));
		if( (i % 2) == 0 ) LabelFenetrePubliL1[i]->setPaletteBackgroundColor(COULEUR_LIGNE_IMG_PUB_0); else LabelFenetrePubliL1[i]->setPaletteBackgroundColor(COULEUR_LIGNE_IMG_PUB_1);

		// Creation du bouton poussoir de publication du fichier
		//
		if( (BoutonFenetrePubliL1[i]=new (std::nothrow) QPushButton(BRHFenetrePubliL1[i],QString("SupervCLIMSO-BRHFenetrePubliL1[%1]-BoutonFenetrePubliL1[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonFenetrePubliL1[" << i << "] de BRHFenetrePubliL1[" << i << "]." << std::endl;
		}
		BoutonFenetrePubliL1[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonFenetrePubliL1[i]->setMinimumSize(TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);
		BoutonFenetrePubliL1[i]->setMaximumSize(TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);
		BoutonFenetrePubliL1[i]->setText(QString::fromLocal8Bit("Publier"));

		// Le nom des fichiers
		//
		FichiersPubliL1[i].reserve(TAILLE_MINI_CHAINE);
		FichiersPubliL1[i]="";
	}


	// Widgets de la fenetre de publication BASS2000 des dernieres images de L2 ------------------------------------------------------------

	// La fenetre de publication en mode modeless (independante de la fenetre principale de l'application, non bloquante
	//  sur les entrees (non modale))
	//
	// On n'utilise pas une QMainWindow ou une QDockWindow car il n'y a pas besoin de menu, barre d'outils, ancre, barre de status...
	//
	if( (FenetrePubliL2=new (std::nothrow) QDialog(this,"SupervCLIMSO-QDialog-FenetrePubliL2",FALSE,Qt::WType_TopLevel | Qt::WStyle_Customize | Qt::WStyle_DialogBorder)) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QDialog:FenetrePubliL2 de la fenetre principale KMainWindow." << std::endl;
	}
	FenetrePubliL2->setCaption(QString::fromLocal8Bit("SupervCLIMSO : Publication BASS2000 images de L2"));
	FenetrePubliL2->setMinimumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE*NB_IMG_PUB_L2);
	FenetrePubliL2->setMaximumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE*NB_IMG_PUB_L2);

	NbImgPubliablesL2=0;	// Pour l'instant aucune image publiable

	// Boite de rangement vertical dans la fenetre de publication BASS2000 des dernieres images de L2
	//
	if( (BRVFenetrePubliL2=new (std::nothrow) QVBox(FenetrePubliL2,"SupervCLIMSO-QVBox-BRVFenetrePubliL2")) == NULL )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QVBox:BRVFenetrePubliL2 de la fenetre FenetrePubliL2." << std::endl;
	}
	BRVFenetrePubliL2->setMinimumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE*NB_IMG_PUB_L2);
	BRVFenetrePubliL2->setMaximumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE*NB_IMG_PUB_L2);

	// Boite de rangement horizontal de chaque image publiable
	//
	for( i=0; i < NB_IMG_PUB_L2; i++ )
	{
		if( (BRHFenetrePubliL2[i]=new (std::nothrow) QHBox(BRVFenetrePubliL2,QString("SupervCLIMSO-QHBox-BRHFenetrePubliL2[%1]").arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QHBox:BRHFenetrePubliL2[" << i << "] de la fenetre ." << std::endl;
		}
		BRHFenetrePubliL2[i]->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
		BRHFenetrePubliL2[i]->setMinimumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);
		BRHFenetrePubliL2[i]->setMaximumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE+TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);

		// Creation de son label d'affichage du nom du fichier
		//
		if( (LabelFenetrePubliL2[i]=new (std::nothrow) QLabel(BRHFenetrePubliL2[i],QString("SupervCLIMSO-BRHFenetrePubliL2[%1]-LabelFenetrePubliL2[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QLabel:LabelFenetrePubliL2[" << i << "] de BRHFenetrePubliL2[" << i << "]." << std::endl;
		}
		LabelFenetrePubliL2[i]->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
		LabelFenetrePubliL2[i]->setMinimumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);
		LabelFenetrePubliL2[i]->setMaximumSize(TAILLE_X_LABEL_NOM_IMG_PUBLIABLE,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);
		LabelFenetrePubliL2[i]->setText(QString::fromLocal8Bit(""));
		if( (i % 2) == 0 ) LabelFenetrePubliL2[i]->setPaletteBackgroundColor(COULEUR_LIGNE_IMG_PUB_0); else LabelFenetrePubliL2[i]->setPaletteBackgroundColor(COULEUR_LIGNE_IMG_PUB_1);

		// Creation du bouton poussoir de publication du fichier
		//
		if( (BoutonFenetrePubliL2[i]=new (std::nothrow) QPushButton(BRHFenetrePubliL2[i],QString("SupervCLIMSO-BRHFenetrePubliL2[%1]-BoutonFenetrePubliL2[%2]").arg(i).arg(i))) == NULL )
		{
			std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le widget QPushButton:BoutonFenetrePubliL2[" << i << "] de BRHFenetrePubliL2[" << i << "]." << std::endl;
		}
		BoutonFenetrePubliL2[i]->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
		BoutonFenetrePubliL2[i]->setMinimumSize(TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);
		BoutonFenetrePubliL2[i]->setMaximumSize(TAILLE_X_BOUTON_PUBLICATION_BASS2000,TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE);
		BoutonFenetrePubliL2[i]->setText(QString::fromLocal8Bit("Publier"));

		// Le nom des fichiers
		//
		FichiersPubliL2[i].reserve(TAILLE_MINI_CHAINE);
		FichiersPubliL2[i]="";
	}


	// Lecture des consignes sauvegardees
	//
	QFile FichierConsignes(CheminRepSuperviseur+"/"+FICHIER_SAUV_CONSIGNES);
	
	if( FichierConsignes.open(IO_ReadOnly) )
	{
		QTextStream FluxTexte(&FichierConsignes);	// Flux en mode texte
		QString Ligne;								// Une chaine qui sera une ligne du fichier

		FichierConsignes.at(0);

		// Chargement des consignes de SupervCLIMSO
		//
		for( i=0; i < NB_CONSIGNES; i++ )
		{
			Ligne=FluxTexte.readLine();
			if( !Ligne.isNull() ) EditConsigne[i]->setText(Ligne);
		}

		// Chargement des consignes pour les TerminOA
		//
		for( i=0; i < NB_TERMINOA; i++ )
		{
			// Chargement de la consigne du seuil bas de visualisation
			//
			Ligne=FluxTexte.readLine();
			if( !Ligne.isNull() ) SpinBoxCSB[i]->setValue(std::atoi(Ligne));

			// Chargement de la consigne du seuil haut de visualisation
			//
			Ligne=FluxTexte.readLine();
			if( !Ligne.isNull() ) SpinBoxCSH[i]->setValue(std::atoi(Ligne));

			// Chargement de la consigne de la puissance de LUT
			//
			Ligne=FluxTexte.readLine();
			if( !Ligne.isNull() ) SpinBoxCPuiLUT[i]->setValue(std::atoi(Ligne));
		}

		FichierConsignes.close();
	}


	// Connexion des slots aux boutons de commande des TerminOA apres l'initialisation des valeurs
	//
	connect(BoutonModeIC[TERMINOA_C1],SIGNAL(clicked()),this,SLOT(SlotBoutonModeIC_0()));
	connect(BoutonModeDiapo[TERMINOA_C1],SIGNAL(clicked()),this,SLOT(SlotBoutonModeDiapo_0()));
	connect(BoutonEchLin[TERMINOA_C1],SIGNAL(clicked()),this,SLOT(SlotBoutonEchLin_0()));
	connect(BoutonEchLog[TERMINOA_C1],SIGNAL(clicked()),this,SLOT(SlotBoutonEchLog_0()));
	connect(BoutonPalNB[TERMINOA_C1],SIGNAL(clicked()),this,SLOT(SlotBoutonPalNB_0()));
	connect(BoutonPalHalpha[TERMINOA_C1],SIGNAL(clicked()),this,SLOT(SlotBoutonPalHalpha_0()));
	connect(BoutonPalNoirOrangeBlanc[TERMINOA_C1],SIGNAL(clicked()),this,SLOT(SlotBoutonPalNoirOrangeBlanc_0()));
	connect(BoutonPalNoirVertBlanc[TERMINOA_C1],SIGNAL(clicked()),this,SLOT(SlotBoutonPalNoirVertBlanc_0()));
	connect(BoutonPalNoirBleuBlanc[TERMINOA_C1],SIGNAL(clicked()),this,SLOT(SlotBoutonPalNoirBleuBlanc_0()));
	connect(BoutonZ0[TERMINOA_C1],SIGNAL(clicked()),this,SLOT(SlotBoutonZ0_0()));
	connect(BoutonZ1[TERMINOA_C1],SIGNAL(clicked()),this,SLOT(SlotBoutonZ1_0()));
	connect(BoutonZ2[TERMINOA_C1],SIGNAL(clicked()),this,SLOT(SlotBoutonZ2_0()));
	connect(BoutonZ3[TERMINOA_C1],SIGNAL(clicked()),this,SLOT(SlotBoutonZ3_0()));
	connect(BoutonZ4[TERMINOA_C1],SIGNAL(clicked()),this,SLOT(SlotBoutonZ4_0()));
	connect(BoutonZ5[TERMINOA_C1],SIGNAL(clicked()),this,SLOT(SlotBoutonZ5_0()));
	connect(BoutonZ6[TERMINOA_C1],SIGNAL(clicked()),this,SLOT(SlotBoutonZ6_0()));
	connect(BoutonZ7[TERMINOA_C1],SIGNAL(clicked()),this,SLOT(SlotBoutonZ7_0()));
	connect(BoutonZ8[TERMINOA_C1],SIGNAL(clicked()),this,SLOT(SlotBoutonZ8_0()));
	connect(BoutonZ9[TERMINOA_C1],SIGNAL(clicked()),this,SLOT(SlotBoutonZ9_0()));
	connect(SpinBoxCSB[TERMINOA_C1],SIGNAL(valueChanged(int)),this,SLOT(SlotSpinBoxCSB_0(int)));
	connect(SpinBoxCSH[TERMINOA_C1],SIGNAL(valueChanged(int)),this,SLOT(SlotSpinBoxCSH_0(int)));
	connect(SpinBoxCPuiLUT[TERMINOA_C1],SIGNAL(valueChanged(int)),this,SLOT(SlotSpinBoxCPuiLUT_0(int)));

	connect(BoutonModeIC[TERMINOA_C2],SIGNAL(clicked()),this,SLOT(SlotBoutonModeIC_1()));
	connect(BoutonModeDiapo[TERMINOA_C2],SIGNAL(clicked()),this,SLOT(SlotBoutonModeDiapo_1()));
	connect(BoutonEchLin[TERMINOA_C2],SIGNAL(clicked()),this,SLOT(SlotBoutonEchLin_1()));
	connect(BoutonEchLog[TERMINOA_C2],SIGNAL(clicked()),this,SLOT(SlotBoutonEchLog_1()));
	connect(BoutonPalNB[TERMINOA_C2],SIGNAL(clicked()),this,SLOT(SlotBoutonPalNB_1()));
	connect(BoutonPalHalpha[TERMINOA_C2],SIGNAL(clicked()),this,SLOT(SlotBoutonPalHalpha_1()));
	connect(BoutonPalNoirOrangeBlanc[TERMINOA_C2],SIGNAL(clicked()),this,SLOT(SlotBoutonPalNoirOrangeBlanc_1()));
	connect(BoutonPalNoirVertBlanc[TERMINOA_C2],SIGNAL(clicked()),this,SLOT(SlotBoutonPalNoirVertBlanc_1()));
	connect(BoutonPalNoirBleuBlanc[TERMINOA_C2],SIGNAL(clicked()),this,SLOT(SlotBoutonPalNoirBleuBlanc_1()));
	connect(BoutonZ0[TERMINOA_C2],SIGNAL(clicked()),this,SLOT(SlotBoutonZ0_1()));
	connect(BoutonZ1[TERMINOA_C2],SIGNAL(clicked()),this,SLOT(SlotBoutonZ1_1()));
	connect(BoutonZ2[TERMINOA_C2],SIGNAL(clicked()),this,SLOT(SlotBoutonZ2_1()));
	connect(BoutonZ3[TERMINOA_C2],SIGNAL(clicked()),this,SLOT(SlotBoutonZ3_1()));
	connect(BoutonZ4[TERMINOA_C2],SIGNAL(clicked()),this,SLOT(SlotBoutonZ4_1()));
	connect(BoutonZ5[TERMINOA_C2],SIGNAL(clicked()),this,SLOT(SlotBoutonZ5_1()));
	connect(BoutonZ6[TERMINOA_C2],SIGNAL(clicked()),this,SLOT(SlotBoutonZ6_1()));
	connect(BoutonZ7[TERMINOA_C2],SIGNAL(clicked()),this,SLOT(SlotBoutonZ7_1()));
	connect(BoutonZ8[TERMINOA_C2],SIGNAL(clicked()),this,SLOT(SlotBoutonZ8_1()));
	connect(BoutonZ9[TERMINOA_C2],SIGNAL(clicked()),this,SLOT(SlotBoutonZ9_1()));
	connect(SpinBoxCSB[TERMINOA_C2],SIGNAL(valueChanged(int)),this,SLOT(SlotSpinBoxCSB_1(int)));
	connect(SpinBoxCSH[TERMINOA_C2],SIGNAL(valueChanged(int)),this,SLOT(SlotSpinBoxCSH_1(int)));
	connect(SpinBoxCPuiLUT[TERMINOA_C2],SIGNAL(valueChanged(int)),this,SLOT(SlotSpinBoxCPuiLUT_1(int)));

	connect(BoutonModeIC[TERMINOA_L1],SIGNAL(clicked()),this,SLOT(SlotBoutonModeIC_2()));
	connect(BoutonModeDiapo[TERMINOA_L1],SIGNAL(clicked()),this,SLOT(SlotBoutonModeDiapo_2()));
	connect(BoutonEchLin[TERMINOA_L1],SIGNAL(clicked()),this,SLOT(SlotBoutonEchLin_2()));
	connect(BoutonEchLog[TERMINOA_L1],SIGNAL(clicked()),this,SLOT(SlotBoutonEchLog_2()));
	connect(BoutonPalNB[TERMINOA_L1],SIGNAL(clicked()),this,SLOT(SlotBoutonPalNB_2()));
	connect(BoutonPalHalpha[TERMINOA_L1],SIGNAL(clicked()),this,SLOT(SlotBoutonPalHalpha_2()));
	connect(BoutonPalNoirOrangeBlanc[TERMINOA_L1],SIGNAL(clicked()),this,SLOT(SlotBoutonPalNoirOrangeBlanc_2()));
	connect(BoutonPalNoirVertBlanc[TERMINOA_L1],SIGNAL(clicked()),this,SLOT(SlotBoutonPalNoirVertBlanc_2()));
	connect(BoutonPalNoirBleuBlanc[TERMINOA_L1],SIGNAL(clicked()),this,SLOT(SlotBoutonPalNoirBleuBlanc_2()));
	connect(BoutonZ0[TERMINOA_L1],SIGNAL(clicked()),this,SLOT(SlotBoutonZ0_2()));
	connect(BoutonZ1[TERMINOA_L1],SIGNAL(clicked()),this,SLOT(SlotBoutonZ1_2()));
	connect(BoutonZ2[TERMINOA_L1],SIGNAL(clicked()),this,SLOT(SlotBoutonZ2_2()));
	connect(BoutonZ3[TERMINOA_L1],SIGNAL(clicked()),this,SLOT(SlotBoutonZ3_2()));
	connect(BoutonZ4[TERMINOA_L1],SIGNAL(clicked()),this,SLOT(SlotBoutonZ4_2()));
	connect(BoutonZ5[TERMINOA_L1],SIGNAL(clicked()),this,SLOT(SlotBoutonZ5_2()));
	connect(BoutonZ6[TERMINOA_L1],SIGNAL(clicked()),this,SLOT(SlotBoutonZ6_2()));
	connect(BoutonZ7[TERMINOA_L1],SIGNAL(clicked()),this,SLOT(SlotBoutonZ7_2()));
	connect(BoutonZ8[TERMINOA_L1],SIGNAL(clicked()),this,SLOT(SlotBoutonZ8_2()));
	connect(BoutonZ9[TERMINOA_L1],SIGNAL(clicked()),this,SLOT(SlotBoutonZ9_2()));
	connect(SpinBoxCSB[TERMINOA_L1],SIGNAL(valueChanged(int)),this,SLOT(SlotSpinBoxCSB_2(int)));
	connect(SpinBoxCSH[TERMINOA_L1],SIGNAL(valueChanged(int)),this,SLOT(SlotSpinBoxCSH_2(int)));
	connect(SpinBoxCPuiLUT[TERMINOA_L1],SIGNAL(valueChanged(int)),this,SLOT(SlotSpinBoxCPuiLUT_2(int)));

	connect(BoutonModeIC[TERMINOA_L2],SIGNAL(clicked()),this,SLOT(SlotBoutonModeIC_3()));
	connect(BoutonModeDiapo[TERMINOA_L2],SIGNAL(clicked()),this,SLOT(SlotBoutonModeDiapo_3()));
	connect(BoutonEchLin[TERMINOA_L2],SIGNAL(clicked()),this,SLOT(SlotBoutonEchLin_3()));
	connect(BoutonEchLog[TERMINOA_L2],SIGNAL(clicked()),this,SLOT(SlotBoutonEchLog_3()));
	connect(BoutonPalNB[TERMINOA_L2],SIGNAL(clicked()),this,SLOT(SlotBoutonPalNB_3()));
	connect(BoutonPalHalpha[TERMINOA_L2],SIGNAL(clicked()),this,SLOT(SlotBoutonPalHalpha_3()));
	connect(BoutonPalNoirOrangeBlanc[TERMINOA_L2],SIGNAL(clicked()),this,SLOT(SlotBoutonPalNoirOrangeBlanc_3()));
	connect(BoutonPalNoirVertBlanc[TERMINOA_L2],SIGNAL(clicked()),this,SLOT(SlotBoutonPalNoirVertBlanc_3()));
	connect(BoutonPalNoirBleuBlanc[TERMINOA_L2],SIGNAL(clicked()),this,SLOT(SlotBoutonPalNoirBleuBlanc_3()));
	connect(BoutonZ0[TERMINOA_L2],SIGNAL(clicked()),this,SLOT(SlotBoutonZ0_3()));
	connect(BoutonZ1[TERMINOA_L2],SIGNAL(clicked()),this,SLOT(SlotBoutonZ1_3()));
	connect(BoutonZ2[TERMINOA_L2],SIGNAL(clicked()),this,SLOT(SlotBoutonZ2_3()));
	connect(BoutonZ3[TERMINOA_L2],SIGNAL(clicked()),this,SLOT(SlotBoutonZ3_3()));
	connect(BoutonZ4[TERMINOA_L2],SIGNAL(clicked()),this,SLOT(SlotBoutonZ4_3()));
	connect(BoutonZ5[TERMINOA_L2],SIGNAL(clicked()),this,SLOT(SlotBoutonZ5_3()));
	connect(BoutonZ6[TERMINOA_L2],SIGNAL(clicked()),this,SLOT(SlotBoutonZ6_3()));
	connect(BoutonZ7[TERMINOA_L2],SIGNAL(clicked()),this,SLOT(SlotBoutonZ7_3()));
	connect(BoutonZ8[TERMINOA_L2],SIGNAL(clicked()),this,SLOT(SlotBoutonZ8_3()));
	connect(BoutonZ9[TERMINOA_L2],SIGNAL(clicked()),this,SLOT(SlotBoutonZ9_3()));
	connect(SpinBoxCSB[TERMINOA_L2],SIGNAL(valueChanged(int)),this,SLOT(SlotSpinBoxCSB_3(int)));
	connect(SpinBoxCSH[TERMINOA_L2],SIGNAL(valueChanged(int)),this,SLOT(SlotSpinBoxCSH_3(int)));
	connect(SpinBoxCPuiLUT[TERMINOA_L2],SIGNAL(valueChanged(int)),this,SLOT(SlotSpinBoxCPuiLUT_3(int)));


	// Connexion des slots aux boutons de commande des images publiables sur BASS2000
	//
	connect(BoutonFenetrePubliC1[0],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliC1_0()));
	connect(BoutonFenetrePubliC1[1],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliC1_1()));
	connect(BoutonFenetrePubliC1[2],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliC1_2()));
	connect(BoutonFenetrePubliC1[3],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliC1_3()));

	connect(BoutonFenetrePubliC2[0],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliC2_0()));
	connect(BoutonFenetrePubliC2[1],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliC2_1()));
	connect(BoutonFenetrePubliC2[2],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliC2_2()));
	connect(BoutonFenetrePubliC2[3],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliC2_3()));
	connect(BoutonFenetrePubliC2[4],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliC2_4()));
	connect(BoutonFenetrePubliC2[5],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliC2_5()));
	connect(BoutonFenetrePubliC2[6],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliC2_6()));
	connect(BoutonFenetrePubliC2[7],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliC2_7()));
	connect(BoutonFenetrePubliC2[8],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliC2_8()));
	connect(BoutonFenetrePubliC2[9],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliC2_9()));
	connect(BoutonFenetrePubliC2[10],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliC2_10()));
	connect(BoutonFenetrePubliC2[11],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliC2_11()));

	connect(BoutonFenetrePubliL1[0],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliL1_0()));
	connect(BoutonFenetrePubliL1[1],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliL1_1()));
	connect(BoutonFenetrePubliL1[2],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliL1_2()));
	connect(BoutonFenetrePubliL1[3],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliL1_3()));

	connect(BoutonFenetrePubliL2[0],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliL2_0()));
	connect(BoutonFenetrePubliL2[1],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliL2_1()));
	connect(BoutonFenetrePubliL2[2],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliL2_2()));
	connect(BoutonFenetrePubliL2[3],SIGNAL(clicked()),this,SLOT(SlotBoutonPubliL2_3()));


	// Creation/Ouverture du fichier de sauvegarde des logs de SupervCLIMSO
	//
	FichierLogsSupervCLIMSO.setName(CheminStockageDonnees+"/"+FICHIER_SAUV_LOGS_SUPERVCLIMSO);
	
	if( !FichierLogsSupervCLIMSO.open(IO_WriteOnly | IO_Append) )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer/modifier le fichier " << CheminStockageDonnees+"/"+FICHIER_SAUV_LOGS_SUPERVCLIMSO << "." << std::endl;
	}
	FluxFichierLogsSupervCLIMSO.setDevice(&FichierLogsSupervCLIMSO);


	// Creation/Ouverture du fichier de sauvegarde des valeurs de la temperature
	//
	FichierTemperatures.setName(CheminStockageDonnees+"/"+FICHIER_SAUV_TEMPERATURES);
	
	if( !FichierTemperatures.open(IO_WriteOnly | IO_Append) )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer/modifier le fichier " << CheminStockageDonnees+"/"+FICHIER_SAUV_TEMPERATURES << "." << std::endl;
	}
	FluxFichierTemperatures.setDevice(&FichierTemperatures);


	// Creation/Ouverture du fichier de sauvegarde de la fiche d'observation journaliere
	//
	FenetreFicheObservation->FichierFicheObservation.setName(CheminStockageDonnees+"/"+FICHIER_SAUV_FICHE_OBS+DateHeureUT.toString("yyyy-MM-dd")+".txt");
	
	if( !FenetreFicheObservation->FichierFicheObservation.open(IO_WriteOnly | IO_Append) )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer/modifier le fichier " << CheminStockageDonnees+"/"+FICHIER_SAUV_FICHE_OBS+DateHeureUT.toString("yyyy-MM-dd")+".txt" << std::endl;
	}
	FenetreFicheObservation->FluxFichierFicheObservation.setDevice(&FenetreFicheObservation->FichierFicheObservation);

	// Entete de la fiche d'observation
	//
	QString Entete=QString::fromLocal8Bit("Fiche d'observation journalière de CLIMSO pour le ")+DateHeureUT.toString("dd/MM/yyyy")+"\n\n";
	FenetreFicheObservation->FicheObservation->append("<B>"+Entete+"</B><BR>\n");
	if( FenetreFicheObservation->FichierFicheObservation.size() < 1 ) FenetreFicheObservation->FluxFichierFicheObservation << Entete;
}


// Destructeur de l'objet de la fenetre principale
//
SupervCLIMSO::~SupervCLIMSO()
{
	int i;		// Variable d'indice

	// On ferme la fenetre de visualisation des CamerOA
	//
	FenetreCamerOA->hide();

	// Sauvegarde des consignes
	//
	QFile FichierConsignes(CheminRepSuperviseur+"/"+FICHIER_SAUV_CONSIGNES);
	
	if( FichierConsignes.open(IO_WriteOnly) )
	{
		QTextStream FluxTexte(&FichierConsignes);	// Flux en mode texte
		QString Ligne;								// Une chaine qui sera une ligne du fichier
		
		FichierConsignes.at(0);

		// Sauvegarde des consignes de SupervCLIMSO
		//
		for( i=0; i < NB_CONSIGNES; i++ )
		{
			Ligne=EditConsigne[i]->text()+"\n";
			FluxTexte << Ligne;
		}

		// Sauvegarde des consignes pour les TerminOA
		//
		for( i=0; i < NB_TERMINOA; i++ )
		{
			// Sauvegarde de la consigne du seuil bas de visualisation
			//
			Ligne=QString("%1\n").arg(SpinBoxCSB[i]->value());
			FluxTexte << Ligne;

			// Sauvegarde de la consigne du seuil haut de visualisation
			//
			Ligne=QString("%1\n").arg(SpinBoxCSH[i]->value());
			FluxTexte << Ligne;

			// Sauvegarde de la consigne de la puissance de LUT
			//
			Ligne=QString("%1\n").arg(SpinBoxCPuiLUT[i]->value());
			FluxTexte << Ligne;
		}

		FichierConsignes.close();
	}
	
	// Arret du timer de pulsation de la seconde de temps
	//
	Pulsar1s->stop();

	// Fermeture des fichiers
	//
	FichierLogsSupervCLIMSO.close();
	FichierTemperatures.close();
	FenetreFicheObservation->FichierFicheObservation.close();

	
	// Destruction des objets de la fenetre de visualisation des CamerOA
	//
/*	delete VisuC1;
	delete VisuC2;
	delete VisuL1;
	delete VisuL2;
	delete BRHLFenetreCamerOA;
	delete BRHCFenetreCamerOA;
	delete BRVFenetreCamerOA;
	delete FenetreCamerOA;

	// Destruction des objets de la fenetre principale
	//
	delete Pulsar1s;
	delete LabelHeureUTBarreStatus;
	delete BarreStatus;
	delete BoutonModePointage;
	delete BoutonModePLU;
	delete BoutonModeCalibration;
	delete BoutonModeObservation;
	delete BoutonInitialisationAxes;
	delete LogoCLIMSO;
	delete Bouton10747;
	delete Bouton10770;
	delete Bouton10798;
	delete Bouton10830;
	delete SpinBoxDeltaXC2;
	delete SpinBoxDeltaYC2;
	delete BoutonPosesBias;
	delete BoutonPosesDark;
	delete BoutonSequencePosesImages;
	delete BoiteRangementHorizontal6aa;
	delete BoiteRangementHorizontal6ab;
	delete BoiteRangementHorizontal6ac;
	delete BoiteRangementHorizontal6ad;
	delete BoutonPoseImageC1;
	delete BoutonPoseImageC2;
	delete BoutonPoseImageL1;
	delete BoutonPoseImageL2;
	delete BoutonPoseBiasC1;
	delete BoutonPoseBiasC2;
	delete BoutonPoseBiasL1;
	delete BoutonPoseBiasL2;
	delete BoutonPoseDarkC1;
	delete BoutonPoseDarkC2;
	delete BoutonPoseDarkL1;
	delete BoutonPoseDarkL2;
	delete LabelEtatC1;
	delete LabelEtatC2;
	delete LabelEtatL1;
	delete LabelEtatL2;
	delete BoiteRangementHorizontal6a;
	delete BoiteRangementVertical6a;
	delete BoiteRangementHorizontal6b;
	delete BoiteRangementHorizontal6;
	delete BoiteRangementHorizontal5;
	delete BoiteRangementHorizontal4;
	delete BoiteRangementHorizontal3;
	delete BoiteRangementHorizontal2;
	delete BoiteRangementHorizontal1;
	delete BoiteRangementVertical;
*/
}


// Surcharge de la fonction de handler de l'evenement closeEvent de fermeture de la fenetre principale de l'application
//
void SupervCLIMSO::closeEvent(QCloseEvent *e)
{
	QString ChaineCmd;				// Chaine avec taille minimale pour la composition de commandes afin d'eviter un bogue QString et la rapidite
	ChaineCmd.reserve(TAILLE_MINI_CHAINE_CMD);

	if( QMessageBox::question(this,QString::fromLocal8Bit("SupervCLIMSO: ARRET DU LOGICIEL SUPERVISEUR ?"),QString::fromLocal8Bit("Voulez-vous vraiment SORTIR du logiciel superviseur de CLIMSO ?"),"Oui","Non",QString::null,1,1) == 0 )
	{
		if( QMessageBox::question(this,QString::fromLocal8Bit("SupervCLIMSO: Arrêt du logiciel superviseur: ARRET DE CLIMSO ?"),QString::fromLocal8Bit("Voulez-vous ARRETER CLIMSO (signal d'extinction électrique sur les CamerOA, TerminOA, RobOA) ou simplement sortir du logiciel superviseur ?"),"ARRETER CLIMSO","juste SORTIR",QString::null,0,1) == 0 )
		{
			int i;		// Variable indice
			int temp;	// Temperature de retour vers ambiante des Cameras CCD

			// On commence par se connecter sur le canal des commandes de chaque CamerOA et TerminOA non connecte
			//
			for( i=0; i < NB_CAMEROA; i++ )
			{
				if( !PLCommandeCamerOA[i]->Client->Connecte() ) PLCommandeCamerOA[i]->ConnexionAutorisee();
			}
			for( i=0; i < NB_TERMINOA; i++ )
			{
				if( !PLCommandeTerminOA[i]->Client->Connecte() ) PLCommandeTerminOA[i]->ConnexionAutorisee();
			}

			Log("!!! LA PROCEDURE D'ARRET ELECTRIQUE DE CLIMSO EST DECLENCHEE !!!");

			// On attend un petit moment pour la connexion rapide aux CamerOA et TerminOA
			//
			time_t debut=time(NULL);
			while( (time(NULL)-debut) < TEMPS_ATTENTE_CONN_ARRET_SUPERVCLIMSO ) appli->processEvents();

			// On positionne les axes aux positions de repos
			//
			DemandeRotationRoueOuverture(ModeRO_PLU);
			DemandeRotationRoueFiltresC2(FiltreC2_10830);
#if not VERSION_SANS_PLATINES
			// Désactivés car pertube le fonctionnement sans platines
			DemandeMouvementXPlatine(POSITION_REPOS_ARRET_CLIMSO_PLATINE);
			DemandeMouvementYPlatine(POSITION_REPOS_ARRET_CLIMSO_PLATINE);
#endif
			Log("RobOA: Axes aux positions de repos.");

			// On peut envoyer aux CamerOA le retour a la temperature ambiante
			//
			if( PLTemperatures->T[TEMP_SONDE_AMBIANTE_COUPOLE] != TEMPERATURE_NON_CONNUE )
			{
				temp=(int) PLTemperatures->T[TEMP_SONDE_AMBIANTE_COUPOLE];
				if( temp > 15 ) temp=15;
			} else temp=10;

			for( i=0; i < NB_CAMEROA; i++ )
			{
				if( PLCommandeCamerOA[i]->Client->Connecte() ) EnvoyerCommandeIntCamerOA(i,CAMEROA_CMD_CTEMP,temp);
			}

			Log("CamerOA: retour de la température des cameras CCD vers la température ambiante.");

			// On attend un petit moment pour que les ordres soient envoyes
			//
			debut=time(NULL);
			while( (time(NULL)-debut) < (TEMPS_ATTENTE_CONN_ARRET_SUPERVCLIMSO*2) ) appli->processEvents();


			// Arret du QTimer puisqu'il ne pourra pas rafraichir les positions et le widget apres la demande d'arret du superviseur
			//
			Pulsar1s->stop();


			// On peut envoyer le signal d'ARRET des machines
			//
			for( i=0; i < NB_CAMEROA; i++ )
			{
				if( PLCommandeCamerOA[i]->Client->Connecte() )
				{
					ChaineCmd=CmdClientCamerOA[CAMEROA_CMD_ARRET];
					ChaineCmd.append("\n");

					MutexEnvChaineBIO_CamerOA[i].lock();

					if( PLCommandeCamerOA[i]->Client->EnvoyerChaineBIO(ChaineCmd) <= 0 )
					{
						// Erreur lors de l'emission
						//
						Log("*** ERREUR: Impossible d'envoyer la commande d'arrêt au CamerOA de l'instrument "+InstrumentCLIMSO[i]+" ***");
					}

					MutexEnvChaineBIO_CamerOA[i].unlock();
				}
			}

			for( i=0; i < NB_TERMINOA; i++ )
			{
				if( PLCommandeTerminOA[i]->Client->Connecte() )
				{
					ChaineCmd=CmdClientTerminOA[TERMINOA_CMD_ARRET];
					ChaineCmd.append("\n");

					MutexEnvChaineBIO_TerminOA[i].lock();

					if( PLCommandeTerminOA[i]->Client->EnvoyerChaineBIO(ChaineCmd) <= 0 )
					{
						// Erreur lors de l'emission
						//
						Log("*** ERREUR: Impossible d'envoyer la commande d'arrêt au TerminOA de l'instrument "+InstrumentCLIMSO[i]+" ***");
					}

					MutexEnvChaineBIO_TerminOA[i].unlock();
				}
			}

			if( PLCommandeRobOA->Client->Connecte() )
			{
				ChaineCmd=CmdClientRobOA[ROBOA_CMD_ARRET];
				ChaineCmd.append("\n");

				MutexEnvChaineBIO_RobOA.lock();

				if( PLCommandeRobOA->Client->EnvoyerChaineBIO(ChaineCmd) <= 0 )
				{
					// Erreur lors de l'emission
					//
					Log("*** ERREUR: Impossible d'envoyer la commande d'arrêt au RobOA ***");
				}

				MutexEnvChaineBIO_RobOA.unlock();
			}

			// On attend un petit moment pour que les ordres soient envoyes
			//
			debut=time(NULL);
			while( (time(NULL)-debut) < (TEMPS_ATTENTE_CONN_ARRET_SUPERVCLIMSO/2) ) appli->processEvents();

			// On peut sortir du programme
			//
			e->accept();
		}
		else
		{
			// Sortie immédiate sans demander l'arret des machines
			//
			e->accept();
		}
	}
	else
	{
		// L'observateur a repondu non pour l'arret de CLIMSO
		//
		e->ignore();
	}
}


// Surcharge de la fonction de slot paintEvent heritee du QWidget
//
void SupervCLIMSO::paintEvent(QPaintEvent *event)
{
	QPaintEvent *e;		// Pour eviter un Warning a la compilation
	e=event;

	// On redimensionne la boite de rangement verticale
	//
	BoiteRangementVertical->resize(this->size());
}


// Slot du signal timeout() du QTimer de pulsation de la seconde de temps
//
void SupervCLIMSO::SlotPulsar1s(void)
{
	int i;				// Variable indice
	int aLoguer=false;	// Drapeau pour savoir si on doit loguer une pose automatique
	QString log;							// Chaine de log
	log.reserve(TAILLE_MINI_CHAINE_LOG);
	QString ChaineCmd;					// Chaine avec taille minimale pour la composition de commandes afin d'eviter un bogue QString et la rapidite
	ChaineCmd.reserve(TAILLE_MINI_CHAINE_CMD);



	// On recupere la date et l'heure courante UT du systeme
	//
	QDateTime DateHeureUT=QDateTime::currentDateTime(Qt::UTC);

	// Affichage de l'heure UT dans la barre de status
	//
	QString ChaineDateHeureUT;
	ChaineDateHeureUT.reserve(TAILLE_MINI_CHAINE);
	ChaineDateHeureUT=DateHeureUT.toString(Qt::ISODate)+" UT";
	ChaineDateHeureUT[10]=' ';
	LabelHeureUTBarreStatus->setText(ChaineDateHeureUT);

	// Si on doit rafraichir le label d'affichage du temps ecoule depuis la derniere acquisition
	//
	for( i=0 ; i < NB_CAMEROA; i++ )
	{
		if( DateHeureDerImg[i].date().year() != 1970 )
		{
			QString Chaine;
			Chaine.reserve(TAILLE_MINI_CHAINE);
			Chaine=DateHeureDerImg[i].toString("hh:mm:ss");
			int te_sec=-DateHeureUT.secsTo(DateHeureDerImg[i]);
			if( te_sec > 60 )
			{
				int min=te_sec/60;
				int sec=te_sec-min*60;
				Chaine+=QString("><B>%1m%2s</B>").arg(min).arg(sec);
			}
			else
			{
				Chaine+=QString("><B>%1s</B>").arg(te_sec);
			}

			switch( i )
			{
				case CAMEROA_C1:	TempsDepuisDerImgC1->setText(Chaine);	break;
				case CAMEROA_C2:	TempsDepuisDerImgC2->setText(Chaine);	break;
				case CAMEROA_L1:	TempsDepuisDerImgL1->setText(Chaine);	break;
				case CAMEROA_L2:	TempsDepuisDerImgL2->setText(Chaine);	break;
			}
		}
	}

	// On examine les consignes de SupervCLIMSO
	//
	// ATTENTION: On doit placer ce code a ce niveau pour que les variables soient correctement initialisees pour l'execution de ce slot
	//
	for( i=0; i < NB_CONSIGNES; i++ )
	{
		// Si une consigne a changee ou si elle n'a jamais ete examinee
		//
		if( EditConsigne[i]->isModified() || aEditConsignes[i] == CONSIGNE_EDIT_NON_INIT )
		{
			EditConsigne[i]->clearModified();	// On repasse en attribut non modifie pour le prochain test

			// Si la valeur saisie est acceptable
			//
			if( EditConsigne[i]->hasAcceptableInput() )
			{
				// Si la valeur n'est pas la meme qu'avant
				//
				if( aEditConsignes[i] != EditConsigne[i]->text() )
				{
					double valeur=EditConsigne[i]->text().toDouble();	// La valeur dans un double
					double fr;											// partie fractionnaire

					// On transforme la consigne dans son unite d'utilisation par le code de SupervCLIMSO
					//
					switch( i )
					{
						case CONSIGNE_C1_IMG_TP_CENTRAGE:
						case CONSIGNE_C1_IMG_TP_COUR:
						case CONSIGNE_C1_IMG_TP_PLU:
						case CONSIGNE_C2_IMG_TP_CENTRAGE_10830:
						case CONSIGNE_C2_IMG_TP_COUR_10747:
						case CONSIGNE_C2_IMG_TP_COUR_10770:
						case CONSIGNE_C2_IMG_TP_COUR_10798:
						case CONSIGNE_C2_IMG_TP_COUR_10830:
						case CONSIGNE_C2_PLU_TP_10747:
						case CONSIGNE_C2_PLU_TP_10770:
						case CONSIGNE_C2_PLU_TP_10798:
						case CONSIGNE_C2_PLU_TP_10830:
						case CONSIGNE_L1_IMG_TP_CENTRAGE:
						case CONSIGNE_L1_IMG_TP_SURF:
						case CONSIGNE_L1_IMG_TP_COUR:
						case CONSIGNE_L1_IMG_TP_PLU:
						case CONSIGNE_L2_IMG_TP_CENTRAGE:
						case CONSIGNE_L2_IMG_TP_SURF:
						case CONSIGNE_L2_IMG_TP_COUR:
						case CONSIGNE_L2_IMG_TP_PLU:
							// Consignes de temps de pose saisies en secondes a transformer en 1/10.000 de seconde
							//
							valeur*=10000.0;
							break;

						case CONSIGNE_CAISSON_INFO_ALERTE_INF:		CaissonInfoLinf=valeur;	break;
						case CONSIGNE_CAISSON_INFO_ALERTE_SUP:		CaissonInfoLsup=valeur;	break;
						case CONSIGNE_CAISSON_FILTREC1_ALERTE_INF:	FiltreC1Linf=valeur;	break;
						case CONSIGNE_CAISSON_FILTREC1_ALERTE_SUP:	FiltreC1Lsup=valeur;	break;
						case CONSIGNE_CAISSON_FILTREC2_ALERTE_INF:	FiltresC2Linf=valeur;	break;
						case CONSIGNE_CAISSON_FILTREC2_ALERTE_SUP:	FiltresC2Lsup=valeur;	break;
					}

					fr=modf(valeur,&valeur);
					if( fr > 0.5 ) valeur+=1.0;

					MutexConsignesDansUniteEntiere.lock();
					ConsignesDansUniteEntiere[i]=(int) valeur;

					// Selon la consigne modifiee dernierement on doit intervenir immediatement pour programmer la nouvelle consigne
					//
					switch( i )
					{
						case CONSIGNE_C1_IMG_TP_CENTRAGE:
							if( C1Actif ) EnvoyerCommandeIntCamerOA(CAMEROA_C1,CAMEROA_CMD_CTPC,ConsignesDansUniteEntiere[i]);
							break;
						case CONSIGNE_C1_TCCD:
							if( C1Actif ) EnvoyerCommandeIntCamerOA(CAMEROA_C1,CAMEROA_CMD_CTEMP,ConsignesDansUniteEntiere[i]);
							break;
						case CONSIGNE_C1_VENTILATEUR:
							if( C1Actif )
							{
								switch( ConsignesDansUniteEntiere[i] )
								{
									case 1:	EnvoyerCommandeCamerOA(CAMEROA_C1,CAMEROA_CMD_FANLOW);		break;
									case 2:	EnvoyerCommandeCamerOA(CAMEROA_C1,CAMEROA_CMD_FANMEDIUM);	break;
									case 3:	EnvoyerCommandeCamerOA(CAMEROA_C1,CAMEROA_CMD_FANHIGH);		break;
									default:	EnvoyerCommandeCamerOA(CAMEROA_C1,CAMEROA_CMD_FANLOW);	break;
								}
							}
							break;
						case CONSIGNE_C2_IMG_TP_CENTRAGE_10830:
							if( C2Actif ) EnvoyerCommandeIntCamerOA(CAMEROA_C2,CAMEROA_CMD_CTPC,ConsignesDansUniteEntiere[i]);
							break;
						case CONSIGNE_C2_TCCD:
							if( C2Actif ) EnvoyerCommandeIntCamerOA(CAMEROA_C2,CAMEROA_CMD_CTEMP,ConsignesDansUniteEntiere[i]);
							break;
						case CONSIGNE_C2_VENTILATEUR:
							if( C2Actif )
							{
								switch( ConsignesDansUniteEntiere[i] )
								{
									case 1:	EnvoyerCommandeCamerOA(CAMEROA_C2,CAMEROA_CMD_FANLOW);		break;
									case 2:	EnvoyerCommandeCamerOA(CAMEROA_C2,CAMEROA_CMD_FANMEDIUM);	break;
									case 3:	EnvoyerCommandeCamerOA(CAMEROA_C2,CAMEROA_CMD_FANHIGH);		break;
									default:	EnvoyerCommandeCamerOA(CAMEROA_C2,CAMEROA_CMD_FANLOW);	break;
								}
							}
							break;
						case CONSIGNE_L1_IMG_TP_CENTRAGE:
							if( L1Actif ) EnvoyerCommandeIntCamerOA(CAMEROA_L1,CAMEROA_CMD_CTPC,ConsignesDansUniteEntiere[i]);
							break;
						case CONSIGNE_L1_TCCD:
							if( L1Actif ) EnvoyerCommandeIntCamerOA(CAMEROA_L1,CAMEROA_CMD_CTEMP,ConsignesDansUniteEntiere[i]);
							break;
						case CONSIGNE_L1_VENTILATEUR:
							if( L1Actif )
							{
								switch( ConsignesDansUniteEntiere[i] )
								{
									case 1:	EnvoyerCommandeCamerOA(CAMEROA_L1,CAMEROA_CMD_FANLOW);		break;
									case 2:	EnvoyerCommandeCamerOA(CAMEROA_L1,CAMEROA_CMD_FANMEDIUM);	break;
									case 3:	EnvoyerCommandeCamerOA(CAMEROA_L1,CAMEROA_CMD_FANHIGH);		break;
									default:	EnvoyerCommandeCamerOA(CAMEROA_L1,CAMEROA_CMD_FANLOW);	break;
								}
							}
							break;
						case CONSIGNE_L2_IMG_TP_CENTRAGE:
							if( L2Actif ) EnvoyerCommandeIntCamerOA(CAMEROA_L2,CAMEROA_CMD_CTPC,ConsignesDansUniteEntiere[i]);
							break;
						case CONSIGNE_L2_TCCD:
							if( L2Actif ) EnvoyerCommandeIntCamerOA(CAMEROA_L2,CAMEROA_CMD_CTEMP,ConsignesDansUniteEntiere[i]);
							break;
						case CONSIGNE_L2_VENTILATEUR:
							if( L2Actif )
							{
								switch( ConsignesDansUniteEntiere[i] )
								{
									case 1:	EnvoyerCommandeCamerOA(CAMEROA_L2,CAMEROA_CMD_FANLOW);		break;
									case 2:	EnvoyerCommandeCamerOA(CAMEROA_L2,CAMEROA_CMD_FANMEDIUM);	break;
									case 3:	EnvoyerCommandeCamerOA(CAMEROA_L2,CAMEROA_CMD_FANHIGH);		break;
									default:	EnvoyerCommandeCamerOA(CAMEROA_L2,CAMEROA_CMD_FANLOW);	break;
								}
							}
							break;
					}
					MutexConsignesDansUniteEntiere.unlock();

					// Mise a jour de l'ancienne valeur
					//
					aEditConsignes[i]=EditConsigne[i]->text();
				}
			}
		}
	}

	// On recalcule les coordonnees heliographiques du centre du disque solaire toutes les minutes
	//
	if( DateHeureUT.time().second() == 10 )
	{
		CalcAstro.CoordonneesHeliographiquesCentreDisqueSolaire(JJ(DateHeureUT),&Po,&Lo,&Bo);
		GraphiqueSoleil->ParametresHeliographiques(Po,Lo,Bo);
	}

	// On evalue si les axes sont initialises dans la condition ou ils ne le sont pas
	//
	if( !AxesInitialises )
	{
		// Si on vient de trouver l'index de la roue d'ouverture
		//
		if( AxeIndexTrouve[AXE_ROUE_OUVERTURE] && (AxeRechIndexEnCours == AXE_ROUE_OUVERTURE) )
		{
			// Le mode d'observation est sans mode pour l'instant
			//
			aModeObservation=ModeRO_NonInitialise;
			ModeObservation=ModeRO_SansMode;

			// On peut maintenant demander la recherche de l'index de la roue a filtre de C2
			//
			AxeRechIndexEnCours=AXE_ROUE_FILTREC2;
			PLCommandeRobOA->DemandeRechercheIndexAxe(AXE_ROUE_FILTREC2);

			// Mise a jour des boutons
			//
			MAJEtatBoutonsFP();
		}

		// Si on vient de trouver l'index de la roue a filtre de C2 et que l'on a deja trouve l'index de la roue d'ouverture
		//
		// XXX A commenter pour la recherche roue à filtre

//		AxeIndexTrouve[AXE_ROUE_FILTREC2]=true;
//		aFiltreC2=FiltreC2_NonInitialise;
//		FiltreC2=FiltreC2_10830;


		if( AxeIndexTrouve[AXE_ROUE_FILTREC2] && (AxeRechIndexEnCours == AXE_ROUE_FILTREC2) )
		{
			// Le filtre actif n'est pas pas connu pour l'instant
			//
			aFiltreC2=FiltreC2_NonInitialise;
			FiltreC2=FiltreC2_SansFiltre;

// XXX A reactiver pour la la recherche platine X
#if not VERSION_SANS_PLATINES
			AxeRechIndexEnCours=AXE_PLATINE_X;
			PLCommandeRobOA->DemandeRechercheIndexAxe(AXE_PLATINE_X);

			// Mise a jour des boutons
			//
			MAJEtatBoutonsFP();
#endif
		}

		// Si on vient de trouver la position HOME de l'axe X de la platine et que l'on a deja trouve l'index de la roue a filtre de C2
		//
// XXX A reactiver pour la recherche platine X
#if not VERSION_SANS_PLATINES
		if( AxeIndexTrouve[AXE_PLATINE_X] && (AxeRechIndexEnCours == AXE_PLATINE_X) )
		{
			AxeRechIndexEnCours=AXE_PLATINE_Y;
			PLCommandeRobOA->DemandeRechercheIndexAxe(AXE_PLATINE_Y);

			// Mise a jour des boutons
			//
			MAJEtatBoutonsFP();
		}
#endif
// XXX A reactiver pour la recherche platine Y
		// Si on vient de trouver la position HOME de l'axe Y de la platine et que l'on a deja trouve la position HOME de la platine X
		//
#if not VERSION_SANS_PLATINES
		if( AxeIndexTrouve[AXE_PLATINE_Y] && (AxeRechIndexEnCours == AXE_PLATINE_Y) )
		{
			// Mise a jour des boutons
			//
			MAJEtatBoutonsFP();
		}
#endif
		// Si on a trouve tous les index
		//
#if not VERSION_SANS_PLATINES
		if( AxeIndexTrouve[AXE_ROUE_OUVERTURE] && AxeIndexTrouve[AXE_ROUE_FILTREC2] && AxeIndexTrouve[AXE_PLATINE_X] && AxeIndexTrouve[AXE_PLATINE_Y] )
#else
		if( AxeIndexTrouve[AXE_ROUE_OUVERTURE] && AxeIndexTrouve[AXE_ROUE_FILTREC2]) // XXX à enlever pour réactiver les platines et la roue à filtres
#endif
		{ // XXX Un ajout à cette condition a été fait en 2010
			AxesInitialises=true;
			AxeRechIndexEnCours=AXE_NON_RECHERCHE;

			// On positionne la roue d'ouverture a la position par defaut
			//
			DemandeRotationRoueOuverture(ModeRO_Pointage);

			// On positionne la roue a filtre de C2 a la position par defaut
			//
			DemandeRotationRoueFiltresC2(FiltreC2_10830);

			// On permet les widgets de controle des axes X et Y de la platine
			//
			SpinBoxDeltaXC2->setValue(POSITION_X_DEMARRAGE_CLIMSO_PLATINE); // XXX Ajouté en 2010
			SpinBoxDeltaXC2->setEnabled(true);
			SpinBoxDeltaYC2->setValue(POSITION_Y_DEMARRAGE_CLIMSO_PLATINE); // XXX Ajouté en 2010
			SpinBoxDeltaYC2->setEnabled(true);

			// Demande de deplacement de la platine X et Y a la position probable de demarrage des observations le matin
			//
			DemandeMouvementXPlatine(POSITION_X_DEMARRAGE_CLIMSO_PLATINE); // XXX Ajouté en 2010
			DemandeMouvementYPlatine(POSITION_Y_DEMARRAGE_CLIMSO_PLATINE); // XXX Ajouté en 2010
		}
	}

	// Si possible on demande la position des codeurs toutes les secondes
	//
	if( AxesInitialises )
	{
		MutexEnvChaineBIO_RobOA.lock();

		if( PLCommandeRobOA->Client->EnvoyerChaineBIO(CmdRobOAPosAxes) <= 0 )
		{
			// Erreur lors de l'emission
			//
			Log("*** ERREUR: Impossible d'envoyer la commande de demande de la position des axes en pas quadrature codeur ***");
		}

		MutexEnvChaineBIO_RobOA.unlock();
	}

	// Si on doit faire un rafraichissement des temperatures toutes les minutes
	//
	// Le Web IO Thermometer est configure pour donner une valeur de temperature toutes les minutes
	//
	if( DateHeureUT.time().second() == 0 || PLTemperatures->PremierRafraichissement )
	{
		// Autorisation de connexion avec requete sur le serveur des temperatures (le thread n'autorise plus la connexion apres la requete et attend donc le prochain passage)
		//
		PLTemperatures->ConnexionAutorisee();

		// Ce n'est plus le premier rafraichissement
		//
		PLTemperatures->PremierRafraichissement=false;
	}

	// On demande toutes les 5s :
	//	- la temperature et la puissance peltier des CamerOA toutes les 5s ;
	//
	if( DateHeureUT.time().second() % 5 == 0 )
	{
		// Les temperatures et puissances des CamerOA
		//
		if( C1Actif && PLCommandeCamerOA[CAMEROA_C1]->Client->Connecte() )
		{
			MutexEnvChaineBIO_CamerOA[CAMEROA_C1].lock();

			if( PLCommandeCamerOA[CAMEROA_C1]->Client->EnvoyerChaineBIO(CmdCamerOATempCCD) <= 0 )
			{
				// Erreur lors de l'emission
				//
				Log("*** ERREUR: Impossible d'envoyer la commande de demande de la température de la caméra CCD à l'instrument "+InstrumentCLIMSO[CAMEROA_C1]+" ***");
			}

			if( PLCommandeCamerOA[CAMEROA_C1]->Client->EnvoyerChaineBIO(CmdCamerOAPuiPeltier) <= 0 )
			{
				// Erreur lors de l'emission
				//
				Log("*** ERREUR: Impossible d'envoyer la commande de demande de la puissance des peltiers de la caméra CCD à l'instrument "+InstrumentCLIMSO[CAMEROA_C1]+" ***");
			}

			MutexEnvChaineBIO_CamerOA[CAMEROA_C1].unlock();
		}
		if( C2Actif && PLCommandeCamerOA[CAMEROA_C2]->Client->Connecte() )
		{
			MutexEnvChaineBIO_CamerOA[CAMEROA_C2].lock();

			if( PLCommandeCamerOA[CAMEROA_C2]->Client->EnvoyerChaineBIO(CmdCamerOATempCCD) <= 0 )
			{
				// Erreur lors de l'emission
				//
				Log("*** ERREUR: Impossible d'envoyer la commande de demande de la température de la caméra CCD à l'instrument "+InstrumentCLIMSO[CAMEROA_C2]+" ***");
			}

			if( PLCommandeCamerOA[CAMEROA_C2]->Client->EnvoyerChaineBIO(CmdCamerOAPuiPeltier) <= 0 )
			{
				// Erreur lors de l'emission
				//
				Log("*** ERREUR: Impossible d'envoyer la commande de demande de la puissance des peltiers de la caméra CCD à l'instrument "+InstrumentCLIMSO[CAMEROA_C2]+" ***");
			}

			MutexEnvChaineBIO_CamerOA[CAMEROA_C2].unlock();
		}
		if( L1Actif && PLCommandeCamerOA[CAMEROA_L1]->Client->Connecte() )
		{
			MutexEnvChaineBIO_CamerOA[CAMEROA_L1].lock();

			if( PLCommandeCamerOA[CAMEROA_L1]->Client->EnvoyerChaineBIO(CmdCamerOATempCCD) <= 0 )
			{
				// Erreur lors de l'emission
				//
				Log("*** ERREUR: Impossible d'envoyer la commande de demande de la température de la caméra CCD à l'instrument "+InstrumentCLIMSO[CAMEROA_L1]+" ***");
			}

			if( PLCommandeCamerOA[CAMEROA_L1]->Client->EnvoyerChaineBIO(CmdCamerOAPuiPeltier) <= 0 )
			{
				// Erreur lors de l'emission
				//
				Log("*** ERREUR: Impossible d'envoyer la commande de demande de la puissance des peltiers de la caméra CCD à l'instrument "+InstrumentCLIMSO[CAMEROA_L1]+" ***");
			}

			MutexEnvChaineBIO_CamerOA[CAMEROA_L1].unlock();
		}
		if( L2Actif && PLCommandeCamerOA[CAMEROA_L2]->Client->Connecte() )
		{
			MutexEnvChaineBIO_CamerOA[CAMEROA_L2].lock();

			if( PLCommandeCamerOA[CAMEROA_L2]->Client->EnvoyerChaineBIO(CmdCamerOATempCCD) <= 0 )
			{
				// Erreur lors de l'emission
				//
				Log("*** ERREUR: Impossible d'envoyer la commande de demande de la température de la caméra CCD à l'instrument "+InstrumentCLIMSO[CAMEROA_L2]+" ***");
			}

			if( PLCommandeCamerOA[CAMEROA_L2]->Client->EnvoyerChaineBIO(CmdCamerOAPuiPeltier) <= 0 )
			{
				// Erreur lors de l'emission
				//
				Log("*** ERREUR: Impossible d'envoyer la commande de demande de la puissance des peltiers de la caméra CCD à l'instrument "+InstrumentCLIMSO[CAMEROA_L2]+" ***");
			}

			MutexEnvChaineBIO_CamerOA[CAMEROA_L2].unlock();
		}
	}

	// Si il y a une alerte sur une sonde de temperature
	//
	for( i=0; i < NB_SONDES_TEMPERATURE; i++ )
	{
		if( AlerteFenetreTemperatures[i] )
		{
			QColor CouleurAlerteCourante;

			if( DateHeureUT.time().second() % 2 == 0 ) CouleurAlerteCourante=COULEUR_LIGNE_TEMP_SONDE_NONOK; else CouleurAlerteCourante=COULEUR_LIGNE_TEMP_SONDE_OK;

			LabelTemperatures[i]->setPaletteBackgroundColor(CouleurAlerteCourante);
		}
	}


	// Si on doit declancher des acquisitions automatiques toutes les 20 secondes
	//
switch( DateHeureUT.time().second() )
{
case 0:
case 1:
case 20:
case 21:
case 40:
case 41:

	if( C1Actif ) if( !PoseEnCours[CAMEROA_C1] ) if( CBAcqAuto[CAMEROA_C1]->isChecked() ) if( ModeObservation != ModeRO_SansMode && (CBCompoSeqAcq[ACQUISITION_C1_COUR]->isChecked()) )
	{
		aLoguer=true;
		log+=" "+InstrumentCLIMSO[CAMEROA_C1];

		PoseEnCours[CAMEROA_C1]=true;

		PLAcqC1->DemandeListeAcquisitions(POSE_LUMIERE,ModeObservation,CBCompoSeqAcq[ACQUISITION_C1_COUR]->isChecked());

		// Faire croire a un changement pour redessiner les boutons
		//
		aC1Actif=-1;
		aModeObservation=ModeRO_NonInitialise;
	}

	if( C2Actif ) if( !PoseEnCours[CAMEROA_C2] ) if( CBAcqAuto[CAMEROA_C2]->isChecked() ) if( ModeObservation != ModeRO_SansMode && FiltreC2 != FiltreC2_SansFiltre && (CBCompoSeqAcq[ACQUISITION_C2_10747]->isChecked() || CBCompoSeqAcq[ACQUISITION_C2_10770]->isChecked() || CBCompoSeqAcq[ACQUISITION_C2_10798]->isChecked() || CBCompoSeqAcq[ACQUISITION_C2_10830]->isChecked()) )
	{
		aLoguer=true;
		log+=" "+InstrumentCLIMSO[CAMEROA_C2];

		PoseEnCours[CAMEROA_C2]=true;

		PLAcqC2->DemandeListeAcquisitions(POSE_LUMIERE,ModeObservation,CBCompoSeqAcq[ACQUISITION_C2_10747]->isChecked(),CBCompoSeqAcq[ACQUISITION_C2_10770]->isChecked(),CBCompoSeqAcq[ACQUISITION_C2_10798]->isChecked(),CBCompoSeqAcq[ACQUISITION_C2_10830]->isChecked());

		// Faire croire a un changement pour redessiner les boutons
		//
		aC2Actif=-1;
		aModeObservation=ModeRO_NonInitialise;
	}

	if( L1Actif ) if( !PoseEnCours[CAMEROA_L1] ) if( CBAcqAuto[CAMEROA_L1]->isChecked() ) if( ModeObservation != ModeRO_SansMode && (CBCompoSeqAcq[ACQUISITION_L1_SURF]->isChecked() || CBCompoSeqAcq[ACQUISITION_L1_COUR]->isChecked()) )
	{
		aLoguer=true;
		log+=" "+InstrumentCLIMSO[CAMEROA_L1];

		PoseEnCours[CAMEROA_L1]=true;

		PLAcqL1->DemandeListeAcquisitions(POSE_LUMIERE,ModeObservation,CBCompoSeqAcq[ACQUISITION_L1_SURF]->isChecked(),CBCompoSeqAcq[ACQUISITION_L1_COUR]->isChecked());

		// Faire croire a un changement pour redessiner les boutons
		//
		aL1Actif=-1;
		aModeObservation=ModeRO_NonInitialise;
	}

	if( L2Actif ) if( !PoseEnCours[CAMEROA_L2] ) if( CBAcqAuto[CAMEROA_L2]->isChecked() ) if( ModeObservation != ModeRO_SansMode && (CBCompoSeqAcq[ACQUISITION_L2_SURF]->isChecked() || CBCompoSeqAcq[ACQUISITION_L2_COUR]->isChecked()) )
	{
		aLoguer=true;
		log+=" "+InstrumentCLIMSO[CAMEROA_L2];

		PoseEnCours[CAMEROA_L2]=true;

		PLAcqL2->DemandeListeAcquisitions(POSE_LUMIERE,ModeObservation,CBCompoSeqAcq[ACQUISITION_L2_SURF]->isChecked(),CBCompoSeqAcq[ACQUISITION_L2_COUR]->isChecked());

		// Faire croire a un changement pour redessiner les boutons
		//
		aL2Actif=-1;
		aModeObservation=ModeRO_NonInitialise;
	}

	if( aLoguer )
	{
		log="Pose(s) automatique(s) d'observation déclenchée(s) sur l(es) instrument(s)"+log+".";

		Log(log);

		MAJEtatBoutonsFP();
	}
break;
}

}


// Slot du bouton de demande d'initialisation des axes de CLIMSO
//
void SupervCLIMSO::SlotBoutonInitialisationAxes(void)
{
	if( PoseEnCours[CAMEROA_C1] || PoseEnCours[CAMEROA_C2] || PoseEnCours[CAMEROA_L1] || PoseEnCours[CAMEROA_L2] ) return;

	BoutonInitialisationAxes->setPixmap(QPixmap(IconModeInitialisationActif_xpm));

	// Les axes ne sont pas initialises
	//
	AxesInitialises=false;

	AxeIndexTrouve[AXE_ROUE_OUVERTURE]=false;
	aModeObservation=ModeRO_NonInitialise;
	ModeObservation=ModeRO_SansMode;

	AxeIndexTrouve[AXE_ROUE_FILTREC2]=false;
	aFiltreC2=FiltreC2_NonInitialise;
	FiltreC2=FiltreC2_SansFiltre;

	// On autorise la connexion au RobOA
	//
	PLCommandeRobOA->ConnexionAutorisee();

	// On demande la recherche des index et position de repos
	//
	AxeRechIndexEnCours=AXE_ROUE_OUVERTURE;
	PLCommandeRobOA->DemandeRechercheIndexAxe(AXE_ROUE_OUVERTURE);

	Log("Début: Recherche des index et positions de repos des axes de CLIMSO.");

	MAJEtatBoutonsFP();
}


// Slot du bouton de demande de la fenetre de saisie des consignes de SupervCLIMSO
//
void SupervCLIMSO::SlotBoutonConsignes(void)
{
	// Si le mot de passe d'acces aux consignes n'est pas connu
	//
	if( !MotDePasseConsignes )
	{
		bool bouton_ok;

		QString mdp=QInputDialog::getText(QString::fromLocal8Bit("SupervCLIMSO : Accès aux consignes"),QString::fromLocal8Bit("Entrez le mot de passe d'accès aux consignes:"),QLineEdit::Password,QString::null,&bouton_ok,this,"SupervCLIMSO-MDP-Consignes");

		if( bouton_ok && mdp == "arbizon" ) MotDePasseConsignes=true;
	}

	MAJEtatBoutonsFP();

	if( MotDePasseConsignes ) FenetreConsignes->show();
}


// Slot du bouton de demande de passage de CLIMSO en mode pointage
//
void SupervCLIMSO::SlotBoutonModePointage(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( PoseEnCours[CAMEROA_C1] | PoseEnCours[CAMEROA_C2] | PoseEnCours[CAMEROA_L1] | PoseEnCours[CAMEROA_L2] )
	{
		MessageUnePoseEnCoursModifModeImpossible();
		return;
	}

	DemandeRotationRoueOuverture(ModeRO_Pointage);

	MAJEtatBoutonsFP();
}


// Slot du bouton de demande de passage de CLIMSO en mode PLU
//
void SupervCLIMSO::SlotBoutonModePLU(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( PoseEnCours[CAMEROA_C1] | PoseEnCours[CAMEROA_C2] | PoseEnCours[CAMEROA_L1] | PoseEnCours[CAMEROA_L2] )
	{
		MessageUnePoseEnCoursModifModeImpossible();
		return;
	}

	DemandeRotationRoueOuverture(ModeRO_PLU);

	MAJEtatBoutonsFP();
}


// Slot du bouton de demande de passage de CLIMSO en mode calibration
//
void SupervCLIMSO::SlotBoutonModeCalibration(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( PoseEnCours[CAMEROA_C1] | PoseEnCours[CAMEROA_C2] | PoseEnCours[CAMEROA_L1] | PoseEnCours[CAMEROA_L2] )
	{
		MessageUnePoseEnCoursModifModeImpossible();
		return;
	}

	DemandeRotationRoueOuverture(ModeRO_Calibration);

	MAJEtatBoutonsFP();
}


// Slot du bouton de demande de passage de CLIMSO en mode observation
//
void SupervCLIMSO::SlotBoutonModeObservation(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( PoseEnCours[CAMEROA_C1] | PoseEnCours[CAMEROA_C2] | PoseEnCours[CAMEROA_L1] | PoseEnCours[CAMEROA_L2] )
	{
		MessageUnePoseEnCoursModifModeImpossible();
		return;
	}

	DemandeRotationRoueOuverture(ModeRO_Observation);

	MAJEtatBoutonsFP();
}


// Slot du bouton de demande de passage en filtre C2 10747 nm
//
void SupervCLIMSO::SlotBouton10747(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( PoseEnCours[CAMEROA_C2] )
	{
		MessageUnePoseEnCoursC2ModifFiltreImpossible();
		return;
	}

	DemandeRotationRoueFiltresC2(FiltreC2_10747);

	MAJEtatBoutonsFP();
}


// Slot du bouton de demande de passage en filtre C2 10770 nm
//
void SupervCLIMSO::SlotBouton10770(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( PoseEnCours[CAMEROA_C2] )
	{
		MessageUnePoseEnCoursC2ModifFiltreImpossible();
		return;
	}

	DemandeRotationRoueFiltresC2(FiltreC2_10770);

	MAJEtatBoutonsFP();
}


// Slot du bouton de demande de passage en filtre C2 10798 nm
//
void SupervCLIMSO::SlotBouton10798(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( PoseEnCours[CAMEROA_C2] )
	{
		MessageUnePoseEnCoursC2ModifFiltreImpossible();
		return;
	}

	DemandeRotationRoueFiltresC2(FiltreC2_10798);

	MAJEtatBoutonsFP();
}


// Slot du bouton de demande de passage en filtre C2 10830 nm
//
void SupervCLIMSO::SlotBouton10830(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( PoseEnCours[CAMEROA_C2] )
	{
		MessageUnePoseEnCoursC2ModifFiltreImpossible();
		return;
	}

	DemandeRotationRoueFiltresC2(FiltreC2_10830);

	MAJEtatBoutonsFP();
}


// Slot du widget d'entree de la consigne de decalage en x de C2
//
void SupervCLIMSO::SlotSpinBoxDeltaXC2(int value)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( PoseEnCours[CAMEROA_C2] )
	{
		MessageUnePoseEnCoursC2ModifFiltreImpossible();
		return;
	}

	DemandeMouvementXPlatine(value);

	MAJEtatBoutonsFP();
}


// Slot du widget d'entree de la consigne de decalage en y de C2
//
void SupervCLIMSO::SlotSpinBoxDeltaYC2(int value)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( PoseEnCours[CAMEROA_C2] )
	{
		MessageUnePoseEnCoursC2ModifFiltreImpossible();
		return;
	}

	DemandeMouvementYPlatine(value);

	MAJEtatBoutonsFP();
}


// Slot du bouton etat de C1
//
void SupervCLIMSO::SlotBoutonEtatC1(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( PoseEnCours[CAMEROA_C1] ) return;

	if( C1Actif ) C1Actif=false; else C1Actif=true;

	if( C1Actif ) BoutonEtatC1->setPixmap(QPixmap(IconC1Actif_xpm)); else BoutonEtatC1->setPixmap(QPixmap(IconC1Inactif_xpm));

	if( C1Actif )
	{
		PLCommandeCamerOA[CAMEROA_C1]->ConnexionAutorisee();
		PLDonneesCamerOA[CAMEROA_C1]->ConnexionAutorisee();
		PLCommandeTerminOA[TERMINOA_C1]->ConnexionAutorisee();
		PLDonneesTerminOA[TERMINOA_C1]->ConnexionAutorisee();
	}
	else
	{
		PLCommandeCamerOA[CAMEROA_C1]->ConnexionNonAutorisee();
		PLDonneesCamerOA[CAMEROA_C1]->ConnexionNonAutorisee();
		PLCommandeTerminOA[TERMINOA_C1]->ConnexionNonAutorisee();
		PLDonneesTerminOA[TERMINOA_C1]->ConnexionNonAutorisee();

		LCDTempCamerOAC1->display("");
		LCDPuiCamerOAC1->display("");

		ConsignesCamerOAInitialisees[CAMEROA_C1]=false;
		ConsignesTerminOAInitialisees[TERMINOA_C1]=false;
	}

	MAJEtatBoutonsFP();

	update();
}


// Slot du bouton etat de C2
//
void SupervCLIMSO::SlotBoutonEtatC2(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( PoseEnCours[CAMEROA_C2] ) return;

	if( C2Actif ) C2Actif=false; else C2Actif=true;

	if( C2Actif ) BoutonEtatC2->setPixmap(QPixmap(IconC2Actif_xpm)); else BoutonEtatC2->setPixmap(QPixmap(IconC2Inactif_xpm));

	if( C2Actif )
	{
		PLCommandeCamerOA[CAMEROA_C2]->ConnexionAutorisee();
		PLDonneesCamerOA[CAMEROA_C2]->ConnexionAutorisee();
		PLCommandeTerminOA[TERMINOA_C2]->ConnexionAutorisee();
		PLDonneesTerminOA[TERMINOA_C2]->ConnexionAutorisee();
	}
	else
	{
		PLCommandeCamerOA[CAMEROA_C2]->ConnexionNonAutorisee();
		PLDonneesCamerOA[CAMEROA_C2]->ConnexionNonAutorisee();
		PLCommandeTerminOA[TERMINOA_C2]->ConnexionNonAutorisee();
		PLDonneesTerminOA[TERMINOA_C2]->ConnexionNonAutorisee();

		LCDTempCamerOAC2->display("");
		LCDPuiCamerOAC2->display("");

		ConsignesCamerOAInitialisees[CAMEROA_C2]=false;
		ConsignesTerminOAInitialisees[TERMINOA_C2]=false;
	}

	MAJEtatBoutonsFP();

	update();
}


// Slot du bouton etat de L1
//
void SupervCLIMSO::SlotBoutonEtatL1(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( PoseEnCours[CAMEROA_L1] ) return;

	if( L1Actif ) L1Actif=false; else L1Actif=true;

	if( L1Actif ) BoutonEtatL1->setPixmap(QPixmap(IconL1Actif_xpm)); else BoutonEtatL1->setPixmap(QPixmap(IconL1Inactif_xpm));

	if( L1Actif )
	{
		PLCommandeCamerOA[CAMEROA_L1]->ConnexionAutorisee();
		PLDonneesCamerOA[CAMEROA_L1]->ConnexionAutorisee();
		PLCommandeTerminOA[TERMINOA_L1]->ConnexionAutorisee();
		PLDonneesTerminOA[TERMINOA_L1]->ConnexionAutorisee();
	}
	else
	{
		PLCommandeCamerOA[CAMEROA_L1]->ConnexionNonAutorisee();
		PLDonneesCamerOA[CAMEROA_L1]->ConnexionNonAutorisee();
		PLCommandeTerminOA[TERMINOA_L1]->ConnexionNonAutorisee();
		PLDonneesTerminOA[TERMINOA_L1]->ConnexionNonAutorisee();

		LCDTempCamerOAL1->display("");
		LCDPuiCamerOAL1->display("");

		ConsignesCamerOAInitialisees[CAMEROA_L1]=false;
		ConsignesTerminOAInitialisees[TERMINOA_L1]=false;
	}

	MAJEtatBoutonsFP();

	update();
}


// Slot du bouton etat de L2
//
void SupervCLIMSO::SlotBoutonEtatL2(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( PoseEnCours[CAMEROA_L2] ) return;

	if( L2Actif ) L2Actif=false; else L2Actif=true;

	if( L2Actif ) BoutonEtatL2->setPixmap(QPixmap(IconL2Actif_xpm)); else BoutonEtatL2->setPixmap(QPixmap(IconL2Inactif_xpm));

	if( L2Actif )
	{
		PLCommandeCamerOA[CAMEROA_L2]->ConnexionAutorisee();
		PLDonneesCamerOA[CAMEROA_L2]->ConnexionAutorisee();
		PLCommandeTerminOA[TERMINOA_L2]->ConnexionAutorisee();
		PLDonneesTerminOA[TERMINOA_L2]->ConnexionAutorisee();
	}
	else
	{
		PLCommandeCamerOA[CAMEROA_L2]->ConnexionNonAutorisee();
		PLDonneesCamerOA[CAMEROA_L2]->ConnexionNonAutorisee();
		PLCommandeTerminOA[TERMINOA_L2]->ConnexionNonAutorisee();
		PLDonneesTerminOA[TERMINOA_L2]->ConnexionNonAutorisee();

		LCDTempCamerOAL2->display("");
		LCDPuiCamerOAL2->display("");

		ConsignesCamerOAInitialisees[CAMEROA_L2]=false;
		ConsignesTerminOAInitialisees[TERMINOA_L2]=false;
	}

	MAJEtatBoutonsFP();

	update();
}


// Slot du bouton de demande de pose bias pour C1
//
void SupervCLIMSO::SlotBoutonPoseBiasC1(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}

	// Si il n'y a pas de pose en cours sur C1
	//
	if( !PoseEnCours[CAMEROA_C1] ) DeclencherPoseBias(true,CAMEROA_C1); else MessageUnePoseDejaEnCoursSur(CAMEROA_C1);

	MAJEtatBoutonsFP();
}


// Slot du bouton de demande de pose bias pour C2
//
void SupervCLIMSO::SlotBoutonPoseBiasC2(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}

	// Si il n'y a pas de pose en cours sur C2
	//
	if( !PoseEnCours[CAMEROA_C2] ) DeclencherPoseBias(true,CAMEROA_C2); else MessageUnePoseDejaEnCoursSur(CAMEROA_C2);

	MAJEtatBoutonsFP();
}


// Slot du bouton de demande de pose bias pour L1
//
void SupervCLIMSO::SlotBoutonPoseBiasL1(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}

	// Si il n'y a pas de pose en cours sur L1
	//
	if( !PoseEnCours[CAMEROA_L1] ) DeclencherPoseBias(true,CAMEROA_L1); else MessageUnePoseDejaEnCoursSur(CAMEROA_L1);

	MAJEtatBoutonsFP();
}


// Slot du bouton de demande de pose bias pour L2
//
void SupervCLIMSO::SlotBoutonPoseBiasL2(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}

	// Si il n'y a pas de pose en cours sur L2
	//
	if( !PoseEnCours[CAMEROA_L2] ) DeclencherPoseBias(true,CAMEROA_L2); else MessageUnePoseDejaEnCoursSur(CAMEROA_L2);

	MAJEtatBoutonsFP();
}


// Slot du bouton de demande de pose dark pour C1
//
void SupervCLIMSO::SlotBoutonPoseDarkC1(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}

	// Si il n'y a pas de pose en cours sur C1
	//
	if( !PoseEnCours[CAMEROA_C1] )
	{
		PoseEnCours[CAMEROA_C1]=true;

		PLAcqC1->DemandeListeAcquisitions(POSE_DARK,ModeObservation,/* CBCompoSeqAcq[ACQUISITION_C1_COUR]->isChecked() */ true);	// On la réalise a chaque fois

		Log("Pose de DARK déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_C1]+".");

		// Faire croire a un changement pour redessiner les boutons
		//
		aC1Actif=-1;
		aModeObservation=ModeRO_NonInitialise;
	}
	else
	{
		MessageUnePoseDejaEnCoursSur(CAMEROA_C1);
	}
}


// Slot du bouton de demande de pose dark pour C2
//
void SupervCLIMSO::SlotBoutonPoseDarkC2(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}

	// Si il n'y a pas de pose en cours sur C2
	//
	if( !PoseEnCours[CAMEROA_C2] )
	{
		PoseEnCours[CAMEROA_C2]=true;

		switch( FiltreC2 )
		{
			case FiltreC2_10747:
				PLAcqC2->DemandeListeAcquisitions(POSE_DARK,ModeObservation,true,false,false,false);
				break;
			case FiltreC2_10770:
				PLAcqC2->DemandeListeAcquisitions(POSE_DARK,ModeObservation,false,true,false,false);
				break;
			case FiltreC2_10798:
				PLAcqC2->DemandeListeAcquisitions(POSE_DARK,ModeObservation,false,false,true,false);
				break;
			case FiltreC2_10830:
				PLAcqC2->DemandeListeAcquisitions(POSE_DARK,ModeObservation,false,false,false,true);
				break;
			default:	break;
		}

		Log("Pose de DARK déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_C2]+".");

		// Faire croire a un changement pour redessiner les boutons
		//
		aC2Actif=-1;
		aModeObservation=ModeRO_NonInitialise;
	}
	else
	{
		MessageUnePoseDejaEnCoursSur(CAMEROA_C2);
	}
}


// Slot du bouton de demande de pose dark pour L1
//
void SupervCLIMSO::SlotBoutonPoseDarkL1(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}

	if( ModeObservation == ModeRO_SansMode )
	{
		MessageModeRoueOuvNonConnuePoseImpossible();
		return;
	}

	// Si il n'y a pas de pose en cours sur L1
	//
	if( !PoseEnCours[CAMEROA_L1] )
	{
		PoseEnCours[CAMEROA_L1]=true;

		if( CBCompoSeqAcq[ACQUISITION_L1_SURF]->isChecked() )
		{
			// Acquisition de la surface
			//
			PLAcqL1->DemandeListeAcquisitions(POSE_DARK,ModeObservation,true,false);
		}
		else
		{
			// Sinon acquisition de la couronne
			//
			PLAcqL1->DemandeListeAcquisitions(POSE_DARK,ModeObservation,false,true);
		}

		Log("Pose de DARK déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_L1]+".");

		// Faire croire a un changement pour redessiner les boutons
		//
		aL1Actif=-1;
		aModeObservation=ModeRO_NonInitialise;
	}
	else
	{
		MessageUnePoseDejaEnCoursSur(CAMEROA_L1);
	}
}


// Slot du bouton de demande de pose dark pour L2
//
void SupervCLIMSO::SlotBoutonPoseDarkL2(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}

	if( ModeObservation == ModeRO_SansMode )
	{
		MessageModeRoueOuvNonConnuePoseImpossible();
		return;
	}

	// Si il n'y a pas de pose en cours sur L2
	//
	if( !PoseEnCours[CAMEROA_L2] )
	{
		PoseEnCours[CAMEROA_L2]=true;

		if( CBCompoSeqAcq[ACQUISITION_L2_SURF]->isChecked() )
		{
			// Acquisition de la surface
			//
			PLAcqL2->DemandeListeAcquisitions(POSE_DARK,ModeObservation,true,false);
		}
		else
		{
			// Sinon acquisition de la couronne
			//
			PLAcqL2->DemandeListeAcquisitions(POSE_DARK,ModeObservation,false,true);
		}

		Log("Pose de DARK déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_L2]+".");

		// Faire croire a un changement pour redessiner les boutons
		//
		aL2Actif=-1;
		aModeObservation=ModeRO_NonInitialise;
	}
	else
	{
		MessageUnePoseDejaEnCoursSur(CAMEROA_L2);
	}
}


// Slot du bouton de demande de pose image pour C1
//
void SupervCLIMSO::SlotBoutonPoseImageC1(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}

	if( ModeObservation == ModeRO_SansMode )
	{
		MessageModeRoueOuvNonConnuePoseImpossible();
		return;
	}

	// Si il n'y a pas de pose en cours sur C1
	//
	if( !PoseEnCours[CAMEROA_C1] )
	{
		PoseEnCours[CAMEROA_C1]=true;

		PLAcqC1->DemandeListeAcquisitions(POSE_LUMIERE,ModeObservation,/* CBCompoSeqAcq[ACQUISITION_C1_COUR]->isChecked() */ true);		// On la realise a chaque fois

		switch( ModeObservation )
		{
			case ModeRO_Observation:
				Log("Pose d'observation déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_C1]+".");
				break;
			case ModeRO_PLU:
				Log("Pose de PLU déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_C1]+".");
				break;
			case ModeRO_Calibration:
				Log("Pose de calibration déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_C1]+".");
				break;
			case ModeRO_Pointage:
				Log("Pose d'observation en mode pointage déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_C1]+".");
				break;
			case ModeRO_NonInitialise:
			case ModeRO_SansMode:
				Log("Pose en mode inconnu déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_C1]+".");
				break;
		}

		// Faire croire a un changement pour redessiner les boutons
		//
		aC1Actif=-1;
		aModeObservation=ModeRO_NonInitialise;
	}
	else
	{
		MessageUnePoseDejaEnCoursSur(CAMEROA_C1);
	}
}


// Slot du bouton de demande de pose image pour C2
//
void SupervCLIMSO::SlotBoutonPoseImageC2(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}

	if( ModeObservation == ModeRO_SansMode )
	{
		MessageModeRoueOuvNonConnuePoseImpossible();
		return;
	}

	if( FiltreC2 == FiltreC2_SansFiltre )
	{
		MessageFiltreC2NonConnuPoseImpossible();
		return;
	}

	// Si il n'y a pas de pose en cours sur C2
	//
	if( !PoseEnCours[CAMEROA_C2] )
	{
		PoseEnCours[CAMEROA_C2]=true;

		switch( FiltreC2 )
		{
			case FiltreC2_10747:
				PLAcqC2->DemandeListeAcquisitions(POSE_LUMIERE,ModeObservation,true,false,false,false);
				break;
			case FiltreC2_10770:
				PLAcqC2->DemandeListeAcquisitions(POSE_LUMIERE,ModeObservation,false,true,false,false);
				break;
			case FiltreC2_10798:
				PLAcqC2->DemandeListeAcquisitions(POSE_LUMIERE,ModeObservation,false,false,true,false);
				break;
			case FiltreC2_10830:
				PLAcqC2->DemandeListeAcquisitions(POSE_LUMIERE,ModeObservation,false,false,false,true);
				break;
			default:	break;
		}

		switch( ModeObservation )
		{
			case ModeRO_Observation:
				Log("Pose d'observation déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_C2]+".");
				break;
			case ModeRO_PLU:
				Log("Pose de PLU déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_C2]+".");
				break;
			case ModeRO_Calibration:
				Log("Pose de calibration déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_C2]+".");
				break;
			case ModeRO_Pointage:
				Log("Pose d'observation en mode pointage déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_C2]+".");
				break;
			case ModeRO_NonInitialise:
			case ModeRO_SansMode:
				Log("Pose en mode inconnu déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_C2]+".");
				break;
		}

		// Faire croire a un changement pour redessiner les boutons
		//
		aC2Actif=-1;
		aModeObservation=ModeRO_NonInitialise;

		// Pour faire croire a un changement et faire redessiner le bouton
		//
		aFiltreC2=FiltreC2_NonInitialise;
	}
	else
	{
		MessageUnePoseDejaEnCoursSur(CAMEROA_C2);
	}
}


// Slot du bouton de demande de pose image pour L1
//
void SupervCLIMSO::SlotBoutonPoseImageL1(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}

	if( ModeObservation == ModeRO_SansMode )
	{
		MessageModeRoueOuvNonConnuePoseImpossible();
		return;
	}

	// Si il n'y a pas de pose en cours sur L1
	//
	if( !PoseEnCours[CAMEROA_L1] )
	{
		PoseEnCours[CAMEROA_L1]=true;

		if( CBCompoSeqAcq[ACQUISITION_L1_SURF]->isChecked() )
		{
			// Acquisition de la surface
			//
			PLAcqL1->DemandeListeAcquisitions(POSE_LUMIERE,ModeObservation,true,false);
		}
		else
		{
			// Sinon acquisition de la couronne
			//
			PLAcqL1->DemandeListeAcquisitions(POSE_LUMIERE,ModeObservation,false,true);
		}

		switch( ModeObservation )
		{
			case ModeRO_Observation:
				Log("Pose d'observation déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_L1]+".");
				break;
			case ModeRO_PLU:
				Log("Pose de PLU déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_L1]+".");
				break;
			case ModeRO_Calibration:
				Log("Pose de calibration déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_L1]+".");
				break;
			case ModeRO_Pointage:
				Log("Pose d'observation en mode pointage déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_L1]+".");
				break;
			case ModeRO_NonInitialise:
			case ModeRO_SansMode:
				Log("Pose en mode inconnu déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_L1]+".");
				break;
		}

		// Faire croire a un changement pour redessiner les boutons
		//
		aL1Actif=-1;
		aModeObservation=ModeRO_NonInitialise;
	}
	else
	{
		MessageUnePoseDejaEnCoursSur(CAMEROA_L1);
	}
}


// Slot du bouton de demande de pose image pour L2
//
void SupervCLIMSO::SlotBoutonPoseImageL2(void)
{
	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}

	if( ModeObservation == ModeRO_SansMode )
	{
		MessageModeRoueOuvNonConnuePoseImpossible();
		return;
	}

	// Si il n'y a pas de pose en cours sur L2
	//
	if( !PoseEnCours[CAMEROA_L2] )
	{
		PoseEnCours[CAMEROA_L2]=true;

		if( CBCompoSeqAcq[ACQUISITION_L2_SURF]->isChecked() )
		{
			// Acquisition de la surface
			//
			PLAcqL2->DemandeListeAcquisitions(POSE_LUMIERE,ModeObservation,true,false);
		}
		else
		{
			// Sinon acquisition de la couronne
			//
			PLAcqL2->DemandeListeAcquisitions(POSE_LUMIERE,ModeObservation,false,true);
		}

		switch( ModeObservation )
		{
			case ModeRO_Observation:
				Log("Pose d'observation déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_L2]+".");
				break;
			case ModeRO_PLU:
				Log("Pose de PLU déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_L2]+".");
				break;
			case ModeRO_Calibration:
				Log("Pose de calibration déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_L2]+".");
				break;
			case ModeRO_Pointage:
				Log("Pose d'observation en mode pointage déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_L2]+".");
				break;
			case ModeRO_NonInitialise:
			case ModeRO_SansMode:
				Log("Pose mode inconnu déclenchée sur l'instrument "+InstrumentCLIMSO[CAMEROA_L2]+".");
				break;
		}

		// Faire croire a un changement pour redessiner les boutons
		//
		aL2Actif=-1;
		aModeObservation=ModeRO_NonInitialise;
	}
	else
	{
		MessageUnePoseDejaEnCoursSur(CAMEROA_L2);
	}
}


// Slot du bouton de demande de poses de bias
//
void SupervCLIMSO::SlotBoutonPosesBias(void)
{
	int aLoguer=false;
	QString log;
	log.reserve(TAILLE_MINI_CHAINE_LOG);

	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( !(C1Actif || C2Actif || L1Actif || L2Actif) )
	{
		MessageDevezValiderUnInstrument();
		return;
	}

	log="Pose(s) de BIAS déclenchée(s) sur l(es) instrument(s)";

	// Si il n'y a pas de pose en cours sur C1
	//
	if( C1Actif && !PoseEnCours[CAMEROA_C1] )
	{
		aLoguer=true;
		DeclencherPoseBias(false,CAMEROA_C1);
		log+=" "+InstrumentCLIMSO[CAMEROA_C1];
	}

	// Si il n'y a pas de pose en cours sur C2
	//
	if( C2Actif && !PoseEnCours[CAMEROA_C2] )
	{
		aLoguer=true;
		DeclencherPoseBias(false,CAMEROA_C2);
		log+=" "+InstrumentCLIMSO[CAMEROA_C2];
	}

	// Si il n'y a pas de pose en cours sur L1
	//
	if( L1Actif && !PoseEnCours[CAMEROA_L1] )
	{
		aLoguer=true;
		DeclencherPoseBias(false,CAMEROA_L1);
		log+=" "+InstrumentCLIMSO[CAMEROA_L1];
	}

	// Si il n'y a pas de pose en cours sur L2
	//
	if( L2Actif && !PoseEnCours[CAMEROA_L2] )
	{
		aLoguer=true;
		DeclencherPoseBias(false,CAMEROA_L2);
		log+=" "+InstrumentCLIMSO[CAMEROA_L2];
	}

	log+=".";

	if( aLoguer ) Log(log);

	MAJEtatBoutonsFP();
}


// Slot du bouton de demande de poses de dark
//
void SupervCLIMSO::SlotBoutonPosesDark(void)
{
	int aLoguer=false;
	QString log;
	log.reserve(TAILLE_MINI_CHAINE_LOG);

	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( !(C1Actif || C2Actif || L1Actif || L2Actif) )
	{
		MessageDevezValiderUnInstrument();
		return;
	}

	log="Pose(s) de DARK déclenchée(s) sur l(es) instrument(s)";

	// Si il n'y a pas de pose en cours sur C1 et qu'il y a au moins une pose dans la liste des acquisitions
	//
	if( C1Actif && !PoseEnCours[CAMEROA_C1] && (CBCompoSeqAcq[ACQUISITION_C1_COUR]->isChecked()) )
	{
		aLoguer=true;
		log+=" "+InstrumentCLIMSO[CAMEROA_C1];

		PoseEnCours[CAMEROA_C1]=true;

		PLAcqC1->DemandeListeAcquisitions(POSE_DARK,ModeObservation,CBCompoSeqAcq[ACQUISITION_C1_COUR]->isChecked());

		// Faire croire a un changement pour redessiner les boutons
		//
		aC1Actif=-1;
		aModeObservation=ModeRO_NonInitialise;
	}

	// Si il n'y a pas de pose en cours sur C2 et qu'il y a au moins une pose dans la liste des acquisitions
	//
	if( C2Actif && !PoseEnCours[CAMEROA_C2] && (CBCompoSeqAcq[ACQUISITION_C2_10747]->isChecked() || CBCompoSeqAcq[ACQUISITION_C2_10770]->isChecked() || CBCompoSeqAcq[ACQUISITION_C2_10798]->isChecked() || CBCompoSeqAcq[ACQUISITION_C2_10830]->isChecked()) )
	{
		aLoguer=true;
		log+=" "+InstrumentCLIMSO[CAMEROA_C2];

		PoseEnCours[CAMEROA_C2]=true;

		PLAcqC2->DemandeListeAcquisitions(POSE_DARK,ModeObservation,CBCompoSeqAcq[ACQUISITION_C2_10747]->isChecked(),CBCompoSeqAcq[ACQUISITION_C2_10770]->isChecked(),CBCompoSeqAcq[ACQUISITION_C2_10798]->isChecked(),CBCompoSeqAcq[ACQUISITION_C2_10830]->isChecked());

		// Faire croire a un changement pour redessiner les boutons
		//
		aC2Actif=-1;
		aModeObservation=ModeRO_NonInitialise;
	}

	// Si il n'y a pas de pose en cours sur L1 et qu'il y a au moins une pose dans la liste des acquisitions
	//
	if( L1Actif && !PoseEnCours[CAMEROA_L1] && (CBCompoSeqAcq[ACQUISITION_L1_SURF]->isChecked() || CBCompoSeqAcq[ACQUISITION_L1_COUR]->isChecked()) )
	{
		aLoguer=true;
		log+=" "+InstrumentCLIMSO[CAMEROA_L1];

		PoseEnCours[CAMEROA_L1]=true;

		PLAcqL1->DemandeListeAcquisitions(POSE_DARK,ModeObservation,CBCompoSeqAcq[ACQUISITION_L1_SURF]->isChecked(),CBCompoSeqAcq[ACQUISITION_L1_COUR]->isChecked());

		// Faire croire a un changement pour redessiner les boutons
		//
		aL1Actif=-1;
		aModeObservation=ModeRO_NonInitialise;
	}

	// Si il n'y a pas de pose en cours sur L2 et qu'il y a au moins une pose dans la liste des acquisitions
	//
	if( L2Actif && !PoseEnCours[CAMEROA_L2] && (CBCompoSeqAcq[ACQUISITION_L2_SURF]->isChecked() || CBCompoSeqAcq[ACQUISITION_L2_COUR]->isChecked()) )
	{
		aLoguer=true;
		log+=" "+InstrumentCLIMSO[CAMEROA_L2];

		PoseEnCours[CAMEROA_L2]=true;

		PLAcqL2->DemandeListeAcquisitions(POSE_DARK,ModeObservation,CBCompoSeqAcq[ACQUISITION_L2_SURF]->isChecked(),CBCompoSeqAcq[ACQUISITION_L2_COUR]->isChecked());

		// Faire croire a un changement pour redessiner les boutons
		//
		aL2Actif=-1;
		aModeObservation=ModeRO_NonInitialise;
	}

	log+=".";

	if( aLoguer ) Log(log);

	MAJEtatBoutonsFP();
}


// Slot du bouton de demande de sequence de poses images
//
void SupervCLIMSO::SlotBoutonSequencePosesImages(void)
{
	int aLoguer=false;
	QString log;
	log.reserve(TAILLE_MINI_CHAINE_LOG);

	// Si les axes ne sont pas initialiser on ne peut pas lancer la fonctionnalite
	//
	if( !AxesInitialises )
	{
		MessageDevezInitialiserAxes();
		return;
	}

	if( !(C1Actif || C2Actif || L1Actif || L2Actif) )
	{
		MessageDevezValiderUnInstrument();
		return;
	}

	if( ModeObservation == ModeRO_SansMode )
	{
		MessageModeRoueOuvNonConnuePoseImpossible();
		return;
	}

	if( FiltreC2 == FiltreC2_SansFiltre )
	{
		MessageFiltreC2NonConnuPoseImpossible();
		return;
	}

	switch( ModeObservation )
	{
		case ModeRO_Observation:
			log="Pose(s) d'observation déclenchée(s) sur l(es) instrument(s)";
			break;
		case ModeRO_PLU:
			log="Pose(s) de PLU déclenchée(s) sur l(es) instrument(s)";
			break;
		case ModeRO_Calibration:
			log="Pose(s) de calibration déclenchée(s) sur l(es) instrument(s)";
			break;
		case ModeRO_Pointage:
			log="Pose(s) d'observation en mode pointage déclenchée(s) sur l(es) instrument(s)";
			break;
		case ModeRO_NonInitialise:
		case ModeRO_SansMode:
			log="Pose(s) mode inconnu déclenchée(s) sur l(es) instrument(s)";
			break;
	}

	// Si il n'y a pas de pose en cours sur C1 et qu'il y a au moins une pose dans la liste des acquisitions
	//
	if( C1Actif && !PoseEnCours[CAMEROA_C1] && (CBCompoSeqAcq[ACQUISITION_C1_COUR]->isChecked()) )
	{
		aLoguer=true;
		log+=" "+InstrumentCLIMSO[CAMEROA_C1];

		PoseEnCours[CAMEROA_C1]=true;

		PLAcqC1->DemandeListeAcquisitions(POSE_LUMIERE,ModeObservation,CBCompoSeqAcq[ACQUISITION_C1_COUR]->isChecked());

		// Faire croire a un changement pour redessiner les boutons
		//
		aC1Actif=-1;
		aModeObservation=ModeRO_NonInitialise;
	}

	// Si il n'y a pas de pose en cours sur C2 et qu'il y a au moins une pose dans la liste des acquisitions
	//
	if( C2Actif && !PoseEnCours[CAMEROA_C2] && (CBCompoSeqAcq[ACQUISITION_C2_10747]->isChecked() || CBCompoSeqAcq[ACQUISITION_C2_10770]->isChecked() || CBCompoSeqAcq[ACQUISITION_C2_10798]->isChecked() || CBCompoSeqAcq[ACQUISITION_C2_10830]->isChecked()) )
	{
		aLoguer=true;
		log+=" "+InstrumentCLIMSO[CAMEROA_C2];

		PoseEnCours[CAMEROA_C2]=true;

		PLAcqC2->DemandeListeAcquisitions(POSE_LUMIERE,ModeObservation,CBCompoSeqAcq[ACQUISITION_C2_10747]->isChecked(),CBCompoSeqAcq[ACQUISITION_C2_10770]->isChecked(),CBCompoSeqAcq[ACQUISITION_C2_10798]->isChecked(),CBCompoSeqAcq[ACQUISITION_C2_10830]->isChecked());

		// Faire croire a un changement pour redessiner les boutons
		//
		aC2Actif=-1;
		aModeObservation=ModeRO_NonInitialise;
	}

	// Si il n'y a pas de pose en cours sur L1 et qu'il y a au moins une pose dans la liste des acquisitions
	//
	if( L1Actif && !PoseEnCours[CAMEROA_L1] && (CBCompoSeqAcq[ACQUISITION_L1_SURF]->isChecked() || CBCompoSeqAcq[ACQUISITION_L1_COUR]->isChecked()) )
	{
		aLoguer=true;
		log+=" "+InstrumentCLIMSO[CAMEROA_L1];

		PoseEnCours[CAMEROA_L1]=true;

		PLAcqL1->DemandeListeAcquisitions(POSE_LUMIERE,ModeObservation,CBCompoSeqAcq[ACQUISITION_L1_SURF]->isChecked(),CBCompoSeqAcq[ACQUISITION_L1_COUR]->isChecked());

		// Faire croire a un changement pour redessiner les boutons
		//
		aL1Actif=-1;
		aModeObservation=ModeRO_NonInitialise;
	}

	// Si il n'y a pas de pose en cours sur L2 et qu'il y a au moins une pose dans la liste des acquisitions
	//
	if( L2Actif && !PoseEnCours[CAMEROA_L2] && (CBCompoSeqAcq[ACQUISITION_L2_SURF]->isChecked() || CBCompoSeqAcq[ACQUISITION_L2_COUR]->isChecked()) )
	{
		aLoguer=true;
		log+=" "+InstrumentCLIMSO[CAMEROA_L2];

		PoseEnCours[CAMEROA_L2]=true;

		PLAcqL2->DemandeListeAcquisitions(POSE_LUMIERE,ModeObservation,CBCompoSeqAcq[ACQUISITION_L2_SURF]->isChecked(),CBCompoSeqAcq[ACQUISITION_L2_COUR]->isChecked());

		// Faire croire a un changement pour redessiner les boutons
		//
		aL2Actif=-1;
		aModeObservation=ModeRO_NonInitialise;
	}

	log+=".";

	if( aLoguer ) Log(log);

	MAJEtatBoutonsFP();
}


// Slot du bouton de demande de suppression de la derniere image acquise par C1
//
void SupervCLIMSO::SlotBoutonSuppressionDerImgC1(void)
{
	if( ListeNomFichDerImg[CAMEROA_C1].isEmpty() ) return;

	QStringList::Iterator it=ListeNomFichDerImg[CAMEROA_C1].fromLast();	// Pointeur vers le dernier element de la liste

	// Selon l'index du bouton clique, si on veut supprimer ou pas un fichier
	//
	if( QMessageBox::question(this,QString::fromLocal8Bit("SupervCLIMSO: Effacer un fichier"),QString::fromLocal8Bit("Voulez-vous vraiment supprimer l'image ?\n\n"+*it+"\n"),"Oui","Non",QString::null,1,1) == 0 )
	{
		// On peut supprimer le fichier
		//
		QFile NomFichier(*it);

		if( NomFichier.remove() == false )
		{
			Log("*** ERREUR: Impossible de supprimer le fichier "+*it+" ***");
		}
		else
		{
			Log("Eff C1: "+*it);
		}

		// On l'enleve de la liste
		//
		ListeNomFichDerImg[CAMEROA_C1].erase(it);

		MAJEtatBoutonsFP();
	}
}


// Slot du bouton de demande de suppression de la derniere image acquise par C2
//
void SupervCLIMSO::SlotBoutonSuppressionDerImgC2(void)
{
	if( ListeNomFichDerImg[CAMEROA_C2].isEmpty() ) return;

	QStringList::Iterator it=ListeNomFichDerImg[CAMEROA_C2].fromLast();	// Pointeur vers le dernier element de la liste

	// Selon l'index du bouton clique, si on veut supprimer ou pas un fichier
	//
	if( QMessageBox::question(this,QString::fromLocal8Bit("SupervCLIMSO: Effacer un fichier"),QString::fromLocal8Bit("Voulez-vous vraiment supprimer l'image ?\n\n"+*it+"\n"),"Oui","Non",QString::null,1,1) == 0 )
	{
		// On peut supprimer le fichier
		//
		QFile NomFichier(*it);

		if( NomFichier.remove() == false )
		{
			Log("*** ERREUR: Impossible de supprimer le fichier "+*it+" ***");
		}
		else
		{
			Log("Eff C2 : "+*it);
		}

		// On l'enleve de la liste
		//
		ListeNomFichDerImg[CAMEROA_C2].erase(it);

		MAJEtatBoutonsFP();
	}
}


// Slot du bouton de demande de suppression de la derniere image acquise par L1
//
void SupervCLIMSO::SlotBoutonSuppressionDerImgL1(void)
{
	if( ListeNomFichDerImg[CAMEROA_L1].isEmpty() ) return;

	QStringList::Iterator it=ListeNomFichDerImg[CAMEROA_L1].fromLast();	// Pointeur vers le dernier element de la liste

	// Selon l'index du bouton clique, si on veut supprimer ou pas un fichier
	//
	if( QMessageBox::question(this,QString::fromLocal8Bit("SupervCLIMSO: Effacer un fichier"),QString::fromLocal8Bit("Voulez-vous vraiment supprimer l'image ?\n\n"+*it+"\n"),"Oui","Non",QString::null,1,1) == 0 )
	{
		// On peut supprimer le fichier
		//
		QFile NomFichier(*it);

		if( NomFichier.remove() == false )
		{
			Log("*** ERREUR: Impossible de supprimer le fichier "+*it+" ***");
		}
		else
		{
			Log("Eff L1 : "+*it);
		}

		// On l'enleve de la liste
		//
		ListeNomFichDerImg[CAMEROA_L1].erase(it);

		MAJEtatBoutonsFP();
	}
}


// Slot du bouton de demande de suppression de la derniere image acquise par L2
//
void SupervCLIMSO::SlotBoutonSuppressionDerImgL2(void)
{
	if( ListeNomFichDerImg[CAMEROA_L2].isEmpty() ) return;

	QStringList::Iterator it=ListeNomFichDerImg[CAMEROA_L2].fromLast();	// Pointeur vers le dernier element de la liste

	// Selon l'index du bouton clique, si on veut supprimer ou pas un fichier
	//
	if( QMessageBox::question(this,QString::fromLocal8Bit("SupervCLIMSO: Effacer un fichier"),QString::fromLocal8Bit("Voulez-vous vraiment supprimer l'image ?\n\n"+*it+"\n"),"Oui","Non",QString::null,1,1) == 0 )
	{
		// On peut supprimer le fichier
		//
		QFile NomFichier(*it);

		if( NomFichier.remove() == false )
		{
			Log("*** ERREUR: Impossible de supprimer le fichier "+*it+" ***");
		}
		else
		{
			Log("Eff L2 : "+*it);
		}

		// On l'enleve de la liste
		//
		ListeNomFichDerImg[CAMEROA_L2].erase(it);

		MAJEtatBoutonsFP();
	}
}


// Slot du bouton de demande de transfert de la derniere image acquise par C1
//
void SupervCLIMSO::SlotBoutonTransfertBASS2000C1(void)
{
/*
16-12-2007 : pour simplification de la procedure de transfert vers BASS2000

	if( FenetrePubliC1->isVisible() )
	{
		FenetrePubliC1->hide();
	}
	else
	{
		ComposerListePubliablesC1();
		FenetrePubliC1->show();
	}
*/

	ComposerListePubliablesC1();
	SlotBoutonPubliC1_0();
}


// Slot du bouton de demande de transfert de la derniere image acquise par C2
//
void SupervCLIMSO::SlotBoutonTransfertBASS2000C2(void)
{
	if( FenetrePubliC2->isVisible() )
	{
		FenetrePubliC2->hide();
	}
	else
	{
		ComposerListePubliablesC2();
		FenetrePubliC2->show();
	}
}


// Slot du bouton de demande de transfert de la derniere image acquise par L1
//
void SupervCLIMSO::SlotBoutonTransfertBASS2000L1(void)
{
/*
16-12-2007 : pour simplification de la procedure de transfert vers BASS2000

	if( FenetrePubliL1->isVisible() )
	{
		FenetrePubliL1->hide();
	}
	else
	{
		ComposerListePubliablesL1();
		FenetrePubliL1->show();
	}
*/

	ComposerListePubliablesL1();
	SlotBoutonPubliL1_0();
}


// Slot du bouton de demande de transfert de la derniere image acquise par L2
//
void SupervCLIMSO::SlotBoutonTransfertBASS2000L2(void)
{
/*
16-12-2007 : pour simplification de la procedure de transfert vers BASS2000

	if( FenetrePubliL2->isVisible() )
	{
		FenetrePubliL2->hide();
	}
	else
	{
		ComposerListePubliablesL2();
		FenetrePubliL2->show();
	}
*/

	ComposerListePubliablesL2();
	SlotBoutonPubliL2_0();
}


// Composition de la liste des images de C1 publiables
//
void SupervCLIMSO::ComposerListePubliablesC1(void)
{
	if( !NbImgPubliablesC1 ) return;

	int i;		// Indice du label
	int j;		// Indice dans tableau des noms de fichiers stockes

	for( i=0; i < NB_IMG_PUB_C1; i++ )
	{
		j=NbImgPubliablesC1-1-i;

		if( j < 0 ) break;		// Il n'y a pas assez de fichiers publiables a afficher

		LabelFenetrePubliC1[i]->setText(FichiersPubliC1[j % NB_IMG_PUB_C1]);
	}
}


// Composition de la liste des images de C2 publiables
//
void SupervCLIMSO::ComposerListePubliablesC2(void)
{
	if( !NbImgPubliablesC2 ) return;

	int i;		// Indice du label
	int j;		// Indice dans tableau des noms de fichiers stockes

	for( i=0; i < NB_IMG_PUB_C2; i++ )
	{
		j=NbImgPubliablesC2-1-i;

		if( j < 0 ) break;		// Il n'y a pas assez de fichiers publiables a afficher

		LabelFenetrePubliC2[i]->setText(FichiersPubliC2[j % NB_IMG_PUB_C2]);
	}
}


// Composition de la liste des images de L1 publiables
//
void SupervCLIMSO::ComposerListePubliablesL1(void)
{
	if( !NbImgPubliablesL1 ) return;

	int i;		// Indice du label
	int j;		// Indice dans tableau des noms de fichiers stockes

	for( i=0; i < NB_IMG_PUB_L1; i++ )
	{
		j=NbImgPubliablesL1-1-i;

		if( j < 0 ) break;		// Il n'y a pas assez de fichiers publiables a afficher

		LabelFenetrePubliL1[i]->setText(FichiersPubliL1[j % NB_IMG_PUB_L1]);
	}
}


// Composition de la liste des images de L2 publiables
//
void SupervCLIMSO::ComposerListePubliablesL2(void)
{
	if( !NbImgPubliablesL2 ) return;

	int i;		// Indice du label
	int j;		// Indice dans tableau des noms de fichiers stockes

	for( i=0; i < NB_IMG_PUB_L2; i++ )
	{
		j=NbImgPubliablesL2-1-i;

		if( j < 0 ) break;		// Il n'y a pas assez de fichiers publiables a afficher

		LabelFenetrePubliL2[i]->setText(FichiersPubliL2[j % NB_IMG_PUB_L2]);
	}
}


// Publication d'une image sur BASS2000
//
void SupervCLIMSO::PublierBASS2000(int n,QString image)
{
	// Si le fichier n'existe plus sur le disque car supprime entre temps
	//
	if( !QFile::exists(image) )
	{
		QMessageBox::information(this,"SupervCLIMSO : Transfert vers BASS2000",QString::fromLocal8Bit("Cette image n'est plus disponible car supprimée par l'observateur."));
		return;
	}

	// Le fichier existe donc on peut l'envoyer
	//
	QString LigneCmd;	// Pour composer la ligne de commande a executer

	LigneCmd.reserve(TAILLE_MINI_CHAINE);

	switch( n )
	{
		case CAMEROA_C1:
			LigneCmd="/usr/bin/xterm -e /SupervCLIMSO/scripts/publierBASS2000-C1 "+image;
			break;

		case CAMEROA_C2:
			if( image.find("_10747_") != -1 ) LigneCmd="/usr/bin/xterm -e /SupervCLIMSO/scripts/publierBASS2000-C2-10747 "+image;
			if( image.find("_10770_") != -1 ) LigneCmd="/usr/bin/xterm -e /SupervCLIMSO/scripts/publierBASS2000-C2-10770 "+image;
			if( image.find("_10798_") != -1 ) LigneCmd="/usr/bin/xterm -e /SupervCLIMSO/scripts/publierBASS2000-C2-10798 "+image;
			if( image.find("_10830_") != -1 ) LigneCmd="/usr/bin/xterm -e /SupervCLIMSO/scripts/publierBASS2000-C2-10830 "+image;
			break;

		case CAMEROA_L1:
			LigneCmd="/usr/bin/xterm -e /SupervCLIMSO/scripts/publierBASS2000-L1 "+image;
			break;

		case CAMEROA_L2:
			LigneCmd="/usr/bin/xterm -e /SupervCLIMSO/scripts/publierBASS2000-L2 "+image;
			break;

		default:
			LigneCmd="goulp.fts";
			break;
	}

	LigneCmd+=" &";

	// On peut lancer en commande externe pour ne pas surcharger le superviseur
	//
	system(LigneCmd.ascii());
}


// Slot pour la publication de l'image C1 du label 0 ---
//
void SupervCLIMSO::SlotBoutonPubliC1_0(void)
{
	if( !LabelFenetrePubliC1[0]->text().isEmpty() ) PublierBASS2000(CAMEROA_C1,LabelFenetrePubliC1[0]->text());
}

// Slot pour la publication de l'image C1 du label 1
//
void SupervCLIMSO::SlotBoutonPubliC1_1(void)
{
	if( !LabelFenetrePubliC1[1]->text().isEmpty() ) PublierBASS2000(CAMEROA_C1,LabelFenetrePubliC1[1]->text());
}

// Slot pour la publication de l'image C1 du label 2
//
void SupervCLIMSO::SlotBoutonPubliC1_2(void)
{
	if( !LabelFenetrePubliC1[2]->text().isEmpty() ) PublierBASS2000(CAMEROA_C1,LabelFenetrePubliC1[2]->text());
}

// Slot pour la publication de l'image C1 du label 3
//
void SupervCLIMSO::SlotBoutonPubliC1_3(void)
{
	if( !LabelFenetrePubliC1[3]->text().isEmpty() ) PublierBASS2000(CAMEROA_C1,LabelFenetrePubliC1[3]->text());
}

// Slot pour la publication de l'image C2 du label 0 ---
//
void SupervCLIMSO::SlotBoutonPubliC2_0(void)
{
	if( !LabelFenetrePubliC2[0]->text().isEmpty() ) PublierBASS2000(CAMEROA_C2,LabelFenetrePubliC2[0]->text());
}

// Slot pour la publication de l'image C2 du label 1
//
void SupervCLIMSO::SlotBoutonPubliC2_1(void)
{
	if( !LabelFenetrePubliC2[1]->text().isEmpty() ) PublierBASS2000(CAMEROA_C2,LabelFenetrePubliC2[1]->text());
}

// Slot pour la publication de l'image C2 du label 2
//
void SupervCLIMSO::SlotBoutonPubliC2_2(void)
{
	if( !LabelFenetrePubliC2[2]->text().isEmpty() ) PublierBASS2000(CAMEROA_C2,LabelFenetrePubliC2[2]->text());
}

// Slot pour la publication de l'image C2 du label 3
//
void SupervCLIMSO::SlotBoutonPubliC2_3(void)
{
	if( !LabelFenetrePubliC2[3]->text().isEmpty() ) PublierBASS2000(CAMEROA_C2,LabelFenetrePubliC2[3]->text());
}

// Slot pour la publication de l'image C2 du label 4
//
void SupervCLIMSO::SlotBoutonPubliC2_4(void)
{
	if( !LabelFenetrePubliC2[4]->text().isEmpty() ) PublierBASS2000(CAMEROA_C2,LabelFenetrePubliC2[4]->text());
}

// Slot pour la publication de l'image C2 du label 5
//
void SupervCLIMSO::SlotBoutonPubliC2_5(void)
{
	if( !LabelFenetrePubliC2[5]->text().isEmpty() ) PublierBASS2000(CAMEROA_C2,LabelFenetrePubliC2[5]->text());
}

// Slot pour la publication de l'image C2 du label 6
//
void SupervCLIMSO::SlotBoutonPubliC2_6(void)
{
	if( !LabelFenetrePubliC2[6]->text().isEmpty() ) PublierBASS2000(CAMEROA_C2,LabelFenetrePubliC2[6]->text());
}

// Slot pour la publication de l'image C2 du label 7
//
void SupervCLIMSO::SlotBoutonPubliC2_7(void)
{
	if( !LabelFenetrePubliC2[7]->text().isEmpty() ) PublierBASS2000(CAMEROA_C2,LabelFenetrePubliC2[7]->text());
}

// Slot pour la publication de l'image C2 du label 8
//
void SupervCLIMSO::SlotBoutonPubliC2_8(void)
{
	if( !LabelFenetrePubliC2[8]->text().isEmpty() ) PublierBASS2000(CAMEROA_C2,LabelFenetrePubliC2[8]->text());
}

// Slot pour la publication de l'image C2 du label 9
//
void SupervCLIMSO::SlotBoutonPubliC2_9(void)
{
	if( !LabelFenetrePubliC2[9]->text().isEmpty() ) PublierBASS2000(CAMEROA_C2,LabelFenetrePubliC2[9]->text());
}

// Slot pour la publication de l'image C2 du label 10
//
void SupervCLIMSO::SlotBoutonPubliC2_10(void)
{
	if( !LabelFenetrePubliC2[10]->text().isEmpty() ) PublierBASS2000(CAMEROA_C2,LabelFenetrePubliC2[10]->text());
}

// Slot pour la publication de l'image C2 du label 11
//
void SupervCLIMSO::SlotBoutonPubliC2_11(void)
{
	if( !LabelFenetrePubliC2[11]->text().isEmpty() ) PublierBASS2000(CAMEROA_C2,LabelFenetrePubliC2[11]->text());
}

// Slot pour la publication de l'image L1 du label 0 ---
//
void SupervCLIMSO::SlotBoutonPubliL1_0(void)
{
	if( !LabelFenetrePubliL1[0]->text().isEmpty() ) PublierBASS2000(CAMEROA_L1,LabelFenetrePubliL1[0]->text());
}

// Slot pour la publication de l'image L1 du label 1
//
void SupervCLIMSO::SlotBoutonPubliL1_1(void)
{
	if( !LabelFenetrePubliL1[1]->text().isEmpty() ) PublierBASS2000(CAMEROA_L1,LabelFenetrePubliL1[1]->text());
}

// Slot pour la publication de l'image L1 du label 2
//
void SupervCLIMSO::SlotBoutonPubliL1_2(void)
{
	if( !LabelFenetrePubliL1[2]->text().isEmpty() ) PublierBASS2000(CAMEROA_L1,LabelFenetrePubliL1[2]->text());
}

// Slot pour la publication de l'image L1 du label 3
//
void SupervCLIMSO::SlotBoutonPubliL1_3(void)
{
	if( !LabelFenetrePubliL1[3]->text().isEmpty() ) PublierBASS2000(CAMEROA_L1,LabelFenetrePubliL1[3]->text());
}

// Slot pour la publication de l'image L2 du label 0 ---
//
void SupervCLIMSO::SlotBoutonPubliL2_0(void)
{
	if( !LabelFenetrePubliL2[0]->text().isEmpty() ) PublierBASS2000(CAMEROA_L2,LabelFenetrePubliL2[0]->text());
}

// Slot pour la publication de l'image L2 du label 1
//
void SupervCLIMSO::SlotBoutonPubliL2_1(void)
{
	if( !LabelFenetrePubliL2[1]->text().isEmpty() ) PublierBASS2000(CAMEROA_L2,LabelFenetrePubliL2[1]->text());
}

// Slot pour la publication de l'image L2 du label 2
//
void SupervCLIMSO::SlotBoutonPubliL2_2(void)
{
	if( !LabelFenetrePubliL2[2]->text().isEmpty() ) PublierBASS2000(CAMEROA_L2,LabelFenetrePubliL2[2]->text());
}

// Slot pour la publication de l'image L2 du label 3
//
void SupervCLIMSO::SlotBoutonPubliL2_3(void)
{
	if( !LabelFenetrePubliL2[3]->text().isEmpty() ) PublierBASS2000(CAMEROA_L2,LabelFenetrePubliL2[3]->text());
}


// Slot du checkbox de passage de C1 en mode de pose automatique
//
void SupervCLIMSO::SlotCBAcqAutoC1(void)
{
	CBAcqAuto[CAMEROA_C1]->setDown(false);

	if( QMessageBox::question(this,QString::fromLocal8Bit("SupervCLIMSO: Changement du mode d'acquisition"),(!CBAcqAuto[CAMEROA_C1]->isChecked()) ? QString::fromLocal8Bit("Voulez-vous vraiment passer l'instrument C1 en mode déclenchement AUTOMATIQUE ?") : QString::fromLocal8Bit("Voulez-vous vraiment passer l'instrument C1 en mode déclenchement MANUEL ?"),"Oui","Non",QString::null,1,1) == 0 ) CBAcqAuto[CAMEROA_C1]->setChecked(!CBAcqAuto[CAMEROA_C1]->isChecked());
}


// Slot du checkbox de passage de C2 en mode de pose automatique
//
void SupervCLIMSO::SlotCBAcqAutoC2(void)
{
	CBAcqAuto[CAMEROA_C2]->setDown(false);

	if( QMessageBox::question(this,QString::fromLocal8Bit("SupervCLIMSO: Changement du mode d'acquisition"),(!CBAcqAuto[CAMEROA_C2]->isChecked()) ? QString::fromLocal8Bit("Voulez-vous vraiment passer l'instrument C2 en mode déclenchement AUTOMATIQUE ?") : QString::fromLocal8Bit("Voulez-vous vraiment passer l'instrument C2 en mode déclenchement MANUEL ?"),"Oui","Non",QString::null,1,1) == 0 ) CBAcqAuto[CAMEROA_C2]->setChecked(!CBAcqAuto[CAMEROA_C2]->isChecked());
}


// Slot du checkbox de passage de L1 en mode de pose automatique
//
void SupervCLIMSO::SlotCBAcqAutoL1(void)
{
	CBAcqAuto[CAMEROA_L1]->setDown(false);

	if( QMessageBox::question(this,QString::fromLocal8Bit("SupervCLIMSO: Changement du mode d'acquisition"),(!CBAcqAuto[CAMEROA_L1]->isChecked()) ? QString::fromLocal8Bit("Voulez-vous vraiment passer l'instrument L1 en mode déclenchement AUTOMATIQUE ?") : QString::fromLocal8Bit("Voulez-vous vraiment passer l'instrument L1 en mode déclenchement MANUEL ?"),"Oui","Non",QString::null,1,1) == 0 ) CBAcqAuto[CAMEROA_L1]->setChecked(!CBAcqAuto[CAMEROA_L1]->isChecked());
}


// Slot du checkbox de passage de L2 en mode de pose automatique
//
void SupervCLIMSO::SlotCBAcqAutoL2(void)
{
	CBAcqAuto[CAMEROA_L2]->setDown(false);

	if( QMessageBox::question(this,QString::fromLocal8Bit("SupervCLIMSO: Changement du mode d'acquisition"),(!CBAcqAuto[CAMEROA_L2]->isChecked()) ? QString::fromLocal8Bit("Voulez-vous vraiment passer l'instrument L2 en mode déclenchement AUTOMATIQUE ?") : QString::fromLocal8Bit("Voulez-vous vraiment passer l'instrument L2 en mode déclenchement MANUEL ?"),"Oui","Non",QString::null,1,1) == 0 ) CBAcqAuto[CAMEROA_L2]->setChecked(!CBAcqAuto[CAMEROA_L2]->isChecked());
}


// Slot de selection de l'acquisition C1 h-alpha pour la sequence d'acquitions de C1
//
void SupervCLIMSO::SlotCBCompoSeqAcqC1(void)
{
	CBCompoSeqAcq[ACQUISITION_C1_COUR]->setDown(false);

	if( QMessageBox::question(this,QString::fromLocal8Bit("SupervCLIMSO: Changement de la liste des acquisitions"),(!CBCompoSeqAcq[ACQUISITION_C1_COUR]->isChecked()) ? QString::fromLocal8Bit("Voulez-vous vraiment AJOUTER h-alpha couronne dans la liste des acquisitions de C1 ?") : QString::fromLocal8Bit("Voulez-vous vraiment RETIRER h-alpha couronne de la liste des acquisitions de C1 ?"),"Oui","Non",QString::null,1,1) == 0 ) CBCompoSeqAcq[ACQUISITION_C1_COUR]->setChecked(!CBCompoSeqAcq[ACQUISITION_C1_COUR]->isChecked());
}


// Slot de selection de l'acquisition C2 10747 pour la sequence d'acquitions de C2
//
void SupervCLIMSO::SlotCBCompoSeqAcqC2_10747(void)
{
	CBCompoSeqAcq[ACQUISITION_C2_10747]->setDown(false);

	if( QMessageBox::question(this,QString::fromLocal8Bit("SupervCLIMSO: Changement de la liste des acquisitions"),(!CBCompoSeqAcq[ACQUISITION_C2_10747]->isChecked()) ? QString::fromLocal8Bit("Voulez-vous vraiment AJOUTER le filtre 10747 nm dans la liste des acquisitions de C2 ?") : QString::fromLocal8Bit("Voulez-vous vraiment RETIRER le filtre 10747 nm de la liste des acquisitions de C2 ?"),"Oui","Non",QString::null,1,1) == 0 ) CBCompoSeqAcq[ACQUISITION_C2_10747]->setChecked(!CBCompoSeqAcq[ACQUISITION_C2_10747]->isChecked());
}


// Slot de selection de l'acquisition C2 10770 pour la sequence d'acquitions de C2
//
void SupervCLIMSO::SlotCBCompoSeqAcqC2_10770(void)
{
	CBCompoSeqAcq[ACQUISITION_C2_10770]->setDown(false);

	if( QMessageBox::question(this,QString::fromLocal8Bit("SupervCLIMSO: Changement de la liste des acquisitions"),(!CBCompoSeqAcq[ACQUISITION_C2_10770]->isChecked()) ? QString::fromLocal8Bit("Voulez-vous vraiment AJOUTER le filtre 10770 nm dans la liste des acquisitions de C2 ?") : QString::fromLocal8Bit("Voulez-vous vraiment RETIRER le filtre 10770 nm de la liste des acquisitions de C2 ?"),"Oui","Non",QString::null,1,1) == 0 ) CBCompoSeqAcq[ACQUISITION_C2_10770]->setChecked(!CBCompoSeqAcq[ACQUISITION_C2_10770]->isChecked());
}


// Slot de selection de l'acquisition C2 10798 pour la sequence d'acquitions de C2
//
void SupervCLIMSO::SlotCBCompoSeqAcqC2_10798(void)
{
	CBCompoSeqAcq[ACQUISITION_C2_10798]->setDown(false);

	if( QMessageBox::question(this,QString::fromLocal8Bit("SupervCLIMSO: Changement de la liste des acquisitions"),(!CBCompoSeqAcq[ACQUISITION_C2_10798]->isChecked()) ? QString::fromLocal8Bit("Voulez-vous vraiment AJOUTER le filtre 10798 nm dans la liste des acquisitions de C2 ?") : QString::fromLocal8Bit("Voulez-vous vraiment RETIRER le filtre 10798 nm de la liste des acquisitions de C2 ?"),"Oui","Non",QString::null,1,1) == 0 ) CBCompoSeqAcq[ACQUISITION_C2_10798]->setChecked(!CBCompoSeqAcq[ACQUISITION_C2_10798]->isChecked());
}


// Slot de selection de l'acquisition C2 10830 pour la sequence d'acquitions de C2
//
void SupervCLIMSO::SlotCBCompoSeqAcqC2_10830(void)
{
	CBCompoSeqAcq[ACQUISITION_C2_10830]->setDown(false);

	if( QMessageBox::question(this,QString::fromLocal8Bit("SupervCLIMSO: Changement de la liste des acquisitions"),(!CBCompoSeqAcq[ACQUISITION_C2_10830]->isChecked()) ? QString::fromLocal8Bit("Voulez-vous vraiment AJOUTER le filtre 10830 nm dans la liste des acquisitions de C2 ?") : QString::fromLocal8Bit("Voulez-vous vraiment RETIRER le filtre 10830 nm de la liste des acquisitions de C2 ?"),"Oui","Non",QString::null,1,1) == 0 ) CBCompoSeqAcq[ACQUISITION_C2_10830]->setChecked(!CBCompoSeqAcq[ACQUISITION_C2_10830]->isChecked());
}


// Slot de selection de l'acquisition L1 surface pour la sequence d'acquitions de L1
//
void SupervCLIMSO::SlotCBCompoSeqAcqL1S(void)
{
	CBCompoSeqAcq[ACQUISITION_L1_SURF]->setDown(false);

	if( QMessageBox::question(this,QString::fromLocal8Bit("SupervCLIMSO: Changement de la liste des acquisitions"),(!CBCompoSeqAcq[ACQUISITION_L1_SURF]->isChecked()) ? QString::fromLocal8Bit("Voulez-vous vraiment AJOUTER L1 surface dans la liste des acquisitions de L1 ?") : QString::fromLocal8Bit("Voulez-vous vraiment RETIRER L1 surface de la liste des acquisitions de L1 ?"),"Oui","Non",QString::null,1,1) == 0 ) CBCompoSeqAcq[ACQUISITION_L1_SURF]->setChecked(!CBCompoSeqAcq[ACQUISITION_L1_SURF]->isChecked());
}


// Slot de selection de l'acquisition L1 couronne pour la sequence d'acquitions de L1
//
void SupervCLIMSO::SlotCBCompoSeqAcqL1C(void)
{
	CBCompoSeqAcq[ACQUISITION_L1_COUR]->setDown(false);

	if( QMessageBox::question(this,QString::fromLocal8Bit("SupervCLIMSO: Changement de la liste des acquisitions"),(!CBCompoSeqAcq[ACQUISITION_L1_COUR]->isChecked()) ? QString::fromLocal8Bit("Voulez-vous vraiment AJOUTER L1 couronne dans la liste des acquisitions de L1 ?") : QString::fromLocal8Bit("Voulez-vous vraiment RETIRER L1 couronne de la liste des acquisitions de L1 ?"),"Oui","Non",QString::null,1,1) == 0 ) CBCompoSeqAcq[ACQUISITION_L1_COUR]->setChecked(!CBCompoSeqAcq[ACQUISITION_L1_COUR]->isChecked());
}


// Slot de selection de l'acquisition L2 surface pour la sequence d'acquitions de L2
//
void SupervCLIMSO::SlotCBCompoSeqAcqL2S(void)
{
	CBCompoSeqAcq[ACQUISITION_L2_SURF]->setDown(false);

	if( QMessageBox::question(this,QString::fromLocal8Bit("SupervCLIMSO: Changement de la liste des acquisitions"),(!CBCompoSeqAcq[ACQUISITION_L2_SURF]->isChecked()) ? QString::fromLocal8Bit("Voulez-vous vraiment AJOUTER L2 surface dans la liste des acquisitions de L2 ?") : QString::fromLocal8Bit("Voulez-vous vraiment RETIRER L2 surface de la liste des acquisitions de L2 ?"),"Oui","Non",QString::null,1,1) == 0 ) CBCompoSeqAcq[ACQUISITION_L2_SURF]->setChecked(!CBCompoSeqAcq[ACQUISITION_L2_SURF]->isChecked());
}


// Slot de selection de l'acquisition L2 couronne pour la sequence d'acquitions de L2
//
void SupervCLIMSO::SlotCBCompoSeqAcqL2C(void)
{
	CBCompoSeqAcq[ACQUISITION_L2_COUR]->setDown(false);

	if( QMessageBox::question(this,QString::fromLocal8Bit("SupervCLIMSO: Changement de la liste des acquisitions"),(!CBCompoSeqAcq[ACQUISITION_L2_COUR]->isChecked()) ? QString::fromLocal8Bit("Voulez-vous vraiment AJOUTER L2 couronne dans la liste des acquisitions de L2 ?") : QString::fromLocal8Bit("Voulez-vous vraiment RETIRER L2 couronne de la liste des acquisitions de L2 ?"),"Oui","Non",QString::null,1,1) == 0 ) CBCompoSeqAcq[ACQUISITION_L2_COUR]->setChecked(!CBCompoSeqAcq[ACQUISITION_L2_COUR]->isChecked());
}


// Boite d'information "Vous devez d'abord initialiser les axes !"
//
void SupervCLIMSO::MessageDevezInitialiserAxes(void)
{
	QMessageBox::information(this,"SupervCLIMSO",QString::fromLocal8Bit("Vous devez d'abord initialiser les axes de CLIMSO."));
}


// Boite d'information "Vous devez valider l'utilisation de l'instrument i de CLIMSO !" 
//
void SupervCLIMSO::MessageDevezValider(int i)
{
	QMessageBox::information(this,"SupervCLIMSO",QString::fromLocal8Bit("Vous devez d'abord valider l'utilisation de l'instrument "+InstrumentCLIMSO[i]+" de CLIMSO."));
}


// Boite d'information "Vous devez valider l'utilisation d'une des instruments de CLIMSO !" 
//
void SupervCLIMSO::MessageDevezValiderUnInstrument(void)
{
	QMessageBox::information(this,"SupervCLIMSO",QString::fromLocal8Bit("Vous devez d'abord valider l'utilisation  d'un instrument de CLIMSO."));
}


// Boite d'information "Une pose est deja en cours sur l'instrument i de CLIMSO !" 
//
void SupervCLIMSO::MessageUnePoseDejaEnCoursSur(int i)
{
	QMessageBox::information(this,"SupervCLIMSO",QString::fromLocal8Bit("Une pose est déjà en cours sur l'instrument "+InstrumentCLIMSO[i]+" de CLIMSO."));
}


// Boite d'information "Une pose est en cours, on ne peut pas changer le mode d'observation de CLIMSO !" 
//
void SupervCLIMSO::MessageUnePoseEnCoursModifModeImpossible(void)
{
	QMessageBox::information(this,"SupervCLIMSO",QString::fromLocal8Bit("Une pose est en cours, on ne peut pas changer le mode d'observation de CLIMSO."));
}


// Boite d'information "Une pose est en cours sur C2, on ne peut pas changer le filtre de C2" 
//
void SupervCLIMSO::MessageUnePoseEnCoursC2ModifFiltreImpossible(void)
{
	QMessageBox::information(this,"SupervCLIMSO",QString::fromLocal8Bit("Une pose est en cours sur C2, on ne peut pas changer le filtre."));
}


// Boite d'information "Le mode d'observation de la roue d'ouverture n'est pas connu, vous ne pouvez pas declancher une pose" 
//
void SupervCLIMSO::MessageModeRoueOuvNonConnuePoseImpossible(void)
{
	QMessageBox::information(this,"SupervCLIMSO",QString::fromLocal8Bit("Le mode d'observation de la roue d'ouverture n'est pas connu, vous ne pouvez pas déclencher une pose."));
}


// Boite d'information "Le filtre actif de la roue a filtre de C2 n'est pas connu, vous ne pouvez pas declancher une pose" 
//
void SupervCLIMSO::MessageFiltreC2NonConnuPoseImpossible(void)
{
	QMessageBox::information(this,"SupervCLIMSO",QString::fromLocal8Bit("Le filtre actif de la roue à filtre de C2 n'est pas connu, vous ne pouvez pas déclencher une pose."));
}


// Mise a jour de l'etat des boutons de la fenetre principale en fonction du contexte
//
void SupervCLIMSO::MAJEtatBoutonsFP(void)
{
	// Si la variable de changement d'etat de l'acces au tableau des consignes de CLIMSO a changee
	//
	if( aMotDePasseConsignes != MotDePasseConsignes )
	{
		BoutonConsignes->setPalette(PaletteBoutonVerdatre);

		if( MotDePasseConsignes )
		{
			BoutonConsignes->setPixmap(QPixmap(IconConsignesActif_xpm));
		}
		else
		{
			BoutonConsignes->setPixmap(QPixmap(IconConsignesInactif_xpm));
		}

		aMotDePasseConsignes=MotDePasseConsignes;
	}


	// Si la variable de changement d'etat de l'initialisation des axes a changee depuis le dernier appel de cette fonction
	//
	if( AxesInitialises != aAxesInitialises )
	{
		// Si les axes ne sont pas initialises
		//
		if( !AxesInitialises )
		{
			BoutonInitialisationAxes->setPalette(PaletteBoutonVerdatre);

			BoutonModePointage->setPalette(PaletteBoutonOrangee);
			BoutonModePLU->setPalette(PaletteBoutonOrangee);
			BoutonModeCalibration->setPalette(PaletteBoutonOrangee);
			BoutonModeObservation->setPalette(PaletteBoutonOrangee);
			Bouton10747->setPalette(PaletteBoutonOrangee);
			Bouton10770->setPalette(PaletteBoutonOrangee);
			Bouton10798->setPalette(PaletteBoutonOrangee);
			Bouton10830->setPalette(PaletteBoutonOrangee);
			BoutonPoseImageC1->setPalette(PaletteBoutonOrangee);
			BoutonPoseImageC2->setPalette(PaletteBoutonOrangee);
			BoutonPoseImageL1->setPalette(PaletteBoutonOrangee);
			BoutonPoseImageL2->setPalette(PaletteBoutonOrangee);
			BoutonPoseBiasC1->setPalette(PaletteBoutonOrangee);
			BoutonPoseBiasC2->setPalette(PaletteBoutonOrangee);
			BoutonPoseBiasL1->setPalette(PaletteBoutonOrangee);
			BoutonPoseBiasL2->setPalette(PaletteBoutonOrangee);
			BoutonPoseDarkC1->setPalette(PaletteBoutonOrangee);
			BoutonPoseDarkC2->setPalette(PaletteBoutonOrangee);
			BoutonPoseDarkL1->setPalette(PaletteBoutonOrangee);
			BoutonPoseDarkL2->setPalette(PaletteBoutonOrangee);
			BoutonEtatC1->setPalette(PaletteBoutonOrangee);
			BoutonEtatC2->setPalette(PaletteBoutonOrangee);
			BoutonEtatL1->setPalette(PaletteBoutonOrangee);
			BoutonEtatL2->setPalette(PaletteBoutonOrangee);
			BoutonPosesBias->setPalette(PaletteBoutonOrangee);
			BoutonPosesDark->setPalette(PaletteBoutonOrangee);
			BoutonSequencePosesImages->setPalette(PaletteBoutonOrangee);

			aAxesInitialises=AxesInitialises;

			update();

			return;
		}
		else
		{
			BoutonInitialisationAxes->setPalette(PaletteBoutonVerdatre);

			BoutonPoseImageC1->setPalette(PaletteBoutonVerdatre);
			BoutonPoseImageC2->setPalette(PaletteBoutonVerdatre);
			BoutonPoseImageL1->setPalette(PaletteBoutonVerdatre);
			BoutonPoseImageL2->setPalette(PaletteBoutonVerdatre);
			BoutonPoseBiasC1->setPalette(PaletteBoutonVerdatre);
			BoutonPoseBiasC2->setPalette(PaletteBoutonVerdatre);
			BoutonPoseBiasL1->setPalette(PaletteBoutonVerdatre);
			BoutonPoseBiasL2->setPalette(PaletteBoutonVerdatre);
			BoutonPoseDarkC1->setPalette(PaletteBoutonVerdatre);
			BoutonPoseDarkC2->setPalette(PaletteBoutonVerdatre);
			BoutonPoseDarkL1->setPalette(PaletteBoutonVerdatre);
			BoutonPoseDarkL2->setPalette(PaletteBoutonVerdatre);
			BoutonEtatC1->setPalette(PaletteBoutonVerdatre);
			BoutonEtatC2->setPalette(PaletteBoutonVerdatre);
			BoutonEtatL1->setPalette(PaletteBoutonVerdatre);
			BoutonEtatL2->setPalette(PaletteBoutonVerdatre);
			BoutonPosesBias->setPalette(PaletteBoutonVerdatre);
			BoutonPosesDark->setPalette(PaletteBoutonVerdatre);
			BoutonSequencePosesImages->setPalette(PaletteBoutonVerdatre);
		}

		aAxesInitialises=AxesInitialises;
	}


	// Si la variable d'etat de changement de l'activite de C1 a changee
	//
	if( C1Actif != aC1Actif && AxesInitialises )
	{
		int TousPoseEnCours=PoseEnCours[CAMEROA_C1] && PoseEnCours[CAMEROA_C2] && PoseEnCours[CAMEROA_L1] && PoseEnCours[CAMEROA_L2];

		if( !PoseEnCours[CAMEROA_C1] )
		{
			BoutonInitialisationAxes->setPalette(PaletteBoutonVerdatre);
			BoutonEtatC1->setPalette(PaletteBoutonVerdatre);
		}
		else
		{
			BoutonInitialisationAxes->setPalette(PaletteBoutonOrangee);
			BoutonEtatC1->setPalette(PaletteBoutonOrangee);
		}

		if( (C1Actif && !PoseEnCours[CAMEROA_C1]) )
		{
			BoutonPoseImageC1->setPalette(PaletteBoutonVerdatre);
			BoutonPoseBiasC1->setPalette(PaletteBoutonVerdatre);
			BoutonPoseDarkC1->setPalette(PaletteBoutonVerdatre);
		}
		else
		{
			BoutonPoseImageC1->setPalette(PaletteBoutonOrangee);
			BoutonPoseBiasC1->setPalette(PaletteBoutonOrangee);
			BoutonPoseDarkC1->setPalette(PaletteBoutonOrangee);
		}

		if( TousPoseEnCours )
		{
			BoutonPosesBias->setPalette(PaletteBoutonOrangee);
			BoutonPosesDark->setPalette(PaletteBoutonOrangee);
			BoutonSequencePosesImages->setPalette(PaletteBoutonOrangee);
		}
		else
		{
			if( (C1Actif && !PoseEnCours[CAMEROA_C1]) | C2Actif | L1Actif | L2Actif ) BoutonPosesBias->setPalette(PaletteBoutonVerdatre); else BoutonPosesBias->setPalette(PaletteBoutonOrangee);

			if( (C1Actif && !PoseEnCours[CAMEROA_C1]) | C2Actif | L1Actif | L2Actif ) BoutonPosesDark->setPalette(PaletteBoutonVerdatre); else BoutonPosesDark->setPalette(PaletteBoutonOrangee);

			if( (C1Actif && !PoseEnCours[CAMEROA_C1]) | C2Actif | L1Actif | L2Actif ) BoutonSequencePosesImages->setPalette(PaletteBoutonVerdatre); else BoutonSequencePosesImages->setPalette(PaletteBoutonOrangee);
		}

		aC1Actif=C1Actif;
	}


	// Si la variable d'etat de changement de l'activite de C2 a changee
	//
	if( C2Actif != aC2Actif && AxesInitialises )
	{
		int TousPoseEnCours=PoseEnCours[CAMEROA_C1] && PoseEnCours[CAMEROA_C2] && PoseEnCours[CAMEROA_L1] && PoseEnCours[CAMEROA_L2];

		if( !PoseEnCours[CAMEROA_C2] )
		{
			BoutonInitialisationAxes->setPalette(PaletteBoutonVerdatre);
			BoutonEtatC2->setPalette(PaletteBoutonVerdatre);
		}
		else
		{
			BoutonInitialisationAxes->setPalette(PaletteBoutonOrangee);
			BoutonEtatC2->setPalette(PaletteBoutonOrangee);
		}

		if( (C2Actif && !PoseEnCours[CAMEROA_C2]) )
		{
			BoutonPoseImageC2->setPalette(PaletteBoutonVerdatre);
			BoutonPoseBiasC2->setPalette(PaletteBoutonVerdatre);
			BoutonPoseDarkC2->setPalette(PaletteBoutonVerdatre);
		}
		else
		{
			BoutonPoseImageC2->setPalette(PaletteBoutonOrangee);
			BoutonPoseBiasC2->setPalette(PaletteBoutonOrangee);
			BoutonPoseDarkC2->setPalette(PaletteBoutonOrangee);
		}

		if( TousPoseEnCours )
		{
			BoutonPosesBias->setPalette(PaletteBoutonOrangee);
			BoutonPosesDark->setPalette(PaletteBoutonOrangee);
			BoutonSequencePosesImages->setPalette(PaletteBoutonOrangee);
		}
		else
		{
			if( C1Actif | (C2Actif && !PoseEnCours[CAMEROA_C2]) | L1Actif | L2Actif ) BoutonPosesBias->setPalette(PaletteBoutonVerdatre); else BoutonPosesBias->setPalette(PaletteBoutonOrangee);

			if( C1Actif | (C2Actif && !PoseEnCours[CAMEROA_C2]) | L1Actif | L2Actif ) BoutonPosesDark->setPalette(PaletteBoutonVerdatre); else BoutonPosesDark->setPalette(PaletteBoutonOrangee);

			if( C1Actif | (C2Actif && !PoseEnCours[CAMEROA_C2]) | L1Actif | L2Actif ) BoutonSequencePosesImages->setPalette(PaletteBoutonVerdatre); else BoutonSequencePosesImages->setPalette(PaletteBoutonOrangee);
		}

		aC2Actif=C2Actif;
	}


	// Si la variable d'etat de changement de l'activite de L1 a changee
	//
	if( L1Actif != aL1Actif && AxesInitialises )
	{
		int TousPoseEnCours=PoseEnCours[CAMEROA_C1] && PoseEnCours[CAMEROA_C2] && PoseEnCours[CAMEROA_L1] && PoseEnCours[CAMEROA_L2];

		if( !PoseEnCours[CAMEROA_L1] )
		{
			BoutonInitialisationAxes->setPalette(PaletteBoutonVerdatre);
			BoutonEtatL1->setPalette(PaletteBoutonVerdatre);
		}
		else
		{
			BoutonInitialisationAxes->setPalette(PaletteBoutonOrangee);
			BoutonEtatL1->setPalette(PaletteBoutonOrangee);
		}

		if( (L1Actif && !PoseEnCours[CAMEROA_L1]) )
		{
			BoutonPoseImageL1->setPalette(PaletteBoutonVerdatre);
			BoutonPoseBiasL1->setPalette(PaletteBoutonVerdatre);
			BoutonPoseDarkL1->setPalette(PaletteBoutonVerdatre);
		}
		else
		{
			BoutonPoseImageL1->setPalette(PaletteBoutonOrangee);
			BoutonPoseBiasL1->setPalette(PaletteBoutonOrangee);
			BoutonPoseDarkL1->setPalette(PaletteBoutonOrangee);
		}

		if( TousPoseEnCours )
		{
			BoutonPosesBias->setPalette(PaletteBoutonOrangee);
			BoutonPosesDark->setPalette(PaletteBoutonOrangee);
			BoutonSequencePosesImages->setPalette(PaletteBoutonOrangee);
		}
		else
		{
			if( C1Actif | C2Actif | (L1Actif && !PoseEnCours[CAMEROA_L1]) | L2Actif ) BoutonPosesBias->setPalette(PaletteBoutonVerdatre); else BoutonPosesBias->setPalette(PaletteBoutonOrangee);

			if( C1Actif | C2Actif | (L1Actif && !PoseEnCours[CAMEROA_L1]) | L2Actif ) BoutonPosesDark->setPalette(PaletteBoutonVerdatre); else BoutonPosesDark->setPalette(PaletteBoutonOrangee);

			if( C1Actif | C2Actif | (L1Actif && !PoseEnCours[CAMEROA_L1]) | L2Actif ) BoutonSequencePosesImages->setPalette(PaletteBoutonVerdatre); else BoutonSequencePosesImages->setPalette(PaletteBoutonOrangee);
		}

		aL1Actif=L1Actif;
	}


	// Si la variable d'etat de changement de l'activite de L2 a changee
	//
	if( L2Actif != aL2Actif && AxesInitialises )
	{
		int TousPoseEnCours=PoseEnCours[CAMEROA_C1] && PoseEnCours[CAMEROA_C2] && PoseEnCours[CAMEROA_L1] && PoseEnCours[CAMEROA_L2];

		if( !PoseEnCours[CAMEROA_L2] )
		{
			BoutonInitialisationAxes->setPalette(PaletteBoutonVerdatre);
			BoutonEtatL2->setPalette(PaletteBoutonVerdatre);
		}
		else
		{
			BoutonInitialisationAxes->setPalette(PaletteBoutonOrangee);
			BoutonEtatL2->setPalette(PaletteBoutonOrangee);
		}

		if( (L2Actif && !PoseEnCours[CAMEROA_L2]) )
		{
			BoutonPoseImageL2->setPalette(PaletteBoutonVerdatre);
			BoutonPoseBiasL2->setPalette(PaletteBoutonVerdatre);
			BoutonPoseDarkL2->setPalette(PaletteBoutonVerdatre);
		}
		else
		{
			BoutonPoseImageL2->setPalette(PaletteBoutonOrangee);
			BoutonPoseBiasL2->setPalette(PaletteBoutonOrangee);
			BoutonPoseDarkL2->setPalette(PaletteBoutonOrangee);
		}

		if( TousPoseEnCours )
		{
			BoutonPosesBias->setPalette(PaletteBoutonOrangee);
			BoutonPosesDark->setPalette(PaletteBoutonOrangee);
			BoutonSequencePosesImages->setPalette(PaletteBoutonOrangee);
		}
		else
		{
			if( C1Actif | C2Actif | L1Actif | (L2Actif && !PoseEnCours[CAMEROA_L2]) ) BoutonPosesBias->setPalette(PaletteBoutonVerdatre); else BoutonPosesBias->setPalette(PaletteBoutonOrangee);

			if( C1Actif | C2Actif | L1Actif | (L2Actif && !PoseEnCours[CAMEROA_L2]) ) BoutonPosesDark->setPalette(PaletteBoutonVerdatre); else BoutonPosesDark->setPalette(PaletteBoutonOrangee);

			if( C1Actif | C2Actif | L1Actif | (L2Actif && !PoseEnCours[CAMEROA_L2]) ) BoutonSequencePosesImages->setPalette(PaletteBoutonVerdatre); else BoutonSequencePosesImages->setPalette(PaletteBoutonOrangee);
		}

		aL2Actif=L2Actif;
	}


	// Si la variable de changement d'etat du mode d'observation courant a changee
	//
	if( ModeObservation != aModeObservation && AxesInitialises )
	{
		int UnePoseEnCours=PoseEnCours[CAMEROA_C1] | PoseEnCours[CAMEROA_C2] | PoseEnCours[CAMEROA_L1] | PoseEnCours[CAMEROA_L2];

		if( ModeObservation != ModeRO_NonInitialise )
		{
			if( UnePoseEnCours )
			{
				BoutonModePointage->setPalette(PaletteBoutonOrangee);
				BoutonModePLU->setPalette(PaletteBoutonOrangee);
				BoutonModeCalibration->setPalette(PaletteBoutonOrangee);
				BoutonModeObservation->setPalette(PaletteBoutonOrangee);
			}
			else
			{
				BoutonModePointage->setPalette(PaletteBoutonVerdatre);
				BoutonModePLU->setPalette(PaletteBoutonVerdatre);
				BoutonModeCalibration->setPalette(PaletteBoutonVerdatre);
				BoutonModeObservation->setPalette(PaletteBoutonVerdatre);
			}
		}
		else
		{
			BoutonModePointage->setPalette(PaletteBoutonOrangee);
			BoutonModePLU->setPalette(PaletteBoutonOrangee);
			BoutonModeCalibration->setPalette(PaletteBoutonOrangee);
			BoutonModeObservation->setPalette(PaletteBoutonOrangee);
		}

		if( ModeObservation == ModeRO_Pointage ) BoutonModePointage->setPixmap(QPixmap(IconModePointageActif_xpm)); else BoutonModePointage->setPixmap(QPixmap(IconModePointageInactif_xpm));

		if( ModeObservation == ModeRO_PLU ) BoutonModePLU->setPixmap(QPixmap(IconModePLUActif_xpm)); else BoutonModePLU->setPixmap(QPixmap(IconModePLUInactif_xpm));

		if( ModeObservation == ModeRO_Calibration ) BoutonModeCalibration->setPixmap(QPixmap(IconModeCalibrationActif_xpm)); else BoutonModeCalibration->setPixmap(QPixmap(IconModeCalibrationInactif_xpm));

		if( ModeObservation == ModeRO_Observation ) BoutonModeObservation->setPixmap(QPixmap(IconModeObservationActif_xpm)); else BoutonModeObservation->setPixmap(QPixmap(IconModeObservationInactif_xpm));

		aModeObservation=ModeObservation;
	}


	// Si la variable de changement d'etat du filtre en place dans C2 a changee
	//
	if( FiltreC2 != aFiltreC2 && AxesInitialises )
	{
		if( FiltreC2 != FiltreC2_NonInitialise )
		{
			if( PoseEnCours[CAMEROA_C2] )
			{
				Bouton10747->setPalette(PaletteBoutonOrangee);
				Bouton10770->setPalette(PaletteBoutonOrangee);
				Bouton10798->setPalette(PaletteBoutonOrangee);
				Bouton10830->setPalette(PaletteBoutonOrangee);
			}
			else
			{
				Bouton10747->setPalette(PaletteBoutonVerdatre);
				Bouton10770->setPalette(PaletteBoutonVerdatre);
				Bouton10798->setPalette(PaletteBoutonVerdatre);
				Bouton10830->setPalette(PaletteBoutonVerdatre);
			}
		}
		else
		{
			Bouton10747->setPalette(PaletteBoutonOrangee);
			Bouton10770->setPalette(PaletteBoutonOrangee);
			Bouton10798->setPalette(PaletteBoutonOrangee);
			Bouton10830->setPalette(PaletteBoutonOrangee);
		}

		if( FiltreC2 == FiltreC2_10747 ) Bouton10747->setPixmap(QPixmap(IconFiltreC2_10747_Actif_xpm)); else Bouton10747->setPixmap(QPixmap(IconFiltreC2_10747_Inactif_xpm));

		if( FiltreC2 == FiltreC2_10770 ) Bouton10770->setPixmap(QPixmap(IconFiltreC2_10770_Actif_xpm)); else Bouton10770->setPixmap(QPixmap(IconFiltreC2_10770_Inactif_xpm));

		if( FiltreC2 == FiltreC2_10798 ) Bouton10798->setPixmap(QPixmap(IconFiltreC2_10798_Actif_xpm)); else Bouton10798->setPixmap(QPixmap(IconFiltreC2_10798_Inactif_xpm));

		if( FiltreC2 == FiltreC2_10830 ) Bouton10830->setPixmap(QPixmap(IconFiltreC2_10830_Actif_xpm)); else Bouton10830->setPixmap(QPixmap(IconFiltreC2_10830_Inactif_xpm));

		aFiltreC2=FiltreC2;
	}


	// Si des images sont supprimables
	//
	for( int i=0 ; i < NB_CAMEROA; i++ )
	{
		if( ListeNomFichDerImg[i].isEmpty() )
		{
			switch( i )
			{
				case CAMEROA_C1:	BoutonSuppressionDerImgC1->setPalette(PaletteBoutonOrangee);	break;
				case CAMEROA_C2:	BoutonSuppressionDerImgC2->setPalette(PaletteBoutonOrangee);	break;
				case CAMEROA_L1:	BoutonSuppressionDerImgL1->setPalette(PaletteBoutonOrangee);	break;
				case CAMEROA_L2:	BoutonSuppressionDerImgL2->setPalette(PaletteBoutonOrangee);	break;
			}
		}
		else
		{
			switch( i )
			{
				case CAMEROA_C1:	BoutonSuppressionDerImgC1->setPalette(PaletteBoutonVerdatre);	break;
				case CAMEROA_C2:	BoutonSuppressionDerImgC2->setPalette(PaletteBoutonVerdatre);	break;
				case CAMEROA_L1:	BoutonSuppressionDerImgL1->setPalette(PaletteBoutonVerdatre);	break;
				case CAMEROA_L2:	BoutonSuppressionDerImgL2->setPalette(PaletteBoutonVerdatre);	break;
			}
		}
	}


	// Mise a jour de la fenetre principale
	//
	update();
}


// Ajouter et Afficher un log dans la fenetre des logs
//
// CE:	On passe la chaine a afficher ;
//
// CS:	-
//
void SupervCLIMSO::Log(QString log)
{
	// On recupere la date et l'heure courante UT du systeme
	//
	QDateTime DateHeureUT=QDateTime::currentDateTime(Qt::UTC);

	// Composition de la chaine pour donner l'heure du log
	//
	QString ChaineHeure=DateHeureUT.toString("hh:mm:ss: ");

	// Chaine de la ligne de log
	//
	QString chaine;
	chaine.reserve(TAILLE_MINI_CHAINE_LOG);
	chaine=QString::fromLocal8Bit(ChaineHeure+log);

	// On ajoute et affiche la ligne du commentaire
	//
	Logs->append(chaine);

	// On sauvegarde la ligne dans le fichier de log
	//
	FluxFichierLogsSupervCLIMSO << chaine+"\n" ;
}


// Declenchement d'une pose de type Bias pour l'instrument i
//
// CE:	On passe true pour afficher le log
//
//		On passe l'indice de l'instrument de CLIMSO
//
void SupervCLIMSO::DeclencherPoseBias(int log,int i)
{
//	QString ChaineCmd;							// Chaine avec taille minimale pour la composition de commandes afin d'eviter un bogue QString et la rapidite
//	ChaineCmd.reserve(TAILLE_MINI_CHAINE_CMD);

	MutexEnvChaineBIO_CamerOA[i].lock();

	if( PLCommandeCamerOA[i]->Client->EnvoyerChaineBIO(CmdCamerOAPoseBias) <= 0 )
	{
		// Erreur lors de l'emission
		//
		Log("*** ERREUR: Impossible d'envoyer la commande de déclenchement de pose de Bias à l'instrument "+InstrumentCLIMSO[i]+" ***");

		PoseEnCours[i]=false;

		return;
	}

	MutexEnvChaineBIO_CamerOA[i].unlock();

	if( log ) Log("Pose de BIAS déclenchée sur l'instrument "+InstrumentCLIMSO[i]+".");

	PoseEnCours[i]=true;

	// Faire croire a un changement pour redessiner les boutons
	//
	switch( i )
	{
		case CAMEROA_C1: aC1Actif=-1; break;
		case CAMEROA_C2:
			aC2Actif=-1;
			aFiltreC2=FiltreC2_NonInitialise;
			break;
		case CAMEROA_L1: aL1Actif=-1; break;
		case CAMEROA_L2: aL2Actif=-1; break;
	}
	aModeObservation=ModeRO_NonInitialise;
}


// Envoyer une commande sans parametre a un CamerOA
//
// CE:	On passe le numero du CamerOA ;
//
//		On passe le numero de la commande ;
//
// CS:	-
//
void SupervCLIMSO::EnvoyerCommandeCamerOA(int n,int cmd)
{
	if( PLCommandeCamerOA[n]->Client->Connecte() )
	{
		QString ChaineCmd;					// Chaine avec taille minimale pour la composition de commandes afin d'eviter un bogue QString et la rapidite
		ChaineCmd.reserve(TAILLE_MINI_CHAINE_CMD);

		// Emission de la commande
		//
		ChaineCmd=CmdClientCamerOA[cmd];
		ChaineCmd.append("\n");

		MutexEnvChaineBIO_CamerOA[n].lock();

		if( PLCommandeCamerOA[n]->Client->EnvoyerChaineBIO(ChaineCmd) <= 0 )
		{
			// Erreur lors de l'emission
			//
			Log("*** ERREUR: Impossible d'envoyer la commande:"+CmdClientCamerOA[cmd]+" à l'instrument "+InstrumentCLIMSO[n]+" ***");
		}

		MutexEnvChaineBIO_CamerOA[n].unlock();
	}
	else
	{
			Log("*** ERREUR: l'instrument "+InstrumentCLIMSO[n]+" n'est pas connecté pour envoyer la commande:"+CmdClientCamerOA[cmd]+" ***");
	}
}


// Envoyer une commande avec un parametre entier a un CamerOA
//
// CE:	On passe le numero du CamerOA ;
//
//		On passe le numero de la commande ;
//
//		On passe la valeur entiere comme argument de cette commande.
//
// CS:	-
//
void SupervCLIMSO::EnvoyerCommandeIntCamerOA(int n,int cmd,int v)
{
	if( PLCommandeCamerOA[n]->Client->Connecte() )
	{
		QString ChaineCmd;					// Chaine avec taille minimale pour la composition de commandes afin d'eviter un bogue QString et la rapidite
		ChaineCmd.reserve(TAILLE_MINI_CHAINE_CMD);

		// Composition de la chaine de commande avec son argument
		//
		ChaineCmd=CmdClientCamerOA[cmd];
		ChaineCmd+=QString("%1\n").arg(v);

		// Emission de la commande
		//
		MutexEnvChaineBIO_CamerOA[n].lock();

		if( PLCommandeCamerOA[n]->Client->EnvoyerChaineBIO(ChaineCmd) <= 0 )
		{
			// Erreur lors de l'emission
			//
			Log("*** ERREUR: Impossible d'envoyer la commande:"+CmdClientCamerOA[cmd]+" à l'instrument "+InstrumentCLIMSO[n]+" ***");
		}

		MutexEnvChaineBIO_CamerOA[n].unlock();
	}
	else
	{
			Log("*** ERREUR: l'instrument "+InstrumentCLIMSO[n]+" n'est pas connecté pour envoyer la commande:"+CmdClientCamerOA[cmd]+" ***");
	}
}


// Surcharge de la fonction de handler des evenements particuliers crees et adresses pour SupervCLIMSO
//
void SupervCLIMSO::customEvent(QCustomEvent *ce)
{
	// On aiguille selon le type d'evenement particulier recu par SupervCLIMSO
	//


	// Evenement de l'arrivee d'une nouvelle image de centrage
	//
	if( ce->type() == ID_CUSTOM_EVENT_SUPERVCLIMSO_NOUVIMGCENTRAGE )
	{
		// Evenement nouvelle image de centrage disponible
		//
		CEventSupervCLIMSO_NouvImageCentrage *event=(CEventSupervCLIMSO_NouvImageCentrage *) ce;	// Typage de l'evenement

		PLDonneesCamerOA[event->Identifieur()]->MutexTrameImageC.lock();

		switch( event->Identifieur() )
		{
			case CAMEROA_C1:
				VisuC1->ChargerImage((unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteIC.tx,(unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteIC.ty,(unsigned short *) &PLDonneesCamerOA[event->Identifieur()]->TrameIC[0],PLDonneesCamerOA[event->Identifieur()]->EnTeteIC.debut,PLDonneesCamerOA[event->Identifieur()]->EnTeteIC.fin,PLDonneesCamerOA[event->Identifieur()]->EnTeteIC.duree);
				break;

			case CAMEROA_C2:
				VisuC2->ChargerImage((unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteIC.tx,(unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteIC.ty,(unsigned short *) &PLDonneesCamerOA[event->Identifieur()]->TrameIC[0],PLDonneesCamerOA[event->Identifieur()]->EnTeteIC.debut,PLDonneesCamerOA[event->Identifieur()]->EnTeteIC.fin,PLDonneesCamerOA[event->Identifieur()]->EnTeteIC.duree);
				break;

			case CAMEROA_L1:
				VisuL1->ChargerImage((unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteIC.tx,(unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteIC.ty,(unsigned short *) &PLDonneesCamerOA[event->Identifieur()]->TrameIC[0],PLDonneesCamerOA[event->Identifieur()]->EnTeteIC.debut,PLDonneesCamerOA[event->Identifieur()]->EnTeteIC.fin,PLDonneesCamerOA[event->Identifieur()]->EnTeteIC.duree);
				break;

			case CAMEROA_L2:
				VisuL2->ChargerImage((unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteIC.tx,(unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteIC.ty,(unsigned short *) &PLDonneesCamerOA[event->Identifieur()]->TrameIC[0],PLDonneesCamerOA[event->Identifieur()]->EnTeteIC.debut,PLDonneesCamerOA[event->Identifieur()]->EnTeteIC.fin,PLDonneesCamerOA[event->Identifieur()]->EnTeteIC.duree);
				break;
		}

		PLDonneesCamerOA[event->Identifieur()]->MutexTrameImageC.unlock();

		// On peut demander la mise a jour du widget
		//
		switch( event->Identifieur() )
		{
			case CAMEROA_C1:
				VisuC1->ConsigneSeuilBas(VisuC1->ValMinImage());
				VisuC1->ConsigneSeuilHaut(VisuC1->ValMaxImage());
				VisuC1->update();
				break;

			case CAMEROA_C2:
				VisuC2->ConsigneSeuilBas(VisuC2->ValMinImage());
				VisuC2->ConsigneSeuilHaut(VisuC2->ValMaxImage());
				VisuC2->update();
				break;

			case CAMEROA_L1:
				VisuL1->ConsigneSeuilBas(VisuL1->ValMinImage());
				VisuL1->ConsigneSeuilHaut(VisuL1->ValMaxImage());
				VisuL1->update();
				break;

			case CAMEROA_L2:
				VisuL2->ConsigneSeuilBas(VisuL2->ValMinImage());
				VisuL2->ConsigneSeuilHaut(VisuL2->ValMaxImage());
				VisuL2->update();
				break;
		}

		// Si les consignes du CamerOA n'ont pas ete initialisees
		//
		if( !ConsignesCamerOAInitialisees[event->Identifieur()] )
		{
			// Il s'agissait donc de la premiere image depuis le demarrage de l'instrument, realisee avec les consignes memorisees
			//
			// On programme les consignes actuelles de SupervCLIMSO
			//
			MutexConsignesDansUniteEntiere.lock();

			switch( event->Identifieur() )
			{
				case CAMEROA_C1:
					EnvoyerCommandeIntCamerOA(CAMEROA_C1,CAMEROA_CMD_CTPC,ConsignesDansUniteEntiere[CONSIGNE_C1_IMG_TP_CENTRAGE]);
					sleep(1);
					EnvoyerCommandeIntCamerOA(CAMEROA_C1,CAMEROA_CMD_CTEMP,ConsignesDansUniteEntiere[CONSIGNE_C1_TCCD]);
					sleep(1);
					switch( ConsignesDansUniteEntiere[CONSIGNE_C1_VENTILATEUR] )
					{
						case 1:	EnvoyerCommandeCamerOA(CAMEROA_C1,CAMEROA_CMD_FANLOW);		break;
						case 2:	EnvoyerCommandeCamerOA(CAMEROA_C1,CAMEROA_CMD_FANMEDIUM);	break;
						case 3:	EnvoyerCommandeCamerOA(CAMEROA_C1,CAMEROA_CMD_FANHIGH);		break;
						default:	EnvoyerCommandeCamerOA(CAMEROA_C1,CAMEROA_CMD_FANLOW);	break;
					}
					break;

				case CAMEROA_C2:
					EnvoyerCommandeIntCamerOA(CAMEROA_C2,CAMEROA_CMD_CTPC,ConsignesDansUniteEntiere[CONSIGNE_C2_IMG_TP_CENTRAGE_10830]);
					sleep(1);
					EnvoyerCommandeIntCamerOA(CAMEROA_C2,CAMEROA_CMD_CTEMP,ConsignesDansUniteEntiere[CONSIGNE_C2_TCCD]);
					sleep(1);
					switch( ConsignesDansUniteEntiere[CONSIGNE_C2_VENTILATEUR] )
					{
						case 1:	EnvoyerCommandeCamerOA(CAMEROA_C2,CAMEROA_CMD_FANLOW);		break;
						case 2:	EnvoyerCommandeCamerOA(CAMEROA_C2,CAMEROA_CMD_FANMEDIUM);	break;
						case 3:	EnvoyerCommandeCamerOA(CAMEROA_C2,CAMEROA_CMD_FANHIGH);		break;
						default:	EnvoyerCommandeCamerOA(CAMEROA_C2,CAMEROA_CMD_FANLOW);	break;
					}
					sleep(1);
					break;

				case CAMEROA_L1:
					EnvoyerCommandeIntCamerOA(CAMEROA_L1,CAMEROA_CMD_CTPC,ConsignesDansUniteEntiere[CONSIGNE_L1_IMG_TP_CENTRAGE]);
					sleep(1);
					EnvoyerCommandeIntCamerOA(CAMEROA_L1,CAMEROA_CMD_CTEMP,ConsignesDansUniteEntiere[CONSIGNE_L1_TCCD]);
					sleep(1);
					switch( ConsignesDansUniteEntiere[CONSIGNE_L1_VENTILATEUR] )
					{
						case 1:	EnvoyerCommandeCamerOA(CAMEROA_L1,CAMEROA_CMD_FANLOW);		break;
						case 2:	EnvoyerCommandeCamerOA(CAMEROA_L1,CAMEROA_CMD_FANMEDIUM);	break;
						case 3:	EnvoyerCommandeCamerOA(CAMEROA_L1,CAMEROA_CMD_FANHIGH);		break;
						default:	EnvoyerCommandeCamerOA(CAMEROA_L1,CAMEROA_CMD_FANLOW);	break;
					}
					break;

				case CAMEROA_L2:
					EnvoyerCommandeIntCamerOA(CAMEROA_L2,CAMEROA_CMD_CTPC,ConsignesDansUniteEntiere[CONSIGNE_L2_IMG_TP_CENTRAGE]);
					sleep(1);
					EnvoyerCommandeIntCamerOA(CAMEROA_L2,CAMEROA_CMD_CTEMP,ConsignesDansUniteEntiere[CONSIGNE_L2_TCCD]);
					sleep(1);
					switch( ConsignesDansUniteEntiere[CONSIGNE_L2_VENTILATEUR] )
					{
						case 1:	EnvoyerCommandeCamerOA(CAMEROA_L2,CAMEROA_CMD_FANLOW);		break;
						case 2:	EnvoyerCommandeCamerOA(CAMEROA_L2,CAMEROA_CMD_FANMEDIUM);	break;
						case 3:	EnvoyerCommandeCamerOA(CAMEROA_L2,CAMEROA_CMD_FANHIGH);		break;
						default:	EnvoyerCommandeCamerOA(CAMEROA_L2,CAMEROA_CMD_FANLOW);	break;
					}
					break;
			}
			MutexConsignesDansUniteEntiere.unlock();

			// Les consignes sont initialisees maintenant
			//
			ConsignesCamerOAInitialisees[event->Identifieur()]=true;
		}

		return;
	}


	// Evenement de l'arrivee d'une nouvelle image de centrage horizontal
	//
	if( ce->type() == ID_CUSTOM_EVENT_SUPERVCLIMSO_NOUVIMGCENTRAGEH )
	{
		// Evenement nouvelle image de centrage horizontal disponible
		//
		CEventSupervCLIMSO_NouvImageCentrageH *event=(CEventSupervCLIMSO_NouvImageCentrageH *) ce;	// Typage de l'evenement

		PLDonneesCamerOA[event->Identifieur()]->MutexTrameImageCH.lock();

		switch( event->Identifieur() )
		{
			case CAMEROA_C1:
				VisuC1->ChargerImageH((unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteICH.tx,(unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteICH.ty,(unsigned short *) &PLDonneesCamerOA[event->Identifieur()]->TrameICH[0],PLDonneesCamerOA[event->Identifieur()]->EnTeteICH.debut,PLDonneesCamerOA[event->Identifieur()]->EnTeteICH.fin,PLDonneesCamerOA[event->Identifieur()]->EnTeteICH.duree);
				break;

			case CAMEROA_C2:
				VisuC2->ChargerImageH((unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteICH.tx,(unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteICH.ty,(unsigned short *) &PLDonneesCamerOA[event->Identifieur()]->TrameICH[0],PLDonneesCamerOA[event->Identifieur()]->EnTeteICH.debut,PLDonneesCamerOA[event->Identifieur()]->EnTeteICH.fin,PLDonneesCamerOA[event->Identifieur()]->EnTeteICH.duree);
				break;

			case CAMEROA_L1:
				VisuL1->ChargerImageH((unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteICH.tx,(unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteICH.ty,(unsigned short *) &PLDonneesCamerOA[event->Identifieur()]->TrameICH[0],PLDonneesCamerOA[event->Identifieur()]->EnTeteICH.debut,PLDonneesCamerOA[event->Identifieur()]->EnTeteICH.fin,PLDonneesCamerOA[event->Identifieur()]->EnTeteICH.duree);
				break;

			case CAMEROA_L2:
				VisuL2->ChargerImageH((unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteICH.tx,(unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteICH.ty,(unsigned short *) &PLDonneesCamerOA[event->Identifieur()]->TrameICH[0],PLDonneesCamerOA[event->Identifieur()]->EnTeteICH.debut,PLDonneesCamerOA[event->Identifieur()]->EnTeteICH.fin,PLDonneesCamerOA[event->Identifieur()]->EnTeteICH.duree);
				break;
		}

		PLDonneesCamerOA[event->Identifieur()]->MutexTrameImageCH.unlock();

		// On peut demander la mise a jour du widget
		//
		switch( event->Identifieur() )
		{
			case CAMEROA_C1:
				VisuC1->update();
				break;

			case CAMEROA_C2:
				VisuC2->update();
				break;

			case CAMEROA_L1:
				VisuL1->update();
				break;

			case CAMEROA_L2:
				VisuL2->update();
				break;
		}

		return;
	}


	// Evenement de l'arrivee d'une nouvelle image de centrage vertical
	//
	if( ce->type() == ID_CUSTOM_EVENT_SUPERVCLIMSO_NOUVIMGCENTRAGEV )
	{
		// Evenement nouvelle image de centrage vertical disponible
		//
		CEventSupervCLIMSO_NouvImageCentrageV *event=(CEventSupervCLIMSO_NouvImageCentrageV *) ce;	// Typage de l'evenement

		PLDonneesCamerOA[event->Identifieur()]->MutexTrameImageCV.lock();

		switch( event->Identifieur() )
		{
			case CAMEROA_C1:
				VisuC1->ChargerImageV((unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteICV.tx,(unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteICV.ty,(unsigned short *) &PLDonneesCamerOA[event->Identifieur()]->TrameICV[0],PLDonneesCamerOA[event->Identifieur()]->EnTeteICV.debut,PLDonneesCamerOA[event->Identifieur()]->EnTeteICV.fin,PLDonneesCamerOA[event->Identifieur()]->EnTeteICV.duree);
				break;

			case CAMEROA_C2:
				VisuC2->ChargerImageV((unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteICV.tx,(unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteICV.ty,(unsigned short *) &PLDonneesCamerOA[event->Identifieur()]->TrameICV[0],PLDonneesCamerOA[event->Identifieur()]->EnTeteICV.debut,PLDonneesCamerOA[event->Identifieur()]->EnTeteICV.fin,PLDonneesCamerOA[event->Identifieur()]->EnTeteICV.duree);
				break;

			case CAMEROA_L1:
				VisuL1->ChargerImageV((unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteICV.tx,(unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteICV.ty,(unsigned short *) &PLDonneesCamerOA[event->Identifieur()]->TrameICV[0],PLDonneesCamerOA[event->Identifieur()]->EnTeteICV.debut,PLDonneesCamerOA[event->Identifieur()]->EnTeteICV.fin,PLDonneesCamerOA[event->Identifieur()]->EnTeteICV.duree);
				break;

			case CAMEROA_L2:
				VisuL2->ChargerImageV((unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteICV.tx,(unsigned short) PLDonneesCamerOA[event->Identifieur()]->EnTeteICV.ty,(unsigned short *) &PLDonneesCamerOA[event->Identifieur()]->TrameICV[0],PLDonneesCamerOA[event->Identifieur()]->EnTeteICV.debut,PLDonneesCamerOA[event->Identifieur()]->EnTeteICV.fin,PLDonneesCamerOA[event->Identifieur()]->EnTeteICV.duree);
				break;
		}

		PLDonneesCamerOA[event->Identifieur()]->MutexTrameImageCV.unlock();

		// On peut demander la mise a jour du widget
		//
		switch( event->Identifieur() )
		{
			case CAMEROA_C1:
				VisuC1->update();
				break;

			case CAMEROA_C2:
				VisuC2->update();
				break;

			case CAMEROA_L1:
				VisuL1->update();
				break;

			case CAMEROA_L2:
				VisuL2->update();
				break;
		}

		return;
	}


	// Evenement de reception de la position des axes en points quadratures codeurs
	//
	if( ce->type() == ID_CUSTOM_EVENT_SUPERVCLIMSO_POSAXES )
	{
		// Evenement nouvelle image disponible
		//
		CEventSupervCLIMSO_PosAxes *event=(CEventSupervCLIMSO_PosAxes *) ce;	// Typage de l'evenement

		for( int i=0; i < NB_AXES; i++ )
		{
			double v,fr;		// Variable de travail

			// Position en micropas moteurs dans le repere reel de l'axe
			//
			switch( i )
			{
				case AXE_ROUE_OUVERTURE:
					v=OFFSET_MICROPAS_MOTEUR_POS_ZERO_ROUE_OUVERTURE;	// pos=0   Ouverture OBS devant C1, C2, L1, L2
					v-=((double) event->Valeur(AXE_ROUE_OUVERTURE))*NB_MICROPAS_MOTEUR_PT_AXE_ROUE_OUVERTURE/NB_POINTS_QUADRATURE_CODEUR_PT_AXE_ROUE_OUVERTURE;
					break;

				case AXE_ROUE_FILTREC2:
					v=OFFSET_MICROPAS_MOTEUR_POS_ZERO_ROUE_FILTREC2;	// pos=0   Filtre 10747 dans l'axe optique
					v-=((double) event->Valeur(AXE_ROUE_FILTREC2))*NB_MICROPAS_MOTEUR_PT_AXE_ROUE_FILTREC2/NB_POINTS_QUADRATURE_CODEUR_PT_AXE_ROUE_FILTREC2;
					break;

				case AXE_PLATINE_X:
					v=((double) event->Valeur(AXE_PLATINE_X));	// PAS DE POSITION MICROPAS POUR CET AXE ON EST EN PAS QUADRATURE CODEUR
					break;

				case AXE_PLATINE_Y:
					v=((double) event->Valeur(AXE_PLATINE_Y));	// PAS DE POSITION MICROPAS POUR CET AXE ON EST EN PAS QUADRATURE CODEUR
					break;
			}

			fr=modf(v,&v);
			if( fr > 0.5 ) v+=1.0;

			PosAxeMicropasMoteur[i]=(int) v;


			// Position equivalente en degres
			//
			aPosAxeDegres[i]=PosAxeDegres[i];	// Sauvegarde de la position courante

			switch( i )
			{
				case AXE_ROUE_OUVERTURE:

					PosAxeDegres[i]=-360.0*((double) PosAxeMicropasMoteur[i])/NB_MICROPAS_MOTEUR_PT_AXE_ROUE_OUVERTURE;

					if( fabs(PosAxeDegres[i]-aPosAxeDegres[i]) < PRECISION_POS_MODE_ROUE_OUVERTURE )
					{
						// La position n'a pas changee assez entre deux rafraichissement, on considere que nous avons atteint un mode d'observation car la roue tourne peut
						//
						if( fabs(PositionsModeOuvertureCLIMSO[ModeRO_Pointage]-PosAxeDegres[i]) < PRECISION_POS_MODE_ROUE_OUVERTURE )
						{
							ModeObservation=ModeRO_Pointage;
						}
						if( fabs(PositionsModeOuvertureCLIMSO[ModeRO_Calibration]-PosAxeDegres[i]) < PRECISION_POS_MODE_ROUE_OUVERTURE )
						{
							ModeObservation=ModeRO_Calibration;
						}
						if( fabs(PositionsModeOuvertureCLIMSO[ModeRO_PLU]-PosAxeDegres[i]) < PRECISION_POS_MODE_ROUE_OUVERTURE )
						{
							ModeObservation=ModeRO_PLU;
						}
						if( fabs(PositionsModeOuvertureCLIMSO[ModeRO_Observation]-PosAxeDegres[i]) < PRECISION_POS_MODE_ROUE_OUVERTURE )
						{
							ModeObservation=ModeRO_Observation;
						}
					}
					else
					{
						ModeObservation=ModeRO_SansMode;
					}
					break;

				case AXE_ROUE_FILTREC2:

					PosAxeDegres[i]=-360.0*((double) PosAxeMicropasMoteur[i])/NB_MICROPAS_MOTEUR_PT_AXE_ROUE_FILTREC2;

					if( fabs(PosAxeDegres[i]-aPosAxeDegres[i]) < PRECISION_POS_MODE_ROUE_FILTREC2 )
					{
						// La position n'a pas changee assez entre deux rafraichissement, on considere que nous avons atteint un filtre car la roue tourne peut
						//
						if( fabs(PositionsFiltresC2CLIMSO[FiltreC2_10747]-PosAxeDegres[i]) < PRECISION_POS_MODE_ROUE_FILTREC2 )
						{
							FiltreC2=FiltreC2_10747;
						}
						if( fabs(PositionsFiltresC2CLIMSO[FiltreC2_10770]-PosAxeDegres[i]) < PRECISION_POS_MODE_ROUE_FILTREC2 )
						{
							FiltreC2=FiltreC2_10770;
						}
						if( fabs(PositionsFiltresC2CLIMSO[FiltreC2_10798]-PosAxeDegres[i]) < PRECISION_POS_MODE_ROUE_FILTREC2 )
						{
							FiltreC2=FiltreC2_10798;
						}
						if( fabs(PositionsFiltresC2CLIMSO[FiltreC2_10830]-PosAxeDegres[i]) < PRECISION_POS_MODE_ROUE_FILTREC2 )
						{
							FiltreC2=FiltreC2_10830;
						}
					}
					else
					{
						FiltreC2=FiltreC2_SansFiltre;
					}
					break;

				case AXE_PLATINE_X:
					PosAxeDegres[i]=PosAxeMicropasMoteur[i];	// PAS DE POSITION EN DEGRES POUR CET AXE ON EST EN PAS QUADRATURE CODEUR
					break;

				case AXE_PLATINE_Y:
					PosAxeDegres[i]=PosAxeMicropasMoteur[i];	// PAS DE POSITION EN DEGRES POUR CET AXE ON EST EN PAS QUADRATURE CODEUR
					break;
			}
		}

		if( aModeObservation != ModeObservation || aFiltreC2 != FiltreC2 ) MAJEtatBoutonsFP();

		// Mise a jour des widgets d'affichage de la position en points codeur en quadrature
		//
		LCDAxeCodeur[AXE_ROUE_OUVERTURE]->display(event->Valeur(AXE_ROUE_OUVERTURE));
		LCDAxeCodeur[AXE_ROUE_FILTREC2]->display(event->Valeur(AXE_ROUE_FILTREC2));
		LCDAxeCodeur[AXE_PLATINE_X]->display(event->Valeur(AXE_PLATINE_X)/RapportMicroPasCodeurPlatine); // XXX Ajouté en 2010
		LCDAxeCodeur[AXE_PLATINE_Y]->display(event->Valeur(AXE_PLATINE_Y)/RapportMicroPasCodeurPlatine); // XXX Ajouté en 2010

		// Mise a jour du graphique de la roue d'ouverture
		//
		if( aPosAxeDegres[AXE_ROUE_OUVERTURE] != PosAxeDegres[AXE_ROUE_OUVERTURE] ) GraphRoueOuverture->AnglePositionRoue(PosAxeDegres[AXE_ROUE_OUVERTURE]);

		// Mise a jour du graphique de la roue a filtre de C2
		//
		if( aPosAxeDegres[AXE_ROUE_FILTREC2] != PosAxeDegres[AXE_ROUE_FILTREC2] ) GraphRoueFiltresC2->AnglePositionRoue(PosAxeDegres[AXE_ROUE_FILTREC2]);

		return;
	}


	// Evenement pour la sortie d'un log
	//
	if( ce->type() == ID_CUSTOM_EVENT_SUPERVCLIMSO_LOG )
	{
		// Evenement de demande d'affichage d'un log
		//
		CEventSupervCLIMSO_Log *event=(CEventSupervCLIMSO_Log *) ce;	// Typage de l'evenement

		Log(event->Chaine());

		return;
	}


	// Evenement de l'arrivee d'une nouvelle pose image
	//
	if( ce->type() == ID_CUSTOM_EVENT_SUPERVCLIMSO_NOUVIMG )
	{
		// Evenement nouvelle image disponible
		//
		CEventSupervCLIMSO_NouvImage *event=(CEventSupervCLIMSO_NouvImage *) ce;	// Typage de l'evenement

		// Bloquage des donnees le temps de les traiter
		//
		PLDonneesCamerOA[event->Identifieur()]->MutexTrameImage.lock();

		// Sauvegarde de l'image en fichier FITS
		//
		QString NomCompletFichier;
		NomCompletFichier.reserve(TAILLE_MINI_CHAINE);
		QString log;
		log.reserve(TAILLE_MINI_CHAINE_LOG);

		if( SauverImageFITS(event->Identifieur(),NomCompletFichier) )
		{
			log="-> Sauvegarde de "+NomCompletFichier;

			Log(log);
		}
		else
		{
			log="*** ERREUR: lors de la sauvegarde de "+NomCompletFichier+" ***";

			Log(log);
		}

		// Si besoin, on previent le processus de liste d'acquisitions que l'image est recue (UNIQUEMENT LES INSTRUMENTS QUI PEUVENT PRODUIRE PLUSIEURS DESIGNATIONS D'IMAGES)
		//
		switch( event->Identifieur() )
		{
			case CAMEROA_C2:	PLAcqC2->ImageRecue();	break;
			case CAMEROA_L1:	PLAcqL1->ImageRecue();	break;
			case CAMEROA_L2:	PLAcqL2->ImageRecue();	break;
		}

		// On stocke son nom dans la liste des dernieres images acquises
		//
		if( ListeNomFichDerImg[event->Identifieur()].count() >= NB_MAXI_NF_DERNIERES_IMAGES )
		{
			// On a depasse le nombre maxi de noms de fichiers conserves alors on supprime le premier element de la liste avant d'ajouter le nouveau
			//
			ListeNomFichDerImg[event->Identifieur()].erase(ListeNomFichDerImg[event->Identifieur()].begin());
		}
		ListeNomFichDerImg[event->Identifieur()].append(NomCompletFichier);

		// Si on est en mode Observation et qu'il s'agit d'une image lumiere d'observation, l'image est diffusable sur BASS2000
		//
		if( (PLDonneesCamerOA[event->Identifieur()]->EnTeteI.type_image == TYPE_IMG_CAMEROA_POSEI) )
		{
			if( ModeObservation == ModeRO_Observation )
			{
				switch( event->Identifieur() )
				{
					case CAMEROA_C1:
						FichiersPubliC1[NbImgPubliablesC1 % NB_IMG_PUB_C1]=NomCompletFichier;
						NbImgPubliablesC1++;
						if( FenetrePubliC1->isVisible() ) ComposerListePubliablesC1();
						break;

					case CAMEROA_C2:
						FichiersPubliC2[NbImgPubliablesC2 % NB_IMG_PUB_C2]=NomCompletFichier;
						NbImgPubliablesC2++;
						if( FenetrePubliC2->isVisible() ) ComposerListePubliablesC2();
						break;

					case CAMEROA_L1:
						FichiersPubliL1[NbImgPubliablesL1 % NB_IMG_PUB_L1]=NomCompletFichier;
						NbImgPubliablesL1++;
						if( FenetrePubliL1->isVisible() ) ComposerListePubliablesL1();
						break;

					case CAMEROA_L2:
						FichiersPubliL2[NbImgPubliablesL2 % NB_IMG_PUB_L2]=NomCompletFichier;
						NbImgPubliablesL2++;
						if( FenetrePubliL2->isVisible() ) ComposerListePubliablesL2();
						break;
				}
			}

			if( ModeObservation == ModeRO_Pointage )
			{
				switch( event->Identifieur() )
				{
					case CAMEROA_L1:
						FichiersPubliL1[NbImgPubliablesL1 % NB_IMG_PUB_L1]=NomCompletFichier;
						NbImgPubliablesL1++;
						if( FenetrePubliL1->isVisible() ) ComposerListePubliablesL1();
						break;

					case CAMEROA_L2:
						FichiersPubliL2[NbImgPubliablesL2 % NB_IMG_PUB_L2]=NomCompletFichier;
						NbImgPubliablesL2++;
						if( FenetrePubliL2->isVisible() ) ComposerListePubliablesL2();
						break;
				}
			}
		}

		// On stocke la date et l'heure de la derniere acquisition
		//
		DateHeureDerImg[event->Identifieur()]=PLDonneesCamerOA[event->Identifieur()]->EnTeteI.debut;

		PLDonneesCamerOA[event->Identifieur()]->MutexTrameImage.unlock();

		// Selon l'axe et le type d'acquisition unitaire ou par liste
		//
		switch( event->Identifieur() )
		{
			case CAMEROA_C1:
				// Si une liste d'acquisition n'est pas en cours et donc qu'il s'agit d'une pose unitaire (ou la derniere de la liste d'acquisition)
				//
				if( !PLAcqC1->EnAcquisitions() )
				{
					// Il n'y a plus de pose unitaire en cours, elle est traitee
					//
					PoseEnCours[event->Identifieur()]=false;
				}
				break;

			case CAMEROA_C2:
				// Si une liste d'acquisition n'est pas en cours et donc qu'il s'agit d'une pose unitaire (ou la derniere de la liste d'acquisition)
				//
				if( !PLAcqC2->EnAcquisitions() )
				{
					// Il n'y a plus de pose unitaire en cours, elle est traitee
					//
					PoseEnCours[event->Identifieur()]=false;
				}
				break;

			case CAMEROA_L1:
				// Si une liste d'acquisition n'est pas en cours et donc qu'il s'agit d'une pose unitaire (ou la derniere de la liste d'acquisition)
				//
				if( !PLAcqL1->EnAcquisitions() )
				{
					// Il n'y a plus de pose unitaire en cours, elle est traitee
					//
					PoseEnCours[event->Identifieur()]=false;
				}
				break;

			case CAMEROA_L2:
				// Si une liste d'acquisition n'est pas en cours et donc qu'il s'agit d'une pose unitaire (ou la derniere de la liste d'acquisition)
				//
				if( !PLAcqL2->EnAcquisitions() )
				{
					// Il n'y a plus de pose unitaire en cours, elle est traitee
					//
					PoseEnCours[event->Identifieur()]=false;
				}
				break;

			default:
				Log("*** ERREUR: de numéro d'instrument dans le code de traitement de la fin d'une pose ***");
				break;
		}

		// Si le TerminOA correpondant est connecte alors on peut lui envoyer la nouvelle image
		//
		if( PLCommandeTerminOA[event->Identifieur()]->Client->Connecte() && PLDonneesTerminOA[event->Identifieur()]->Client->Connecte() )
		{
			// Si les consignes du TerminOA n'ont jamais ete envoyees
			//
			if( !ConsignesTerminOAInitialisees[event->Identifieur()] )
			{
				EnvoyerCommandeIntTerminOA(event->Identifieur(),TERMINOA_CMD_CSB,SpinBoxCSB[event->Identifieur()]->value());
				EnvoyerCommandeIntTerminOA(event->Identifieur(),TERMINOA_CMD_CSH,SpinBoxCSH[event->Identifieur()]->value());
				EnvoyerCommandeIntTerminOA(event->Identifieur(),TERMINOA_CMD_CPUILUT,SpinBoxCPuiLUT[event->Identifieur()]->value());

				ConsignesTerminOAInitialisees[event->Identifieur()]=true;
			}

			char ChaineMagique[]=CH_MAG_EDTITERMINOA;	// Chaine magique du debut de trame image

			// Generation de l'identificateur aleatoire de l'image courante pour le TerminOA
			//
			// TAILLE_IDENTITE_FICHIER est une constante heritee de pointscomm.h
			//
			QString ChaineIdImageCourante;
			ChaineIdImageCourante.reserve(TAILLE_MINI_CHAINE);
			ChaineIdImageCourante=GenererChaineAleatoire(TAILLE_IDENTITE_FICHIER);

			//
			// Emission de l'image courante vers le TerminOA
			//
			// ATTENTION: L'UTILISATION DU MUTEX EST OBLIGATOIRE POUR GARANTIR L'ATOMICITE DE LA TRAME SUR LA SOCKET CAR PLUSIEURS PROCESSUS L'UTILISE !
			//

			// On commence par envoyer la trame magique d'empreinte de debut de trame image sur la socket du TerminOA
			//
			// On envoie aussi le zero de fin de chaine
			//
			PLDonneesTerminOA[event->Identifieur()]->MutexEmission.lock();

			if( PLDonneesTerminOA[event->Identifieur()]->Client->EnvoyerDonneesSocket(ChaineMagique,TAILLE_CH_MAG_EDTITERMINOA) == TAILLE_CH_MAG_EDTITERMINOA )
			{
				// On peut envoyer l'image
				//
				if( PLDonneesTerminOA[event->Identifieur()]->Client->EnvoyerFichierSocket(NomCompletFichier.ascii(),ChaineIdImageCourante.ascii()) <= 0 )
				{
					Log("*** ERREUR: lors du transfert de "+NomCompletFichier+" vers TerminOA["+InstrumentCLIMSO[event->Identifieur()]+"] ***");
				}
			}
			else
			{
				Log("*** ERREUR: lors de l'emission de la trame empreinte de debut d'image vers TerminOA["+InstrumentCLIMSO[event->Identifieur()]+"] ***");
			}

			PLDonneesTerminOA[event->Identifieur()]->MutexEmission.unlock();
		}

		// Faire croire a un changement pour redessiner les boutons
		//
		switch( event->Identifieur() )
		{
			case CAMEROA_C1: aC1Actif=-1; break;
			case CAMEROA_C2: aC2Actif=-1; break;
			case CAMEROA_L1: aL1Actif=-1; break;
			case CAMEROA_L2: aL2Actif=-1; break;
		}
		aModeObservation=ModeRO_NonInitialise;
		aFiltreC2=FiltreC2_NonInitialise;

		MAJEtatBoutonsFP();

		update();

		return;
	}


	// Evenement de demande de rotation de la roue a filtre de C2 vers un filtre
	//
	if( ce->type() == ID_CUSTOM_EVENT_SUPERVCLIMSO_ROTVFILTREC2 )
	{
		CEventSupervCLIMSO_RotationVFiltreC2 *event=(CEventSupervCLIMSO_RotationVFiltreC2 *) ce;	// Typage de l'evenement

		// On demande la rotation de la roue
		//
		DemandeRotationRoueFiltresC2(event->Filtre());

		return;
	}


	// Evenement de notification de la fin d'une liste d'acquisitions
	//
	if( ce->type() == ID_CUSTOM_EVENT_SUPERVCLIMSO_FINLISTEACQ )
	{
		CEventSupervCLIMSO_FinListeAcquisitions *event=(CEventSupervCLIMSO_FinListeAcquisitions *) ce;	// Typage de l'evenement

		// Nous sommes arrives a la fin d'une liste d'acquisitions et donc il n'y a plus de pose en cours sur cet instrument
		//
		PoseEnCours[event->Identifieur()]=false;

		MAJEtatBoutonsFP();

		update();

		return;
	}


	// Evenement de l'arrivee d'une nouvelle image sur un TerminOA
	//
	if( ce->type() == ID_CUSTOM_EVENT_SUPERVCLIMSO_IMGRECUETERMINOA )
	{
		CEventSupervCLIMSO_ImgRecueTerminOA *event=(CEventSupervCLIMSO_ImgRecueTerminOA *) ce;	// Typage de l'evenement

		// L'image est correctement arrivee on peut maintenant declencher son affichage sur le TerminOA
		//
		QString Chaine;
		Chaine.reserve(TAILLE_MINI_CHAINE_CMD);

		Chaine=CmdClientTerminOA[TERMINOA_CMD_AFFICHER]+event->IdImage();
		Chaine.append("\n");

		MutexEnvChaineBIO_TerminOA[event->Identifieur()].lock();

		if( PLCommandeTerminOA[event->Identifieur()]->Client->EnvoyerChaineBIO(Chaine) <= 0 )
		{
			// Erreur lors de l'emission de la commande
			//
			Log("*** ERREUR: Impossible d'envoyer la commande d'affichage de l'image sur le TerminOA["+InstrumentCLIMSO[event->Identifieur()]+"] ***");
		}

		MutexEnvChaineBIO_TerminOA[event->Identifieur()].unlock();

		return;
	}


	// Evenement pour la reception de la temperature CCD d'un CamerOA
	//
	if( ce->type() == ID_CUSTOM_EVENT_SUPERVCLIMSO_TEMPCCD )
	{
		// Evenement de reception de la temperature CCD d'un CamerOA
		//
		CEventSupervCLIMSO_TempCCD *event=(CEventSupervCLIMSO_TempCCD *) ce;	// Typage de l'evenement

		switch( event->Identifieur() )
		{
			case CAMEROA_C1:
				LCDTempCamerOAC1->display(event->Temperature());
				break;

			case CAMEROA_C2:
				LCDTempCamerOAC2->display(event->Temperature());
				break;

			case CAMEROA_L1:
				LCDTempCamerOAL1->display(event->Temperature());
				break;

			case CAMEROA_L2:
				LCDTempCamerOAL2->display(event->Temperature());
				break;
		}

		// Sauvegarde de la temperature des CCD
		//
		TemperatureCamerOA[event->Identifieur()]=event->Temperature();

		return;
	}


	// Evenement pour la reception de la puissance peltier d'un CamerOA
	//
	if( ce->type() == ID_CUSTOM_EVENT_SUPERVCLIMSO_PUIPELTIER )
	{
		// Evenement de reception de la puissance peltier d'un CamerOA
		//
		CEventSupervCLIMSO_PuiPeltier *event=(CEventSupervCLIMSO_PuiPeltier *) ce;	// Typage de l'evenement

		switch( event->Identifieur() )
		{
			case CAMEROA_C1:
				LCDPuiCamerOAC1->display(event->Puissance());
				break;

			case CAMEROA_C2:
				LCDPuiCamerOAC2->display(event->Puissance());
				break;

			case CAMEROA_L1:
				LCDPuiCamerOAL1->display(event->Puissance());
				break;

			case CAMEROA_L2:
				LCDPuiCamerOAL2->display(event->Puissance());
				break;
		}

		return;
	}


	// Evenement pour la reception des temperatures sur le Web-IO Thermometer
	//
	if( ce->type() == ID_CUSTOM_EVENT_SUPERVCLIMSO_NOUVTEMPERATURES )
	{
		QString ChaineSauvee;
		ChaineSauvee.reserve(TAILLE_MINI_CHAINE);
		ChaineSauvee=PLTemperatures->t_UT.toString(Qt::ISODate);

		for( int i=0; i < NB_SONDES_TEMPERATURE; i++ )
		{
			if( PLTemperatures->T[i] == TEMPERATURE_NON_CONNUE )
			{
				LCDTemperatures[i]->display("-");

				ChaineSauvee+="\t-";

				AlerteFenetreTemperatures[i]=false;
			}
			else
			{
				// Affichage de la temperature dans son LCD
				//
				LCDTemperatures[i]->display(PLTemperatures->T[i]);
				
				// Sauvegarde dans le fichier journalier
				//
				ChaineSauvee+=QString("\t%1").arg(PLTemperatures->T[i],0,'f',1);

				// Selon la sonde et les consignes d'alerte
				//
				switch( i )
				{
					case TEMP_SONDE_CAISSON_INFO:
						// Si on doit alerter au niveau de la temperature du caisson informatique
						//
						if( PLTemperatures->T[i] < CaissonInfoLinf || PLTemperatures->T[i] > CaissonInfoLsup )
						{
							Log("*** ALERTE: La température du caisson informatique n'est pas dans l'intervalle sécuritaire ***");
							LabelTemperatures[i]->setPaletteBackgroundColor(COULEUR_LIGNE_TEMP_SONDE_NONOK);
							AlerteFenetreTemperatures[i]=true;
						}
						else
						{
							LabelTemperatures[i]->setPaletteBackgroundColor(COULEUR_LIGNE_TEMP_SONDE_OK);
							AlerteFenetreTemperatures[i]=false;
						}
						break;

					case TEMP_SONDE_FILTRE_C1:
						// Si on doit alerter au niveau de la temperature du filtre de C1
						//
						if( PLTemperatures->T[i] < FiltreC1Linf || PLTemperatures->T[i] > FiltreC1Lsup )
						{
							Log("*** ALERTE: La température du filtre de C1 n'est pas dans l'intervalle de bon fonctionnement ***");
							LabelTemperatures[i]->setPaletteBackgroundColor(COULEUR_LIGNE_TEMP_SONDE_NONOK);
							AlerteFenetreTemperatures[i]=true;
						}
						else
						{
							LabelTemperatures[i]->setPaletteBackgroundColor(COULEUR_LIGNE_TEMP_SONDE_OK);
							AlerteFenetreTemperatures[i]=false;
						}
						break;

					case TEMP_SONDE_FILTRES_C2:
						// Si on doit alerter au niveau de la temperature des filtres de C2
						//
						if( PLTemperatures->T[i] < FiltresC2Linf || PLTemperatures->T[i] > FiltresC2Lsup )
						{
							Log("*** ALERTE: La température des filtres de C2 n'est pas dans l'intervalle de bon fonctionnement ***");
							LabelTemperatures[i]->setPaletteBackgroundColor(COULEUR_LIGNE_TEMP_SONDE_NONOK);
							AlerteFenetreTemperatures[i]=true;
						}
						else
						{
							LabelTemperatures[i]->setPaletteBackgroundColor(COULEUR_LIGNE_TEMP_SONDE_OK);
							AlerteFenetreTemperatures[i]=false;
						}
						break;
				}
			}
		}

		ChaineSauvee+="\n";

		FluxFichierTemperatures << ChaineSauvee;

		return;
	}


	// Evenement d'un index d'axe trouve
	//
	if( ce->type() == ID_CUSTOM_EVENT_SUPERVCLIMSO_INDEXAXETROUVE )
	{
		// Evenement d'un index d'axe trouve
		//
		CEventSupervCLIMSO_IndexAxeTrouve *event=(CEventSupervCLIMSO_IndexAxeTrouve *) ce;			// Typage de l'evenement

		switch( event->Numero() )
		{
			case AXE_ROUE_OUVERTURE:
			case AXE_ROUE_FILTREC2:
				Log("-> Index du codeur de l'axe de "+Axe[event->Numero()]+" trouvé.");
				// XXX On peut demander ici de mettre la roue à la bonne position !
				break;

			case AXE_PLATINE_X:
			case AXE_PLATINE_Y:
				Log("-> Front du switch de la position home de l'axe de "+Axe[event->Numero()]+" trouvé.");
				break;
		}

		AxeIndexTrouve[event->Numero()]=true;

		return;
	}


	// Evenement d'un index d'axe NON trouve
	//
	if( ce->type() == ID_CUSTOM_EVENT_SUPERVCLIMSO_INDEXAXENONTROUVE )
	{
		// Evenement d'un index d'axe NON trouve
		//
		CEventSupervCLIMSO_IndexAxeNonTrouve *event=(CEventSupervCLIMSO_IndexAxeNonTrouve *) ce;	// Typage de l'evenement

		Log(QString("-> *** ERREUR: Index de l'axe de "+Axe[event->Numero()]+" NON trouvé ***"));

		return;
	}
}


// Demande de rotation de la roue d'ouverture jusqu'a la position d'un mode particulier
//
// CE:	On passe le mode d'observation
//
// CS:	-
//
void SupervCLIMSO::DemandeRotationRoueOuverture(ModeRoueOuvertureCLIMSO position)
{
	double pos;				// Contiendra la position a atteindre en micropas moteurs dans le repere de l'AXE (tient compte de l'offset) et pas le repere de la ROUE
	double fr;				// Partie fractionnaire
	QString ChaineCmd;						// Chaine avec taille minimale pour la composition de commandes afin d'eviter un bogue QString et la rapidite
	ChaineCmd.reserve(TAILLE_MINI_CHAINE_CMD);

	// Position en degres dans le repere REEL de la roue selon nos conventions
	//
	switch( position )
	{
		case ModeRO_Pointage:
		case ModeRO_Calibration:
		case ModeRO_PLU:
		case ModeRO_Observation:
			pos=PositionsModeOuvertureCLIMSO[position];
			break;

		default:
			pos=PositionsModeOuvertureCLIMSO[ModeRO_Pointage];
			break;
	}

	// On passe dans le repere de l'axe en micropas moteur
	//
	pos*=NB_MICROPAS_MOTEUR_PT_AXE_ROUE_OUVERTURE;
	pos/=360.0;
	pos+=OFFSET_MICROPAS_MOTEUR_POS_ZERO_ROUE_OUVERTURE;

	fr=modf(pos,&pos);
	if( fr > 0.5 ) pos+=1.0;

	// On peut envoyer la commande au RobOA
	//
	ChaineCmd=CmdClientRobOA[ROBOA_CMD_MVTAXEPASMOT]+QString("1 %1\n").arg((int) pos);

	MutexEnvChaineBIO_RobOA.lock();

	if( PLCommandeRobOA->Client->EnvoyerChaineBIO(ChaineCmd) <= 0 )
	{
		// Erreur lors de l'emission
		//
		Log("*** ERREUR: Impossible d'envoyer la commande de demande de mouvement sur l'axe de la roue d'ouverture ***");
	}

	MutexEnvChaineBIO_RobOA.unlock();

	// La position actuelle n'est plus connue
	//
	ModeObservation=ModeRO_SansMode;
}


// Demande de rotation de la roue a filtre de C2 jusqu'a la position d'un filtre
//
// CE:	On passe le filtre ;
//
// CS:	-
//
void SupervCLIMSO::DemandeRotationRoueFiltresC2(FiltresC2CLIMSO filtre)
{
	double pos;				// Contiendra la position a atteindre en micropas moteurs dans le repere de l'AXE (tient compte de l'offset) et pas le repere de la ROUE A FILTRES
	double fr;				// Partie fractionnaire
	QString ChaineCmd;						// Chaine avec taille minimale pour la composition de commandes afin d'eviter un bogue QString et la rapidite
	ChaineCmd.reserve(TAILLE_MINI_CHAINE_CMD);

	// Position en degres dans le repere REEL de la roue a filtre selon nos conventions
	//
	switch( filtre )
	{
		case FiltreC2_10747:
		case FiltreC2_10770:
		case FiltreC2_10798:
		case FiltreC2_10830:
			pos=PositionsFiltresC2CLIMSO[filtre];
			break;

		default:
			pos=PositionsFiltresC2CLIMSO[FiltreC2_10830];
			break;
	}

	// On passe dans le repere de l'axe en micropas moteur
	//
	pos*=NB_MICROPAS_MOTEUR_PT_AXE_ROUE_FILTREC2;
	pos/=360.0;
	pos+=OFFSET_MICROPAS_MOTEUR_POS_ZERO_ROUE_FILTREC2;

	fr=modf(pos,&pos);
	if( fr > 0.5 ) pos+=1.0;

	// On peut envoyer la commande au RobOA
	//
	ChaineCmd=CmdClientRobOA[ROBOA_CMD_MVTAXEPASMOT]+QString("2 %1\n").arg((int) pos);

	MutexEnvChaineBIO_RobOA.lock();

	if( PLCommandeRobOA->Client->EnvoyerChaineBIO(ChaineCmd) <= 0 )
	{
		// Erreur lors de l'emission
		//
		Log("*** ERREUR: Impossible d'envoyer la commande de demande de mouvement sur l'axe de la roue à filtres de C2 ***");
	}

	MutexEnvChaineBIO_RobOA.unlock();

	// La position actuelle n'est plus connue
	//
	FiltreC2=FiltreC2_SansFiltre;
}


// Fonction retournant le filtre courant sur C2
//
// CE:	-
//
// CS:	La fonction retourne le filtre courant ;
//
FiltresC2CLIMSO SupervCLIMSO::FiltreC2Courant(void)
{
	return FiltreC2;
}


// Demande de mouvement de l'axe X de la platine de C2
//
// CE:	On passe la valeur de decalage en micropas moteur
//
void SupervCLIMSO::DemandeMouvementXPlatine(int valeur)
{
	QString ChaineCmd;						// Chaine avec taille minimale pour la composition de commandes afin d'eviter un bogue QString et la rapidite
	ChaineCmd.reserve(TAILLE_MINI_CHAINE_CMD);

	// On peut envoyer la commande au RobOA
	//
	ChaineCmd=CmdClientRobOA[ROBOA_CMD_MVTAXEPASMOT]+QString("3 %1\n").arg(valeur);

	MutexEnvChaineBIO_RobOA.lock();

	if( PLCommandeRobOA->Client->EnvoyerChaineBIO(ChaineCmd) <= 0 )
	{
		// Erreur lors de l'emission
		//
		Log("*** ERREUR: Impossible d'envoyer la commande de demande de mouvement sur l'axe X de la platine de C2 ***");
	}

	MutexEnvChaineBIO_RobOA.unlock();
}


// Demande de mouvement de l'axe Y de la platine de C2
//
// CE:	On passe la valeur de decalage en micropas moteur
//
void SupervCLIMSO::DemandeMouvementYPlatine(int valeur)
{
	QString ChaineCmd;						// Chaine avec taille minimale pour la composition de commandes afin d'eviter un bogue QString et la rapidite
	ChaineCmd.reserve(TAILLE_MINI_CHAINE_CMD);

	// On peut envoyer la commande au RobOA
	//
	ChaineCmd=CmdClientRobOA[ROBOA_CMD_MVTAXEPASMOT]+QString("4 %1\n").arg(valeur);

	MutexEnvChaineBIO_RobOA.lock();

	if( PLCommandeRobOA->Client->EnvoyerChaineBIO(ChaineCmd) <= 0 )
	{
		// Erreur lors de l'emission
		//
		Log("*** ERREUR: Impossible d'envoyer la commande de demande de mouvement sur l'axe Y de la platine de C2 ***");
	}

	MutexEnvChaineBIO_RobOA.unlock();
}


// Sauver une image FITS recue de l'instrument n
//
// CE:	On passe l'identifieur de l'instrument ;
//
//		On passe une reference sur un QString qui contiendra le nom de fichier complet du fichier ;
//
// CS:	La fonction est vraie si la sauvegarde s'est bien deroulee, fausse dans le cas contraire
//
int SupervCLIMSO::SauverImageFITS(int n,QString &ncf)
{
	int vint=0;					// Variable de travail
	int status=0;				// Pour obtenir le status des fonctions CFITSIO utilisees
	long naxis=2;				// Nombre d'axes dans l'image du fichier FITS
	long naxes[2];				// Nombre de pixels sur chaque axe de l'image du fichier FITS
	double vdouble=0;			// Variable de travail
	char ceFITS[FLEN_ERRMSG];	// Chaine d'erreur FITS
	fitsfile *Id;				// Identifieur du fichier avec CFITSIO
	QString NomFichier;			// Nom du fichier
	NomFichier.reserve(TAILLE_MINI_CHAINE);
	QString NomFichierComplet;	// Nom du fichier et chemin complet
	NomFichierComplet.reserve(TAILLE_MINI_CHAINE);
	QString Chaine;				// Chaine de composition
	Chaine.reserve(TAILLE_MINI_CHAINE);

	// Composition du nom du fichier
	//
	ncf=CheminStockageDonnees+"/";
	NomFichierComplet=CheminStockageDonnees+"/";
	NomFichier="imoa";
	switch( n )
	{
		case CAMEROA_C1:
			NomFichier+="_06563_c1";	break;
			break;

		case CAMEROA_C2:
			switch( FiltreC2 )
			{
				case FiltreC2_10747:	NomFichier+="_10747_c2";	break;
				case FiltreC2_10770:	NomFichier+="_10770_c2";	break;
				case FiltreC2_10798:	NomFichier+="_10798_c2";	break;
				case FiltreC2_10830:	NomFichier+="_10830_c2";	break;
				default:	break;
			}
			break;

		case CAMEROA_L1:
			NomFichier+="_06563_l1";	break;
			break;

		case CAMEROA_L2:
			NomFichier+="_03933_l2";	break;
			break;
	}

	NomFichier+=PLDonneesCamerOA[n]->EnTeteI.debut.toString("_yyyyMMdd_hhmmss00");

	switch( PLDonneesCamerOA[n]->EnTeteI.type_image )
	{
		case TYPE_IMG_CAMEROA_POSEI:
			if( ModeObservation == ModeRO_Pointage)
			{
				switch( n )
				{
					case CAMEROA_C1:
					case CAMEROA_C2:
						NomFichier+="_po.fts";
						break;

					case CAMEROA_L1:
					case CAMEROA_L2:
						NomFichier+="_b1.fts";
						break;
				}
			}
			if( ModeObservation == ModeRO_Calibration) NomFichier+="_ca.fts";
			if( ModeObservation == ModeRO_PLU ) NomFichier+="_pl.fts";
			if( ModeObservation == ModeRO_Observation ) NomFichier+="_b1.fts";
			if( ModeObservation == ModeRO_SansMode ) NomFichier+="_sm.fts";
			break;

		case TYPE_IMG_CAMEROA_POSEBIAS:
			NomFichier+="_bi.fts";
			break;

		case TYPE_IMG_CAMEROA_POSEDARK:
			NomFichier+="_da.fts";
			break;

		default:
			Log("*** ERREUR: SupervCLIMSO: SauverImageFITS(): Image de type non identifiable en provenance de l'instrument "+InstrumentCLIMSO[n]+" ***");
			return false;
	}
	ncf+=NomFichier;
	NomFichierComplet+=NomFichier;

	// Creation du fichier
	//
	if( fits_create_file(&Id,NomFichierComplet.ascii(),&status) )
	{
		fits_get_errstatus(status,ceFITS);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible de créer le fichier:"+NomFichierComplet+" ***");
		return false;
	}

	// Initialisation du tableau de la taille de l'image
	//
	naxes[0]=(long) PLDonneesCamerOA[n]->EnTeteI.tx;
	naxes[1]=(long) PLDonneesCamerOA[n]->EnTeteI.ty;

	// Creation d'une image dans le fichier FITS
	//
	if( fits_create_img(Id,USHORT_IMG,naxis,naxes,&status) )
	{
		fits_get_errstatus(status,ceFITS);
		fits_close_file(Id,&status);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible de créer une image dans le fichier:"+NomFichierComplet+" ***");
		return false;
	}

	if( fits_delete_key(Id,(char *) "COMMENT",&status) )
	{
		fits_get_errstatus(status,ceFITS);
		fits_close_file(Id,&status);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible de supprimer le mot clé COMMENT dans le fichier:"+NomFichierComplet+" ***");
		return false;
	}

	if( fits_delete_key(Id,(char *) "COMMENT",&status) )
	{
		fits_get_errstatus(status,ceFITS);
		fits_close_file(Id,&status);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible de supprimer le mot clé COMMENT dans le fichier:"+NomFichierComplet+" ***");
		return false;
	}

	if( fits_delete_key(Id,(char *) "EXTEND",&status) )
	{
		fits_get_errstatus(status,ceFITS);
		fits_close_file(Id,&status);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible de supprimer le mot clé EXTEND dans le fichier:"+NomFichierComplet+" ***");
		return false;
	}

	// Ajout de la date de creation dans l'entete
	//
	if( fits_write_date(Id,&status) )
	{
		fits_get_errstatus(status,ceFITS);
		fits_close_file(Id,&status);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé de la date de création du fichier dans le fichier:"+NomFichierComplet+" ***");
		return false;
	}

	// Ajout du nom du fichier
	//
	if( fits_write_key(Id,TSTRING,(char *) "FILENAME",(char *) NomFichier.ascii(),(char *) "Original filename",&status) )
	{
		fits_get_errstatus(status,ceFITS);
		fits_close_file(Id,&status);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé du nom du fichier dans le fichier:"+NomFichierComplet+" ***");
		return false;
	}

	// Ajout du nom de l'institut
	//
	if( fits_write_key(Id,TSTRING,(char *) "INSTITUT",(char *) "OMP, OA, Pic-du-Midi",(char *) "Name of the institut",&status) )
	{
		fits_get_errstatus(status,ceFITS);
		fits_close_file(Id,&status);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé du nom de l'Institut dans le fichier:"+NomFichierComplet+" ***");
		return false;
	}

	// Ajout du nom de l'instrument
	//
	switch( n )
	{
		case CAMEROA_C1:
			if( fits_write_key(Id,TSTRING,(char *) "INSTRUME",(char *) "CLIMSO C1",(char *) "Name of the instrument",&status) )
			{
				fits_get_errstatus(status,ceFITS);
				fits_close_file(Id,&status);
				Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé du nom de l'instrument dans le fichier:"+NomFichierComplet+" ***");
				return false;
			}
			break;

		case CAMEROA_C2:
			if( fits_write_key(Id,TSTRING,(char *) "INSTRUME",(char *) "CLIMSO C2",(char *) "Name of the instrument",&status) )
			{
				fits_get_errstatus(status,ceFITS);
				fits_close_file(Id,&status);
				Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé du nom de l'instrument dans le fichier:"+NomFichierComplet+" ***");
				return false;
			}
			break;

		case CAMEROA_L1:
			if( fits_write_key(Id,TSTRING,(char *) "INSTRUME",(char *) "CLIMSO L1",(char *) "Name of the instrument",&status) )
			{
				fits_get_errstatus(status,ceFITS);
				fits_close_file(Id,&status);
				Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé du nom de l'instrument dans le fichier:"+NomFichierComplet+" ***");
				return false;
			}
			break;

		case CAMEROA_L2:
			if( fits_write_key(Id,TSTRING,(char *) "INSTRUME",(char *) "CLIMSO L2",(char *) "Name of the instrument",&status) )
			{
				fits_get_errstatus(status,ceFITS);
				fits_close_file(Id,&status);
				Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé du nom de l'instrument dans le fichier:"+NomFichierComplet+" ***");
				return false;
			}
			break;
	}

	// Ajout de la camera
	//
	if( fits_write_key(Id,TSTRING,(char *) "CAMERA",(char *) "U4000",(char *) "Name of the CCD camera",&status) )
	{
		fits_get_errstatus(status,ceFITS);
		fits_close_file(Id,&status);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé du nom de la caméra dans le fichier:"+NomFichierComplet+" ***");
		return false;
	}

	// Ajout du nom de l'observateur
	//
	if( fits_write_key(Id,TSTRING,(char *) "OBSERVER",(char *) "OA-FIDUCIAL",(char *) "Name of instrument operator",&status) )
	{
		fits_get_errstatus(status,ceFITS);
		fits_close_file(Id,&status);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé du nom de l'opérateur dans le fichier:"+NomFichierComplet+" ***");
		return false;
	}

	// Ajout de la date de debut d'observation : DATE pour la librairie CCFITS, DATE-OBS et DATE_OBS pour la conformite BASS2000
	//
	Chaine=PLDonneesCamerOA[n]->EnTeteI.debut.toString("yyyy-MM-ddThh:mm:ss.zzz");

	if( fits_write_key(Id,TSTRING,(char *) "DATE",(char *) Chaine.ascii(),(char *) "Date start of the observation UT",&status) )
	{
		fits_get_errstatus(status,ceFITS);
		fits_close_file(Id,&status);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé de la date de début d'observation DATE dans le fichier:"+NomFichierComplet+" ***");
		return false;
	}

	if( fits_write_key(Id,TSTRING,(char *) "DATE-OBS",(char *) Chaine.ascii(),(char *) "Date start of the observation UT",&status) )
	{
		fits_get_errstatus(status,ceFITS);
		fits_close_file(Id,&status);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé de la date de début d'observation DATE-OBS dans le fichier:"+NomFichierComplet+" ***");
		return false;
	}

	if( fits_write_key(Id,TSTRING,(char *) "DATE_OBS",(char *) Chaine.ascii(),(char *) "Date start of the observation UT",&status) )
	{
		fits_get_errstatus(status,ceFITS);
		fits_close_file(Id,&status);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé de la date de début d'observation DATE_OBS dans le fichier:"+NomFichierComplet+" ***");
		return false;
	}

	// Ajout de la date de la fin d'observation
	//
	Chaine=PLDonneesCamerOA[n]->EnTeteI.fin.toString("yyyy-MM-ddThh:mm:ss.zzz");

	if( fits_write_key(Id,TSTRING,(char *) "DATE_END",(char *) Chaine.ascii(),(char *) "Date end of the observation UT",&status) )
	{
		fits_get_errstatus(status,ceFITS);
		fits_close_file(Id,&status);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé de la date de fin d'observation dans le fichier:"+NomFichierComplet+" ***");
		return false;
	}

	// Ajout du temps de pose
	//
	double tp=(double) PLDonneesCamerOA[n]->EnTeteI.duree;
	tp/=10000.0;

	if( fits_write_key(Id,TDOUBLE,(char *) "EXPTIME",&tp,(char *) "[s] Exposure time",&status) )
	{
		fits_get_errstatus(status,ceFITS);
		fits_close_file(Id,&status);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé de la durée de la pose dans le fichier:"+NomFichierComplet+" ***");
		return false;
	}

	// Ajout de la temperature du CCD
	//
	tp=TemperatureCamerOA[n];

	if( tp != TEMPERATURE_NON_CONNUE )
	{
		if( fits_write_key(Id,TDOUBLE,(char *) "CAMTEM",&tp,(char *) "[degC] CCD chip temperature",&status) )
		{
			fits_get_errstatus(status,ceFITS);
			fits_close_file(Id,&status);
			Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé de la température de la matrice CCD dans le fichier:"+NomFichierComplet+" ***");
			return false;
		}
	}

	// Ajout de la temperature dans la coupole au moment de la pose
	//
	tp=PLTemperatures->T[TEMP_SONDE_AMBIANTE_COUPOLE];

	if( tp != TEMPERATURE_NON_CONNUE )
	{
		if( fits_write_key(Id,TDOUBLE,(char *) "DMETEM",&tp,(char *) "[degC] Temperature inside the dome",&status) )
		{
			fits_get_errstatus(status,ceFITS);
			fits_close_file(Id,&status);
			Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé de la température ambiante de la coupole dans le fichier:"+NomFichierComplet+" ***");
			return false;
		}
	}

	// Ajout de la longueur d'onde d'observation si la pose voit la lumiere
	//
	if( !(PLDonneesCamerOA[n]->EnTeteI.type_image == TYPE_IMG_CAMEROA_POSEBIAS || PLDonneesCamerOA[n]->EnTeteI.type_image == TYPE_IMG_CAMEROA_POSEDARK) )
	{
		// Ajout de la longueur d'onde d'observation
		//
		switch( n )
		{
			case CAMEROA_C1:
				vdouble=6562.82;	// Coronographe h-alpha
				break;

			case CAMEROA_C2:		// Coronographe infrarouge
				vdouble=0.0;
				switch( FiltreC2 )
				{
					case FiltreC2_10747:	vdouble=10747.0;	break;
					case FiltreC2_10770:	vdouble=10770.0;	break;
					case FiltreC2_10798:	vdouble=10798.0;	break;
					case FiltreC2_10830:	vdouble=10830.0;	break;
					default:				vdouble=0.0;		break;
				}
				break;

			case CAMEROA_L1:
				vdouble=6562.82;	// Lunette h-alpha
				break;

			case CAMEROA_L2:
				vdouble=3933.682;	// Lunette CaK
				break;
		}

		if( fits_write_key(Id,TDOUBLE,(char *) "WAVELNTH",&vdouble,(char *) "[Angstrom] Wavelength observation",&status) )
		{
			fits_get_errstatus(status,ceFITS);
			fits_close_file(Id,&status);
			Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé de la longueur d'onde dans le fichier:"+NomFichierComplet+" ***");
			return false;
		}

		// Ajout de l'unite de la longueur d'onde
		//
		vint=-10;
		if( fits_write_key(Id,TINT,(char *) "WAVEUNIT",&vint,(char *) "[power] Power unit of WAVELNTH in meter",&status) )
		{
			fits_get_errstatus(status,ceFITS);
			fits_close_file(Id,&status);
			Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé de l'unité de la longueur d'onde dans le fichier:"+NomFichierComplet+" ***");
			return false;
		}
	}

	// Ajout du niveau de traitement
	//
	vint=0;

	if( fits_write_key(Id,TINT,(char *) "LEVEL",&vint,(char *) "Processing level",&status) )
	{
		fits_get_errstatus(status,ceFITS);
		fits_close_file(Id,&status);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé du niveau de traitement dans le fichier:"+NomFichierComplet+" ***");
		return false;
	}

	// Si il s'agit d'une pose d'observation
	//
	if( (PLDonneesCamerOA[n]->EnTeteI.type_image == TYPE_IMG_CAMEROA_POSEI) && (ModeObservation == ModeRO_Observation || ModeObservation == ModeRO_Pointage) )
	{
		// L'objet observe
		//
		switch( n )
		{
			case CAMEROA_C1:
			case CAMEROA_C2:
				if( ModeObservation == ModeRO_Observation )
				{
					if( fits_write_key(Id,TSTRING,(char *) "OBJECT",(char *) "COR",(char *) "Sun corona observation",&status) )
					{
						fits_get_errstatus(status,ceFITS);
						fits_close_file(Id,&status);
						Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé de l'objet observé dans le fichier:"+NomFichierComplet+" ***");
						return false;
					}
				}
				break;

			case CAMEROA_L1:
			case CAMEROA_L2:
				if( fits_write_key(Id,TSTRING,(char *) "OBJECT",(char *) "SUN",(char *) "Sun disk observation",&status) )
				{
					fits_get_errstatus(status,ceFITS);
					fits_close_file(Id,&status);
					Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé de l'objet observé dans le fichier:"+NomFichierComplet+" ***");
					return false;
				}
				break;
		}

		double P,L,B;
		CalcAstro.CoordonneesHeliographiquesCentreDisqueSolaire(JJ(PLDonneesCamerOA[n]->EnTeteI.debut),&P,&L,&B);

		// Ajout de l'angle au pole de l'extremite du pole nord solaire
		//
		if( fits_write_key(Id,TDOUBLE,(char *) "SOLAR_P0",&P,(char *) "[rad] P.A. of the Sun's rotation axis",&status) )
		{
			fits_get_errstatus(status,ceFITS);
			fits_close_file(Id,&status);
			Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé de l'angle au pole de l'extremite du pole nord solaire dans le fichier:"+NomFichierComplet+" ***");
			return false;
		}

		// Ajout de la longitude heliographique de Carrington du centre du disque solaire
		//
		if( fits_write_key(Id,TDOUBLE,(char *) "LONGCARR",&L,(char *) "[rad] He. Longitude central point solar disk",&status) )
		{
			fits_get_errstatus(status,ceFITS);
			fits_close_file(Id,&status);
			Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé de la longitude héliographique du centre du disque solaire dans le fichier:"+NomFichierComplet+" ***");
			return false;
		}

		// Ajout de la latitude heliographique du centre du disque solaire
		//
		if( fits_write_key(Id,TDOUBLE,(char *) "SOLAR_B0",&B,(char *) "[rad] He. Latitude central point solar disk",&status) )
		{
			fits_get_errstatus(status,ceFITS);
			fits_close_file(Id,&status);
			Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé de la latitude héliographique du centre du disque solaire dans le fichier:"+NomFichierComplet+" ***");
			return false;
		}
	}

	// Le parametre physique
	//
	if( fits_write_key(Id,TSTRING,(char *) "PHYSPARA",(char *) "INTENSITY",(char *) "[ADU] Analog to Digital Unit",&status) )
	{
		fits_get_errstatus(status,ceFITS);
		fits_close_file(Id,&status);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé du paramètre physique dans le fichier:"+NomFichierComplet+" ***");
		return false;
	}

	// Le type de procedure de calcul
	//
	if( fits_write_key(Id,TSTRING,(char *) "PROCTYPE",(char *) "RAW",(char *) "Raw CCD data",&status) )
	{
		fits_get_errstatus(status,ceFITS);
		fits_close_file(Id,&status);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé du type de procédure de calcul dans le fichier:"+NomFichierComplet+" ***");
		return false;
	}

	// Ajout des contacts
	//
	//mail contact retouche
	if( fits_write_key(Id,TSTRING,(char *) "CONTACT",(char *) "laurent.lastname@irap.omp.eu",(char *) "rebuild e-mail's contact : L.Koechlin",&status) )
	{
		fits_get_errstatus(status,ceFITS);
		fits_close_file(Id,&status);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé du contact dans le fichier:"+NomFichierComplet+" ***");
		return false;
	}
	//mail contact1 retouche
	if( fits_write_key(Id,TSTRING,(char *) "CONTACT1",(char *) "m-lastname@wanadoo.fr",(char *) "rebuild e-mail's contact : M.Audejean",&status) )
	{
		fits_get_errstatus(status,ceFITS);
		fits_close_file(Id,&status);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé du contact dans le fichier:"+NomFichierComplet+" ***");
		return false;
	}
	//mail contact2 retouche
	if( fits_write_key(Id,TSTRING,(char *) "CONTACT2",(char *) "Jacques-clair.lastname@wanadoo.fr",(char *) "rebuild e-mail's contact : J.-C. Noens END ",&status) )
	{
		fits_get_errstatus(status,ceFITS);
		fits_close_file(Id,&status);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible d'ajouter le mot clé du contact dans le fichier:"+NomFichierComplet+" ***");
		return false;
	}

/*	ATTENTION: Une image FITS en unsigned short est codee BITPIX = 16, BSCALE = 1, BZERO = 32768 par CFITSIO sinon erreur CFITSIO car depassement de valeur

	// Mise a jour du mot cle BZERO
	//
	vint=0;

	if( fits_update_key(Id,TINT,(char *) "BZERO",&vint,(char *) "Offset data range",&status) )
	{
		fits_get_errstatus(status,ceFITS);
		fits_close_file(Id,&status);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible de mettre à jour le mot clé BZERO dans le fichier:"+NomFichierComplet+" ***");
		return false;
	}
*/

	// Sauvegarde de la zone donnee de l'image en unsigned short USHORT_IMG => BITPIX = 16, BSCALE = 1, BZERO = 32768 et pas BZERO=0 en CFITSIO FITS
	//
	if( fits_write_img(Id,USHORT_IMG,1,PLDonneesCamerOA[n]->EnTeteI.tx*PLDonneesCamerOA[n]->EnTeteI.ty,&PLDonneesCamerOA[n]->TrameI[0],&status) )
	{
		fits_get_errstatus(status,ceFITS);
		fits_close_file(Id,&status);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible de sauver les données de l'image dans le fichier:"+NomFichierComplet+" ***");
		return false;
	}


	// Fermeture correcte du fichier FITS
	//
	if( fits_close_file(Id,&status) )
	{
		fits_get_errstatus(status,ceFITS);
		Log("*** ERREUR FITS:"+QString(ceFITS)+": SupervCLIMSO: SauverImageFITS(): Impossible de fermer correctement le fichier:"+NomFichierComplet+" ***");
		return false;
	}

	return true;
}


// Fonction de calcul du Jour Julien en fonction d'un objet QDateTime
//
// CE:	On passe la date et l'heure dans un QDateTime ;
//
// CS:	La fonction retourne le jour julien de la date et l'heure ;
//
double SupervCLIMSO::JJ(QDateTime t)
{
	double jj=CalcAstro.JJ(t.date().day(),t.date().month(),t.date().year());

	jj+=((double) t.time().hour())/24.0;
	jj+=((double) t.time().minute())/1440.0;
	jj+=( ((double) t.time().second()) + ((double) t.time().msec())/1000.0 )/86400.0;

	return jj;
}


// Generation d'une chaine de caracteres aleatoires
//
// CE:	On passe le nombre de caracteres de la chaine a generer ;
//
// CS:	La fonction retourne la chaine generee aleatoirement ;
//
QString SupervCLIMSO::GenererChaineAleatoire(int n)
{
	QString Chaine;
	Chaine.reserve(TAILLE_MINI_CHAINE);

	Chaine="";

	srandom((unsigned int) time(NULL));

	for( int i=0; i < n; i++ )
	{
		char c='A'+(char) (26.0*random()/(RAND_MAX+1.0));

		Chaine.append(c);
	}

	return Chaine;
}


//
// Slots du TerminOA 0 : C1
//
void SupervCLIMSO::SlotBoutonModeIC_0(void)
{
	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C1,TERMINOA_CMD_MODE_IC,0);
}
void SupervCLIMSO::SlotBoutonModeDiapo_0(void)
{
	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C1,TERMINOA_CMD_MODE_DIAPO,0);
}
void SupervCLIMSO::SlotBoutonEchLin_0(void)
{
	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C1,TERMINOA_CMD_ECH_LIN,0);
}
void SupervCLIMSO::SlotBoutonEchLog_0(void)
{
	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C1,TERMINOA_CMD_ECH_LOG,0);
}
void SupervCLIMSO::SlotBoutonPalNB_0(void)
{
	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C1,TERMINOA_CMD_PAL_NB,0);
}
void SupervCLIMSO::SlotBoutonPalHalpha_0(void)
{
	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C1,TERMINOA_CMD_PAL_HALPHA,0);
}
void SupervCLIMSO::SlotBoutonPalNoirOrangeBlanc_0(void)
{
	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C1,TERMINOA_CMD_PAL_NOB,0);
}
void SupervCLIMSO::SlotBoutonPalNoirVertBlanc_0(void)
{
	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C1,TERMINOA_CMD_PAL_NVB,0);
}
void SupervCLIMSO::SlotBoutonPalNoirBleuBlanc_0(void)
{
	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C1,TERMINOA_CMD_PAL_NBB,0);
}
void SupervCLIMSO::SlotBoutonZ0_0(void)
{
	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C1,TERMINOA_CMD_Z0,0);
}
void SupervCLIMSO::SlotBoutonZ1_0(void)
{
	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C1,TERMINOA_CMD_Z1,0);
}
void SupervCLIMSO::SlotBoutonZ2_0(void)
{
	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C1,TERMINOA_CMD_Z2,0);
}
void SupervCLIMSO::SlotBoutonZ3_0(void)
{
	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C1,TERMINOA_CMD_Z3,0);
}
void SupervCLIMSO::SlotBoutonZ4_0(void)
{
	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C1,TERMINOA_CMD_Z4,0);
}
void SupervCLIMSO::SlotBoutonZ5_0(void)
{
	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C1,TERMINOA_CMD_Z5,0);
}
void SupervCLIMSO::SlotBoutonZ6_0(void)
{
	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C1,TERMINOA_CMD_Z6,0);
}
void SupervCLIMSO::SlotBoutonZ7_0(void)
{
	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C1,TERMINOA_CMD_Z7,0);
}
void SupervCLIMSO::SlotBoutonZ8_0(void)
{
	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C1,TERMINOA_CMD_Z8,0);
}
void SupervCLIMSO::SlotBoutonZ9_0(void)
{
	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C1,TERMINOA_CMD_Z9,0);
}
void SupervCLIMSO::SlotSpinBoxCSB_0(int value)
{
	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C1,TERMINOA_CMD_CSB,value);
}
void SupervCLIMSO::SlotSpinBoxCSH_0(int value)
{
	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C1,TERMINOA_CMD_CSH,value);
}
void SupervCLIMSO::SlotSpinBoxCPuiLUT_0(int value)
{
	if( !C1Actif )
	{
		MessageDevezValider(CAMEROA_C1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C1,TERMINOA_CMD_CPUILUT,value);
}

//
// Slots du TerminOA 1 : C2
//
void SupervCLIMSO::SlotBoutonModeIC_1(void)
{
	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C2,TERMINOA_CMD_MODE_IC,0);
}
void SupervCLIMSO::SlotBoutonModeDiapo_1(void)
{
	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C2,TERMINOA_CMD_MODE_DIAPO,0);
}
void SupervCLIMSO::SlotBoutonEchLin_1(void)
{
	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C2,TERMINOA_CMD_ECH_LIN,0);
}
void SupervCLIMSO::SlotBoutonEchLog_1(void)
{
	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C2,TERMINOA_CMD_ECH_LOG,0);
}
void SupervCLIMSO::SlotBoutonPalNB_1(void)
{
	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C2,TERMINOA_CMD_PAL_NB,0);
}
void SupervCLIMSO::SlotBoutonPalHalpha_1(void)
{
	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C2,TERMINOA_CMD_PAL_HALPHA,0);
}
void SupervCLIMSO::SlotBoutonPalNoirOrangeBlanc_1(void)
{
	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C2,TERMINOA_CMD_PAL_NOB,0);
}
void SupervCLIMSO::SlotBoutonPalNoirVertBlanc_1(void)
{
	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C2,TERMINOA_CMD_PAL_NVB,0);
}
void SupervCLIMSO::SlotBoutonPalNoirBleuBlanc_1(void)
{
	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C2,TERMINOA_CMD_PAL_NBB,0);
}
void SupervCLIMSO::SlotBoutonZ0_1(void)
{
	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C2,TERMINOA_CMD_Z0,0);
}
void SupervCLIMSO::SlotBoutonZ1_1(void)
{
	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C2,TERMINOA_CMD_Z1,0);
}
void SupervCLIMSO::SlotBoutonZ2_1(void)
{
	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C2,TERMINOA_CMD_Z2,0);
}
void SupervCLIMSO::SlotBoutonZ3_1(void)
{
	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C2,TERMINOA_CMD_Z3,0);
}
void SupervCLIMSO::SlotBoutonZ4_1(void)
{
	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C2,TERMINOA_CMD_Z4,0);
}
void SupervCLIMSO::SlotBoutonZ5_1(void)
{
	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C2,TERMINOA_CMD_Z5,0);
}
void SupervCLIMSO::SlotBoutonZ6_1(void)
{
	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C2,TERMINOA_CMD_Z6,0);
}
void SupervCLIMSO::SlotBoutonZ7_1(void)
{
	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C2,TERMINOA_CMD_Z7,0);
}
void SupervCLIMSO::SlotBoutonZ8_1(void)
{
	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C2,TERMINOA_CMD_Z8,0);
}
void SupervCLIMSO::SlotBoutonZ9_1(void)
{
	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C2,TERMINOA_CMD_Z9,0);
}
void SupervCLIMSO::SlotSpinBoxCSB_1(int value)
{
	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C2,TERMINOA_CMD_CSB,value);
}
void SupervCLIMSO::SlotSpinBoxCSH_1(int value)
{
	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C2,TERMINOA_CMD_CSH,value);
}
void SupervCLIMSO::SlotSpinBoxCPuiLUT_1(int value)
{
	if( !C2Actif )
	{
		MessageDevezValider(CAMEROA_C2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_C2,TERMINOA_CMD_CPUILUT,value);
}

//
// Slots du TerminOA 2 : L1
//
void SupervCLIMSO::SlotBoutonModeIC_2(void)
{
	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L1,TERMINOA_CMD_MODE_IC,0);
}
void SupervCLIMSO::SlotBoutonModeDiapo_2(void)
{
	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L1,TERMINOA_CMD_MODE_DIAPO,0);
}
void SupervCLIMSO::SlotBoutonEchLin_2(void)
{
	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L1,TERMINOA_CMD_ECH_LIN,0);
}
void SupervCLIMSO::SlotBoutonEchLog_2(void)
{
	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L1,TERMINOA_CMD_ECH_LOG,0);
}
void SupervCLIMSO::SlotBoutonPalNB_2(void)
{
	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L1,TERMINOA_CMD_PAL_NB,0);
}
void SupervCLIMSO::SlotBoutonPalHalpha_2(void)
{
	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L1,TERMINOA_CMD_PAL_HALPHA,0);
}
void SupervCLIMSO::SlotBoutonPalNoirOrangeBlanc_2(void)
{
	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L1,TERMINOA_CMD_PAL_NOB,0);
}
void SupervCLIMSO::SlotBoutonPalNoirVertBlanc_2(void)
{
	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L1,TERMINOA_CMD_PAL_NVB,0);
}
void SupervCLIMSO::SlotBoutonPalNoirBleuBlanc_2(void)
{
	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L1,TERMINOA_CMD_PAL_NBB,0);
}
void SupervCLIMSO::SlotBoutonZ0_2(void)
{
	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L1,TERMINOA_CMD_Z0,0);
}
void SupervCLIMSO::SlotBoutonZ1_2(void)
{
	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L1,TERMINOA_CMD_Z1,0);
}
void SupervCLIMSO::SlotBoutonZ2_2(void)
{
	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L1,TERMINOA_CMD_Z2,0);
}
void SupervCLIMSO::SlotBoutonZ3_2(void)
{
	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L1,TERMINOA_CMD_Z3,0);
}
void SupervCLIMSO::SlotBoutonZ4_2(void)
{
	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L1,TERMINOA_CMD_Z4,0);
}
void SupervCLIMSO::SlotBoutonZ5_2(void)
{
	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L1,TERMINOA_CMD_Z5,0);
}
void SupervCLIMSO::SlotBoutonZ6_2(void)
{
	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L1,TERMINOA_CMD_Z6,0);
}
void SupervCLIMSO::SlotBoutonZ7_2(void)
{
	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L1,TERMINOA_CMD_Z7,0);
}
void SupervCLIMSO::SlotBoutonZ8_2(void)
{
	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L1,TERMINOA_CMD_Z8,0);
}
void SupervCLIMSO::SlotBoutonZ9_2(void)
{
	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L1,TERMINOA_CMD_Z9,0);
}
void SupervCLIMSO::SlotSpinBoxCSB_2(int value)
{
	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L1,TERMINOA_CMD_CSB,value);
}
void SupervCLIMSO::SlotSpinBoxCSH_2(int value)
{
	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L1,TERMINOA_CMD_CSH,value);
}
void SupervCLIMSO::SlotSpinBoxCPuiLUT_2(int value)
{
	if( !L1Actif )
	{
		MessageDevezValider(CAMEROA_L1);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L1,TERMINOA_CMD_CPUILUT,value);
}

//
// Slots du TerminOA 3 : L2
//
void SupervCLIMSO::SlotBoutonModeIC_3(void)
{
	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L2,TERMINOA_CMD_MODE_IC,0);
}
void SupervCLIMSO::SlotBoutonModeDiapo_3(void)
{
	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L2,TERMINOA_CMD_MODE_DIAPO,0);
}
void SupervCLIMSO::SlotBoutonEchLin_3(void)
{
	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L2,TERMINOA_CMD_ECH_LIN,0);
}
void SupervCLIMSO::SlotBoutonEchLog_3(void)
{
	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L2,TERMINOA_CMD_ECH_LOG,0);
}
void SupervCLIMSO::SlotBoutonPalNB_3(void)
{
	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L2,TERMINOA_CMD_PAL_NB,0);
}
void SupervCLIMSO::SlotBoutonPalHalpha_3(void)
{
	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L2,TERMINOA_CMD_PAL_HALPHA,0);
}
void SupervCLIMSO::SlotBoutonPalNoirOrangeBlanc_3(void)
{
	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L2,TERMINOA_CMD_PAL_NOB,0);
}
void SupervCLIMSO::SlotBoutonPalNoirVertBlanc_3(void)
{
	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L2,TERMINOA_CMD_PAL_NVB,0);
}
void SupervCLIMSO::SlotBoutonPalNoirBleuBlanc_3(void)
{
	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L2,TERMINOA_CMD_PAL_NBB,0);
}
void SupervCLIMSO::SlotBoutonZ0_3(void)
{
	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L2,TERMINOA_CMD_Z0,0);
}
void SupervCLIMSO::SlotBoutonZ1_3(void)
{
	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L2,TERMINOA_CMD_Z1,0);
}
void SupervCLIMSO::SlotBoutonZ2_3(void)
{
	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L2,TERMINOA_CMD_Z2,0);
}
void SupervCLIMSO::SlotBoutonZ3_3(void)
{
	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L2,TERMINOA_CMD_Z3,0);
}
void SupervCLIMSO::SlotBoutonZ4_3(void)
{
	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L2,TERMINOA_CMD_Z4,0);
}
void SupervCLIMSO::SlotBoutonZ5_3(void)
{
	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L2,TERMINOA_CMD_Z5,0);
}
void SupervCLIMSO::SlotBoutonZ6_3(void)
{
	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L2,TERMINOA_CMD_Z6,0);
}
void SupervCLIMSO::SlotBoutonZ7_3(void)
{
	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L2,TERMINOA_CMD_Z7,0);
}
void SupervCLIMSO::SlotBoutonZ8_3(void)
{
	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L2,TERMINOA_CMD_Z8,0);
}
void SupervCLIMSO::SlotBoutonZ9_3(void)
{
	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L2,TERMINOA_CMD_Z9,0);
}
void SupervCLIMSO::SlotSpinBoxCSB_3(int value)
{
	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L2,TERMINOA_CMD_CSB,value);
}
void SupervCLIMSO::SlotSpinBoxCSH_3(int value)
{
	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L2,TERMINOA_CMD_CSH,value);
}
void SupervCLIMSO::SlotSpinBoxCPuiLUT_3(int value)
{
	if( !L2Actif )
	{
		MessageDevezValider(CAMEROA_L2);
		return;
	}
	EnvoyerCommandeIntTerminOA(TERMINOA_L2,TERMINOA_CMD_CPUILUT,value);
}


// Envoyer une commande avec un parametre entier a un TerminOA
//
// CE:	On passe l'identifieur du TerminOA ;
//
//		On passe le numero de la commande ;
//
//		On passe la valeur eventuelle de la commande ;
//
void SupervCLIMSO::EnvoyerCommandeIntTerminOA(int id,int cmd,int valeur)
{
	if( !PLCommandeTerminOA[id]->Client->Connecte() ) return;

	QString ChaineCmd;					// Chaine avec taille minimale pour la composition de commandes afin d'eviter un bogue QString et la rapidite
	ChaineCmd.reserve(TAILLE_MINI_CHAINE_CMD);

	ChaineCmd=CmdClientTerminOA[cmd];	// La chaine de commande qui sera transmise

	// Selon le numero de commande, si on doit ajouter quelque chose
	//
	switch( cmd )
	{
		case TERMINOA_CMD_CSB:
		case TERMINOA_CMD_CSH:
		case TERMINOA_CMD_CPUILUT:
			ChaineCmd+=QString("%1").arg(valeur);
			break;
	}

	ChaineCmd+="\n";

	MutexEnvChaineBIO_TerminOA[id].lock();

	if( PLCommandeTerminOA[id]->Client->EnvoyerChaineBIO(ChaineCmd) <= 0 )
	{
		// Erreur lors de l'emission
		//
		Log("*** ERREUR: Impossible d'envoyer la commande "+ChaineCmd.left(ChaineCmd.length()-1)+" au TerminOA de "+InstrumentCLIMSO[id]+" ***");
	}

	MutexEnvChaineBIO_TerminOA[id].unlock();
}



//--------------------------------------------------------------------------------------------------------------------------------

// Constructeur du processus leger client chiffre du canal de commande d'un RobOA
//
// CE:	On passe un pointeur vers la fenetre principale SupervCLIMSO ;
//
//		On passe l'adresse IP du serveur RobOA en valeur host (0x________) ;
//
//		On passe le port du serveur RoboOA en valeur host (0x____) ;
//
//		On passe le timeout en secondes pour la tentative d'ecriture de donnees dans la socket ;
//
//		On passe le timeout en secondes pour la tentative de lecture de donnees dans la socket ;
//
//		On passe true si on veut parametrer la redirection de SIGPIPE (ecriture dans tube ferme) ou false dans le cas contraire ;
//
//		On passe un pointeur sur la fonction C de handler du signal SIGPIPE ;
//
//		On passe un pointeur sur une chaine de char qui contient le mot de passe pour acceder a la cle privee du client SSL
//	 	Ce mot de passe ne doit pas contenir plus de TAILLE_MAX_MDP_CLE_PRIVEE-1 caracteres ;
//
//		On passe un pointeur sur char vers un buffer de stockage du mot de passe pour acceder a la cle privee du client SSL
//	 	Ce buffer doit etre reserve avec TAILLE_MAX_MDP_CLE_PRIVEE elements ;
//
//		On passe un pointeur sur la fonction C appelee par la librairie SSL lors de la demande du mot de passe pour acceder a la cle
//	 	privee du client SSL stockee dans un fichier PEM ;
//
//		On passe un pointeur sur une chaine de char qui contient le chemin complet du fichier PEM du certificat
//		 de l'autorite de certification CA qui a signe les certificats du client ;
//
//		On passe un pointeur sur une chaine de char qui contient le chemin complet du fichier PEM du certificat du client ;
//
//		On passe un pointeur sur une chaine de char qui contient le chemin complet du fichier PEM de la cle privee du client ;
//
// CS:	-
//
ProcessusLegerClientCommandeRobOA::ProcessusLegerClientCommandeRobOA(SupervCLIMSO *pfp,uint32_t pAdresse,uint16_t pPort,int pTimeoutSocketPut,int pTimeoutSocketGet,int pParamSIGPIPE,void (*pFnHandlerSIGPIPE)(int),const char *pMdpClePriveeClient,char *pBuffStockMdpClePriveeClient,int (*pFnMotDePasseClePriveeChiffree)(char*, int, int, void*),const char *pCheminCertificatCA,const char *pCheminCertificatClient,const char *pCheminClePriveeClient)
{
	// Initialisation des variables
	//
	DrapeauDemandeTerminaison=false;
	DrapeauConnexion=false;

	PCI7334Initialise=false;

	for( int i=0; i < NB_AXES; i++ ) DrapeauDemandeRechIndexAxe[i]=false;
	AxeEnRechercheIndex=false;

	// Instanciation de l'objet client chiffre
	//
	if( (Client=new (std::nothrow) PointCommClientChiffre(false,pAdresse,pPort,pTimeoutSocketPut,pTimeoutSocketGet,pParamSIGPIPE,pFnHandlerSIGPIPE,pMdpClePriveeClient,pBuffStockMdpClePriveeClient,pFnMotDePasseClePriveeChiffree,pCheminCertificatCA,pCheminCertificatClient,pCheminClePriveeClient)) == NULL )
	{
		std::cerr << "ProcessusLegerClientCommandeRobOA: ERREUR: Impossible de creer l'objet client chiffre." << std::endl;
	}

	// Pointeur vers l'application parent SupervCLIMSO
	//
	FPSupervCLIMSO=pfp;

	// Copie des commandes et reponses dans l'objet pour etre thread safe (bogues avec QString en inter processus)
	//
	for( int i=0; i < NB_CMD_CLIENT_ROBOA; i++ ) CmdClientRobOA[i]=ListeCmdClientROBOA[i];
	for( int i=0; i < NB_REP_SERVEUR_ROBOA; i++ ) RepServeurRobOA[i]=ListeRepServeurROBOA[i];

	// Chaines des commandes completes pour eviter les bogues (#0 0x00a1864c in memcpy () from /lib/libc.so.6) lies a QString dans les threads avec +"\n"
	//
	CmdSesame=CmdClientRobOA[ROBOA_CMD_SESAMEOUVRETOI]+"\n";
	CmdInit=CmdClientRobOA[ROBOA_CMD_INITCONFIGHW]+"\n";
	CmdDeconnexion=CmdClientRobOA[ROBOA_CMD_DECONNEXION]+"\n";
}


// Destructeur du processus leger client chiffre du canal de commande d'un RobOA
//
ProcessusLegerClientCommandeRobOA::~ProcessusLegerClientCommandeRobOA()
{
	// Si le thread est encore actif et donc que le serveur ne s'est pas termine normalement
	//
	if( running() )
	{
		terminate();	// On termine le thread de maniere brutale
	}

	// On supprime l'objet client
	//
	delete Client;
}


// Fonction de la demande de terminaison propre du processus leger du canal de commande d'un RobOA
//
void ProcessusLegerClientCommandeRobOA::DemandeTerminaison(void)
{
	DrapeauDemandeTerminaison=true;

	// La socket passe en mode non bloquant
	//
	Client->SocketNonBloquante();
}


// Fonction d'autorisation de la connexion a un serveur RobOA
//
void ProcessusLegerClientCommandeRobOA::ConnexionAutorisee(void)
{
	DrapeauConnexion=true;
}


// Fonction de non autorisation de connexion a un serveur RobOA
//
void ProcessusLegerClientCommandeRobOA::ConnexionNonAutorisee(void)
{
	DrapeauConnexion=false;
}


// Surcharge de la methode run() qui contient le code d'execution du thread du client chiffre du canal de commande d'un RobOA
//
// ATTENTION : QT3 n'est pas thread-safe (c'est a dire que les fonctions ne peuvent pas etre appellees par plusieurs threads a la fois).
//		Les widgets doivent etre modifies uniquement par l'application maitre qui gere la boucle evenementielle. Donc un thread
//		qui doit modifier un widget de l'application doit communiquer par un evenement particulier QCustomEvent via la fontion
//		thread-safe QApplication::postEvent(). Il ne doit pas modifier directement le widget sinon l'application plantera.
//
void ProcessusLegerClientCommandeRobOA::run()
{
	int Sortir=false;	// Drapeau d'indication de sortie de la boucle de traitement des commandes
	QString Chaine_log;						// Pour composer une chaine de log
	Chaine_log.reserve(TAILLE_MINI_CHAINE_LOG);
	QString ChaineCmd;						// Chaine avec taille minimale pour la composition de commandes afin d'eviter un bogue QString et la rapidite
	ChaineCmd.reserve(TAILLE_MINI_CHAINE_CMD);


	// On capture un element du semaphore de synchronisation
	//
	SemaphoreSyncLancementThreadSupervCLIMSO++;


	// Boucle de connexion au serveur RobOA
	//
	do
	{
		// Si on a l'autorisation pour se connecter
		//
		if( DrapeauConnexion )
		{
			// On tente une connexion sur le serveur RobOA
			//
			if( Client->Connecter() )
			{
				// La connexion sur le serveur RobOA a reussie
				//
				// On commence par envoyer la chaine secrete d'ouverture aux commandes
				//
				MutexEnvChaineBIO_RobOA.lock();

				if( Client->EnvoyerChaineBIO(CmdSesame) <= 0 )
				{
					MutexEnvChaineBIO_RobOA.unlock();

					// Erreur lors de l'emission, la liaison n'est pas correcte, on peut refermer cette connexion
					//
					std::cerr << "ProcessusLegerClientCommandeRobOA: run(): ERREUR: Impossible d'envoyer la chaine secrete d'ouverture aux commandes." << std::endl;

					Client->Fermer();
				}
				else
				{
					int SortirBoucleER=false;					// Drapeau pour sortir ou non de la boucle emission/reception des commandes
					char LigneRecue[TAILLE_MAXI_CHAINE_BIO+1];	// Ligne de caracteres recu du serveur RobOA

					MutexEnvChaineBIO_RobOA.unlock();

					// Emission d'un log
					//
					Chaine_log="Connexion à RobOA canal des commandes : ok.";
					CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(Chaine_log);
					QApplication::postEvent(FPSupervCLIMSO,event);

					// On initialise la configuration du NI PCI-7334
					//
					MutexEnvChaineBIO_RobOA.lock();

					if( Client->EnvoyerChaineBIO(CmdInit) <= 0 )
					{
						// Erreur lors de l'emission, la liaison n'est pas correcte, on peut refermer cette connexion
						//
						std::cerr << "ProcessusLegerClientCommandeRobOA: run(): ERREUR: Impossible d'envoyer la commande d'initialisation du NI-PCI-7334." << std::endl;

						Client->Fermer();
					}

					MutexEnvChaineBIO_RobOA.unlock();

					// On entre dans la boucle emission/reception des commandes
					//
					do
					{
						// Si il est possible de lire des donnees sur la socket dans la seconde qui suit
						//
						if( Client->PossibleLireDonneesSocket(1000) )
						{
							if( Client->RecevoirChaineBIO(LigneRecue) > 0 )
							{
								int i=0;					// Indice
								int icmd=0;					// Indice du retour de commande
								QString Ligne;		// La ligne recue dans un QString sans les caracteres speciaux et les espacements multiples
								Ligne.reserve(TAILLE_MINI_CHAINE);

								Ligne="";

								// On coupe la chaine au premier \r ou \n
								//
								// On supprime les espacements multiples  ATTENTION: TRES IMPORTANT POUR QUE QString.section(" ",,) FONCTIONNE CORRECTEMENT
								//
								while( LigneRecue[i] != 0 )
								{
									if( LigneRecue[i] == '\r' ) break;
									if( LigneRecue[i] == '\n' ) break;
									if( LigneRecue[i] != ' ' )
									{
										Ligne+=LigneRecue[i];
									}
									else
									{
										// Le caractere courant est un espacement, on ne l'ajoute pas si le dernier caractere de Ligne est aussi un espacement
										//
										if( Ligne.length() > 0 )
										{
											if( Ligne.right(1) != " " ) Ligne+=LigneRecue[i];
										}
									}
									i++;
								}
//std::cout << "Ligne recue propre:" << Ligne << std::endl;

								// Analyse de la ligne recue du serveur RobOA, recherche du retour de commande
								//
								while( RepServeurRobOA[icmd] != QString("") && Ligne.left(RepServeurRobOA[icmd].length()) != RepServeurRobOA[icmd] ) icmd++;

								// Si on a bien identifie un retour de valeur d'une commande
								//
								if( RepServeurRobOA[icmd] !=  QString("") )
								{
									QString ValReponse;			// Les valeurs de la reponse
									ValReponse.reserve(TAILLE_MINI_CHAINE);

									ValReponse=Ligne.right(Ligne.length()-RepServeurRobOA[icmd].length());

									switch( icmd )
									{
										case ROBOA_REP_OKINIT:			// Bonne initialisation du NI PCI-7334

											PCI7334Initialise=true;

											{
												Chaine_log="National Instrument PCI-7334 et MID-7604 initialisés.";
												CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(Chaine_log);
												QApplication::postEvent(FPSupervCLIMSO,event);
											}
											break;

										case ROBOA_REP_NONINIT:			// Mauvaise initialisation du NI PCI-7334

											PCI7334Initialise=false;

											{
												Chaine_log="*** ERREUR: National Instrument PCI-7334 et MID-7604 NON initialisés ***";
												CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(Chaine_log);
												QApplication::postEvent(FPSupervCLIMSO,event);
											}

											// Pas la peine de rester dans la boucle, il faudra retenter une connexion pour initialiser l'electronique
											//
											SortirBoucleER=true;

											break;

										case ROBOA_REP_OKINDEXAXE:		// L'index d'un axe a ete trouve
											{
												QString rep1;			// Numero de l'axe

												rep1=ValReponse.section(" ",0,0);

												int n=rep1.toInt()-1;		// Numero de l'axe initialise (de 0 a NB_AXES-1 pour etre conforme au tableau et definitions)

												// S'il s'agit d'un numero d'axe correct
												//
												if( n >= 0 && n < NB_AXES )
												{
													AxeEnRechercheIndex=false;				// L'index est trouve, nous ne sommes plus en recherche d'index
													DrapeauDemandeRechIndexAxe[n]=false;	// Plus la peine de rechercher cet index d'axe

													CEventSupervCLIMSO_IndexAxeTrouve *event=new CEventSupervCLIMSO_IndexAxeTrouve(n);
													QApplication::postEvent(FPSupervCLIMSO,event);
												}
												else
												{
													Chaine_log="*** ERREUR: Retour de RobOA incohérent: le numéro d'axe initialisé n'existe pas ***";
													CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(Chaine_log);
													QApplication::postEvent(FPSupervCLIMSO,event);
												}
											}
											break;

										case ROBOA_REP_NONOKINDEXAXE:	// L'index d'un axe N'A PAS ETE trouve
											{
												QString rep1;	// Premiere valeur de la reponse en retour

												rep1=ValReponse.section(" ",0,0);		// Numero de l'axe

												int n=rep1.toInt()-1;		// Numero de l'axe non initialise (de 0 a NB_AXES-1 pour etre conforme au tableau et definitions)

												// S'il s'agit d'un numero d'axe correct
												//
												if( n >= 0 && n < NB_AXES )
												{
													AxeEnRechercheIndex=false;				// L'index n'est pas trouve, nous ne sommes plus en recherche d'index

													CEventSupervCLIMSO_IndexAxeNonTrouve *event=new CEventSupervCLIMSO_IndexAxeNonTrouve(n);
													QApplication::postEvent(FPSupervCLIMSO,event);
												}
												else
												{
													Chaine_log="*** ERREUR: Retour de RobOA incohérent: le numéro d'axe non initialisé n'existe pas ***";
													CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(Chaine_log);
													QApplication::postEvent(FPSupervCLIMSO,event);
												}
											}
											break;

										case ROBOA_REP_OKPOSREPOSAXE:	// La position home d'un axe a ete trouvee
											{
												QString rep1;			// Numero de l'axe

												rep1=ValReponse.section(" ",0,0);

												int n=rep1.toInt()-1;		// Numero de l'axe initialise (de 0 a NB_AXES-1 pour etre conforme au tableau et definitions)

												// S'il s'agit d'un numero d'axe correct
												//
												if( n >= 0 && n < NB_AXES )
												{
													AxeEnRechercheIndex=false;				// L'index home est trouve, nous ne sommes plus en recherche d'index home
													DrapeauDemandeRechIndexAxe[n]=false;	// Plus la peine de rechercher cet index d'axe

													CEventSupervCLIMSO_IndexAxeTrouve *event=new CEventSupervCLIMSO_IndexAxeTrouve(n);
													QApplication::postEvent(FPSupervCLIMSO,event);
												}
												else
												{
													Chaine_log="*** ERREUR: Retour de RobOA incohérent: le numéro d'axe initialisé n'existe pas ***";
													CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(Chaine_log);
													QApplication::postEvent(FPSupervCLIMSO,event);
												}
											}
											break;

										case ROBOA_REP_NONOKPOSREPOSAXE:	// La position home d'un axe N'A PAS ETE trouvee
											{
												QString rep1;	// Premiere valeur de la reponse en retour

												rep1=ValReponse.section(" ",0,0);		// Numero de l'axe

												int n=rep1.toInt()-1;		// Numero de l'axe non initialise (de 0 a NB_AXES-1 pour etre conforme au tableau et definitions)

												// S'il s'agit d'un numero d'axe correct
												//
												if( n >= 0 && n < NB_AXES )
												{
													AxeEnRechercheIndex=false;				// L'index home n'est pas trouve, nous ne sommes plus en recherche d'index

													CEventSupervCLIMSO_IndexAxeNonTrouve *event=new CEventSupervCLIMSO_IndexAxeNonTrouve(n);
													QApplication::postEvent(FPSupervCLIMSO,event);
												}
												else
												{
													Chaine_log="*** ERREUR: Retour de RobOA incohérent: le numéro d'axe non initialisé n'existe pas ***";
													CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(Chaine_log);
													QApplication::postEvent(FPSupervCLIMSO,event);
												}
											}
											break;

										case ROBOA_REP_POSAXESPASENC:	// retour de la position des axes en pas encodeur en quadrature
											{
												QString rep1;			// Premiere valeur de la reponse en retour
												QString rep2;			// Deuxieme valeur de la reponse en retour
												QString rep3;			// Troisieme valeur de la reponse en retour
												QString rep4;			// Quatrieme valeur de la reponse en retour

												rep1=ValReponse.section(" ",1,1);		// Position de l'axe 1 (il y a un premier espace au debut de la valeur de reponse)
												rep2=ValReponse.section(" ",2,2);		// Position de l'axe 2
												rep3=ValReponse.section(" ",3,3);		// Position de l'axe 3
												rep4=ValReponse.section(" ",4,4);		// Position de l'axe 4

												CEventSupervCLIMSO_PosAxes *event=new CEventSupervCLIMSO_PosAxes(rep1.toInt(),rep2.toInt(),rep3.toInt(),rep4.toInt());
												QApplication::postEvent(FPSupervCLIMSO,event);
											}
											break;
									}
								}
							}
							else
							{
								// Il y a une erreur ou la connexion est perdue...
								//
								SortirBoucleER=true;
							}
						}
						else
						{
							// Si on demande d'initier la recherche de l'index de l'axe n
							//
							if( !AxeEnRechercheIndex )
							{
								for( int i=0; i < NB_AXES; i++ )
								{
									if( DrapeauDemandeRechIndexAxe[i] == true )
									{
										// La recherche de l'index de l'axe est declenchee
										//  ATTENTION ELLE EST BLOQUANTE POUR LES LIAISONS AVEC ROBOA TANT QUE L'INDEX N'EST PAS TROUVE !!!
										//
										AxeEnRechercheIndex=true;

										switch( i )
										{
											case AXE_ROUE_OUVERTURE:
											case AXE_ROUE_FILTREC2:
												ChaineCmd=CmdClientRobOA[ROBOA_CMD_RECH_INDEX_AXE]+QString("%1\n").arg(i+1);
												break;

											case AXE_PLATINE_X:
											case AXE_PLATINE_Y:
												ChaineCmd=CmdClientRobOA[ROBOA_CMD_RECH_POSREPOS_AXE]+QString("%1\n").arg(i+1);
												break;
										}

										MutexEnvChaineBIO_RobOA.lock();

										if( Client->EnvoyerChaineBIO(ChaineCmd) <= 0 )
										{
											// Erreur lors de l'emission, la liaison n'est pas correcte, on peut refermer cette connexion
											//
											std::cerr << "ProcessusLegerClientCommandeRobOA: run(): ERREUR: Impossible d'envoyer la demande de recherche de l'index de l'axe " << i+1 << "." << std::endl;

											SortirBoucleER=true;
											AxeEnRechercheIndex=false;
										}

										MutexEnvChaineBIO_RobOA.unlock();
									}
								}
							}
							else
							{
/* PAS LA PEINE CAR IL Y A CHAQUE SECONDE UNE DEMANDE DE LA POSITION DES CODEURS

								// Il n'y a rien a lire du serveur depuis 1s donc on peut envoyer un "es-tu vivant ?" au serveur
								//  pour eviter un timeout. Le serveur RobOA ferme automatiquement la connexion si elle est incactive.
								//
								if( Client->EnvoyerChaineBIO(CmdClientROBOA[ROBOA_CMD_EN_ATTENTE]+"\n") <= 0 )
								{
									// Erreur lors de l'emission, la liaison n'est pas correcte, on peut refermer cette connexion
									//
									std::cerr << "ProcessusLegerClientCommandeRobOA: run(): ERREUR: Impossible d'envoyer la chaine es-tu en vie ?." << std::endl;

									SortirBoucleER=true;
								}

								msleep(500);	// On patiente pour ne pas emballer la liaison
*/
							}

						}

						// Si on demande une deconnexion du serveur
						//
						if( !DrapeauConnexion )
						{
							// On demande la deconnexion au serveur
							//
							MutexEnvChaineBIO_RobOA.lock();

							if( Client->EnvoyerChaineBIO(CmdDeconnexion) <= 0 )
							{
								// Erreur lors de l'emission, la liaison n'est pas correcte, on peut refermer cette connexion
								//
								std::cerr << "ProcessusLegerClientCommandeRobOA: run(): ERREUR: Impossible d'envoyer la commande de deconnexion." << std::endl;
							}
							else
							{
								Chaine_log="Déconnexion engagée de RobOA canal des commandes.";
								CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(Chaine_log);
								QApplication::postEvent(FPSupervCLIMSO,event);

								sleep(2);				// On attend un peu
							}

							MutexEnvChaineBIO_RobOA.unlock();

							SortirBoucleER=true;
						}

						if( DrapeauDemandeTerminaison ) SortirBoucleER=true;

					} while( !SortirBoucleER );

					// On peut fermer la connexion avec le serveur RobOA
					//
					Client->Fermer();
				}
			}
			else
			{
				// La connexion sur le serveur RobOA a echouee
				//
				// On patientera un peu avant de retenter une connexion
				//
				Chaine_log="*** Echec de connexion sur RobOA canal des commandes ***";
				CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(Chaine_log);
				QApplication::postEvent(FPSupervCLIMSO,event);
			}
		}

		if( DrapeauDemandeTerminaison ) Sortir=true; else sleep(TEMPS_ATTENTE_AVANT_NOUVELLE_TENTATIVE_CONNEXION);

	} while( !Sortir );
}


// Pour savoir si le materiel National Instrument est initialise au sens electronique
//
// CE:	-
//
// CS:	La fonction est vraie si l'electronique est initialisee ;
//
int ProcessusLegerClientCommandeRobOA::NI_Hardware_Initialise(void)
{
	return PCI7334Initialise;
}

// Demande au thread d'initier la recherche de l'index codeur ou de l'index de la position HOME de l'axe n
//
// CE:	On passe le numero de l'axe
//
// CS:	-
//
void ProcessusLegerClientCommandeRobOA::DemandeRechercheIndexAxe(int n)
{
	DrapeauDemandeRechIndexAxe[n]=true;
}



//--------------------------------------------------------------------------------------------------------------------------------

// Constructeur du processus leger client chiffre du canal de commande d'un CamerOA
//
// CE:	On passe le numero id de ce processus leger ;
//
//		On passe un pointeur vers la fenetre principale SupervCLIMSO ;
//
//		On passe l'adresse IP du serveur CamerOA en valeur host (0x________) ;
//
//		On passe le port du serveur CamerOA en valeur host (0x____) ;
//
//		On passe le timeout en secondes pour la tentative d'ecriture de donnees dans la socket ;
//
//		On passe le timeout en secondes pour la tentative de lecture de donnees dans la socket ;
//
//		On passe true si on veut parametrer la redirection de SIGPIPE (ecriture dans tube ferme) ou false dans le cas contraire ;
//
//		On passe un pointeur sur la fonction C de handler du signal SIGPIPE ;
//
//		On passe un pointeur sur une chaine de char qui contient le mot de passe pour acceder a la cle privee du client SSL
//	 	Ce mot de passe ne doit pas contenir plus de TAILLE_MAX_MDP_CLE_PRIVEE-1 caracteres ;
//
//		On passe un pointeur sur char vers un buffer de stockage du mot de passe pour acceder a la cle privee du client SSL
//	 	Ce buffer doit etre reserve avec TAILLE_MAX_MDP_CLE_PRIVEE elements ;
//
//		On passe un pointeur sur la fonction C appelee par la librairie SSL lors de la demande du mot de passe pour acceder a la cle
//	 	privee du client SSL stockee dans un fichier PEM ;
//
//		On passe un pointeur sur une chaine de char qui contient le chemin complet du fichier PEM du certificat
//		 de l'autorite de certification CA qui a signe les certificats du client ;
//
//		On passe un pointeur sur une chaine de char qui contient le chemin complet du fichier PEM du certificat du client ;
//
//		On passe un pointeur sur une chaine de char qui contient le chemin complet du fichier PEM de la cle privee du client ;
//
// CS:	-
//
ProcessusLegerClientCommandeCamerOA::ProcessusLegerClientCommandeCamerOA(int pid,SupervCLIMSO *pfp,uint32_t pAdresse,uint16_t pPort,int pTimeoutSocketPut,int pTimeoutSocketGet,int pParamSIGPIPE,void (*pFnHandlerSIGPIPE)(int),const char *pMdpClePriveeClient,char *pBuffStockMdpClePriveeClient,int (*pFnMotDePasseClePriveeChiffree)(char*, int, int, void*),const char *pCheminCertificatCA,const char *pCheminCertificatClient,const char *pCheminClePriveeClient)
{
	// Initialisation des variables
	//
	id=pid;

	DrapeauDemandeTerminaison=false;
	DrapeauConnexion=false;

	// Instanciation de l'objet client chiffre
	//
	if( (Client=new (std::nothrow) PointCommClientChiffre(false,pAdresse,pPort,pTimeoutSocketPut,pTimeoutSocketGet,pParamSIGPIPE,pFnHandlerSIGPIPE,pMdpClePriveeClient,pBuffStockMdpClePriveeClient,pFnMotDePasseClePriveeChiffree,pCheminCertificatCA,pCheminCertificatClient,pCheminClePriveeClient)) == NULL )
	{
		std::cerr << "ProcessusLegerClientCommandeCamerOA " << id << ": ERREUR: Impossible de creer l'objet client chiffre." << std::endl;
	}

	// Pointeur vers l'application parent SupervCLIMSO
	//
	FPSupervCLIMSO=pfp;

	// Copie des commandes et reponses dans l'objet pour etre thread safe (bogues avec QString en inter processus)
	//
	for( int i=0; i < NB_CMD_CLIENT_CAMEROA; i++ ) CmdClientCamerOA[i]=ListeCmdClientCamerOA[i];
	for( int i=0; i < NB_REP_SERVEUR_CAMEROA; i++ ) RepServeurCamerOA[i]=ListeRepServeurCamerOA[i];

	// Chaines des commandes completes pour eviter les bogues (#0 0x00a1864c in memcpy () from /lib/libc.so.6) lies a QString dans les threads avec +"\n"
	//
	CmdSesame=CmdClientCamerOA[CAMEROA_CMD_SESAMEOUVRETOI]+"\n";
	CmdDeconnexion=CmdClientCamerOA[CAMEROA_CMD_DECONNEXION]+"\n";
}


// Destructeur du processus leger client chiffre du canal de commande d'un CamerOA
//
ProcessusLegerClientCommandeCamerOA::~ProcessusLegerClientCommandeCamerOA()
{
	// Si le thread est encore actif et donc que le serveur ne s'est pas termine normalement
	//
	if( running() )
	{
		terminate();	// On termine le thread de maniere brutale
	}

	// On supprime l'objet client
	//
	delete Client;
}


// Fonction de la demande de terminaison propre du processus leger du canal de commande d'un CamerOA
//
void ProcessusLegerClientCommandeCamerOA::DemandeTerminaison(void)
{
	DrapeauDemandeTerminaison=true;

	// La socket passe en mode non bloquant
	//
	Client->SocketNonBloquante();
}


// Fonction d'autorisation de la connexion a un serveur CamerOA
//
void ProcessusLegerClientCommandeCamerOA::ConnexionAutorisee(void)
{
	DrapeauConnexion=true;
}


// Fonction de non autorisation de connexion a un serveur CamerOA
//
void ProcessusLegerClientCommandeCamerOA::ConnexionNonAutorisee(void)
{
	DrapeauConnexion=false;
}


// Surcharge de la methode run() qui contient le code d'execution du thread du client chiffre du canal de commande d'un CamerOA
//
// ATTENTION : QT3 n'est pas thread-safe (c'est a dire que les fonctions ne peuvent pas etre appellees par plusieurs threads a la fois).
//		Les widgets doivent etre modifies uniquement par l'application maitre qui gere la boucle evenementielle. Donc un thread
//		qui doit modifier un widget de l'application doit communiquer par un evenement particulier QCustomEvent via la fontion
//		thread-safe QApplication::postEvent(). Il ne doit pas modifier directement le widget sinon l'application plantera.
//
void ProcessusLegerClientCommandeCamerOA::run()
{
	int Sortir=false;	// Drapeau d'indication de sortie de la boucle de traitement des commandes
	QString Chaine_log;					// Pour composer une chaine de log
	Chaine_log.reserve(TAILLE_MINI_CHAINE_LOG);
//	QString ChaineCmd;					// Chaine avec taille minimale pour la composition de commandes afin d'eviter un bogue QString et la rapidite
//	ChaineCmd.reserve(TAILLE_MINI_CHAINE_CMD);

	// On capture un element du semaphore de synchronisation
	//
	SemaphoreSyncLancementThreadSupervCLIMSO++;


	// Boucle de connexion au serveur CamerOA
	//
	do
	{
		// Si on a l'autorisation pour se connecter
		//
		if( DrapeauConnexion )
		{
			// On tente une connexion sur le serveur CamerOA
			//
			if( Client->Connecter() )
			{
				// La connexion sur le serveur CamerOA a reussie
				//
				// On commence par envoyer la chaine secrete d'ouverture aux commandes
				//
				MutexEnvChaineBIO_CamerOA[id].lock();

				if( Client->EnvoyerChaineBIO(CmdSesame) <= 0 )
				{
					MutexEnvChaineBIO_CamerOA[id].unlock();

					// Erreur lors de l'emission, la liaison n'est pas correcte, on peut refermer cette connexion
					//
					std::cerr << "ProcessusLegerClientCommandeCamerOA " << id << ": run(): ERREUR: Impossible d'envoyer la chaine secrete d'ouverture aux commandes." << std::endl;

					Client->Fermer();
				}
				else
				{
					int SortirBoucleER=false;					// Drapeau pour sortir ou non de la boucle emission/reception des commandes
					char LigneRecue[TAILLE_MAXI_CHAINE_BIO+1];	// Ligne de caracteres recu du serveur CamerOA

					MutexEnvChaineBIO_CamerOA[id].unlock();

					// Emission d'un log
					//
					Chaine_log="Connexion à CamerOA["+InstrumentCLIMSO[id]+"] canal des commandes : ok.";
					CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(Chaine_log);
					QApplication::postEvent(FPSupervCLIMSO,event);

					// On entre dans la boucle emission/reception des commandes
					//
					do
					{
						// Si il est possible de lire des donnees sur la socket dans la seconde qui suit
						//
						if( Client->PossibleLireDonneesSocket(1000) )
						{
							if( Client->RecevoirChaineBIO(LigneRecue) > 0 )
							{
								int i=0;					// Indice
								int icmd=0;					// Indice du retour de commande
								QString Ligne;		// La ligne recue dans un QString sans les caracteres speciaux et les espacements multiples
								Ligne.reserve(TAILLE_MINI_CHAINE);

								Ligne="";

								// On coupe la chaine au premier \r ou \n
								//
								// On supprime les espacements multiples  ATTENTION: TRES IMPORTANT POUR QUE QString.section(" ",,) FONCTIONNE CORRECTEMENT
								//
								while( LigneRecue[i] != 0 )
								{
									if( LigneRecue[i] == '\r' ) break;
									if( LigneRecue[i] == '\n' ) break;
									if( LigneRecue[i] != ' ' )
									{
										Ligne+=LigneRecue[i];
									}
									else
									{
										// Le caractere courant est un espacement, on ne l'ajoute pas si le dernier caractere de Ligne est aussi un espacement
										//
										if( Ligne.length() > 0 )
										{
											if( Ligne.right(1) != " " ) Ligne+=LigneRecue[i];
										}
									}
									i++;
								}
//std::cout << "Ligne recue propre:" << Ligne << std::endl;

								// Analyse de la ligne recue du serveur CamerOA, recherche du retour de commande
								//
								while( RepServeurCamerOA[icmd] != QString("") && Ligne.left(RepServeurCamerOA[icmd].length()) != RepServeurCamerOA[icmd] ) icmd++;

								// Si on a bien identifie un retour de valeur d'une commande
								//
								if( RepServeurCamerOA[icmd] !=  QString("") )
								{
									QString ValReponse;
									ValReponse.reserve(TAILLE_MINI_CHAINE);

									ValReponse=Ligne.right(Ligne.length()-RepServeurCamerOA[icmd].length());	// Les valeurs de la reponse

									switch( icmd )
									{
										case CAMEROA_REP_TEMPCCD:					// retour de la temperature du CCD en degres C
											{
												QString rep1;	// Premiere valeur de la reponse en retour
												QString rep2;	// Deuxieme valeur de la reponse en retour

												rep1=ValReponse.section(" ",0,0);		// Date de la mesure au format ISO
												rep2=ValReponse.section(" ",1,1);		// temperature

												CEventSupervCLIMSO_TempCCD *event=new CEventSupervCLIMSO_TempCCD(id,QDateTime::fromString(rep1,Qt::ISODate),rep2.toDouble());
												QApplication::postEvent(FPSupervCLIMSO,event);
											}
											break;

										case CAMEROA_REP_PUIPELTIER:				// retour de la puissance des peltiers en %
											{
												QString rep1;	// Premiere valeur de la reponse en retour
												QString rep2;	// Deuxieme valeur de la reponse en retour

												rep1=ValReponse.section(" ",0,0);		// Date de la mesure au format ISO
												rep2=ValReponse.section(" ",1,1);		// puissance

												CEventSupervCLIMSO_PuiPeltier *event=new CEventSupervCLIMSO_PuiPeltier(id,QDateTime::fromString(rep1,Qt::ISODate),rep2.toDouble());
												QApplication::postEvent(FPSupervCLIMSO,event);
											}
											break;
									}
								}
								
							}
							else
							{
								// Il y a une erreur ou la connexion est perdue...
								//
								SortirBoucleER=true;
							}
						}
						else
						{
/* PAS LA PEINE CAR RAFRAICHISSEMENT DE LA TEMPERATURE ET PUISSANCE PELTIER TOUTES LES SECONDES
							// Il n'y a rien a lire du serveur depuis 1s donc on peut envoyer un "es-tu vivant ?" au serveur
							//  pour eviter un timeout. Le serveur CamerOA ferme automatiquement la connexion si elle est incactive.
							//
							if( Client->EnvoyerChaineBIO(CmdClientCamerOA[CAMEROA_CMD_EN_ATTENTE]+"\n") <= 0 )
							{
								// Erreur lors de l'emission, la liaison n'est pas correcte, on peut refermer cette connexion
								//
								std::cerr << "ProcessusLegerClientCommandeCamerOA " << id << ": run(): ERREUR: Impossible d'envoyer la chaine es-tu en vie ?." << std::endl;

								SortirBoucleER=true;
							}

							msleep(500);	// On patiente pour ne pas emballer la liaison
*/						}

						// Si on demande une deconnexion du serveur
						//
						if( !DrapeauConnexion )
						{
							// On demande la deconnexion au serveur
							//
							MutexEnvChaineBIO_CamerOA[id].lock();

							if( Client->EnvoyerChaineBIO(CmdDeconnexion) <= 0 )
							{
								// Erreur lors de l'emission, la liaison n'est pas correcte, on peut refermer cette connexion
								//
								std::cerr << "ProcessusLegerClientCommandeCamerOA " << id << ": run(): ERREUR: Impossible d'envoyer la commande de deconnexion." << std::endl;
							}
							else
							{
								Chaine_log="Déconnexion engagée de CamerOA["+InstrumentCLIMSO[id]+"] canal des commandes.";
								CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(Chaine_log);
								QApplication::postEvent(FPSupervCLIMSO,event);

								sleep(2);				// On attend un peu
							}

							MutexEnvChaineBIO_CamerOA[id].unlock();

							SortirBoucleER=true;
						}

						if( DrapeauDemandeTerminaison ) SortirBoucleER=true;

					} while( !SortirBoucleER );

					// On peut fermer la connexion avec le serveur CamerOA
					//
					Client->Fermer();
				}
			}
			else
			{
				// La connexion sur le serveur CamerOA a echouee
				//
				// On patientera un peu avant de retenter une connexion
				//
				Chaine_log="*** Echec de connexion sur CamerOA["+InstrumentCLIMSO[id]+"] canal des commandes ***";
				CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(Chaine_log);
				QApplication::postEvent(FPSupervCLIMSO,event);
			}
		}

		if( DrapeauDemandeTerminaison ) Sortir=true; else sleep(TEMPS_ATTENTE_AVANT_NOUVELLE_TENTATIVE_CONNEXION);

	} while( !Sortir );
}



//--------------------------------------------------------------------------------------------------------------------------------

// Constructeur du processus leger client non chiffre du canal des donnees d'un CamerOA
//
// CE:	On passe le numero id de ce processus leger ;
//
//		On passe un pointeur vers la fenetre principale SupervCLIMSO ;
//
//		On passe l'adresse IP du serveur CamerOA en valeur host (0x________) ;
//
//		On passe le port du serveur CamerOA en valeur host (0x____) ;
//
//		On passe le timeout en secondes pour la tentative d'ecriture de donnees dans la socket ;
//
//		On passe le timeout en secondes pour la tentative de lecture de donnees dans la socket ;
//
//	CS:	-
ProcessusLegerClientDonneesCamerOA::ProcessusLegerClientDonneesCamerOA(int pid,SupervCLIMSO *pfp,uint32_t pAdresse,uint16_t pPort,int pTimeoutSocketPut,int pTimeoutSocketGet)
{
	// Initialisation des variables
	//
	id=pid;

	DrapeauDemandeTerminaison=false;
	DrapeauConnexion=false;

	EnTeteI.tx=EnTeteI.ty=0;
	TrameI.resize(0);

	EnTeteIC.tx=EnTeteIC.ty=0;
	TrameIC.resize(0);

	EnTeteICH.tx=EnTeteICH.ty=0;
	TrameICH.resize(0);

	EnTeteICV.tx=EnTeteICV.ty=0;
	TrameICV.resize(0);

	// Instanciation de l'objet client non chiffre
	//
	if( (Client=new (std::nothrow) PointCommClientNonChiffre(false,pAdresse,pPort,pTimeoutSocketPut,pTimeoutSocketGet)) == NULL )
	{
		std::cerr << "ProcessusLegerClientDonneesCamerOA " << id << ": ERREUR: Impossible de creer l'objet client non chiffre." << std::endl;
	}

	// Pointeur vers l'application parent SupervCLIMSO
	//
	FPSupervCLIMSO=pfp;
}


// Destructeur du processus leger client non chiffre du canal des donnees d'un CamerOA
//
ProcessusLegerClientDonneesCamerOA::~ProcessusLegerClientDonneesCamerOA()
{
	// Si le thread est encore actif et donc que le serveur ne s'est pas termine normalement
	//
	if( running() )
	{
		terminate();	// On termine le thread de maniere brutale
	}

	// On supprime l'objet client
	//
	delete Client;
}


// Fonction de la demande de terminaison propre du processus leger du canal des donnees d'un CamerOA
//
void ProcessusLegerClientDonneesCamerOA::DemandeTerminaison(void)
{
	DrapeauDemandeTerminaison=true;

	// La socket passe en mode non bloquant
	//
	Client->SocketNonBloquante();
}


// Fonction d'autorisation de la connexion a un serveur CamerOA
//
void ProcessusLegerClientDonneesCamerOA::ConnexionAutorisee(void)
{
	DrapeauConnexion=true;
}


// Fonction de non autorisation de connexion a un serveur CamerOA
//
void ProcessusLegerClientDonneesCamerOA::ConnexionNonAutorisee(void)
{
	DrapeauConnexion=false;
}


// Surcharge de la methode run() qui contient le code d'execution du thread du client non chiffre du canal des donnees d'un CamerOA
//
// ATTENTION : QT3 n'est pas thread-safe (c'est a dire que les fonctions ne peuvent pas etre appellees par plusieurs threads a la fois).
//		Les widgets doivent etre modifies uniquement par l'application maitre qui gere la boucle evenementielle. Donc un thread
//		qui doit modifier un widget de l'application doit communiquer par un evenement particulier QCustomEvent via la fontion
//		thread-safe QApplication::postEvent(). Il ne doit pas modifier directement le widget sinon l'application plantera.
//
void ProcessusLegerClientDonneesCamerOA::run()
{
	int Sortir=false;	// Drapeau d'indication de sortie de la boucle de traitement des commandes
	QString Chaine_log;	// Pour composer une chaine de log
	Chaine_log.reserve(TAILLE_MINI_CHAINE_LOG);

	// On capture un element du semaphore de synchronisation
	//
	SemaphoreSyncLancementThreadSupervCLIMSO++;


	// Boucle de connexion au serveur CamerOA
	//
	do
	{
		// Si on a l'autorisation pour se connecter
		//
		if( DrapeauConnexion )
		{
			// On tente une connexion sur le serveur CamerOA
			//
			if( Client->Connecter() )
			{
				// La connexion sur le serveur CamerOA a reussie
				//
				int SortirBoucleER=false;										// Drapeau pour sortir ou non de la boucle emission/reception des donnees
				char cmagti[TAILLE_CH_MAG_ENTDONCAMEROA]=CH_MAG_ENTDONCAMEROA;	// Chaine magique depart trame image

				// Emission d'un log
				//
				Chaine_log="Connexion à CamerOA["+InstrumentCLIMSO[id]+"] canal des données : ok.";
				CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(Chaine_log);
				QApplication::postEvent(FPSupervCLIMSO,event);

				// On entre dans la boucle emission/reception des donnees
				//
				do
				{
					char octet;		// Un octet

					// Si il est possible de lire des donnees sur la socket dans la seconde qui suit
					//
					if( Client->PossibleLireDonneesSocket(1000) )
					{
						if( Client->LireDonneesSocket(&octet,1) > 0 )
						{
							// Si le caractere lu correspond au premier caractere de la chaine magique d'une trame image CamerOA
							//
							if( octet == cmagti[0] )
							{
								int nb_cokcm=1;	// Nombre de caracteres a la suite identifies comme la chaine magique de depart de trame

								// On essaye d'identifier la chaine magique de depart de trame image
								//
								while( nb_cokcm < TAILLE_CH_MAG_ENTDONCAMEROA )
								{
									// Si on peut lire immediatement un caractere
									//
									if( Client->PossibleLireDonneesSocket(0) )
									{
										if( Client->LireDonneesSocket(&octet,1) > 0 )
										{
											// Si le caractere courant correspond bien a la suite dans la chaine magique
											//
											if( octet == cmagti[nb_cokcm] )
											{
												// L'octet courant correspond a la chaine magique
												//
												nb_cokcm++;
											}
											else break;	// Sinon on arrete la car ce n'est pas la chaine magique de depart de trame
										}
										else
										{
											// Il y a une erreur ou la connexion est perdue...
											//
											SortirBoucleER=true;
										}
									}
									else break;
								}

								// Si la chaine magique de depart de trame image est reperee dans le flux avec tous ses caracteres
								//
								if( nb_cokcm == TAILLE_CH_MAG_ENTDONCAMEROA )
								{
									struct EnteteTrameDonneesCamerOA EnTeteTrame;	// Structure de donnees de l'entete a charger

									// Pas la peine de remplir completement le membre de la chaine magique
									//
									EnTeteTrame.chaine_magique[0]=0;

									// On attend le chargement de la suite de l'entete de la trame image qui contiendra
									//  tous les renseignements. Si la lecture n'est pas complete alors la trame de donnees courante
									//  sera ignoree jusqu'a la dectection d'un nouveau debut de trame image.
									//
									if( Client->LireNbDonneesSocket(((char *) &EnTeteTrame)+TAILLE_CH_MAG_ENTDONCAMEROA,sizeof(struct EnteteTrameDonneesCamerOA)-TAILLE_CH_MAG_ENTDONCAMEROA) == (sizeof(struct EnteteTrameDonneesCamerOA)-TAILLE_CH_MAG_ENTDONCAMEROA) )
									{
										int ttramep=0;			// Nombre de pixels de la trame courante
										int ttrameo=0;			// Nombre d'octets de la trame courante
										int nborecus=0;			// Nombre d'octets recus

										// Variables de parcours de l'image pour son orientation rapide correcte
										unsigned int x1=0;		// Colonne 1
//										unsigned int x2=0;		// Colonne 2
										unsigned int y1=0;		// Ligne 1
										unsigned int y2=0;		// Ligne 2
										unsigned int iy1=0;		// Indice du pixel sur la ligne y1
										unsigned int iy2=0;		// Indice du pixel sur la ligne y2
										unsigned short memo=0;	// Variable de memorisation pour swapping

										// Nombre de pixels de la trame courante
										//
										ttramep=(int) (EnTeteTrame.tx*EnTeteTrame.ty);

										// Nombre d'octets de la trame courante
										//
										ttrameo=ttramep*sizeof(unsigned short);

										// On attend le chargement des donnees des pixels de la trame image
										//
										switch( EnTeteTrame.type_trame )
										{
											case TRAME_IMAGE:
												MutexTrameImage.lock();

												if( EnTeteI.tx != EnTeteTrame.tx || EnTeteI.ty != EnTeteTrame.ty ) TrameI.resize(ttramep);

												EnTeteI=EnTeteTrame;

												if( (nborecus=Client->LireNbDonneesSocket(((char *) &TrameI[0]),ttrameo)) != ttrameo )
												{
													std::cerr << "ProcessusLegerClientDonneesCamerOA " << id << ": run(): ERREUR: Impossible de recevoir la totalite des donnees de la trame image courante " << nborecus << "/" << ttrameo << "." << std::endl;
												}

												// Orientation correcte de l'image
												//
												for( y1=0; y1 < (EnTeteTrame.ty/2); y1++ )
												{
													// y1 = ligne 1
													// indice pixel courant ligne 1
													//
													iy1=y1*EnTeteTrame.tx;

													// y2 = ligne 2
													//
													y2=EnTeteTrame.ty-1-y1;

													// indice pixel courant ligne 2
													//
													iy2=y2*EnTeteTrame.tx;

													// On inverse les pixels de la ligne 1 avec ceux de la ligne 2
													//
													for( x1=0; x1 < EnTeteTrame.tx; x1++ )
													{
														memo=TrameI[iy1];
														TrameI[iy1]=TrameI[iy2];
														TrameI[iy2]=memo;

														// On avance sur la ligne
														//
														iy1++;
														iy2++;
													}
												}

												MutexTrameImage.unlock();

												// On communique l'evenement de reception d'une nouvelle image au processus de l'interface
												//
												{
													CEventSupervCLIMSO_NouvImage *event=new CEventSupervCLIMSO_NouvImage(id);

													QApplication::postEvent(FPSupervCLIMSO,event);
												}
												break;

											case TRAME_CENTRAGE_IMAGE:
												MutexTrameImageC.lock();

												if( EnTeteIC.tx != EnTeteTrame.tx || EnTeteIC.ty != EnTeteTrame.ty ) TrameIC.resize(ttramep);

												EnTeteIC=EnTeteTrame;

												if( (nborecus=Client->LireNbDonneesSocket(((char *) &TrameIC[0]),ttrameo)) != ttrameo )
												{
													std::cerr << "ProcessusLegerClientDonneesCamerOA " << id << ": run(): ERREUR: Impossible de recevoir la totalite des donnees de la trame image de centrage courante " << nborecus << "/" << ttrameo << "." << std::endl;
												}

												// Orientation correcte de l'image
												//
												for( y1=0; y1 < (EnTeteTrame.ty/2); y1++ )
												{
													// y1 = ligne 1
													// indice pixel courant ligne 1
													//
													iy1=y1*EnTeteTrame.tx;

													// y2 = ligne 2
													//
													y2=EnTeteTrame.ty-1-y1;

													// indice pixel courant ligne 2
													//
													iy2=y2*EnTeteTrame.tx;

													// On inverse les pixels de la ligne 1 avec ceux de la ligne 2
													//
													for( x1=0; x1 < EnTeteTrame.tx; x1++ )
													{
														memo=TrameIC[iy1];
														TrameIC[iy1]=TrameIC[iy2];
														TrameIC[iy2]=memo;

														// On avance sur la ligne
														//
														iy1++;
														iy2++;
													}
												}

												MutexTrameImageC.unlock();

												// On communique l'evenement de reception d'une nouvelle image de centrage au processus de
												//  l'interface
												//
												{
													CEventSupervCLIMSO_NouvImageCentrage *event=new CEventSupervCLIMSO_NouvImageCentrage(id);

													QApplication::postEvent(FPSupervCLIMSO,event);
												}
												break;

											case TRAME_CENTRAGE_H:
												MutexTrameImageCH.lock();

												if( EnTeteICH.tx != EnTeteTrame.tx || EnTeteICH.ty != EnTeteTrame.ty ) TrameICH.resize(ttramep);

												EnTeteICH=EnTeteTrame;

												if( (nborecus=Client->LireNbDonneesSocket(((char *) &TrameICH[0]),ttrameo)) != ttrameo )
												{
													std::cerr << "ProcessusLegerClientDonneesCamerOA " << id << ": run(): ERREUR: Impossible de recevoir la totalite des donnees de la trame image de centrage horizontal courante " << nborecus << "/" << ttrameo << "." << std::endl;
												}

												// Orientation correcte de l'image
												//
												for( y1=0; y1 < (EnTeteTrame.ty/2); y1++ )
												{
													// y1 = ligne 1
													// indice pixel courant ligne 1
													//
													iy1=y1*EnTeteTrame.tx;

													// y2 = ligne 2
													//
													y2=EnTeteTrame.ty-1-y1;

													// indice pixel courant ligne 2
													//
													iy2=y2*EnTeteTrame.tx;

													// On inverse les pixels de la ligne 1 avec ceux de la ligne 2
													//
													for( x1=0; x1 < EnTeteTrame.tx; x1++ )
													{
														memo=TrameICH[iy1];
														TrameICH[iy1]=TrameICH[iy2];
														TrameICH[iy2]=memo;

														// On avance sur la ligne
														//
														iy1++;
														iy2++;
													}
												}

												MutexTrameImageCH.unlock();

												// On communique l'evenement de reception d'une nouvelle image de centrage horizontal
												//  au processus de l'interface
												//
												{
													CEventSupervCLIMSO_NouvImageCentrageH *event=new CEventSupervCLIMSO_NouvImageCentrageH(id);

													QApplication::postEvent(FPSupervCLIMSO,event);
												}
												break;

											case TRAME_CENTRAGE_V:
												MutexTrameImageCV.lock();

												if( EnTeteICV.tx != EnTeteTrame.tx || EnTeteICV.ty != EnTeteTrame.ty ) TrameICV.resize(ttramep);

												EnTeteICV=EnTeteTrame;

												if( (nborecus=Client->LireNbDonneesSocket(((char *) &TrameICV[0]),ttrameo)) != ttrameo )
												{
													std::cerr << "ProcessusLegerClientDonneesCamerOA " << id << ": run(): ERREUR: Impossible de recevoir la totalite des donnees de la trame image de centrage vertical courante. " << nborecus << "/" << ttrameo << "." << std::endl;
												}

												// Orientation correcte de l'image
												//
												for( y1=0; y1 < (EnTeteTrame.ty/2); y1++ )
												{
													// y1 = ligne 1
													// indice pixel courant ligne 1
													//
													iy1=y1*EnTeteTrame.tx;

													// y2 = ligne 2
													//
													y2=EnTeteTrame.ty-1-y1;

													// indice pixel courant ligne 2
													//
													iy2=y2*EnTeteTrame.tx;

													// On inverse les pixels de la ligne 1 avec ceux de la ligne 2
													//
													for( x1=0; x1 < EnTeteTrame.tx; x1++ )
													{
														memo=TrameICV[iy1];
														TrameICV[iy1]=TrameICV[iy2];
														TrameICV[iy2]=memo;

														// On avance sur la ligne
														//
														iy1++;
														iy2++;
													}
												}

												MutexTrameImageCV.unlock();

												// On communique l'evenement de reception d'une nouvelle image de centrage vertical
												//  au processus de l'interface
												//
												{
													CEventSupervCLIMSO_NouvImageCentrageV *event=new CEventSupervCLIMSO_NouvImageCentrageV(id);

													QApplication::postEvent(FPSupervCLIMSO,event);
												}
												break;
										}
									}
									else
									{
										std::cerr << "ProcessusLegerClientDonneesCamerOA " << id << ": run(): ERREUR: Impossible de recevoir l'entete de la trame image courante complete." << std::endl;
									}
								}
							}
						}
						else
						{
							// Il y a une erreur ou la connexion est perdue...
							//
							SortirBoucleER=true;
						}
					}
					else
					{
						// On peut envoyer un "es-tu vivant ?" au serveur pour eviter un timeout.
						//  Le serveur CamerOA ferme automatiquement la connexion si elle est inactive.
						//
						if( Client->EnvoyerChaineSocket("#") <= 0 )
						{
							// Erreur lors de l'emission, la liaison n'est pas correcte, on peut refermer cette connexion
							//
							std::cerr << "ProcessusLegerClientDonneesCamerOA " << id << ": run(): ERREUR: Impossible d'envoyer l'octet es-tu en vie ?." << std::endl;

							SortirBoucleER=true;
						}

						msleep(500);	// On patiente pour ne pas emballer la liaison
					}

					// Si on demande la deconnexion au serveur
					//
					if( !DrapeauConnexion )
					{
						Chaine_log="Déconnexion engagée de CamerOA["+InstrumentCLIMSO[id]+"] canal des données.";
						CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(Chaine_log);
						QApplication::postEvent(FPSupervCLIMSO,event);

						sleep(2);				// On attend un peu

						SortirBoucleER=true;	// On sort de la boucle Emission/Reception et donc provoque la fermeture
					}

					if( DrapeauDemandeTerminaison ) SortirBoucleER=true;

				} while( !SortirBoucleER );

				// On peut fermer la connexion avec le serveur CamerOA
				//
				Client->Fermer();
			}
			else
			{
				// La connexion sur le serveur CamerOA a echouee
				//
				// On patientera un peu avant de retenter une connexion
				//
				Chaine_log="*** Echec de connexion sur CamerOA["+InstrumentCLIMSO[id]+"] canal des données ***";
				CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(Chaine_log);
				QApplication::postEvent(FPSupervCLIMSO,event);
			}
		}

		if( DrapeauDemandeTerminaison ) Sortir=true; else sleep(TEMPS_ATTENTE_AVANT_NOUVELLE_TENTATIVE_CONNEXION);

	} while( !Sortir );
}



//--------------------------------------------------------------------------------------------------------------------------------

// Constructeur du processus leger client chiffre du canal de commande d'un TerminOA
//
// CE:	On passe le numero id de ce processus leger ;
//
//		On passe un pointeur vers la fenetre principale SupervCLIMSO ;
//
//		On passe l'adresse IP du serveur TerminOA en valeur host (0x________) ;
//
//		On passe le port du serveur TerminOA en valeur host (0x____) ;
//
//		On passe le timeout en secondes pour la tentative d'ecriture de donnees dans la socket ;
//
//		On passe le timeout en secondes pour la tentative de lecture de donnees dans la socket ;
//
//		On passe true si on veut parametrer la redirection de SIGPIPE (ecriture dans tube ferme) ou false dans le cas contraire ;
//
//		On passe un pointeur sur la fonction C de handler du signal SIGPIPE ;
//
//		On passe un pointeur sur une chaine de char qui contient le mot de passe pour acceder a la cle privee du client SSL
//	 	Ce mot de passe ne doit pas contenir plus de TAILLE_MAX_MDP_CLE_PRIVEE-1 caracteres ;
//
//		On passe un pointeur sur char vers un buffer de stockage du mot de passe pour acceder a la cle privee du client SSL
//	 	Ce buffer doit etre reserve avec TAILLE_MAX_MDP_CLE_PRIVEE elements ;
//
//		On passe un pointeur sur la fonction C appelee par la librairie SSL lors de la demande du mot de passe pour acceder a la cle
//	 	privee du client SSL stockee dans un fichier PEM ;
//
//		On passe un pointeur sur une chaine de char qui contient le chemin complet du fichier PEM du certificat
//		 de l'autorite de certification CA qui a signe les certificats du client ;
//
//		On passe un pointeur sur une chaine de char qui contient le chemin complet du fichier PEM du certificat du client ;
//
//		On passe un pointeur sur une chaine de char qui contient le chemin complet du fichier PEM de la cle privee du client ;
//
// CS:	-
//
ProcessusLegerClientCommandeTerminOA::ProcessusLegerClientCommandeTerminOA(int pid,SupervCLIMSO *pfp,uint32_t pAdresse,uint16_t pPort,int pTimeoutSocketPut,int pTimeoutSocketGet,int pParamSIGPIPE,void (*pFnHandlerSIGPIPE)(int),const char *pMdpClePriveeClient,char *pBuffStockMdpClePriveeClient,int (*pFnMotDePasseClePriveeChiffree)(char*, int, int, void*),const char *pCheminCertificatCA,const char *pCheminCertificatClient,const char *pCheminClePriveeClient)
{
	// Initialisation des variables
	//
	id=pid;

	DrapeauDemandeTerminaison=false;
	DrapeauConnexion=false;

	// Instanciation de l'objet client chiffre
	//
	if( (Client=new (std::nothrow) PointCommClientChiffre(false,pAdresse,pPort,pTimeoutSocketPut,pTimeoutSocketGet,pParamSIGPIPE,pFnHandlerSIGPIPE,pMdpClePriveeClient,pBuffStockMdpClePriveeClient,pFnMotDePasseClePriveeChiffree,pCheminCertificatCA,pCheminCertificatClient,pCheminClePriveeClient)) == NULL )
	{
		std::cerr << "ProcessusLegerClientCommandeTerminOA " << id << ": ERREUR: Impossible de creer l'objet client chiffre." << std::endl;
	}

	// Pointeur vers l'application parent SupervCLIMSO
	//
	FPSupervCLIMSO=pfp;

	// Copie des commandes et reponses dans l'objet pour etre thread safe (bogues avec QString en inter processus)
	//
	for( int i=0; i < NB_CMD_CLIENT_TERMINOA; i++ ) CmdClientTerminOA[i]=ListeCmdClientTerminOA[i];
	for( int i=0; i < NB_REP_SERVEUR_TERMINOA; i++ ) RepServeurTerminOA[i]=ListeRepServeurTerminOA[i];

	// Chaines des commandes completes pour eviter les bogues (#0 0x00a1864c in memcpy () from /lib/libc.so.6) lies a QString dans les threads avec +"\n"
	//
	CmdSesame=CmdClientTerminOA[TERMINOA_CMD_SESAMEOUVRETOI]+"\n";
	CmdAttente=CmdClientTerminOA[TERMINOA_CMD_EN_ATTENTE]+"\n";
	CmdDeconnexion=CmdClientTerminOA[TERMINOA_CMD_DECONNEXION]+"\n";
}


// Destructeur du processus leger client chiffre du canal de commande d'un TerminOA
//
ProcessusLegerClientCommandeTerminOA::~ProcessusLegerClientCommandeTerminOA()
{
	// Si le thread est encore actif et donc que le serveur ne s'est pas termine normalement
	//
	if( running() )
	{
		terminate();	// On termine le thread de maniere brutale
	}

	// On supprime l'objet client
	//
	delete Client;
}


// Fonction de la demande de terminaison propre du processus leger du canal de commande d'un TerminOA
//
void ProcessusLegerClientCommandeTerminOA::DemandeTerminaison(void)
{
	DrapeauDemandeTerminaison=true;

	// La socket passe en mode non bloquant
	//
	Client->SocketNonBloquante();
}


// Fonction d'autorisation de la connexion a un serveur TerminOA
//
void ProcessusLegerClientCommandeTerminOA::ConnexionAutorisee(void)
{
	DrapeauConnexion=true;
}


// Fonction de non autorisation de connexion a un serveur TerminOA
//
void ProcessusLegerClientCommandeTerminOA::ConnexionNonAutorisee(void)
{
	DrapeauConnexion=false;
}


// Surcharge de la methode run() qui contient le code d'execution du thread du client chiffre du canal de commande d'un TerminOA
//
// ATTENTION : QT3 n'est pas thread-safe (c'est a dire que les fonctions ne peuvent pas etre appellees par plusieurs threads a la fois).
//		Les widgets doivent etre modifies uniquement par l'application maitre qui gere la boucle evenementielle. Donc un thread
//		qui doit modifier un widget de l'application doit communiquer par un evenement particulier QCustomEvent via la fontion
//		thread-safe QApplication::postEvent(). Il ne doit pas modifier directement le widget sinon l'application plantera.
//
void ProcessusLegerClientCommandeTerminOA::run()
{
	int Sortir=false;	// Drapeau d'indication de sortie de la boucle de traitement des commandes
	QString Chaine_log;					// Pour composer une chaine de log
	Chaine_log.reserve(TAILLE_MINI_CHAINE_LOG);
//	QString ChaineCmd;					// Chaine avec taille minimale pour la composition de commandes afin d'eviter un bogue QString et la rapidite
//	ChaineCmd.reserve(TAILLE_MINI_CHAINE_CMD);


	// On capture un element du semaphore de synchronisation
	//
	SemaphoreSyncLancementThreadSupervCLIMSO++;


	// Boucle de connexion au serveur TerminOA
	//
	do
	{
		// Si on a l'autorisation pour se connecter
		//
		if( DrapeauConnexion )
		{
			// On tente une connexion sur le serveur TerminOA
			//
			if( Client->Connecter() )
			{
				// La connexion sur le serveur TerminOA a reussie
				//
				// On commence par envoyer la chaine secrete d'ouverture aux commandes
				//
				MutexEnvChaineBIO_TerminOA[id].lock();

				if( Client->EnvoyerChaineBIO(CmdSesame) <= 0 )
				{
					MutexEnvChaineBIO_TerminOA[id].unlock();

					// Erreur lors de l'emission, la liaison n'est pas correcte, on peut refermer cette connexion
					//
					std::cerr << "ProcessusLegerClientCommandeTerminOA " << id << ": run(): ERREUR: Impossible d'envoyer la chaine secrete d'ouverture aux commandes." << std::endl;

					Client->Fermer();
				}
				else
				{
					int SortirBoucleER=false;					// Drapeau pour sortir ou non de la boucle emission/reception des commandes
					char LigneRecue[TAILLE_MAXI_CHAINE_BIO+1];	// Ligne de caracteres recu du serveur TerminOA

					MutexEnvChaineBIO_TerminOA[id].unlock();

					// Emission d'un log
					//
					Chaine_log="Connexion à TerminOA["+InstrumentCLIMSO[id]+"] canal des commandes : ok.";
					CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(Chaine_log);
					QApplication::postEvent(FPSupervCLIMSO,event);

					// On entre dans la boucle emission/reception des commandes
					//
					do
					{
						// Si il est possible de lire des donnees sur la socket dans la seconde qui suit
						//
						if( Client->PossibleLireDonneesSocket(1000) )
						{
							if( Client->RecevoirChaineBIO(LigneRecue) > 0 )
							{
								int i=0;					// Indice
								int icmd=0;					// Indice du retour de commande
								QString Ligne;		// La ligne recue dans un QString sans les caracteres speciaux et les espacements multiples
								Ligne.reserve(TAILLE_MINI_CHAINE);

								Ligne="";

								// On coupe la chaine au premier \r ou \n
								//
								// On supprime les espacements multiples  ATTENTION: TRES IMPORTANT POUR QUE QString.section(" ",,) FONCTIONNE CORRECTEMENT
								//
								while( LigneRecue[i] != 0 )
								{
									if( LigneRecue[i] == '\r' ) break;
									if( LigneRecue[i] == '\n' ) break;
									if( LigneRecue[i] != ' ' )
									{
										Ligne+=LigneRecue[i];
									}
									else
									{
										// Le caractere courant est un espacement, on ne l'ajoute pas si le dernier caractere de Ligne est aussi un espacement
										//
										if( Ligne.length() > 0 )
										{
											if( Ligne.right(1) != " " ) Ligne+=LigneRecue[i];
										}
									}
									i++;
								}
//std::cout << "Ligne recue TerminOA propre:" << Ligne << std::endl;

								// Analyse de la ligne recue du serveur TerminOA, recherche du retour de commande
								//
								while( RepServeurTerminOA[icmd] != QString("") && Ligne.left(RepServeurTerminOA[icmd].length()) != RepServeurTerminOA[icmd] ) icmd++;

								// Si on a bien identifie un retour de valeur d'une commande
								//
								if( RepServeurTerminOA[icmd] !=  QString("") )
								{
									QString ValReponse;
									ValReponse.reserve(TAILLE_MINI_CHAINE);
									ValReponse=Ligne.right(Ligne.length()-RepServeurTerminOA[icmd].length());	// Les valeurs de la reponse

									switch( icmd )
									{
										case TERMINOA_REP_OK_IMG_RECUE:		// Le TerminOA signale qu'il a recu une image
											{
												QString rep1;	// Premiere valeur de la reponse en retour
												QString rep2;	// Deuxieme valeur de la reponse en retour
												QString rep3;	// Troisieme valeur de la reponse en retour

												rep1=ValReponse.section(" ",0,0);		// numero de l'image recue depuis le lancement
												rep2=ValReponse.section(" ",1,1);		// taille de l'image recue en octets
												rep3=ValReponse.section(" ",2,2);		// la chaine d'identification de l'image courante

												CEventSupervCLIMSO_ImgRecueTerminOA *event=new CEventSupervCLIMSO_ImgRecueTerminOA(id,rep3);
												QApplication::postEvent(FPSupervCLIMSO,event);
											}
											break;
									}
								}
							}
							else
							{
								// Il y a une erreur ou la connexion est perdue...
								//
								SortirBoucleER=true;
							}
						}
						else
						{
							// Il n'y a rien a lire du serveur depuis 1s donc on peut envoyer un "es-tu vivant ?" au serveur
							//  pour eviter un timeout. Le serveur TerminOA ferme automatiquement la connexion si elle est inactive.
							//
							MutexEnvChaineBIO_TerminOA[id].lock();

							if( Client->EnvoyerChaineBIO(CmdAttente) <= 0 )
							{
								// Erreur lors de l'emission, la liaison n'est pas correcte, on peut refermer cette connexion
								//
								std::cerr << "ProcessusLegerClientCommandeTerminOA " << id << ": run(): ERREUR: Impossible d'envoyer la chaine es-tu en vie ?." << std::endl;

								SortirBoucleER=true;
							}

							MutexEnvChaineBIO_TerminOA[id].unlock();

							msleep(500);	// On patiente pour ne pas emballer la liaison
						}

						// Si on demande une deconnexion du serveur
						//
						if( !DrapeauConnexion )
						{
							// On demande la deconnexion au serveur
							//
							MutexEnvChaineBIO_TerminOA[id].lock();

							if( Client->EnvoyerChaineBIO(CmdDeconnexion) <= 0 )
							{
								// Erreur lors de l'emission, la liaison n'est pas correcte, on peut refermer cette connexion
								//
								std::cerr << "ProcessusLegerClientCommandeTerminOA " << id << ": run(): ERREUR: Impossible d'envoyer la commande de deconnexion." << std::endl;
							}
							else
							{
								Chaine_log="Déconnexion engagée de TerminOA["+InstrumentCLIMSO[id]+"] canal des commandes.";
								CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(Chaine_log);
								QApplication::postEvent(FPSupervCLIMSO,event);

								sleep(2);				// On attend un peu
							}

							MutexEnvChaineBIO_TerminOA[id].unlock();

							SortirBoucleER=true;
						}

						if( DrapeauDemandeTerminaison ) SortirBoucleER=true;

					} while( !SortirBoucleER );

					// On peut fermer la connexion avec le serveur TerminOA
					//
					Client->Fermer();
				}
			}
			else
			{
				// La connexion sur le serveur TerminOA a echouee
				//
				// On patientera un peu avant de retenter une connexion
				//
				Chaine_log="*** Echec de connexion sur TerminOA["+InstrumentCLIMSO[id]+"] canal des commandes ***";
				CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(Chaine_log);
				QApplication::postEvent(FPSupervCLIMSO,event);
			}
		}

		if( DrapeauDemandeTerminaison ) Sortir=true; else sleep(TEMPS_ATTENTE_AVANT_NOUVELLE_TENTATIVE_CONNEXION);

	} while( !Sortir );
}



//--------------------------------------------------------------------------------------------------------------------------------

// Constructeur du processus leger client non chiffre du canal des donnees d'un TerminOA
//
// CE:	On passe le numero id de ce processus leger ;
//
//		On passe un pointeur vers la fenetre principale SupervCLIMSO ;
//
//		On passe l'adresse IP du serveur TerminOA en valeur host (0x________) ;
//
//		On passe le port du serveur TerminOA en valeur host (0x____) ;
//
//		On passe le timeout en secondes pour la tentative d'ecriture de donnees dans la socket ;
//
//		On passe le timeout en secondes pour la tentative de lecture de donnees dans la socket ;
//
//	CS:	-
ProcessusLegerClientDonneesTerminOA::ProcessusLegerClientDonneesTerminOA(int pid,SupervCLIMSO *pfp,uint32_t pAdresse,uint16_t pPort,int pTimeoutSocketPut,int pTimeoutSocketGet)
{
	// Initialisation des variables
	//
	id=pid;

	DrapeauDemandeTerminaison=false;
	DrapeauConnexion=false;

	// Instanciation de l'objet client non chiffre
	//
	if( (Client=new (std::nothrow) PointCommClientNonChiffre(false,pAdresse,pPort,pTimeoutSocketPut,pTimeoutSocketGet)) == NULL )
	{
		std::cerr << "ProcessusLegerClientDonneesTerminOA " << id << ": ERREUR: Impossible de creer l'objet client non chiffre." << std::endl;
	}
	MutexEmission.unlock();

	// Pointeur vers l'application parent SupervCLIMSO
	//
	FPSupervCLIMSO=pfp;
}


// Destructeur du processus leger client non chiffre du canal des donnees d'un TerminOA
//
ProcessusLegerClientDonneesTerminOA::~ProcessusLegerClientDonneesTerminOA()
{
	// Si le thread est encore actif et donc que le serveur ne s'est pas termine normalement
	//
	if( running() )
	{
		terminate();	// On termine le thread de maniere brutale
	}

	// On supprime l'objet client
	//
	delete Client;
}


// Fonction de la demande de terminaison propre du processus leger du canal des donnees d'un TerminOA
//
void ProcessusLegerClientDonneesTerminOA::DemandeTerminaison(void)
{
	DrapeauDemandeTerminaison=true;

	// La socket passe en mode non bloquant
	//
	Client->SocketNonBloquante();
}


// Fonction d'autorisation de la connexion a un serveur TerminOA
//
void ProcessusLegerClientDonneesTerminOA::ConnexionAutorisee(void)
{
	DrapeauConnexion=true;
}


// Fonction de non autorisation de connexion a un serveur TerminOA
//
void ProcessusLegerClientDonneesTerminOA::ConnexionNonAutorisee(void)
{
	DrapeauConnexion=false;
}


// Surcharge de la methode run() qui contient le code d'execution du thread du client non chiffre du canal des donnees d'un TerminOA
//
// ATTENTION : QT3 n'est pas thread-safe (c'est a dire que les fonctions ne peuvent pas etre appellees par plusieurs threads a la fois).
//		Les widgets doivent etre modifies uniquement par l'application maitre qui gere la boucle evenementielle. Donc un thread
//		qui doit modifier un widget de l'application doit communiquer par un evenement particulier QCustomEvent via la fontion
//		thread-safe QApplication::postEvent(). Il ne doit pas modifier directement le widget sinon l'application plantera.
//
void ProcessusLegerClientDonneesTerminOA::run()
{
	int Sortir=false;	// Drapeau d'indication de sortie de la boucle de traitement des commandes
	QString Chaine_log;	// Pour composer une chaine de log
	Chaine_log.reserve(TAILLE_MINI_CHAINE_LOG);

	// On capture un element du semaphore de synchronisation
	//
	SemaphoreSyncLancementThreadSupervCLIMSO++;


	// Boucle de connexion au serveur TerminOA
	//
	do
	{
		// Si on a l'autorisation pour se connecter
		//
		if( DrapeauConnexion )
		{
			// On tente une connexion sur le serveur TerminOA
			//
			if( Client->Connecter() )
			{
				// La connexion sur le serveur TerminOA a reussie
				//
				int SortirBoucleER=false;					// Drapeau pour sortir ou non de la boucle emission/reception des donnees

				// Emission d'un log
				//
				Chaine_log="Connexion à TerminOA["+InstrumentCLIMSO[id]+"] canal des données : ok.";
				CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(Chaine_log);
				QApplication::postEvent(FPSupervCLIMSO,event);

				// On entre dans la boucle emission/reception des donnees
				//
				do
				{
					char octet;		// Un octet

					// Si il est possible de lire des donnees sur la socket dans la seconde qui suit
					//
					if( Client->PossibleLireDonneesSocket(1000) )
					{
						if( Client->LireDonneesSocket(&octet,1) > 0 )
						{
//std::cout << QChar(octet) ;
						}
						else
						{
							// Il y a une erreur ou la connexion est perdue...
							//
							SortirBoucleER=true;
						}
					}
					else
					{
						// On peut envoyer un "es-tu vivant ?" au serveur pour eviter un timeout.
						//  Le serveur TerminOA ferme automatiquement la connexion si elle est inactive.
						//
						MutexEmission.lock();

						if( Client->EnvoyerChaineSocket("#") <= 0 )
						{
							// Erreur lors de l'emission, la liaison n'est pas correcte, on peut refermer cette connexion
							//
							std::cerr << "ProcessusLegerClientDonneesTerminOA " << id << ": run(): ERREUR: Impossible d'envoyer l'octet es-tu en vie ?." << std::endl;

							SortirBoucleER=true;
						}

						MutexEmission.unlock();

						msleep(500);	// On patiente pour ne pas emballer la liaison
					}

					// Si on demande la deconnexion au serveur
					//
					if( !DrapeauConnexion )
					{
						Chaine_log="Déconnexion engagée de TerminOA["+InstrumentCLIMSO[id]+"] canal des données.";
						CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(Chaine_log);
						QApplication::postEvent(FPSupervCLIMSO,event);

						sleep(2);				// On attend un peu

						SortirBoucleER=true;	// On sort de la boucle Emission/Reception et donc provoque la fermeture
					}

					if( DrapeauDemandeTerminaison ) SortirBoucleER=true;

				} while( !SortirBoucleER );

				// On peut fermer la connexion avec le serveur TerminOA
				//
				Client->Fermer();
			}
			else
			{
				// La connexion sur le serveur TerminOA a echouee
				//
				// On patientera un peu avant de retenter une connexion
				//
				Chaine_log="*** Echec de connexion sur TerminOA["+InstrumentCLIMSO[id]+"] canal des données ***";
				CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(Chaine_log);
				QApplication::postEvent(FPSupervCLIMSO,event);
			}
		}

		if( DrapeauDemandeTerminaison ) Sortir=true; else sleep(TEMPS_ATTENTE_AVANT_NOUVELLE_TENTATIVE_CONNEXION);

	} while( !Sortir );
}



//--------------------------------------------------------------------------------------------------------------------------------

// Constructeur du processus leger client non chiffre vers le serveur des temperatures
//
// CE:	On passe un pointeur vers la fenetre principale SupervCLIMSO ;
//
//		On passe l'adresse IP du serveur des temperatures en valeur host (0x________) ;
//
//		On passe le port du serveur des temperatures en valeur host (0x____) ;
//
//		On passe le timeout en secondes pour la tentative d'ecriture de donnees dans la socket ;
//
//		On passe le timeout en secondes pour la tentative de lecture de donnees dans la socket ;
//
//	CS:	-
ProcessusLegerClientTemperatures::ProcessusLegerClientTemperatures(SupervCLIMSO *pfp,uint32_t pAdresse,uint16_t pPort,int pTimeoutSocketPut,int pTimeoutSocketGet)
{
	// Initialisation des variables
	//
	DrapeauDemandeTerminaison=false;
	DrapeauConnexion=false;

	// Initialisation de la temperature sur les sondes
	//
	for( int i=0; i < NB_SONDES_TEMPERATURE; i++) T[i]=TEMPERATURE_NON_CONNUE;

	PremierRafraichissement=true;

	// Instanciation de l'objet client non chiffre
	//
	if( (Client=new (std::nothrow) PointCommClientNonChiffre(false,pAdresse,pPort,pTimeoutSocketPut,pTimeoutSocketGet)) == NULL )
	{
		std::cerr << "ProcessusLegerClientTemperatures: ERREUR: Impossible de creer l'objet client non chiffre." << std::endl;
	}

	// Pointeur vers l'application parent SupervCLIMSO
	//
	FPSupervCLIMSO=pfp;
}


// Destructeur du processus leger client non chiffre vers le serveur des temperatures
//
ProcessusLegerClientTemperatures::~ProcessusLegerClientTemperatures()
{
	// Si le thread est encore actif et donc que le serveur ne s'est pas termine normalement
	//
	if( running() )
	{
		terminate();	// On termine le thread de maniere brutale
	}

	// On supprime l'objet client
	//
	delete Client;
}


// Fonction de la demande de terminaison propre du processus leger client non chiffre vers le serveur des temperatures
//
void ProcessusLegerClientTemperatures::DemandeTerminaison(void)
{
	DrapeauDemandeTerminaison=true;

	// La socket passe en mode non bloquant
	//
	Client->SocketNonBloquante();
}


// Fonction d'autorisation de la connexion au serveur des temperatures
//
void ProcessusLegerClientTemperatures::ConnexionAutorisee(void)
{
	DrapeauConnexion=true;
}


// Fonction de non autorisation de connexion au serveur des temperatures
//
void ProcessusLegerClientTemperatures::ConnexionNonAutorisee(void)
{
	DrapeauConnexion=false;
}


// Surcharge de la methode run() qui contient le code d'execution du thread du client non chiffre vers le serveur des temperatures
//
// ATTENTION : QT3 n'est pas thread-safe (c'est a dire que les fonctions ne peuvent pas etre appellees par plusieurs threads a la fois).
//		Les widgets doivent etre modifies uniquement par l'application maitre qui gere la boucle evenementielle. Donc un thread
//		qui doit modifier un widget de l'application doit communiquer par un evenement particulier QCustomEvent via la fontion
//		thread-safe QApplication::postEvent(). Il ne doit pas modifier directement le widget sinon l'application plantera.
//
void ProcessusLegerClientTemperatures::run()
{
	int Sortir=false;	// Drapeau d'indication de sortie de la boucle de traitement des commandes
	QString Chaine_log;	// Pour composer une chaine de log
	Chaine_log.reserve(TAILLE_MINI_CHAINE_LOG);

	// On capture un element du semaphore de synchronisation
	//
	SemaphoreSyncLancementThreadSupervCLIMSO++;


	// Boucle de connexion au serveur des temperatures
	//
	do
	{
		// Si on a l'autorisation pour se connecter
		//
		if( DrapeauConnexion )
		{
			// On tente une connexion sur le serveur des temperatures
			//
			if( Client->Connecter() )
			{
				//
				// La connexion sur le serveur des temperatures a reussie
				//
				// ATTENTION: Web-IO Thermometer FERME AUTOMATIQUEMENT LA SOCKET APRES LA REQUETE
				//
				int SortirBoucleR=false;					// Drapeau pour sortir ou non de la boucle reception des donnees

				if( Client->EnvoyerChaineSocket("GET /Single\n") <= 0 )
				{
					// Erreur lors de l'emission, la liaison n'est pas correcte, on peut refermer cette connexion
					//
					std::cerr << "ProcessusLegerClientTemperatures: run(): ERREUR: Impossible d'envoyer la commande de requete des temperatures." << std::endl;

					SortirBoucleR=true;
				}

				if( !SortirBoucleR )
				{
					// On entre dans la boucle reception des donnees
					//
					char octet;		// Un octet

					// Si il est possible de lire des donnees sur la socket dans la seconde qui suit
					//
					if( Client->PossibleLireDonneesSocket(1000) )
					{
						int Longueur=0;					// Longueur de la reponse du serveur des temperatures en octets
						QString ChaineReponse;	// Chaine reponse du serveur des temperatures
						ChaineReponse.reserve(TAILLE_MINI_CHAINE);

						ChaineReponse="";

						do
						{
							if( Client->LireDonneesSocket(&octet,1) > 0 )
							{
								if( octet != '\n' ) ChaineReponse+=QChar(octet);
								Longueur++;
							}
							else
							{
								// Il y a une erreur ou la connexion est perdue...
								//
								SortirBoucleR=true;
							}
						} while( octet != '\n' && Longueur < 256 && !SortirBoucleR );

//std::cout << "Chaine:" << ChaineReponse << std::endl;

						// S'il s'agit bien d'une reponse du Web-IO Thermometer
						//
						if( ChaineReponse.section(";",1,1) == "W&T Web-IO Thermometer" )
						{
							// On consigne l'heure de la prise de temperature
							//
							t_UT=QDateTime::currentDateTime(Qt::UTC);

							// Analyse de la chaine retournee
							//
							for( int i=0; i < NB_SONDES_TEMPERATURE; i++ )
							{
								QString sc;
								sc.reserve(TAILLE_MINI_CHAINE);
								sc=ChaineReponse.section(";",i+2,i+2);		// Chaque temperature sont separees par des ";"

								// Si une sonde PT n'est pas branchee
								//

//std::cout << sc << std::endl;

								if( sc[0] == QChar('-') && sc[1] == QChar('-') )
								{
									T[i]=TEMPERATURE_NON_CONNUE;
								}
								else
								{
									uint p;								// Indice du premier caractere different d'un chiffre ou "-" ou ","

									for( p=0; p < sc.length(); p++ )
									{
										if( sc.at(p) != ',' && sc.at(p) != '-' ) if( sc.at(p) < '0' || sc.at(p) > '9' ) break;
									}
									sc=sc.left(p);						// On coupe la chaine de la valeur au premier caractere ne faisant pas partie de la valeur

									sc.replace(',',".",true);			// On remplace la "," par un "." pour que la fonction toDouble() fonctionne

									T[i]=sc.toDouble();
								}
							}

							CEventSupervCLIMSO_NouvTemperatures *event=new CEventSupervCLIMSO_NouvTemperatures();
							QApplication::postEvent(FPSupervCLIMSO,event);
						}
					}
				}

				// On peut fermer la connexion avec le serveur des temperatures
				//
				// ATTENTION: Web-IO Thermometer L'A FERMEE AUTOMATIQUEMENT APRES LA REQUETE
				//
				Client->Fermer();
			}
			else
			{
				// La connexion au serveur des temperatures a echouee
				//
				// On patientera un peu avant de retenter une connexion
				//
				Chaine_log="*** Echec de la connexion au serveur des températures ***";
				CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(Chaine_log);
				QApplication::postEvent(FPSupervCLIMSO,event);
			}

			// On ne permet plus la connexion au serveur des temperatures SupervCLIMSO devra la rearmer !!!
			//
			ConnexionNonAutorisee();
		}

		if( DrapeauDemandeTerminaison ) Sortir=true; else sleep(TEMPS_ATTENTE_AVANT_NOUVELLE_TENTATIVE_CONNEXION);

	} while( !Sortir );
}


//--------------------------------------------------------------------------------------------------------------------------------

// Constructeur du processus leger d'une liste d'acquisitions d'images sur C1
//
// CE:	On passe un pointeur vers la fenetre principale SupervCLIMSO ;
//
//		On passe un pointeur vers le processus leger CamerOA associe a C1 ;
//
// CS:	-
//
ProcessusLegerListeAcquisitionsC1::ProcessusLegerListeAcquisitionsC1(SupervCLIMSO *pfp,ProcessusLegerClientCommandeCamerOA *pcam)
{
	// Initialisation des variables
	//
	DrapeauDemandeTerminaison=false;
	DrapeauDemandeAcquisitions=false;

	// Pointeur vers l'application parent SupervCLIMSO
	//
	FPSupervCLIMSO=pfp;

	// Pointeur vers processus leger de commande CamerOA associe
	//
	PLCamerOA=pcam;

	// Copie des commandes et reponses dans l'objet pour etre thread safe (bogues avec QString en inter processus)
	//
	for( int i=0; i < NB_CMD_CLIENT_CAMEROA; i++ ) CmdClientCamerOA[i]=ListeCmdClientCamerOA[i];
	CmdCamerOAPoseI=CmdClientCamerOA[CAMEROA_CMD_POSEI]+"\n";
	CmdCamerOAPoseDark=CmdClientCamerOA[CAMEROA_CMD_POSEIDARK]+"\n";
}


// Destructeur du processus leger d'une liste d'acquisitions d'images sur C1
//
ProcessusLegerListeAcquisitionsC1::~ProcessusLegerListeAcquisitionsC1()
{
	// Si le thread est encore actif et donc que le serveur ne s'est pas termine normalement
	//
	if( running() )
	{
		terminate();	// On termine le thread de maniere brutale
	}
}


// Fonction de la demande de terminaison propre du processus leger d'une liste d'acquisitions d'images sur C1
//
void ProcessusLegerListeAcquisitionsC1::DemandeTerminaison(void)
{
	// Si une demande de terminaison est deja en cours on s'en retourne
	//
	if( DrapeauDemandeTerminaison ) return;

	// On demande la terminaison
	//
	DrapeauDemandeTerminaison=true;
}


// Fonction de la demande d'une liste d'acquisitions d'images sur C1 en fonction d'un contexte
//
// CE:	On passe le contexte du type de la pose (POSE_LUMIERE, POSE_DARK) ;
//
//		On passe le contexte du mode de la roue d'ouverture ;
//
//		On passe le contexte de si on doit realiser la pose de C1 couronne ;
//
// CS:	-
//
void ProcessusLegerListeAcquisitionsC1::DemandeListeAcquisitions(int ctxtypepose,ModeRoueOuvertureCLIMSO ctxpmode,int ctxc1cour)
{
	// Si une acquisition est deja en cours alors on s'en retourne pour ne pas pouvoir changer le contexte en cours
	//
	if( DrapeauDemandeAcquisitions ) return;

	// Si on veut au moins une pose
	//
	if( !ctxc1cour ) return;

	// Sauvegarde du contexte de l'acquisition
	//
	ContexteMode=ctxpmode;
	ContexteTypePose=ctxtypepose;
	ContextePoseC1Couronne=ctxc1cour;

	// On declenche l'acquisition
	//
	DrapeauDemandeAcquisitions=true;
}


// Fonction pour savoir si une liste d'acquisitions est en cours sur C1
//
// CE:	-
//
// CS:	La fonction est vraie si une liste d'acquisition est en cours
//
int ProcessusLegerListeAcquisitionsC1::EnAcquisitions(void)
{
	return DrapeauDemandeAcquisitions;
}


// Fonction d'emission des commandes de pose (consigne temps pose + pose) sur le CamerOA de C1 selon le contexte
//
// CE:	-
//
// CS:	La fonction est vraie si l'emission s'est bien deroulee selon le contexte de pose, fausse dans le cas contraire
//
int ProcessusLegerListeAcquisitionsC1::EnvoyerCommandePoseContexte(void)
{
	int tp;						// Temps de pose en 1/10000 s
	QString ChaineCommande;		// Composition de la chaine de commande
	ChaineCommande.reserve(TAILLE_MINI_CHAINE_CMD);
	QString ChaineLog;			// Composition d'une chaine de log
	ChaineLog.reserve(TAILLE_MINI_CHAINE_LOG);


	// Si le client CamerOA associe n'est pas connecte au serveur CamerOA
	//
	if( !PLCamerOA->Client->Connecte() ) return false;

	// On commence par envoyer la consigne du temps de pose selon le contexte
	//
	FPSupervCLIMSO->MutexConsignesDansUniteEntiere.lock();

	switch( ContexteMode )
	{
		case ModeRO_PLU:
			tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_C1_IMG_TP_PLU];
			break;

		case ModeRO_Calibration:
		case ModeRO_Observation:
		case ModeRO_Pointage:
			tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_C1_IMG_TP_COUR];
			break;

		default:
			tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_C1_IMG_TP_COUR];
			break;
	}

	FPSupervCLIMSO->MutexConsignesDansUniteEntiere.unlock();

	switch( ContexteTypePose )
	{
		case POSE_LUMIERE:
			ChaineCommande=CmdClientCamerOA[CAMEROA_CMD_CTPI]+QString("%1\n").arg(tp);
			break;

		case POSE_DARK:
			ChaineCommande=CmdClientCamerOA[CAMEROA_CMD_CTPD]+QString("%1\n").arg(tp);
			break;

		default:
			ChaineCommande=CmdClientCamerOA[CAMEROA_CMD_CTPI]+QString("%1\n").arg(tp);
			break;
	}

	MutexEnvChaineBIO_CamerOA[CAMEROA_C1].lock();

	if( PLCamerOA->Client->EnvoyerChaineBIO(ChaineCommande) <= 0 )
	{
		MutexEnvChaineBIO_CamerOA[CAMEROA_C1].unlock();

		// Erreur lors de l'emission
		//
		ChaineLog="*** ERREUR: Impossible d'envoyer la commande "+ChaineCommande.left(ChaineCommande.length()-1)+" au CamerOA de "+InstrumentCLIMSO[CAMEROA_C1]+" ***";
		CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(ChaineLog);
		QApplication::postEvent(FPSupervCLIMSO,event);

		return false;
	}
	MutexEnvChaineBIO_CamerOA[CAMEROA_C1].unlock();


	// On emet la commande de pose selon le contexte
	//
	switch( ContexteTypePose )
	{
		case POSE_LUMIERE:
			ChaineCommande=CmdCamerOAPoseI;
			break;

		case POSE_DARK:
			ChaineCommande=CmdCamerOAPoseDark;
			break;

		default:
			ChaineCommande=CmdCamerOAPoseI;
			break;
	}

	MutexEnvChaineBIO_CamerOA[CAMEROA_C1].lock();

	if( PLCamerOA->Client->EnvoyerChaineBIO(ChaineCommande) <= 0 )
	{
		MutexEnvChaineBIO_CamerOA[CAMEROA_C1].unlock();

		// Erreur lors de l'emission
		//
		ChaineLog="*** ERREUR: Impossible d'envoyer la commande "+ChaineCommande.left(ChaineCommande.length()-1)+" au CamerOA de "+InstrumentCLIMSO[CAMEROA_C1]+" ***";
		CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(ChaineLog);
		QApplication::postEvent(FPSupervCLIMSO,event);

		return false;
	}
	MutexEnvChaineBIO_CamerOA[CAMEROA_C1].unlock();

	return true;
}


// Surcharge de la methode run() qui contient le code d'execution du thread d'une liste d'acquisition sur C1
//
// ATTENTION : QT3 n'est pas thread-safe (c'est a dire que les fonctions ne peuvent pas etre appellees par plusieurs threads a la fois).
//		Les widgets doivent etre modifies uniquement par l'application maitre qui gere la boucle evenementielle. Donc un thread
//		qui doit modifier un widget de l'application doit communiquer par un evenement particulier QCustomEvent via la fontion
//		thread-safe QApplication::postEvent(). Il ne doit pas modifier directement le widget sinon l'application plantera.
//
void ProcessusLegerListeAcquisitionsC1::run()
{
	int Sortir=false;	// Drapeau d'indication de sortie de la boucle d'acquisitions
	QString Chaine_log;	// Pour composer une chaine de log
	Chaine_log.reserve(TAILLE_MINI_CHAINE_LOG);

	// On capture un element du semaphore de synchronisation
	//
	SemaphoreSyncLancementThreadSupervCLIMSO++;


	// Boucle de liste d'acquisitions sur C1
	//
	do
	{
		// Si on demande une liste d'acquisitions sur C1
		//
		if( DrapeauDemandeAcquisitions )
		{
			// Si on demande une pose C1 couronne
			//
			if( ContextePoseC1Couronne )
			{
				if( !EnvoyerCommandePoseContexte() )
				{
					// On doit prevenir de la fin de la liste d'acquisition car l'image n'arrivera jamais
					//
					CEventSupervCLIMSO_FinListeAcquisitions *event=new CEventSupervCLIMSO_FinListeAcquisitions(CAMEROA_C1);
					QApplication::postEvent(FPSupervCLIMSO,event);

					// Nous ne somme plus en acquisitions
					//
					DrapeauDemandeAcquisitions=false;
				}
			}

			// On a termine la liste des acquisitions sur C1
			//
			DrapeauDemandeAcquisitions=false;
		}

		if( DrapeauDemandeTerminaison ) Sortir=true; else msleep(TEMPS_BOUCLAGE_LISTE_ACQUISITIONS_MS);	// On bouclera et donc testera dans xxx ms

	} while( !Sortir );
}


//--------------------------------------------------------------------------------------------------------------------------------

// Constructeur du processus leger d'une liste d'acquisitions d'images sur C2
//
// CE:	On passe un pointeur vers la fenetre principale SupervCLIMSO ;
//
//		On passe un pointeur vers le processus leger CamerOA associe a C2 ;
//
// CS:	-
//
ProcessusLegerListeAcquisitionsC2::ProcessusLegerListeAcquisitionsC2(SupervCLIMSO *pfp,ProcessusLegerClientCommandeCamerOA *pcam)
{
	// Initialisation des variables
	//
	DrapeauDemandeTerminaison=false;
	DrapeauDemandeAcquisitions=false;
	DrapeauImageRecue=false;

	// Pointeur vers l'application parent SupervCLIMSO
	//
	FPSupervCLIMSO=pfp;

	// Pointeur vers processus leger de commande CamerOA associe
	//
	PLCamerOA=pcam;

	// Copie des commandes et reponses dans l'objet pour etre thread safe (bogues avec QString en inter processus)
	//
	for( int i=0; i < NB_CMD_CLIENT_CAMEROA; i++ ) CmdClientCamerOA[i]=ListeCmdClientCamerOA[i];
	CmdCamerOAPoseI=CmdClientCamerOA[CAMEROA_CMD_POSEI]+"\n";
	CmdCamerOAPoseDark=CmdClientCamerOA[CAMEROA_CMD_POSEIDARK]+"\n";
}


// Destructeur du processus leger d'une liste d'acquisitions d'images sur C2
//
ProcessusLegerListeAcquisitionsC2::~ProcessusLegerListeAcquisitionsC2()
{
	// Si le thread est encore actif et donc que le serveur ne s'est pas termine normalement
	//
	if( running() )
	{
		terminate();	// On termine le thread de maniere brutale
	}
}


// Fonction de la demande de terminaison propre du processus leger d'une liste d'acquisitions d'images sur C2
//
void ProcessusLegerListeAcquisitionsC2::DemandeTerminaison(void)
{
	// Si une demande de terminaison est deja en cours on s'en retourne
	//
	if( DrapeauDemandeTerminaison ) return;

	// On demande la terminaison
	//
	DrapeauDemandeTerminaison=true;
}


// Fonction de la demande d'une liste d'acquisitions d'images sur C2 en fonction d'un contexte
//
// CE:	On passe le contexte du type de la pose (POSE_LUMIERE, POSE_DARK) ;
//
//		On passe le contexte du mode de la roue d'ouverture ;
//
//		On passe le contexte de si on doit realiser la pose de C2 10747 couronne ;
//
//		On passe le contexte de si on doit realiser la pose de C2 10770 couronne ;
//
//		On passe le contexte de si on doit realiser la pose de C2 10798 couronne ;
//
//		On passe le contexte de si on doit realiser la pose de C2 10830 couronne ;
//
// CS:	-
//
void ProcessusLegerListeAcquisitionsC2::DemandeListeAcquisitions(int ctxtypepose,ModeRoueOuvertureCLIMSO ctxpmode,int ctxc2_10747,int ctxc2_10770,int ctxc2_10798,int ctxc2_10830)
{
	// Si une acquisition est deja en cours alors on s'en retourne pour ne pas pouvoir changer le contexte en cours
	//
	if( DrapeauDemandeAcquisitions ) return;

	// Si on veut au moins une pose
	//
	if( !(ctxc2_10747 || ctxc2_10770 || ctxc2_10798 || ctxc2_10830) ) return;

	// Sauvegarde du contexte de l'acquisition
	//
	ContexteMode=ctxpmode;
	ContexteTypePose=ctxtypepose;
	ContextePoseC2_10747=ctxc2_10747;
	ContextePoseC2_10770=ctxc2_10770;
	ContextePoseC2_10798=ctxc2_10798;
	ContextePoseC2_10830=ctxc2_10830;

	// On declenche l'acquisition
	//
	DrapeauDemandeAcquisitions=true;
}


// Fonction pour savoir si une liste d'acquisitions est en cours sur C2
//
// CE:	-
//
// CS:	La fonction est vraie si une liste d'acquisition est en cours
//
int ProcessusLegerListeAcquisitionsC2::EnAcquisitions(void)
{
	return DrapeauDemandeAcquisitions;
}


// Fonction d'emission des commandes de pose (consigne temps pose + pose) sur le CamerOA de C2 selon le contexte
//
// CE:	On passe le filtre du contexte courant ;
//
// CS:	La fonction est vraie si l'emission s'est bien deroulee selon le contexte de pose, fausse dans le cas contraire
//
int ProcessusLegerListeAcquisitionsC2::EnvoyerCommandePoseContexte(FiltresC2CLIMSO FiltreC2)
{
	int tp;						// Temps de pose en 1/10000 s
	QString ChaineCommande;		// Composition de la chaine de commande
	ChaineCommande.reserve(TAILLE_MINI_CHAINE_CMD);
	QString ChaineLog;			// Composition d'une chaine de log
	ChaineLog.reserve(TAILLE_MINI_CHAINE_LOG);

	// Si le client CamerOA associe n'est pas connecte au serveur CamerOA
	//
	if( !PLCamerOA->Client->Connecte() ) return false;

	// On commence par envoyer la consigne du temps de pose selon le contexte
	//
	FPSupervCLIMSO->MutexConsignesDansUniteEntiere.lock();

	switch( ContexteMode )
	{
		case ModeRO_PLU:
			switch( FiltreC2 )
			{
				case FiltreC2_10747:	tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_C2_PLU_TP_10747];	break;
				case FiltreC2_10770:	tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_C2_PLU_TP_10770];	break;
				case FiltreC2_10798:	tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_C2_PLU_TP_10798];	break;
				case FiltreC2_10830:	tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_C2_PLU_TP_10830];	break;
				default:
					tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_C2_PLU_TP_10830];
					break;
			}
			break;

		case ModeRO_Calibration:
		case ModeRO_Observation:
		case ModeRO_Pointage:
			switch( FiltreC2 )
			{
				case FiltreC2_10747:	tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_C2_IMG_TP_COUR_10747];	break;
				case FiltreC2_10770:	tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_C2_IMG_TP_COUR_10770];	break;
				case FiltreC2_10798:	tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_C2_IMG_TP_COUR_10798];	break;
				case FiltreC2_10830:	tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_C2_IMG_TP_COUR_10830];	break;
				default:
					tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_C2_IMG_TP_COUR_10830];
					break;
			}
			break;

		default:
			tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_C2_IMG_TP_COUR_10830];
			break;
	}
	FPSupervCLIMSO->MutexConsignesDansUniteEntiere.unlock();

	switch( ContexteTypePose )
	{
		case POSE_LUMIERE:
			ChaineCommande=CmdClientCamerOA[CAMEROA_CMD_CTPI]+QString("%1\n").arg(tp);
			break;

		case POSE_DARK:
			ChaineCommande=CmdClientCamerOA[CAMEROA_CMD_CTPD]+QString("%1\n").arg(tp);
			break;

		default:
			ChaineCommande=CmdClientCamerOA[CAMEROA_CMD_CTPI]+QString("%1\n").arg(tp);
			break;
	}

	MutexEnvChaineBIO_CamerOA[CAMEROA_C2].lock();

	if( PLCamerOA->Client->EnvoyerChaineBIO(ChaineCommande) <= 0 )
	{
		MutexEnvChaineBIO_CamerOA[CAMEROA_C2].unlock();

		// Erreur lors de l'emission
		//
		ChaineLog="*** ERREUR: Impossible d'envoyer la commande "+ChaineCommande.left(ChaineCommande.length()-1)+" au CamerOA de "+InstrumentCLIMSO[CAMEROA_C2]+" ***";
		CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(ChaineLog);
		QApplication::postEvent(FPSupervCLIMSO,event);

		return false;
	}
	MutexEnvChaineBIO_CamerOA[CAMEROA_C2].unlock();


	// On emet la commande de pose selon le contexte
	//
	switch( ContexteTypePose )
	{
		case POSE_LUMIERE:
			ChaineCommande=CmdCamerOAPoseI;
			break;

		case POSE_DARK:
			ChaineCommande=CmdCamerOAPoseDark;
			break;

		default:
			ChaineCommande=CmdCamerOAPoseI;
			break;
	}

	MutexEnvChaineBIO_CamerOA[CAMEROA_C2].lock();

	if( PLCamerOA->Client->EnvoyerChaineBIO(ChaineCommande) <= 0 )
	{
		MutexEnvChaineBIO_CamerOA[CAMEROA_C2].unlock();

		// Erreur lors de l'emission
		//
		ChaineLog="*** ERREUR: Impossible d'envoyer la commande "+ChaineCommande.left(ChaineCommande.length()-1)+" au CamerOA de "+InstrumentCLIMSO[CAMEROA_C2]+" ***";
		CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(ChaineLog);
		QApplication::postEvent(FPSupervCLIMSO,event);

		return false;
	}
	MutexEnvChaineBIO_CamerOA[CAMEROA_C2].unlock();

	return true;
}


// Fonction d'attente qu'un filtre soit positionne dans un temps imparti
//
// CE:	On passe le filtre attendu en position ;
//
// CS:	La fonction est vraie si le filtre s'est positionne dans le temps imparti, fausse dans le cas contraire ;
//
int ProcessusLegerListeAcquisitionsC2::AttendreFiltreC2(FiltresC2CLIMSO FiltreC2)
{
	if( ContexteTypePose == POSE_DARK ) return true;	// Dans le cas d'une pose de type DARK, le filtre est toujours en place !

	time_t debut=time(NULL);

	while( (time(NULL)-debut) < TIMEOUT_ATTENTE_FILTREC2_EN_POSITION )
	{
		if( FPSupervCLIMSO->FiltreC2Courant() == FiltreC2 ) return true;

		msleep(TEMPS_BOUCLAGE_TEST_ATTENTE_FILTREC2_EN_POSITION);
	}

	QString ChaineLog;
	ChaineLog.reserve(TAILLE_MINI_CHAINE_LOG);
	ChaineLog="*** ERREUR: Impossible de positionner le filtre ";
	switch( FiltreC2 )
	{
		case FiltreC2_10747:	ChaineLog+="10747";	break;
		case FiltreC2_10770:	ChaineLog+="10770";	break;
		case FiltreC2_10798:	ChaineLog+="10798";	break;
		case FiltreC2_10830:	ChaineLog+="10830";	break;
		default:
			ChaineLog+="!NON_LISTE!";
			break;
	}
	ChaineLog+=" nm dans la chaine optique ***";

	CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(ChaineLog);
	QApplication::postEvent(FPSupervCLIMSO,event);

	return false;
}


// Fonction appelee par le processus principal de SupervCLIMSO pour signifier qu'une nouvelle image attendue est recue
//
void ProcessusLegerListeAcquisitionsC2::ImageRecue(void)
{
	DrapeauImageRecue=true;
}


// Fonction d'attente de la reception d'une image par le processus principal de SupervCLIMSO dans un temps imparti
//
// CE:	-
//
// CS:	La fonction est vraie si SupervCLIMSO a recu une image dans le temps imparti
//
int ProcessusLegerListeAcquisitionsC2::AttendreReceptionImage(void)
{
	time_t debut=time(NULL);

	while( (time(NULL)-debut) < TIMEOUT_ATTENTE_SUPERVCLIMSO_IMAGE_RECUE )
	{
		if( DrapeauImageRecue ) return true;

		msleep(TEMPS_BOUCLAGE_TEST_ATTENTE_SUPERVCLIMSO_IMAGE_RECUE);
	}

	QString ChaineLog;
	ChaineLog.reserve(TAILLE_MINI_CHAINE_LOG);
	ChaineLog=QString::fromLocal8Bit("*** ERREUR: Une image attendue de C2 n'est pas arrivée à SupervCLIMSO ***");

	CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(ChaineLog);
	QApplication::postEvent(FPSupervCLIMSO,event);

	return false;
}


// Surcharge de la methode run() qui contient le code d'execution du thread d'une liste d'acquisition sur C2
//
// ATTENTION : QT3 n'est pas thread-safe (c'est a dire que les fonctions ne peuvent pas etre appellees par plusieurs threads a la fois).
//		Les widgets doivent etre modifies uniquement par l'application maitre qui gere la boucle evenementielle. Donc un thread
//		qui doit modifier un widget de l'application doit communiquer par un evenement particulier QCustomEvent via la fontion
//		thread-safe QApplication::postEvent(). Il ne doit pas modifier directement le widget sinon l'application plantera.
//
void ProcessusLegerListeAcquisitionsC2::run()
{
	int Sortir=false;	// Drapeau d'indication de sortie de la boucle d'acquisitions
	QString Chaine_log;	// Pour composer une chaine de log
	Chaine_log.reserve(TAILLE_MINI_CHAINE_LOG);

	// On capture un element du semaphore de synchronisation
	//
	SemaphoreSyncLancementThreadSupervCLIMSO++;


	// Boucle de liste d'acquisitions sur C2
	//
	do
	{
		// Si on demande une liste d'acquisitions sur C2
		//
		if( DrapeauDemandeAcquisitions )
		{
			// Si on demande une pose C2 10747 couronne
			//
			if( ContextePoseC2_10747 )
			{
				// On demande la mise en place du filtre 10747 s'il s'agit d'une pose lumiere
				//
				if( FPSupervCLIMSO->FiltreC2Courant() != FiltreC2_10747 && ContexteTypePose == POSE_LUMIERE )
				{
					CEventSupervCLIMSO_RotationVFiltreC2 *event=new CEventSupervCLIMSO_RotationVFiltreC2(FiltreC2_10747);
					QApplication::postEvent(FPSupervCLIMSO,event);
				}

				// On attend que le filtre soit positionne
				//
				if( AttendreFiltreC2(FiltreC2_10747) )
				{
					DrapeauImageRecue=false;

					// Si il s'agit de la derniere pose de la serie
					//
					if( !ContextePoseC2_10770 && !ContextePoseC2_10798 && !ContextePoseC2_10830 ) DrapeauDemandeAcquisitions=false;

					if( !EnvoyerCommandePoseContexte(FiltreC2_10747) )
					{
						// On doit prevenir de la fin de la liste d'acquisition car l'image n'arrivera jamais
						//
						CEventSupervCLIMSO_FinListeAcquisitions *event=new CEventSupervCLIMSO_FinListeAcquisitions(CAMEROA_C2);
						QApplication::postEvent(FPSupervCLIMSO,event);

						// Nous ne somme plus en acquisitions
						//
						DrapeauDemandeAcquisitions=false;
					}
					else
					{
						if( !AttendreReceptionImage() )
						{
							// On doit prevenir de la fin de la liste d'acquisition car l'image n'arrivera jamais
							//
							CEventSupervCLIMSO_FinListeAcquisitions *event=new CEventSupervCLIMSO_FinListeAcquisitions(CAMEROA_C2);
							QApplication::postEvent(FPSupervCLIMSO,event);

							// Nous ne somme plus en acquisitions
							//
							DrapeauDemandeAcquisitions=false;
						}
					}
				}
				else
				{
					// Il y a un timeout depasse pour le positionnement du filtre donc on provoque une sortie
					//
					CEventSupervCLIMSO_FinListeAcquisitions *event=new CEventSupervCLIMSO_FinListeAcquisitions(CAMEROA_C2);
					QApplication::postEvent(FPSupervCLIMSO,event);

					DrapeauDemandeAcquisitions=false;
				}
			}

			// Si on demande une pose C2 10770 couronne
			//
			if( ContextePoseC2_10770 && DrapeauDemandeAcquisitions )
			{
				// On demande la mise en place du filtre 10770 s'il s'agit d'une pose lumiere
				//
				if( FPSupervCLIMSO->FiltreC2Courant() != FiltreC2_10770 && ContexteTypePose == POSE_LUMIERE )
				{
					CEventSupervCLIMSO_RotationVFiltreC2 *event=new CEventSupervCLIMSO_RotationVFiltreC2(FiltreC2_10770);
					QApplication::postEvent(FPSupervCLIMSO,event);
				}

				// On attend que le filtre soit positionne
				//
				if( AttendreFiltreC2(FiltreC2_10770) )
				{
					DrapeauImageRecue=false;

					// Si il s'agit de la derniere pose de la serie
					//
					if( !ContextePoseC2_10798 && !ContextePoseC2_10830 ) DrapeauDemandeAcquisitions=false;

					if( !EnvoyerCommandePoseContexte(FiltreC2_10770) )
					{
						// On doit prevenir de la fin de la liste d'acquisition car l'image n'arrivera jamais
						//
						CEventSupervCLIMSO_FinListeAcquisitions *event=new CEventSupervCLIMSO_FinListeAcquisitions(CAMEROA_C2);
						QApplication::postEvent(FPSupervCLIMSO,event);

						// Nous ne somme plus en acquisitions
						//
						DrapeauDemandeAcquisitions=false;
					}
					else
					{
						if( !AttendreReceptionImage() )
						{
							// On doit prevenir de la fin de la liste d'acquisition car l'image n'arrivera jamais
							//
							CEventSupervCLIMSO_FinListeAcquisitions *event=new CEventSupervCLIMSO_FinListeAcquisitions(CAMEROA_C2);
							QApplication::postEvent(FPSupervCLIMSO,event);

							// Nous ne somme plus en acquisitions
							//
							DrapeauDemandeAcquisitions=false;
						}
					}
				}
				else
				{
					// Il y a un timeout depasse pour le positionnement du filtre donc on provoque une sortie
					//
					CEventSupervCLIMSO_FinListeAcquisitions *event=new CEventSupervCLIMSO_FinListeAcquisitions(CAMEROA_C2);
					QApplication::postEvent(FPSupervCLIMSO,event);

					DrapeauDemandeAcquisitions=false;
				}
			}

			// Si on demande une pose C2 10798 couronne
			//
			if( ContextePoseC2_10798 && DrapeauDemandeAcquisitions )
			{
				// On demande la mise en place du filtre 10798 s'il s'agit d'une pose lumiere
				//
				if( FPSupervCLIMSO->FiltreC2Courant() != FiltreC2_10798 && ContexteTypePose == POSE_LUMIERE )
				{
					CEventSupervCLIMSO_RotationVFiltreC2 *event=new CEventSupervCLIMSO_RotationVFiltreC2(FiltreC2_10798);
					QApplication::postEvent(FPSupervCLIMSO,event);
				}

				// On attend que le filtre soit positionne
				//
				if( AttendreFiltreC2(FiltreC2_10798) )
				{
					DrapeauImageRecue=false;

					// Si il s'agit de la derniere pose de la serie
					//
					if( !ContextePoseC2_10830 ) DrapeauDemandeAcquisitions=false;

					if( !EnvoyerCommandePoseContexte(FiltreC2_10798) )
					{
						// On doit prevenir de la fin de la liste d'acquisition car l'image n'arrivera jamais
						//
						CEventSupervCLIMSO_FinListeAcquisitions *event=new CEventSupervCLIMSO_FinListeAcquisitions(CAMEROA_C2);
						QApplication::postEvent(FPSupervCLIMSO,event);

						// Nous ne somme plus en acquisitions
						//
						DrapeauDemandeAcquisitions=false;
					}
					else
					{
						if( !AttendreReceptionImage() )
						{
							// On doit prevenir de la fin de la liste d'acquisition car l'image n'arrivera jamais
							//
							CEventSupervCLIMSO_FinListeAcquisitions *event=new CEventSupervCLIMSO_FinListeAcquisitions(CAMEROA_C2);
							QApplication::postEvent(FPSupervCLIMSO,event);

							// Nous ne somme plus en acquisitions
							//
							DrapeauDemandeAcquisitions=false;
						}
					}
				}
				else
				{
					// Il y a un timeout depasse pour le positionnement du filtre donc on provoque une sortie
					//
					CEventSupervCLIMSO_FinListeAcquisitions *event=new CEventSupervCLIMSO_FinListeAcquisitions(CAMEROA_C2);
					QApplication::postEvent(FPSupervCLIMSO,event);

					DrapeauDemandeAcquisitions=false;
				}
			}

			// Si on demande une pose C2 10830 couronne
			//
			if( ContextePoseC2_10830 && DrapeauDemandeAcquisitions )
			{
				// On a termine la liste des acquisitions sur C2
				//
				// ATTENTION: On doit placer l'etat false A CE NIVEAU DU CODE (avant le declenchement de la pose) pour que la fonction de gestion des evenements
				//  detecte la fin des poses sur C2 a la reception de cette image.
				//
				DrapeauDemandeAcquisitions=false;

				// On demande la mise en place du filtre 10830 s'il s'agit d'une pose lumiere
				//
				if( FPSupervCLIMSO->FiltreC2Courant() != FiltreC2_10830 && ContexteTypePose == POSE_LUMIERE )
				{
					CEventSupervCLIMSO_RotationVFiltreC2 *event=new CEventSupervCLIMSO_RotationVFiltreC2(FiltreC2_10830);
					QApplication::postEvent(FPSupervCLIMSO,event);
				}

				// On attend que le filtre soit positionne
				//
				if( AttendreFiltreC2(FiltreC2_10830) )
				{
					if( !EnvoyerCommandePoseContexte(FiltreC2_10830) )
					{
						// On doit prevenir de la fin de la liste d'acquisition car l'image n'arrivera jamais
						//
						CEventSupervCLIMSO_FinListeAcquisitions *event=new CEventSupervCLIMSO_FinListeAcquisitions(CAMEROA_C2);
						QApplication::postEvent(FPSupervCLIMSO,event);

						// Nous ne somme plus en acquisitions
						//
						DrapeauDemandeAcquisitions=false;
					}
				}
				else
				{
					// Il y a un timeout depasse pour le positionnement du filtre donc on provoque une sortie
					//
					CEventSupervCLIMSO_FinListeAcquisitions *event=new CEventSupervCLIMSO_FinListeAcquisitions(CAMEROA_C2);
					QApplication::postEvent(FPSupervCLIMSO,event);

					DrapeauDemandeAcquisitions=false;
				}
			}
		}

		if( DrapeauDemandeTerminaison ) Sortir=true; else msleep(TEMPS_BOUCLAGE_LISTE_ACQUISITIONS_MS);	// On bouclera et donc testera dans xxx ms

	} while( !Sortir );
}


//--------------------------------------------------------------------------------------------------------------------------------

// Constructeur du processus leger d'une liste d'acquisitions d'images sur L1
//
// CE:	On passe un pointeur vers la fenetre principale SupervCLIMSO ;
//
//		On passe un pointeur vers le processus leger CamerOA associe a L1 ;
//
// CS:	-
//
ProcessusLegerListeAcquisitionsL1::ProcessusLegerListeAcquisitionsL1(SupervCLIMSO *pfp,ProcessusLegerClientCommandeCamerOA *pcam)
{
	// Initialisation des variables
	//
	DrapeauDemandeTerminaison=false;
	DrapeauDemandeAcquisitions=false;
	DrapeauImageRecue=false;

	// Pointeur vers l'application parent SupervCLIMSO
	//
	FPSupervCLIMSO=pfp;

	// Pointeur vers processus leger de commande CamerOA associe
	//
	PLCamerOA=pcam;

	// Copie des commandes et reponses dans l'objet pour etre thread safe (bogues avec QString en inter processus)
	//
	for( int i=0; i < NB_CMD_CLIENT_CAMEROA; i++ ) CmdClientCamerOA[i]=ListeCmdClientCamerOA[i];
	CmdCamerOAPoseI=CmdClientCamerOA[CAMEROA_CMD_POSEI]+"\n";
	CmdCamerOAPoseDark=CmdClientCamerOA[CAMEROA_CMD_POSEIDARK]+"\n";
}


// Destructeur du processus leger d'une liste d'acquisitions d'images sur L1
//
ProcessusLegerListeAcquisitionsL1::~ProcessusLegerListeAcquisitionsL1()
{
	// Si le thread est encore actif et donc que le serveur ne s'est pas termine normalement
	//
	if( running() )
	{
		terminate();	// On termine le thread de maniere brutale
	}
}


// Fonction de la demande de terminaison propre du processus leger d'une liste d'acquisitions d'images sur L1
//
void ProcessusLegerListeAcquisitionsL1::DemandeTerminaison(void)
{
	// Si une demande de terminaison est deja en cours on s'en retourne
	//
	if( DrapeauDemandeTerminaison ) return;

	// On demande la terminaison
	//
	DrapeauDemandeTerminaison=true;
}


// Fonction de la demande d'une liste d'acquisitions d'images sur L1 en fonction d'un contexte
//
// CE:	On passe le contexte du type de la pose (POSE_LUMIERE, POSE_DARK) ;
//
//		On passe le contexte du mode de la roue d'ouverture ;
//
//		On passe le contexte de si on doit realiser la pose L1 surface ;
//
//		On passe le contexte de si on doit realiser la pose L1 couronne ;
//
// CS:	-
//
void ProcessusLegerListeAcquisitionsL1::DemandeListeAcquisitions(int ctxtypepose,ModeRoueOuvertureCLIMSO ctxpmode,int ctxl1s,int ctxl1c)
{
	// Si une acquisition est deja en cours alors on s'en retourne pour ne pas pouvoir changer le contexte en cours
	//
	if( DrapeauDemandeAcquisitions ) return;

	// Si on veut au moins une pose
	//
	if( !(ctxl1s || ctxl1c) ) return;

	// Sauvegarde du contexte de l'acquisition
	//
	ContexteMode=ctxpmode;
	ContexteTypePose=ctxtypepose;
	ContextePoseL1S=ctxl1s;
	ContextePoseL1C=ctxl1c;

	// On declenche l'acquisition
	//
	DrapeauDemandeAcquisitions=true;
}


// Fonction pour savoir si une liste d'acquisitions est en cours sur L1
//
// CE:	-
//
// CS:	La fonction est vraie si une liste d'acquisition est en cours
//
int ProcessusLegerListeAcquisitionsL1::EnAcquisitions(void)
{
	return DrapeauDemandeAcquisitions;
}


// Fonction d'emission des commandes de pose (consigne temps pose + pose) sur le CamerOA de L1 selon le contexte
//
// CE:	On passe la designation de la pose POSE_SURFACE ou POSE_COURONNE ;
//
// CS:	La fonction est vraie si l'emission s'est bien deroulee selon le contexte de pose, fausse dans le cas contraire
//
int ProcessusLegerListeAcquisitionsL1::EnvoyerCommandePoseContexte(int designation)
{
	int tp;						// Temps de pose en 1/10000 s
	QString ChaineCommande;		// Composition de la chaine de commande
	ChaineCommande.reserve(TAILLE_MINI_CHAINE_CMD);
	QString ChaineLog;			// Composition d'une chaine de log
	ChaineLog.reserve(TAILLE_MINI_CHAINE_LOG);

	// Si le client CamerOA associe n'est pas connecte au serveur CamerOA
	//
	if( !PLCamerOA->Client->Connecte() ) return false;

	// On commence par envoyer la consigne du temps de pose selon le contexte
	//
	FPSupervCLIMSO->MutexConsignesDansUniteEntiere.lock();

	switch( ContexteMode )
	{
		case ModeRO_PLU:
			switch( designation )
			{
				case POSE_SURFACE:	tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_L1_IMG_TP_PLU];	break;
				case POSE_COURONNE:	tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_L1_IMG_TP_PLU];	break;
				default:
					tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_L1_IMG_TP_PLU];
					break;
			}
			break;

		case ModeRO_Calibration:
		case ModeRO_Observation:
		case ModeRO_Pointage:
			switch( designation )
			{
				case POSE_SURFACE:	tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_L1_IMG_TP_SURF];	break;
				case POSE_COURONNE:	tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_L1_IMG_TP_COUR];	break;
				default:
					tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_L1_IMG_TP_SURF];
					break;
			}
			break;

		default:
			tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_L1_IMG_TP_SURF];
			break;
	}

	FPSupervCLIMSO->MutexConsignesDansUniteEntiere.unlock();

	switch( ContexteTypePose )
	{
		case POSE_LUMIERE:
			ChaineCommande=CmdClientCamerOA[CAMEROA_CMD_CTPI]+QString("%1\n").arg(tp);
			break;

		case POSE_DARK:
			ChaineCommande=CmdClientCamerOA[CAMEROA_CMD_CTPD]+QString("%1\n").arg(tp);
			break;

		default:
			ChaineCommande=CmdClientCamerOA[CAMEROA_CMD_CTPI]+QString("%1\n").arg(tp);
			break;
	}

	MutexEnvChaineBIO_CamerOA[CAMEROA_L1].lock();

	if( PLCamerOA->Client->EnvoyerChaineBIO(ChaineCommande) <= 0 )
	{
		MutexEnvChaineBIO_CamerOA[CAMEROA_L1].unlock();

		// Erreur lors de l'emission
		//
		ChaineLog="*** ERREUR: Impossible d'envoyer la commande "+ChaineCommande.left(ChaineCommande.length()-1)+" au CamerOA de "+InstrumentCLIMSO[CAMEROA_L1]+" ***";
		CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(ChaineLog);
		QApplication::postEvent(FPSupervCLIMSO,event);

		return false;
	}
	MutexEnvChaineBIO_CamerOA[CAMEROA_L1].unlock();


	// On emet la commande de pose selon le contexte
	//
	switch( ContexteTypePose )
	{
		case POSE_LUMIERE:
			ChaineCommande=CmdCamerOAPoseI;
			break;

		case POSE_DARK:
			ChaineCommande=CmdCamerOAPoseDark;
			break;

		default:
			ChaineCommande=CmdCamerOAPoseI;
			break;
	}

	MutexEnvChaineBIO_CamerOA[CAMEROA_L1].lock();

	if( PLCamerOA->Client->EnvoyerChaineBIO(ChaineCommande) <= 0 )
	{
		MutexEnvChaineBIO_CamerOA[CAMEROA_L1].unlock();

		// Erreur lors de l'emission
		//
		ChaineLog="*** ERREUR: Impossible d'envoyer la commande "+ChaineCommande.left(ChaineCommande.length()-1)+" au CamerOA de "+InstrumentCLIMSO[CAMEROA_L1]+" ***";
		CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(ChaineLog);
		QApplication::postEvent(FPSupervCLIMSO,event);

		return false;
	}
	MutexEnvChaineBIO_CamerOA[CAMEROA_L1].unlock();

	return true;
}


// Fonction appelee par le processus principal de SupervCLIMSO pour signifier qu'une nouvelle image attendue est recue
//
void ProcessusLegerListeAcquisitionsL1::ImageRecue(void)
{
	DrapeauImageRecue=true;
}


// Fonction d'attente de la reception d'une image par le processus principal de SupervCLIMSO dans un temps imparti
//
// CE:	-
//
// CS:	La fonction est vraie si SupervCLIMSO a recu une image dans le temps imparti
//
int ProcessusLegerListeAcquisitionsL1::AttendreReceptionImage(void)
{
	time_t debut=time(NULL);

	while( (time(NULL)-debut) < TIMEOUT_ATTENTE_SUPERVCLIMSO_IMAGE_RECUE )
	{
		if( DrapeauImageRecue ) return true;

		msleep(TEMPS_BOUCLAGE_TEST_ATTENTE_SUPERVCLIMSO_IMAGE_RECUE);
	}

	QString ChaineLog;
	ChaineLog.reserve(TAILLE_MINI_CHAINE_LOG);
	ChaineLog=QString::fromLocal8Bit("*** ERREUR: Une image attendue de L1 n'est pas arrivée à SupervCLIMSO ***");

	CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(ChaineLog);
	QApplication::postEvent(FPSupervCLIMSO,event);

	return false;
}


// Surcharge de la methode run() qui contient le code d'execution du thread d'une liste d'acquisition sur L1
//
// ATTENTION : QT3 n'est pas thread-safe (c'est a dire que les fonctions ne peuvent pas etre appellees par plusieurs threads a la fois).
//		Les widgets doivent etre modifies uniquement par l'application maitre qui gere la boucle evenementielle. Donc un thread
//		qui doit modifier un widget de l'application doit communiquer par un evenement particulier QCustomEvent via la fontion
//		thread-safe QApplication::postEvent(). Il ne doit pas modifier directement le widget sinon l'application plantera.
//
void ProcessusLegerListeAcquisitionsL1::run()
{
	int Sortir=false;	// Drapeau d'indication de sortie de la boucle d'acquisitions
	QString Chaine_log;	// Pour composer une chaine de log
	Chaine_log.reserve(TAILLE_MINI_CHAINE_LOG);

	// On capture un element du semaphore de synchronisation
	//
	SemaphoreSyncLancementThreadSupervCLIMSO++;


	// Boucle de liste d'acquisitions sur L1
	//
	do
	{
		// Si on demande une liste d'acquisitions sur L1
		//
		if( DrapeauDemandeAcquisitions )
		{
			// Si on demande une pose L1 couronne
			//
			if( ContextePoseL1C )
			{
				DrapeauImageRecue=false;

				// Si il s'agit de la derniere pose de la serie
				//
				if( !ContextePoseL1S ) DrapeauDemandeAcquisitions=false;

				if( !EnvoyerCommandePoseContexte(POSE_COURONNE) )
				{
					// On doit prevenir de la fin de la liste d'acquisition car l'image n'arrivera jamais
					//
					CEventSupervCLIMSO_FinListeAcquisitions *event=new CEventSupervCLIMSO_FinListeAcquisitions(CAMEROA_L1);
					QApplication::postEvent(FPSupervCLIMSO,event);

					// Nous ne somme plus en acquisitions
					//
					DrapeauDemandeAcquisitions=false;
				}
				else
				{
					if( !AttendreReceptionImage() )
					{
						// On doit prevenir de la fin de la liste d'acquisition car l'image n'arrivera jamais
						//
						CEventSupervCLIMSO_FinListeAcquisitions *event=new CEventSupervCLIMSO_FinListeAcquisitions(CAMEROA_L1);
						QApplication::postEvent(FPSupervCLIMSO,event);

						// Nous ne somme plus en acquisitions
						//
						DrapeauDemandeAcquisitions=false;
					}
				}
			}

			// Si on demande une pose L1 surface
			//
			if( ContextePoseL1S && DrapeauDemandeAcquisitions )
			{
				// On a termine la liste des acquisitions sur L1
				//
				// ATTENTION: On doit placer l'etat false A CE NIVEAU DU CODE (avant le declenchement de la pose) pour que la fonction de gestion des evenements
				//  detecte la fin des poses sur L1 a la reception de cette image.
				//
				DrapeauDemandeAcquisitions=false;

				if( !EnvoyerCommandePoseContexte(POSE_SURFACE) )
				{
					// On doit prevenir de la fin de la liste d'acquisition car l'image n'arrivera jamais
					//
					CEventSupervCLIMSO_FinListeAcquisitions *event=new CEventSupervCLIMSO_FinListeAcquisitions(CAMEROA_L1);
					QApplication::postEvent(FPSupervCLIMSO,event);

					// Nous ne somme plus en acquisitions
					//
					DrapeauDemandeAcquisitions=false;
				}
			}
		}

		if( DrapeauDemandeTerminaison ) Sortir=true; else msleep(TEMPS_BOUCLAGE_LISTE_ACQUISITIONS_MS);	// On bouclera et donc testera dans xxx ms

	} while( !Sortir );
}


//--------------------------------------------------------------------------------------------------------------------------------

// Constructeur du processus leger d'une liste d'acquisitions d'images sur L2
//
// CE:	On passe un pointeur vers la fenetre principale SupervCLIMSO ;
//
//		On passe un pointeur vers le processus leger CamerOA associe a L2 ;
//
// CS:	-
//
ProcessusLegerListeAcquisitionsL2::ProcessusLegerListeAcquisitionsL2(SupervCLIMSO *pfp,ProcessusLegerClientCommandeCamerOA *pcam)
{
	// Initialisation des variables
	//
	DrapeauDemandeTerminaison=false;
	DrapeauDemandeAcquisitions=false;
	DrapeauImageRecue=false;

	// Pointeur vers l'application parent SupervCLIMSO
	//
	FPSupervCLIMSO=pfp;

	// Pointeur vers processus leger de commande CamerOA associe
	//
	PLCamerOA=pcam;

	// Copie des commandes et reponses dans l'objet pour etre thread safe (bogues avec QString en inter processus)
	//
	for( int i=0; i < NB_CMD_CLIENT_CAMEROA; i++ ) CmdClientCamerOA[i]=ListeCmdClientCamerOA[i];
	CmdCamerOAPoseI=CmdClientCamerOA[CAMEROA_CMD_POSEI]+"\n";
	CmdCamerOAPoseDark=CmdClientCamerOA[CAMEROA_CMD_POSEIDARK]+"\n";
}


// Destructeur du processus leger d'une liste d'acquisitions d'images sur L2
//
ProcessusLegerListeAcquisitionsL2::~ProcessusLegerListeAcquisitionsL2()
{
	// Si le thread est encore actif et donc que le serveur ne s'est pas termine normalement
	//
	if( running() )
	{
		terminate();	// On termine le thread de maniere brutale
	}
}


// Fonction de la demande de terminaison propre du processus leger d'une liste d'acquisitions d'images sur L2
//
void ProcessusLegerListeAcquisitionsL2::DemandeTerminaison(void)
{
	// Si une demande de terminaison est deja en cours on s'en retourne
	//
	if( DrapeauDemandeTerminaison ) return;

	// On demande la terminaison
	//
	DrapeauDemandeTerminaison=true;
}


// Fonction de la demande d'une liste d'acquisitions d'images sur L2 en fonction d'un contexte
//
// CE:	On passe le contexte du type de la pose (POSE_LUMIERE, POSE_DARK) ;
//
//		On passe le contexte du mode de la roue d'ouverture ;
//
//		On passe le contexte de si on doit realiser la pose L2 surface ;
//
//		On passe le contexte de si on doit realiser la pose L2 couronne ;
//
// CS:	-
//
void ProcessusLegerListeAcquisitionsL2::DemandeListeAcquisitions(int ctxtypepose,ModeRoueOuvertureCLIMSO ctxpmode,int ctxl2s,int ctxl2c)
{
	// Si une acquisition est deja en cours alors on s'en retourne pour ne pas pouvoir changer le contexte en cours
	//
	if( DrapeauDemandeAcquisitions ) return;

	// Si on veut au moins une pose
	//
	if( !(ctxl2s || ctxl2c) ) return;

	// Sauvegarde du contexte de l'acquisition
	//
	ContexteMode=ctxpmode;
	ContexteTypePose=ctxtypepose;
	ContextePoseL2S=ctxl2s;
	ContextePoseL2C=ctxl2c;

	// On declenche l'acquisition
	//
	DrapeauDemandeAcquisitions=true;
}


// Fonction pour savoir si une liste d'acquisitions est en cours sur L2
//
// CE:	-
//
// CS:	La fonction est vraie si une liste d'acquisition est en cours
//
int ProcessusLegerListeAcquisitionsL2::EnAcquisitions(void)
{
	return DrapeauDemandeAcquisitions;
}


// Fonction d'emission des commandes de pose (consigne temps pose + pose) sur le CamerOA de L2 selon le contexte
//
// CE:	On passe la designation de la pose POSE_SURFACE ou POSE_COURONNE ;
//
// CS:	La fonction est vraie si l'emission s'est bien deroulee selon le contexte de pose, fausse dans le cas contraire
//
int ProcessusLegerListeAcquisitionsL2::EnvoyerCommandePoseContexte(int designation)
{
	int tp;						// Temps de pose en 1/10000 s
	QString ChaineCommande;		// Composition de la chaine de commande
	ChaineCommande.reserve(TAILLE_MINI_CHAINE_CMD);
	QString ChaineLog;			// Composition d'une chaine de log
	ChaineLog.reserve(TAILLE_MINI_CHAINE_LOG);

	// Si le client CamerOA associe n'est pas connecte au serveur CamerOA
	//
	if( !PLCamerOA->Client->Connecte() ) return false;

	// On commence par envoyer la consigne du temps de pose selon le contexte
	//
	FPSupervCLIMSO->MutexConsignesDansUniteEntiere.lock();

	switch( ContexteMode )
	{
		case ModeRO_PLU:
			switch( designation )
			{
				case POSE_SURFACE:	tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_L2_IMG_TP_PLU];	break;
				case POSE_COURONNE:	tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_L2_IMG_TP_PLU];	break;
				default:
					tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_L2_IMG_TP_PLU];
					break;
			}
			break;

		case ModeRO_Calibration:
		case ModeRO_Observation:
		case ModeRO_Pointage:
			switch( designation )
			{
				case POSE_SURFACE:	tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_L2_IMG_TP_SURF];	break;
				case POSE_COURONNE:	tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_L2_IMG_TP_COUR];	break;
				default:
					tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_L2_IMG_TP_SURF];
					break;
			}
			break;

		default:
			tp=FPSupervCLIMSO->ConsignesDansUniteEntiere[CONSIGNE_L2_IMG_TP_SURF];
			break;
	}
	FPSupervCLIMSO->MutexConsignesDansUniteEntiere.unlock();

	switch( ContexteTypePose )
	{
		case POSE_LUMIERE:
			ChaineCommande=CmdClientCamerOA[CAMEROA_CMD_CTPI]+QString("%1\n").arg(tp);
			break;

		case POSE_DARK:
			ChaineCommande=CmdClientCamerOA[CAMEROA_CMD_CTPD]+QString("%1\n").arg(tp);
			break;

		default:
			ChaineCommande=CmdClientCamerOA[CAMEROA_CMD_CTPI]+QString("%1\n").arg(tp);
			break;
	}

	MutexEnvChaineBIO_CamerOA[CAMEROA_L2].lock();

	if( PLCamerOA->Client->EnvoyerChaineBIO(ChaineCommande) <= 0 )
	{
		MutexEnvChaineBIO_CamerOA[CAMEROA_L2].unlock();

		// Erreur lors de l'emission
		//
		ChaineLog="*** ERREUR: Impossible d'envoyer la commande "+ChaineCommande.left(ChaineCommande.length()-1)+" au CamerOA de "+InstrumentCLIMSO[CAMEROA_L2]+" ***";
		CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(ChaineLog);
		QApplication::postEvent(FPSupervCLIMSO,event);

		return false;
	}
	MutexEnvChaineBIO_CamerOA[CAMEROA_L2].unlock();


	// On emet la commande de pose selon le contexte
	//
	switch( ContexteTypePose )
	{
		case POSE_LUMIERE:
			ChaineCommande=CmdCamerOAPoseI;
			break;

		case POSE_DARK:
			ChaineCommande=CmdCamerOAPoseDark;
			break;

		default:
			ChaineCommande=CmdCamerOAPoseI;
			break;
	}

	MutexEnvChaineBIO_CamerOA[CAMEROA_L2].lock();

	if( PLCamerOA->Client->EnvoyerChaineBIO(ChaineCommande) <= 0 )
	{
		MutexEnvChaineBIO_CamerOA[CAMEROA_L2].unlock();

		// Erreur lors de l'emission
		//
		ChaineLog="*** ERREUR: Impossible d'envoyer la commande "+ChaineCommande.left(ChaineCommande.length()-1)+" au CamerOA de "+InstrumentCLIMSO[CAMEROA_L2]+" ***";
		CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(ChaineLog);
		QApplication::postEvent(FPSupervCLIMSO,event);

		return false;
	}
	MutexEnvChaineBIO_CamerOA[CAMEROA_L2].unlock();

	return true;
}


// Fonction appelee par le processus principal de SupervCLIMSO pour signifier qu'une nouvelle image attendue est recue
//
void ProcessusLegerListeAcquisitionsL2::ImageRecue(void)
{
	DrapeauImageRecue=true;
}


// Fonction d'attente de la reception d'une image par le processus principal de SupervCLIMSO dans un temps imparti
//
// CE:	-
//
// CS:	La fonction est vraie si SupervCLIMSO a recu une image dans le temps imparti
//
int ProcessusLegerListeAcquisitionsL2::AttendreReceptionImage(void)
{
	time_t debut=time(NULL);

	while( (time(NULL)-debut) < TIMEOUT_ATTENTE_SUPERVCLIMSO_IMAGE_RECUE )
	{
		if( DrapeauImageRecue ) return true;

		msleep(TEMPS_BOUCLAGE_TEST_ATTENTE_SUPERVCLIMSO_IMAGE_RECUE);
	}

	QString ChaineLog;
	ChaineLog.reserve(TAILLE_MINI_CHAINE_LOG);
	ChaineLog=QString::fromLocal8Bit("*** ERREUR: Une image attendue de L2 n'est pas arrivée à SupervCLIMSO ***");

	CEventSupervCLIMSO_Log *event=new CEventSupervCLIMSO_Log(ChaineLog);
	QApplication::postEvent(FPSupervCLIMSO,event);

	return false;
}


// Surcharge de la methode run() qui contient le code d'execution du thread d'une liste d'acquisition sur L2
//
// ATTENTION : QT3 n'est pas thread-safe (c'est a dire que les fonctions ne peuvent pas etre appellees par plusieurs threads a la fois).
//		Les widgets doivent etre modifies uniquement par l'application maitre qui gere la boucle evenementielle. Donc un thread
//		qui doit modifier un widget de l'application doit communiquer par un evenement particulier QCustomEvent via la fontion
//		thread-safe QApplication::postEvent(). Il ne doit pas modifier directement le widget sinon l'application plantera.
//
void ProcessusLegerListeAcquisitionsL2::run()
{
	int Sortir=false;	// Drapeau d'indication de sortie de la boucle d'acquisitions
	QString Chaine_log;	// Pour composer une chaine de log
	Chaine_log.reserve(TAILLE_MINI_CHAINE_LOG);

	// On capture un element du semaphore de synchronisation
	//
	SemaphoreSyncLancementThreadSupervCLIMSO++;


	// Boucle de liste d'acquisitions sur L2
	//
	do
	{
		// Si on demande une liste d'acquisitions sur L2
		//
		if( DrapeauDemandeAcquisitions )
		{
			// Si on demande une pose L2 couronne
			//
			if( ContextePoseL2C )
			{
				DrapeauImageRecue=false;

				// Si il s'agit de la derniere pose de la serie
				//
				if( !ContextePoseL2S ) DrapeauDemandeAcquisitions=false;

				if( !EnvoyerCommandePoseContexte(POSE_COURONNE) )
				{
					// On doit prevenir de la fin de la liste d'acquisition car l'image n'arrivera jamais
					//
					CEventSupervCLIMSO_FinListeAcquisitions *event=new CEventSupervCLIMSO_FinListeAcquisitions(CAMEROA_L2);
					QApplication::postEvent(FPSupervCLIMSO,event);

					// Nous ne somme plus en acquisitions
					//
					DrapeauDemandeAcquisitions=false;
				}
				else
				{
					if( !AttendreReceptionImage() )
					{
						// On doit prevenir de la fin de la liste d'acquisition car l'image n'arrivera jamais
						//
						CEventSupervCLIMSO_FinListeAcquisitions *event=new CEventSupervCLIMSO_FinListeAcquisitions(CAMEROA_L2);
						QApplication::postEvent(FPSupervCLIMSO,event);

						// Nous ne somme plus en acquisitions
						//
						DrapeauDemandeAcquisitions=false;
					}
				}
			}

			// Si on demande une pose L2 surface
			//
			if( ContextePoseL2S && DrapeauDemandeAcquisitions )
			{
				// On a termine la liste des acquisitions sur L2
				//
				// ATTENTION: On doit placer l'etat false A CE NIVEAU DU CODE (avant le declenchement de la pose) pour que la fonction de gestion des evenements
				//  detecte la fin des poses sur L2 a la reception de cette image.
				//
				DrapeauDemandeAcquisitions=false;

				if( !EnvoyerCommandePoseContexte(POSE_SURFACE) )
				{
					// On doit prevenir de la fin de la liste d'acquisition car l'image n'arrivera jamais
					//
					CEventSupervCLIMSO_FinListeAcquisitions *event=new CEventSupervCLIMSO_FinListeAcquisitions(CAMEROA_L2);
					QApplication::postEvent(FPSupervCLIMSO,event);

					// Nous ne somme plus en acquisitions
					//
					DrapeauDemandeAcquisitions=false;
				}
			}
		}

		if( DrapeauDemandeTerminaison ) Sortir=true; else msleep(TEMPS_BOUCLAGE_LISTE_ACQUISITIONS_MS);	// On bouclera et donc testera dans xxx ms

	} while( !Sortir );
}


// #include "supervclimso.moc.cpp" XXX Ce fichier est maintenant inclus lors de la compilation (voir
