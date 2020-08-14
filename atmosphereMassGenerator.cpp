//	This function returns the mass of the world's atmosphere in terms
//	of the Earth's

#include <string>

#include "declarations/functions/diceRoller.h"
#include "declarations/functions/floatRNG.h"

using namespace std;

float atmosphereMassGenerator(string worldType)
{
	float atmosphereMass;

//	Worlds that have no significant atmosphere
	if ((worldType == "Asteroid Belt") || (worldType == "Tiny (Ice)") || (worldType == "Tiny (Rock)") || (worldType == "Tiny (Sulfur)") || (worldType == "Small (Hadean)") || (worldType == "Small (Rock)") || (worldType == "Standard (Hadean)") || (worldType == "Standard (Chthonian)") || (worldType == "Large (Chthonian)"))
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
