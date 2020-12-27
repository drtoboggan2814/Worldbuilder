//	C++ libraries
#include <cstdint>
//#include <iostream>

//	Function declarations
#include "declarations/functions/diceRoller.h"

uint8_t csv_DetermineStarCount(const int& comp1, const int& comp2, const int& comp3)
{
//	Initialize return value
	uint8_t csv_StarCount;
/*	std::cout << "comp1 == " << comp1 << std::endl;
	std::cout << "comp2 == " << comp2 << std::endl;
	std::cout << "comp3 == " << comp3 << std::endl;
*/
//	Check for trinary system
	if (comp1 == 1 && comp2 == 2 && comp3 == 3)	{csv_StarCount = 3;}
//	Check for binary system
	else if (comp1 == 1 && comp2 == 2)			{csv_StarCount = 2;}
//	Otherwise, the system has one star
	else										{csv_StarCount = 1;}

//	std::cout << "csv_StarCount == " << csv_StarCount << std::endl;

	return csv_StarCount;
}

uint8_t determineStarNumber()
{
	int diceRoll = diceRoller(6, 3);
	uint8_t numberOfStars;

	if 		(diceRoll >= 3 	&& diceRoll <= 10) 	{numberOfStars = 1;}
	else if (diceRoll >= 11 && diceRoll <= 15) 	{numberOfStars = 2;}
	else 										{numberOfStars = 3;}

	return numberOfStars;
}
