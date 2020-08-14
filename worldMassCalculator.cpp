/*
	This function corresponds to "Mass" in "Step 6: World Size".
	It takes the world's density and diameter as parameters.
	The world's mass in terms of Earth's is returned.
*/
#include <math.h>

float worldMassCalculator(float worldDensity, float worldDiameter)
{
	float worldMass = worldDensity * pow(worldDiameter, 3);
	return worldMass;
}
