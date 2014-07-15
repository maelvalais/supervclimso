//
// HEADER DU MODULE DU WIDGET DE REPRESENTATION GRAPHIQUE DU SOLEIL EN COORDONNEES HELIOGRAPHIQUES
//
// (d)2006 David.Romeuf@univ-lyon1.fr
//

#ifndef _WIDGETSOLEILHELIOGRAPHIQUE_
#define _WIDGETSOLEILHELIOGRAPHIQUE_

#include <qbrush.h>
#include <qpen.h>
#include <qsize.h>
#include <qwidget.h>

#define TAILLE_X_OBJSOLEILHELIOGRAPHIQUE_RECOMMANDEE	256
#define TAILLE_Y_OBJSOLEILHELIOGRAPHIQUE_RECOMMANDEE	256


class SoleilHeliographique : public QWidget
{
	Q_OBJECT

private:
	int Dimx_soleil;		// Dimension en x de la representation graphique
	int Dimy_soleil;		// Dimension en y de la representation graphique
	int r_soleil;			// Rayon du Soleil en pixels de la representation graphique
	int xc_soleil;			// Position du centre du Soleil
	int yc_soleil;			// Position du centre du Soleil

	double Po;				// Angle au pole de l'extremite Nord du Soleil en radians
	double Lo;				// Longitude heliographique du centre du disque solaire en radians
	double Bo;				// Latitude heliographique du centre du disque solaire en radians

	int PasGradLoTexte;		// Pas de la graduation sur la longitude heliographique en degres sur le texte
	int PasGradBoTexte;		// Pas de la graduation sur la latitude heliographique en degres sur le texte
	int PasGradPTexte;		// Pas de la graduation sur l'angle au pole en degres sur le texte

	QPen PinceauBlanc;		// Pinceau de couleur blanc
	QPen PinceauNoir;		// Pinceau de couleur noir
	QBrush BrosseCiel;		// Brosse pour peindre le fond de ciel
	QPen PinceauDisque;		// Pinceau pour tracer le disque solaire
	QBrush BrosseDisque;	// Brosse pour peindre le disque solaire
	QPen PinceauGraduations;// Pinceau pour tracer les graduations

protected:
	void paintEvent(QPaintEvent *event);	// Surcharge du slot herite de QWidget
	QSize sizeHint();						// Surcharge de la fonction retournant la dimension recommandee pour le widget

public:
	// Constructeur de l'objet (jamais de type de retour)
	//
	SoleilHeliographique(QWidget *parent=0,const char *name=0,WFlags f=0);

	// Destructeur de l'objet (jamais de type de retour et d'argument)
	//
	~SoleilHeliographique();

	// Parametrage des coordonnees heliographiques a representer
	//
	void ParametresHeliographiques(double pPo,double pLo,double pBo);

	// Parametrage du pas de la graduation sur Lo en degres pour le texte
	//
	void ParametragePasGradLoTexte(int pas);

	// Parametrage du pas de la graduation sur Bo en degres pour le texte
	//
	void ParametragePasGradBoTexte(int pas);

	// Parametrage du pas de la graduation sur P en degres pour le texte
	//
	void ParametragePasGradPTexte(int pas);
};

#endif
