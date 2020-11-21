/*
	This corresponds to "Diameter and Surface Gravity" in "Step 6: World Size"
	on page 85 of GURPS Space 4e.
	This function cannot take WT_ASTEROID_BELT as its worldType parameter.
*/

//	C++ libraries
#include <string>
#include <math.h>

//	Constant declarations
#include "declarations/constants/sizeConstraintsTableConstants.h"
#include "declarations/constants/worldTypeConstants.h"

//	Function declarations
#include "declarations/functions/floatRNG.h"
#include "declarations/functions/diceRoller.h"

using namespace std;

float worldDiameterCalculator(int blackbodyTemperature, float worldDensity, char worldType)
{
	float minDiameter, maxDiameter;
	float variance, worldDiameter;
	float difference, result;

//	The final variance is 5%
	variance = floatRNG(-0.05, 0.05);

//	If the world is "Tiny"
	if (worldType == WT_TINY_SULFUR || worldType == WT_TINY_ICE || worldType == WT_TINY_SULFUR)
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
	else if (worldType == WT_SMALL_HADEAN || worldType == WT_SMALL_ICE || worldType == WT_SMALL_ROCK)
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
	else if (worldType == WT_STANDARD_CHTHONIAN || worldType == WT_STANDARD_GREENHOUSE || worldType == WT_STANDARD_AMMONIA || worldType == WT_STANDARD_OCEAN || worldType == WT_STANDARD_ICE || worldType == WT_STANDARD_HADEAN || worldType == WT_STANDARD_GARDEN )
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
	else if (worldType == WT_LARGE_AMMONIA || worldType == WT_LARGE_GREENHOUSE || worldType == WT_LARGE_CHTHONIAN || worldType == WT_LARGE_OCEAN || worldType == WT_LARGE_ICE || worldType == WT_LARGE_GARDEN)
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
