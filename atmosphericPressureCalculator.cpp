// Constant declarations
#include "declarations/constants/worldTypeConstants.h"

//	Function declarations
#include "declarations/functions/pressureFactorsLookup.h"
/*
	This function corresponds to "Determining Atmospheric Pressure" in "Step 6:	World Size".
	It takes the world's surface gravity, atmospheric mass, and world type as parameters.
	The world's calculated atmospheric pressure in terms of Earth's is returned.
*/
float atmosphericPressureCalculator(float atmosphereMass, float surfaceGravity, char worldType)
{
	int pressureFactor;
	float atmosphericPressure;

	if (worldType == WT_ASTEROID_BELT || atmosphereMass == 0)
	{
		atmosphericPressure = 0;
	}

	else
	{
		pressureFactor = pressureFactorsLookup(worldType);
		atmosphericPressure = atmosphereMass * surfaceGravity * pressureFactor;
	}

	return atmosphericPressure;
}
