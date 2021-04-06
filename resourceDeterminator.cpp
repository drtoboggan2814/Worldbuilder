/*
	This function corresponds to "Determining Resources" in "Step 7: Resources and Habitability".
	It takes the world's type as a parameter.
	It returns the world's resource value modifier.
*/
//	C++ libraries
#include <cstdint>
#include <string>

//	Constant declarations
#include "declarations/constants/worldTypeConstants.h"

//	Function declarations
#include "declarations/functions/diceRoller.h"

using namespace std;

int resourceDeterminator(char worldType)
{
	int resourceValueModifier = 0;
	int diceRoll = diceRoller(6, 3);

	if (worldType == WT_ASTEROID_BELT)
	{
		if 		(diceRoll == 3) 					{resourceValueModifier = -5	;}
		else if (diceRoll == 4) 					{resourceValueModifier = -4	;}
		else if (diceRoll == 5) 					{resourceValueModifier = -3	;}
		else if (diceRoll == 6 	|| diceRoll == 7) 	{resourceValueModifier = -2	;}
		else if (diceRoll == 8 	|| diceRoll == 9) 	{resourceValueModifier = -1	;}
		else if (diceRoll == 10 || diceRoll == 11) 	{resourceValueModifier =  0	;}
		else if (diceRoll == 12 || diceRoll == 13) 	{resourceValueModifier =  1	;}
		else if (diceRoll == 14 || diceRoll == 15) 	{resourceValueModifier =  2	;}
		else if (diceRoll == 16) 					{resourceValueModifier =  3	;}
		else if (diceRoll == 17) 					{resourceValueModifier =  4	;}
		else if (diceRoll == 18) 					{resourceValueModifier =  5	;}
	}

	else
	{
		if		(diceRoll <= 2)						{resourceValueModifier = -3 ;}
		else if (diceRoll == 3	|| diceRoll == 4)	{resourceValueModifier = -2 ;}
		else if (diceRoll >= 5	&& diceRoll <= 7)	{resourceValueModifier = -1 ;}
		else if (diceRoll >= 8	&& diceRoll <= 13)	{resourceValueModifier =  0 ;}
		else if (diceRoll >= 14	&& diceRoll <= 16)	{resourceValueModifier =  1 ;}
		else if (diceRoll >= 17	&& diceRoll <= 18)	{resourceValueModifier =  2 ;}
		else if (diceRoll >= 19)					{resourceValueModifier =  3 ;}
	}

	return resourceValueModifier;
}
