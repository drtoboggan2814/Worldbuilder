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
	int pressureFactor = 0;

	if 		(worldType == WT_SMALL_ICE) 																												{pressureFactor = PF_SMALL_ICE;}
	else if (worldType == WT_STANDARD_AMMONIA 	|| worldType == WT_STANDARD_ICE || worldType == WT_STANDARD_OCEAN || worldType == WT_STANDARD_GARDEN)	{pressureFactor = PF_STANDARD_AIOG;}
	else if (worldType == WT_STANDARD_GREENHOUSE) 																										{pressureFactor = PF_STANDARD_GREENHOUSE;}
	else if (worldType == WT_LARGE_AMMONIA 	|| worldType == WT_LARGE_ICE || worldType == WT_LARGE_OCEAN || worldType == WT_LARGE_GARDEN) 				{pressureFactor = PF_LARGE_AIOG;}
	else if (worldType == WT_LARGE_GREENHOUSE) 																											{pressureFactor = PF_LARGE_GREENHOUSE;}

	return pressureFactor;
}
