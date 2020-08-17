//	C++ libraries
#include <string>

//	Constant declarations
#include "declarations/constants/climateStepConstants.h"
#include "declarations/constants/worldTypeConstants.h"

using namespace std;

int climateStepLookup(char worldType)
{
	int step;

	if 		(worldType == WT_ASTEROID_BELT) 													{step = step_AsteroidBelt;}
	else if (worldType == WT_TINY_ICE || worldType == WT_TINY_SULFUR) 					{step = step_Tiny_IceorSulfur;}
	else if (worldType == WT_TINY_SULFUR) 													{step = step_Tiny_Rock;}
	else if (worldType == WT_SMALL_HADEAN) 												{step = step_Small_Hadean;}
	else if (worldType == WT_SMALL_ICE) 													{step = step_Small_Ice;}
	else if (worldType == WT_SMALL_ROCK) 													{step = step_Small_Rock;}
	else if (worldType == WT_STANDARD_HADEAN) 												{step = step_Standard_Hadean;}
	else if (worldType == WT_STANDARD_AMMONIA) 											{step = step_Standard_Ammonia;}
	else if (worldType == WT_STANDARD_ICE) 												{step = step_Standard_Ice;}
	else if (worldType == WT_STANDARD_OCEAN || worldType == WT_STANDARD_GARDEN) 			{step = step_Standard_OceanorGarden;}
	else if (worldType == WT_STANDARD_GREENHOUSE || worldType == WT_STANDARD_CHTHONIAN)	{step = step_Standard_GreenhouseorChthonian;}
	else if (worldType == WT_LARGE_AMMONIA) 												{step = step_Large_Ammonia;}
	else if (worldType == WT_LARGE_ICE) 													{step = step_Large_Ice;}
	else if (worldType == WT_LARGE_OCEAN || worldType == WT_LARGE_GARDEN) 				{step = step_Large_OceanorGarden;}
	else if (worldType == WT_LARGE_GREENHOUSE || worldType == WT_LARGE_CHTHONIAN) 		{step = step_Large_GreenhouseorChthonian;}

	return step;
}
