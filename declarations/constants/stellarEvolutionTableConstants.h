#ifndef STELLAREVOLUTIONTABLECONSTANTS
#define STELLAREVOLUTIONTABLECONSTANTS

/*  Stellar evolution
	This is an array with each row corresponding to a star's mass, and holds a main sequence star'
		Mass (in solar masses
		Type (corresponds to stellarTypeTable)
		Temperature (most likely effective temperature in kelvins)
		L-Min (minimum luminosity)
		L-Max (maximum luminosity)
		M-Span (main sequence span in billions of years)
		S-Span (subgiant span in billions of years)
		G-Span (giant span in billions of years)
*/

const int STELLEREVOLUTIONTABLE_MAXROWS = 34;
const int STELLEREVOLUTIONTABLE_MAXCOLS = 8;

const float stellarEvolutionTable[STELLEREVOLUTIONTABLE_MAXROWS][STELLEREVOLUTIONTABLE_MAXCOLS] =
{
//	Mass	|	Type	|	Temp	|	L-Min	|	L-Max	|	M-Span	|	S-Span	|	G-Span
	0.10	,	0		,	3100	,	0.0012	,	0		,	0		,	0		,	0		,
	0.15	,	1		,	3200	,	0.0036	,	0		,	0		,	0		,	0		,
	0.20	,	2		,	3200	,	0.0079	,	0		,	0		,	0		,	0		,
	0.25	,	3		,	3300	,	0.015	,	0		,	0		,	0		,	0		,
	0.30	,	4		,	3300	,	0.024	,	0		,	0		,	0		,	0		,
	0.35	,	5		,	3400	,	0.037	,	0		,	0		,	0		,	0		,
	0.40	,	6		,	3500	,	0.054	,	0		,	0		,	0		,	0		,
	0.45	,	7		,	3600	,	0.07	,	0.08	,	70		,	0		,	0		,
	0.50	,	8		,	3800	,	0.09	,	0.11	,	59		,	0		,	0		,
	0.55	,	9		,	4000	,	0.11	,	0.15	,	50		,	0		,	0		,
	0.60	,	10		,	4200	,	0.13	,	0.20	,	42		,	0		,	0		,
	0.65	,	11		,	4400	,	0.15	,	0.25	,	37		,	0		,	0		,
	0.70	,	12		,	4600	,	0.19	,	0.35	,	30		,	0		,	0		,
	0.75	,	13		,	4900	,	0.23	,	0.48	,	24		,	0		,	0		,
	0.80	,	14		,	5200	,	0.28	,	0.65	,	20		,	0		,	0		,
	0.85	,	15		,	5400	,	0.36	,	0.84	,	17		,	0		,	0		,
	0.90	,	16		,	5500	,	0.45	,	1.00	,	14		,	0		,	0		,
	0.95	,	17		,	5700	,	0.56	,	1.30	,	12		,	1.8		,	1.1		,
	1.00	,	18		,	5800	,	0.68	,	1.60	,	10		,	1.6		,	1		,
	1.05	,	19		,	5900	,	0.87	,	1.90	,	8.8		,	1.4		,	0.8		,
	1.10	,	20		,	6000	,	1.10	,	2.20	,	7.7		,	1.2		,	0.7		,
	1.15	,	21		,	6100	,	1.40	,	2.60	,	6.7		,	1		,	0.6		,
	1.20	,	22		,	6300	,	1.70	,	3.00	,	5.9		,	0.9		,	0.6		,
	1.25	,	23		,	6400	,	2.10	,	3.50	,	5.2		,	0.8		,	0.5		,
	1.30	,	24		,	6500	,	2.50	,	3.90	,	4.6		,	0.7		,	0.4		,
	1.35	,	25		,	6600	,	3.10	,	4.50	,	4.1		,	0.6		,	0.4		,
	1.40	,	26		,	6700	,	3.70	,	5.10	,	3.7		,	0.6		,	0.4		,
	1.45	,	27		,	6900	,	4.30	,	5.70	,	3.3		,	0.5		,	0.3		,
	1.50	,	28		,	7000	,	5.10	,	6.50	,	3		,	0.5		,	0.3		,
	1.60	,	29		,	7300	,	6.70	,	8.20	,	2.5		,	0.4		,	0.2		,
	1.70	,	30		,	7500	,	8.60	,	10.0	,	2.1		,	0.3		,	0.2		,
	1.80	,	31		,	7800	,	11.0	,	13.0	,	1.8		,	0.3		,	0.2		,
	1.90	,	32		,	8000	,	13.0	,	16.0	,	1.5		,	0.2		,	0.1		,
	2.00	,	33		,	8200	,	16.0	,	20.0	,	1.3		,	0.2		,	0.1
};

#endif
