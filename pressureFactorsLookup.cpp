/*
	This function returns the world type's pressure factor.
*/
#include <string>
#include "declarations/constants/pressureFactorsTableConstants.h"

using namespace std;

int pressureFactorsLookup(string worldType)
{
	int pressureFactor;

	if 		(worldType == "Small (Ice)") 																													{pressureFactor = pf_Small_Ice;}
	else if (worldType == "Standard (Ammonia)" 	|| worldType == "Standard (Ice)" || worldType == "Standard (Ocean)" || worldType == "Standard (Garden)")	{pressureFactor = pf_Standard_AIOG;}
	else if (worldType == "Standard (Greenhouse)") 																											{pressureFactor = pf_Standard_Greenhouse;}
	else if (worldType == "Large (Ammonia)" 	|| worldType == "Large (Ice)" || worldType == "Large (Ocean)" || worldType == "Large (Garden)") 			{pressureFactor = pf_Large_AIOG;}
	else if (worldType == "Large (Greenhouse)") 																											{pressureFactor = pf_Large_Greenhouse;}

	return pressureFactor;
}
