//	C+= libraries
#include <iostream>
#include <string>

//	Constant declarations
#include "declarations/constants/csvLengthConstants.h"

//	Structure declarations
#include "declarations/structures/star_t.h"

//	Function declarations
#include "declarations/functions/diceRoller.h"
#include "declarations/functions/floatRNG.h"
#include "declarations/functions/placingFirstPlanets.h"

//	Third party
#include "declarations/third_party/rapidcsv.h"

//	using namespace std;

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
star_t placePlanetaryOrbits(star_t& primary, rapidcsv::Document& worldDoc, bool randomStar, char numberOfStars, float companionAInnerForbiddenZone, float companionAOuterForbiddenZone, float companionBInnerForbiddenZone, float companionBOuterForbiddenZone, float companionAOrbitalRadius, float companionBOrbitalRadius)
{
//	Keep track of the distance between each orbit
	float distanceBetweenOrbits = 0;
//	Keep track of the planet's distance from the primary
	float distanceFromPrimary = 0;
//	The current ratio between orbits
	float currentOrbitalRatio = 0;
//	The array index of the world closest to the primary
	int innerWorldIndex = 0;
	std::cout << "primary.innerForbiddenZone == " << primary.innerForbiddenZone << std::endl;
	std::cout << "primary.outerLimitRadius == " << primary.outerLimitRadius << std::endl;
//	If the star is generated randomly
	int orbitalRadiusIndex = 0;
	bool matchWasFound = false;
	if (randomStar == true)
	{
		orbitalRadiusIndex = 0;
//		If the first gas giant has already been placed, use that orbital radius as the basline for the others
		if (primary.firstGasGiantPresent == true)
		{
			primary.orbitalRadiusArray[0] = primary.firstGasGiantOrbitalRadius;
		}

//		Otherwise, generate the firt planetary orbit
		else
		{
			float divisor = 0;
			if (primary.outerLimitRadius > primary.innerForbiddenZone || primary.innerForbiddenZone == 0) {divisor = primary.outerLimitRadius;}
			else {divisor = primary.innerForbiddenZone;}

			primary.orbitalRadiusArray[0] = getOrbitalRadius(divisor);
		}
	}

//	If the star is generated from a .csv
	else
	{
		std::cout << "\nEntered .csv placePlanetaryOrbits" << std::endl;
//		Initialize index
		orbitalRadiusIndex = 0;
		//		If the star has a gas giant
		if (primary.firstGasGiantPresent == true)
		{
			std::cout << "primary.firstGasGiantPresent == true" << std::endl;
			primary.orbitalRadiusArray[0] = primary.firstGasGiantOrbitalRadius;
			orbitalRadiusIndex = 1;
		}

		else
		{
			std::cout << "primary.firstGasGiantPresent == false" << std::endl;
			float divisor = 0;
			std::cout << "primary.innerForbiddenZone == " << primary.innerForbiddenZone << std::endl;
			std::cout << "primary.outerLimitRadius == " << primary.outerLimitRadius << std::endl;
			if (primary.outerLimitRadius > primary.innerForbiddenZone || primary.innerForbiddenZone == 0) {divisor = primary.outerLimitRadius;}
			else {divisor = primary.innerForbiddenZone;}
			std::cout << "divisor == " << divisor << std::endl;
			primary.orbitalRadiusArray[0] = getOrbitalRadius(divisor);
			std::cout << "primary.orbitalRadiusArray[0] == " << primary.orbitalRadiusArray[0] << std::endl;
		}


/*
//		Go through worldDoc and check if a terrestrial world is in the system

		for (int i = 0; i < WORLDDOC_LENGTH; i++)
		{
//			If a match is found
			if (csv_starWorldMatch(worldDoc, std::to_string(primary.hipIndex), std::to_string(primary.hdIndex), primary.glieseIndex, primary.properName) == true)
			{
				matchWasFound = true;
				std::cout << "\nA match between starDoc and worldDoc has been found" << std::endl;
//				Assign worlds to star
				if (worldDoc.GetCell<std::string>("pl_letter", i) == "b")
				{
//					Assign orbital radius
					primary.orbitalRadiusArray[orbitalRadiusIndex] = worldDoc.GetCell<float>("pl_orbsmax", i);
//					Record the world's index in the worldDoc
					primary.worldArray[orbitalRadiusIndex].planetDBIndex = i;
//					Record the orbitalRadiusIndex as preplaced
					primary.preplacedWorldIndex[0] = orbitalRadiusIndex;
					primary.preplacedWorldPlanetDBIndex[0] = i;
//					Check for other worlds in the system
//					Check for out of bounds
					if (i + 1 < WORLDDOC_LENGTH)
					{
						if (worldDoc.GetCell<std::string>("pl_letter", i + 1) == "c")
						{
//							Assign orbital radius
							primary.orbitalRadiusArray[orbitalRadiusIndex] = worldDoc.GetCell<float>("pl_orbsmax", i + 1);
//							Record the world's index in the worldDoc
							primary.worldArray[orbitalRadiusIndex].planetDBIndex = i + 1;
							primary.preplacedWorldIndex[1] = orbitalRadiusIndex;
							primary.preplacedWorldPlanetDBIndex[1] = i;
							orbitalRadiusIndex = 2;
//							Check for out of bounds
							if (i + 2 < WORLDDOC_LENGTH)
							{
								if (worldDoc.GetCell<std::string>("pl_letter", i + 2) == "d")
								{
//									Assign orbital radius
									primary.orbitalRadiusArray[orbitalRadiusIndex] = worldDoc.GetCell<float>("pl_orbsmax", i + 2);
//									Record the world's index in the worldDoc
									primary.worldArray[orbitalRadiusIndex].planetDBIndex = i + 2;
									primary.preplacedWorldIndex[2] = orbitalRadiusIndex;
									primary.preplacedWorldPlanetDBIndex[2] = i;
									orbitalRadiusIndex = 3;
//									Check for out of bounds
									if (i + 3 < WORLDDOC_LENGTH)
									{
										if (worldDoc.GetCell<std::string>("pl_letter", i + 3) == "e")
										{
//											Assign orbital radius
											primary.orbitalRadiusArray[orbitalRadiusIndex] = worldDoc.GetCell<float>("pl_orbsmax", i + 3);
//											Record the world's index in the worldDoc
											primary.worldArray[orbitalRadiusIndex].planetDBIndex = i + 3;
											primary.preplacedWorldIndex[3] = orbitalRadiusIndex;
											primary.preplacedWorldPlanetDBIndex[3] = i;
											orbitalRadiusIndex = 4;
//											Check for out of bounds
											if (i + 4 < WORLDDOC_LENGTH)
											{
												if (worldDoc.GetCell<std::string>("pl_letter", i + 4) == "f")
												{
				//									Assign orbital radius
													primary.orbitalRadiusArray[orbitalRadiusIndex] = worldDoc.GetCell<float>("pl_orbsmax", i + 4);
				//									Record the world's index in the worldDoc
													primary.worldArray[orbitalRadiusIndex].planetDBIndex = i + 4;
													primary.preplacedWorldIndex[4] = orbitalRadiusIndex;
													primary.preplacedWorldPlanetDBIndex[4] = i;
													orbitalRadiusIndex = 5;
//													Check for out of bounds
													if (i + 5 < WORLDDOC_LENGTH)
													{
														if (worldDoc.GetCell<std::string>("pl_letter", i + 5) == "g")
														{
					//										Assign orbital radius
															primary.orbitalRadiusArray[orbitalRadiusIndex] = worldDoc.GetCell<float>("pl_orbsmax", i + 5);
					//										Record the world's index in the worldDoc
															primary.worldArray[orbitalRadiusIndex].planetDBIndex = i + 5;
															primary.preplacedWorldIndex[5] = orbitalRadiusIndex;
															primary.preplacedWorldPlanetDBIndex[5] = i;
															orbitalRadiusIndex = 6;
//															Check for out of bounds
															if (i + 6 < WORLDDOC_LENGTH)
															{
																if (worldDoc.GetCell<std::string>("pl_letter", i + 6) == "h")
																{
						//											Assign orbital radius
																	primary.orbitalRadiusArray[orbitalRadiusIndex] = worldDoc.GetCell<float>("pl_orbsmax", i + 6);
						//											Record the world's index in the worldDoc
																	primary.worldArray[orbitalRadiusIndex].planetDBIndex = i + 6;
																	primary.preplacedWorldIndex[6] = orbitalRadiusIndex;
																	primary.preplacedWorldPlanetDBIndex[6] = i;
																	orbitalRadiusIndex = 7;
																}
						//										If there are no further worlds in the system, break
																else	{break;}
															}
														}
	//									If there are no further worlds in the system, break
														else	{break;}
													}
												}
	//											If there are no further worlds in the system, break
												else	{break;}
											}
										}
//										If there are no further worlds in the system, break
										else	{break;}
									}
//								If there are no further worlds in the system, break
								else	{break;}
								}
							}
						}
//						If there are no further worlds in the system, break
						else	{break;}
					}
				}
			}

*/
		/*
		if (matchWasFound == false)
		{
			//	std::cout << "\nNo match was found between starDoc and worldDoc\n" << std::endl;
			float divisor;
			if (primary.outerLimitRadius > primary.innerForbiddenZone || primary.innerForbiddenZone == 0) {divisor = primary.outerLimitRadius;}
			else {divisor = primary.innerForbiddenZone;}
			//	std::cout << "divisor == " << divisor << std::endl;
			primary.orbitalRadiusArray[0] = getOrbitalRadius(divisor);
			//	std::cout << "primary.orbitalRadiusArray[0] == " << primary.orbitalRadiusArray[0] << "\n" << std::endl;

		}
		*/
	//}

	}
	std::cout << "orbitalRadiusIndex == " << orbitalRadiusIndex << std::endl;
	std::cout << "primary.orbitalRadiusArray[0] = " << primary.orbitalRadiusArray[0] << std::endl;

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
	bool inCompanionAForbiddenZone = false;
	bool inCompanionBForbiddenZone = false;
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

	std::cout << "\nINWARD" << std::endl;

	std::cout << "inPrimaryForbiddenZone = " 	<< inPrimaryForbiddenZone 	<< std::endl;
	std::cout << "inCorrectRadius = " 			<< inCorrectRadius 			<< std::endl;
	std::cout << "lessThanFirstOrbit = " 		<< lessThanFirstOrbit 		<< std::endl;

	std::cout << "orbitalRadiusIndex == " << orbitalRadiusIndex << std::endl;
	std::cout << "distanceBetweenOrbits == " << distanceBetweenOrbits << std::endl;
	for (int index = 1; (distanceBetweenOrbits >= 0.15 && !inPrimaryForbiddenZone && inCorrectRadius && lessThanFirstOrbit); index++)
	{
			std::cout << "Entered inward orbit generation for loop successfully" << std::endl;
//		If the index is less than or equal to orbitalRadiusIndex, then a planet has already been placed there
		if (index <= orbitalRadiusIndex && randomStar == false && matchWasFound == true)	{continue;}

//		Get the current orbital ratio
		currentOrbitalRatio = orbitalSpacingTable();
		std::cout << "currentOrbitalRatio = " << currentOrbitalRatio << std::endl;
//		Determine the orbital radius
		std::cout << "index == " << index << std::endl;
		std::cout << "primary.orbitalRadiusArray[" << index << "] == " << primary.orbitalRadiusArray[index] << std::endl;
		std::cout << "primary.orbitalRadiusArray[" << index - 1 << "] == " << primary.orbitalRadiusArray[index - 1] << std::endl;
		distanceFromPrimary = primary.orbitalRadiusArray[index - 1] / currentOrbitalRatio;
		std::cout << "distanceFromPrimary = " << distanceFromPrimary << std::endl;
//		Determine the current distance between orbits
		distanceBetweenOrbits = primary.orbitalRadiusArray[index - 1] - distanceFromPrimary;
		std::cout << "distanceBetweenOrbits = " << distanceBetweenOrbits << std::endl;
//		Store the orbital radius in the array
		primary.orbitalRadiusArray[index] = distanceFromPrimary;
		std::cout << "primary.orbitalRadiusArray[" << index << "] = " << primary.orbitalRadiusArray[index] << std::endl;
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


		std::cout << "inPrimaryForbiddenZone = " << inPrimaryForbiddenZone << std::endl;
		std::cout << "inCorrectRadius = " << inCorrectRadius << std::endl;
		std::cout << "lessThanFirstOrbit = " << lessThanFirstOrbit << std::endl;


//		If any of the flags turn true, redo the for loop
		if (inPrimaryForbiddenZone == true || inCorrectRadius == false || lessThanFirstOrbit == false || distanceBetweenOrbits < 0.15 || inCompanionAForbiddenZone == true || inCompanionBForbiddenZone == true)
		{
			index - 1;
		}
	}

	//	std::cout << "\nInward orbit generation loop exited successfully\n" << std::endl;

//	Delete last entry if invalid and subtract one from innerWorldIndex
	if (distanceBetweenOrbits < 0.15)
	{
		primary.orbitalRadiusArray[innerWorldIndex] = 0;
		innerWorldIndex -= 1;
	}

	std::cout << "innerWorldIndex = " << innerWorldIndex << std::endl;

	std::cout << std::endl << "OUTWARD" << std::endl;
//	Work outward from the first planet placed
//	Generate the orbital radius of the next furthest world from the first placed world
//	Determine the new orbital ratio
	currentOrbitalRatio = orbitalSpacingTable();
	std::cout << "currentOrbitalRatio = " << currentOrbitalRatio << std::endl;
//	Reset the distance from the primary to the first placed orbit
	distanceFromPrimary = primary.orbitalRadiusArray[0] * currentOrbitalRatio;
	std::cout << "distanceFromPrimary = " << distanceFromPrimary << std::endl;
//	Reset the distance between the orbits to factor in the first placed orbit
	distanceBetweenOrbits = distanceFromPrimary - primary.orbitalRadiusArray[0];
	std::cout << "distanceBetweenOrbits = " << distanceBetweenOrbits << std::endl;

//	Last index value (easier than sizeof())
	int outerWorldIndex = 0;

//	Check if the orbit is less than or equal to the first placed orbit
	bool greaterThanFirstOrbit = (distanceFromPrimary >= primary.orbitalRadiusArray[0]) || (distanceFromPrimary == primary.orbitalRadiusArray[0]);

//	Check if the initial orbit falls between the star's inner and outer radii
	inCorrectRadius = (distanceFromPrimary >= primary.innerLimitRadius && distanceFromPrimary <= primary.outerLimitRadius);
//	Check if the initial orbit is less than or equal to the first placed orbit
	lessThanFirstOrbit = (distanceFromPrimary <= primary.orbitalRadiusArray[0]) || (distanceFromPrimary == primary.orbitalRadiusArray[0]);

//	Set the orbital radius of the orbit after the first to distanceBetweenOrbits
	if (distanceBetweenOrbits >= 0.15 && !inPrimaryForbiddenZone && inCorrectRadius && greaterThanFirstOrbit)
	{
//		Check for out of bounds
		if ((innerWorldIndex + 1) < SIZE_ORBITALRADIUS_SIZECLASS_WORLD_ARRAY)
		{
			primary.orbitalRadiusArray[innerWorldIndex + 1] = distanceFromPrimary;
		}
	}
	std::cout << "primary.orbitalRadiusArray[" << innerWorldIndex + 1 << "] = " << primary.orbitalRadiusArray[innerWorldIndex + 1] << std::endl;
	std::cout << "inPrimaryForbiddenZone = " << inPrimaryForbiddenZone << std::endl;
	std::cout << "inCorrectRadius = " << inCorrectRadius << std::endl;
	std::cout << "greaterThanFirstOrbit = " << greaterThanFirstOrbit << std::endl;

//	While the distance between orbits is greater than 0.15 AU, the star's inner limit radius, and the first planet's orbital radius and less than the star's outer limit radius and any forbidden zones
	for (int index = innerWorldIndex + 2; (distanceBetweenOrbits >= 0.15 && !inPrimaryForbiddenZone && inCorrectRadius && greaterThanFirstOrbit); index++)
	{
//		Get the current orbital ratio
		currentOrbitalRatio = orbitalSpacingTable();
		std::cout << "currentOrbitalRatio = " << currentOrbitalRatio << std::endl;
//		Determine the orbital radius
		distanceFromPrimary = primary.orbitalRadiusArray[index - 1] * currentOrbitalRatio;
		std::cout << "distanceFromPrimary = " << distanceFromPrimary << std::endl;
//		Determine the current distance between orbits
		distanceBetweenOrbits = distanceFromPrimary - primary.orbitalRadiusArray[index - 1];
		std::cout << "distanceBetweenOrbits = " << distanceBetweenOrbits << std::endl;
//		Store the orbital radius in the array
		primary.orbitalRadiusArray[index] = distanceFromPrimary;
		std::cout << "primary.orbitalRadiusArray[" << index << "] = " << primary.orbitalRadiusArray[index] << std::endl;
//		Store the current index
		outerWorldIndex = index;
//		Check if the orbit falls between the star's inner and outer radii
		inCorrectRadius = (distanceFromPrimary >= primary.innerLimitRadius && distanceFromPrimary <= primary.outerLimitRadius);
//		Check if the orbit is less than or equal to the first placed orbit
		greaterThanFirstOrbit = (distanceFromPrimary > primary.orbitalRadiusArray[0]);
//		Check if the orbit is in the forbidden zone
		inPrimaryForbiddenZone = (numberOfStars > 1) && (primary.orbitalRadiusArray[index] <= primary.outerForbiddenZone && primary.orbitalRadiusArray[index] >= primary.innerForbiddenZone);

		std::cout << "inPrimaryForbiddenZone = " << inPrimaryForbiddenZone << std::endl;
		std::cout << "inCorrectRadius = " << inCorrectRadius << std::endl;
		std::cout << "greaterThanFirstOrbit = " << greaterThanFirstOrbit << std::endl;

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
	std::cout << "outerWorldIndex = " << outerWorldIndex << std::endl;

//	outerWorldIndex holds the index of the last orbit placed, so it also gives the number of orbits
	primary.numberOfOrbits = (innerWorldIndex >= outerWorldIndex) ? innerWorldIndex : outerWorldIndex;
//	Sort orbital radii in ascending order
//	Temp value for sorting
	float tempValue = 0;
	for (int i = 0; i < outerWorldIndex + 1; i++)
	{
//		Check for out of bounds
		if (outerWorldIndex + 1 < SIZE_ORBITALRADIUS_SIZECLASS_WORLD_ARRAY)
		{
			for (int j = i + 1; j < outerWorldIndex + 1; j++)
			{
				tempValue = primary.orbitalRadiusArray[i];
				primary.orbitalRadiusArray[i] = primary.orbitalRadiusArray[j];
				primary.orbitalRadiusArray[j] = tempValue;
			}
		}
	}

	return primary;

}
