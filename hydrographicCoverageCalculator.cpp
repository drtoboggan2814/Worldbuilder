#include <string>
#include "declarations/functions/diceRoller.h"
#include "declarations/functions/floatRNG.h"

using namespace std;

float hydrographicCoverageCalculator(string worldType)
{
	float hydrographicCoverage;
	float big, small;

	if (worldType == "Asteroid Belt" || worldType == "Tiny (Rock)" || worldType == "Small (Rock)" || worldType == "Tiny (Ice)" || worldType == "Small (Hadean)" || worldType == "Standard (Hadean)" || worldType == "Tiny (Sulfur)" || worldType == "Standard (Chthonian)" || worldType == "Large (Chthonian)")
	{
		hydrographicCoverage = 0;
	}

	else if (worldType == "Small (Ice)") // Oceans are composed of liquid hydrocarbons rather than water.
	{
		big = (diceRoller(6, 1) + 2) * 0.1;
		small = floatRNG(-0.05, 0.05);
		hydrographicCoverage = big + small;
		if (big + small < 0) {hydrographicCoverage = 0;}
		else if (big + small > 1) {hydrographicCoverage = 1;}
	}

	else if (worldType == "Standard (Ammonia)" || worldType == "Large (Ammonia)") // Oceans are composed of liquid ammonia mixed with water and other substances, mingled in a eutetic solution whose freezing point is much lower than that of pure ammonia or water.
	{
		big = diceRoller(6, 2) * 0.1;
		small = floatRNG(-0.05, 0.05);
		hydrographicCoverage = big + small;
		if (big + small < 0) {hydrographicCoverage = 0;}
		else if (big + small > 1) {hydrographicCoverage = 1;}
	}

	else if (worldType == "Standard (Ice)" || worldType == "Large (Ice)") // Water
	{
		big = (diceRoller(6, 2) - 10) * 0.1;
		small = floatRNG(-0.05, 0.05);
		hydrographicCoverage = big + small;
		if (big + small < 0) {hydrographicCoverage = 0;}
		else if (big + small > 1) {hydrographicCoverage = 1;}
	}

	else if (worldType == "Standard (Ocean)" || worldType == "Standard (Garden)") // Water
	{
		big = (diceRoller(6, 1) + 4) * 0.1;
		small = floatRNG(-0.05, 0.05);
		hydrographicCoverage = big + small;
		if (big + small < 0) {hydrographicCoverage = 0;}
		else if (big + small > 1) {hydrographicCoverage = 1;}
	}

	else if (worldType == "Large (Ocean)" || worldType == "Large (Garden)") // Water
	{
		big = (diceRoller(6, 1) + 6) * 0.1;
		small = floatRNG(-0.05, 0.05);
		hydrographicCoverage = big + small;
		if (big + small < 0) {hydrographicCoverage = 0;}
		else if (big + small > 1) {hydrographicCoverage = 1;}
	}

	else if (worldType == "Standard (Greenhouse)" || worldType == "Large (Greenhouse)") // Some extremely impure water, rich in dissolved carbon or sulfur compounds.
	{
		big = (diceRoller(6, 2) - 7) * 0.1;
		small = floatRNG(-0.05, 0.05);
		hydrographicCoverage = big + small;
		if (big + small < 0) {hydrographicCoverage = 0;}
		else if (big + small > 1) {hydrographicCoverage = 1;}
	}

	return hydrographicCoverage;
}
