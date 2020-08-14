//	C++ libraries
#include <tuple>

//	Structure declarations
#include "declarations/structures/atmosphericComposition_t.h"
#include "declarations/structures/world_t.h"

//	Function declarations
#include "declarations/functions/atmosphericPressureCalculator.h"
#include "declarations/functions/diceRoller.h"
#include "declarations/functions/floatRNG.h"

using namespace std;

//	This function returns the day face modifier
float tideLockedDayFaceModifierTable(string pressureCategory)
{
	if 		(pressureCategory == "None" || pressureCategory == "Trace") {return 1.20;}
	else if (pressureCategory == "Very Thin"						  ) {return 1.20;}
	else if (pressureCategory == "Thin"								  ) {return 1.16;}
	else if (pressureCategory == "Standard"							  ) {return 1.12;}
	else if (pressureCategory == "Dense"							  ) {return 1.09;}
	else if (pressureCategory == "Very Dense"						  ) {return 1.05;}
	else 																{return 1.00;}
}

//	This function returns the night face modifier
float tideLockedNightFaceModifierTable(string pressureCategory)
{
	if 		(pressureCategory == "None" || pressureCategory == "Trace") {return 0.10;}
	else if (pressureCategory == "Very Thin"						  ) {return 0.10;}
	else if (pressureCategory == "Thin"								  ) {return 0.67;}
	else if (pressureCategory == "Standard"							  ) {return 0.80;}
	else if (pressureCategory == "Dense"							  ) {return 0.88;}
	else if (pressureCategory == "Very Dense"						  ) {return 0.95;}
	else 																{return 1.00;}
}

//	The effect of tidal forces on the pressure category of the atmosphere
string tideLockedFinalAtmosphereTable(string pressureCategory)
{
	if 		(pressureCategory == "None" || pressureCategory == "Trace") {pressureCategory = "None"			;}
	else if (pressureCategory == "Very Thin"						  ) {pressureCategory = "Trace"			;}
	else if (pressureCategory == "Thin"								  ) {pressureCategory = "Very Thin"		;}
	else 																{pressureCategory = pressureCategory;}
	return pressureCategory;
}

//	This function acts as a lookup table for the hydrographic coverage modifier
float tideLockedHydrographicCoverageModifier(string pressureCategory)
{
	if 		(pressureCategory == "None" || pressureCategory == "Trace") {return -1.00;}
	else if (pressureCategory == "Very Thin"						  ) {return -1.00;}
	else if (pressureCategory == "Thin"								  ) {return -0.50;}
	else if (pressureCategory == "Standard"							  ) {return -0.25;}
	else if (pressureCategory == "Dense"							  ) {return -0.10;}
	else if (pressureCategory == "Very Dense"						  ) {return 0.000;}
	else 																{return 0.000;}
}

//	This function takes the effects of a tidally locked world on a world's
//	atmosphere and hydrographic coverage into account
tuple<float, string, float> tideLockedWorldEffects(bool tidalLockedOrNot, float surfaceTemperature, string atmosphericPressureCategory, float atmosphericPressure, float atmosphereMass, float surfaceGravity, string worldType, float hydrographicCoverage)
{
//	For worlds that are tidally locked
	float dayFaceAverageTemperature = surfaceTemperature * tideLockedDayFaceModifierTable(atmosphericPressureCategory);
	float nightFaceAverageTemperature = surfaceTemperature * tideLockedNightFaceModifierTable(atmosphericPressureCategory);

	string newPressureCategory = tideLockedFinalAtmosphereTable(atmosphericPressureCategory);
//		If the pressure category is changed, update the atmospheric pressure
	if (newPressureCategory != atmosphericPressureCategory)
	{
		if 		(newPressureCategory == "None")
		{
			atmosphericPressure = 0;
		}

		else if (newPressureCategory == "Trace")
		{
			atmosphericPressure = floatRNG(0.0001, 0.0099);
		}

		else if (newPressureCategory == "Very Thin")
		{
			atmosphericPressure = floatRNG(0.01, 0.5);
		}
//			Assign the new pressure category
		atmosphericPressureCategory = newPressureCategory;
	}

//		Apply the hydrographic coverage modifier
	hydrographicCoverage += tideLockedHydrographicCoverageModifier(atmosphericPressureCategory);

	return make_tuple(atmosphericPressure, atmosphericPressureCategory, hydrographicCoverage);
}

//	This function checks to see if the world is in a stable resonant pattern,
//	rather than being tide-locked
tuple<bool, float> resonantWorldEffects(float orbitalEccentricity, bool tidalLockedOrNot, float orbitalPeriod, float apparentDayLength)
{
	bool resonantOrNot;
	if (orbitalEccentricity >= 0.1 && tidalLockedOrNot == false)
	{
		int diceRoll = diceRoller(6, 3);
		if (diceRoll < 12)
		{
			resonantOrNot = false;
			return make_tuple(resonantOrNot, apparentDayLength);
		}

		else
		{
			resonantOrNot = true;
//			The length of a day on a resonant world is twice its orbital period
			apparentDayLength = 2 * orbitalPeriod;
			return make_tuple(resonantOrNot, apparentDayLength);
		}
	}

	else
	{
		resonantOrNot = false;
		return make_tuple(resonantOrNot, apparentDayLength);
	}
}
