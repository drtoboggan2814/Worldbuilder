//	This function returns the star's current stellar luminosity


//#include "stellarEvolutionTable.h"
//	Constant declarations
#include "declarations/constants/luminosityClassConstants.h"

//	Function declarations
#include "declarations/functions/floatRNG.h"
#include "declarations/functions/diceRoller.h"

float calculateStellarTemperature(const char &luminosityClass, const float &stellarMass, const float &stellarAge, const float &sSpan, const float &tableTemperature)
{
//	Initialize return value
	float stellarTemperature;

	float variance = floatRNG(-100, 100);
	int firstRoll;
	float currentTemperature;

//	If the star is a giant
	if (luminosityClass == LC_III)
	{
		firstRoll = diceRoller(6, 2);
		currentTemperature = ( 2 * (firstRoll - 2)) + 3000;
		stellarTemperature = currentTemperature + variance;
	}

//	If it is a subgiant
	else if (luminosityClass == LC_IV)
	{
		currentTemperature = stellarMass - ((stellarAge / sSpan) * (stellarMass - 4800));
		stellarTemperature = currentTemperature + variance;
	}

//	If it is on the main sequence or a white dwarf
	else
	{
		stellarTemperature = tableTemperature + variance;
	}

	return stellarTemperature;
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
