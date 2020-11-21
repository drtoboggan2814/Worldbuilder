#include "declarations/functions/diceRoller.h"

//	Return the base age of the star
float getBaseAge(int diceRoll)
{
	if 		(diceRoll == 3) 					{return 0;}
	else if (diceRoll >= 4 && diceRoll <= 6) 	{return 0.1;}
	else if (diceRoll >= 7 && diceRoll <= 10) 	{return 2;}
	else if (diceRoll >= 11 && diceRoll <= 14) 	{return 5.6;}
	else if (diceRoll >= 15 && diceRoll <= 17) 	{return 8;}
	else 										{return 10;}
}

//	Return the step-a modifier
float getStepA(int diceRoll)
{
	if 		(diceRoll == 3) 					{return 0;}
	else if (diceRoll >= 4 && diceRoll <= 6) 	{return 0.3;}
	else 										{return 0.6;}
}

//	Return the step-b modifier
float getStepB(int diceRoll)
{
	if 		(diceRoll == 3) 					{return 0;}
	else if (diceRoll >= 4 && diceRoll <= 6) 	{return 0.05;}
	else 										{return 0.1;}
}

float stellarAgeTable(bool gardenWorldPresent)
{
	int firstRoll, secondRoll, thirdRoll;
	float stellarMass, variance, baseAge, stepA, stepB;

//	If there is a garden world present in this system, roll 2d6+2
	if (gardenWorldPresent == true)
	{
		firstRoll = diceRoller(6, 2) + 2;
	}

//	If not, roll 3d6+2
	else
	{
		firstRoll = diceRoller(6, 3);
	}

//	Roll for steps a and b
	secondRoll = diceRoller(6, 1) - 1;
	thirdRoll = diceRoller(6, 1) - 1;

//	Get the star's base age
	baseAge = getBaseAge(firstRoll);

//	Get the modifiers
	stepA = getStepA(firstRoll) * secondRoll;
	stepB = getStepB(firstRoll) * thirdRoll;

//	Return the age of the star
	return baseAge + stepA + stepB;
}
