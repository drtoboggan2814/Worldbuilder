//	Constant declarations
#include "declarations/constants/gasGiantArrangementConstants.h"

//	Function declarations
#include "declarations/functions/diceRoller.h"

/*
	These functions determine the characteristics of the gas giant closest to
	the primary in this system.
*/
char gasGiantArrangementTable()
{
	int diceRoll = diceRoller(6, 3);

	if (diceRoll <= 10) {return GGA_NO_GAS_GIANT;}
	else if (diceRoll == 11 || diceRoll == 12) {return GGA_CONVENTIONAL_GAS_GIANT;}
	else if (diceRoll == 13 || diceRoll == 14) {return GGA_ECCENTRIC_GAS_GIANT;}
	else {return GGA_EPISTELLAR_GAS_GIANT;}
}

//	This function returns the orbital radius of the first gas giant in the system
float placeFirstGasGiant(float snowLineRadius, char gasGiantType)
{
	int diceRoll;
	if (gasGiantType == GGA_CONVENTIONAL_GAS_GIANT)
	{
		diceRoll = diceRoller(6, 2) - 2;
		return ((0.05 * diceRoll) + 1) * snowLineRadius;
	}

	else if (gasGiantType == GGA_ECCENTRIC_GAS_GIANT)
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
