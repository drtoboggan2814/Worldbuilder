//	C++ libraries
#include <tuple>

//	Constant declarations
#include "declarations/constants/atmosphericPressureCategoryConstants.h"
#include "declarations/constants/worldTypeConstants.h"

//	Structure declarations
#include "declarations/structures/atmosphericComposition_t.h"
#include "declarations/structures/world_t.h"

//	Function declarations
#include "declarations/functions/atmosphericPressureCalculator.h"
#include "declarations/functions/diceRoller.h"
#include "declarations/functions/floatRNG.h"


//	This function returns the day face modifier
float tideLockedDayFaceModifierTable(const char& pressureCategory)
{
	if 		(pressureCategory == APC_NONE || pressureCategory == APC_NONE) {return 1.20;}
	else if (pressureCategory == APC_VERY_THIN						  ) {return 1.20;}
	else if (pressureCategory == APC_THIN							  ) {return 1.16;}
	else if (pressureCategory == APC_STANDARD							  ) {return 1.12;}
	else if (pressureCategory == APC_DENSE							  ) {return 1.09;}
	else if (pressureCategory == APC_VERY_DENSE						  ) {return 1.05;}
	else 																{return 1.00;}
}

//	This function returns the night face modifier
float tideLockedNightFaceModifierTable(const char& pressureCategory)
{
	if 		(pressureCategory == APC_NONE || pressureCategory == APC_NONE) {return 0.10;}
	else if (pressureCategory == APC_VERY_THIN						  ) {return 0.10;}
	else if (pressureCategory == APC_THIN							  ) {return 0.67;}
	else if (pressureCategory == APC_STANDARD							  ) {return 0.80;}
	else if (pressureCategory == APC_DENSE							  ) {return 0.88;}
	else if (pressureCategory == APC_VERY_DENSE						  ) {return 0.95;}
	else 																{return 1.00;}
}

//	The effect of tidal forces on the pressure category of the atmosphere
char tideLockedFinalAtmosphereTable(const char& pressureCategory)
{
//	Initialize return value
	char pressureCategoryTemp;
	if 		(pressureCategory == APC_NONE || pressureCategory == APC_NONE) {pressureCategoryTemp = APC_NONE			;}
	else if (pressureCategory == APC_VERY_THIN						  ) {pressureCategoryTemp = APC_NONE			;}
	else if (pressureCategory == APC_THIN							  ) {pressureCategoryTemp = APC_VERY_THIN		;}
	else 																{pressureCategoryTemp = pressureCategory;}
	return pressureCategoryTemp;
}

//	This function acts as a lookup table for the hydrographic coverage modifier
float tideLockedHydrographicCoverageModifier(const char& pressureCategory)
{
	if 		(pressureCategory == APC_NONE || pressureCategory == APC_NONE) {return -1.00;}
	else if (pressureCategory == APC_VERY_THIN						  ) {return -1.00;}
	else if (pressureCategory == APC_THIN							  ) {return -0.50;}
	else if (pressureCategory == APC_STANDARD							  ) {return -0.25;}
	else if (pressureCategory == APC_DENSE							  ) {return -0.10;}
	else if (pressureCategory == APC_VERY_DENSE						  ) {return 0.000;}
	else 																{return 0.000;}
}

//	This function takes the effects of a tidally locked world on a world's
//	atmosphere and hydrographic coverage into account
tuple<float, char, float> tideLockedWorldEffects(bool tidalLockedOrNot, float surfaceTemperature, const char& atmosphericPressureCategory, float atmosphericPressure, float atmosphereMass, float surfaceGravity, const char& worldType, float hydrographicCoverage)
{
//	Initialize return values
	float atmosphericPressureTemp = atmosphericPressure;
	float hydrographicCoverageTemp = hydrographicCoverage;
	char atmosphericPressureCategoryTemp = atmosphericPressureCategory;
//	For worlds that are tidally locked
	float dayFaceAverageTemperature = surfaceTemperature * tideLockedDayFaceModifierTable(atmosphericPressureCategoryTemp);
	float nightFaceAverageTemperature = surfaceTemperature * tideLockedNightFaceModifierTable(atmosphericPressureCategoryTemp);

	char newPressureCategory = tideLockedFinalAtmosphereTable(atmosphericPressureCategoryTemp);
//		If the pressure category is changed, update the atmospheric pressure
	if (newPressureCategory != atmosphericPressureCategoryTemp)
	{
		if 		(newPressureCategory == APC_NONE)
		{
			atmosphericPressureTemp = 0;
		}

		else if (newPressureCategory == APC_NONE)
		{
			atmosphericPressureTemp = floatRNG(0.0001, 0.0099);
		}

		else if (newPressureCategory == APC_VERY_THIN)
		{
			atmosphericPressureTemp = floatRNG(0.01, 0.5);
		}
//			Assign the new pressure category
		atmosphericPressureCategoryTemp = newPressureCategory;
	}

//		Apply the hydrographic coverage modifier
	hydrographicCoverageTemp += tideLockedHydrographicCoverageModifier(atmosphericPressureCategoryTemp);
	hydrographicCoverageTemp = (hydrographicCoverageTemp <= 0) ? 0 : hydrographicCoverageTemp;

	return make_tuple(atmosphericPressureTemp, atmosphericPressureCategoryTemp, hydrographicCoverageTemp);
}

//	This function checks to see if the world is in a stable resonant pattern,
//	rather than being tide-locked
tuple<bool, float> resonantWorldEffects(float orbitalEccentricity, bool tidalLockedOrNot, float orbitalPeriod, float apparentDayLength)
{
//	Initialize return value
	float apparentDayLengthTemp = apparentDayLength;
	bool resonantOrNot;
	if (orbitalEccentricity >= 0.1 && tidalLockedOrNot == false)
	{
		int diceRoll = diceRoller(6, 3);
		if (diceRoll < 12)
		{
			resonantOrNot = false;
			return make_tuple(resonantOrNot, apparentDayLengthTemp);
		}

		else
		{
			resonantOrNot = true;
//			The length of a day on a resonant world is twice its orbital period
			apparentDayLengthTemp = 2 * orbitalPeriod;
			return make_tuple(resonantOrNot, apparentDayLengthTemp);
		}
	}

	else
	{
		resonantOrNot = false;
		return make_tuple(resonantOrNot, apparentDayLengthTemp);
	}
}
