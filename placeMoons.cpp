//	This file corresponds to "Step 24: Place Moons"
#include <cstdint>
//	Constant declarations
#include "declarations/constants/worldTypeConstants.h"

//	Function declarations
#include "declarations/functions/diceRoller.h"

//	Gas giants

//	Generate the number of moonlets in the gas giant's first family
int getFirstFamily(float distanceToPrimary)
{
//	Roll for number of moonlets
	int moonletsRoll = diceRoller(6, 2);
//	Modifier for moonletsRoll
	int moonletsRollModifier = 0;

	if 		(distanceToPrimary <= 0.1							   ) {moonletsRollModifier = -10;}
	else if (distanceToPrimary >  0.1  && distanceToPrimary <= 0.5 ) {moonletsRollModifier = -8	;}
	else if (distanceToPrimary >  0.5  && distanceToPrimary <= 0.75) {moonletsRollModifier = -6	;}
	else if (distanceToPrimary >  0.75 && distanceToPrimary <= 1.5 ) {moonletsRollModifier = -3	;}
	else															 {moonletsRollModifier = 0	;}

//	Return the number of moonlets
	return moonletsRoll + moonletsRollModifier;
}

//	See how visible the ring system is
//	0 is not visible, 1 can be seen through a telescope, 2 is comparable to Saturn
int getRingSystemVisibility(int moonlets)
{
	if 		(moonlets <  6				   ) {return 0;}
	else if (moonlets >= 6 && moonlets < 10) {return 1;}
	else 									 {return 2;}
}

int getSecondFamily(float distanceToPrimary)
{
//	Initialize return value
	int numberOfSecondFamilyMoons = 0;

//	If the gas giant is within 0.1 AU of the primary, there are no moons in the second family
	if (distanceToPrimary <= 0.1) {numberOfSecondFamilyMoons = 0;}

	else
	{
		int majorMoonRoll = diceRoller(6, 1);
		int majorMoonRollModifier = 0;

		if 		(distanceToPrimary > 0.1  && distanceToPrimary <= 0.5 ) {majorMoonRollModifier = -5;}
		else if (distanceToPrimary > 0.5  && distanceToPrimary <= 0.75) {majorMoonRollModifier = -4;}
		else if (distanceToPrimary > 0.75 && distanceToPrimary <= 1.5 ) {majorMoonRollModifier = -1;}
		else 															{majorMoonRollModifier =  0;}

		numberOfSecondFamilyMoons = majorMoonRoll + majorMoonRollModifier;
	}

	return numberOfSecondFamilyMoons;
}

int getThirdFamily(float distanceToPrimary)
{
//	Roll for number of moonlets
	int moonletsRoll = 0;
//	Modifier for moonletsRoll
	int moonletsRollModifier = 0;

//	If the gas giant is within 0.5 AU of the primary, there are no moons in the third family
	if (distanceToPrimary <= 0.5) {return 0;}

	else
	{
		moonletsRoll = diceRoller(6, 1);

		if 		(distanceToPrimary > 0.5  && distanceToPrimary <= 0.75) {moonletsRollModifier = -5;}
		else if (distanceToPrimary > 0.75 && distanceToPrimary <= 1.5 ) {moonletsRollModifier = -4;}
		else if (distanceToPrimary > 1.5  && distanceToPrimary <= 3	  ) {moonletsRollModifier = -1;}
		else 															{moonletsRollModifier =  0;}
		return moonletsRoll + moonletsRollModifier;
	}
}

int getTerrestrialMajorMoons(float distanceToPrimary, char worldType)
{
//	Roll for number of major moons
	int majorMoonRoll = 0;
//	Modifier for majorMoonRoll
	int majorMoonRollModifier = 0;

//	If the planet is within 0.5 AU of the primary, there are no moons
	if (distanceToPrimary <= 0.5 || worldType == WT_ASTEROID_BELT) {return 0;}

	else
	{
		majorMoonRoll = diceRoller(6, 1) - 4;

		if 		(distanceToPrimary > 0.5  && distanceToPrimary <= 0.75) {majorMoonRollModifier = -3;}
		else if	(distanceToPrimary > 0.75 && distanceToPrimary <= 1.5 ) {majorMoonRollModifier = -1;}
		else 															{majorMoonRollModifier =  0;}

//		Check world size
		if 		(worldType == WT_TINY_SULFUR 	|| worldType == WT_TINY_ICE 		 || worldType == WT_TINY_SULFUR) 																										{majorMoonRollModifier = -2;}
		else if (worldType == WT_SMALL_HADEAN 	|| worldType == WT_SMALL_ICE 		 || worldType == WT_SMALL_ROCK) 																										{majorMoonRollModifier = -1;}
		else if (worldType == WT_LARGE_AMMONIA || worldType == WT_LARGE_GREENHOUSE || worldType == WT_LARGE_CHTHONIAN || worldType == WT_LARGE_OCEAN || worldType == WT_LARGE_ICE || worldType == WT_LARGE_GARDEN)	{majorMoonRollModifier =  1;}
		else 						 {majorMoonRollModifier =  0;}

		if (majorMoonRoll + majorMoonRollModifier <= 0) {return 0;}
		else											{return majorMoonRoll + majorMoonRollModifier;}
	}
}

int getTerrestrialMoonlets(float distanceToPrimary, char worldType)
{
//	Roll for number of moonlets
	int moonletsRoll = 0;
//	Modifier for moonletsRoll
	int moonletsRollModifier = 0;

//	If the planet is within 0.5 AU of the primary, there are no moons
	if (distanceToPrimary <= 0.5) {return 0;}

	else
	{
		moonletsRoll = diceRoller(6, 1) - 2;

		if 		(distanceToPrimary > 0.5  && distanceToPrimary <= 0.75) {moonletsRollModifier = -3;}
		else if	(distanceToPrimary > 0.75 && distanceToPrimary <= 1.5 ) {moonletsRollModifier = -1;}
		else 															{moonletsRollModifier =  0;}

//		Check world size
		if 		(worldType == WT_TINY_SULFUR || worldType == WT_TINY_ICE || worldType == WT_TINY_SULFUR) 																													{moonletsRollModifier = -2;}
		else if (worldType == WT_SMALL_HADEAN || worldType == WT_SMALL_ICE || worldType == WT_SMALL_ROCK) 																												{moonletsRollModifier = -1;}
		else if (worldType == WT_LARGE_AMMONIA || worldType == WT_LARGE_GREENHOUSE || worldType == WT_LARGE_CHTHONIAN || worldType == WT_LARGE_OCEAN || worldType == WT_LARGE_ICE || worldType == WT_LARGE_GARDEN)	{moonletsRollModifier =  1;}
		else 						 {moonletsRollModifier =  0;}

		if (moonletsRoll + moonletsRollModifier <= 0) {return 0;}
		else										  {return moonletsRoll + moonletsRollModifier;}
	}
}

//	Determine the size of the major moon
int moonSizeTable()
{
//	Roll for size
	int diceRoll = diceRoller(6, 3);

	if 		(diceRoll <= 11					 ) {return -3;}
	else if (diceRoll >= 12 && diceRoll <= 14) {return -2;}
	else 									   {return -1;}
}
