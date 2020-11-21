//	This function returns the star's current stellar luminosity

//#include "stellarEvolutionTable.h"
//	Constant declarations
#include "declarations/constants/luminosityClassConstants.h"

//	Function declarations
#include "declarations/functions/floatRNG.h"

//	Struct declarations
#include "declarations/structures/world_t.h"
#include "declarations/structures/star_t.h"

star_t calculateStellarLuminosity(star_t primary)
{
	float variance = floatRNG(-0.1, 0.1);
	float currentLuminosity = primary.lMin + ((primary.stellarAge / primary.mSpan) * (primary.lMax - primary.lMin));

//	If the star is a giant
	if (primary.luminosityClass == LC_III)
	{
		currentLuminosity *= 25;
		variance *= currentLuminosity;
		primary.stellarLuminosity = currentLuminosity;
	}

//	If the star is a white dwarf
	else if (primary.luminosityClass == LC_D)
	{
		currentLuminosity = 0.01;
		variance *= currentLuminosity;
		primary.stellarLuminosity = currentLuminosity + variance;
	}

//	If it is a subgiant
	else if (primary.luminosityClass == LC_IV)
	{
		primary.stellarLuminosity = primary.lMax + (variance * primary.lMax);
	}

//	If it is on the main sequence
	else
	{
		variance *= currentLuminosity;
		primary.stellarLuminosity = currentLuminosity;
	}

	return primary;
}
