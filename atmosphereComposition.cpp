//	C++ libraries
#include <string>

//	Constant declarations
#include "declarations/constants/worldTypeConstants.h"

//	Struct declarations
#include "declarations/structures/marginalAtmosphere_t.h"
#include "declarations/structures/atmosphericComposition_t.h"

//	Function declarations
#include "declarations/functions/diceRoller.h"
#include "declarations/functions/marginalAtmosphereTable.h"


using namespace std;

atmosphericComposition_t atmosphereComposition(char worldType)
{
//	Initialize the atmospheric composition
	atmosphericComposition_t atmosphereComposition;

//	Roll dice
	int result = diceRoller(6, 3);
	int marginalAtmosphereRNG = diceRoller(6, 3);

//	Initialize marginal atmosphere
	marginalAtmosphere_t marginalAtmosphere;
	int marginalAtmosphereArray[9];

//	Assign values
	if 		(worldType == WT_SMALL_ICE)
	{
		if (result <= 15)
		{
			atmosphereComposition.toxicity				= 1;
			atmosphereComposition.chlorineOrFluorine 	= 0;
			atmosphereComposition.lowOxygen	 			= 0;
			atmosphereComposition.highOxygen			= 0;
			atmosphereComposition.organicToxins 		= 0;
			atmosphereComposition.sulfurCompounds		= 0;
			atmosphereComposition.suffocating 			= 1;
			atmosphereComposition.highCarbonDioxide 	= 0;
			atmosphereComposition.inertGases 			= 0;
			atmosphereComposition.nitrogenCompounds 	= 0;
			atmosphereComposition.pollutants 			= 0;
			atmosphereComposition.corrosive 			= 0;
		}

		else
		{
			atmosphereComposition.toxicity				= 2;
			atmosphereComposition.chlorineOrFluorine 	= 0;
			atmosphereComposition.lowOxygen	 			= 0;
			atmosphereComposition.highOxygen			= 0;
			atmosphereComposition.organicToxins 		= 0;
			atmosphereComposition.sulfurCompounds		= 0;
			atmosphereComposition.suffocating 			= 1;
			atmosphereComposition.highCarbonDioxide 	= 0;
			atmosphereComposition.inertGases 			= 0;
			atmosphereComposition.nitrogenCompounds 	= 0;
			atmosphereComposition.pollutants 			= 0;
			atmosphereComposition.corrosive 			= 0;
		}
	}

	else if (worldType == WT_STANDARD_AMMONIA)
	{
		atmosphereComposition.toxicity				= 3;
		atmosphereComposition.chlorineOrFluorine 	= 0;
		atmosphereComposition.lowOxygen	 			= 0;
		atmosphereComposition.highOxygen			= 0;
		atmosphereComposition.organicToxins 		= 0;
		atmosphereComposition.sulfurCompounds		= 0;
		atmosphereComposition.suffocating 			= 1;
		atmosphereComposition.highCarbonDioxide 	= 0;
		atmosphereComposition.inertGases 			= 0;
		atmosphereComposition.nitrogenCompounds 	= 0;
		atmosphereComposition.pollutants 			= 0;
		atmosphereComposition.corrosive 			= 1;
	}

	else if (worldType == WT_STANDARD_ICE)
	{
		if (result <= 12)
		{
			atmosphereComposition.toxicity				= 0;
			atmosphereComposition.chlorineOrFluorine 	= 0;
			atmosphereComposition.lowOxygen	 			= 0;
			atmosphereComposition.highOxygen			= 0;
			atmosphereComposition.organicToxins 		= 0;
			atmosphereComposition.sulfurCompounds		= 0;
			atmosphereComposition.suffocating 			= 1;
			atmosphereComposition.highCarbonDioxide 	= 0;
			atmosphereComposition.inertGases 			= 0;
			atmosphereComposition.nitrogenCompounds 	= 0;
			atmosphereComposition.pollutants 			= 0;
			atmosphereComposition.corrosive 			= 0;
		}

		else
		{
			atmosphereComposition.toxicity				= 1;
			atmosphereComposition.chlorineOrFluorine 	= 0;
			atmosphereComposition.lowOxygen	 			= 0;
			atmosphereComposition.highOxygen			= 0;
			atmosphereComposition.organicToxins 		= 0;
			atmosphereComposition.sulfurCompounds		= 0;
			atmosphereComposition.suffocating 			= 1;
			atmosphereComposition.highCarbonDioxide 	= 0;
			atmosphereComposition.inertGases 			= 0;
			atmosphereComposition.nitrogenCompounds 	= 0;
			atmosphereComposition.pollutants 			= 0;
			atmosphereComposition.corrosive 			= 0;
		}
	}

	else if (worldType == WT_STANDARD_OCEAN)
	{
		if (result <= 12)
		{
			atmosphereComposition.toxicity				= 0;
			atmosphereComposition.chlorineOrFluorine 	= 0;
			atmosphereComposition.lowOxygen	 			= 0;
			atmosphereComposition.highOxygen			= 0;
			atmosphereComposition.organicToxins 		= 0;
			atmosphereComposition.sulfurCompounds		= 0;
			atmosphereComposition.suffocating 			= 1;
			atmosphereComposition.highCarbonDioxide 	= 0;
			atmosphereComposition.inertGases 			= 0;
			atmosphereComposition.nitrogenCompounds 	= 0;
			atmosphereComposition.pollutants 			= 0;
			atmosphereComposition.corrosive 			= 0;
		}

		else
		{
			atmosphereComposition.toxicity				= 1;
			atmosphereComposition.chlorineOrFluorine 	= 0;
			atmosphereComposition.lowOxygen	 			= 0;
			atmosphereComposition.highOxygen			= 0;
			atmosphereComposition.organicToxins 		= 0;
			atmosphereComposition.sulfurCompounds		= 0;
			atmosphereComposition.suffocating 			= 1;
			atmosphereComposition.highCarbonDioxide 	= 0;
			atmosphereComposition.inertGases 			= 0;
			atmosphereComposition.nitrogenCompounds 	= 0;
			atmosphereComposition.pollutants 			= 0;
			atmosphereComposition.corrosive 			= 0;
		}
	}

	else if (worldType == WT_STANDARD_GARDEN)
	{
		if (result <= 11)
		{
			atmosphereComposition.toxicity				= 0;
			atmosphereComposition.chlorineOrFluorine 	= 0;
			atmosphereComposition.lowOxygen	 			= 0;
			atmosphereComposition.highOxygen			= 0;
			atmosphereComposition.organicToxins 		= 0;
			atmosphereComposition.sulfurCompounds		= 0;
			atmosphereComposition.suffocating 			= 0;
			atmosphereComposition.highCarbonDioxide 	= 0;
			atmosphereComposition.inertGases 			= 0;
			atmosphereComposition.nitrogenCompounds 	= 0;
			atmosphereComposition.pollutants 			= 0;
			atmosphereComposition.corrosive 			= 0;
		}

		else
		{
			marginalAtmosphere = marginalAtmosphereTable(marginalAtmosphereRNG);

			atmosphereComposition.toxicity				= 0;
			atmosphereComposition.chlorineOrFluorine 	= marginalAtmosphere.marginalAtmosphereArray[0];
			atmosphereComposition.sulfurCompounds		= marginalAtmosphere.marginalAtmosphereArray[1];
			atmosphereComposition.nitrogenCompounds		= marginalAtmosphere.marginalAtmosphereArray[2];
			atmosphereComposition.organicToxins			= marginalAtmosphere.marginalAtmosphereArray[3];
			atmosphereComposition.lowOxygen				= marginalAtmosphere.marginalAtmosphereArray[4];
			atmosphereComposition.pollutants			= marginalAtmosphere.marginalAtmosphereArray[5];
			atmosphereComposition.highCarbonDioxide		= marginalAtmosphere.marginalAtmosphereArray[6];
			atmosphereComposition.highOxygen			= marginalAtmosphere.marginalAtmosphereArray[7];
			atmosphereComposition.inertGases			= marginalAtmosphere.marginalAtmosphereArray[8];
			atmosphereComposition.corrosive 			= 0;
		}
	}

	else if (worldType == WT_STANDARD_GREENHOUSE)
	{
		atmosphereComposition.toxicity				= 3;
		atmosphereComposition.chlorineOrFluorine 	= 0;
		atmosphereComposition.lowOxygen	 			= 0;
		atmosphereComposition.highOxygen			= 0;
		atmosphereComposition.organicToxins 		= 0;
		atmosphereComposition.sulfurCompounds		= 0;
		atmosphereComposition.suffocating 			= 1;
		atmosphereComposition.highCarbonDioxide 	= 0;
		atmosphereComposition.inertGases 			= 0;
		atmosphereComposition.nitrogenCompounds 	= 0;
		atmosphereComposition.pollutants 			= 0;
		atmosphereComposition.corrosive 			= 1;
	}

	else if (worldType == WT_LARGE_AMMONIA)
	{
		atmosphereComposition.toxicity				= 3;
		atmosphereComposition.chlorineOrFluorine 	= 0;
		atmosphereComposition.lowOxygen	 			= 0;
		atmosphereComposition.highOxygen			= 0;
		atmosphereComposition.organicToxins 		= 0;
		atmosphereComposition.sulfurCompounds		= 0;
		atmosphereComposition.suffocating 			= 1;
		atmosphereComposition.highCarbonDioxide 	= 0;
		atmosphereComposition.inertGases 			= 0;
		atmosphereComposition.nitrogenCompounds 	= 0;
		atmosphereComposition.pollutants 			= 0;
		atmosphereComposition.corrosive 			= 1;
	}

	else if (worldType == WT_LARGE_ICE)
	{
		atmosphereComposition.toxicity				= 2;
		atmosphereComposition.chlorineOrFluorine 	= 0;
		atmosphereComposition.lowOxygen	 			= 0;
		atmosphereComposition.highOxygen			= 0;
		atmosphereComposition.organicToxins 		= 0;
		atmosphereComposition.sulfurCompounds		= 0;
		atmosphereComposition.suffocating 			= 1;
		atmosphereComposition.highCarbonDioxide 	= 0;
		atmosphereComposition.inertGases 			= 0;
		atmosphereComposition.nitrogenCompounds 	= 0;
		atmosphereComposition.pollutants 			= 0;
		atmosphereComposition.corrosive 			= 0;
	}

	else if (worldType == WT_LARGE_OCEAN)
	{
		atmosphereComposition.toxicity				= 2;
		atmosphereComposition.chlorineOrFluorine 	= 0;
		atmosphereComposition.lowOxygen	 			= 0;
		atmosphereComposition.highOxygen			= 0;
		atmosphereComposition.organicToxins 		= 0;
		atmosphereComposition.sulfurCompounds		= 0;
		atmosphereComposition.suffocating 			= 1;
		atmosphereComposition.highCarbonDioxide 	= 0;
		atmosphereComposition.inertGases 			= 0;
		atmosphereComposition.nitrogenCompounds 	= 0;
		atmosphereComposition.pollutants 			= 0;
		atmosphereComposition.corrosive 			= 0;
	}

	else if (worldType == WT_LARGE_GARDEN)
	{
		if (result <= 12)
		{
			atmosphereComposition.toxicity				= 0;
			atmosphereComposition.chlorineOrFluorine 	= 0;
			atmosphereComposition.lowOxygen	 			= 0;
			atmosphereComposition.highOxygen			= 0;
			atmosphereComposition.organicToxins 		= 0;
			atmosphereComposition.sulfurCompounds		= 0;
			atmosphereComposition.suffocating 			= 0;
			atmosphereComposition.highCarbonDioxide 	= 0;
			atmosphereComposition.inertGases 			= 0;
			atmosphereComposition.nitrogenCompounds 	= 0;
			atmosphereComposition.pollutants 			= 0;
			atmosphereComposition.corrosive 			= 0;
		}

		else
		{
			marginalAtmosphere = marginalAtmosphereTable(marginalAtmosphereRNG);

			atmosphereComposition.toxicity				= 0;
			atmosphereComposition.chlorineOrFluorine 	= marginalAtmosphereArray[0];
			atmosphereComposition.sulfurCompounds		= marginalAtmosphereArray[1];
			atmosphereComposition.nitrogenCompounds		= marginalAtmosphereArray[2];
			atmosphereComposition.organicToxins			= marginalAtmosphereArray[3];
			atmosphereComposition.lowOxygen				= marginalAtmosphereArray[4];
			atmosphereComposition.pollutants			= marginalAtmosphereArray[5];
			atmosphereComposition.highCarbonDioxide		= marginalAtmosphereArray[6];
			atmosphereComposition.highOxygen			= marginalAtmosphereArray[7];
			atmosphereComposition.inertGases			= marginalAtmosphereArray[8];
			atmosphereComposition.corrosive 			= 0;
		}
	}

	else if (worldType == WT_LARGE_GREENHOUSE)
	{
		atmosphereComposition.toxicity				= 3;
		atmosphereComposition.chlorineOrFluorine 	= 0;
		atmosphereComposition.lowOxygen	 			= 0;
		atmosphereComposition.highOxygen			= 0;
		atmosphereComposition.organicToxins 		= 0;
		atmosphereComposition.sulfurCompounds		= 0;
		atmosphereComposition.suffocating 			= 1;
		atmosphereComposition.highCarbonDioxide 	= 0;
		atmosphereComposition.inertGases 			= 0;
		atmosphereComposition.nitrogenCompounds 	= 0;
		atmosphereComposition.pollutants 			= 0;
		atmosphereComposition.corrosive 			= 1;
	}

	else
	{
		atmosphereComposition.toxicity				= 0;
		atmosphereComposition.chlorineOrFluorine 	= 0;
		atmosphereComposition.lowOxygen	 			= 0;
		atmosphereComposition.highOxygen			= 0;
		atmosphereComposition.organicToxins 		= 0;
		atmosphereComposition.sulfurCompounds		= 0;
		atmosphereComposition.suffocating 			= 0;
		atmosphereComposition.highCarbonDioxide 	= 0;
		atmosphereComposition.inertGases 			= 0;
		atmosphereComposition.nitrogenCompounds 	= 0;
		atmosphereComposition.pollutants 			= 0;
		atmosphereComposition.corrosive 			= 0;
	}

	return atmosphereComposition;
}
