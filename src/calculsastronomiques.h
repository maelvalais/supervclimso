//
// HEADER DU MODULE DES CALCULS ASTRONOMIQUES
//
// (d) David.Romeuf@univ-lyon1.fr le 23/11/2006
//

#ifndef _CALCULSASTRONOMIQUES_
#define _CALCULSASTRONOMIQUES_

class CalculsAstronomiques
{
	public:
		double JJ(int jo,int mo,int an);		// Le jour julien
		double UT1mTAI_1990_2020(double jj);	// Calcul de la difference de temps UT1-TAI
		double PENT(double x);					// La partie entiere
		double Modulo_2PI(double x);			// Modulo 2 PI

		// Calcul de la Nutation et de l'obliquite de l'ecliptique
		//
		void CalculNutationObliquite(double jde,double *nl,double *no,double *epsilon);

		// Calcul des coordonnees heliographiques du centre et du disque solaire
		//
		void CoordonneesHeliographiquesCentreDisqueSolaire(double jj,double *P,double *Lo,double *Bo);

		// Calcul des coordonnees ecliptiques heliocentriques de la Terre par VSOP87
		//
		void CalculCoordonneesEcliptiquesHeliocentriquesTerreVSOP87(double jj,double *L,double *B,double *R);
};

#endif
