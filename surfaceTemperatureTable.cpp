//	Constant declarations
#include "declarations/constants/climateStepConstants.h"
#include "declarations/constants/climateMinConstants.h"
#include "declarations/constants/worldTypeConstants.h"

//	Function declarations
#include "declarations/functions/climateStepLookup.h"
#include "declarations/functions/climateMinLookup.h"
#include "declarations/functions/diceRoller.h"
#include "declarations/functions/intRNG.h"

using namespace std;

int surfaceTemperatureTable(char worldType)
{
	int surfaceTemperature;
	int step		= climateStepLookup(worldType);
	int min			= climateMinLookup(worldType);
	int variance	= intRNG(min * -0.5, min * 0.5);

	surfaceTemperature = ((diceRoller(6, 3) - 3) * step) + min + variance;

	return surfaceTemperature;
}
