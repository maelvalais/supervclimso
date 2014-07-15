//
// MODULE DU WIDGET DE REPRESENTATION GRAPHIQUE DE LA ROUE A FILTRES DE L'INSTRUMENT C2 DE CLIMSO
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

#include <WidgetRoueFiltresC2.h>


// Constructeur de la classe du widget de representation graphique de la roue a filtres de l'instrument C2 de CLIMSO
//
RoueFiltresC2::RoueFiltresC2(QWidget *parent,const char *name,WFlags f) : QWidget(parent,name,f)
{
	// Ce widget ne sera pas efface avant un evenement paintEvent() car il est trace sur toute sa surface
	//
	setWFlags(Qt::WNoAutoErase);

	// Initialisation des variables
	//
	pos=0;

	PinceauBlanc.setColor(Qt::white);
	PinceauNoir.setColor(Qt::black);

	PinceauFond.setColor(QColor(123,154,231));
	BrosseFond.setColor(QColor(123,154,231));
	BrosseFond.setStyle(SolidPattern);

	PinceauRoue.setColor(QColor(190,190,190));
	BrosseRoue.setColor(QColor(190,190,190));
	BrosseRoue.setStyle(SolidPattern);

	PinceauFiltreActif.setColor(QColor(255,0,0));
}


// Destructeur de la classe
//
RoueFiltresC2::~RoueFiltresC2()
{
}


// Angle de position de la roue a filtres de C2 en degres
//
// CE:	On passe l'angle de position de la roue a filtres de C2 en degres (pos=0° vers le bas, positif dans le sens trigonometrique vu de derriere l'instrument)
//
void RoueFiltresC2::AnglePositionRoue(double ppos)
{
	pos=ppos;

	// Declanchement d'un evenement d'affichage
	//
	update();
}


// Surcharge de la fonction de slot paintEvent heritee du QWidget
//
void RoueFiltresC2::paintEvent(QPaintEvent *event)
{
	QPaintEvent *ev;			// Pour eviter un Warning a la compilation
	ev=event;
	double Trad=M_PI/180.0;		// Degres vers Radians
	double xc;					// Position d'un centre
	double yc;
	double v;					// Variable de travail

	// L'objet de dessin va directement dessiner sur l'objet qui herite de QWidget et donc de QPaintDevice
	//
	QPainter Dessin(this);

	QFontMetrics InfosFontCourante=Dessin.fontMetrics();

	// On trace le fond de la representation
	//
	Dessin.fillRect(0,0,width(),height(),BrosseFond);

	// Centre de la roue
	//
	xc_roue=width()/2;
	yc_roue=height()/2;

	// Rayon de la roue
	//
	r_roue=xc_roue*4/5;

	// On dessine l'angle de la roue
	//
	Dessin.setPen(PinceauNoir);
	Dessin.drawLine(xc_roue,yc_roue,xc_roue,height());
	v=(-90.0+pos)*Trad;
	xc=yc=((double) (r_roue+5));
	xc*=cos(v);
	yc*=-sin(v);
	xc+=(double) xc_roue;
	yc+=(double) yc_roue;
	Dessin.drawLine(xc_roue,yc_roue,((int) xc),((int) yc));

	// On dessine la roue a filtres
	//
	Dessin.setPen(PinceauRoue);
	Dessin.setBrush(BrosseRoue);
	Dessin.drawPie(xc_roue-r_roue,yc_roue-r_roue,r_roue*2,r_roue*2,0,5760);
	Dessin.setPen(PinceauNoir);
	Dessin.drawArc(xc_roue-r_roue,yc_roue-r_roue,r_roue*2,r_roue*2,0,5760);

	// Rayon du centre du filtre
	//
	v=((double) r_roue)*0.75;
	int r_cenF=(int) v;

	// Rayon des filtres
	//
	v=((double) r_roue)*0.21;
	int r_ouvF=(int) v;

	// Pour chaque ouverture
	//
	for( double p=0; p < 360.0; p +=360.0/6.0 )
	{
		// Position du filtre dans le repere graphique du widget
		//
		v=(-90.0+pos+p)*Trad;

		xc=yc=((double) r_cenF);
		xc*=cos(v);
		yc*=-sin(v);
		xc+=(double) xc_roue;
		yc+=(double) yc_roue;

		Dessin.setPen(PinceauFond);
		Dessin.setBrush(BrosseFond);
		Dessin.drawPie(((int) xc)-r_ouvF,((int) yc)-r_ouvF,r_ouvF*2,r_ouvF*2,0,5760);
		Dessin.setPen(PinceauNoir);
		Dessin.drawArc(((int) xc)-r_ouvF,((int) yc)-r_ouvF,r_ouvF*2,r_ouvF*2,0,5760);
	}

	// Representation du centre de la roue
	//
	Dessin.setPen(PinceauNoir);
	Dessin.drawPoint(xc_roue,yc_roue);

	// Pour chaque filtre
	//
	for( int modeobs=0; modeobs < 4; modeobs++ )
	{
		int dx;								// Decalage en x pour l'affichage du filtre
		int dy;								// Decalage en y pour l'affichage du filtre
		double vF=(-90.0+pos)*Trad;			// Angle de position du filtre dans le repere graphique du widget
		QString NomFiltre;

		switch( modeobs )
		{
			case 0:
				NomFiltre="10747";
				v=0.0;					// Angle du filtre dans le repere graphique du widget
				break;

			case 1:
				NomFiltre="10770";
				v=-360.0/6.0;			// Angle du filtre dans le repere graphique du widget
				break;

			case 2:
				NomFiltre="10798";
				v=-2.0*360.0/6.0;		// Angle du filtre dans le repere graphique du widget
				break;

			case 3:
				NomFiltre="10830";
				v=-3.0*360.0/6.0;		// Angle du filtre dans le repere graphique du widget
				break;
		}
		dx=InfosFontCourante.width(NomFiltre)/2;
		dy=-InfosFontCourante.height()/4;

		v*=Trad;
		vF+=v;

		// Position du filtre
		//
		xc=yc=((double) r_cenF);
		xc*=cos(vF);
		yc*=-sin(vF);
		xc+=(double) xc_roue;
		yc+=(double) yc_roue;

		Dessin.drawText(((int) xc)-dx,((int) yc)-dy,NomFiltre);
	}

	// La position du filtre actif
	//
	Dessin.setPen(PinceauFiltreActif);
	Dessin.setBrush(QBrush(NoBrush));

	v=-M_PI_2;
	xc=yc=((double) r_cenF);
	xc*=cos(v);
	yc*=-sin(v);
	xc+=(double) xc_roue;
	yc+=(double) yc_roue;
	Dessin.drawRect(((int) xc)-r_ouvF-2,((int) yc)-r_ouvF-2,r_ouvF*2+4,r_ouvF*2+4);

	Dessin.end();
}


// Surcharge de la fonction retournant la dimension recommandee du widget
//
QSize RoueFiltresC2::sizeHint()
{
	QSize dimension_recommandee(TAILLE_X_OBJROUEFILTRESC2_RECOMMANDEE,TAILLE_Y_OBJROUEFILTRESC2_RECOMMANDEE);
	
	return dimension_recommandee;
}

