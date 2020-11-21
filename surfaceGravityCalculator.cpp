/*
	This function corresponds to "Diameter and Surface Gravity" in "Step 6: World Size".
	The function takes the world's density and diameter as parameters.
	It returns the world's surface gravity in Terran G's.
*/
float surfaceGravityCalculator(float worldDensity, float worldDiameter)
{
	float surfaceGravity;

	surfaceGravity = worldDensity * worldDiameter;

	return surfaceGravity;
}
