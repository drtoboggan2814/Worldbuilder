#include "declarations/structures/atmosphericComposition_t.h"

bool breathableChecker(const atmosphericComposition_t& atmosphereComposition)
{
	bool breathable;

	if (atmosphereComposition.toxicity != 0 || atmosphereComposition.chlorineOrFluorine != 0 || atmosphereComposition.lowOxygen != 0 || atmosphereComposition.highOxygen != 0 || atmosphereComposition.organicToxins != 0 || atmosphereComposition.sulfurCompounds != 0 || atmosphereComposition.suffocating != 0 || atmosphereComposition.highCarbonDioxide != 0 || atmosphereComposition.inertGases != 0 || atmosphereComposition.nitrogenCompounds != 0 || atmosphereComposition.pollutants != 0 || atmosphereComposition.corrosive != 0)
	{
		breathable = false;
	}

	else
	{
		breathable = true;
	}

	return breathable;
}
