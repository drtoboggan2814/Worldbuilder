//	C+= libraries
#include <iostream>

//	Structure declarations
#include "declarations/structures/star_t.h"

//	Function declarations
#include "declarations/functions/diceRoller.h"
#include "declarations/functions/floatRNG.h"

using namespace std;

//	This function returns the ratio between orbits
float orbitalSpacingTable()
{
	int diceRoll = diceRoller(6, 3);


	float variance = floatRNG(-0.05, 0.05);

	if 		(diceRoll ==  3 || diceRoll == 4 ) {return 1.4 + variance;}
	else if (diceRoll =  5 	|| diceRoll == 6 ) {return 1.5 + variance;}
	else if (diceRoll =  7 	|| diceRoll == 8 ) {return 1.6 + variance;}
	else if (diceRoll >= 9 	&& diceRoll <= 12) {return 1.7 + variance;}
	else if (diceRoll == 13 || diceRoll == 14) {return 1.8 + variance;}
	else if (diceRoll == 15 || diceRoll == 16) {return 1.9 + variance;}
	else									   {return 2.0 + variance;}
}

//	Get the orbital radius of the first world
float getOrbitalRadius(float outermostLegalDistance)
{
	int diceRoll = diceRoller(6, 1);
	return outermostLegalDistance / ((diceRoll * 0.05) + 1);
}

//	This function returns the orbital radii of the primary in ascending order
star_t placePlanetaryOrbits(star_t primary, int numberOfStars, float companionAInnerForbiddenZone, float companionAOuterForbiddenZone, float companionBInnerForbiddenZone, float companionBOuterForbiddenZone, float companionAOrbitalRadius, float companionBOrbitalRadius)
{
//	Keep track of the distance between each orbit
	float distanceBetweenOrbits = 0;
//	Keep track of the planet's distance from the primary
	float distanceFromPrimary = 0;
//	The current ratio between orbits
	float currentOrbitalRatio = 0;
//	The array index of the world closest to the primary
	int innerWorldIndex = 0;

//	If the first gas giant has already been placed, use that orbital radius as the basline for the others
	if (primary.firstGasGiantPresent == true)
	{
		primary.orbitalRadiusArray[0] = primary.firstGasGiantOrbitalRadius;
//		//cout << "primary.firstGasGiantOrbitalRadius = " << primary.firstGasGiantOrbitalRadius << endl;
	}

//	Otherwise, generate the firt planetary orbit
	else
	{
		float divisor;
		if (primary.outerLimitRadius > primary.innerForbiddenZone || primary.innerForbiddenZone == 0) {divisor = primary.outerLimitRadius;}
		else {divisor = primary.innerForbiddenZone;}

		primary.orbitalRadiusArray[0] = getOrbitalRadius(divisor);
	}

//	//cout << "primary.orbitalRadiusArray[0] = " << primary.orbitalRadiusArray[0] << endl;

//	Work inward from the first planet
//	While the distance between orbits is greater than 0.15 AU, the orbital radius of the first world, falls between the star's inner and outer radii, and is not in the forbidden zone
//	Iterate through planetaryOrbits.primary.orbitalRadiusArray
//	Initial distance from primary is the orbit of the first world
	distanceFromPrimary = primary.orbitalRadiusArray[0];
//	Initial distance between orbits is the orbit of the first world
	distanceBetweenOrbits = primary.orbitalRadiusArray[0];

//	Check if the orbit falls in the forbidden zone
//	If there are more than 1 stars and the first orbit is in the forbidden zone
	bool inPrimaryForbiddenZone = (numberOfStars > 1) && (primary.orbitalRadiusArray[0] <= primary.outerForbiddenZone && primary.orbitalRadiusArray[0] >= primary.innerForbiddenZone);
	bool inCompanionAForbiddenZone;
	bool inCompanionBForbiddenZone;
	if (numberOfStars > 1)
	{
/*
		if (primary.starNumber == 0)
		{
			inCompanionAForbiddenZone = ((companionAOrbitalRadius - primary.orbitalRadiusArray[0]) <= companionAOuterForbiddenZone) && ((companionAOrbitalRadius - primary.orbitalRadiusArray[0]) >= companionAInnerForbiddenZone);
		}

		else
		{
			inCompanionAForbiddenZone = ((companionAOrbitalRadius - primary.orbitalRadiusArray[0]) <= companionAOuterForbiddenZone) && ((companionAOrbitalRadius - primary.orbitalRadiusArray[0]) >= companionAInnerForbiddenZone);
		}
*/
		inCompanionAForbiddenZone = ((companionAOrbitalRadius - primary.orbitalRadiusArray[0]) <= companionAOuterForbiddenZone) && ((companionAOrbitalRadius - primary.orbitalRadiusArray[0]) >= companionAInnerForbiddenZone);

		if (numberOfStars == 3)
		{
			inCompanionBForbiddenZone = ((companionBOrbitalRadius - primary.orbitalRadiusArray[0]) <= companionBOuterForbiddenZone) && ((companionBOrbitalRadius - primary.orbitalRadiusArray[0]) >= companionBInnerForbiddenZone);
		}
	}

//	Check if the initial orbit falls between the star's inner and outer radii
	bool inCorrectRadius = (distanceFromPrimary >= primary.innerLimitRadius && distanceFromPrimary <= primary.outerLimitRadius);
//	Check if the initial orbit is less than or equal to the first placed orbit
	bool lessThanFirstOrbit = (distanceFromPrimary <= primary.orbitalRadiusArray[0]) || (distanceFromPrimary == primary.orbitalRadiusArray[0]);

	cout << endl << "INWARD" << endl;

//	cout << "inPrimaryForbiddenZone = " << inPrimaryForbiddenZone << endl;
//	cout << "inCorrectRadius = " << inCorrectRadius << endl;
//	cout << "lessThanFirstOrbit = " << lessThanFirstOrbit << endl;

	for (int index = 1; (distanceBetweenOrbits >= 0.15 && !inPrimaryForbiddenZone && inCorrectRadius && lessThanFirstOrbit); index++)
	{
//		Get the current orbital ratio
		currentOrbitalRatio = orbitalSpacingTable();
//		cout << "currentOrbitalRatio = " << currentOrbitalRatio << endl;
//		Determine the orbital radius
		distanceFromPrimary = primary.orbitalRadiusArray[index - 1] / currentOrbitalRatio;
//		cout << "distanceFromPrimary = " << distanceFromPrimary << endl;
//		Determine the current distance between orbits
		distanceBetweenOrbits = primary.orbitalRadiusArray[index - 1] - distanceFromPrimary;
//		cout << "distanceBetweenOrbits = " << distanceBetweenOrbits << endl;
//		Store the orbital radius in the array
		primary.orbitalRadiusArray[index] = distanceFromPrimary;
//		cout << "primary.orbitalRadiusArray[" << index << "] = " << primary.orbitalRadiusArray[index] << endl;
//		Store the current index
		innerWorldIndex = index;
//		Check if the orbit falls between the star's inner and outer radii
		inCorrectRadius = (distanceFromPrimary >= primary.innerLimitRadius && distanceFromPrimary <= primary.outerLimitRadius);
//		Check if the orbit is less than or equal to the first placed orbit
		lessThanFirstOrbit = (distanceFromPrimary <= primary.orbitalRadiusArray[0]);
//		Check if the orbit is in the forbidden zone
		inPrimaryForbiddenZone = (numberOfStars > 1) && (primary.orbitalRadiusArray[index] <= primary.outerForbiddenZone && primary.orbitalRadiusArray[index] >= primary.innerForbiddenZone);

		if (numberOfStars > 1)
		{
			inCompanionAForbiddenZone = ((companionAOrbitalRadius - primary.orbitalRadiusArray[index]) <= companionAOuterForbiddenZone) && ((companionAOrbitalRadius - primary.orbitalRadiusArray[index]) >= companionAInnerForbiddenZone);

			if (numberOfStars == 3)
			{
				inCompanionBForbiddenZone = ((companionBOrbitalRadius - primary.orbitalRadiusArray[index]) <= companionBOuterForbiddenZone) && ((companionBOrbitalRadius - primary.orbitalRadiusArray[index]) >= companionBInnerForbiddenZone);
			}
		}


//		cout << "inPrimaryForbiddenZone = " << inPrimaryForbiddenZone << endl;
//		cout << "inCorrectRadius = " << inCorrectRadius << endl;
//		cout << "lessThanFirstOrbit = " << lessThanFirstOrbit << endl;


//		If any of the flags turn true, redo the for loop
		if (inPrimaryForbiddenZone == true || inCorrectRadius == false || lessThanFirstOrbit == false || distanceBetweenOrbits < 0.15 || inCompanionAForbiddenZone == true || inCompanionBForbiddenZone == true)
		{
			index - 1;
		}
	}

//	Delete last entry if invalid and subtract one from innerWorldIndex
	if (distanceBetweenOrbits < 0.15)
	{
		primary.orbitalRadiusArray[innerWorldIndex] = 0;
		innerWorldIndex -= 1;
	}

//	cout << "innerWorldIndex = " << innerWorldIndex << endl;

	//cout << endl << "OUTWARD" << endl;
//	Work outward from the first planet placed
//	Generate the orbital radius of the next furthest world from the first placed world
//	Determine the new orbital ratio
	currentOrbitalRatio = orbitalSpacingTable();
//	cout << "currentOrbitalRatio = " << currentOrbitalRatio << endl;
//	Reset the distance from the primary to the first placed orbit
	distanceFromPrimary = primary.orbitalRadiusArray[0] * currentOrbitalRatio;
//	cout << "distanceFromPrimary = " << distanceFromPrimary << endl;
//	Reset the distance between the orbits to factor in the first placed orbit
	distanceBetweenOrbits = distanceFromPrimary - primary.orbitalRadiusArray[0];
//	cout << "distanceBetweenOrbits = " << distanceBetweenOrbits << endl;

//	Last index value (easier than sizeof())
	int outerWorldIndex = 0;

//	Check if the orbit is less than or equal to the first placed orbit
	bool greaterThanFirstOrbit = (distanceFromPrimary >= primary.orbitalRadiusArray[0]) || (distanceFromPrimary == primary.orbitalRadiusArray[0]);

//	Check if the initial orbit falls between the star's inner and outer radii
	inCorrectRadius = (distanceFromPrimary >= primary.innerLimitRadius && distanceFromPrimary <= primary.outerLimitRadius);
//	Check if the initial orbit is less than or equal to the first placed orbit
	lessThanFirstOrbit = (distanceFromPrimary <= primary.orbitalRadiusArray[0]) || (distanceFromPrimary == primary.orbitalRadiusArray[0]);

//	Set the orbital radius of the orbit after the first to distanceBetweenOrbits
	if (distanceBetweenOrbits >= 0.15 && !inPrimaryForbiddenZone && inCorrectRadius && greaterThanFirstOrbit) {primary.orbitalRadiusArray[innerWorldIndex + 1] = distanceFromPrimary;}
//	cout << "primary.orbitalRadiusArray[" << innerWorldIndex + 1 << "] = " << primary.orbitalRadiusArray[innerWorldIndex + 1] << endl;
//	cout << "inPrimaryForbiddenZone = " << inPrimaryForbiddenZone << endl;
//	cout << "inCorrectRadius = " << inCorrectRadius << endl;
//	cout << "greaterThanFirstOrbit = " << greaterThanFirstOrbit << endl;

//	While the distance between orbits is greater than 0.15 AU, the star's inner limit radius, and the first planet's orbital radius and less than the star's outer limit radius and any forbidden zones
	for (int index = innerWorldIndex + 2; (distanceBetweenOrbits >= 0.15 && !inPrimaryForbiddenZone && inCorrectRadius && greaterThanFirstOrbit); index++)
	{
//		Get the current orbital ratio
		currentOrbitalRatio = orbitalSpacingTable();
//		cout << "currentOrbitalRatio = " << currentOrbitalRatio << endl;
//		Determine the orbital radius
		distanceFromPrimary = primary.orbitalRadiusArray[index - 1] * currentOrbitalRatio;
//		cout << "distanceFromPrimary = " << distanceFromPrimary << endl;
//		Determine the current distance between orbits
		distanceBetweenOrbits = distanceFromPrimary - primary.orbitalRadiusArray[index - 1];
//		cout << "distanceBetweenOrbits = " << distanceBetweenOrbits << endl;
//		Store the orbital radius in the array
		primary.orbitalRadiusArray[index] = distanceFromPrimary;
//		cout << "primary.orbitalRadiusArray[" << index << "] = " << primary.orbitalRadiusArray[index] << endl;
//		Store the current index
		outerWorldIndex = index;
//		Check if the orbit falls between the star's inner and outer radii
		inCorrectRadius = (distanceFromPrimary >= primary.innerLimitRadius && distanceFromPrimary <= primary.outerLimitRadius);
//		Check if the orbit is less than or equal to the first placed orbit
		greaterThanFirstOrbit = (distanceFromPrimary > primary.orbitalRadiusArray[0]);
//		Check if the orbit is in the forbidden zone
		inPrimaryForbiddenZone = (numberOfStars > 1) && (primary.orbitalRadiusArray[index] <= primary.outerForbiddenZone && primary.orbitalRadiusArray[index] >= primary.innerForbiddenZone);

//		cout << "inPrimaryForbiddenZone = " << inPrimaryForbiddenZone << endl;
//		cout << "inCorrectRadius = " << inCorrectRadius << endl;
//		cout << "greaterThanFirstOrbit = " << greaterThanFirstOrbit << endl;

		if (numberOfStars > 1)
		{
			inCompanionAForbiddenZone = ((companionAOrbitalRadius - primary.orbitalRadiusArray[index]) <= companionAOuterForbiddenZone) && ((companionAOrbitalRadius - primary.orbitalRadiusArray[index]) >= companionAInnerForbiddenZone);

			if (numberOfStars == 3)
			{
				inCompanionBForbiddenZone = ((companionBOrbitalRadius - primary.orbitalRadiusArray[index]) <= companionBOuterForbiddenZone) && ((companionBOrbitalRadius - primary.orbitalRadiusArray[index]) >= companionBInnerForbiddenZone);
			}
		}

//		If any of the flags turn true, redo the for loop
		if (inPrimaryForbiddenZone == true || inCorrectRadius == false || greaterThanFirstOrbit == false || greaterThanFirstOrbit < 0.15 || inCompanionAForbiddenZone == true || inCompanionBForbiddenZone == true)
		{
			index - 1;
		}
	}
//	cout << "outerWorldIndex = " << outerWorldIndex << endl;

//	outerWorldIndex holds the index of the last orbit placed, so it also gives the number of orbits
	primary.numberOfOrbits = (innerWorldIndex >= outerWorldIndex) ? innerWorldIndex : outerWorldIndex;
//	Sort orbital radii in ascending order
//	Temp value for sorting
	float tempValue;
	for (int i = 0; i < outerWorldIndex + 1; i++)
	{
		for (int j = i + 1; j < outerWorldIndex + 1; j++)
		{
			tempValue = primary.orbitalRadiusArray[i];
			primary.orbitalRadiusArray[i] = primary.orbitalRadiusArray[j];
			primary.orbitalRadiusArray[j] = tempValue;
		}
	}

	return primary;
}
