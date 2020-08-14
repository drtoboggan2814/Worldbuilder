/*
	This corresponds to "Diameter and Surface Gravity" in "Step 6: World Size"
	on page 85 of GURPS Space 4e.
	This function cannot take "Asteroid Belt" as its worldType parameter.
*/

//	C++ libraries
#include <string>
#include <math.h>

//	Constant declarations
#include "declarations/constants/sizeConstraintsTableConstants.h"

//	Function declarations
#include "declarations/functions/floatRNG.h"
#include "declarations/functions/diceRoller.h"

using namespace std;

float worldDiameterCalculator(int blackbodyTemperature, float worldDensity, string worldType)
{
	float minDiameter, maxDiameter;
	float variance, worldDiameter;
	float difference, result;

//	The final variance is 5%
	variance = floatRNG(-0.05, 0.05);

//	If the world is "Tiny"
	if (worldType == "Tiny (Sulfur)" || worldType == "Tiny (Ice)" || worldType == "Tiny (Rock)")
	{
//		Calculate the minimum and maximum diamaters
		minDiameter = sqrt(blackbodyTemperature / worldDensity) * TINYMIN;
		maxDiameter = sqrt(blackbodyTemperature / worldDensity) * TINYMAX;

		difference = maxDiameter - minDiameter;

		result = (diceRoller(6, 2) - 2) * (0.1 * (difference)) + minDiameter + (variance * difference);

//		The result cannot be smaller than the minimum nor larger than the maximum
		if		(result > maxDiameter) {worldDiameter = maxDiameter;}
		else if (result < minDiameter) {worldDiameter = minDiameter;}
		else 	{worldDiameter = result;}
	}

//	If the world is "Small"
	else if (worldType == "Small (Hadean)" || worldType == "Small (Ice)" || worldType == "Small (Rock)")
	{
//		Calculate the minimum and maximum diamaters
		minDiameter = sqrt(blackbodyTemperature / worldDensity) * SMALLMIN;
		maxDiameter = sqrt(blackbodyTemperature / worldDensity) * SMALLMAX;

		difference = maxDiameter - minDiameter;

		result = (diceRoller(6, 2) - 2) * (0.1 * (difference)) + minDiameter + (variance * difference);

//		The result cannot be smaller than the minimum nor larger than the maximum
		if		(result > maxDiameter) {worldDiameter = maxDiameter;}
		else if (result < minDiameter) {worldDiameter = minDiameter;}
		else 	{worldDiameter = result;}
	}

//	If the world is "Standard"
	else if (worldType == "Standard (Chthonian)" || worldType == "Standard (Greenhouse)" || worldType == "Standard (Ammonia)" || worldType == "Standard (Ocean)" || worldType == "Standard (Ice)" || worldType == "Standard (Hadean)" || worldType == "Standard (Garden)" )
	{
//		Calculate the minimum and maximum diamaters
		minDiameter = sqrt(blackbodyTemperature / worldDensity) * STANDARDMIN;
		maxDiameter = sqrt(blackbodyTemperature / worldDensity) * STANDARDMAX;

		difference = maxDiameter - minDiameter;

		result = (diceRoller(6, 2) - 2) * (0.1 * (difference)) + minDiameter + (variance * difference);

//		The result cannot be smaller than the minimum nor larger than the maximum
		if		(result > maxDiameter) {worldDiameter = maxDiameter;}
		else if (result < minDiameter) {worldDiameter = minDiameter;}
		else 	{worldDiameter = result;}
	}

//	If the world is "Large"
	else if (worldType == "Large (Ammonia)" || worldType == "Large (Greenhouse)" || worldType == "Large (Chthonian)" || worldType == "Large (Ocean)" || worldType == "Large (Ice)" || worldType == "Large (Garden)")
	{
//		Calculate the minimum and maximum diamaters
		minDiameter = sqrt(blackbodyTemperature / worldDensity) * LARGEMIN;
		maxDiameter = sqrt(blackbodyTemperature / worldDensity) * LARGEMAX;

		difference = maxDiameter - minDiameter;

		result = (diceRoller(6, 2) - 2) * (0.1 * (difference)) + minDiameter + (variance * difference);

//		The result cannot be smaller than the minimum nor larger than the maximum
		if		(result > maxDiameter) {worldDiameter = maxDiameter;}
		else if (result < minDiameter) {worldDiameter = minDiameter;}
		else 	{worldDiameter = result;}
	}

//	This applies only to asteroid belts
	else
	{
		worldDiameter = 0;
	}

	return worldDiameter;
}
