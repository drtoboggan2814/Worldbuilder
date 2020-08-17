//	This function returns the star's current stellar luminosity


//#include "stellarEvolutionTable.h"
//	Constant declarations
#include "declarations/constants/luminosityClassConstants.h"

//	Function declarations
#include "declarations/functions/floatRNG.h"
#include "declarations/functions/diceRoller.h"

//	Structure declarations
#include "declarations/structures/world_t.h"
#include "declarations/structures/star_t.h"

star_t calculateStellarTemperature(star_t primary)
{
	float variance = floatRNG(-100, 100);
	int firstRoll;
	float currentTemperature;

//	If the star is a giant
	if (primary.luminosityClass == LC_III)
	{
		firstRoll = diceRoller(6, 2);
		currentTemperature = ( 2 * (firstRoll - 2)) + 3000;
		primary.stellarTemperature = currentTemperature + variance;
	}

//	If it is a subgiant
	else if (primary.luminosityClass == LC_IV)
	{
		currentTemperature = primary.stellarMass - ((primary.stellarAge / primary.sSpan) * (primary.stellarMass - 4800));
		primary.stellarTemperature = currentTemperature + variance;
	}

//	If it is on the main sequence or a white dwarf
	else
	{
		primary.stellarTemperature = primary.tableTemperature + variance;
	}

	return primary;
/*
//	If the star is a giant
	if (age > (sSpan + mSpan))
	{
		firstRoll = diceRoller(6, 2);
		currentTemperature = ( 2 * (firstRoll - 2)) + 3000;
		return currentTemperature + variance;
	}

//	If the star is a subgiant
	else if (age > mSpan && age <= (mSpan + sSpan))
	{
		currentTemperature = temperature - ((age / sSpan) * (temperature - 4800));
		return currentTemperature + variance;
	}

//	If the star is on the main sequence
	else
	{
		return temperature + variance;
	}

*/
}
