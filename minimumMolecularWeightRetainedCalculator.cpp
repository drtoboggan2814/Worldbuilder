/*
	This function corresponds to "Worlds Big and Little" in "Step 6: World Size".
	It takes the world's blackbody temperature, diameter, and density as parameters.
	It returns the world's minimum molecular weight retained.
*/
//	C++ libraries
#include <string>
#include <iostream>

//	Constant declarations
#include "declarations/constants/worldTypeConstants.h"

using namespace std;

float minimumMolecularWeightRetainedCalculator(float blackbodyTemperature, float worldDiameter, float worldDensity, char worldType)
{
/*
	cout << "For MMWR:" << endl;
	cout << "worldType = " << worldType << endl;
	cout << "blackbodyTemperature = " << blackbodyTemperature << endl;
	cout << "worldDiameter = " << worldDiameter << endl;
	cout << "worldDensity = " << worldDensity << endl;
*/
	float minimumMolecularWeightRetained;
	if (worldType == WT_ASTEROID_BELT) {minimumMolecularWeightRetained = 0;}
	else							  {minimumMolecularWeightRetained = blackbodyTemperature / (60 * worldDiameter * worldDiameter * worldDensity);}
	return minimumMolecularWeightRetained;
}
