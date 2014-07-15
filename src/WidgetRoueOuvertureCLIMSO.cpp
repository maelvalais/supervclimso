//
// MODULE DU WIDGET DE REPRESENTATION GRAPHIQUE DE LA ROUE D'OUVERTURE DE CLIMSO
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

#include <WidgetRoueOuvertureCLIMSO.h>


// Constructeur de la classe du widget de representation graphique de la roue d'ouverture de CLIMSO
//
RoueOuvertureCLIMSO::RoueOuvertureCLIMSO(QWidget *parent,const char *name,WFlags f) : QWidget(parent,name,f)
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

	PinceauInstruments.setColor(QColor(255,0,0));
}


// Destructeur de la classe
//
RoueOuvertureCLIMSO::~RoueOuvertureCLIMSO()
{
}


// Angle de position de la roue d'ouverture de CLIMSO en degres
//
// CE:	On passe l'angle de position de la roue d'ouverture en degres (pos=0° vers le bas, positif dans le sens trigonometrique vu de derriere l'instrument)
//
void RoueOuvertureCLIMSO::AnglePositionRoue(double ppos)
{
	pos=-ppos;

	// Declanchement d'un evenement d'affichage
	//
	update();
}


// Surcharge de la fonction de slot paintEvent heritee du QWidget
//
void RoueOuvertureCLIMSO::paintEvent(QPaintEvent *event)
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
	r_roue=xc_roue-5;

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

	// On dessine la roue d'ouverture
	//
	Dessin.setPen(PinceauRoue);
	Dessin.setBrush(BrosseRoue);
	Dessin.drawPie(xc_roue-r_roue,yc_roue-r_roue,r_roue*2,r_roue*2,0,5760);
	Dessin.setPen(PinceauNoir);
	Dessin.drawArc(xc_roue-r_roue,yc_roue-r_roue,r_roue*2,r_roue*2,0,5760);

	// Rayon du centre de l'ouverture de L1
	//
	v=((double) r_roue)*0.532;
	int r_cenL1=(int) v;

	// Rayon du centre de l'ouverture de L2
	//
	v=((double) r_roue)*0.354;
	int r_cenL2=(int) v;

	// Rayon du centre de l'ouverture de C1 et C2
	//
	v=((double) r_roue)*0.768;
	int r_cenC=(int) v;

	// Rayon des ouvertures de C1 et C2
	//
	v=((double) r_roue)*0.184;
	int r_ouvC=(int) v;

	// Rayon des ouvertures de L1 et L2
	//
	v=((double) r_roue)*0.081;
	int r_ouvL=(int) v;

	// Pour chaque ouverture
	//
	for( double p=0; p < 360.0; p +=360.0/11.0 )
	{
		// Position de l'ouverture de C1 ou C2
		//
		v=(-90.0+pos+p)*Trad;

		xc=yc=((double) r_cenC);
		xc*=cos(v);
		yc*=-sin(v);
		xc+=(double) xc_roue;
		yc+=(double) yc_roue;

		Dessin.setPen(PinceauFond);
		Dessin.setBrush(BrosseFond);
		Dessin.drawPie(((int) xc)-r_ouvC,((int) yc)-r_ouvC,r_ouvC*2,r_ouvC*2,0,5760);
		Dessin.setPen(PinceauNoir);
		Dessin.drawArc(((int) xc)-r_ouvC,((int) yc)-r_ouvC,r_ouvC*2,r_ouvC*2,0,5760);

		// Position de l'ouverture L2 (angle identique a C1 et C2)
		//
		xc=yc=((double) r_cenL2);
		xc*=cos(v);
		yc*=-sin(v);
		xc+=(double) xc_roue;
		yc+=(double) yc_roue;

		Dessin.setPen(PinceauFond);
		Dessin.setBrush(BrosseFond);
		Dessin.drawPie(((int) xc)-r_ouvL,((int) yc)-r_ouvL,r_ouvL*2,r_ouvL*2,0,5760);
		Dessin.setPen(PinceauNoir);
		Dessin.drawArc(((int) xc)-r_ouvL,((int) yc)-r_ouvL,r_ouvL*2,r_ouvL*2,0,5760);

		// Position de l'ouverture de L1
		//
		v=(-90.0+pos+p+360.0/11.0/2.0)*Trad;

		xc=yc=((double) r_cenL1);
		xc*=cos(v);
		yc*=-sin(v);
		xc+=(double) xc_roue;
		yc+=(double) yc_roue;

		Dessin.setPen(PinceauFond);
		Dessin.setBrush(BrosseFond);
		Dessin.drawPie(((int) xc)-r_ouvL,((int) yc)-r_ouvL,r_ouvL*2,r_ouvL*2,0,5760);
		Dessin.setPen(PinceauNoir);
		Dessin.drawArc(((int) xc)-r_ouvL,((int) yc)-r_ouvL,r_ouvL*2,r_ouvL*2,0,5760);

	}

	// Representation du centre de la roue
	//
	Dessin.setPen(PinceauNoir);
	Dessin.drawPoint(xc_roue,yc_roue);

	// Pour chaque mode d'observation
	//
	for( int modeobs=0; modeobs < 4; modeobs++ )
	{
		int dx;													// Decalage en x pour l'affichage du mode
		int dy;													// Decalage en y pour l'affichage du mode
		double vC1=(-90.0+pos)*Trad;							// Angle de position de C1 dans le repere graphique du widget
		double vC2=(-90.0+pos-2.0*360.0/11.0)*Trad;				// Angle de position de C2 dans le repere graphique du widget
		double vL1=(-90.0+pos+360.0/11.0+360.0/11.0/2.0)*Trad;	// Angle de position de L1 dans le repere graphique du widget
		double vL2=(-90.0+pos)*Trad;							// Angle de position de L2 dans le repere graphique du widget
		QString NomMode;

		switch( modeobs )
		{
			case 0:
				// Mode Observation
				NomMode="obs";
				v=0.0;					// Angle du mode d'observation dans le repere graphique du widget
				break;

			case 1:
				// Mode Pointage
				NomMode="pta";
				v=-360.0/11.0;			// Angle du mode d'observation dans le repere graphique du widget
				break;

			case 2:
				// Mode Calibration
				NomMode="cal";
				v=-4.0*360.0/11.0;		// Angle du mode d'observation dans le repere graphique du widget
				break;

			case 3:
				// Mode PLU
				NomMode="plu";
				v=-5.0*360.0/11.0;		// Angle du mode d'observation dans le repere graphique du widget
				break;
		}
		dx=InfosFontCourante.width(NomMode)/2;
		dy=-InfosFontCourante.height()/4;

		v*=Trad;
		vC1+=v;
		vC2+=v;
		vL1+=v;
		vL2+=v;

		// Position de l'ouverture de C1
		//
		xc=yc=((double) r_cenC);
		xc*=cos(vC1);
		yc*=-sin(vC1);
		xc+=(double) xc_roue;
		yc+=(double) yc_roue;

		Dessin.drawText(((int) xc)-dx,((int) yc)-dy,NomMode);

		// Position de l'ouverture de C2
		//
		xc=yc=((double) r_cenC);
		xc*=cos(vC2);
		yc*=-sin(vC2);
		xc+=(double) xc_roue;
		yc+=(double) yc_roue;

		Dessin.drawText(((int) xc)-dx,((int) yc)-dy,NomMode);

		// Position de l'ouverture L1
		//
		xc=yc=((double) r_cenL1);
		xc*=cos(vL1);
		yc*=-sin(vL1);
		xc+=(double) xc_roue;
		yc+=(double) yc_roue;

		Dessin.drawText(((int) xc)-dx,((int) yc)-dy,NomMode);

		// Position de l'ouverture de L2
		//
		xc=yc=((double) r_cenL2);
		xc*=cos(vL2);
		yc*=-sin(vL2);
		xc+=(double) xc_roue;
		yc+=(double) yc_roue;

		Dessin.drawText(((int) xc)-dx,((int) yc)-dy,NomMode);
	}

	// La position des instruments
	//
	Dessin.setPen(PinceauInstruments);
	Dessin.setBrush(QBrush(NoBrush));

	// La position de C1
	//
	v=(-90.0)*Trad;
	xc=yc=((double) r_cenC);
	xc*=cos(v);
	yc*=-sin(v);
	xc+=(double) xc_roue;
	yc+=(double) yc_roue;
	Dessin.drawRect(((int) xc)-r_ouvC-2,((int) yc)-r_ouvC-2,r_ouvC*2+4,r_ouvC*2+4);

	// La position de C2
	//
	v=(-90.0-2.0*360.0/11.0)*Trad;
	xc=yc=((double) r_cenC);
	xc*=cos(v);
	yc*=-sin(v);
	xc+=(double) xc_roue;
	yc+=(double) yc_roue;
	Dessin.drawRect(((int) xc)-r_ouvC-2,((int) yc)-r_ouvC-2,r_ouvC*2+4,r_ouvC*2+4);

	// La position de L1
	//
	v=(-90.0+360.0/11.0+360.0/11.0/2.0)*Trad;
	xc=yc=((double) r_cenL1);
	xc*=cos(v);
	yc*=-sin(v);
	xc+=(double) xc_roue;
	yc+=(double) yc_roue;
	Dessin.drawRect(((int) xc)-r_ouvL-2,((int) yc)-r_ouvL-2,r_ouvL*2+4,r_ouvL*2+4);

	// La position de L2
	//
	v=(-90.0)*Trad;
	xc=yc=((double) r_cenL2);
	xc*=cos(v);
	yc*=-sin(v);
	xc+=(double) xc_roue;
	yc+=(double) yc_roue;
	Dessin.drawRect(((int) xc)-r_ouvL-2,((int) yc)-r_ouvL-2,r_ouvL*2+4,r_ouvL*2+4);

	Dessin.end();
}


// Surcharge de la fonction retournant la dimension recommandee du widget
//
QSize RoueOuvertureCLIMSO::sizeHint()
{
	QSize dimension_recommandee(TAILLE_X_OBJROUEOUVERTURECLIMSO_RECOMMANDEE,TAILLE_Y_OBJROUEOUVERTURECLIMSO_RECOMMANDEE);
	
	return dimension_recommandee;
}

