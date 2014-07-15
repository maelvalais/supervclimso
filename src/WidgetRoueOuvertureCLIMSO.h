//
// HEADER DU MODULE DU WIDGET DE REPRESENTATION GRAPHIQUE DE LA ROUE D'OUVERTURE DE CLIMSO
//
// (d)2006 David.Romeuf@univ-lyon1.fr
//

#ifndef _WIDGETROUEOUVERTURECLIMSO_
#define _WIDGETROUEOUVERTURECLIMSO_

#include <qbrush.h>
#include <qpen.h>
#include <qsize.h>
#include <qwidget.h>

#define TAILLE_X_OBJROUEOUVERTURECLIMSO_RECOMMANDEE	256
#define TAILLE_Y_OBJROUEOUVERTURECLIMSO_RECOMMANDEE	256


class RoueOuvertureCLIMSO : public QWidget
{
	Q_OBJECT

private:

	int xc_roue;			// Abscisse du centre de la roue
	int yc_roue;			// Ordonnees du centre de la roue
	int r_roue;				// Rayon de la roue

	double pos;				// Angle de position en degres

	QPen PinceauBlanc;		// Pinceau de couleur blanc
	QPen PinceauNoir;		// Pinceau de couleur noir

	QPen PinceauFond;		// Pinceau pour tracer le fond
	QBrush BrosseFond;		// Brosse pour peindre le fond
	QPen PinceauRoue;		// Pinceau pour tracer la roue
	QBrush BrosseRoue;		// Brosse pour peindre la roue

	QPen PinceauInstruments;// Pinceau pour tracer l'emplacement des instruments

protected:
	void paintEvent(QPaintEvent *event);	// Surcharge du slot herite de QWidget
	QSize sizeHint();						// Surcharge de la fonction retournant la dimension recommandee pour le widget

public:
	// Constructeur de l'objet (jamais de type de retour)
	//
	RoueOuvertureCLIMSO(QWidget *parent=0,const char *name=0,WFlags f=0);

	// Destructeur de l'objet (jamais de type de retour et d'argument)
	//
	~RoueOuvertureCLIMSO();

	// Position de la roue d'ouverture de CLIMSO en degres (pos=0° vers le bas, positif dans le sens trigonometrique vu de derriere l'instrument)
	//
	void AnglePositionRoue(double ppos);
};

#endif
