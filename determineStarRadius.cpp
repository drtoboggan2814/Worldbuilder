//	Determine the star's radius (except for white dwarfs)
#include <math.h>

//	Constant declarations
#include "declarations/constants/luminosityClassConstants.h"

//	Function declarations
#include "declarations/functions/floatRNG.h"

float determineStarRadius(char luminosityClass, float stellarLuminosity, float stellarTemperature)
{
//	Initialize return value
	float stellarRadius;
//	For white dwarfs
	if (luminosityClass == LC_D)
	{
		stellarRadius = floatRNG(0.005, 0.015);
	}

//	All other stars
	else
	{
//		R = (155000 * sqrt*(L)) / T^2
		stellarRadius = 155000 * sqrt(stellarLuminosity) / (stellarTemperature * stellarTemperature);
	}

	return stellarRadius;
}
