//	C++ libraries
#include <iostream>

//	Constant declarations
#include "declarations/constants/planetaryOrbitalEccentricityTableConstants.h"

//	Function declarations
#include "declarations/functions/diceRoller.h"
#include "declarations/functions/floatRNG.h"
#include "declarations/functions/generateWorldDetails.h"

//	Structure declarations
#include "declarations/structures/star_t.h"

//	Determine the number of jump points around the star
int getNumberOfJumpPoints()
{
	int diceRoll = diceRoller(100, 1);
	if 		(diceRoll >= 1 	&& diceRoll <= 15)	{return 1;}
	else if (diceRoll >= 16 && diceRoll <= 55)	{return 2;}
	else if (diceRoll >= 56 && diceRoll <= 76)	{return 3;}
	else if (diceRoll >= 77 && diceRoll <= 92)	{return 4;}
	else										{return (4 + diceRoller(4, 1));}
}

//	Determine the ratio between orbits
float jumpPointOrbitalSpacingTable()
{
	float variance = floatRNG(-0.025, 0.025);
	int diceRoll = diceRoller(6, 3);
	if 		(diceRoll == 3 	|| diceRoll == 4 ) {return 1.05 + variance;}
	else if (diceRoll =  5 	|| diceRoll == 6 ) {return 1.10 + variance;}
	else if (diceRoll =  7 	|| diceRoll == 8 ) {return 1.15 + variance;}
	else if (diceRoll >= 9 	&& diceRoll <= 12) {return 1.20 + variance;}
	else if (diceRoll == 13 || diceRoll == 14) {return 1.25 + variance;}
	else if (diceRoll == 15 || diceRoll == 16) {return 1.30 + variance;}
	else									   {return 1.35 + variance;}
}

star_t assignJumpPointDetails(star_t& primary, int i, int jumpPointArrayIndex, bool belowSnowLine)
{
	int diceRoll = diceRoller(6, 3);
	std::cout << "Entered assignJumpPointDetails" << std::endl;
	primary.jumpPointArray[jumpPointArrayIndex].semiMajorAxis = belowSnowLine ? (primary.orbitalRadiusArray[i] / jumpPointOrbitalSpacingTable()) : (primary.orbitalRadiusArray[i] * jumpPointOrbitalSpacingTable());
	std::cout << "primary.jumpPointArray[" << jumpPointArrayIndex << "].semiMajorAxis == " << primary.jumpPointArray[jumpPointArrayIndex].semiMajorAxis << std::endl;
	primary.jumpPointArray[jumpPointArrayIndex].eccentricity = planetaryOrbitalEccentricityTable(diceRoll);
	std::cout << "primary.jumpPointArray[" << jumpPointArrayIndex << "].eccentricity == " << primary.jumpPointArray[jumpPointArrayIndex].eccentricity << std::endl;
	primary.jumpPointArray[jumpPointArrayIndex].minimumSeparation = calculatePlanetPrimaryMinimumSeparation(primary.jumpPointArray[jumpPointArrayIndex].semiMajorAxis, primary.jumpPointArray[jumpPointArrayIndex].eccentricity);
	std::cout << "primary.jumpPointArray[" << jumpPointArrayIndex << "].minimumSeparation == " << primary.jumpPointArray[jumpPointArrayIndex].minimumSeparation << std::endl;
	primary.jumpPointArray[jumpPointArrayIndex].maximumSeparation = calculatePlanetPrimaryMaximumSeparation(primary.jumpPointArray[jumpPointArrayIndex].semiMajorAxis, primary.jumpPointArray[jumpPointArrayIndex].eccentricity);
	std::cout << "primary.jumpPointArray[" << jumpPointArrayIndex << "].maximumSeparation == " << primary.jumpPointArray[jumpPointArrayIndex].maximumSeparation << std::endl;

	return primary;
}

star_t placeJumpPointOrbits(star_t& primary)
{
	std::cout << "\nEnterred placeJumpPointOrbits" << std::endl;
//	Get number of jump points
	primary.numberofJumpPoints = getNumberOfJumpPoints();
//	Maximum number of jump points is equal to primary.numberOfOrbits
	primary.numberofJumpPoints = primary.numberofJumpPoints <= primary.numberOfOrbits ? primary.numberofJumpPoints : primary.numberOfOrbits;
	std::cout << "primary.numberofJumpPoints == " << primary.numberofJumpPoints << std::endl;
	std::cout << "primary.snowLineRadius == " << primary.snowLineRadius << std::endl;
	int jumpPointArrayIndex = 0;
	int firstBelowSnowLine = 0;
//	Find the last orbit before the snow line
//	Worlds (and orbits) are in descending order
	for (int i = 0; i < primary.numberOfOrbits; i++)
	{
		std::cout << "i == " << i << std::endl;
		std::cout << "primary.orbitalRadiusArray[" << i << "] == " << primary.orbitalRadiusArray[i] << std::endl;
//		If the orbit is below the snow line
		if (primary.orbitalRadiusArray[i] <= primary.snowLineRadius)
		{
			std::cout << "primary.orbitalRadiusArray[" << i << "] is less than primary.snowLineRadius" << std::endl;
			if (jumpPointArrayIndex == 0)	{firstBelowSnowLine = i;}
			primary = assignJumpPointDetails(primary, i, jumpPointArrayIndex, true);
			jumpPointArrayIndex++;
		}
		std::cout << "jumpPointArrayIndex == " << jumpPointArrayIndex << std::endl;
//		Break if all jump points have been placed or there are no slots left
		if (jumpPointArrayIndex == primary.numberofJumpPoints || primary.orbitalRadiusArray[i + 1] == 0)	{break;}
	}

//	If there are leftover jump points but the number of inward slots has run out
	if (jumpPointArrayIndex < primary.numberofJumpPoints)
	{
		std::cout << "Outwards from the snow line" << std::endl;
		std::cout << "jumpPointArrayIndex == " << jumpPointArrayIndex << std::endl;

//		If no orbits were found below the snow line
		if (firstBelowSnowLine == 0 && jumpPointArrayIndex == 0)
		{
//			Work outwards from the orbit closest to the star
			for (int i = (primary.numberOfOrbits - 1); i > -1; i--)
			{
				std::cout << "primary.orbitalRadiusArray[" << i << "] is greater than primary.snowLineRadius" << std::endl;
				primary = assignJumpPointDetails(primary, i, jumpPointArrayIndex, false);
				jumpPointArrayIndex++;
				if (jumpPointArrayIndex == primary.numberofJumpPoints || primary.orbitalRadiusArray[i + 1] == 0)	{break;}
			}
		}

		else if (jumpPointArrayIndex != 0)
		{
	//		Work backwards from the first orbit after the snowline
			for (int i = (firstBelowSnowLine - 1); i > -1; i--)
			{
				primary = assignJumpPointDetails(primary, i, jumpPointArrayIndex, false);
				jumpPointArrayIndex++;
	//			Break if all jump points have been placed or there are no slots left
				if (jumpPointArrayIndex == primary.numberofJumpPoints)	{break;}
			}
		}

	}

	//	Sort orbital radii in ascending order
	//	Temp value for sorting
		jumpPoint_t tempValue;
		for (int i = 0; i < primary.numberofJumpPoints; i++)
		{
			for (int j = i + 1; j < primary.numberofJumpPoints; j++)
			{
				tempValue = primary.jumpPointArray[i];
				primary.jumpPointArray[i] = primary.jumpPointArray[j];
				primary.jumpPointArray[j] = tempValue;
			}
		}
	return primary;
}
