//
// MODULE DU WIDGET DE REPRESENTATION GRAPHIQUE DU SOLEIL EN COORDONNEES HELIOGRAPHIQUES
//
// (d)2006 David.Romeuf@univ-lyon1.fr
//

// Inclusions C++
//
#include <iostream>
#include <math.h>

using namespace std;

// Inclusions Qt
//
#include <qcolor.h>
#include <qfont.h>
#include <qpainter.h>
#include <qstring.h>

#include <WidgetSoleilHeliographique.h>

//
// Nom des cardinaux pour le Soleil
//
QString NomCardinauxSoleil[] = {
	"Nord",
	"Est",
	"Sud",
	"Ouest"
};

#define NORDSOL		0
#define ESTSOL		1
#define SUDSOL		2
#define OUESTSOL	3


// Constructeur de la classe du widget de representation graphique du Soleil en coordonnees heliographiques
//
SoleilHeliographique::SoleilHeliographique(QWidget *parent,const char *name,WFlags f) : QWidget(parent,name,f)
{
	// Ce widget ne sera pas efface avant un evenement paintEvent() car il est trace sur toute sa surface
	//
	setWFlags(Qt::WNoAutoErase);

	// Initialisation des variables
	//
	Po=Lo=Bo=0;
	PasGradLoTexte=10;
	PasGradBoTexte=10;
	PasGradPTexte=10;

	PinceauBlanc.setColor(Qt::white);
	PinceauNoir.setColor(Qt::black);
	BrosseCiel.setColor(QColor(123,154,231));
	BrosseCiel.setStyle(SolidPattern);
	PinceauDisque.setColor(QColor(255,255,0));
	BrosseDisque.setColor(QColor(255,255,0));
	BrosseDisque.setStyle(SolidPattern);
	PinceauGraduations.setColor(QColor(150,150,150));
}


// Destructeur de la classe
//
SoleilHeliographique::~SoleilHeliographique()
{
}


// Fonction de parametrage des coordonnees heliographiques a representer
//
//	CE: On passe l'angle au pole de l'extremite Nord du Soleil en radians ;
//
//		On passe la longitude heliographique du centre du disque solaire en radians ;
//
//		On passe la latitude heliographique du centre du disque solaire en radians ;
//
void SoleilHeliographique::ParametresHeliographiques(double pPo,double pLo,double pBo)
{
	Po=pPo;
	Lo=pLo;
	Bo=pBo;

	// Declanchement d'un evenement d'affichage
	//
	update();
}


// Parametrage du pas de la graduation sur Lo en degres sur le texte
//
// CE:	On passe le pas de la graduation en degres
//
void SoleilHeliographique::ParametragePasGradLoTexte(int pas)
{
	PasGradLoTexte=pas;

	update();
}


// Parametrage du pas de la graduation sur Bo en degres sur le texte
//
// CE:	On passe le pas de la graduation en degres
//
void SoleilHeliographique::ParametragePasGradBoTexte(int pas)
{
	PasGradBoTexte=pas;

	update();
}


// Parametrage du pas de la graduation sur P en degres sur le texte
//
// CE:	On passe le pas de la graduation en degres
//
void SoleilHeliographique::ParametragePasGradPTexte(int pas)
{
	PasGradPTexte=pas;

	update();
}


// Surcharge de la fonction de slot paintEvent heritee du QWidget
//
void SoleilHeliographique::paintEvent(QPaintEvent *event)
{
	QPaintEvent *ev;	// Pour eviter un Warning a la compilation
	ev=event;

	// L'objet de dessin va directement dessiner sur l'objet qui herite de QWidget et donc de QPaintDevice
	//
	QPainter Dessin(this);

	QFontMetrics InfosFontCourante=Dessin.fontMetrics();

	int Dimx_soleil=size().width();				// Largeur du widget
	int Dimy_soleil=size().height();			// Hauteur du widget

	int r_soleil=( Dimx_soleil < Dimy_soleil ) ? Dimx_soleil : Dimy_soleil;
	r_soleil/=2;
	r_soleil-=InfosFontCourante.height()*3/2;
	if( r_soleil % 2 == 0 ) r_soleil-=1;		// Si le rayon est paire alors on le place impaire

	// On decide de la position et la dimension du soleil
	//
	xc_soleil=Dimx_soleil >> 1;
	yc_soleil=Dimy_soleil >> 1;

	// On trace le fond de la representation
	//
	Dessin.fillRect(0,0,Dimx_soleil,Dimy_soleil,BrosseCiel);

	//
	// On trace le disque du Soleil
	//
	Dessin.setPen(PinceauBlanc);
	Dessin.drawLine(0,yc_soleil,Dimx_soleil,yc_soleil);
	Dessin.drawLine(xc_soleil,0,xc_soleil,Dimy_soleil);
	Dessin.setPen(PinceauDisque);
	Dessin.setBrush(BrosseDisque);
	Dessin.drawPie(xc_soleil-r_soleil,yc_soleil-r_soleil,r_soleil*2,r_soleil*2,0,5760);

	//
	// On affiche les cardinaux celestes
	//
	Dessin.setPen(PinceauNoir);
	Dessin.drawText(xc_soleil-InfosFontCourante.width(NomCardinauxSoleil[NORDSOL])/2,yc_soleil-r_soleil-InfosFontCourante.height()/2,NomCardinauxSoleil[NORDSOL]);
	Dessin.drawText(xc_soleil-InfosFontCourante.width(NomCardinauxSoleil[SUDSOL])/2,yc_soleil+r_soleil+InfosFontCourante.height(),NomCardinauxSoleil[SUDSOL]);
	Dessin.save();
	Dessin.translate(xc_soleil-r_soleil-InfosFontCourante.height()/2,yc_soleil+InfosFontCourante.width(NomCardinauxSoleil[ESTSOL])/2);
	Dessin.rotate(-90);
	Dessin.drawText(0,0,NomCardinauxSoleil[ESTSOL],-1,QPainter::LTR);
	Dessin.restore();
	Dessin.save();
	Dessin.translate(xc_soleil+r_soleil+InfosFontCourante.height()/2,yc_soleil-InfosFontCourante.width(NomCardinauxSoleil[OUESTSOL])/2);
	Dessin.rotate(90);
	Dessin.drawText(0,0,NomCardinauxSoleil[OUESTSOL],-1,QPainter::LTR);
	Dessin.restore();


	// On trace maintenant les reperes heliographiques
	//
	QFont FontGraduation=Dessin.font();
	FontGraduation.setStretch(70);
	Dessin.setFont(FontGraduation);
	InfosFontCourante=Dessin.fontMetrics();

	double Trad=M_PI/180.0;				// Transformation degres en radians
	double Tdeg=180.0/M_PI;				// Transformation degres en radians
	double P;							// Variable de l'angle au pole PA
	double L;							// Variable de la longitude heliographique
	double B;							// Variable de la latitude heliographique
	double Lo10;						// Partie entiere de Lo en multiple de 10 degres
	double LoMLo10;						// Ecart angulaire entre Lo et Lo10
	double aPo;							// Angle au pole adapte a la representation
	QString chaine;						// Chaine de composition

	Dessin.setPen(PinceauBlanc);

	for( P=0; P < 360.0; P+=10.0 )
	{
		int iP;
		double x1;
		double y1;
		double x2;
		double y2;
		double cosP=cos(P*Trad+M_PI_2);
		double sinP=sin(P*Trad+M_PI_2);

		x1=y1=((double) r_soleil);
		x2=y2=x1+4;

		x1*=cosP;
		x2*=cosP;
		y1*=-sinP;
		y2*=-sinP;

		x1+=xc_soleil;
		x2+=xc_soleil;
		y1+=yc_soleil;
		y2+=yc_soleil;

		Dessin.drawLine((int) x1,(int) y1,(int) x2,(int) y2);

		iP=(int) P;

		if( iP != 0 && iP != 180 && (iP % PasGradPTexte) == 0 )
		{
			chaine=QString("%1").arg(iP);

			Dessin.save();
			Dessin.setPen(PinceauNoir);
			if( iP < 180 )
			{
				Dessin.drawText(((int) x2)-InfosFontCourante.width(chaine),((int) y2)+((iP > 90 && iP < 270 ) ? InfosFontCourante.height() : 0),chaine);
			}
			else
			{
				Dessin.drawText(((int) x2),((int) y2)+((iP > 90 && iP < 270 ) ? InfosFontCourante.height() : 0),chaine);
			}
			Dessin.restore();
		}
	}

	Dessin.setPen(PinceauGraduations);

	// Angle au pole du pole du Soleil
	//
	aPo=-Po;

	// Partie entiere de Lo en modulo de 10 degres
	//
	modf(Lo*Tdeg/10.0,&Lo10);
	Lo10*=10.0;

	// Ecart angulaire entre Lo et Lo10 pour representer le meridien Lo et pas les coordonnees heliographiques L=0 au centre
	//
	LoMLo10=Lo*Tdeg-Lo10;

	for( L=-80.0; L <= 90.0; L+=10.0 )
	{
		int ax=-9999;
		int ay=-9999;

		for( B=-90.0; B <= 90.0; B+=10.0 )
		{
			double Lar;	// Longitude heliographique a representer
			double x;	// Variables pour le calcul de la projection
			double y;
			double X;	// Variables pour le calcul de la rotation
			double Y;

			// Longitude heliographique a representer
			//
			Lar=(L-LoMLo10)*Trad;

			// Coordonnees rectangulaires du point represente
			//
			x=((double) r_soleil)*cos(B*Trad)*sin(Lar);
			y=((double) r_soleil)*(sin(B*Trad)*cos(Bo)-cos(B*Trad)*cos(Lar)*sin(Bo));

			// Rotation de l'angle au Pole
			//
			X=x*cos(aPo)+y*sin(aPo);
			Y=-x*sin(aPo)+y*cos(aPo);

			// On trace le point ou le segment
			//
			if( ax != -9999 )
			{
				int mx;
				int my;

				Dessin.drawLine(ax,ay,mx=xc_soleil+(int) X,my=yc_soleil-(int) Y);

				ax=mx;
				ay=my;
			}
			else
			{
				Dessin.drawPoint(ax=xc_soleil+(int) X,ay=yc_soleil-(int) Y);
			}

			// On affiche la longitude heliographique au niveau de la latitude nulle
			//
			if( B == 0.0 )
			{
				int iLaff;					// Longitude a afficher en entier
				double Laff;				// Longitude a afficher

				Laff=Lo10+L;
				if( Laff >= 360.0 ) Laff-=360.0;
				if( Laff < 0.0 ) Laff+=360.0;

				if( modf(Laff,&Laff) > 0.5 ) Laff+=1.0;

				iLaff=(int) Laff;

				if( (iLaff % PasGradLoTexte) == 0 )
				{
					chaine=QString("%1").arg(iLaff);

					Dessin.save();
					Dessin.translate(xc_soleil+((int) X)+InfosFontCourante.height()/2,yc_soleil-((int) Y)+InfosFontCourante.width(chaine)/2);
					Dessin.rotate(-90);
					Dessin.setPen(PinceauNoir);
					Dessin.drawText(0,0,chaine,-1,QPainter::LTR);
					Dessin.restore();
				}
			}
		}
	}


	for( B=-90.0; B <= 90.0; B+=10.0 )
	{
		int ax=-9999;
		int ay=-9999;

		for(  L=-80.0; L <= 90.0; L+=5.0 )
		{
			double Lar;	// Longitude heliographique a representer
			double x;	// Variables pour le calcul de la projection
			double y;
			double X;	// Variables pour le calcul de la rotation
			double Y;

			// Longitude heliographique a representer
			//
			Lar=(L-LoMLo10)*Trad;

			// Coordonnees rectangulaires du point represente
			//
			x=((double) r_soleil)*cos(B*Trad)*sin(Lar);
			y=((double) r_soleil)*(sin(B*Trad)*cos(Bo)-cos(B*Trad)*cos(Lar)*sin(Bo));

			// Rotation de l'angle au Pole
			//
			X=x*cos(aPo)+y*sin(aPo);
			Y=-x*sin(aPo)+y*cos(aPo);

			// On trace le point ou le segment
			//
			if( ax != -9999 )
			{
				int mx;
				int my;

				Dessin.drawLine(ax,ay,mx=xc_soleil+(int) X,my=yc_soleil-(int) Y);

				ax=mx;
				ay=my;
			}
			else
			{
				Dessin.drawPoint(ax=xc_soleil+(int) X,ay=yc_soleil-(int) Y);
			}

			// On affiche la latitude heliographique au niveau de la longitude heliographique -10
			//
			if( L == -10.0 )
			{
				int iB;				// Latitude a afficher en entier

				iB=(int) B;

				if( (iB % PasGradBoTexte) == 0 )
				{
					chaine=QString("%1").arg(B,0);

					Dessin.save();
					Dessin.setPen(PinceauNoir);
					Dessin.drawText(xc_soleil+((int) X)-InfosFontCourante.width(chaine)/2,yc_soleil-((int) Y)+InfosFontCourante.height()/2,chaine);
					Dessin.restore();
				}
			}
		}
	}

	Dessin.setPen(PinceauNoir);
	chaine=QString("Lo=%1").arg(Lo*Tdeg,0,'f',2);
	Dessin.drawText(5,height()-5,chaine);
	chaine=QString("Bo=%1").arg(Bo*Tdeg,0,'f',2);
	Dessin.drawText(width()-InfosFontCourante.width(chaine)-5,height()-5,chaine);
	chaine=QString("Po=%1").arg(Po*Tdeg,0,'f',2);
	Dessin.drawText(5,5+InfosFontCourante.height(),chaine);

	Dessin.end();
}


// Surcharge de la fonction retournant la dimension recommandee du widget
//
QSize SoleilHeliographique::sizeHint()
{
	QSize dimension_recommandee(TAILLE_X_OBJSOLEILHELIOGRAPHIQUE_RECOMMANDEE,TAILLE_Y_OBJSOLEILHELIOGRAPHIQUE_RECOMMANDEE);
	
	return dimension_recommandee;
}

