/*
	This function corresponds to "Worlds Big and Little" in "Step 6: World Size".
	It takes the world's blackbody temperature, diameter, and density as parameters.
	It returns the world's minimum molecular weight retained.
*/
#include <string>
#include <iostream>

using namespace std;

float minimumMolecularWeightRetainedCalculator(float blackbodyTemperature, float worldDiameter, float worldDensity, string worldType)
{
/*
	cout << "For MMWR:" << endl;
	cout << "worldType = " << worldType << endl;
	cout << "blackbodyTemperature = " << blackbodyTemperature << endl;
	cout << "worldDiameter = " << worldDiameter << endl;
	cout << "worldDensity = " << worldDensity << endl;
*/
	float minimumMolecularWeightRetained;
	if (worldType == "Asteroid Belt") {minimumMolecularWeightRetained = 0;}
	else							  {minimumMolecularWeightRetained = blackbodyTemperature / (60 * worldDiameter * worldDiameter * worldDensity);}
	return minimumMolecularWeightRetained;
}
