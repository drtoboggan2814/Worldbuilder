//	This function returns the mass of the world's atmosphere in terms
//	of the Earth's

//	Constant declarations
#include "declarations/constants/worldTypeConstants.h"

//	Function declarations
#include "declarations/functions/diceRoller.h"
#include "declarations/functions/floatRNG.h"

float atmosphereMassGenerator(const char& worldType)
{
	float atmosphereMass;

//	Worlds that have no significant atmosphere
	if ((worldType == WT_ASTEROID_BELT) || (worldType == WT_TINY_ICE) || (worldType == WT_TINY_SULFUR) || (worldType == WT_TINY_SULFUR) || (worldType == WT_SMALL_HADEAN) || (worldType == WT_SMALL_ROCK) || (worldType == WT_STANDARD_HADEAN) || (worldType == WT_STANDARD_CHTHONIAN) || (worldType == WT_LARGE_CHTHONIAN))
	{
		atmosphereMass = 0;
	}

//	Worlds that can have an atmosphere
	else
	{
//		Roll 3d6
		int diceRoll = diceRoller(6, 3);
//		Generate variance
		float variance = floatRNG(-0.05, 0.05);
//		Divide the dice roll by 10 and add the variance
		atmosphereMass = (diceRoll / 10) + variance;

//		If atmosphereMass is negative
		if (atmosphereMass < 0) {atmosphereMass = 0;}
	}

	return atmosphereMass;
}
