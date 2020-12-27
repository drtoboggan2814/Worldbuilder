//	Constant declarations
#include "declarations/constants/absorptionFactorConstants.h"
#include "declarations/constants/worldTypeConstants.h"

using namespace std;

float absorptionFactorLookup(const char& worldType, const float& hydrographicCoverage)
{
	float af;

	if 		(worldType == WT_ASTEROID_BELT) 																																														{af = af_AsteroidBelt;}
	else if (worldType == WT_TINY_ICE) 																																														{af = af_Tiny_Ice;}
	else if (worldType == WT_TINY_SULFUR) 																																														{af = af_Tiny_Sulfur;}
	else if (worldType == WT_TINY_SULFUR) 																																														{af = af_Tiny_Rock;}
	else if (worldType == WT_SMALL_HADEAN) 																																													{af = af_Small_Hadean;}
	else if (worldType == WT_SMALL_ICE) 																																														{af = af_Small_Ice;}
	else if (worldType == WT_SMALL_ROCK) 																																														{af = af_Small_Rock;}
	else if (worldType == WT_STANDARD_HADEAN) 																																													{af = af_Standard_Hadean;}
	else if (worldType == WT_STANDARD_AMMONIA 		|| worldType == WT_LARGE_AMMONIA)																																			{af = af_StandardLarge_Ammonia;}
	else if (worldType == WT_STANDARD_ICE 			|| worldType == WT_LARGE_ICE) 																																				{af = af_StandardLarge_Ice;}
	else if (worldType == WT_STANDARD_OCEAN 		|| worldType == WT_LARGE_OCEAN 	|| worldType == WT_STANDARD_GARDEN || worldType == WT_LARGE_GARDEN && hydrographicCoverage <= 0.2) 									{af = af_StandardLarge_OceanGarden_00;}
	else if (worldType == WT_STANDARD_OCEAN 		|| worldType == WT_LARGE_OCEAN 	|| worldType == WT_STANDARD_GARDEN || worldType == WT_LARGE_GARDEN && hydrographicCoverage > 0.2 && hydrographicCoverage <= 0.5) 		{af = af_StandardLarge_OceanGarden_01;}
	else if (worldType == WT_STANDARD_OCEAN 		|| worldType == WT_LARGE_OCEAN 	|| worldType == WT_STANDARD_GARDEN || worldType == WT_LARGE_GARDEN && hydrographicCoverage > 0.5 && hydrographicCoverage <= 0.9) 		{af = af_StandardLarge_OceanGarden_02;}
	else if (worldType == WT_STANDARD_OCEAN 		|| worldType == WT_LARGE_OCEAN 	|| worldType == WT_STANDARD_GARDEN || worldType == WT_LARGE_GARDEN && hydrographicCoverage > 0.9) 									{af = af_StandardLarge_OceanGarden_03;}
	else if (worldType == WT_STANDARD_CHTHONIAN 	|| worldType == WT_LARGE_CHTHONIAN)																																		{af = af_StandardLarge_Chthonian;}
	else if (worldType == WT_STANDARD_GREENHOUSE 	|| worldType == WT_LARGE_GREENHOUSE)																																		{af = af_StandardLarge_Greenhouse;}

	return af;
}
