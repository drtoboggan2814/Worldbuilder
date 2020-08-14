/*
	This function refers to "Diameter and Surface Gravity" in "Step 6: World Size".
	The sole parameter is the world type, and returns the world's density in
	terms of the Earth's.
*/
//	C++ libraries
#include <string>

//	Function declarations
#include "declarations/functions/floatRNG.h"
#include "declarations/functions/diceRoller.h"

using namespace std;

float worldDensityTable(string worldType)
{
	float worldDensity;
	float variance;
	int diceResult;

	diceResult = diceRoller(6, 3);

	variance = floatRNG(-0.05, 0.05);

//	Icy core worlds
	if (worldType == "Tiny (Ice)" || worldType == "Tiny (Sulfur)" || worldType == "Small (Hadean)" || worldType == "Small (Ice)" || worldType == "Standard (Hadean)" || worldType == "Standard (Ammonia)" || worldType == "Large (Ammonia)")
	{
		if 		(diceResult >= 3  	&& diceResult <= 6) 	{worldDensity = 0.3 + variance;}
		else if (diceResult >= 7  	&& diceResult <= 10) 	{worldDensity = 0.4 + variance;}
		else if (diceResult >= 11 	&& diceResult <= 14) 	{worldDensity = 0.5 + variance;}
		else if (diceResult >= 15	&& diceResult <= 17) 	{worldDensity = 0.6 + variance;}
		else if (diceResult == 18) 							{worldDensity = 0.7 + variance;}
	}

//	Small iron core worlds
	else if (worldType == "Tiny (Rock)" || worldType == "Small (Rock)")
	{
		if 		(diceResult >= 3  	&& diceResult <= 6) 	{worldDensity = 0.6 + variance;}
		else if (diceResult >= 7  	&& diceResult <= 10) 	{worldDensity = 0.7 + variance;}
		else if (diceResult >= 11 	&& diceResult <= 14) 	{worldDensity = 0.8 + variance;}
		else if (diceResult >= 15	&& diceResult <= 17) 	{worldDensity = 0.9 + variance;}
		else if (diceResult == 18) 							{worldDensity = 1.0 + variance;}
	}

	else if (worldType == "Asteroid Belt")
	{
		worldDensity = 0;
	}

//	Large iron core worlds
	else
	{
		if 		(diceResult >= 3  	&& diceResult <= 6) 	{worldDensity = 0.8 + variance;}
		else if (diceResult >= 7  	&& diceResult <= 10) 	{worldDensity = 0.9 + variance;}
		else if (diceResult >= 11 	&& diceResult <= 14) 	{worldDensity = 1.0 + variance;}
		else if (diceResult >= 15	&& diceResult <= 17) 	{worldDensity = 1.1 + variance;}
		else if (diceResult == 18) 							{worldDensity = 1.2 + variance;}
	}

	return worldDensity;
}
