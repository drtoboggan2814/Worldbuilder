//	C++ libraries
#include <string>

//	Constant declarations
#include "declarations/constants/worldTypeConstants.h"

//	Function declarations
#include "declarations/functions/diceRoller.h"
#include "declarations/functions/floatRNG.h"

using namespace std;

float hydrographicCoverageCalculator(char worldType)
{
	float hydrographicCoverage;
	float big, small;

	if (worldType == WT_ASTEROID_BELT || worldType == WT_TINY_SULFUR || worldType == WT_SMALL_ROCK || worldType == WT_TINY_ICE || worldType == WT_SMALL_HADEAN || worldType == WT_STANDARD_HADEAN || worldType == WT_TINY_SULFUR || worldType == WT_STANDARD_CHTHONIAN || worldType == WT_LARGE_CHTHONIAN)
	{
		hydrographicCoverage = 0;
	}

	else if (worldType == WT_SMALL_ICE) // Oceans are composed of liquid hydrocarbons rather than water.
	{
		big = (diceRoller(6, 1) + 2) * 0.1;
		small = floatRNG(-0.05, 0.05);
		hydrographicCoverage = big + small;
		if (big + small < 0) {hydrographicCoverage = 0;}
		else if (big + small > 1) {hydrographicCoverage = 1;}
	}

	else if (worldType == WT_STANDARD_AMMONIA || worldType == WT_LARGE_AMMONIA) // Oceans are composed of liquid ammonia mixed with water and other substances, mingled in a eutetic solution whose freezing point is much lower than that of pure ammonia or water.
	{
		big = diceRoller(6, 2) * 0.1;
		small = floatRNG(-0.05, 0.05);
		hydrographicCoverage = big + small;
		if (big + small < 0) {hydrographicCoverage = 0;}
		else if (big + small > 1) {hydrographicCoverage = 1;}
	}

	else if (worldType == WT_STANDARD_ICE || worldType == WT_LARGE_ICE) // Water
	{
		big = (diceRoller(6, 2) - 10) * 0.1;
		small = floatRNG(-0.05, 0.05);
		hydrographicCoverage = big + small;
		if (big + small < 0) {hydrographicCoverage = 0;}
		else if (big + small > 1) {hydrographicCoverage = 1;}
	}

	else if (worldType == WT_STANDARD_OCEAN || worldType == WT_STANDARD_GARDEN) // Water
	{
		big = (diceRoller(6, 1) + 4) * 0.1;
		small = floatRNG(-0.05, 0.05);
		hydrographicCoverage = big + small;
		if (big + small < 0) {hydrographicCoverage = 0;}
		else if (big + small > 1) {hydrographicCoverage = 1;}
	}

	else if (worldType == WT_LARGE_OCEAN || worldType == WT_LARGE_GARDEN) // Water
	{
		big = (diceRoller(6, 1) + 6) * 0.1;
		small = floatRNG(-0.05, 0.05);
		hydrographicCoverage = big + small;
		if (big + small < 0) {hydrographicCoverage = 0;}
		else if (big + small > 1) {hydrographicCoverage = 1;}
	}

	else if (worldType == WT_STANDARD_GREENHOUSE || worldType == WT_LARGE_GREENHOUSE) // Some extremely impure water, rich in dissolved carbon or sulfur compounds.
	{
		big = (diceRoller(6, 2) - 7) * 0.1;
		small = floatRNG(-0.05, 0.05);
		hydrographicCoverage = big + small;
		if (big + small < 0) {hydrographicCoverage = 0;}
		else if (big + small > 1) {hydrographicCoverage = 1;}
	}

	return hydrographicCoverage;
}
