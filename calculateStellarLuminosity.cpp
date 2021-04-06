//	This function returns the star's current stellar luminosity

//#include "stellarEvolutionTable.h"
//	Constant declarations
#include "declarations/constants/luminosityClassConstants.h"

//	Function declarations
#include "declarations/functions/floatRNG.h"

//	Struct declarations

float calculateStellarLuminosity(char luminosityClass, float stellarAge, float mSpan, float lMax, float lMin)
{
//	Initialize return value
	float stellarLuminosity;

	float variance = floatRNG(-0.1, 0.1);
	float currentLuminosity = lMin + ((stellarAge / mSpan) * (lMax - lMin));

//	If the star is a giant
	if (luminosityClass == LC_III)
	{
		currentLuminosity *= 25;
		variance *= currentLuminosity;
		stellarLuminosity = currentLuminosity;
	}

//	If the star is a white dwarf
	else if (luminosityClass == LC_D)
	{
		currentLuminosity = 0.01;
		variance *= currentLuminosity;
		stellarLuminosity = currentLuminosity + variance;
	}

//	If it is a subgiant
	else if (luminosityClass == LC_IV)
	{
		stellarLuminosity = lMax + (variance * lMax);
	}

//	If it is on the main sequence
	else
	{
		variance *= currentLuminosity;
		stellarLuminosity = currentLuminosity;
	}

	return stellarLuminosity;
}
