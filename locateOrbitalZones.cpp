#include <math.h>

float getInnerLimitRadius(float stellarMass, float stellarLuminosity)
{
	float limit1 = 0.1 * stellarMass;
	float limit2 = 0.01 * sqrt(stellarLuminosity);

	if (limit1 > limit2) {return limit1;}
	else {return limit2;}
}

float getOuterLimitRadius(float stellarMass)
{
	return 40 * stellarMass;
}

float getSnowLine(float stellarLuminosity)
{
	return 4.85 * sqrt(stellarLuminosity);
}

//	Deprecated in favor of orbitalSeparationTable
/*
float getInnerForbiddenZone(float minimumSeparation)
{
	return minimumSeparation / 3;
}

float getOuterForbiddenZone(float maximumSeparation)
{
	return maximumSeparation * 3;
}
*/
