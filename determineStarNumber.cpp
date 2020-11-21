#include "declarations/functions/diceRoller.h"

int determineStarNumber()
{
	int diceRoll = diceRoller(6, 3);
	char numberOfStars;

	if 		(diceRoll >= 3 	&& diceRoll <= 10) 	{numberOfStars = 1;}
	else if (diceRoll >= 11 && diceRoll <= 15) 	{numberOfStars = 2;}
	else 										{numberOfStars = 3;}

	return numberOfStars;
}
