#include <string>

#include "declarations/functions/diceRoller.h"

using namespace std;

/*
	These functions determine the characteristics of the gas giant closest to
	the primary in this system.
*/
string gasGiantArrangementTable()
{
	int diceRoll = diceRoller(6, 3);

	if (diceRoll <= 10) {return "No Gas Giant";}
	else if (diceRoll == 11 || diceRoll == 12) {return "Conventional Gas Giant";}
	else if (diceRoll == 13 || diceRoll == 14) {return "Eccentric Gas Giant";}
	else {return "Epistellar Gas Giant";}
}

//	This function returns the orbital radius of the first gas giant in the system
float placeFirstGasGiant(float snowLineRadius, string gasGiantType)
{
	int diceRoll;
	if (gasGiantType == "Conventional Gas Giant")
	{
		diceRoll = diceRoller(6, 2) - 2;
		return ((0.05 * diceRoll) + 1) * snowLineRadius;
	}

	else if (gasGiantType == "Eccentric Gas Giant")
	{
		diceRoll = diceRoller(6, 1);
		return (diceRoll * 0.125) * snowLineRadius;
	}

	else
	{
		diceRoll = diceRoller(6, 3);
		return (diceRoll * 0.1) * snowLineRadius;
	}
}
