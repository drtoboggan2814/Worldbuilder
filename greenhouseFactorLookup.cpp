//	C++ libraries
#include <string>

//	Constant declarations
#include "declarations/constants/greenhouseFactorConstants.h"
#include "declarations/constants/worldTypeConstants.h"

using namespace std;

float greenhouseFactorLookup(char worldType, float hydrographicCoverage)
{
	float gf;

if 		(worldType == WT_ASTEROID_BELT) 																																											{gf = GF_ASTEROIDBELT;}
else if (worldType == WT_TINY_ICE) 																																													{gf = GF_TINY_ICE;}
else if (worldType == WT_TINY_SULFUR) 																																												{gf = GF_TINY_SULFUR;}
else if (worldType == WT_TINY_ROCK) 																																												{gf = GF_TINY_ROCK;}
else if (worldType == WT_SMALL_HADEAN) 																																												{gf = GF_SMALL_HADEAN;}
else if (worldType == WT_SMALL_ICE) 																																												{gf = GF_SMALL_ICE;}
else if (worldType == WT_SMALL_ROCK) 																																												{gf = GF_SMALL_ROCK;}
else if (worldType == WT_STANDARD_HADEAN) 																																											{gf = GF_STANDARD_HADEAN;}
else if (worldType == WT_STANDARD_AMMONIA 		|| worldType == WT_LARGE_AMMONIA)																																	{gf = GF_STANDARDLARGE_AMMONIA;}
else if (worldType == WT_STANDARD_ICE 			|| worldType == WT_LARGE_ICE) 																																		{gf = GF_STANDARDLARGE_ICE;}
else if (worldType == WT_STANDARD_OCEAN 		|| worldType == WT_LARGE_OCEAN 	|| worldType == WT_STANDARD_GARDEN || worldType == WT_LARGE_GARDEN && hydrographicCoverage <= 0.2) 									{gf = GF_STANDARDLARGE_OCEANGARDEN_00;}
else if (worldType == WT_STANDARD_OCEAN 		|| worldType == WT_LARGE_OCEAN 	|| worldType == WT_STANDARD_GARDEN || worldType == WT_LARGE_GARDEN && hydrographicCoverage > 0.2 && hydrographicCoverage <= 0.5) 	{gf = GF_STANDARDLARGE_OCEANGARDEN_01;}
else if (worldType == WT_STANDARD_OCEAN 		|| worldType == WT_LARGE_OCEAN 	|| worldType == WT_STANDARD_GARDEN || worldType == WT_LARGE_GARDEN && hydrographicCoverage > 0.5 && hydrographicCoverage <= 0.9) 	{gf = GF_STANDARDLARGE_OCEANGARDEN_02;}
else if (worldType == WT_STANDARD_OCEAN 		|| worldType == WT_LARGE_OCEAN 	|| worldType == WT_STANDARD_GARDEN || worldType == WT_LARGE_GARDEN && hydrographicCoverage > 0.9) 									{gf = GF_STANDARDLARGE_OCEANGARDEN_03;}
else if (worldType == WT_STANDARD_CHTHONIAN 	|| worldType == WT_LARGE_CHTHONIAN)																																	{gf = GF_STANDARDLARGE_CHTHONIAN;}
else if (worldType == WT_STANDARD_GREENHOUSE 	|| worldType == WT_LARGE_GREENHOUSE)																																{gf = GF_STANDARDLARGE_GREENHOUSE;}

	return gf;
}
