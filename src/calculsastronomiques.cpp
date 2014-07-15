//
// MODULE DES CALCULS ASTRONOMIQUES
//
// (d) David.Romeuf@univ-lyon1.fr le 23/11/2006
//

#include <math.h>
#include "calculsastronomiques.h"


// Valeur de UT1-TAI obtenues sur le site de l'observatoire de Paris
//
// http://hpiers.obspm.fr/eop-pc/products/combined/C04.html
//
#define NbValeursUT1mTAIPeriode1990_2020	121

static struct dataUT1mTAI
{
	int jour;
	int mois;
	int annee;
	float valeur;
} TableauUT1mTAI[] = {
	{1,	1,	1990,	-24.671},
	{1,	4,	1990,	-24.863},
	{1,	7,	1990,	-25.038},
	{1,	10,	1990,	-25.180},
	{1,	1,	1991,	-25.381},
	{1,	4,	1991,	-25.587},
	{1,	7,	1991,	-25.773},
	{1,	10,	1991,	-25.920},
	{1,	1,	1992,	-26.125},
	{1,	4,	1992,	-26.356},
	{1,	7,	1992,	-26.556},
	{1,	10,	1992,	-26.714},
	{1,	1,	1993,	-26.937},
	{1,	4,	1993,	-27.173},
	{1,	7,	1993,	-27.400},
	{1,	10,	1993,	-27.574},
	{1,	1,	1994,	-27.800},
	{1,	4,	1994,	-28.020},
	{1,	7,	1994,	-28.217},
	{1,	10,	1994,	-28.373},
	{1,	1,	1995,	-28.601},
	{1,	4,	1995,	-28.843},
	{1,	7,	1995,	-29.061},
	{1,	10,	1995,	-29.219},
	{1,	1,	1996,	-29.444},
	{1,	4,	1996,	-29.629},
	{1,	7,	1996,	-29.812},
	{1,	10,	1996,	-29.936},
	{1,	1,	1997,	-30.110},
	{1,	4,	1997,	-30.291},
	{1,	7,	1997,	-30.473},
	{1,	10,	1997,	-30.608},
	{1,	1,	1998,	-30.781},
	{1,	4,	1998,	-30.962},
	{1,	7,	1998,	-31.100},
	{1,	10,	1998,	-31.158},
	{1,	1,	1999,	-31.283},
	{1,	4,	1999,	-31.383},
	{1,	7,	1999,	-31.480},
	{1,	10,	1999,	-31.530},
	{1,	1,	2000,	-31.644},
	{1,	4,	2000,	-31.723},
	{1,	7,	2000,	-31.795},
	{1,	10,	2000,	-31.825},
	{1,	1,	2001,	-31.906},
	{1,	4,	2001,	-31.974},
	{1,	7,	2001,	-32.027},
	{1,	10,	2001,	-32.038},
	{1,	1,	2002,	-32.115},
	{1,	4,	2002,	-32.189},
	{1,	7,	2002,	-32.229},
	{1,	10,	2002,	-32.232},
	{1,	1,	2003,	-32.289},
	{1,	4,	2003,	-32.342},
	{1,	7,	2003,	-32.383},
	{1,	10,	2003,	-32.429},
	{1,	1,	2004,	-32.474},
	{1,	4,	2004,	-32.519},
	{1,	7,	2004,	-32.565},
	{1,	10,	2004,	-32.610},
	{1,	1,	2005,	-32.656},
	{1,	4,	2005,	-32.700},
	{1,	7,	2005,	-32.746},
	{1,	10,	2005,	-32.791},
	{1,	1,	2006,	-32.837},
	{1,	4,	2006,	-32.881},
	{1,	7,	2006,	-32.927},
	{1,	10,	2006,	-32.972},
	{1,	1,	2007,	-33.018},
	{1,	4,	2007,	-33.062},
	{1,	7,	2007,	-33.108},
	{1,	10,	2007,	-33.153},
	{1,	1,	2008,	-33.199},
	{1,	4,	2008,	-33.244},
	{1,	7,	2008,	-33.289},
	{1,	10,	2008,	-33.335},
	{1,	1,	2009,	-33.380},
	{1,	4,	2009,	-33.425},
	{1,	7,	2009,	-33.470},
	{1,	10,	2009,	-33.516},
	{1,	1,	2010,	-33.561},
	{1,	4,	2010,	-33.606},
	{1,	7,	2010,	-33.651},
	{1,	10,	2010,	-33.697},
	{1,	1,	2011,	-33.742},
	{1,	4,	2011,	-33.787},
	{1,	7,	2011,	-33.832},
	{1,	10,	2011,	-33.878},
	{1,	1,	2012,	-33.923},
	{1,	4,	2012,	-33.969},
	{1,	7,	2012,	-34.014},
	{1,	10,	2012,	-34.059},
	{1,	1,	2013,	-34.105},
	{1,	4,	2013,	-34.150},
	{1,	7,	2013,	-34.195},
	{1,	10,	2013,	-34.240},
	{1,	1,	2014,	-34.286},
	{1,	4,	2014,	-34.331},
	{1,	7,	2014,	-34.376},
	{1,	10,	2014,	-34.421},
	{1,	1,	2015,	-34.467},
	{1,	4,	2015,	-34.512},
	{1,	7,	2015,	-34.557},
	{1,	10,	2015,	-34.602},
	{1,	1,	2016,	-34.648},
	{1,	4,	2016,	-34.693},
	{1,	7,	2016,	-34.738},
	{1,	10,	2016,	-34.784},
	{1,	1,	2017,	-34.829},
	{1,	4,	2017,	-34.874},
	{1,	7,	2017,	-34.919},
	{1,	10,	2017,	-34.965},
	{1,	1,	2018,	-35.010},
	{1,	4,	2018,	-35.055},
	{1,	7,	2018,	-35.100},
	{1,	10,	2018,	-35.146},
	{1,	1,	2019,	-35.191},
	{1,	4,	2019,	-35.236},
	{1,	7,	2019,	-35.281},
	{1,	10,	2019,	-35.327},
	{1,	1,	2020,	-35.372}
};



/* Terme pour le calcul de la Nutation en obliquite
*/
static double TNutation[] = {
	0,	0,	0,	0,	1.0,	-171996.0,	-174.2,	92025.0,	8.9,
	-2.0,	0,	0,	2.0,	2.0,	-13187.0,	-1.6,	5736.0,		-3.1,
	0,	0,	0,	2.0,	2.0,	-2274.0,	-0.2,	977.0,		-0.5,
	0,	0,	0,	0,	2.0,	2062.0,		0.2,	-895.0,		0.5,
	0,	1.0,	0,	0,	0,	1426.0,		-3.4,	54.0,		-0.1,
	0,	0,	1.0,	0,	0,	712.0,		0.1,	-7.0,		0,
	-2.0,	1.0,	0,	2.0,	2.0,	-517.0,		1.2,	224.0,		-0.6,
	0,	0,	0,	2.0,	1.0,	-386.0,		-0.4,	200.0,		0,
	0,	0,	1.0,	2.0,	2.0,	-301.0,		0,	129.0,		-0.1,
	-2.0,	-1.0,	0,	2.0,	2.0,	217.0,		-0.5,	-95.0,		0.3,
	-2.0,	0,	1.0,	0,	0,	-158.0,		0,	0,		0,
	-2.0,	0,	0,	2.0,	1.0,	129.0,		0.1,	-70.0,		0,
	0,	0,	-1.0,	2.0,	2.0,	123.0,		0,	-53.0,		0,
	2.0,	0,	0,	0,	0,	63.0,		0,	0,		0,
	0,	0,	1.0,	0,	1.0,	63.0,		0.1,	-33.0,		0,
	2.0,	0,	-1.0,	2.0,	2.0,	-59.0,		0,	26.0,		0,
	0,	0,	-1.0,	0,	1.0,	-58.0,		-0.1,	32.0,		0,
	0,	0,	1.0,	2.0,	1.0,	-51.0,		0,	27.0,		0,
	-2.0,	0,	2.0,	0,	0,	48.0,		0,	0,		0,
	0,	0,	-2.0,	2.0,	1.0,	46.0,		0,	-24.0,		0,
	2.0,	0,	0,	2.0,	2.0,	-38.0,		0,	16.0,		0,
	0,	0,	2.0,	2.0,	2.0,	-31.0,		0,	13.0,		0,
	0,	0,	2.0,	0,	0,	29.0,		0,	0,		0,
	-2.0,	0,	1.0,	2.0,	2.0,	29.0,		0,	-12.0,		0,
	0,	0,	0,	2.0,	0,	26.0,		0,	0,		0,
	-2.0,	0,	0,	2.0,	0,	-22.0,		0,	0,		0,
	0,	0,	-1.0,	2.0,	1.0,	21.0,		0,	-10.0,		0,
	0,	2.0,	0,	0,	0,	17.0,		-0.1,	0,		0,
	2.0,	0,	-1.0,	0,	1.0,	16.0,		0,	-8.0,		0,
	-2.0,	2.0,	0,	2.0,	2.0,	-16.0,		0.1,	7.0,		0,
	0,	1.0,	0,	0,	1.0,	-15.0,		0,	9.0,		0,
	-2.0,	0,	1.0,	0,	1.0,	-13.0,		0,	7.0,		0,
	0,	-1.0,	0,	0,	1.0,	-12.0,		0,	6.0,		0,
	0,	0,	2.0,	-2.0,	0,	11.0,		0,	0,		0,
	2.0,	0,	-1.0,	2.0,	1.0,	-10.0,		0,	5.0,		0,
	2.0,	0,	1.0,	2.0,	2.0,	-8.0,		0,	3.0,		0,
	0,	1.0,	0,	2.0,	2.0,	7.0,		0,	-3.0,		0,
	-2.0,	1.0,	1.0,	0,	0,	-7.0,		0,	0,		0,
	0,	-1.0,	0,	2.0,	2.0,	-7.0,		0,	3.0,		0,
	2.0,	0,	0,	2.0,	1.0,	-7.0,		0,	3.0,		0,
	2.0,	0,	1.0,	0,	0,	6.0,		0,	0,		0,
	-2.0,	0,	2.0,	2.0,	2.0,	6.0,		0,	-3.0,		0,
	-2.0,	0,	1.0,	2.0,	1.0,	6.0,		0,	-3.0,		0,
	2.0,	0,	-2.0,	0,	1.0,	-6.0,		0,	3.0,		0,
	2.0,	0,	0,	0,	1.0,	-6.0,		0,	3.0,		0,
	0,	-1.0,	1.0,	0,	0,	5.0,		0,	0,		0,
	-2.0,	-1.0,	0,	2.0,	1.0,	-5.0,		0,	3.0,		0,
	-2.0,	0,	0,	0,	1.0,	-5.0,		0,	3.0,		0,
	0,	0,	2.0,	2.0,	1.0,	-5.0,		0,	3.0,		0,
	-2.0,	0,	2.0,	0,	1.0,	4.0,		0,	0,		0,
	-2.0,	1.0,	0,	2.0,	1.0,	4.0,		0,	0,		0,
	0,	0,	1.0,	-2.0,	0,	4.0,		0,	0,		0,
	-1.0,	0,	1.0,	0,	0,	-4.0,		0,	0,		0,
	-2.0,	1.0,	0,	0,	0,	-4.0,		0,	0,		0,
	1.0,	0,	0,	0,	0,	-4.0,		0,	0,		0,
	0,	0,	1.0,	2.0,	0,	3.0,		0,	0,		0,
	0,	0,	-2.0,	2.0,	2.0,	-3.0,		0,	0,		0,
	-1.0,	-1.0,	1.0,	0,	0,	-3.0,		0,	0,		0,
	0,	1.0,	1.0,	0,	0,	-3.0,		0,	0,		0,
	0,	-1.0,	1.0,	2.0,	2.0,	-3.0,		0,	0,		0,
	2.0,	-1.0,	-1.0,	2.0,	2.0,	-3.0,		0,	0,		0,
	0,	0,	3.0,	2.0,	2.0,	-3.0,		0,	0,		0,
	2.0,	-1.0,	0,	2.0,	2.0,	-3.0,		0,	0,		0
};



/* Tableau des termes periodiques les plus representatifs de la theorie VSOP87 pour le calcul des coordonnees
    heliocentriques de la Terre. Il s'agit directement des coordonnees ecliptiques en radians pour l'equinoxe
    moyen de la date et l'ecliptique dynamique moyen.
*/

/* Termes pour le calcul de la longitude ecliptique heliocentrique de la Terre
*/
static double L0_Terre[] = {
	175347046.0,0,0,
	3341656.0,4.6692568,6283.0758500,
	34894.0,4.62610,12566.15170,
	3497.0,2.7441,5753.3849,
	3418.0,2.8289,3.5231,
	3136.0,3.6277,77713.7715,
	2676.0,4.4181,7860.4194,
	2343.0,6.1352,3930.2097,
	1324.0,0.7425,11506.7698,
	1273.0,2.0371,529.6910,
	1199.0,1.1096,1577.3435,
	990.0,5.233,5884.927,
	902.0,2.045,26.298,
	857.0,3.508,398.149,
	780.0,1.179,5223.694,
	753.0,2.533,5507.553,
	505.0,4.583,18849.228,
	492.0,4.205,775.523,
	357.0,2.920,0.067,
	317.0,5.849,11790.629,
	284.0,1.899,796.298,
	271.0,0.315,10977.079,
	243.0,0.345,5486.778,
	206.0,4.806,2544.314,
	205.0,1.869,5573.143,
	202.0,2.458,6069.777,
	156.0,0.833,213.299,
	132.0,3.411,2942.463,
	126.0,1.083,20.775,
	115.0,0.645,0.980,
	103.0,0.636,4694.003,
	102.0,0.976,15720.839,
	102.0,4.267,7.114,
	99.0,6.21,2146.17,
	98.0,0.68,155.42,
	86.0,5.98,161000.69,
	85.0,1.30,6275.96,
	85.0,3.67,71430.70,
	80.0,1.81,17260.15,
	79.0,3.04,12036.46,
	75.0,1.76,5088.63,
	74.0,3.50,3154.69,
	74.0,4.68,801.82,
	70.0,0.83,9437.76,
	62.0,3.98,8827.39,
	61.0,1.82,7084.90,
	57.0,2.78,6286.60,
	56.0,4.39,14143.50,
	56.0,3.47,6279.55,
	52.0,0.19,12139.55,
	52.0,1.33,1748.02,
	51.0,0.28,5856.48,
	49.0,0.49,1194.45,
	41.0,5.37,8429.24,
	41.0,2.40,19651.05,
	39.0,6.17,10447.39,
	37.0,6.04,10213.29,
	37.0,2.57,1059.38,
	36.0,1.71,2352.87,
	36.0,1.78,6812.77,
	33.0,0.59,17789.85,
	30.0,0.44,83996.85,
	30.0,2.74,1349.87,
	25.0,3.16,4690.48
};

static double L1_Terre[] = {
	628331966747.0,0,0,
	206059.0,2.678235,6283.075850,
	4303.0,2.6351,12566.1517,
	425.0,1.590,3.523,
	119.0,5.796,26.298,
	109.0,2.966,1577.344,
	93.0,2.59,18849.23,
	72.0,1.14,529.69,
	68.0,1.87,398.15,
	67.0,4.41,5507.55,
	59.0,2.89,5223.69,
	56.0,2.17,155.42,
	45.0,0.40,796.30,
	36.0,0.47,775.52,
	29.0,2.65,7.11,
	21.0,5.34,0.98,
	19.0,1.85,5486.78,
	19.0,4.97,213.30,
	17.0,2.99,6275.96,
	16.0,0.03,2544.31,
	16.0,1.43,2146.17,
	15.0,1.21,10977.08,
	12.0,2.83,1748.02,
	12.0,3.26,5088.63,
	12.0,5.27,1194.45,
	12.0,2.08,4694.00,
	11.0,0.77,553.57,
	10.0,1.30,6286.60,
	10.0,4.24,1349.87,
	9.0,2.70,242.73,
	9.0,5.64,951.72,
	8.0,5.30,2352.87,
	6.0,2.65,9437.76,
	6.0,4.67,4690.48
};

static double L2_Terre[] = {
	52919.0,0,0,
	8720.0,1.0721,6283.0758,
	309.0,0.867,12566.152,
	27.0,0.05,3.52,
	16.0,5.19,26.30,
	16.0,3.68,155.42,
	10.0,0.76,18849.23,
	9.0,2.06,77713.77,
	7.0,0.83,775.52,
	5.0,4.66,1577.34,
	4.0,1.03,7.11,
	4.0,3.44,5573.14,
	3.0,5.14,796.30,
	3.0,6.05,5507.55,
	3.0,1.19,242.73,
	3.0,6.12,529.69,
	3.0,0.31,398.15,
	3.0,2.28,553.57,
	2.0,4.38,5223.69,
	2.0,3.75,0.98
};

static double L3_Terre[] = {
	289.0,5.844,6283.076,
	35.0,0,0,
	17.0,5.49,12566.15,
	3.0,5.20,155.42,
	1.0,4.72,3.52,
	1.0,5.30,18849.23,
	1.0,5.97,242.73
};

static double L4_Terre[] = {
	114.0,3.142,0,
	8.0,4.13,6283.08,
	1.0,3.84,12566.15
};

static double L5_Terre[] = {
	1.0,3.14,0
};


/* Termes pour le calcul de la latitude ecliptique heliocentrique de la Terre
*/
static double B0_Terre[] = {
	280.0,3.199,84334.662,
	102.0,5.422,5507.553,
	80.0,3.88,5223.69,
	44.0,3.70,2352.87,
	32.0,4.00,1577.34
};

static double B1_Terre[] = {
	9.0,3.90,5507.55,
	6.0,1.73,5223.69
};


/* Termes pour le calcul du rayon vecteur de la Terre
*/
static double R0_Terre[] = {
	100013989.0,0,0,
	1670700.0,3.0984635,6283.0758500,
	13956.0,3.05525,12566.15170,
	3084.0,5.1985,77713.7715,
	1628.0,1.1739,5753.3849,
	1576.0,2.8469,7860.4194,
	925.0,5.453,11506.770,
	542.0,4.564,3930.210,
	472.0,3.661,5884.927,
	346.0,0.964,5507.553,
	329.0,5.900,5223.694,
	307.0,0.299,5573.143,
	243.0,4.273,11790.629,
	212.0,5.847,1577.344,
	186.0,5.022,10977.079,
	175.0,3.012,18849.228,
	110.0,5.055,5486.778,
	98.0,0.89,6069.78,
	86.0,5.69,15720.84,
	86.0,1.27,161000.69,
	65.0,0.27,17260.15,
	63.0,0.92,529.69,
	57.0,2.01,83996.85,
	56.0,5.24,71430.70,
	49.0,3.25,2544.31,
	47.0,2.58,775.52,
	45.0,5.54,9437.76,
	43.0,6.01,6275.96,
	39.0,5.36,4694.00,
	38.0,2.39,8827.39,
	37.0,0.83,19651.05,
	37.0,4.90,12139.55,
	36.0,1.67,12036.46,
	35.0,1.84,2942.46,
	33.0,0.24,7084.90,
	32.0,0.18,5088.63,
	32.0,1.78,398.15,
	28.0,1.21,6286.60,
	28.0,1.90,6279.55,
	26.0,4.59,10447.39
};

static double R1_Terre[] = {
	103019.0,1.107490,6283.075850,
	1721.0,1.0644,12566.1517,
	702.0,3.142,0,
	32.0,1.02,18849.23,
	31.0,2.84,5507.55,
	25.0,1.32,5223.69,
	18.0,1.42,1577.34,
	10.0,5.91,10977.08,
	9.0,1.42,6275.96,
	9.0,0.27,5486.78
};

static double R2_Terre[] = {
	4359.0,5.7846,6283.0758,
	124.0,5.579,12566.152,
	12.0,3.14,0,
	9.0,3.63,77713.77,
	6.0,1.87,5573.14,
	3.0,5.47,18849.23
};

static double R3_Terre[] = {
	145.0,4.273,6283.076,
	7.0,3.92,12566.15
};

static double R4_Terre[] = {
	4.0,2.56,6283.08
};



// FONCTION DE CALCUL DU JOUR JULIEN DE LA DATE A ZERO HEURE
//
// L'origine du jour julien est le 01/01/-4712 et dure 7980 ans.
// Il tient compte de la reforme Gregorienne du 4/10/1582 qui supprime trois jours tous les 400 ans a partir de 1583
//
// CE:	On passe le jour, le mois, l'annee dans des int
//
// CS:	La fonction retourne un double

double CalculsAstronomiques::JJ(int jo,int mo,int an)
{
	double jd=0.0;
	double c1;
	double c2;
	double c3;
	double c4;

	// Calcul des constantes
	//
	c1=( mo < 3 ) ? ((double) an)-1.0 : (double) an;
	c2=( mo < 3 ) ? ((double) mo)+12.0 : (double) mo;
	c3=c1+c2/100.0+((double) jo)/10000.0;
	c4=PENT(c1/100.0);

	// Calcul du jour julien a zero heure
	//
	jd+=PENT(365.25*c1);
	jd+=PENT(30.6001*(c2+1.0));
	jd+=(double) jo;
	jd+=1720994.5;
	if( c3 > 1582.1014 ) jd+=2.0-c4+PENT(c4/4.0);

	return(jd);
}


// Fonction de calcul de la difference de temps UT1-TAI (temps base sur la rotation de la Terre-temps atomique international)
//
// CE:	On passe le jour julien entre le 01/01/1990 et le 01/01/2020 ;
//
// CS: La fonction retourne UT1-TAI ;
//
double CalculsAstronomiques::UT1mTAI_1990_2020(double jj)
{
	int i;				/* Indice de parcours du tableau des valeurs */
	double UT1mTAI=0;	/* Valeur de UT1mTAI                         */

	/* Si jj n'est pas dans la periode 01/01/1990 au 01/01/2020 alors on retourne la valeur nulle
	*/
	if( jj < 2447892.5 || jj > 2458849.5 ) return 0;

	/* On recherche l'interval des valeurs echantillons ou jj se trouve
	*/
	for( i=0; i < NbValeursUT1mTAIPeriode1990_2020-1; i++ )
	{
		double jji;		/* Jour julien pour l'indice i   */
		double jjip;	/* Jour julien pour l'indice i+1 */

		/* Jour julien a i
		*/
		jji=JJ(TableauUT1mTAI[i].jour,TableauUT1mTAI[i].mois,TableauUT1mTAI[i].annee);

		/* Jour julien a i+1
		*/
		jjip=JJ(TableauUT1mTAI[i+1].jour,TableauUT1mTAI[i+1].mois,TableauUT1mTAI[i+1].annee);

		/* Si jj est dans la periode jji et jjip
		*/
		if( jj >= jji && jj <= jjip )
		{
			UT1mTAI=(jj-jji)*(TableauUT1mTAI[i+1].valeur-TableauUT1mTAI[i].valeur)/(jjip-jji);
			UT1mTAI+=TableauUT1mTAI[i].valeur;
		}
	}

	return UT1mTAI;
}


// FONCTION PARTIE ENTIERE PENT
//
// CE:	On passe la valeur ;
//
// CS:	La partie entiere est retournee ;
//
double CalculsAstronomiques::PENT(double x)
{
	modf(x,&x);
	return( x );
}


// FONCTION MODULO DEUX PI
//
// CE:	On passe la valeur ;
//
// CS:	La valeur modulo 2 pi est retournee ;
//
double CalculsAstronomiques::Modulo_2PI(double x)
{
	double nbf;

	nbf=PENT(x/(2.0*M_PI));

	if( x < 0 )
	{
		if( nbf == 0 ) nbf=-1.0; else nbf-=1.0;
	}

	nbf=x-nbf*2.0*M_PI;

	return(nbf);
}


// FONCTION DE CALCUL DE LA NUTATION ET DE L'OBLIQUITE DE L'ECLIPTIQUE
//
// CE:	On passe le jour julien des ephemerides (ATTENTION : JJ+DeltaT pour le temps dynamique) ;
//
//		On passe un pointeur sur double qui contiendra la nutation en longitude en radians ;
//
//		On passe un pointeur sur double qui contiendra la nutation en obliquite en radians ;
//
//		On passe un pointeur sur double qui contiendra l'obliquite de l'ecliptique sur l'equateur en radians ;
//
// CS:	La valeur des pointeurs est initialisee ;
//
void CalculsAstronomiques::CalculNutationObliquite(double jde,double *nl,double *no,double *epsilon)
{
	unsigned long i;	/* Indice dans tableau      */
	double T;			/* Variables pour le calcul */
	double T2;
	double T3;
	double D;
	double M;
	double Mp;
	double F;
	double Om;
	double U;
	double DegRad=M_PI/180.0;


	/* Temps ecoule depuis J2000 en siecle julien
	*/
	T=(jde-2451545.0)/36525.0;
	T2=T*T;
	T3=T2*T;

	/* Elongation moyenne de la Lune au soleil
	*/
	D=297.85036+445267.111480*T-0.0019142*T2+T3/189474.0;
	D*=DegRad;

	/* Anomalie moyenne du Soleil
	*/
	M=357.52772+35999.050340*T-0.0001603*T2-T3/300000.0;
	M*=DegRad;

	/* Anomalie moyenne de la Lune
	*/
	Mp=134.96298+477198.867398*T+0.0086972*T2+T3/56250.0;
	Mp*=DegRad;

	/* Argument de la latitude de la Lune
	*/
	F=93.27191+483202.017538*T-0.0036825*T2+T3/327270.0;
	F*=DegRad;

	/* Longitude du noeud ascendant de l'orbite moyenne de la Lune sur l'ecliptique mesuree depuis l'equinoxe
	    moyen de la date
	*/
	Om=125.04452-1934.136261*T+0.0020708*T2+T3/450000.0;
	Om*=DegRad;


	/* Calcul de la nutation en longitude et en obliquite
	*/
	*nl=*no=0;

	for( i=0; i < 63; i++ )
	{
		unsigned long offset;	/* Offset dans le tableau TNutation */

		offset=i*9;

		/* Calcul de la nutation en longitude
		*/
		*nl+=(TNutation[offset+5]+TNutation[offset+6]*T)*sin(TNutation[offset]*D+TNutation[offset+1]*M+TNutation[offset+2]*Mp+TNutation[offset+3]*F+TNutation[offset+4]*Om);
		
		/* Calcul de la nutation en obliquite
		*/
		*no+=(TNutation[offset+7]+TNutation[offset+8]*T)*cos(TNutation[offset]*D+TNutation[offset+1]*M+TNutation[offset+2]*Mp+TNutation[offset+3]*F+TNutation[offset+4]*Om);
	}

	*nl/=10000.0;
	*no/=10000.0;
	*nl/=3600.0;
	*no/=3600.0;
	*nl*=DegRad;
	*no*=DegRad;


	/* Obliquite de l'ecliptique
	*/
	U=T/100.0;

	*epsilon=23.0+26.0/60.0+21.448/3600.0-4680.93*U/3600.0-1.55*pow(U,2.0)/3600.0+1999.25*pow(U,3.0)/3600.0-51.38*pow(U,4.0)/3600.0-249.67*pow(U,5.0)/3600.0-39.05*pow(U,6.0)/3600.0+7.12*pow(U,7.0)/3600.0+27.87*pow(U,8.0)/3600.0+5.79*pow(U,9.0)/3600.0+2.45*pow(U,10.0)/3600.0;
	*epsilon*=DegRad;
}


// FONCTION DE CALCUL DES COORDONNEES HELIOGRAPHIQUES ET DE L'ANGLE AU POLE DU SOLEIL
//
// CE:	On passe le jour julien et sa fraction ;
//
//		On passe un pointeur sur double qui contiendra l'angle au pole de l'extremite Nord du Soleil en radians ;
//
//		On passe un pointeur sur double qui contiendra la longitude heliographique du centre du disque solaire en radians ;
//
//		On passe un pointeur sur double qui contiendra la latitude heliographique du centre du disque solaire en radians ;
//
//	CS:	La valeur des pointeurs est initialisee ;
//
void CalculsAstronomiques::CoordonneesHeliographiquesCentreDisqueSolaire(double jj,double *P,double *Lo,double *Bo)
{
	double Dt;			// Variables pour le calcul
	double Theta;
	double I;
	double K;
	double T;
	double Lterre;
	double Bterre;
	double Rterre;
	double NutationL;
	double NutationO;
	double Epsilon;
	double Aberration;
	double LappS;
	double LappSn;
	double x;
	double y;
	double DegRad=M_PI/180.0;


	/* Calcul de l'ecart entre le temps civil et le temps dynamique (des ephemerides) base sur le mouvement
	    des planetes et corrigeant des effets de l'irregularite de la vitesse de rotation de la Terre sur
	    elle meme, pour les ephemerides physiques.
	*/
	if( jj >= 2447892.5  && jj <= 2458849.5 )
	{
		/* Pour la periode du 01/01/1990 au 01/01/2020 on utilise la fonction UT1mTAI_1990_2020()
		    a laquelle on ajoute 32.184s (difference de temps entre le TT temps terrestre et le
		    temps atomique international). En toute rigueure il faudrait ajouter UT1-UTC, la
		    difference de temps entre le temps universel et le temps universel coordonne. Cette
		    valeur est toujours inferieure a 0,9s en valeur absolue. Donc ici on la neglige.
		    Ces valeurs sont recuperables sur le site de l'observatoire de Paris :
		    http://hpiers.obspm.fr/eop-pc/products/combined/C04.html
		*/
		Dt=32.184-UT1mTAI_1990_2020(jj);
	}
	else
	{
		/* ATTENTION : CETTE FORMULE EST TRES APPROCHEE. LA PRECISION N'EST PAS BONNE.
		*/
		Dt=-15.0+pow(jj-2382148.0,2.0)/41048480.0;
	}
	Dt/=86400.0;	/* de seconde en fraction de jour */


	/* Correction du jour julien en temps civil vers le jour julien en temps dynamique
	*/
	jj+=Dt;

	/* Longitude du meridien origine du Soleil
	*/
	Theta=(jj-2398220.0)*360.0/25.38;
	Theta*=DegRad;

	/* Inclinaison de l'equateur solaire sur l'ecliptique
	*/
	I=7.25*DegRad;

	/* Longitude du noeud ascendant de l'equateur solaire sur l'ecliptique
	*/
	K=73.6667+1.3958333*(jj-2396758.0)/36525.0;
	K*=DegRad;

	/* Temps en siecles juliens depuis J2000.0
	*/
	T=(jj-2451545.0)/36525.0;

	/* Calcul des coordonnees ecliptiques heliocentriques de la Terre
	*/
	CalculCoordonneesEcliptiquesHeliocentriquesTerreVSOP87(jj,&Lterre,&Bterre,&Rterre);

	/* Calcul de la nutation et de l'obliquite de l'ecliptique
	*/
	CalculNutationObliquite(jj,&NutationL,&NutationO,&Epsilon);

	/* On ajoute la nutation en obliquite a l'obliquite
	*/
	Epsilon+=NutationO;

	/* Calcul de l'aberration
	*/
	Aberration=-20.4898/3600.0/Rterre;
	Aberration*=DegRad;

	/* Calcul de la longitude apparente du Soleil (incluant l'effet de l'aberration mais pas la nutation)
	*/
	LappS=Lterre+M_PI+Aberration;

	/* Calcul de la longitude apparente du Soleil incluant l'effet de la nutation
	*/
	LappSn=LappS+NutationL;

	/* Calcul de l'angle au pole
	*/
	y=atan(-cos(LappS-K)*tan(I));
	x=atan(-cos(LappSn)*tan(Epsilon));
	*P=Modulo_2PI(x+y);

	/* Calcul de la latitude Heliographique
	*/
	*Bo=asin(sin(LappS-K)*sin(I));

	/* Calcul de la longitude heliographique du centre du disque solaire
	*/
	*Lo=atan2(-sin(LappS-K)*cos(I),-cos(LappS-K));
	*Lo-=Theta;
	*Lo=Modulo_2PI(*Lo);
}


// FONCTION DE CALCUL DES COORDONNEES ECLIPTIQUES HELIOCENTRIQUES DE LA TERRE PAR VSOP87
//
// CE:	On passe le jour julien et sa fraction ;
//
// 		On passe un pointeur sur double qui contiendra la longitude ecliptique heliocentrique pour
//		 l'ecliptique dynamique et l'equinoxe moyen de la date en radians ;
//
//		On passe un pointeur sur double qui contiendra la latitude ecliptique heliocentrique pour
//		 l'ecliptique dynamique et l'equinoxe moyen de la date en radians ;
//
//		On passe un pointeur sur double qui contiendra le rayon vecteur en UA ;
//
// CS:	Les valeurs des pointeurs sont initialises ;
//
void CalculsAstronomiques::CalculCoordonneesEcliptiquesHeliocentriquesTerreVSOP87(double jj,double *L,double *B,double *R)
{
	int i;						/* Variable indice              */
	double tau;					/* Temps ecoule                 */
	double L0,L1,L2,L3,L4,L5;	/* Termes pour la longitude     */
	double B0,B1;				/* Termes pour la latitude      */
	double R0,R1,R2,R3,R4;		/* Termes pour la rayon vecteur */


	/* Calcul du temps ecoule depuis J2000 en millenaires juliens
	*/
	tau=(jj-2451545.0)/365250.0;


	/* Calcul des termes pour la longitude
	*/
	L0=0;
	for( i=0; i < 64; i++ ) L0+=L0_Terre[i*3]*cos(L0_Terre[i*3+1]+L0_Terre[i*3+2]*tau);

	L1=0;
	for( i=0; i < 34; i++ ) L1+=L1_Terre[i*3]*cos(L1_Terre[i*3+1]+L1_Terre[i*3+2]*tau);

	L2=0;
	for( i=0; i < 20; i++ ) L2+=L2_Terre[i*3]*cos(L2_Terre[i*3+1]+L2_Terre[i*3+2]*tau);

	L3=0;
	for( i=0; i < 7; i++ ) L3+=L3_Terre[i*3]*cos(L3_Terre[i*3+1]+L3_Terre[i*3+2]*tau);

	L4=0;
	for( i=0; i < 3; i++ ) L4+=L4_Terre[i*3]*cos(L4_Terre[i*3+1]+L4_Terre[i*3+2]*tau);

	L5=0;
	for( i=0; i < 1; i++ ) L5+=L5_Terre[i*3]*cos(L5_Terre[i*3+1]+L5_Terre[i*3+2]*tau);

	*L=(L0+L1*tau+L2*tau*tau+L3*tau*tau*tau+L4*tau*tau*tau*tau+L5*tau*tau*tau*tau*tau)/100000000.0;


	/* Calcul des termes pour la latitude
	*/
	B0=0;
	for( i=0; i < 5; i++ ) B0+=B0_Terre[i*3]*cos(B0_Terre[i*3+1]+B0_Terre[i*3+2]*tau);

	B1=0;
	for( i=0; i < 2; i++ ) B1+=B1_Terre[i*3]*cos(B1_Terre[i*3+1]+B1_Terre[i*3+2]*tau);

	*B=(B0+B1*tau)/100000000.0;


	/* Calcul des termes pour le rayon vecteur
	*/
	R0=0;
	for( i=0; i < 40; i++ ) R0+=R0_Terre[i*3]*cos(R0_Terre[i*3+1]+R0_Terre[i*3+2]*tau);

	R1=0;
	for( i=0; i < 10; i++ ) R1+=R1_Terre[i*3]*cos(R1_Terre[i*3+1]+R1_Terre[i*3+2]*tau);

	R2=0;
	for( i=0; i < 6; i++ ) R2+=R2_Terre[i*3]*cos(R2_Terre[i*3+1]+R2_Terre[i*3+2]*tau);

	R3=0;
	for( i=0; i < 2; i++ ) R3+=R3_Terre[i*3]*cos(R3_Terre[i*3+1]+R3_Terre[i*3+2]*tau);

	R4=0;
	for( i=0; i < 1; i++ ) R4+=R4_Terre[i*3]*cos(R4_Terre[i*3+1]+R4_Terre[i*3+2]*tau);

	*R=(R0+R1*tau+R2*tau*tau+R3*tau*tau*tau+R4*tau*tau*tau*tau)/100000000.0;
}


