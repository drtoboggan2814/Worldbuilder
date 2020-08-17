//	Determine the star's radius (except for white dwarfs)
#include <math.h>

//	Constant declarations
#include "declarations/constants/luminosityClassConstants.h"

//	Function declarations
#include "declarations/functions/floatRNG.h"

//	Structure declarations
#include "declarations/structures/world_t.h"
#include "declarations/structures/star_t.h"

star_t determineStarRadius(star_t primary)
{

//	For white dwarfs
	if (primary.luminosityClass == LC_D)
	{
		primary.stellarRadius = floatRNG(0.005, 0.015);
	}

//	All other stars
	else
	{
//		R = (155000 * sqrt*(L)) / T^2
		primary.stellarRadius = 155000 * sqrt(primary.stellarLuminosity) / (primary.stellarTemperature * primary.stellarTemperature);
	}

	return primary;
}
