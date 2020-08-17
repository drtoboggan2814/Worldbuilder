/*
	This function returns the world type's pressure factor.
*/
//	C++ libraries
#include <string>

//	Constant declarations
#include "declarations/constants/pressureFactorsTableConstants.h"
#include "declarations/constants/worldTypeConstants.h"

using namespace std;

int pressureFactorsLookup(char worldType)
{
	int pressureFactor;

	if 		(worldType == WT_SMALL_ICE) 																													{pressureFactor = pf_Small_Ice;}
	else if (worldType == WT_STANDARD_AMMONIA 	|| worldType == WT_STANDARD_ICE || worldType == WT_STANDARD_OCEAN || worldType == WT_STANDARD_GARDEN)	{pressureFactor = pf_Standard_AIOG;}
	else if (worldType == WT_STANDARD_GREENHOUSE) 																											{pressureFactor = pf_Standard_Greenhouse;}
	else if (worldType == WT_LARGE_AMMONIA 	|| worldType == WT_LARGE_ICE || worldType == WT_LARGE_OCEAN || worldType == WT_LARGE_GARDEN) 			{pressureFactor = pf_Large_AIOG;}
	else if (worldType == WT_LARGE_GREENHOUSE) 																											{pressureFactor = pf_Large_Greenhouse;}

	return pressureFactor;
}
