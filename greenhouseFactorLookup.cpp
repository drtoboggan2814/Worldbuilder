//	C++ libraries
#include <string>

//	Constant declarations
#include "declarations/constants/greenhouseFactorConstants.h"
#include "declarations/constants/worldTypeConstants.h"

using namespace std;

float greenhouseFactorLookup(char worldType, float hydrographicCoverage)
{
	float gf;

	if 		(worldType == WT_ASTEROID_BELT) 																																														{gf = gf_AsteroidBelt;}
	else if (worldType == WT_TINY_ICE) 																																														{gf = gf_Tiny_Ice;}
	else if (worldType == WT_TINY_SULFUR) 																																														{gf = gf_Tiny_Sulfur;}
	else if (worldType == WT_TINY_SULFUR) 																																														{gf = gf_Tiny_Rock;}
	else if (worldType == WT_SMALL_HADEAN) 																																													{gf = gf_Small_Hadean;}
	else if (worldType == WT_SMALL_ICE) 																																														{gf = gf_Small_Ice;}
	else if (worldType == WT_SMALL_ROCK) 																																														{gf = gf_Small_Rock;}
	else if (worldType == WT_STANDARD_HADEAN) 																																													{gf = gf_Standard_Hadean;}
	else if (worldType == WT_STANDARD_AMMONIA 		|| worldType == WT_LARGE_AMMONIA)																																			{gf = gf_StandardLarge_Ammonia;}
	else if (worldType == WT_STANDARD_ICE 			|| worldType == WT_LARGE_ICE) 																																				{gf = gf_StandardLarge_Ice;}
	else if (worldType == WT_STANDARD_OCEAN 		|| worldType == WT_LARGE_OCEAN 	|| worldType == WT_STANDARD_GARDEN || worldType == WT_LARGE_GARDEN && hydrographicCoverage <= 0.2) 									{gf = gf_StandardLarge_OceanGarden_00;}
	else if (worldType == WT_STANDARD_OCEAN 		|| worldType == WT_LARGE_OCEAN 	|| worldType == WT_STANDARD_GARDEN || worldType == WT_LARGE_GARDEN && hydrographicCoverage > 0.2 && hydrographicCoverage <= 0.5) 		{gf = gf_StandardLarge_OceanGarden_01;}
	else if (worldType == WT_STANDARD_OCEAN 		|| worldType == WT_LARGE_OCEAN 	|| worldType == WT_STANDARD_GARDEN || worldType == WT_LARGE_GARDEN && hydrographicCoverage > 0.5 && hydrographicCoverage <= 0.9) 		{gf = gf_StandardLarge_OceanGarden_02;}
	else if (worldType == WT_STANDARD_OCEAN 		|| worldType == WT_LARGE_OCEAN 	|| worldType == WT_STANDARD_GARDEN || worldType == WT_LARGE_GARDEN && hydrographicCoverage > 0.9) 									{gf = gf_StandardLarge_OceanGarden_03;}
	else if (worldType == WT_STANDARD_CHTHONIAN 	|| worldType == WT_LARGE_CHTHONIAN)																																		{gf = gf_StandardLarge_Chthonian;}
	else if (worldType == WT_STANDARD_GREENHOUSE 	|| worldType == WT_LARGE_GREENHOUSE)																																		{gf = gf_StandardLarge_Greenhouse;}

	return gf;
}
