//	This file contains fucntions pertaining to solar power in a star system
//	C++ libraries
#include <math.h>

//	Constant declarations
//	#include "declarations/constants/unitConversions.h"
#include "declarations/constants/universalConstants.h"

//	Calculates the energy radiated by the star in W / m^2
float stefanBoltzmannCalculator(float effectiveTemperature)
{
	float energyRadiated = STEFAN_BOLTZMANN_CONSTANT * pow(effectiveTemperature, 4);
	return energyRadiated;
}

//	stellarRadius and distance are given in au's, energyRadiated in W / m^2
//	The return value is in W / m^2
float solarPowerAtDistance(float stellarRadius, float distance, float energyRadiated)
{
	float solarPower = ((stellarRadius * stellarRadius) / (distance * distance)) * energyRadiated;
	return solarPower;
}
