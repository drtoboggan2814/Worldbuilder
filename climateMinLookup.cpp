//	Constant declarations
#include "declarations/constants/climateMinConstants.h"
#include "declarations/constants/worldTypeConstants.h"

using namespace std;

int climateMinLookup(char worldType)
{
	int min;

	if 		(worldType == WT_ASTEROID_BELT) 													{min = min_AsteroidBelt;}
	else if (worldType == WT_TINY_ICE || worldType == WT_TINY_SULFUR) 					{min = min_Tiny_IceorSulfur;}
	else if (worldType == WT_TINY_SULFUR) 													{min = min_Tiny_Rock;}
	else if (worldType == WT_SMALL_HADEAN) 												{min = min_Small_Hadean;}
	else if (worldType == WT_SMALL_ICE) 													{min = min_Small_Ice;}
	else if (worldType == WT_SMALL_ROCK) 													{min = min_Small_Rock;}
	else if (worldType == WT_STANDARD_HADEAN) 												{min = min_Standard_Hadean;}
	else if (worldType == WT_STANDARD_AMMONIA) 											{min = min_Standard_Ammonia;}
	else if (worldType == WT_STANDARD_ICE) 												{min = min_Standard_Ice;}
	else if (worldType == WT_STANDARD_OCEAN || worldType == WT_STANDARD_GARDEN) 			{min = min_Standard_OceanorGarden;}
	else if (worldType == WT_STANDARD_GREENHOUSE || worldType == WT_STANDARD_CHTHONIAN)	{min = min_Standard_GreenhouseorChthonian;}
	else if (worldType == WT_LARGE_AMMONIA) 												{min = min_Large_Ammonia;}
	else if (worldType == WT_LARGE_ICE) 													{min = min_Large_Ice;}
	else if (worldType == WT_LARGE_OCEAN || worldType == WT_LARGE_GARDEN) 				{min = min_Large_OceanorGarden;}
	else if (worldType == WT_LARGE_GREENHOUSE || worldType == WT_LARGE_CHTHONIAN) 		{min = min_Large_GreenhouseorChthonian;}

	return min;
}
