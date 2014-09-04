/* HEADER DU MODULE DE LA CLASSE DE LA FENETRE PRINCIPALE DE L'APPLICATION SupervCLIMSO

   LOGICIEL DE SUPERVISION DE L'INSTRUMENT CLIMSO

  (C)David.Romeuf@univ-lyon1.fr 26/10/2006 par David Romeuf
*/


#ifndef _SUPERVCLIMSO_H_
#define _SUPERVCLIMSO_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// Inclusions C++
//
#include <iostream>
#include <valarray>

// Inclusions Qt et KDE
//
#include <kmainwindow.h>
#include <kapplication.h>
#include <qcheckbox.h>
#include <qdialog.h>
#include <qevent.h>
#include <qhbox.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qlcdnumber.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <qstatusbar.h>
#include <qstring.h>
#include <qtextedit.h>
#include <qthread.h>
#include <qtimer.h>
#include <qtooltip.h>
#include <qvalidator.h>
#include <qvbox.h>
#include <qfile.h>

// Inclusions C++
//
#include "calculsastronomiques.h"
#include "pointscomm.h"
#include "trameimagecameroa.h"
#include "trameimageterminoa.h"
#include "WidgetPoseCentrage.h"
#include "WidgetRoueFiltresC2.h"
#include "WidgetRoueOuvertureCLIMSO.h"
#include "WidgetSoleilHeliographique.h"
#include "ListesCommandesReponsesRobOA.h"
#include "ListesCommandesReponsesCamerOA.h"
#include "ListesCommandesReponsesTerminOA.h"

// Definitions
//
#define TAILLE_MINI_CHAINE				255

#define TAILLE_Y_LOGS					150
#define FICHIER_SAUV_LOGS_SUPERVCLIMSO	"supervclimso.log"
#define TAILLE_MINI_CHAINE_LOG			1024

#define TAILLE_X_LCD_MPCAMEROA	133
#define TAILLE_Y_LCD_MPCAMEROA	38

#define NB_CONSIGNES							34
#define CONSIGNE_C1_IMG_TP_CENTRAGE				0
#define CONSIGNE_C1_IMG_TP_COUR					1
#define CONSIGNE_C1_IMG_TP_PLU					2
#define CONSIGNE_C1_TCCD						3
#define CONSIGNE_C1_VENTILATEUR					4
#define CONSIGNE_C2_IMG_TP_CENTRAGE_10830		5
#define CONSIGNE_C2_IMG_TP_COUR_10747			6
#define CONSIGNE_C2_IMG_TP_COUR_10770			7
#define CONSIGNE_C2_IMG_TP_COUR_10798			8
#define CONSIGNE_C2_IMG_TP_COUR_10830			9
#define CONSIGNE_C2_PLU_TP_10747				10
#define CONSIGNE_C2_PLU_TP_10770				11
#define CONSIGNE_C2_PLU_TP_10798				12
#define CONSIGNE_C2_PLU_TP_10830				13
#define CONSIGNE_C2_TCCD						14
#define CONSIGNE_C2_VENTILATEUR					15
#define CONSIGNE_L1_IMG_TP_CENTRAGE				16
#define CONSIGNE_L1_IMG_TP_SURF					17
#define CONSIGNE_L1_IMG_TP_COUR					18
#define CONSIGNE_L1_IMG_TP_PLU					19
#define CONSIGNE_L1_TCCD						20
#define CONSIGNE_L1_VENTILATEUR					21
#define CONSIGNE_L2_IMG_TP_CENTRAGE				22
#define CONSIGNE_L2_IMG_TP_SURF					23
#define CONSIGNE_L2_IMG_TP_COUR					24
#define CONSIGNE_L2_IMG_TP_PLU					25
#define CONSIGNE_L2_TCCD						26
#define CONSIGNE_L2_VENTILATEUR					27
#define CONSIGNE_CAISSON_INFO_ALERTE_INF		28
#define CONSIGNE_CAISSON_INFO_ALERTE_SUP		29
#define CONSIGNE_CAISSON_FILTREC1_ALERTE_INF	30
#define CONSIGNE_CAISSON_FILTREC1_ALERTE_SUP	31
#define CONSIGNE_CAISSON_FILTREC2_ALERTE_INF	32
#define CONSIGNE_CAISSON_FILTREC2_ALERTE_SUP	33
#define CONSIGNE_EDIT_NON_INIT					"#"
#define CONSIGNE_TEMPS_POSE_MINI				0.0001
#define CONSIGNE_TEMPS_POSE_MAXI				500.0
#define CONSIGNE_TEMPERATURE_MINI				-50.0
#define CONSIGNE_TEMPERATURE_MAXI				50.0
#define CONSIGNE_VENTILATEUR_MINI				1.0
#define CONSIGNE_VENTILATEUR_MAXI				3.0
#define TAILLE_X_LABEL_CONSIGNE	512
#define TAILLE_X_EDIT_CONSIGNE	80
#define TAILLE_Y_LABEL_CONSIGNE	32
#define COULEUR_LIGNE_CONSIGNE_0	QColor(255,240,225)
#define COULEUR_LIGNE_CONSIGNE_1	QColor(225,240,255)
#define FICHIER_SAUV_CONSIGNES		"SupervCLIMSO_Consignes.dat"

#define FICHIER_SAUV_TEMPERATURES	"temperatures.dat"

#define TAILLE_MINI_CHAINE_CMD		255

#define NB_ROBOA	1							// Nombre de RobOA que SupervCLIMSO doit superviser
#define NB_AXES		4							// Nombre d'axes que CLIMSO doit gérer
#define AXE_ROUE_OUVERTURE	0
#define AXE_ROUE_FILTREC2	1
#define AXE_PLATINE_X		2
#define AXE_PLATINE_Y		3
#define AXE_NON_RECHERCHE	-1
#define TAILLE_X_LABEL_AXECODEUR	95
#define TAILLE_X_LABEL_AXECODEUR_PLATINE	25
#define TAILLE_Y_LABEL_AXECODEUR	38
#define TAILLE_X_LCD_AXECODEUR		120
#define TAILLE_X_LCD_AXECODEUR_PLATINE		163
#define TAILLE_Y_LCD_AXECODEUR		38
#define TAILLE_X_SPINBOX_AXECODEUR_PLATINE	120
#define TAILLE_Y_SPINBOX_AXECODEUR	38
#define POSITION_AXE_MICROPAS_NON_CONNUE	-99999999
#define POSITION_AXE_DEGRES_NON_CONNUE		-99999999.0
#define VALMIN_DELTA_X_C2	-25000
#define VALMAX_DELTA_X_C2	25000
#define VALMIN_DELTA_Y_C2	-25000
#define VALMAX_DELTA_Y_C2	25000
#define VALINC_DELTA_X_C2	100
#define VALINC_DELTA_Y_C2	100

#define NB_POINTS_QUADRATURE_CODEUR_PT_AXE_ROUE_OUVERTURE	24000.0
#define NB_MICROPAS_MOTEUR_PT_AXE_ROUE_OUVERTURE			157575.0
#define OFFSET_MICROPAS_MOTEUR_POS_ZERO_ROUE_OUVERTURE		63500.0
#define PRECISION_POS_MODE_ROUE_OUVERTURE					0.3			// Precision en degres dans le repere reel de la roue d'ouverture pour considerer un mode

#define NB_POINTS_QUADRATURE_CODEUR_PT_AXE_ROUE_FILTREC2	8192.0
#define NB_MICROPAS_MOTEUR_PT_AXE_ROUE_FILTREC2				7480.0
#define OFFSET_MICROPAS_MOTEUR_POS_ZERO_ROUE_FILTREC2		955.0
#define PRECISION_POS_MODE_ROUE_FILTREC2					0.3

#define RapportMicroPasCodeurPlatine	3								// Rapport en valeur entre l'information codeur et MicroPas sur les axes de la platine
																		//  on affiche la même valeur en micropas et codeur sur le LCD pour ne pas perturber l'observateur

#define NB_CAMEROA	4							// Nombre de CamerOA que SupervCLIMSO doit superviser
#define CAMEROA_C1	0
#define CAMEROA_C2	1
#define CAMEROA_L1	2
#define CAMEROA_L2	3

#define NB_TYPES_ACQUISITIONS	9
#define ACQUISITION_C1_COUR		0
#define ACQUISITION_C2_10830	1
#define ACQUISITION_C2_10747	2
#define ACQUISITION_C2_10770	3
#define ACQUISITION_C2_10798	4
#define ACQUISITION_L1_SURF		5
#define ACQUISITION_L1_COUR		6
#define ACQUISITION_L2_SURF		7
#define ACQUISITION_L2_COUR		8
#define COULEUR_LABEL_ACQUISITION	QColor(235,235,255)

#define TEMPS_BOUCLAGE_LISTE_ACQUISITIONS_MS	500
#define POSE_LUMIERE	0
#define POSE_DARK		1

#define TIMEOUT_ATTENTE_SUPERVCLIMSO_IMAGE_RECUE				60	// En s
#define TEMPS_BOUCLAGE_TEST_ATTENTE_SUPERVCLIMSO_IMAGE_RECUE	10	// En ms

#define TIMEOUT_ATTENTE_FILTREC2_EN_POSITION				60	// En s
#define TEMPS_BOUCLAGE_TEST_ATTENTE_FILTREC2_EN_POSITION	10	// En ms

#define POSE_SURFACE	0
#define POSE_COURONNE	1

#define NB_MAXI_NF_DERNIERES_IMAGES	30

#define TAILLE_X_LABEL_TEMPS_ECOULE_DER_IMG		110
#define TAILLE_Y_LABEL_TEMPS_ECOULE_DER_IMG		32

#define NB_TERMINOA	4							// Nombre de TerminOA que SupervCLIMSO doit superviser
#define TERMINOA_C1	0
#define TERMINOA_C2	1
#define TERMINOA_L1	2
#define TERMINOA_L2	3

#define TAILLE_Y_QHBOX_CTRL_TERMINOA			35
#define TAILLE_X_ICON_CTRL_TERMINOA				32
#define TAILLE_Y_ICON_CTRL_TERMINOA				32
#define TAILLE_X_LABEL_CTRL_TERMINOA			20
#define TAILLE_X_SPINBOX_SEUIL_CTRL_TERMINOA	70
#define TAILLE_X_SPINBOX_PUILUT_CTRL_TERMINOA	55

#define NB_SONDES_TEMPERATURE		8
#define TEMP_SONDE_AMBIANTE_COUPOLE				0
#define TEMP_SONDE_CAISSON_INFO					1
#define TEMP_SONDE_OCC_C1						2
#define TEMP_SONDE_FILTRE_C1					3
#define TEMP_SONDE_O3_C1						4
#define TEMP_SONDE_OCC_C2						5
#define TEMP_SONDE_FILTRES_C2					6
#define TEMP_SONDE_O3_C2						7
#define TEMPERATURE_NON_CONNUE			-275.0
#define TAILLE_X_LCD_TEMPERATURES		90
#define TAILLE_Y_LCD_TEMPERATURES		38
#define TAILLE_X_LABEL_TEMPERATURES		155
#define TAILLE_Y_LABEL_TEMPERATURES		38
#define COULEUR_LIGNE_TEMP_SONDE_OK		QColor(235,235,255)
#define COULEUR_LIGNE_TEMP_SONDE_NONOK	QColor(255,200,200)

#define TAILLE_X_FICHE_OBS_RECOMMANDEE		300
#define TAILLE_Y_FICHE_OBS_RECOMMANDEE		500
#define TAILLE_X_BOUTON_AJOUT_FICHE_OBS		60
#define TAILLE_Y_BOUTON_AJOUT_FICHE_OBS		32
#define COULEUR_FOND_EDIT_FICHE_OBS			QColor(255,255,230)
#define COULEUR_FOND_FICHE_OBS				QColor(221,236,255)
#define FICHIER_SAUV_FICHE_OBS	"ficheobs"

#define TEMPS_ATTENTE_AVANT_NOUVELLE_TENTATIVE_CONNEXION	2	// en secondes
#define TEMPS_ATTENTE_CONN_ARRET_SUPERVCLIMSO				15	// en secondes
#define POSITION_REPOS_ARRET_CLIMSO_PLATINE					0

#define POSITION_X_DEMARRAGE_CLIMSO_PLATINE	0
#define POSITION_Y_DEMARRAGE_CLIMSO_PLATINE	0


#define TAILLE_X_BOUTONS_SUPPR_ET_BASS	80
// Les images publiables sur BASS2000
//
#define NB_IMG_PUB_C1	4
#define NB_IMG_PUB_C2	12
#define NB_IMG_PUB_L1	4
#define NB_IMG_PUB_L2	4
#define TAILLE_X_LABEL_NOM_IMG_PUBLIABLE		490
#define TAILLE_Y_LABEL_NOM_IMG_PUBLIABLE		32
#define TAILLE_X_BOUTON_PUBLICATION_BASS2000	60
#define COULEUR_LIGNE_IMG_PUB_0					QColor(255,240,225)
#define COULEUR_LIGNE_IMG_PUB_1					QColor(225,240,255)


// Definitions pour les objets de visualisation des images de centrage des CamerOA
//
#define MAX_COMPOSANTES_RVB_OBJ_CENTRAGE	200

#define MIN_MATRICE_AMP_PROF	1
#define MAX_MATRICE_AMP_PROF	100

#define MIN_LARG_ZA_PROF		1.0
#define MAX_LARG_ZA_PROF		100.0

#define MIN_AMPLI_PROF			0.0
#define MAX_AMPLI_PROF			1000.0


// Les evenements
//
#define ID_CUSTOM_EVENT_SUPERVCLIMSO_NOUVIMG			30000
#define ID_CUSTOM_EVENT_SUPERVCLIMSO_NOUVIMGCENTRAGE	30001
#define ID_CUSTOM_EVENT_SUPERVCLIMSO_NOUVIMGCENTRAGEH	30002
#define ID_CUSTOM_EVENT_SUPERVCLIMSO_NOUVIMGCENTRAGEV	30003
#define ID_CUSTOM_EVENT_SUPERVCLIMSO_LOG				30004
#define ID_CUSTOM_EVENT_SUPERVCLIMSO_TEMPCCD			30005
#define ID_CUSTOM_EVENT_SUPERVCLIMSO_PUIPELTIER			30006
#define ID_CUSTOM_EVENT_SUPERVCLIMSO_IMGRECUETERMINOA	30007
#define ID_CUSTOM_EVENT_SUPERVCLIMSO_NOUVTEMPERATURES	30008
#define ID_CUSTOM_EVENT_SUPERVCLIMSO_INDEXAXETROUVE		30009
#define ID_CUSTOM_EVENT_SUPERVCLIMSO_INDEXAXENONTROUVE	30010
#define ID_CUSTOM_EVENT_SUPERVCLIMSO_POSAXES			30011
#define ID_CUSTOM_EVENT_SUPERVCLIMSO_FINLISTEACQ		30012
#define ID_CUSTOM_EVENT_SUPERVCLIMSO_ROTVFILTREC2		30013


// Les modes possibles de la roue d'ouverture de CLIMSO
//
enum ModeRoueOuvertureCLIMSO
{
	ModeRO_NonInitialise,
	ModeRO_Pointage,
	ModeRO_Calibration,
	ModeRO_PLU,
	ModeRO_Observation,
	ModeRO_SansMode			// Entre deux positions ou pas de mode
};

// Les filtres possibles de la roue a filtre de C2
//
enum FiltresC2CLIMSO
{
	FiltreC2_NonInitialise,
	FiltreC2_10747,
	FiltreC2_10770,
	FiltreC2_10798,
	FiltreC2_10830,
	FiltreC2_SansFiltre		// Entre deux positions ou pas de mode
};


// Predeclaration des classes pour imbrication de pointeurs entre processus
//
class SupervCLIMSO;
class ProcessusLegerClientCommandeRobOA;
class ProcessusLegerClientCommandeCamerOA;
class ProcessusLegerClientDonneesCamerOA;
class ProcessusLegerClientCommandeTerminOA;
class ProcessusLegerClientDonneesTerminOA;
class ProcessusLegerClientTemperatures;
class ProcessusLegerListeAcquisitionsC1;
class ProcessusLegerListeAcquisitionsC2;
class ProcessusLegerListeAcquisitionsL1;
class ProcessusLegerListeAcquisitionsL2;


// Classe de definition du thread d'un client chiffre vers un serveur chiffre RobOA
//
class ProcessusLegerClientCommandeRobOA : public QThread
{
private:
	int DrapeauDemandeTerminaison;			// Variable drapeau de demande de terminaison propre du processus
	int DrapeauConnexion;					// Variable drapeau d'autorisation de la connexion au serveur

	int PCI7334Initialise;					// Drapeau pour savoir si le materiel National Instrument est initialise

	int DrapeauDemandeRechIndexAxe[NB_AXES];	// Drapeau de demande de recherche de l'index de l'axe n
	int AxeEnRechercheIndex;					// Drapeau pour savoir si la recherche de l'index d'un axe est en cours

	// Copie des commandes et reponses dans l'objet pour etre thread safe (bogues avec QString)
	QString CmdClientRobOA[NB_CMD_CLIENT_ROBOA];	// Les commandes d'un client RobOA
	QString RepServeurRobOA[NB_REP_SERVEUR_ROBOA];	// Les reponses d'un serveur RobOA
	QString CmdSesame;
	QString CmdInit;
	QString CmdDeconnexion;

public:
	SupervCLIMSO *FPSupervCLIMSO;			// Pointeur sur l'objet fenetre principale de l'application

	// Pointeur vers un objet client chiffre
	//
	PointCommClientChiffre *Client;

	// Constructeur du thread
	//
	ProcessusLegerClientCommandeRobOA(SupervCLIMSO *pfp,uint32_t pAdresse,uint16_t pPort,int pTimeoutSocketPut,int pTimeoutSocketGet,int pParamSIGPIPE,void (*pFnHandlerSIGPIPE)(int),const char *pMdpClePriveeClient,char *pBuffStockMdpClePriveeClient,int (*pFnMotDePasseClePriveeChiffree)(char*, int, int, void*),const char *pCheminCertificatCA,const char *pCheminCertificatClient,const char *pCheminClePriveeClient);

	// Destructeur du thread
	//
	virtual ~ProcessusLegerClientCommandeRobOA();

	virtual void run();						// Surcharge de la methode run() qui contient le code d'execution du thread

	void DemandeTerminaison(void);			// Fonction de positionnement de la demande de terminaison propre du processus leger
	void ConnexionAutorisee(void);			// Fonction d'autorisation de la connexion au serveur
	void ConnexionNonAutorisee(void);		// Fonction de non autorisation de la connexion au serveur

	void DemandeRechercheIndexAxe(int n);	// Demande au thread d'initier la recherche de l'index codeur ou l'index de la position HOME de l'axe n

	int NI_Hardware_Initialise(void);		// Pour savoir si le materiel National Instrument est initialise au sens electronique
};


// Classe de definition du thread d'un client chiffre vers un serveur chiffre CamerOA (canal de commande)
//
class ProcessusLegerClientCommandeCamerOA : public QThread
{
private:
	int id;									// Identifieur du processus
	int DrapeauDemandeTerminaison;			// Variable drapeau de demande de terminaison propre du processus
	int DrapeauConnexion;					// Variable drapeau d'autorisation de la connexion au serveur

	// Copie des commandes et reponses dans l'objet pour etre thread safe (bogues avec QString)
	QString CmdClientCamerOA[NB_CMD_CLIENT_CAMEROA];	// Les commandes d'un client CamerOA
	QString RepServeurCamerOA[NB_REP_SERVEUR_CAMEROA];	// Les reponses d'un serveur CamerOA
	QString CmdSesame;
	QString CmdDeconnexion;

public:
	SupervCLIMSO *FPSupervCLIMSO;			// Pointeur sur l'objet fenetre principale de l'application

	// Pointeur vers un objet client chiffre
	//
	PointCommClientChiffre *Client;

	// Constructeur du thread
	//
	ProcessusLegerClientCommandeCamerOA(int pid,SupervCLIMSO *pfp,uint32_t pAdresse,uint16_t pPort,int pTimeoutSocketPut,int pTimeoutSocketGet,int pParamSIGPIPE,void (*pFnHandlerSIGPIPE)(int),const char *pMdpClePriveeClient,char *pBuffStockMdpClePriveeClient,int (*pFnMotDePasseClePriveeChiffree)(char*, int, int, void*),const char *pCheminCertificatCA,const char *pCheminCertificatClient,const char *pCheminClePriveeClient);

	// Destructeur du thread
	//
	virtual ~ProcessusLegerClientCommandeCamerOA();

	virtual void run();						// Surcharge de la methode run() qui contient le code d'execution du thread

	void DemandeTerminaison(void);			// Fonction de positionnement de la demande de terminaison propre du processus leger
	void ConnexionAutorisee(void);			// Fonction d'autorisation de la connexion au serveur
	void ConnexionNonAutorisee(void);		// Fonction de non autorisation de la connexion au serveur
};


// Classe de definition du thread d'un client non chiffre vers un serveur non chiffre CamerOA (canal des donnees)
//
class ProcessusLegerClientDonneesCamerOA : public QThread
{
private:
	int id;									// Identifieur du processus
	int DrapeauDemandeTerminaison;			// Variable drapeau de demande de terminaison propre du processus
	int DrapeauConnexion;					// Variable drapeau d'autorisation de la connexion au serveur

public:
	SupervCLIMSO *FPSupervCLIMSO;			// Pointeur sur l'objet fenetre principale de l'application

	QMutex MutexTrameImage;						// Mutex d'utilisation des donnees de la trame image
	struct EnteteTrameDonneesCamerOA EnTeteI;	// Structure de donnees d'entete d'une trame image
	std::valarray<unsigned short> TrameI;		// Donnees de la trame image courante dans un tableau de valeur de la STL C++

	QMutex MutexTrameImageC;					// Mutex d'utilisation des donnees de la trame image de centrage
	struct EnteteTrameDonneesCamerOA EnTeteIC;	// Structure de donnees d'entete d'une trame image de centrage
	std::valarray<unsigned short> TrameIC;		// Donnees de la trame image de centrage courante

	QMutex MutexTrameImageCH;					// Mutex d'utilisation des donnees de la trame image de centrage horizontal
	struct EnteteTrameDonneesCamerOA EnTeteICH;	// Structure de donnees d'entete d'une trame image de centrage horizontal
	std::valarray<unsigned short> TrameICH;		// Donnees de la trame image de centrage horizontal courante

	QMutex MutexTrameImageCV;					// Mutex d'utilisation des donnees de la trame image de centrage vertical
	struct EnteteTrameDonneesCamerOA EnTeteICV;	// Structure de donnees d'entete d'une trame image de centrage vertical
	std::valarray<unsigned short> TrameICV;		// Donnees de la trame image de centrage vertical courante


	// Pointeur vers un objet client non chiffre
	//
	PointCommClientNonChiffre *Client;

	// Constructeur du thread
	//
	ProcessusLegerClientDonneesCamerOA(int pid,SupervCLIMSO *pfp,uint32_t pAdresse,uint16_t pPort,int pTimeoutSocketPut,int pTimeoutSocketGet);

	// Destructeur du thread
	//
	virtual ~ProcessusLegerClientDonneesCamerOA();

	virtual void run();						// Surcharge de la methode run() qui contient le code d'execution du thread

	void DemandeTerminaison(void);			// Fonction de positionnement de la demande de terminaison propre du processus leger
	void ConnexionAutorisee(void);			// Fonction d'autorisation de la connexion au serveur
	void ConnexionNonAutorisee(void);		// Fonction de non autorisation de la connexion au serveur
};


// Classe de definition du thread d'une liste d'acquisitions d'images sur C1
//
class ProcessusLegerListeAcquisitionsC1 : public QThread
{
private:
	int DrapeauDemandeAcquisitions;			// Variable drapeau de demande d'une liste d'acquisitions
	int DrapeauDemandeTerminaison;			// Variable drapeau de demande de terminaison propre du processus

	ModeRoueOuvertureCLIMSO ContexteMode;	// Contexte de la roue d'ouverture au moment du declenchement de la pose
	int ContexteTypePose;					// Contexte du type de la pose POSE_IMAGE, POSE_DARK
	int ContextePoseC1Couronne;				// Contexte si on doit realiser une pose C1 couronne (on ne peut pas tester la chexkbox car non thread safe)

	// Copie des commandes dans l'objet pour etre thread safe (bogues avec QString inter processus)
	QString CmdClientCamerOA[NB_CMD_CLIENT_CAMEROA];		// Les commandes d'un client CamerOA
	QString CmdCamerOAPoseI;
	QString CmdCamerOAPoseDark;

public:
	SupervCLIMSO *FPSupervCLIMSO;					// Pointeur sur l'objet fenetre principale de l'application
	ProcessusLegerClientCommandeCamerOA *PLCamerOA;	// Pointeur sur le thread CamerOA associe a cette liste d'acquisitions

	// Constructeur du thread
	//
	ProcessusLegerListeAcquisitionsC1(SupervCLIMSO *pfp,ProcessusLegerClientCommandeCamerOA *pcam);

	// Destructeur du thread
	//
	virtual ~ProcessusLegerListeAcquisitionsC1();

	virtual void run();						// Surcharge de la methode run() qui contient le code d'execution du thread

	void DemandeListeAcquisitions(int ctxtypepose,ModeRoueOuvertureCLIMSO ctxpmode,int ctxc1cour);	// Fonction de demande d'une liste d'acquisitions en fonction d'un contexte
	void DemandeTerminaison(void);			// Fonction de positionnement de la demande de terminaison propre du processus leger
	int EnAcquisitions(void);				// Fonction pour savoir si une liste d'acquisitions est en cours
	int EnvoyerCommandePoseContexte(void);	// Fonction d'emission des commandes de pose (consigne temps pose + pose) sur le CamerOA de C1 selon le contexte
};


// Classe de definition du thread d'une liste d'acquisitions d'images sur C2
//
class ProcessusLegerListeAcquisitionsC2 : public QThread
{
private:
	int DrapeauDemandeAcquisitions;			// Variable drapeau de demande d'une liste d'acquisitions
	int DrapeauDemandeTerminaison;			// Variable drapeau de demande de terminaison propre du processus

	ModeRoueOuvertureCLIMSO ContexteMode;	// Contexte de la roue d'ouverture au moment du declenchement de la pose
	int ContexteTypePose;					// Contexte du type de la pose POSE_IMAGE, POSE_DARK
	int ContextePoseC2_10747;				// Contexte si on doit realiser une pose C2 10747 (on ne peut pas tester la chexkbox car non thread safe)
	int ContextePoseC2_10770;				// Contexte si on doit realiser une pose C2 10770 (on ne peut pas tester la chexkbox car non thread safe)
	int ContextePoseC2_10798;				// Contexte si on doit realiser une pose C2 10798 (on ne peut pas tester la chexkbox car non thread safe)
	int ContextePoseC2_10830;				// Contexte si on doit realiser une pose C2 10830 (on ne peut pas tester la chexkbox car non thread safe)

	int DrapeauImageRecue;					// Drapeau pour signifier qu'une image est recue par le superviseur

	// Copie des commandes dans l'objet pour etre thread safe (bogues avec QString inter processus)
	QString CmdClientCamerOA[NB_CMD_CLIENT_CAMEROA];		// Les commandes d'un client CamerOA
	QString CmdCamerOAPoseI;
	QString CmdCamerOAPoseDark;

public:
	SupervCLIMSO *FPSupervCLIMSO;					// Pointeur sur l'objet fenetre principale de l'application
	ProcessusLegerClientCommandeCamerOA *PLCamerOA;	// Pointeur sur le thread CamerOA associe a cette liste d'acquisitions

	// Constructeur du thread
	//
	ProcessusLegerListeAcquisitionsC2(SupervCLIMSO *pfp,ProcessusLegerClientCommandeCamerOA *pcam);

	// Destructeur du thread
	//
	virtual ~ProcessusLegerListeAcquisitionsC2();

	virtual void run();						// Surcharge de la methode run() qui contient le code d'execution du thread

	// Fonction de demande d'une liste d'acquisitions en fonction d'un contexte
	void DemandeListeAcquisitions(int ctxtypepose,ModeRoueOuvertureCLIMSO ctxpmode,int ctxc2_10747,int ctxc2_10770,int ctxc2_10798,int ctxc2_10830);
	void DemandeTerminaison(void);			// Fonction de positionnement de la demande de terminaison propre du processus leger
	int EnAcquisitions(void);				// Fonction pour savoir si une liste d'acquisitions est en cours
	int EnvoyerCommandePoseContexte(FiltresC2CLIMSO FiltreC2);	// Fonction d'emission des commandes de pose (consigne temps pose + pose) sur le CamerOA de C2 selon le contexte
	int AttendreFiltreC2(FiltresC2CLIMSO FiltreC2);				// Fonction d'attente qu'un filtre soit positionne dans un temps imparti
	void ImageRecue(void);										// Fonction appelee par le processus principal de SupervCLIMSO pour signifier qu'une nouvelle image attendue est recue
	int AttendreReceptionImage(void);							// Fonction d'attente de la reception d'une image dans un temps imparti
};


// Classe de definition du thread d'une liste d'acquisitions d'images sur L1
//
class ProcessusLegerListeAcquisitionsL1 : public QThread
{
private:
	int DrapeauDemandeAcquisitions;			// Variable drapeau de demande d'une liste d'acquisitions
	int DrapeauDemandeTerminaison;			// Variable drapeau de demande de terminaison propre du processus

	ModeRoueOuvertureCLIMSO ContexteMode;	// Contexte de la roue d'ouverture au moment du declenchement de la pose
	int ContexteTypePose;					// Contexte du type de la pose POSE_IMAGE, POSE_DARK
	int ContextePoseL1S;					// Contexte si on doit realiser une pose L1 surface (on ne peut pas tester la chexkbox car non thread safe)
	int ContextePoseL1C;					// Contexte si on doit realiser une pose L1 couronne (on ne peut pas tester la chexkbox car non thread safe)

	int DrapeauImageRecue;					// Drapeau pour signifier qu'une image est recue par le superviseur

	// Copie des commandes dans l'objet pour etre thread safe (bogues avec QString inter processus)
	QString CmdClientCamerOA[NB_CMD_CLIENT_CAMEROA];		// Les commandes d'un client CamerOA
	QString CmdCamerOAPoseI;
	QString CmdCamerOAPoseDark;

public:
	SupervCLIMSO *FPSupervCLIMSO;					// Pointeur sur l'objet fenetre principale de l'application
	ProcessusLegerClientCommandeCamerOA *PLCamerOA;	// Pointeur sur le thread CamerOA associe a cette liste d'acquisitions

	// Constructeur du thread
	//
	ProcessusLegerListeAcquisitionsL1(SupervCLIMSO *pfp,ProcessusLegerClientCommandeCamerOA *pcam);

	// Destructeur du thread
	//
	virtual ~ProcessusLegerListeAcquisitionsL1();

	virtual void run();						// Surcharge de la methode run() qui contient le code d'execution du thread

	// Fonction de demande d'une liste d'acquisitions en fonction d'un contexte
	void DemandeListeAcquisitions(int ctxtypepose,ModeRoueOuvertureCLIMSO ctxpmode,int ctxl1s,int ctxl1c);
	void DemandeTerminaison(void);			// Fonction de positionnement de la demande de terminaison propre du processus leger
	int EnAcquisitions(void);				// Fonction pour savoir si une liste d'acquisitions est en cours
	int EnvoyerCommandePoseContexte(int designation);	// Fonction d'emission des commandes de pose (consigne temps pose + pose) sur le CamerOA de L1 selon le contexte
	void ImageRecue(void);								// Fonction appelee par le processus principal de SupervCLIMSO pour signifier qu'une nouvelle image attendue est recue
	int AttendreReceptionImage(void);					// Fonction d'attente de la reception d'une image dans un temps imparti
};


// Classe de definition du thread d'une liste d'acquisitions d'images sur L2
//
class ProcessusLegerListeAcquisitionsL2 : public QThread
{
private:
	int DrapeauDemandeAcquisitions;			// Variable drapeau de demande d'une liste d'acquisitions
	int DrapeauDemandeTerminaison;			// Variable drapeau de demande de terminaison propre du processus

	ModeRoueOuvertureCLIMSO ContexteMode;	// Contexte de la roue d'ouverture au moment du declenchement de la pose
	int ContexteTypePose;					// Contexte du type de la pose POSE_IMAGE, POSE_DARK
	int ContextePoseL2S;					// Contexte si on doit realiser une pose L2 surface (on ne peut pas tester la chexkbox car non thread safe)
	int ContextePoseL2C;					// Contexte si on doit realiser une pose L2 couronne (on ne peut pas tester la chexkbox car non thread safe)

	int DrapeauImageRecue;					// Drapeau pour signifier qu'une image est recue par le superviseur

	// Copie des commandes dans l'objet pour etre thread safe (bogues avec QString inter processus)
	QString CmdClientCamerOA[NB_CMD_CLIENT_CAMEROA];		// Les commandes d'un client CamerOA
	QString CmdCamerOAPoseI;
	QString CmdCamerOAPoseDark;

public:
	SupervCLIMSO *FPSupervCLIMSO;					// Pointeur sur l'objet fenetre principale de l'application
	ProcessusLegerClientCommandeCamerOA *PLCamerOA;	// Pointeur sur le thread CamerOA associe a cette liste d'acquisitions

	// Constructeur du thread
	//
	ProcessusLegerListeAcquisitionsL2(SupervCLIMSO *pfp,ProcessusLegerClientCommandeCamerOA *pcam);

	// Destructeur du thread
	//
	virtual ~ProcessusLegerListeAcquisitionsL2();

	virtual void run();						// Surcharge de la methode run() qui contient le code d'execution du thread

	// Fonction de demande d'une liste d'acquisitions en fonction d'un contexte
	void DemandeListeAcquisitions(int ctxtypepose,ModeRoueOuvertureCLIMSO ctxpmode,int ctxl2s,int ctxc2c);
	void DemandeTerminaison(void);			// Fonction de positionnement de la demande de terminaison propre du processus leger
	int EnAcquisitions(void);				// Fonction pour savoir si une liste d'acquisitions est en cours
	int EnvoyerCommandePoseContexte(int designation);	// Fonction d'emission des commandes de pose (consigne temps pose + pose) sur le CamerOA de L2 selon le contexte
	void ImageRecue(void);								// Fonction appelee par le processus principal de SupervCLIMSO pour signifier qu'une nouvelle image attendue est recue
	int AttendreReceptionImage(void);					// Fonction d'attente de la reception d'une image dans un temps imparti
};


// Classe de definition du thread d'un client chiffre vers un serveur chiffre TerminOA (canal de commande)
//
class ProcessusLegerClientCommandeTerminOA : public QThread
{
private:
	int id;									// Identifieur du processus
	int DrapeauDemandeTerminaison;			// Variable drapeau de demande de terminaison propre du processus
	int DrapeauConnexion;					// Variable drapeau d'autorisation de la connexion au serveur

	// Copie des commandes et reponses dans l'objet pour etre thread safe (bogues avec QString)
	QString CmdClientTerminOA[NB_CMD_CLIENT_TERMINOA];		// Les commandes d'un client TerminOA
	QString RepServeurTerminOA[NB_REP_SERVEUR_TERMINOA];	// Les reponses d'un serveur TerminOA
	QString CmdSesame;
	QString CmdAttente;
	QString CmdDeconnexion;

public:
	SupervCLIMSO *FPSupervCLIMSO;			// Pointeur sur l'objet fenetre principale de l'application

	// Pointeur vers un objet client chiffre
	//
	PointCommClientChiffre *Client;

	// Constructeur du thread
	//
	ProcessusLegerClientCommandeTerminOA(int pid,SupervCLIMSO *pfp,uint32_t pAdresse,uint16_t pPort,int pTimeoutSocketPut,int pTimeoutSocketGet,int pParamSIGPIPE,void (*pFnHandlerSIGPIPE)(int),const char *pMdpClePriveeClient,char *pBuffStockMdpClePriveeClient,int (*pFnMotDePasseClePriveeChiffree)(char*, int, int, void*),const char *pCheminCertificatCA,const char *pCheminCertificatClient,const char *pCheminClePriveeClient);

	// Destructeur du thread
	//
	virtual ~ProcessusLegerClientCommandeTerminOA();

	virtual void run();						// Surcharge de la methode run() qui contient le code d'execution du thread

	void DemandeTerminaison(void);			// Fonction de positionnement de la demande de terminaison propre du processus leger
	void ConnexionAutorisee(void);			// Fonction d'autorisation de la connexion au serveur
	void ConnexionNonAutorisee(void);		// Fonction de non autorisation de la connexion au serveur
};



// Classe de definition du thread d'un client non chiffre vers un serveur non chiffre TerminOA (canal des donnees)
//
class ProcessusLegerClientDonneesTerminOA : public QThread
{
private:
	int id;									// Identifieur du processus
	int DrapeauDemandeTerminaison;			// Variable drapeau de demande de terminaison propre du processus
	int DrapeauConnexion;					// Variable drapeau d'autorisation de la connexion au serveur

public:
	SupervCLIMSO *FPSupervCLIMSO;			// Pointeur sur l'objet fenetre principale de l'application


	// Pointeur vers un objet client non chiffre
	//
	PointCommClientNonChiffre *Client;

	QMutex MutexEmission;					// Mutex pour l'emission atomique des trames

	// Constructeur du thread
	//
	ProcessusLegerClientDonneesTerminOA(int pid,SupervCLIMSO *pfp,uint32_t pAdresse,uint16_t pPort,int pTimeoutSocketPut,int pTimeoutSocketGet);

	// Destructeur du thread
	//
	virtual ~ProcessusLegerClientDonneesTerminOA();

	virtual void run();						// Surcharge de la methode run() qui contient le code d'execution du thread

	void DemandeTerminaison(void);			// Fonction de positionnement de la demande de terminaison propre du processus leger
	void ConnexionAutorisee(void);			// Fonction d'autorisation de la connexion au serveur
	void ConnexionNonAutorisee(void);		// Fonction de non autorisation de la connexion au serveur
};


// Classe de definition du thread du client non chiffre vers un serveur de temperatures
//
class ProcessusLegerClientTemperatures : public QThread
{
private:
	int DrapeauDemandeTerminaison;			// Variable drapeau de demande de terminaison propre du processus
	int DrapeauConnexion;					// Variable drapeau d'autorisation de la connexion au serveur

public:
	SupervCLIMSO *FPSupervCLIMSO;			// Pointeur sur l'objet fenetre principale de l'application

	// Pointeur vers un objet client non chiffre
	//
	PointCommClientNonChiffre *Client;

	// Indicateur de premier rafraichissement
	//
	int PremierRafraichissement;

	// Valeur de la temperature sur les sondes
	//
	double T[NB_SONDES_TEMPERATURE];

	// Date et heure de la prise de temperature en UT
	//
	QDateTime t_UT;

	// Constructeur du thread
	//
	ProcessusLegerClientTemperatures(SupervCLIMSO *pfp,uint32_t pAdresse,uint16_t pPort,int pTimeoutSocketPut,int pTimeoutSocketGet);

	// Destructeur du thread
	//
	virtual ~ProcessusLegerClientTemperatures();

	virtual void run();						// Surcharge de la methode run() qui contient le code d'execution du thread

	void DemandeTerminaison(void);			// Fonction de positionnement de la demande de terminaison propre du processus leger
	void ConnexionAutorisee(void);			// Fonction d'autorisation de la connexion au serveur
	void ConnexionNonAutorisee(void);		// Fonction de non autorisation de la connexion au serveur
};



// Objet de visualisation des images de centrage des CamerOA
//
// Il herite de QDialog pour pouvoir surcharger l'evenement closeEvent(). En effet, le bouton de fermeture de la fenetre QDialog
//  depend du WindowsManager X et pas du QWidget donc il faut surcharger closeEvent et ignorer le signal close().
// La seule autre solution serait de creer la fenetre dialogue avec le drapeau Qt::WStyle_NoBorder mais la fenetre n'a plus de bords
//  du windows manager et n'est plus deplacable, n'a plus de titre...
//
class DialogFenetreCamerOA : public QDialog
{
public:
	DialogFenetreCamerOA(QWidget *parent,const char *name,bool modal,WFlags f);

	void closeEvent(QCloseEvent *e);	// pour surcharger est ignorer close()
};



// Objet de visualisation des temperatures
//
// Il herite de QDialog pour pouvoir surcharger l'evenement closeEvent(). En effet, le bouton de fermeture de la fenetre QDialog
//  depend du WindowsManager X et pas du QWidget donc il faut surcharger closeEvent et ignorer le signal close().
// La seule autre solution serait de creer la fenetre dialogue avec le drapeau Qt::WStyle_NoBorder mais la fenetre n'a plus de bords
//  du windows manager et n'est plus deplacable, n'a plus de titre...
//
class DialogFenetreTemperatures : public QDialog
{
public:
	DialogFenetreTemperatures(QWidget *parent,const char *name,bool modal,WFlags f);

	void closeEvent(QCloseEvent *e);	// pour surcharger est ignorer close()
};



// Objet de controle des TerminOA de visualisation
//
// Il herite de QDialog pour pouvoir surcharger l'evenement closeEvent(). En effet, le bouton de fermeture de la fenetre QDialog
//  depend du WindowsManager X et pas du QWidget donc il faut surcharger closeEvent et ignorer le signal close().
// La seule autre solution serait de creer la fenetre dialogue avec le drapeau Qt::WStyle_NoBorder mais la fenetre n'a plus de bords
//  du windows manager et n'est plus deplacable, n'a plus de titre...
//
class DialogFenetreCtrlTerminOA : public QDialog
{
public:
	DialogFenetreCtrlTerminOA(QWidget *parent,const char *name,bool modal,WFlags f);

	void closeEvent(QCloseEvent *e);	// pour surcharger est ignorer close()
};



// Objet de la fiche d'observation de CLIMSO
//
// Il herite de QDialog pour pouvoir surcharger l'evenement closeEvent(). En effet, le bouton de fermeture de la fenetre QDialog
//  depend du WindowsManager X et pas du QWidget donc il faut surcharger closeEvent et ignorer le signal close().
// La seule autre solution serait de creer la fenetre dialogue avec le drapeau Qt::WStyle_NoBorder mais la fenetre n'a plus de bords
//  du windows manager et n'est plus deplacable, n'a plus de titre...
//
class DialogFenetreFicheObservation : public QDialog
{
    Q_OBJECT

protected slots:
	void SlotBoutonAjouter(void);					// Slot du bouton de demande d'ajout de la ligne saisie dans la fiche d'observation

public:
	DialogFenetreFicheObservation(QWidget *parent,const char *name,bool modal,WFlags f);

	void closeEvent(QCloseEvent *e);				// pour surcharger est ignorer close()
	void paintEvent(QPaintEvent *event);			// pour surcharger l'evenement de demande d'affichage du contenu de la fenetre

	QVBox *BRVFenetreFicheObservation;				// Boite de rangement vertical dans la fenetre de la fiche d'observation
	QHBox *BRHFenetreFicheObservation1;				// Boite de rangement horizontal de la fiche d'observation
	QHBox *BRHFenetreFicheObservation2;				// Boite de rangement horizontal de la ligne de saisie de la fiche d'observation
	QTextEdit *FicheObservation;					// Fiche d'observation de CLIMSO
	QLineEdit *EditFicheObservation;				// Ligne d'edition de la fiche d'observation
	QPushButton *BoutonAjouterFicheObservation;		// Bouton d'ajout de la ligne saisie dans la fiche d'observation

	QFile FichierFicheObservation;					// Fichier de sauvegarde de la fiche d'observation
	QTextStream FluxFichierFicheObservation;		// Flux en mode texte du fichier de sauvegarde de la fiche d'observation
};



// Classe de la fenetre principale de l'application SupervCLIMSO
//
class SupervCLIMSO : public KMainWindow
{
    Q_OBJECT

protected slots:
	void paintEvent(QPaintEvent *event);		// Surcharge du slot herite de QWidget
	void SlotPulsar1s(void);					// Slot pour le signal timeout() du QTimer Pulsar1s de pulsation de la seconde

public slots:
	void SlotBoutonInitialisationAxes(void);	// Slot du bouton de demande d'initialisation des axes de CLIMSO
	void SlotBoutonConsignes(void);				// Slot du bouton de demande de la fenetre de saisie des consignes
	void SlotBoutonModePointage(void);			// Slot du bouton de demande de passage de CLIMSO en mode pointage
	void SlotBoutonModePLU(void);				// Slot du bouton de demande de passage de CLIMSO en mode PLU
	void SlotBoutonModeCalibration(void);		// Slot du bouton de demande de passage de CLIMSO en mode calibration
	void SlotBoutonModeObservation(void);		// Slot du bouton de demande de passage de CLIMSO en mode observation
	void SlotBouton10747(void);					// Slot du bouton de demande de passage en filtre C2 10747 nm
	void SlotBouton10770(void);					// Slot du bouton de demande de passage en filtre C2 10770 nm
	void SlotBouton10798(void);					// Slot du bouton de demande de passage en filtre C2 10798 nm
	void SlotBouton10830(void);					// Slot du bouton de demande de passage en filtre C2 10830 nm
	void SlotSpinBoxDeltaXC2(int value);		// Slot du widget d'entree de la consigne de decalage en x de C2
	void SlotSpinBoxDeltaYC2(int value);		// Slot du widget d'entree de la consigne de decalage en y de C2
	void SlotBoutonPoseImageC1(void);			// Slot du bouton de demande de pose image pour C1
	void SlotBoutonPoseImageC2(void);			// Slot du bouton de demande de pose image pour C2
	void SlotBoutonPoseImageL1(void);			// Slot du bouton de demande de pose image pour L1
	void SlotBoutonPoseImageL2(void);			// Slot du bouton de demande de pose image pour L2
	void SlotBoutonPoseBiasC1(void);			// Slot du bouton de demande de pose bias pour C1
	void SlotBoutonPoseBiasC2(void);			// Slot du bouton de demande de pose bias pour C2
	void SlotBoutonPoseBiasL1(void);			// Slot du bouton de demande de pose bias pour L1
	void SlotBoutonPoseBiasL2(void);			// Slot du bouton de demande de pose bias pour L2
	void SlotBoutonPoseDarkC1(void);			// Slot du bouton de demande de pose dark pour C1
	void SlotBoutonPoseDarkC2(void);			// Slot du bouton de demande de pose dark pour C2
	void SlotBoutonPoseDarkL1(void);			// Slot du bouton de demande de pose dark pour L1
	void SlotBoutonPoseDarkL2(void);			// Slot du bouton de demande de pose dark pour L2
	void SlotBoutonEtatC1(void);				// Slot du bouton etat de C1
	void SlotBoutonEtatC2(void);				// Slot du bouton etat de C2
	void SlotBoutonEtatL1(void);				// Slot du bouton etat de L1
	void SlotBoutonEtatL2(void);				// Slot du bouton etat de L2
	void SlotBoutonPosesBias(void);				// Slot du bouton de demande de poses de bias
	void SlotBoutonPosesDark(void);				// Slot du bouton de demande de poses de dark
	void SlotBoutonSequencePosesImages(void);	// Slot du bouton de demande de sequence de poses images
	void SlotBoutonSuppressionDerImgC1(void);	// Slot du bouton de demande de suppression de la derniere image acquise par C1
	void SlotBoutonSuppressionDerImgC2(void);	// Slot du bouton de demande de suppression de la derniere image acquise par C2
	void SlotBoutonSuppressionDerImgL1(void);	// Slot du bouton de demande de suppression de la derniere image acquise par L1
	void SlotBoutonSuppressionDerImgL2(void);	// Slot du bouton de demande de suppression de la derniere image acquise par L2
	void SlotBoutonTransfertBASS2000C1(void);	// Slot du bouton de demande de transfert de la derniere image acquise par C1
	void SlotBoutonTransfertBASS2000C2(void);	// Slot du bouton de demande de transfert de la derniere image acquise par C2
	void SlotBoutonTransfertBASS2000L1(void);	// Slot du bouton de demande de transfert de la derniere image acquise par L1
	void SlotBoutonTransfertBASS2000L2(void);	// Slot du bouton de demande de transfert de la derniere image acquise par L2
	void SlotCBAcqAutoC1(void);					// Slot du checkbox de passage de C1 en mode de pose automatique
	void SlotCBAcqAutoC2(void);					// Slot du checkbox de passage de C2 en mode de pose automatique
	void SlotCBAcqAutoL1(void);					// Slot du checkbox de passage de L1 en mode de pose automatique
	void SlotCBAcqAutoL2(void);					// Slot du checkbox de passage de L2 en mode de pose automatique
	void SlotCBCompoSeqAcqC1(void);				// Slot de selection de l'acquisition C1 h-alpha pour la sequence d'acquitions de C1
	void SlotCBCompoSeqAcqC2_10747(void);		// Slot de selection de l'acquisition C2 10747 pour la sequence d'acquitions de C2
	void SlotCBCompoSeqAcqC2_10770(void);		// Slot de selection de l'acquisition C2 10770 pour la sequence d'acquitions de C2
	void SlotCBCompoSeqAcqC2_10798(void);		// Slot de selection de l'acquisition C2 10798 pour la sequence d'acquitions de C2
	void SlotCBCompoSeqAcqC2_10830(void);		// Slot de selection de l'acquisition C2 10830 pour la sequence d'acquitions de C2
	void SlotCBCompoSeqAcqL1S(void);			// Slot de selection de l'acquisition L1 surface pour la sequence d'acquitions de L1
	void SlotCBCompoSeqAcqL1C(void);			// Slot de selection de l'acquisition L1 couronne pour la sequence d'acquitions de L1
	void SlotCBCompoSeqAcqL2S(void);			// Slot de selection de l'acquisition L2 surface pour la sequence d'acquitions de L2
	void SlotCBCompoSeqAcqL2C(void);			// Slot de selection de l'acquisition L2 couronne pour la sequence d'acquitions de L2

	// Slots du TerminOA 0 : C1
	void SlotBoutonModeIC_0(void);				// Slot pour le passage en mode affichage de l'image courante
	void SlotBoutonModeDiapo_0(void);			// Slot pour le passage en mode diaporama
	void SlotBoutonEchLin_0(void);				// Slot pour le passage en echelle de representation histogramme lineaire
	void SlotBoutonEchLog_0(void);				// Slot pour le passage en echelle de representation histogramme logarithmique
	void SlotBoutonPalNB_0(void);				// Slot pour le passage en palette noir et blanc
	void SlotBoutonPalHalpha_0(void);			// Slot pour le passage en palette h-alpha
	void SlotBoutonPalNoirOrangeBlanc_0(void);	// Slot pour le passage en palette noir-orange-blanc
	void SlotBoutonPalNoirVertBlanc_0(void);	// Slot pour le passage en palette noir-vert-blanc
	void SlotBoutonPalNoirBleuBlanc_0(void);	// Slot pour le passage en palette noir-bleu-blanc
	void SlotBoutonZ0_0(void);					// Slot pour le passage en visualisation zone Z0
	void SlotBoutonZ1_0(void);					// Slot pour le passage en visualisation zone Z1
	void SlotBoutonZ2_0(void);					// Slot pour le passage en visualisation zone Z2
	void SlotBoutonZ3_0(void);					// Slot pour le passage en visualisation zone Z3
	void SlotBoutonZ4_0(void);					// Slot pour le passage en visualisation zone Z4
	void SlotBoutonZ5_0(void);					// Slot pour le passage en visualisation zone Z5
	void SlotBoutonZ6_0(void);					// Slot pour le passage en visualisation zone Z6
	void SlotBoutonZ7_0(void);					// Slot pour le passage en visualisation zone Z7
	void SlotBoutonZ8_0(void);					// Slot pour le passage en visualisation zone Z8
	void SlotBoutonZ9_0(void);					// Slot pour le passage en visualisation zone Z9
	void SlotSpinBoxCSB_0(int value);			// Slot pour le changement de la valeur de la spinbox de la consigne seuil bas
	void SlotSpinBoxCSH_0(int value);			// Slot pour le changement de la valeur de la spinbox de la consigne seuil haut
	void SlotSpinBoxCPuiLUT_0(int value);		// Slot pour le changement de la valeur de la spinbox de la consigne puissance lut

	// Slots du TerminOA 1 : C2
	void SlotBoutonModeIC_1(void);				// Slot pour le passage en mode affichage de l'image courante
	void SlotBoutonModeDiapo_1(void);			// Slot pour le passage en mode diaporama
	void SlotBoutonEchLin_1(void);				// Slot pour le passage en echelle de representation histogramme lineaire
	void SlotBoutonEchLog_1(void);				// Slot pour le passage en echelle de representation histogramme logarithmique
	void SlotBoutonPalNB_1(void);				// Slot pour le passage en palette noir et blanc
	void SlotBoutonPalHalpha_1(void);			// Slot pour le passage en palette h-alpha
	void SlotBoutonPalNoirOrangeBlanc_1(void);	// Slot pour le passage en palette noir-orange-blanc
	void SlotBoutonPalNoirVertBlanc_1(void);	// Slot pour le passage en palette noir-vert-blanc
	void SlotBoutonPalNoirBleuBlanc_1(void);	// Slot pour le passage en palette noir-bleu-blanc
	void SlotBoutonZ0_1(void);					// Slot pour le passage en visualisation zone Z0
	void SlotBoutonZ1_1(void);					// Slot pour le passage en visualisation zone Z1
	void SlotBoutonZ2_1(void);					// Slot pour le passage en visualisation zone Z2
	void SlotBoutonZ3_1(void);					// Slot pour le passage en visualisation zone Z3
	void SlotBoutonZ4_1(void);					// Slot pour le passage en visualisation zone Z4
	void SlotBoutonZ5_1(void);					// Slot pour le passage en visualisation zone Z5
	void SlotBoutonZ6_1(void);					// Slot pour le passage en visualisation zone Z6
	void SlotBoutonZ7_1(void);					// Slot pour le passage en visualisation zone Z7
	void SlotBoutonZ8_1(void);					// Slot pour le passage en visualisation zone Z8
	void SlotBoutonZ9_1(void);					// Slot pour le passage en visualisation zone Z9
	void SlotSpinBoxCSB_1(int value);			// Slot pour le changement de la valeur de la spinbox de la consigne seuil bas
	void SlotSpinBoxCSH_1(int value);			// Slot pour le changement de la valeur de la spinbox de la consigne seuil haut
	void SlotSpinBoxCPuiLUT_1(int value);		// Slot pour le changement de la valeur de la spinbox de la consigne puissance lut

	// Slots du TerminOA 2 : L1
	void SlotBoutonModeIC_2(void);				// Slot pour le passage en mode affichage de l'image courante
	void SlotBoutonModeDiapo_2(void);			// Slot pour le passage en mode diaporama
	void SlotBoutonEchLin_2(void);				// Slot pour le passage en echelle de representation histogramme lineaire
	void SlotBoutonEchLog_2(void);				// Slot pour le passage en echelle de representation histogramme logarithmique
	void SlotBoutonPalNB_2(void);				// Slot pour le passage en palette noir et blanc
	void SlotBoutonPalHalpha_2(void);			// Slot pour le passage en palette h-alpha
	void SlotBoutonPalNoirOrangeBlanc_2(void);	// Slot pour le passage en palette noir-orange-blanc
	void SlotBoutonPalNoirVertBlanc_2(void);	// Slot pour le passage en palette noir-vert-blanc
	void SlotBoutonPalNoirBleuBlanc_2(void);	// Slot pour le passage en palette noir-bleu-blanc
	void SlotBoutonZ0_2(void);					// Slot pour le passage en visualisation zone Z0
	void SlotBoutonZ1_2(void);					// Slot pour le passage en visualisation zone Z1
	void SlotBoutonZ2_2(void);					// Slot pour le passage en visualisation zone Z2
	void SlotBoutonZ3_2(void);					// Slot pour le passage en visualisation zone Z3
	void SlotBoutonZ4_2(void);					// Slot pour le passage en visualisation zone Z4
	void SlotBoutonZ5_2(void);					// Slot pour le passage en visualisation zone Z5
	void SlotBoutonZ6_2(void);					// Slot pour le passage en visualisation zone Z6
	void SlotBoutonZ7_2(void);					// Slot pour le passage en visualisation zone Z7
	void SlotBoutonZ8_2(void);					// Slot pour le passage en visualisation zone Z8
	void SlotBoutonZ9_2(void);					// Slot pour le passage en visualisation zone Z9
	void SlotSpinBoxCSB_2(int value);			// Slot pour le changement de la valeur de la spinbox de la consigne seuil bas
	void SlotSpinBoxCSH_2(int value);			// Slot pour le changement de la valeur de la spinbox de la consigne seuil haut
	void SlotSpinBoxCPuiLUT_2(int value);		// Slot pour le changement de la valeur de la spinbox de la consigne puissance lut

	// Slots du TerminOA 3 : L2
	void SlotBoutonModeIC_3(void);				// Slot pour le passage en mode affichage de l'image courante
	void SlotBoutonModeDiapo_3(void);			// Slot pour le passage en mode diaporama
	void SlotBoutonEchLin_3(void);				// Slot pour le passage en echelle de representation histogramme lineaire
	void SlotBoutonEchLog_3(void);				// Slot pour le passage en echelle de representation histogramme logarithmique
	void SlotBoutonPalNB_3(void);				// Slot pour le passage en palette noir et blanc
	void SlotBoutonPalHalpha_3(void);			// Slot pour le passage en palette h-alpha
	void SlotBoutonPalNoirOrangeBlanc_3(void);	// Slot pour le passage en palette noir-orange-blanc
	void SlotBoutonPalNoirVertBlanc_3(void);	// Slot pour le passage en palette noir-vert-blanc
	void SlotBoutonPalNoirBleuBlanc_3(void);	// Slot pour le passage en palette noir-bleu-blanc
	void SlotBoutonZ0_3(void);					// Slot pour le passage en visualisation zone Z0
	void SlotBoutonZ1_3(void);					// Slot pour le passage en visualisation zone Z1
	void SlotBoutonZ2_3(void);					// Slot pour le passage en visualisation zone Z2
	void SlotBoutonZ3_3(void);					// Slot pour le passage en visualisation zone Z3
	void SlotBoutonZ4_3(void);					// Slot pour le passage en visualisation zone Z4
	void SlotBoutonZ5_3(void);					// Slot pour le passage en visualisation zone Z5
	void SlotBoutonZ6_3(void);					// Slot pour le passage en visualisation zone Z6
	void SlotBoutonZ7_3(void);					// Slot pour le passage en visualisation zone Z7
	void SlotBoutonZ8_3(void);					// Slot pour le passage en visualisation zone Z8
	void SlotBoutonZ9_3(void);					// Slot pour le passage en visualisation zone Z9
	void SlotSpinBoxCSB_3(int value);			// Slot pour le changement de la valeur de la spinbox de la consigne seuil bas
	void SlotSpinBoxCSH_3(int value);			// Slot pour le changement de la valeur de la spinbox de la consigne seuil haut
	void SlotSpinBoxCPuiLUT_3(int value);		// Slot pour le changement de la valeur de la spinbox de la consigne puissance lut

	// Slots des boutons de publication sur BASS2000
	//
	void SlotBoutonPubliC1_0(void);				// Slot pour la publication de l'image C1 du label 0
	void SlotBoutonPubliC1_1(void);				// Slot pour la publication de l'image C1 du label 1
	void SlotBoutonPubliC1_2(void);				// Slot pour la publication de l'image C1 du label 2
	void SlotBoutonPubliC1_3(void);				// Slot pour la publication de l'image C1 du label 3

	void SlotBoutonPubliC2_0(void);				// Slot pour la publication de l'image C2 du label 0
	void SlotBoutonPubliC2_1(void);				// Slot pour la publication de l'image C2 du label 1
	void SlotBoutonPubliC2_2(void);				// Slot pour la publication de l'image C2 du label 2
	void SlotBoutonPubliC2_3(void);				// Slot pour la publication de l'image C2 du label 3
	void SlotBoutonPubliC2_4(void);				// Slot pour la publication de l'image C2 du label 4
	void SlotBoutonPubliC2_5(void);				// Slot pour la publication de l'image C2 du label 5
	void SlotBoutonPubliC2_6(void);				// Slot pour la publication de l'image C2 du label 6
	void SlotBoutonPubliC2_7(void);				// Slot pour la publication de l'image C2 du label 7
	void SlotBoutonPubliC2_8(void);				// Slot pour la publication de l'image C2 du label 8
	void SlotBoutonPubliC2_9(void);				// Slot pour la publication de l'image C2 du label 9
	void SlotBoutonPubliC2_10(void);			// Slot pour la publication de l'image C2 du label 10
	void SlotBoutonPubliC2_11(void);			// Slot pour la publication de l'image C2 du label 11

	void SlotBoutonPubliL1_0(void);				// Slot pour la publication de l'image L1 du label 0
	void SlotBoutonPubliL1_1(void);				// Slot pour la publication de l'image L1 du label 1
	void SlotBoutonPubliL1_2(void);				// Slot pour la publication de l'image L1 du label 2
	void SlotBoutonPubliL1_3(void);				// Slot pour la publication de l'image L1 du label 3

	void SlotBoutonPubliL2_0(void);				// Slot pour la publication de l'image L2 du label 0
	void SlotBoutonPubliL2_1(void);				// Slot pour la publication de l'image L2 du label 1
	void SlotBoutonPubliL2_2(void);				// Slot pour la publication de l'image L2 du label 2
	void SlotBoutonPubliL2_3(void);				// Slot pour la publication de l'image L2 du label 3


protected:
	QString CheminRepSuperviseur;				// Chemin vers le repertoire de base du superviseur
	QString CheminStockageDonnees;				// Chemin vers le repertoire de stockage des donnees acquises

	QFile FichierLogsSupervCLIMSO;				// Fichier de sauvegarde des logs de SupervCLIMSO
	QTextStream FluxFichierLogsSupervCLIMSO;	// Flux en mode texte du fichier de sauvegarde des logs de SupervCLIMSO

	QFile FichierTemperatures;					// Fichier de sauvegarde des valeurs de la temperature
	QTextStream FluxFichierTemperatures;		// Flux en mode texte du fichier de sauvegarde des valeurs de la temperature

	QPalette PaletteBoutonVerdatre;				// Palette verdatre des couleurs des QPushButton selon leur etat
	QPalette PaletteBoutonOrangee;				// Palette orangee des couleurs des QPushButton selon leur etat

	double Po;		// P.A. de l'axe de rotation du Soleil en radians
	double Lo;		// Longitude heliographique du centre du dique solaire en radians
	double Bo;		// Latitude heliographique du centre du disque solaire en radians

public:
												// Constructeur non typable mais avec des argument(s)
	SupervCLIMSO(QString p_chemRepSuperviseur,KApplication *p_appli);

	virtual ~SupervCLIMSO();					// Destructeur non typable

	void customEvent(QCustomEvent *ce);			// Surcharge de la fonction de handler des evenements particuliers
	void closeEvent(QCloseEvent *e);			// Surcharge de la fonction de handler de l'evenement closeEvent de fermeture de l'application
	
	KApplication *appli;						// Pointeur vers application KApplication parent de l'objet
	ProcessusLegerClientCommandeRobOA		*PLCommandeRobOA;					// Pointeurs sur thread canal commande RoboOA
	ProcessusLegerClientCommandeCamerOA		*PLCommandeCamerOA[NB_CAMEROA];		// Tableau pointeurs sur thread canal commande CamerOA
	ProcessusLegerClientDonneesCamerOA		*PLDonneesCamerOA[NB_CAMEROA];		// Tableau pointeurs sur thread canal donnees CamerOA
	ProcessusLegerClientCommandeTerminOA	*PLCommandeTerminOA[NB_TERMINOA];	// Tableau pointeurs sur thread canal commande TerminOA
	ProcessusLegerClientDonneesTerminOA		*PLDonneesTerminOA[NB_TERMINOA];	// Tableau pointeurs sur thread canal donnees TerminOA
	ProcessusLegerClientTemperatures		*PLTemperatures;					// Pointeur sur thread client serveur temperatures
	ProcessusLegerListeAcquisitionsC1		*PLAcqC1;							// Pointeur sur thread d'une liste d'acquisitions sur C1
	ProcessusLegerListeAcquisitionsC2		*PLAcqC2;							// Pointeur sur thread d'une liste d'acquisitions sur C2
	ProcessusLegerListeAcquisitionsL1		*PLAcqL1;							// Pointeur sur thread d'une liste d'acquisitions sur L1
	ProcessusLegerListeAcquisitionsL2		*PLAcqL2;							// Pointeur sur thread d'une liste d'acquisitions sur L2

	// Copie des commandes dans l'objet pour etre thread safe (bogues avec QString inter processus)
	QString CmdClientRobOA[NB_CMD_CLIENT_ROBOA];			// Les commandes d'un client RobOA
	QString CmdRobOAPosAxes;
	QString CmdClientTerminOA[NB_CMD_CLIENT_TERMINOA];		// Les commandes d'un client TerminOA
	QString CmdClientCamerOA[NB_CMD_CLIENT_CAMEROA];		// Les commandes d'un client CamerOA
	QString CmdCamerOATempCCD;
	QString CmdCamerOAPuiPeltier;
	QString CmdCamerOAPoseBias;

	// Variables
	//
	int MotDePasseConsignes;					// Le mot de passe d'acces au tableau des consignes est connu ou pas
	int aMotDePasseConsignes;					//  ancien

	int AxesInitialises;						// Les axes sont initialises ou pas
	int aAxesInitialises;						//  ancien etat de la variable maj a l'execution de la fonction MAJEtatBoutonsFP()
	int AxeIndexTrouve[NB_AXES];				// Drapeau lorsque l'index d'un axe est trouve
	int AxePositionReposTrouvee[NB_AXES];		// Drapeau lorsque la position de repos d'un axe est trouvee
	int AxeRechIndexEnCours;					// Numero de l'axe dont la recherche de l'index est en cours

	int PosAxeMicropasMoteur[NB_AXES];			// Position des axes en micropas moteurs dans le repere REEL MECANIQUE DE L'AXE DEFINIT PAR CONVENTION
												//  calculees lors de l'evenement ID_CUSTOM_EVENT_SUPERVCLIMSO_POSAXES
	double PosAxeDegres[NB_AXES];				// Position des axes en degres dans le repere REEL MECANIQUE DE L'AXE DEFINIT PAR CONVENTION
												//  calculees lors de l'evenement ID_CUSTOM_EVENT_SUPERVCLIMSO_POSAXES
	double aPosAxeDegres[NB_AXES];				// Ancien position des axes en degres dans le repere REEL MECANIQUE DE L'AXE DEFINIT PAR CONVENTION (pour calculer le mode courant)
												//  calculees lors de l'evenement ID_CUSTOM_EVENT_SUPERVCLIMSO_POSAXES

	int C1Actif;								// C1 doit etre actif
	int aC1Actif;								//  ancien
	int C2Actif;								// C2 doit etre actif
	int aC2Actif;								//  ancien
	int L1Actif;								// L1 doit etre actif
	int aL1Actif;								//  ancien
	int L2Actif;								// L2 doit etre actif
	int aL2Actif;								//  ancien

	ModeRoueOuvertureCLIMSO ModeObservation;	// Mode d'observation courant en fonction de la position de la roue d'ouverture
	ModeRoueOuvertureCLIMSO aModeObservation;	//  ancien mode d'observation

	FiltresC2CLIMSO FiltreC2;					// Filtre en place dans l'instrument C2
	FiltresC2CLIMSO aFiltreC2;					//  ancien filtre en place dans C2

	int PoseEnCours[NB_CAMEROA];						// Drapeau si une pose image est en cours sur l'instrument correspondant a l'indice
	int ConsignesCamerOAInitialisees[NB_CAMEROA];		// Drapeau si consignes des CamerOA sont initialisees ou pas
	int ConsignesTerminOAInitialisees[NB_TERMINOA];		// Drapeau si consignes des TerminOA sont initialisees ou pas

	QStringList ListeNomFichDerImg[NB_CAMEROA];	// Liste des noms de fichier des dernieres images acquises par l'instrument n
	QDateTime DateHeureDerImg[NB_CAMEROA];		// Date et heure de l'acquisition de la derniere image par l'instrument n

	// Objet de calcul
	//
	CalculsAstronomiques CalcAstro;				// Quelques calculs astronomiques
	double JJ(QDateTime t);						// Retourne le jour julien en fonction d'un objet QDateTime

	// Les widgets de la fenetre principale
	//
	QVBox *BoiteRangementVertical;				// Widget de rangement vertical des widgets enfants
	QHBox *BoiteRangementHorizontal1;			// Widget de rangement horizontal 1 de la BoiteRangementVertical de la fenetre principale
	QVBox *BoiteRangementVertical1a;			// Widget de rangement vertical 1a dans la boite de rangement horizontal 1
	QPushButton *BoutonConsignes;				// Bouton de demande d'acces au tableau des consignes de CLIMSO
	QPushButton *BoutonInitialisationAxes;		// Bouton de demande d'initialisation des axes de CLIMSO
	QTextEdit *Logs;							// Affichage des logs
	QHBox *BoiteRangementHorizontal2;			// Widget de rangement horizontal 2 de la BoiteRangementVertical de la fenetre principale
	QLabel *LogoCLIMSO;							// Label d'affichage du logo de CLIMSO
	SoleilHeliographique *GraphiqueSoleil;		// Widget de representation du Soleil en coordonnees heliographiques
	RoueOuvertureCLIMSO *GraphRoueOuverture;	// Widget de representation de la roue d'ouverture de CLIMSO
	RoueFiltresC2 *GraphRoueFiltresC2;			// Widget de representation graphique de la roue a filtre de l'instrument C2 de CLIMSO
	QHBox *BoiteRangementHorizontal3;			// Widget de rangement horizontal 3 de la BoiteRangementVertical de la fenetre principale
	QPushButton *BoutonModePointage;			// Bouton de demande de passage de CLIMSO en mode pointage
	QPushButton *BoutonModePLU;					// Bouton de demande de passage de CLIMSO en mode PLU
	QPushButton *BoutonModeCalibration;			// Bouton de demande de passage de CLIMSO en mode calibration
	QPushButton *BoutonModeObservation;			// Bouton de demande de passage de CLIMSO en mode observation
	QHBox *BoiteRangementHorizontal4;			// Widget de rangement horizontal 4 de la BoiteRangementVertical de la fenetre principale
	QPushButton *Bouton10747;					// Bouton de demande de passage en filtre C2 10747 nm
	QPushButton *Bouton10770;					// Bouton de demande de passage en filtre C2 10770 nm
	QPushButton *Bouton10798;					// Bouton de demande de passage en filtre C2 10798 nm
	QPushButton *Bouton10830;					// Bouton de demande de passage en filtre C2 10830 nm
	QHBox *BoiteRangementHorizontal5;			// Widget de rangement horizontal 5 de la BoiteRangementVertical de la fenetre principale
	QLabel *LabelAxe[NB_AXES];					// Widget label du nom des axes
	QLCDNumber *LCDAxeCodeur[NB_AXES];			// LCD d'affichage de la position en points quadratures codeur
	QSpinBox *SpinBoxDeltaXC2;					// Widget d'entree de la consigne de decalage en x de C2
	QSpinBox *SpinBoxDeltaYC2;					// Widget d'entree de la consigne de decalage en y de C2
	QHBox *BoiteRangementHorizontal6;			// Widget de rangement horizontal 6 de la BoiteRangementVertical de la fenetre principale
	QHBox *BoiteRangementHorizontal6a;			// Widget de rangement horizontal 6a de la BoiteRangementHorizontal6
	QHBox *BoiteRangementVertical6a;			// Widget de rangement vertical 6a de la BoiteRangementHorizontal6a
	QHBox *BoiteRangementHorizontal6aa;			// Widget de rangement horizontal 6aa de la BoiteRangementVertical6a
	QHBox *BoiteRangementHorizontal6ab;			// Widget de rangement horizontal 6ab de la BoiteRangementVertical6a
	QHBox *BoiteRangementHorizontal6ac;			// Widget de rangement horizontal 6ac de la BoiteRangementVertical6a
	QHBox *BoiteRangementHorizontal6ad;			// Widget de rangement horizontal 6ad de la BoiteRangementVertical6a
	QVBox *BRVMPCamerOAC1;						// Widget de rangement vertical dans 6aa pour l'affichage des mesures physiques de CamerOAC1
	QVBox *BRVMPCamerOAC2;						// Widget de rangement vertical dans 6ab pour l'affichage des mesures physiques de CamerOAC2
	QVBox *BRVMPCamerOAL1;						// Widget de rangement vertical dans 6ac pour l'affichage des mesures physiques de CamerOAL1
	QVBox *BRVMPCamerOAL2;						// Widget de rangement vertical dans 6ad pour l'affichage des mesures physiques de CamerOAL2
	QPushButton *BoutonPoseImageC1;				// Bouton de demande de pose image pour C1
	QPushButton *BoutonPoseImageC2;				// Bouton de demande de pose image pour C2
	QPushButton *BoutonPoseImageL1;				// Bouton de demande de pose image pour L1
	QPushButton *BoutonPoseImageL2;				// Bouton de demande de pose image pour L2
	QPushButton *BoutonPoseBiasC1;				// Bouton de demande de pose bias pour C1
	QPushButton *BoutonPoseBiasC2;				// Bouton de demande de pose bias pour C2
	QPushButton *BoutonPoseBiasL1;				// Bouton de demande de pose bias pour L1
	QPushButton *BoutonPoseBiasL2;				// Bouton de demande de pose bias pour L2
	QPushButton *BoutonPoseDarkC1;				// Bouton de demande de pose dark pour C1
	QPushButton *BoutonPoseDarkC2;				// Bouton de demande de pose dark pour C2
	QPushButton *BoutonPoseDarkL1;				// Bouton de demande de pose dark pour L1
	QPushButton *BoutonPoseDarkL2;				// Bouton de demande de pose dark pour L2
	QPushButton *BoutonEtatC1;					// Bouton etat de C1
	QPushButton *BoutonEtatC2;					// Bouton etat de C2
	QPushButton *BoutonEtatL1;					// Bouton etat de L1
	QPushButton *BoutonEtatL2;					// Bouton etat de L2
	QLCDNumber *LCDTempCamerOAC1;				// LCD d'affichage de la temperature de la CamerOA C1
	QLCDNumber *LCDPuiCamerOAC1;				// LCD d'affichage de la puissance peltier de la CamerOA C1
	QLCDNumber *LCDTempCamerOAC2;				// LCD d'affichage de la temperature de la CamerOA C2
	QLCDNumber *LCDPuiCamerOAC2;				// LCD d'affichage de la puissance peltier de la CamerOA C2
	QLCDNumber *LCDTempCamerOAL1;				// LCD d'affichage de la temperature de la CamerOA L1
	QLCDNumber *LCDPuiCamerOAL1;				// LCD d'affichage de la puissance peltier de la CamerOA L1
	QLCDNumber *LCDTempCamerOAL2;				// LCD d'affichage de la temperature de la CamerOA L2
	QLCDNumber *LCDPuiCamerOAL2;				// LCD d'affichage de la puissance peltier de la CamerOA L2
	double TemperatureCamerOA[NB_CAMEROA];		// Temperature des CCD de chaque CamerOA
	QHBox *BoiteRangementHorizontal6b;			// Widget de rangement horizontal 6b de la BoiteRangementHorizontal6
	QPushButton *BoutonPosesBias;				// Bouton de demande de poses de bias
	QPushButton *BoutonPosesDark;				// Bouton de demande de poses de dark
	QPushButton *BoutonSequencePosesImages;		// Bouton de demande de sequence de poses images
	QHBox *BoiteRangementHorizontal7;			// Widget de rangement horizontal 7 de la BoiteRangementVertical de la fenetre principale
	QLabel *LabelCBAcqAuto;						// Label de la designation des checkboxs d'acquisition automatique des instruments
	QCheckBox *CBAcqAuto[NB_CAMEROA];			// Les checkboxs d'acquisition automatique
	QLabel *LabelCompoSeqAcq;					// Label de la composition des sequences d'acquisition pour chaque instrument
	QCheckBox *CBCompoSeqAcq[NB_TYPES_ACQUISITIONS];	// Les checkboxs de la composition des sequences d'acquisition
	QHBox *BoiteRangementHorizontal8;			// Widget de rangement horizontal 8 de la BoiteRangementVertical de la fenetre principale
	QLabel *TempsDepuisDerImgC1;				// Label d'affichage du temps passe depuis la derniere image acquise par C1
	QLabel *TempsDepuisDerImgC2;				// Label d'affichage du temps passe depuis la derniere image acquise par C2
	QLabel *TempsDepuisDerImgL1;				// Label d'affichage du temps passe depuis la derniere image acquise par L1
	QLabel *TempsDepuisDerImgL2;				// Label d'affichage du temps passe depuis la derniere image acquise par L2
	QPushButton *BoutonSuppressionDerImgC1;		// Bouton de demande de suppression de la derniere image acquise par C1
	QPushButton *BoutonSuppressionDerImgC2;		// Bouton de demande de suppression de la derniere image acquise par C2
	QPushButton *BoutonSuppressionDerImgL1;		// Bouton de demande de suppression de la derniere image acquise par L1
	QPushButton *BoutonSuppressionDerImgL2;		// Bouton de demande de suppression de la derniere image acquise par L2
	QPushButton *BoutonTransfertBASS2000C1;		// Bouton de demande de transfert de la derniere image acquise par C1
	QPushButton *BoutonTransfertBASS2000C2;		// Bouton de demande de transfert de la derniere image acquise par C2
	QPushButton *BoutonTransfertBASS2000L1;		// Bouton de demande de transfert de la derniere image acquise par L1
	QPushButton *BoutonTransfertBASS2000L2;		// Bouton de demande de transfert de la derniere image acquise par L2
	QStatusBar *BarreStatus;					// Widget de barre horizontale pour presenter des informations de status
	QLabel *LabelHeureUTBarreStatus;			// Widget label ajoute a la barre de status pour l'affichage de l'heure UT
	QTimer *Pulsar1s;							// Timer de pulsation de la seconde de temps


	// Les widgets pour la fenetre de saisie des consignes
	//
	QDialog *FenetreConsignes;					// Fenetre de saisie des consignes pour CLIMSO
	QVBox *BRVFenetreConsignes;					// Boite de rangement vertical dans la fenetre de saisie des consignes
	QHBox *BRHFenetreConsignes[NB_CONSIGNES];	// Boites de rangement horizontal pour chaque ligne de consigne
	QLabel *LabelConsigne[NB_CONSIGNES];		// Label de chaque ligne de consigne
	QLineEdit *EditConsigne[NB_CONSIGNES];		// Ligne d'edition de la consigne
	QString aEditConsignes[NB_CONSIGNES];		//  ancienne consignes pour determiner rapidement si il y a eu un changement de consigne
	int ConsignesDansUniteEntiere[NB_CONSIGNES];// Valeur de la consigne dans la bonne unite (prete a etre utilise par le code)
	QMutex MutexConsignesDansUniteEntiere;		// Mutex pour l'utilisation du tableau des consignes dans l'unite entiere
	double CaissonInfoLinf;						// Consignes temperatures limites pour le caisson informatique
	double CaissonInfoLsup;
	double FiltreC1Linf;						// Consignes temperatures limites pour le filtre de C1
	double FiltreC1Lsup;
	double FiltresC2Linf;						// Consignes temperatures limites pour les filtres de C2
	double FiltresC2Lsup;
	QDoubleValidator *ValideurConsigne[NB_CONSIGNES];	// Valideur de saisie d'une consigne en fonction de bornes


	// Les widgets pour la fenetre de la fiche d'observation journaliere
	//
	DialogFenetreFicheObservation *FenetreFicheObservation;	// Fenetre de la fiche d'observation journaliere de CLIMSO


	// Les widgets pour la fenetre de visualisation des images des CamerOA
	//
	DialogFenetreCamerOA *FenetreCamerOA;					// Fenetre de visualisation des CamerOA (heritage d'un QDialog)
	QVBox *BRVFenetreCamerOA;								// Boite de rangement vertical dans la fenetre de visualisation des CamerOA
	QHBox *BRHCFenetreCamerOA;								// Boite de rangement horizontal des coronographes dans la fenetre de visualisation des CamerOA
	QHBox *BRHLFenetreCamerOA;								// Boite de rangement horizontal des lunettes dans la fenetre de visualisation des CamerOA
	ObjPoseCentrage *VisuC1;								// Objet de visualisation d'une pose de centrage pour le C1 de CLIMSO
	ObjPoseCentrage *VisuC2;								// Objet de visualisation d'une pose de centrage pour le C2 de CLIMSO
	ObjPoseCentrage *VisuL1;								// Objet de visualisation d'une pose de centrage pour la L1 de CLIMSO
	ObjPoseCentrage *VisuL2;								// Objet de visualisation d'une pose de centrage pour la L2 de CLIMSO
	void EnvoyerCommandeCamerOA(int n,int cmd);				// Envoyer une commande sans parametre a un CamerOA
	void EnvoyerCommandeIntCamerOA(int n,int cmd,int v);	// Envoyer une commande avec un parametre entier a un CamerOA


	// Les widgets pour la fenetre de visualisation des temperatures
	//
	DialogFenetreTemperatures *FenetreTemperatures;			// Fenetre de visualisation des temperatures
	QVBox *BRVFenetreTemperatures;							// Boite de rangement vertical dans la fenetre de visualisation des temperatures
	QHBox *BRHFenetreTemperatures[NB_SONDES_TEMPERATURE];	// Boite de rangement horizontal dans la fenetre de visualisation des temperatures
	QLabel *LabelTemperatures[NB_SONDES_TEMPERATURE];		// Label d'affichage de la designation des temperatures
	QLCDNumber *LCDTemperatures[NB_SONDES_TEMPERATURE];		// LCD d'affichage des temperatures
	int AlerteFenetreTemperatures[NB_SONDES_TEMPERATURE];	// Drapeau d'alerte sur une sonde de temperature

	// Les widgets et fonctions pour la fenetre de controle des TerminOA
	//
	DialogFenetreCtrlTerminOA *FenetreCtrlTerminOA;			// Fenetre de controle des TerminOA
	QVBox *BRVFenetreCtrlTerminOA;							// Boite de rangement vertical dans la fenetre de controle des TerminOA
	QHBox *BRHFenetreCtrlTerminOA[NB_TERMINOA];				// Boite de rangement horizontal dans la fenetre de controle des TerminOA
	QLabel *LabelTerminOA[NB_TERMINOA];						// Label d'affichage de la designation des TerminOA controles
	QPushButton *BoutonModeIC[NB_TERMINOA];					// Bouton pour passer en mode affichage image courante
	QPushButton *BoutonModeDiapo[NB_TERMINOA];				// Bouton pour passer en mode diaporama
	QPushButton *BoutonEchLin[NB_TERMINOA];					// Bouton pour passer en echelle de representation histogramme lineaire
	QPushButton *BoutonEchLog[NB_TERMINOA];					// Bouton pour passer en echelle de representation histogramme logarithmique
	QPushButton *BoutonPalNB[NB_TERMINOA];					// Bouton pour passer en palette noir et blanc
	QPushButton *BoutonPalHalpha[NB_TERMINOA];				// Bouton pour passer en palette h-alpha
	QPushButton *BoutonPalNoirOrangeBlanc[NB_TERMINOA];		// Bouton pour passer en palette noir-orange-blanc
	QPushButton *BoutonPalNoirVertBlanc[NB_TERMINOA];		// Bouton pour passer en palette noir-vert-blanc
	QPushButton *BoutonPalNoirBleuBlanc[NB_TERMINOA];		// Bouton pour passer en palette noir-bleu-blanc
	QPushButton *BoutonZ0[NB_TERMINOA];						// Bouton pour passer en zone de visualisation z0
	QPushButton *BoutonZ1[NB_TERMINOA];						// Bouton pour passer en zone de visualisation z1
	QPushButton *BoutonZ2[NB_TERMINOA];						// Bouton pour passer en zone de visualisation z2
	QPushButton *BoutonZ3[NB_TERMINOA];						// Bouton pour passer en zone de visualisation z3
	QPushButton *BoutonZ4[NB_TERMINOA];						// Bouton pour passer en zone de visualisation z4
	QPushButton *BoutonZ5[NB_TERMINOA];						// Bouton pour passer en zone de visualisation z5
	QPushButton *BoutonZ6[NB_TERMINOA];						// Bouton pour passer en zone de visualisation z6
	QPushButton *BoutonZ7[NB_TERMINOA];						// Bouton pour passer en zone de visualisation z7
	QPushButton *BoutonZ8[NB_TERMINOA];						// Bouton pour passer en zone de visualisation z8
	QPushButton *BoutonZ9[NB_TERMINOA];						// Bouton pour passer en zone de visualisation z9
	QSpinBox *SpinBoxCSB[NB_TERMINOA];						// SpinBox d'entree de la consigne du seuil bas de visualisation
	QSpinBox *SpinBoxCSH[NB_TERMINOA];						// SpinBox d'entree de la consigne du seuil haut de visualisation
	QSpinBox *SpinBoxCPuiLUT[NB_TERMINOA];					// SpinBox d'entree de la consigne de la puissance de la LUT de visualisation
	void EnvoyerCommandeIntTerminOA(int id,int cmd,int valeur);	// Envoyer une commande avec un parametre entier a un TerminOA

	// Les widgets et fonctions pour la fenetre de la publication BASS2000 des dernieres images de C1
	//
	QDialog *FenetrePubliC1;								// Fenetre de publication BASS2000 des dernieres images de C1
	QVBox *BRVFenetrePubliC1;								// Boite de rangement vertical dans la fenetre de publication des dernieres images de C1
	QHBox *BRHFenetrePubliC1[NB_IMG_PUB_C1];				// Boite de rangement horizontal dans la fenetre de publication des dernieres images de C1
	QLabel *LabelFenetrePubliC1[NB_IMG_PUB_C1];				// Label du nom du fichier a publier
	QPushButton *BoutonFenetrePubliC1[NB_IMG_PUB_C1];		// Bouton de declenchement de la publication sur BASS2000
	QString FichiersPubliC1[NB_IMG_PUB_C1];					// Chemin et nom des fichiers publiables
	int NbImgPubliablesC1;									// Le nombre d'images publiables de C1 (un compteur qui s'incremente)
	void ComposerListePubliablesC1(void);					// Composition de la liste des images de C1 publiables

	// Les widgets et fonctions pour la fenetre de la publication BASS2000 des dernieres images de C2
	//
	QDialog *FenetrePubliC2;								// Fenetre de publication BASS2000 des dernieres images de C2
	QVBox *BRVFenetrePubliC2;								// Boite de rangement vertical dans la fenetre de publication des dernieres images de C2
	QHBox *BRHFenetrePubliC2[NB_IMG_PUB_C2];				// Boite de rangement horizontal dans la fenetre de publication des dernieres images de C2
	QLabel *LabelFenetrePubliC2[NB_IMG_PUB_C2];				// Label du nom du fichier a publier
	QPushButton *BoutonFenetrePubliC2[NB_IMG_PUB_C2];		// Bouton de declenchement de la publication sur BASS2000
	QString FichiersPubliC2[NB_IMG_PUB_C2];					// Chemin et nom des fichiers publiables
	int NbImgPubliablesC2;									// Le nombre d'images publiables de C2 (un compteur qui s'incremente)
	void ComposerListePubliablesC2(void);					// Composition de la liste des images de C2 publiables

	// Les widgets et fonctions pour la fenetre de la publication BASS2000 des dernieres images de L1
	//
	QDialog *FenetrePubliL1;								// Fenetre de publication BASS2000 des dernieres images de L1
	QVBox *BRVFenetrePubliL1;								// Boite de rangement vertical dans la fenetre de publication des dernieres images de L1
	QHBox *BRHFenetrePubliL1[NB_IMG_PUB_L1];				// Boite de rangement horizontal dans la fenetre de publication des dernieres images de L1
	QLabel *LabelFenetrePubliL1[NB_IMG_PUB_L1];				// Label du nom du fichier a publier
	QPushButton *BoutonFenetrePubliL1[NB_IMG_PUB_L1];		// Bouton de declenchement de la publication sur BASS2000
	QString FichiersPubliL1[NB_IMG_PUB_L1];					// Chemin et nom des fichiers publiables
	int NbImgPubliablesL1;									// Le nombre d'images publiables de L1 (un compteur qui s'incremente)
	void ComposerListePubliablesL1(void);					// Composition de la liste des images de L1 publiables

	// Les widgets et fonctions pour la fenetre de la publication BASS2000 des dernieres images de L2
	//
	QDialog *FenetrePubliL2;								// Fenetre de publication BASS2000 des dernieres images de L2
	QVBox *BRVFenetrePubliL2;								// Boite de rangement vertical dans la fenetre de publication des dernieres images de L2
	QHBox *BRHFenetrePubliL2[NB_IMG_PUB_L2];				// Boite de rangement horizontal dans la fenetre de publication des dernieres images de L2
	QLabel *LabelFenetrePubliL2[NB_IMG_PUB_L2];				// Label du nom du fichier a publier
	QPushButton *BoutonFenetrePubliL2[NB_IMG_PUB_L2];		// Bouton de declenchement de la publication sur BASS2000
	QString FichiersPubliL2[NB_IMG_PUB_L2];					// Chemin et nom des fichiers publiables
	int NbImgPubliablesL2;									// Le nombre d'images publiables de L2 (un compteur qui s'incremente)
	void ComposerListePubliablesL2(void);					// Composition de la liste des images de L2 publiables

	void PublierBASS2000(int n,QString image);				// Publication d'une image sur BASS2000

	//
	// Les fonctions utilisables
	//
	QString CheminRepertoireSuperviseur(void);				// Retourne le chemin vers le repertoire de base du superviseur
	void DeclencherPoseBias(int log,int i);					// Declenchement d'une pose de type Bias pour l'instrument i
	QString GenererChaineAleatoire(int n);					// Generation d'une chaine de caracteres aleatoires
	void Log(QString log);									// Ajouter et afficher un commentaire dans la fenetre des logs
	void MAJEtatBoutonsFP(void);							// Mettre a jour les etats des boutons de la fenetre principale en fonction du contexte
	void MessageDevezInitialiserAxes(void);					// Dialogue "Vous devez d'abord initialiser les axes"
	void MessageDevezValider(int i);						// Dialogue "Vous devez d'abord valider l'instrument i"
	void MessageDevezValiderUnInstrument(void);				// Dialogue "Vous devez d'abord valider un instrument"
	void MessageUnePoseDejaEnCoursSur(int i);				// Dialogue "Une pose est deja en cours sur l'instrument i"
	void MessageUnePoseEnCoursModifModeImpossible(void);	// Dialogue "Une pose est en cours, on ne peut pas changer le mode d'observation de CLIMSO"
	void MessageUnePoseEnCoursC2ModifFiltreImpossible(void);// Dialogue "Une pose est en cours sur C2, on ne peut pas changer le filtre
	void MessageModeRoueOuvNonConnuePoseImpossible(void);	// Dialogue "Le mode d'observation de la roue d'ouverture n'est pas connu, vous ne pouvez pas declencher une pose"
	void MessageFiltreC2NonConnuPoseImpossible(void);		// Dialogue "Le filtre actif de la roue a filtre de C2 n'est pas connu, vous ne pouvez pas declencher une pose"
	void DemandeRotationRoueOuverture(ModeRoueOuvertureCLIMSO position);	// Demande de rotation de la roue d'ouverture jusqu'a la position d'un mode particulier
	void DemandeRotationRoueFiltresC2(FiltresC2CLIMSO filtre);				// Demande de rotation de la roue a filtre de C2 jusqu'a la position d'un filtre
	void DemandeMouvementXPlatine(int valeur);								// Demande de mouvement de l'axe X de la platine de C2
	void DemandeMouvementYPlatine(int valeur);								// Demande de mouvement de l'axe Y de la platine de C2
	FiltresC2CLIMSO FiltreC2Courant(void);					// Retourne le filtre courant sur C2
	int SauverImageFITS(int n,QString &ncf);				// Sauver une image au format FITS
};


//
// Evenements associes a la modification de widgets de la fenetre principale par d'autres processus legers -----------------------------
//

class CEventSupervCLIMSO_NouvImage : public QCustomEvent	// Notification de reception d'une nouvelle image
{
	private:
		int id;

	public:
		CEventSupervCLIMSO_NouvImage(int pid) : QCustomEvent(ID_CUSTOM_EVENT_SUPERVCLIMSO_NOUVIMG)
		{
			id=pid;
		}

		int Identifieur(void)	{	return id;	}
};

class CEventSupervCLIMSO_NouvImageCentrage : public QCustomEvent	// Notification de reception d'une nouvelle image de centrage
{
	private:
		int id;

	public:
		CEventSupervCLIMSO_NouvImageCentrage(int pid) : QCustomEvent(ID_CUSTOM_EVENT_SUPERVCLIMSO_NOUVIMGCENTRAGE)
		{
			id=pid;
		}

		int Identifieur(void)	{	return id;	}
};

class CEventSupervCLIMSO_NouvImageCentrageH : public QCustomEvent	// Notification de reception d'une nouvelle image de centrage horizontal
{
	private:
		int id;

	public:
		CEventSupervCLIMSO_NouvImageCentrageH(int pid) : QCustomEvent(ID_CUSTOM_EVENT_SUPERVCLIMSO_NOUVIMGCENTRAGEH)
		{
			id=pid;
		}

		int Identifieur(void)	{	return id;	}
};

class CEventSupervCLIMSO_NouvImageCentrageV : public QCustomEvent	// Notification de reception d'une nouvelle image de centrage vertical
{
	private:
		int id;

	public:
		CEventSupervCLIMSO_NouvImageCentrageV(int pid) : QCustomEvent(ID_CUSTOM_EVENT_SUPERVCLIMSO_NOUVIMGCENTRAGEV)
		{
			id=pid;
		}

		int Identifieur(void)	{	return id;	}
};

class CEventSupervCLIMSO_FinListeAcquisitions : public QCustomEvent	// Notification de la fin d'une liste d'acquisition
{
	private:
		int id;

	public:
		CEventSupervCLIMSO_FinListeAcquisitions(int pid) : QCustomEvent(ID_CUSTOM_EVENT_SUPERVCLIMSO_FINLISTEACQ)
		{
			id=pid;
		}

		int Identifieur(void)	{	return id;	}
};

class CEventSupervCLIMSO_RotationVFiltreC2 : public QCustomEvent	// Notification de rotation de la roue a filtre de C2 vers le filtre en argument
{
	private:
		FiltresC2CLIMSO filtre;

	public:
		CEventSupervCLIMSO_RotationVFiltreC2(FiltresC2CLIMSO pf) : QCustomEvent(ID_CUSTOM_EVENT_SUPERVCLIMSO_ROTVFILTREC2)
		{
			filtre=pf;
		}

		FiltresC2CLIMSO Filtre(void)	{	return filtre;	}
};

class CEventSupervCLIMSO_Log : public QCustomEvent					// Affichage d'un log
{
	private:
		QString chaine;

	public:
		CEventSupervCLIMSO_Log(QString pchaine) : QCustomEvent(ID_CUSTOM_EVENT_SUPERVCLIMSO_LOG)
		{
			chaine=pchaine;
		}

		QString Chaine(void)	{	return chaine;	}
};

class CEventSupervCLIMSO_TempCCD : public QCustomEvent				// Retour de la temperature de la CCD d'un CamerOA
{
	private:
		int id;
		QDateTime temps;
		double temperature;

	public:
		CEventSupervCLIMSO_TempCCD(int pid,QDateTime ptemps,double ptemperature) : QCustomEvent(ID_CUSTOM_EVENT_SUPERVCLIMSO_TEMPCCD)
		{
			id=pid;
			temps=ptemps;
			temperature=ptemperature;
		}

		int Identifieur(void)		{	return id;			}
		QDateTime Temps(void)		{	return temps; 		}
		double Temperature(void)	{	return temperature;	}
};

class CEventSupervCLIMSO_PuiPeltier : public QCustomEvent				// Retour de la puissance peltier d'un CamerOA
{
	private:
		int id;
		QDateTime temps;
		double puissance;

	public:
		CEventSupervCLIMSO_PuiPeltier(int pid,QDateTime ptemps,double ppuissance) : QCustomEvent(ID_CUSTOM_EVENT_SUPERVCLIMSO_PUIPELTIER)
		{
			id=pid;
			temps=ptemps;
			puissance=ppuissance;
		}

		int Identifieur(void)		{	return id;			}
		QDateTime Temps(void)		{	return temps; 		}
		double Puissance(void)		{	return puissance;	}
};

class CEventSupervCLIMSO_ImgRecueTerminOA : public QCustomEvent			// Une image a ete recue par un TerminOA
{
	private:
		int id;
		QString idImage;

	public:
		CEventSupervCLIMSO_ImgRecueTerminOA(int pid,QString pidimg) : QCustomEvent(ID_CUSTOM_EVENT_SUPERVCLIMSO_IMGRECUETERMINOA)
		{
			id=pid;
			idImage=pidimg;
		}

		int Identifieur(void)		{	return id;			}
		QString IdImage(void)		{	return idImage;		}
};

class CEventSupervCLIMSO_NouvTemperatures : public QCustomEvent			// Pour signaler que les temperatures ont ete lues sur le Web-IO-Thermometer
{
	public:
		CEventSupervCLIMSO_NouvTemperatures(void) : QCustomEvent(ID_CUSTOM_EVENT_SUPERVCLIMSO_NOUVTEMPERATURES) {}
};

class CEventSupervCLIMSO_IndexAxeTrouve : public QCustomEvent			// Pour signaler que l'index de l'axe n a ete trouve
{
	private:
		int n;

	public:
		CEventSupervCLIMSO_IndexAxeTrouve(int pn) : QCustomEvent(ID_CUSTOM_EVENT_SUPERVCLIMSO_INDEXAXETROUVE)
		{
			n=pn;
		}

		int Numero(void)	{	return n;	}
};

class CEventSupervCLIMSO_IndexAxeNonTrouve : public QCustomEvent		// Pour signaler que l'index de l'axe n N'A PAS ETE trouve
{
	private:
		int n;

	public:
		CEventSupervCLIMSO_IndexAxeNonTrouve(int pn) : QCustomEvent(ID_CUSTOM_EVENT_SUPERVCLIMSO_INDEXAXENONTROUVE)
		{
			n=pn;
		}

		int Numero(void)	{	return n;	}
};

class CEventSupervCLIMSO_PosAxes : public QCustomEvent					// Pour signaler le rafraichissement de la position des axes codeurs
{
	private:
		int pos[NB_AXES];

	public:
		CEventSupervCLIMSO_PosAxes(int pv1,int pv2,int pv3,int pv4) : QCustomEvent(ID_CUSTOM_EVENT_SUPERVCLIMSO_POSAXES)
		{
			pos[0]=pv1; pos[1]=pv2; pos[2]=pv3; pos[3]=pv4;
		}

		int Valeur(int n)	{	return pos[n];	}
};

#endif // _SUPERVCLIMSO_H_
