//	Constant declarations
#include "declarations/constants/absorptionFactorConstants.h"
#include "declarations/constants/worldTypeConstants.h"

using namespace std;

float absorptionFactorLookup(char worldType, float hydrographicCoverage)
{
	float af;

	if 		(worldType == WT_ASTEROID_BELT) 																																											{af = AF_ASTEROIDBELT;}
	else if (worldType == WT_TINY_ICE) 																																													{af = AF_TINY_ICE;}
	else if (worldType == WT_TINY_SULFUR) 																																												{af = AF_TINY_SULFUR;}
	else if (worldType == WT_TINY_ROCK) 																																												{af = AF_TINY_ROCK;}
	else if (worldType == WT_SMALL_HADEAN) 																																												{af = AF_SMALL_HADEAN;}
	else if (worldType == WT_SMALL_ICE) 																																												{af = AF_SMALL_ICE;}
	else if (worldType == WT_SMALL_ROCK) 																																												{af = AF_SMALL_ROCK;}
	else if (worldType == WT_STANDARD_HADEAN) 																																											{af = AF_STANDARD_HADEAN;}
	else if (worldType == WT_STANDARD_AMMONIA 		|| worldType == WT_LARGE_AMMONIA)																																	{af = AF_STANDARDLARGE_AMMONIA;}
	else if (worldType == WT_STANDARD_ICE 			|| worldType == WT_LARGE_ICE) 																																		{af = AF_STANDARDLARGE_ICE;}
	else if (worldType == WT_STANDARD_OCEAN 		|| worldType == WT_LARGE_OCEAN 	|| worldType == WT_STANDARD_GARDEN || worldType == WT_LARGE_GARDEN && hydrographicCoverage <= 0.2) 									{af = AF_STANDARDLARGE_OCEANGARDEN_00;}
	else if (worldType == WT_STANDARD_OCEAN 		|| worldType == WT_LARGE_OCEAN 	|| worldType == WT_STANDARD_GARDEN || worldType == WT_LARGE_GARDEN && hydrographicCoverage > 0.2 && hydrographicCoverage <= 0.5) 	{af = AF_STANDARDLARGE_OCEANGARDEN_01;}
	else if (worldType == WT_STANDARD_OCEAN 		|| worldType == WT_LARGE_OCEAN 	|| worldType == WT_STANDARD_GARDEN || worldType == WT_LARGE_GARDEN && hydrographicCoverage > 0.5 && hydrographicCoverage <= 0.9) 	{af = AF_STANDARDLARGE_OCEANGARDEN_02;}
	else if (worldType == WT_STANDARD_OCEAN 		|| worldType == WT_LARGE_OCEAN 	|| worldType == WT_STANDARD_GARDEN || worldType == WT_LARGE_GARDEN && hydrographicCoverage > 0.9) 									{af = AF_STANDARDLARGE_OCEANGARDEN_03;}
	else if (worldType == WT_STANDARD_CHTHONIAN 	|| worldType == WT_LARGE_CHTHONIAN)																																	{af = AF_STANDARDLARGE_CHTHONIAN;}
	else if (worldType == WT_STANDARD_GREENHOUSE 	|| worldType == WT_LARGE_GREENHOUSE)																																{af = AF_STANDARDLARGE_GREENHOUSE;}

	return af;
}
