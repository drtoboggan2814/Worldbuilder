/*
	This function corresponds to the orbital separation table in "Step 19: Companion Star Orbits".
	This function only applies to star systems with more than one star.
	The function takes the number of stars in the system, the presence of a
	garden world, and the number of companion stars in the system as parameters.
	It returns the minimum and maximum separation of the star from the primary in AU's.
*/

#include <iostream>
using namespace std;

//	Structure declarations
#include "declarations/structures/world_t.h"
#include "declarations/structures/star_t.h"
#include "declarations/structures/starSystem_t.h"

//	Function declarations
#include "declarations/functions/diceRoller.h"

float getRadiusMultiplier(int diceRoll)
{
//	Initialize return value
	float radiusMultiplier = 0;
	if 		(diceRoll <= 6) 					{radiusMultiplier = 0.05;}
	else if (diceRoll >= 7 && diceRoll <= 9) 	{radiusMultiplier = 0.5;}
	else if (diceRoll == 10 || diceRoll == 11) 	{radiusMultiplier = 2;}
	else if (diceRoll >= 12 && diceRoll <= 14) 	{radiusMultiplier = 10;}
	else 										{radiusMultiplier = 50;}

	return radiusMultiplier;
}

float getEccentricity(int diceRoll)
{
	float eccentricity = 0;
	if 		(diceRoll <= 3) 					{eccentricity = 0;}
	else if (diceRoll == 4) 					{eccentricity = 0.1;}
	else if (diceRoll == 5) 					{eccentricity = 0.2;}
	else if (diceRoll == 6) 					{eccentricity = 0.3;}
	else if (diceRoll == 7 || diceRoll == 8) 	{eccentricity = 0.4;}
	else if (diceRoll >= 9 && diceRoll <= 11) 	{eccentricity = 0.5;}
	else if (diceRoll == 12 || diceRoll == 13) 	{eccentricity = 0.6;}
	else if (diceRoll == 14 || diceRoll == 15) 	{eccentricity = 0.7;}
	else if (diceRoll == 16) 					{eccentricity = 0.8;}
	else if (diceRoll == 17) 					{eccentricity = 0.9;}
	else 										{eccentricity = 0.95;}

	return eccentricity;
}

//	Determine the star's orbital eccentricity and its minimum, maximum, and average orbital separations from its primary
star_t orbitalSeparationTable(char numberOfStars, int companionStar, star_t& primary, bool gardenWorldPresent)
{
//	The first roll gives the general idea of how widely separated the primary is from its companion
	int firstRoll;
//	The second roll determines the average radius for that separation
	int secondRoll;
//	The third roll determines the eccentricity of the two stars
	int thirdRoll;

//	Roll the dice
	firstRoll = diceRoller(6, 3);
	secondRoll = diceRoller(6, 2);
	thirdRoll = diceRoller(6, 3);

//	If there is a garden world present in-system
	if (gardenWorldPresent == true) {firstRoll += 4;}

//	If the system is trinary and the current star is the second companion
	if (numberOfStars == 3 && companionStar == 2) {firstRoll += 6;}

//	If the two stars are very close
	if (firstRoll <= 6) {thirdRoll += -6;}
//	If the two stars are close
	else if (firstRoll >= 7 && firstRoll <= 9) {thirdRoll += -4;}
//	If the two stars have a moderate separation
	else if (firstRoll == 10 || firstRoll == 11) {thirdRoll += -2;}

//	Calculate the orbital eccentricity
//	std::cout << "\norbitalSeparationTable" << std::endl;
	primary.orbitalEccentricity = getEccentricity(thirdRoll);
//	std::cout << "star " << companionStar << " orbitalEccentricity == " << primary.orbitalEccentricity << std::endl;
//	Calculate the average orbital radius
	primary.averageOrbitalRadius = getRadiusMultiplier(secondRoll) * secondRoll;
//	std::cout << "star " << companionStar << " averageOrbitalRadius == " << primary.averageOrbitalRadius << std::endl;
//	Calculate the minimum orbital radius
	primary.minSeparationToCompanion = (1 - getEccentricity(thirdRoll)) * (getRadiusMultiplier(thirdRoll) * secondRoll);
//	std::cout << "star " << companionStar << " minSeparationToCompanion == " << primary.minSeparationToCompanion << std::endl;
//	Calculate the maximum orbital radius
	primary.maxSeparationToCompanion = (1 + getEccentricity(thirdRoll)) * (getRadiusMultiplier(thirdRoll) * secondRoll);
//	std::cout << "star " << companionStar << " maxSeparationToCompanion == " << primary.maxSeparationToCompanion << std::endl;
//	Calculate the inner forbidden zone
	primary.innerForbiddenZone = primary.minSeparationToCompanion / 3;
//	std::cout << "star " << companionStar << " innerForbiddenZone == " << primary.innerForbiddenZone << std::endl;
//	Calculate the outer forbidden zone
	primary.outerForbiddenZone = primary.maxSeparationToCompanion * 3;
//	std::cout << "star " << companionStar << " outerForbiddenZone == " << primary.outerForbiddenZone << "\n" << std::endl;

	return primary;
}

starSystem_t companionStarOrbits(starSystem_t& starSystem)
{
	if (starSystem.numberOfStars == 2)
	{
//		Roll on orbitalSeparationTable for the companion
		starSystem.stars[1] = orbitalSeparationTable(starSystem.numberOfStars, 1, starSystem.stars[1], starSystem.gardenWorldPresent);
//		Set the min and max distances from the companion to the primary
		starSystem.stars[0].minSeparationToCompanion = starSystem.stars[1].minSeparationToCompanion;
		starSystem.stars[0].maxSeparationToCompanion = starSystem.stars[1].maxSeparationToCompanion;
//		Calculate the primary's forbidden zone
		starSystem.stars[0].innerForbiddenZone = starSystem.stars[1].minSeparationToCompanion / 3;
		starSystem.stars[0].outerForbiddenZone = starSystem.stars[1].maxSeparationToCompanion * 3;
	//	std::cout << "COMPANIONSTARORBITS IS BEING CALLED" << std::endl;
	//	std::cout << "starSystem.stars[0].innerForbiddenZone = " << starSystem.stars[0].innerForbiddenZone << std::endl;
	//	std::cout << "starSystem.stars[0].outerForbiddenZone = " << starSystem.stars[0].outerForbiddenZone << std::endl;
	//	std::cout << "starSystem.stars[1].innerForbiddenZone = " << starSystem.stars[1].innerForbiddenZone << std::endl;
	//	std::cout << "starSystem.stars[1].outerForbiddenZone = " << starSystem.stars[1].outerForbiddenZone << std::endl;
	//	std::cout << "starSystem.stars[0].minSeparationToCompanion = " << starSystem.stars[0].minSeparationToCompanion << std::endl;
	//	std::cout << "starSystem.stars[0].maxSeparationToCompanion = " << starSystem.stars[0].maxSeparationToCompanion << std::endl;
	//	std::cout << "starSystem.stars[1].minSeparationToCompanion = " << starSystem.stars[1].minSeparationToCompanion << std::endl;
	//	std::cout << "starSystem.stars[1].maxSeparationToCompanion = " << starSystem.stars[1].maxSeparationToCompanion << std::endl;
		starSystem.stars[0].innerForbiddenZone = starSystem.stars[1].outerForbiddenZone;
		starSystem.stars[0].outerForbiddenZone = starSystem.stars[1].innerForbiddenZone;
		return starSystem;
	}

	else if (starSystem.numberOfStars == 3)
	{
	//	std::cout << "COMPANIONSTARORBITS IS BEING CALLED" << std::endl;
		starSystem.stars[2] = orbitalSeparationTable(starSystem.numberOfStars, 2, starSystem.stars[2], starSystem.gardenWorldPresent);
		starSystem.stars[1] = orbitalSeparationTable(starSystem.numberOfStars, 1, starSystem.stars[1], starSystem.gardenWorldPresent);
		starSystem.stars[0].innerForbiddenZone = starSystem.stars[1].outerForbiddenZone;
		starSystem.stars[0].outerForbiddenZone = starSystem.stars[1].innerForbiddenZone;
	//	std::cout << "starSystem.stars[0].minSeparationToCompanion = " << starSystem.stars[0].minSeparationToCompanion << std::endl;
	//	std::cout << "starSystem.stars[0].maxSeparationToCompanion = " << starSystem.stars[0].maxSeparationToCompanion << std::endl;
	//	std::cout << "starSystem.stars[1].minSeparationToCompanion = " << starSystem.stars[1].minSeparationToCompanion << std::endl;
	//	std::cout << "starSystem.stars[1].maxSeparationToCompanion = " << starSystem.stars[1].maxSeparationToCompanion << std::endl;
	//	std::cout << "starSystem.stars[2].minSeparationToCompanion = " << starSystem.stars[2].minSeparationToCompanion << std::endl;
	//	std::cout << "starSystem.stars[2].maxSeparationToCompanion = " << starSystem.stars[2].maxSeparationToCompanion << std::endl;
		return starSystem;
	}

	else
	{
//		Set the min and max distances from the companion to the primary
		starSystem.stars[0].minSeparationToCompanion = 0;
		starSystem.stars[0].maxSeparationToCompanion = 0;
//		Calculate the primary's forbidden zone
		starSystem.stars[0].innerForbiddenZone = 0;
		starSystem.stars[0].outerForbiddenZone = 0;
	//	std::cout << "COMPANIONSTARORBITS IS BEING CALLED" << std::endl;
	//	std::cout << "starSystem.stars[0].minSeparationToCompanion = " << starSystem.stars[0].minSeparationToCompanion << std::endl;
	//	std::cout << "starSystem.stars[0].maxSeparationToCompanion = " << starSystem.stars[0].maxSeparationToCompanion << std::endl;
		return starSystem;
	}
}
