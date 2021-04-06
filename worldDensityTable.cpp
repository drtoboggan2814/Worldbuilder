/*
	This function refers to "Diameter and Surface Gravity" in "Step 6: World Size".
	The sole parameter is the world type, and returns the world's density in
	terms of the Earth's.
*/
//	C++ libraries
#include <string>

//	Constant declarations
#include "declarations/constants/worldTypeConstants.h"

//	Function declarations
#include "declarations/functions/floatRNG.h"
#include "declarations/functions/diceRoller.h"

using namespace std;

float worldDensityTable(char worldType)
{
	float worldDensity = 0;
	float variance = floatRNG(-0.05, 0.05);
	int diceResult = diceRoller(6, 3);

	//	Icy core worlds
	if (worldType == WT_TINY_ICE || worldType == WT_TINY_SULFUR || worldType == WT_SMALL_HADEAN || worldType == WT_SMALL_ICE || worldType == WT_STANDARD_HADEAN || worldType == WT_STANDARD_AMMONIA || worldType == WT_LARGE_AMMONIA)
	{
		if 		(diceResult >= 3  	&& diceResult <= 6) 	{worldDensity = 0.3 + variance;}
		else if (diceResult >= 7  	&& diceResult <= 10) 	{worldDensity = 0.4 + variance;}
		else if (diceResult >= 11 	&& diceResult <= 14) 	{worldDensity = 0.5 + variance;}
		else if (diceResult >= 15	&& diceResult <= 17) 	{worldDensity = 0.6 + variance;}
		else if (diceResult == 18) 							{worldDensity = 0.7 + variance;}
	}

//	Small iron core worlds
	else if (worldType == WT_TINY_ROCK || worldType == WT_SMALL_ROCK)
	{
		if 		(diceResult >= 3  	&& diceResult <= 6) 	{worldDensity = 0.6 + variance;}
		else if (diceResult >= 7  	&& diceResult <= 10) 	{worldDensity = 0.7 + variance;}
		else if (diceResult >= 11 	&& diceResult <= 14) 	{worldDensity = 0.8 + variance;}
		else if (diceResult >= 15	&& diceResult <= 17) 	{worldDensity = 0.9 + variance;}
		else if (diceResult == 18) 							{worldDensity = 1.0 + variance;}
	}

	else if (worldType == WT_ASTEROID_BELT)
	{
		worldDensity = 0;
	}

//	Large iron core worlds
	else
	{
		if 		(diceResult <= 6) 							{worldDensity = 0.8 + variance;}
		else if (diceResult >= 7  	&& diceResult <= 10) 	{worldDensity = 0.9 + variance;}
		else if (diceResult >= 11 	&& diceResult <= 14) 	{worldDensity = 1.0 + variance;}
		else if (diceResult >= 15	&& diceResult <= 17) 	{worldDensity = 1.1 + variance;}
		else if (diceResult == 18) 							{worldDensity = 1.2 + variance;}
	}

	return worldDensity;
}
