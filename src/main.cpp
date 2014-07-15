//
// MODULE PRINCIPAL DE L'APPLICATION KDE : SupervCLIMSO
//
// LOGICIEL DE SUPERVISION DE L'INSTRUMENT CLIMSO
//
// (C)David.Romeuf@univ-lyon1.fr 26/10/2006 par David Romeuf
//

// Inclusions C++
//
#include <iostream>
#include <new>

// Inclusions Qt et KDE
//
#include <qdir.h>
#include <qsemaphore.h>
#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>

// Inclusions de l'applications
//
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "supervclimso.h"

// Declarations
//

static const char description[] = I18N_NOOP("A KDE KPart Application");
static const char version[] = "1.0";

// Liste des options supportees par la ligne de commande
//
enum ArgumentsApplication {
	CheminRepSuperviseur,
	CheminFichCertCA_OA,
	CheminFichCertClientSupervCLIMSO,
	CheminFichClePriveeClientSupervCLIMSO,
	MdpClePriveeClient
};

const char *OptionsLC[] = {
	"chemsuperviseur",
	"chemficaoa",
	"chemficertclient",
	"chemficleprivclient",
	"mdpcleprivclient"
};

static KCmdLineOptions options[] =
{
	{"chemsuperviseur ",I18N_NOOP("Chemin vers le repertoire du superviseur"),"/SupervCLIMSO"},
	{"chemficaoa ",I18N_NOOP("Chemin et nom du certificat (PEM) du CA des OA"),"/SupervCLIMSO/ssl/CertificatCA_OA.pem"},
	{"chemficertclient ",I18N_NOOP("Chemin et nom du certificat (PEM) du client"),"/SupervCLIMSO/ssl/CertificatClientSupervCLIMSO.pem"},
	{"chemficleprivclient ",I18N_NOOP("Chemin et nom du fichier PEM contenant la cle privee du client SupervCLIMSO"),"/SupervCLIMSO/ssl/ClePriveeClientSupervCLIMSO.pem"},
	{"mdpcleprivclient ",I18N_NOOP("Mot de passe d'acces a la cle privee du client"),"???"},
//	{" ", I18N_NOOP(""),""},
	KCmdLineLastOption
};


// - Pour les processus legers ---------------------------------------------------------------------------------------------------------

// Temps d'attente de la terminaison d'un processus leger
//
#define TEMPS_ATTENTE_TERMINAISON_PROCESSUS_LEGER	5000

#define TIMEOUT_EMISSION	5		// Timeout des liaisons pour les canaux de commandes et de donnees
#define TIMEOUT_RECEPTION	120

char MotDePasseClePriveeClientSUPERVCLIMSO[NB_CAMEROA+NB_TERMINOA+NB_ROBOA][TAILLE_MAX_MDP_CLE_PRIVEE];	// Mot de passe pour acces a la cle privee du client

// FONCTION APPELEE PAR LA LIBRAIRIE SSL POUR LIRE OU STOCKER LES FICHIERS PEM CONTENANT UNE CLE CHIFFREE
//
// CE:	La librairie SSL passe un pointeur vers le tableau ou doit etre copie le mot de passe ;
//
// 		La librairie SSL passe la dimension maximale du mot de passe ;
//
// 		La librairie SSL passe 0 si la fonction est utilisee pour lire/decryptee, ou, 1 si la fonction est appelee pour ecrire/encryptee
//
// 		La librairie SSL passe un pointeur vers une donnee passee par la routine PEM. Il permet qu'une donnee arbitraire soit passee
// 	 	a cette fonction par une application (comme par exemple un identifieur de fenetre dans une application graphique).
//
// CS:	La fonction doit retourner la longueur du mot de passe.
//
int FnMotDePasseClePriveeChiffreeSUPERVCLIMSO_0(char *buf,int size,int rwflag,void *data)
{
	rwflag=rwflag;	// pour eviter un warning lors de la compilation
	data=data;
	
	if( size < (int) (strlen(MotDePasseClePriveeClientSUPERVCLIMSO[0])+1) ) return 0;

	strcpy(buf,MotDePasseClePriveeClientSUPERVCLIMSO[0]);

	return( strlen(buf) );
}

int FnMotDePasseClePriveeChiffreeSUPERVCLIMSO_1(char *buf,int size,int rwflag,void *data)
{
	rwflag=rwflag;	// pour eviter un warning lors de la compilation
	data=data;
	
	if( size < (int) (strlen(MotDePasseClePriveeClientSUPERVCLIMSO[1])+1) ) return 0;

	strcpy(buf,MotDePasseClePriveeClientSUPERVCLIMSO[1]);

	return( strlen(buf) );
}

int FnMotDePasseClePriveeChiffreeSUPERVCLIMSO_2(char *buf,int size,int rwflag,void *data)
{
	rwflag=rwflag;	// pour eviter un warning lors de la compilation
	data=data;
	
	if( size < (int) (strlen(MotDePasseClePriveeClientSUPERVCLIMSO[2])+1) ) return 0;

	strcpy(buf,MotDePasseClePriveeClientSUPERVCLIMSO[2]);

	return( strlen(buf) );
}

int FnMotDePasseClePriveeChiffreeSUPERVCLIMSO_3(char *buf,int size,int rwflag,void *data)
{
	rwflag=rwflag;	// pour eviter un warning lors de la compilation
	data=data;
	
	if( size < (int) (strlen(MotDePasseClePriveeClientSUPERVCLIMSO[3])+1) ) return 0;

	strcpy(buf,MotDePasseClePriveeClientSUPERVCLIMSO[3]);

	return( strlen(buf) );
}

int FnMotDePasseClePriveeChiffreeSUPERVCLIMSO_4(char *buf,int size,int rwflag,void *data)
{
	rwflag=rwflag;	// pour eviter un warning lors de la compilation
	data=data;
	
	if( size < (int) (strlen(MotDePasseClePriveeClientSUPERVCLIMSO[4])+1) ) return 0;

	strcpy(buf,MotDePasseClePriveeClientSUPERVCLIMSO[4]);

	return( strlen(buf) );
}

int FnMotDePasseClePriveeChiffreeSUPERVCLIMSO_5(char *buf,int size,int rwflag,void *data)
{
	rwflag=rwflag;	// pour eviter un warning lors de la compilation
	data=data;
	
	if( size < (int) (strlen(MotDePasseClePriveeClientSUPERVCLIMSO[5])+1) ) return 0;

	strcpy(buf,MotDePasseClePriveeClientSUPERVCLIMSO[5]);

	return( strlen(buf) );
}

int FnMotDePasseClePriveeChiffreeSUPERVCLIMSO_6(char *buf,int size,int rwflag,void *data)
{
	rwflag=rwflag;	// pour eviter un warning lors de la compilation
	data=data;
	
	if( size < (int) (strlen(MotDePasseClePriveeClientSUPERVCLIMSO[6])+1) ) return 0;

	strcpy(buf,MotDePasseClePriveeClientSUPERVCLIMSO[6]);

	return( strlen(buf) );
}

int FnMotDePasseClePriveeChiffreeSUPERVCLIMSO_7(char *buf,int size,int rwflag,void *data)
{
	rwflag=rwflag;	// pour eviter un warning lors de la compilation
	data=data;
	
	if( size < (int) (strlen(MotDePasseClePriveeClientSUPERVCLIMSO[7])+1) ) return 0;

	strcpy(buf,MotDePasseClePriveeClientSUPERVCLIMSO[7]);

	return( strlen(buf) );
}

int FnMotDePasseClePriveeChiffreeSUPERVCLIMSO_8(char *buf,int size,int rwflag,void *data)
{
	rwflag=rwflag;	// pour eviter un warning lors de la compilation
	data=data;
	
	if( size < (int) (strlen(MotDePasseClePriveeClientSUPERVCLIMSO[8])+1) ) return 0;

	strcpy(buf,MotDePasseClePriveeClientSUPERVCLIMSO[8]);

	return( strlen(buf) );
}

// FONCTION DE HANDLER DU SIGNAL SIGPIPE
//
// CE:	Le systeme passe le signal ;
//
// CS:	-
//
void FnHandlerSIGPIPESupervCLIMSO(int signal)
{
	std::cerr << "PointCommClientChiffreMonoClient: Signal " << signal << "->SIGPIPE<- recu par le processus." << std::endl;
}

// Semaphore de synchronisation des processus legers de SupervCLIMSO
//
QSemaphore SemaphoreSyncLancementThreadSupervCLIMSO(22);


// - Fin Pour les processus legers -----------------------------------------------------------------------------------------------------


// Fonction principale de l'application
//
int main(int argc, char **argv)
{
	int i;																	// Indice
	int lancement=true;														// Drapeau pour savoir si on doit lancer l'application

	// Renseignements KDE
	//
	KAboutData about("supervclimso", I18N_NOOP("SupervCLIMSO"), version, description,KAboutData::License_GPL, "(C) 2006 David Romeuf", 0, 0, "David.Romeuf@univ-lyon1.fr");
	about.addAuthor( "David Romeuf", 0, "David.Romeuf@univ-lyon1.fr" );
	
	
	// Initialisation des options de la ligne de commande (avec les Qt et KDE specifiques)
	//
	KCmdLineArgs::init(argc, argv, &about);
	
	// Ajout des options possibles sur la ligne de commande supportees par l'application
	//
	KCmdLineArgs::addCmdLineOptions(options);
	
	// Acces aux arguments reconnus par l'application
	//
	KCmdLineArgs *arguments=KCmdLineArgs::parsedArgs();
	
	// On test la validite des arguments
	//
	if( !QDir(arguments->getOption(OptionsLC[CheminRepSuperviseur])).exists() )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Le repertoire " << arguments->getOption(OptionsLC[CheminRepSuperviseur]) << " n'existe pas." << std::endl;
		lancement=false;
	}
	
	if( !QFile(arguments->getOption(OptionsLC[CheminFichCertCA_OA])).exists() )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Le fichier " << arguments->getOption(OptionsLC[CheminFichCertCA_OA]) << " n'existe pas." << std::endl;
		lancement=false;
	}
	
	if( !QFile(arguments->getOption(OptionsLC[CheminFichClePriveeClientSupervCLIMSO])).exists() )
	{
		std::cerr << "SupervCLIMSO: ERREUR: Le fichier " << arguments->getOption(OptionsLC[CheminFichClePriveeClientSupervCLIMSO]) << " n'existe pas." << std::endl;
		lancement=false;
	}
	
	if( lancement )
	{
		QRect GeometrieFenetre;														// Rectangle geometrie d'une fenetre
		ProcessusLegerClientCommandeRobOA		*PLCommandeRobOA;					// Pointeur sur thread canal commande RobOA
		ProcessusLegerClientCommandeCamerOA		*PLCommandeCamerOA[NB_CAMEROA];		// Tableau pointeurs sur thread canal commande CamerOA
		ProcessusLegerClientDonneesCamerOA		*PLDonneesCamerOA[NB_CAMEROA];		// Tableau pointeurs sur thread canal donnees CamerOA
		ProcessusLegerClientCommandeTerminOA	*PLCommandeTerminOA[NB_TERMINOA];	// Tableau pointeurs sur thread canal commande TerminOA
		ProcessusLegerClientDonneesTerminOA		*PLDonneesTerminOA[NB_TERMINOA];	// Tableau pointeurs sur thread canal donnees TerminOA
		ProcessusLegerClientTemperatures		*PLTemperatures;					// Pointeur sur thread client du serveur des temperatures
		ProcessusLegerListeAcquisitionsC1		*PLAcqC1;							// Pointeur sur thread de la liste des acquisitions sur C1
		ProcessusLegerListeAcquisitionsC2		*PLAcqC2;							// Pointeur sur thread de la liste des acquisitions sur C2
		ProcessusLegerListeAcquisitionsL1		*PLAcqL1;							// Pointeur sur thread de la liste des acquisitions sur L1
		ProcessusLegerListeAcquisitionsL2		*PLAcqL2;							// Pointeur sur thread de la liste des acquisitions sur L2

		// Creation d'un objet application KDE
		//
		KApplication appli;
		
		// Pointeur sur un objet de fenetre principale KDE
		//
		SupervCLIMSO *FenetrePrincipale=0;		// Pointeur sur objet fenetre principale de notre application

		// Si l'application est restauree par le gestionnaire de session
		//
		if( appli.isRestored() )
		{
			// On restaure l'application a l'aide de l'objet de configuration de la session sauve lors de la fermeture de session
			//
			RESTORE(SupervCLIMSO(arguments->getOption(OptionsLC[CheminRepSuperviseur]),&appli));
		}
		else
		{
			// Pas de restauration de session donc on demarre l'application normalement
			//

			// Creation de l'objet fenetre principale de l'application
			//
			if( (FenetrePrincipale=new (std::nothrow) SupervCLIMSO(arguments->getOption(OptionsLC[CheminRepSuperviseur]),&appli)) == NULL )
			{
    				std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer la fenetre principale KMainWindow de l'application." << std::endl;
					appli.exit(-1);
			}
				
			// On fixe la fenetre principale pour l'objet application KDE
			//
			appli.setMainWidget(FenetrePrincipale);

			// On affiche la fenetre principale
			//
			FenetrePrincipale->show();

			// On fixe les dimensions apres l'affichage pour que les dimensions des QVBox et QHBox soient calculees
			//
			QSize DimensionBoiteRangementHorizontal1=FenetrePrincipale->BoiteRangementHorizontal1->size();
			QSize DimensionBoiteRangementHorizontal2=FenetrePrincipale->BoiteRangementHorizontal2->size();
			QSize DimensionBoiteRangementHorizontal3=FenetrePrincipale->BoiteRangementHorizontal3->size();
			QSize DimensionBoiteRangementHorizontal4=FenetrePrincipale->BoiteRangementHorizontal4->size();
			QSize DimensionBoiteRangementHorizontal5=FenetrePrincipale->BoiteRangementHorizontal5->size();
			QSize DimensionBoiteRangementHorizontal6=FenetrePrincipale->BoiteRangementHorizontal6->size();
			QSize DimensionBoiteRangementHorizontal7=FenetrePrincipale->BoiteRangementHorizontal7->size();
			QSize DimensionBoiteRangementHorizontal8=FenetrePrincipale->BoiteRangementHorizontal8->size();
			QSize DimensionBarreStatus=FenetrePrincipale->BarreStatus->size();
			QSize DimensionBoutonModePointage=FenetrePrincipale->BoutonModePointage->size();
			QSize DimensionBoutonEtatC1=FenetrePrincipale->BoutonEtatC1->size();

			FenetrePrincipale->BRVMPCamerOAC1->setFixedHeight(DimensionBoutonEtatC1.height());
			FenetrePrincipale->BRVMPCamerOAC2->setFixedHeight(DimensionBoutonEtatC1.height());
			FenetrePrincipale->BRVMPCamerOAL1->setFixedHeight(DimensionBoutonEtatC1.height());
			FenetrePrincipale->BRVMPCamerOAL2->setFixedHeight(DimensionBoutonEtatC1.height());

			FenetrePrincipale->BoutonPosesBias->setFixedHeight(DimensionBoiteRangementHorizontal6.height());
			FenetrePrincipale->BoutonPosesDark->setFixedHeight(DimensionBoiteRangementHorizontal6.height());
			FenetrePrincipale->BoutonSequencePosesImages->setFixedHeight(DimensionBoiteRangementHorizontal6.height());

			FenetrePrincipale->Logs->setFixedWidth(FenetrePrincipale->BoutonInitialisationAxes->width()*3);
			FenetrePrincipale->Logs->setFixedHeight(FenetrePrincipale->BoutonInitialisationAxes->height()*2);

			//std::cout << DimensionBoutonModePointage.width() << std::endl;
			FenetrePrincipale->LogoCLIMSO->setFixedWidth(DimensionBoutonModePointage.width());
			FenetrePrincipale->LogoCLIMSO->setFixedHeight(DimensionBoutonModePointage.width());
			FenetrePrincipale->GraphiqueSoleil->setFixedWidth(DimensionBoutonModePointage.width());
			FenetrePrincipale->GraphiqueSoleil->setFixedHeight(DimensionBoutonModePointage.width());
			FenetrePrincipale->GraphRoueOuverture->setFixedWidth(DimensionBoutonModePointage.width());
			FenetrePrincipale->GraphRoueOuverture->setFixedHeight(DimensionBoutonModePointage.width());
			FenetrePrincipale->GraphRoueFiltresC2->setFixedWidth(DimensionBoutonModePointage.width());
			FenetrePrincipale->GraphRoueFiltresC2->setFixedHeight(DimensionBoutonModePointage.width());

			QSize TailleFenetrePrincipale;
			TailleFenetrePrincipale.setWidth(FenetrePrincipale->BoutonModeObservation->width()*4);
			TailleFenetrePrincipale.setHeight(DimensionBoiteRangementHorizontal1.height()+DimensionBoiteRangementHorizontal2.height()+DimensionBoiteRangementHorizontal3.height()+DimensionBoiteRangementHorizontal4.height()+DimensionBoiteRangementHorizontal5.height()+DimensionBoiteRangementHorizontal6.height()+DimensionBoiteRangementHorizontal7.height()+DimensionBoiteRangementHorizontal8.height()+DimensionBarreStatus.height());
			FenetrePrincipale->setMinimumSize(TailleFenetrePrincipale);
			FenetrePrincipale->setMaximumSize(TailleFenetrePrincipale);
		}

		//
		// Creation de tous les processus legers du superviseur de CLIMSO
		//

		// Le processus leger client du serveur des temperatures
		//
		if( (PLTemperatures=new (std::nothrow) ProcessusLegerClientTemperatures(FenetrePrincipale,0xC0A8061E,80,TIMEOUT_EMISSION,TIMEOUT_RECEPTION)) == NULL )
		{
				std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le processus leger PLTemperatures." << std::endl;
				delete FenetrePrincipale;
				appli.exit(-1);
		}
		FenetrePrincipale->PLTemperatures=PLTemperatures;


		// Le processus leger client de gestion des commandes entre le superviseur et RobOA
		//
		if( (PLCommandeRobOA=new (std::nothrow) ProcessusLegerClientCommandeRobOA(FenetrePrincipale,0xC0A8060A,22443,TIMEOUT_EMISSION,TIMEOUT_RECEPTION,true,FnHandlerSIGPIPESupervCLIMSO,arguments->getOption(OptionsLC[MdpClePriveeClient]),MotDePasseClePriveeClientSUPERVCLIMSO[8],FnMotDePasseClePriveeChiffreeSUPERVCLIMSO_8,arguments->getOption(OptionsLC[CheminFichCertCA_OA]),arguments->getOption(OptionsLC[CheminFichCertClientSupervCLIMSO]),arguments->getOption(OptionsLC[CheminFichClePriveeClientSupervCLIMSO]))) == NULL )
		{
   				std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le processus leger PLCommandeRobOA." << std::endl;
				delete FenetrePrincipale;
				appli.exit(-1);
		}
		FenetrePrincipale->PLCommandeRobOA=PLCommandeRobOA;


		// On instancie les processus legers de gestion des liaisons entre le superviseur et les CamerOA
		//
		for( i=0; i < NB_CAMEROA; i++ )
		{
			uint32_t adresse;													// Adresse du client pour cet indice
			uint16_t portc;														// Port du service des commandes sur le client
			uint16_t portd;														// Port du service des donnees sur le client
			char *pt_BuffStockMdpClePriveeClient;								// Stockage mot de passe cle privee pour indice
			int (*pt_FnMotDePasseClePriveeChiffree)(char*, int, int, void*);	// Fn passage mot de passe cle privee pour indice


			// Selon l'indice et donc le CamerOA
			//
			switch( i )
			{
				case CAMEROA_C1:
					adresse=0xC0A80614;		// 192.168.6.20
					pt_BuffStockMdpClePriveeClient=MotDePasseClePriveeClientSUPERVCLIMSO[0];
					pt_FnMotDePasseClePriveeChiffree=FnMotDePasseClePriveeChiffreeSUPERVCLIMSO_0;
					portc=33443;
					portd=33444;
					break;

				case CAMEROA_C2:
					adresse=0xC0A80615;		// 192.168.6.21
					pt_BuffStockMdpClePriveeClient=MotDePasseClePriveeClientSUPERVCLIMSO[1];
					pt_FnMotDePasseClePriveeChiffree=FnMotDePasseClePriveeChiffreeSUPERVCLIMSO_1;
					portc=33443;
					portd=33444;
					break;

				case CAMEROA_L1:
					adresse=0xC0A80616;		// 192.168.6.22
					pt_BuffStockMdpClePriveeClient=MotDePasseClePriveeClientSUPERVCLIMSO[2];
					pt_FnMotDePasseClePriveeChiffree=FnMotDePasseClePriveeChiffreeSUPERVCLIMSO_2;
					portc=33443;
					portd=33444;
					break;

				case CAMEROA_L2:
					adresse=0xC0A80617;		// 192.168.6.23
					pt_BuffStockMdpClePriveeClient=MotDePasseClePriveeClientSUPERVCLIMSO[3];
					pt_FnMotDePasseClePriveeChiffree=FnMotDePasseClePriveeChiffreeSUPERVCLIMSO_3;
					portc=33443;
					portd=33444;
					break;

				default:
					std::cerr << "ERREUR : l'indice i n'existe pas dans les processus legers des CamerOA." << std::endl;
			}

			// Le canal de commande
			//
			if( (PLCommandeCamerOA[i]=new (std::nothrow) ProcessusLegerClientCommandeCamerOA(i,FenetrePrincipale,adresse,portc,TIMEOUT_EMISSION,TIMEOUT_RECEPTION,true,FnHandlerSIGPIPESupervCLIMSO,arguments->getOption(OptionsLC[MdpClePriveeClient]),pt_BuffStockMdpClePriveeClient,pt_FnMotDePasseClePriveeChiffree,arguments->getOption(OptionsLC[CheminFichCertCA_OA]),arguments->getOption(OptionsLC[CheminFichCertClientSupervCLIMSO]),arguments->getOption(OptionsLC[CheminFichClePriveeClientSupervCLIMSO]))) == NULL )
			{
    				std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le processus leger PLCommandeCamerOA[" << i << "]." << std::endl;
					delete FenetrePrincipale;
					appli.exit(-1);
			}
			FenetrePrincipale->PLCommandeCamerOA[i]=PLCommandeCamerOA[i];

			// Le canal des donnees
			//
			if( (PLDonneesCamerOA[i]=new (std::nothrow) ProcessusLegerClientDonneesCamerOA(i,FenetrePrincipale,adresse,portd,TIMEOUT_EMISSION,TIMEOUT_RECEPTION)) == NULL )
			{
    				std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le processus leger PLDonneesCamerOA[" << i << "]." << std::endl;
					delete FenetrePrincipale;
					appli.exit(-1);
			}
			FenetrePrincipale->PLDonneesCamerOA[i]=PLDonneesCamerOA[i];
		}

		// On instancie les processus legers de gestion des liaisons entre le superviseur et les TerminOA
		//
		for( i=0; i < NB_TERMINOA; i++ )
		{
			uint32_t adresse;													// Adresse du client pour cet indice
			uint16_t portc;														// Port du service des commandes sur le client
			uint16_t portd;														// Port du service des donnees sur le client
			char *pt_BuffStockMdpClePriveeClient;								// Stockage mot de passe cle privee pour indice
			int (*pt_FnMotDePasseClePriveeChiffree)(char*, int, int, void*);	// Fn passage mot de passe cle privee pour indice


			// Selon l'indice et donc le TerminOA
			//
			switch( i )
			{
				case TERMINOA_C1:
					adresse=0xC0A80632;		// 192.168.6.50
					pt_BuffStockMdpClePriveeClient=MotDePasseClePriveeClientSUPERVCLIMSO[4];
					pt_FnMotDePasseClePriveeChiffree=FnMotDePasseClePriveeChiffreeSUPERVCLIMSO_4;
					portc=22443;
					portd=22444;
					break;

				case TERMINOA_C2:
					adresse=0xC0A80632;		// 192.168.6.50
					pt_BuffStockMdpClePriveeClient=MotDePasseClePriveeClientSUPERVCLIMSO[5];
					pt_FnMotDePasseClePriveeChiffree=FnMotDePasseClePriveeChiffreeSUPERVCLIMSO_5;
					portc=33443;
					portd=33444;
					break;

				case TERMINOA_L1:
					adresse=0xC0A80633;		// 192.168.6.51
					pt_BuffStockMdpClePriveeClient=MotDePasseClePriveeClientSUPERVCLIMSO[6];
					pt_FnMotDePasseClePriveeChiffree=FnMotDePasseClePriveeChiffreeSUPERVCLIMSO_6;
					portc=22443;
					portd=22444;
					break;

				case TERMINOA_L2:
					adresse=0xC0A80633;		// 192.168.6.51
					pt_BuffStockMdpClePriveeClient=MotDePasseClePriveeClientSUPERVCLIMSO[7];
					pt_FnMotDePasseClePriveeChiffree=FnMotDePasseClePriveeChiffreeSUPERVCLIMSO_7;
					portc=33443;
					portd=33444;
					break;

				default:
					std::cerr << "ERREUR : l'indice i n'existe pas dans les processus legers des TerminOA." << std::endl;
			}

			// Le canal de commande
			//
			if( (PLCommandeTerminOA[i]=new (std::nothrow) ProcessusLegerClientCommandeTerminOA(i,FenetrePrincipale,adresse,portc,TIMEOUT_EMISSION,TIMEOUT_RECEPTION,true,FnHandlerSIGPIPESupervCLIMSO,arguments->getOption(OptionsLC[MdpClePriveeClient]),pt_BuffStockMdpClePriveeClient,pt_FnMotDePasseClePriveeChiffree,arguments->getOption(OptionsLC[CheminFichCertCA_OA]),arguments->getOption(OptionsLC[CheminFichCertClientSupervCLIMSO]),arguments->getOption(OptionsLC[CheminFichClePriveeClientSupervCLIMSO]))) == NULL )
			{
    				std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le processus leger PLCommandeTerminOA[" << i << "]." << std::endl;
					delete FenetrePrincipale;
					appli.exit(-1);
			}
			FenetrePrincipale->PLCommandeTerminOA[i]=PLCommandeTerminOA[i];

			// Le canal des donnees
			//
			if( (PLDonneesTerminOA[i]=new (std::nothrow) ProcessusLegerClientDonneesTerminOA(i,FenetrePrincipale,adresse,portd,TIMEOUT_EMISSION,TIMEOUT_RECEPTION)) == NULL )
			{
    				std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le processus leger PLDonneesTerminOA[" << i << "]." << std::endl;
					delete FenetrePrincipale;
					appli.exit(-1);
			}
			FenetrePrincipale->PLDonneesTerminOA[i]=PLDonneesTerminOA[i];
		}

		// Le processus leger d'une liste d'acquisitions sur C1
		//
		if( (PLAcqC1=new (std::nothrow) ProcessusLegerListeAcquisitionsC1(FenetrePrincipale,PLCommandeCamerOA[CAMEROA_C1])) == NULL )
		{
				std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le processus leger PLAcqC1." << std::endl;
				delete FenetrePrincipale;
				appli.exit(-1);
		}
		FenetrePrincipale->PLAcqC1=PLAcqC1;

		// Le processus leger d'une liste d'acquisitions sur C2
		//
		if( (PLAcqC2=new (std::nothrow) ProcessusLegerListeAcquisitionsC2(FenetrePrincipale,PLCommandeCamerOA[CAMEROA_C2])) == NULL )
		{
				std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le processus leger PLAcqC2." << std::endl;
				delete FenetrePrincipale;
				appli.exit(-1);
		}
		FenetrePrincipale->PLAcqC2=PLAcqC2;

		// Le processus leger d'une liste d'acquisitions sur L1
		//
		if( (PLAcqL1=new (std::nothrow) ProcessusLegerListeAcquisitionsL1(FenetrePrincipale,PLCommandeCamerOA[CAMEROA_L1])) == NULL )
		{
				std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le processus leger PLAcqL1." << std::endl;
				delete FenetrePrincipale;
				appli.exit(-1);
		}
		FenetrePrincipale->PLAcqL1=PLAcqL1;

		// Le processus leger d'une liste d'acquisitions sur L2
		//
		if( (PLAcqL2=new (std::nothrow) ProcessusLegerListeAcquisitionsL2(FenetrePrincipale,PLCommandeCamerOA[CAMEROA_L2])) == NULL )
		{
				std::cerr << "SupervCLIMSO: ERREUR: Impossible de creer le processus leger PLAcqL2." << std::endl;
				delete FenetrePrincipale;
				appli.exit(-1);
		}
		FenetrePrincipale->PLAcqL2=PLAcqL2;


		// Demarrage de tous les processus legers de l'application
		//
		PLTemperatures->start();

		PLCommandeRobOA->start();

		for( i=0; i < NB_CAMEROA; i++ )
		{
				PLCommandeCamerOA[i]->start();
				PLDonneesCamerOA[i]->start();
		}

		for( i=0; i < NB_TERMINOA; i++ )
		{
				PLCommandeTerminOA[i]->start();
				PLDonneesTerminOA[i]->start();
		}

		PLAcqC1->start();
		PLAcqC2->start();
		PLAcqL1->start();
		PLAcqL2->start();


		// Tant que les threads ne sont pas tous lances et operationnels
		//
		while( SemaphoreSyncLancementThreadSupervCLIMSO.available() > 0 );


		// On place la fenetre principale
		//
		GeometrieFenetre=FenetrePrincipale->geometry();
		GeometrieFenetre.setLeft(0);
		GeometrieFenetre.setTop(0);
		FenetrePrincipale->setGeometry(GeometrieFenetre);

		// On peut afficher la fenetre de controle des TerminOA en mode modeless independante (pas modale)
		//
		GeometrieFenetre=FenetrePrincipale->geometry();
		QRect GeometrieFenetreCtrlTerminOA=FenetrePrincipale->FenetreCtrlTerminOA->geometry();
		GeometrieFenetreCtrlTerminOA.setLeft(0);
		GeometrieFenetreCtrlTerminOA.setTop(GeometrieFenetre.bottom()+30);
		FenetrePrincipale->FenetreCtrlTerminOA->setGeometry(GeometrieFenetreCtrlTerminOA);
		FenetrePrincipale->FenetreCtrlTerminOA->show();

		// On peut afficher la fenetre de la fiche d'observation en mode modeless independante (pas modale)
		//
		GeometrieFenetre=FenetrePrincipale->geometry();
		QRect GeometrieFenetreCahier=FenetrePrincipale->FenetreFicheObservation->geometry();
		GeometrieFenetreCahier.setLeft(GeometrieFenetre.right()+20);
		GeometrieFenetreCahier.setRight(1599);
		GeometrieFenetreCahier.setTop(0);
		GeometrieFenetreCahier.setBottom(GeometrieFenetre.bottom());
		FenetrePrincipale->FenetreFicheObservation->setGeometry(GeometrieFenetreCahier);
		FenetrePrincipale->FenetreFicheObservation->show();

		// On peut afficher la fenetre de visualisation des CamerOA en mode modeless independante (pas modale)
		//
		GeometrieFenetre=FenetrePrincipale->FenetreCamerOA->geometry();
		GeometrieFenetre.setLeft(1601);
		GeometrieFenetre.setTop(0);
		FenetrePrincipale->FenetreCamerOA->setGeometry(GeometrieFenetre);
		FenetrePrincipale->FenetreCamerOA->show();

		// On peut afficher la fenetre de visualisation des temperatures en mode modeless independante (pas modale)
		//
		GeometrieFenetre=FenetrePrincipale->FenetreCamerOA->geometry();
		QRect GeometrieFenetreT=FenetrePrincipale->FenetreTemperatures->geometry();
		GeometrieFenetreT.setLeft(GeometrieFenetre.right()+10);
		GeometrieFenetreT.setTop(0);
		FenetrePrincipale->FenetreTemperatures->setGeometry(GeometrieFenetreT);
		FenetrePrincipale->FenetreTemperatures->show();


		FenetrePrincipale->MAJEtatBoutonsFP();
		FenetrePrincipale->Log("SupervCLIMSO lancé.");


		// Autorisation du rafraichissement des sondes de temperature
		//
		PLTemperatures->ConnexionAutorisee();

		// Boucle d'execution de la fenetre principale (elle a un drapeau WDestructiveClose par defaut, elle se detruira elle meme)
		//
		int retour=appli.exec();


		// Arrêt des processus legers
		//
		if( PLAcqC1->running() ) PLAcqC1->DemandeTerminaison();
		if( PLAcqC2->running() ) PLAcqC2->DemandeTerminaison();
		if( PLAcqL1->running() ) PLAcqL1->DemandeTerminaison();
		if( PLAcqL2->running() ) PLAcqL2->DemandeTerminaison();

		if( PLTemperatures->running() ) PLTemperatures->DemandeTerminaison();

		if( PLCommandeRobOA->running() ) PLCommandeRobOA->DemandeTerminaison();

		for( i=0; i < NB_CAMEROA; i++ )
		{
			if( PLCommandeCamerOA[i]->running() )
			{
				PLCommandeCamerOA[i]->DemandeTerminaison();
			}

			if( PLDonneesCamerOA[i]->running() )
			{
				PLDonneesCamerOA[i]->DemandeTerminaison();
			}
		}
		for( i=0; i < NB_TERMINOA; i++ )
		{
			if( PLCommandeTerminOA[i]->running() )
			{
				PLCommandeTerminOA[i]->DemandeTerminaison();
			}

			if( PLDonneesTerminOA[i]->running() )
			{
				PLDonneesTerminOA[i]->DemandeTerminaison();
			}
		}

		// Attente de la terminaison des processus legers
		//
		for( i=0; i < NB_CAMEROA; i++ )
		{
			PLCommandeCamerOA[i]->wait(TEMPS_ATTENTE_TERMINAISON_PROCESSUS_LEGER);
			PLDonneesCamerOA[i]->wait(TEMPS_ATTENTE_TERMINAISON_PROCESSUS_LEGER);
		}
		for( i=0; i < NB_TERMINOA; i++ )
		{
			PLCommandeTerminOA[i]->wait(TEMPS_ATTENTE_TERMINAISON_PROCESSUS_LEGER);
			PLDonneesTerminOA[i]->wait(TEMPS_ATTENTE_TERMINAISON_PROCESSUS_LEGER);
		}
		PLCommandeRobOA->wait(TEMPS_ATTENTE_TERMINAISON_PROCESSUS_LEGER);
		PLTemperatures->wait(TEMPS_ATTENTE_TERMINAISON_PROCESSUS_LEGER);
		PLAcqC1->wait(TEMPS_ATTENTE_TERMINAISON_PROCESSUS_LEGER);
		PLAcqC2->wait(TEMPS_ATTENTE_TERMINAISON_PROCESSUS_LEGER);
		PLAcqL1->wait(TEMPS_ATTENTE_TERMINAISON_PROCESSUS_LEGER);
		PLAcqL2->wait(TEMPS_ATTENTE_TERMINAISON_PROCESSUS_LEGER);


		// On lave la liste des options et arguments de la ligne de commande de l'application
		//
		arguments->clear();
		
		// Resultat de l'execution de la QApplication heritee par KApplication
		//
		return retour;
	}
}
