//	C++ libraries
#include <iostream>
#include <math.h>
#include <string>

//	Constant declarations
#include "declarations/constants/gasGiantArrangementConstants.h"
#include "declarations/constants/sizeClassConstants.h"
#include "declarations/constants/stringConstants.h"
#include "declarations/constants/unitConversions.h"
#include "declarations/constants/universalConstants.h"

//	Structure declarations
#include "declarations/structures/world_t.h"
#include "declarations/structures/star_t.h"

//	Function declarations
#include "declarations/functions/diceRoller.h"
#include "declarations/functions/placingFirstPlanets.h"

//	Third party
#include "declarations/third_party/rapidcsv.h"

using namespace std;


int findAppropriateOrbitalSlot(star_t& primary, float semiMajorAxis)
{
//	Initialize return value
//	If no appropriate slot is found, return primary.numberOfOrbits + 1
	int orbitalSlotIndex = 0;
	bool matchFound = false;
//	Loop through orbitalRadiusArray
	for (int i = 0; i < primary.numberOfOrbits; i++)
	{
//		Check if the slot is available
		if (primary.sizeClassArray[i] == SC_EMPTY_ORBIT)
		{
//			If this is the last orbital slot
			if 		(i == (primary.numberOfOrbits - 1))
			{
			//	Check if the orbit is greater than or equal to the current slot, but less than the outerLimitRadius
				if (semiMajorAxis >= primary.orbitalRadiusArray[i] && semiMajorAxis < primary.outerLimitRadius)
				{
//					Return orbitalSlotIndex
					matchFound = true;
					orbitalSlotIndex = i;
					break;
				}
			}

		//	Check if the orbit is greater than or equal to the current slot, but less than the next
			else if (semiMajorAxis >= primary.orbitalRadiusArray[i] && semiMajorAxis < primary.orbitalRadiusArray[i + 1])
			{
//				Return orbitalSlotIndex
				matchFound = true;
				orbitalSlotIndex = i;
				break;
			}
		}

//		If there are no slots available
		else if (i == (primary.numberOfOrbits - 1))
		{
			orbitalSlotIndex = primary.numberOfOrbits + 1;
		}
	}

	return orbitalSlotIndex;
}

int getPreplacedArrayIndex(std::string letter)
{
//	Initialize return value
	int preplacedArrayIndex = 0;
	if 		(letter == "b")	{preplacedArrayIndex = 0;}
	else if (letter == "c")	{preplacedArrayIndex = 1;}
	else if (letter == "d")	{preplacedArrayIndex = 2;}
	else if (letter == "e")	{preplacedArrayIndex = 3;}
	else if (letter == "f")	{preplacedArrayIndex = 4;}
	else if (letter == "g")	{preplacedArrayIndex = 5;}
	else if (letter == "h")	{preplacedArrayIndex = 6;}

	return preplacedArrayIndex;
}

star_t assignPreplacedOrbitalSlot (int i, star_t& primary, rapidcsv::Document& worldDoc, std::string letter)
{
	int preplacedArrayIndex = getPreplacedArrayIndex(letter);
	int orbitalSlotIndex = 0;
	float semiMajorAxis = 0;
	if (worldDoc.GetCell<std::string>("pl_orbsmax", i) != "" && worldDoc.GetCell<std::string>("pl_orbsmax", i) != "~")
	{
		semiMajorAxis = worldDoc.GetCell<float>("pl_orbsmax", i);
	}

	else if (worldDoc.GetCell<std::string>("pl_orbper", i) != "" && worldDoc.GetCell<std::string>("pl_orbper", i) != "~")
	{
		float period = worldDoc.GetCell<float>("pl_orbper", i);
		semiMajorAxis = cbrt((UNIVERSAL_GRAVITATIONAL_CONSTANT * primary.stellarMass * SOL_MASS_IN_KG * pow(period * DAY_TO_SEC, 2)));
	}

	orbitalSlotIndex = findAppropriateOrbitalSlot(primary, semiMajorAxis);
//	Record the world's index in the worldDoc
	primary.worldArray[orbitalSlotIndex].planetDBIndex = i;
	std::cout << "i == " << i << std::endl;
	std::cout << "primary.worldArray[" << orbitalSlotIndex << "].planetDBIndex == " << primary.worldArray[orbitalSlotIndex].planetDBIndex << std::endl;
	if (orbitalSlotIndex != primary.numberOfOrbits + 1)
	{
//		Record the orbitalRadiusIndex as preplaced
		primary.preplacedWorldIndex[preplacedArrayIndex] = orbitalSlotIndex;
		primary.preplacedWorldPlanetDBIndex[preplacedArrayIndex] = i;
	}

	return primary;
}

star_t checkForCSVWorld(star_t& primary, rapidcsv::Document& worldDoc)
{
	for (int i = 0; i < WORLDDOC_LENGTH; i++)
	{
		bool matchWasFound = false;
//			If a match is found
		if (csv_starWorldMatch(worldDoc, std::to_string(primary.hipIndex), std::to_string(primary.hdIndex), primary.glieseIndex, primary.properName, i) == true)
		{
			matchWasFound = true;
			std::cout << "\nA match between starDoc and worldDoc has been found" << std::endl;
//				Assign worlds to star
			if (worldDoc.GetCell<std::string>("pl_letter", i) == "b")
			{
				std::cout << "checkForCSVWorld i == " << i << std::endl;
				primary = assignPreplacedOrbitalSlot (i, primary, worldDoc, "b");
//				Check for other worlds in the system
//				Check for out of bounds
				if (i + 1 < WORLDDOC_LENGTH)
				{
					if (worldDoc.GetCell<std::string>("pl_letter", i + 1) == "c")
					{
						primary = assignPreplacedOrbitalSlot (i + 1, primary, worldDoc, "c");
//							Check for out of bounds
						if (i + 2 < WORLDDOC_LENGTH)
						{
							if (worldDoc.GetCell<std::string>("pl_letter", i + 2) == "d")
							{
								primary = assignPreplacedOrbitalSlot (i + 2, primary, worldDoc, "d");
//									Check for out of bounds
								if (i + 3 < WORLDDOC_LENGTH)
								{
									if (worldDoc.GetCell<std::string>("pl_letter", i + 3) == "e")
									{
										primary = assignPreplacedOrbitalSlot (i + 3, primary, worldDoc, "e");
//											Check for out of bounds
										if (i + 4 < WORLDDOC_LENGTH)
										{
											if (worldDoc.GetCell<std::string>("pl_letter", i + 4) == "f")
											{
												primary = assignPreplacedOrbitalSlot (i + 4, primary, worldDoc, "f");
//													Check for out of bounds
												if (i + 5 < WORLDDOC_LENGTH)
												{
													if (worldDoc.GetCell<std::string>("pl_letter", i + 5) == "g")
													{
														primary = assignPreplacedOrbitalSlot (i + 5, primary, worldDoc, "g");
//															Check for out of bounds
														if (i + 6 < WORLDDOC_LENGTH)
														{
															if (worldDoc.GetCell<std::string>("pl_letter", i + 6) == "h")
															{
																primary = assignPreplacedOrbitalSlot (i + 6, primary, worldDoc, "h");
															}

															else	{break;}
														}

														else	{break;}
													}

													else	{break;}
												}

												else	{break;}
											}

											else	{break;}
										}

										else	{break;}
									}

									else	{break;}
								}

								else	{break;}
							}

							else	{break;}
						}

						else	{break;}
					}

					else	{break;}
				}

				else	{break;}
			}

			if (matchWasFound == true)	{break;}
		}
	}

	return primary;
}


//	This functions returns a string representing the size of the gas giant
char getGasGiantSize(int diceRoll)
{
	if 		(diceRoll >= 3  && diceRoll <= 10) 	{return SC_SMALL_GAS_GIANT;}
	else if (diceRoll >= 11 && diceRoll <= 16) 	{return SC_MEDIUM_GAS_GIANT;}
	else 										{return SC_LARGE_GAS_GIANT;}
}

//	This function returns a string representing the non-gas giant contents of the orbit
char orbitContentsTable(int orbitContentsRoll)
{
	if 		(orbitContentsRoll <= 3								) {return SC_EMPTY_ORBIT					 ;}
	else if (orbitContentsRoll >= 4  && orbitContentsRoll <= 6	) {return SC_ASTEROID_BELT				 ;}
	else if (orbitContentsRoll == 7  || orbitContentsRoll == 8	) {return SC_TERRESTRIAL_PLANET_TINY	 ;}
	else if (orbitContentsRoll >= 9  && orbitContentsRoll <= 11	) {return SC_TERRESTRIAL_PLANET_SMALL	 ;}
	else if (orbitContentsRoll >= 12 && orbitContentsRoll <= 15	) {return SC_TERRESTRIAL_PLANET_STANDARD;}
	else														  {return SC_TERRESTRIAL_PLANET_LARGE	 ;}
}

//	This function checks which modifiers should be applied to orbitContentsRoll
//	currentIndex is the current index of the for loop iterating through the orbits
int getOrbitContentsRollModifier(star_t& primary, int currentIndex)
{
//	orbitContentsRoll modifier should the orbit be adjacent to a forbidden zone
	const int ADJACENT_TO_FORBIDDEN_ZONE = -6;
//	orbitContentsRoll modifier should the next orbit outward is a gas giant
	const int NEXT_OUTWARD_ORBIT_IS_GAS_GIANT = -6;
//	orbitContentsRoll modifier should the next orbit inward is a gas giant
	const int NEXT_INWARD_ORBIT_IS_GAS_GIANT = -3;
//	orbitContentsRoll modifier should the orbit be adjacent to the inner or outer limit radii
	const int ADJACENT_TO_INNER_OR_OUTER_LIMIT = -3;

//	The final modifier to be applied to orbitContentsRoll
	int finalModifier = 0;

//	Check for out of bounds
	if ((currentIndex + 1) < SIZE_ORBITALRADIUS_SIZECLASS_WORLD_ARRAY)
	{
		if ((currentIndex - 1) >= 0)
		{
		//	Check if the orbit is adjacent to a forbidden zone
		//	Check if there is no companion
			if (primary.innerForbiddenZone != 0 && primary.outerForbiddenZone != 0)
			{
				if (primary.orbitalRadiusArray[currentIndex + 1] >= primary.innerForbiddenZone && primary.orbitalRadiusArray[currentIndex + 1] <= primary.outerForbiddenZone										) {finalModifier += ADJACENT_TO_FORBIDDEN_ZONE		;}
			}
		//	cout << "First if succeeded" << endl;
		//	Check if the next orbit outward contains a gas giant
			if (primary.gasGiantArrangement != GGA_NO_GAS_GIANT)
			{
				if (primary.sizeClassArray[currentIndex + 1] == SC_SMALL_GAS_GIANT || primary.sizeClassArray[currentIndex + 1] == SC_MEDIUM_GAS_GIANT || primary.sizeClassArray[currentIndex + 1] == SC_LARGE_GAS_GIANT) {finalModifier += NEXT_OUTWARD_ORBIT_IS_GAS_GIANT	;}
			}
		//	cout << "Second if succeeded" << endl;
		}
	}
//	Check if there is another orbit inward
	if (currentIndex != 0)
	{
	//	Check for out of bounds
		if ((currentIndex + 1) < SIZE_ORBITALRADIUS_SIZECLASS_WORLD_ARRAY)
		{
			if ((currentIndex - 1) >= 0)
			{
				//		Check if the next orbit inward contains a gas giant
				if (primary.sizeClassArray[currentIndex - 1] == SC_SMALL_GAS_GIANT || primary.sizeClassArray[currentIndex - 1] == SC_MEDIUM_GAS_GIANT || primary.sizeClassArray[currentIndex - 1] == SC_LARGE_GAS_GIANT) {finalModifier += NEXT_INWARD_ORBIT_IS_GAS_GIANT	;}
		//		cout << "Third if succeeded" << endl;
		//		Check if the orbit is adjacent to the inner or outer limit radii
				if (primary.orbitalRadiusArray[currentIndex + 1] >= primary.outerLimitRadius || primary.orbitalRadiusArray[currentIndex - 1] <= primary.innerLimitRadius											) {finalModifier += ADJACENT_TO_INNER_OR_OUTER_LIMIT;}
		//		cout << "Fourth if succeeded" << endl;
			}
		}
	}

	return finalModifier;
}

//	This function determines the world type of a world described in the worldDoc
//	NOTE: The distinguishing values for terrestrial worlds were pulled out of my ass
//	They do somewhat agree with GURPS Space 4e's assignment of worlds in the Solar System
//	This setup allows for Mercury to be tiny, Mars to be small, Earth and Venus to standard, and any world twice as massive as Earth to be large
char csv_determineWorldSizeClass(star_t& primary, rapidcsv::Document& worldDoc, int currentIndex)
{
//	Initialize return value
	char worldSizeClass = 0;

//	Check if the system has a gas giant
	if (primary.firstGasGiantPresent == true)
	{
//		Check if this world has a valid pl_bmasse value
		if (worldDoc.GetCell<std::string>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) != "~")
		{
//			Check for a conventional gas giant arrangement
			if (primary.gasGiantArrangement == GGA_CONVENTIONAL_GAS_GIANT)
			{

	//			Conventional gas giant arrangements will only have gas giants outside of the snow line
				if (primary.orbitalRadiusArray[currentIndex] >= primary.snowLineRadius)
				{
	//				Determine the gas giant size class
					if (worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) <= 100)																									{worldSizeClass = SC_SMALL_GAS_GIANT;}
					else if (worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) > 100 && worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) <= 600)	{worldSizeClass = SC_MEDIUM_GAS_GIANT;}
					else																																																{worldSizeClass = SC_LARGE_GAS_GIANT;}
				}

	//			For terrestrial worlds
				else
				{
					if 		(worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) >= 2 /*&& worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) < 10*/)	{worldSizeClass = SC_TERRESTRIAL_PLANET_LARGE;}
					else if (worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) < 2 && worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) >= 0.8)		{worldSizeClass = SC_TERRESTRIAL_PLANET_STANDARD;}
					else if (worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) < 0.8 && worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) >= 0.1)		{worldSizeClass = SC_TERRESTRIAL_PLANET_SMALL;}
					else																																																	{worldSizeClass = SC_TERRESTRIAL_PLANET_TINY;}
				}
			}

	//		Check for an eccentric gas giant arrangement
			else if (primary.gasGiantArrangement == GGA_ECCENTRIC_GAS_GIANT)
			{
				if (worldDoc.GetCell<std::string>("pl_orbeccen", primary.preplacedWorldPlanetDBIndex[currentIndex]) != "~")
				{
		//			An eccentric gas giant has an eccentricity greater than 0.6
					if (worldDoc.GetCell<float>("pl_orbeccen", primary.preplacedWorldPlanetDBIndex[currentIndex]) >= 0.6)
					{
		//				Determine the gas giant size class
						if (worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) <= 100)																									{worldSizeClass = SC_SMALL_GAS_GIANT;}
						else if (worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) > 100 && worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) <= 600)	{worldSizeClass = SC_MEDIUM_GAS_GIANT;}
						else																																																{worldSizeClass = SC_LARGE_GAS_GIANT;}
					}
				}
	//			For terrestrial worlds
				else
				{
					if 		(worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) >= 2 /*&& worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) < 10*/)	{worldSizeClass = SC_TERRESTRIAL_PLANET_LARGE;}
					else if (worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) < 2 && worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) >= 0.8)		{worldSizeClass = SC_TERRESTRIAL_PLANET_STANDARD;}
					else if (worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) < 0.8 && worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) >= 0.1)		{worldSizeClass = SC_TERRESTRIAL_PLANET_SMALL;}
					else																																																	{worldSizeClass = SC_TERRESTRIAL_PLANET_TINY;}
				}
			}

	//		Check for an epistellar gas giant arrangement
			else if (primary.gasGiantArrangement == GGA_EPISTELLAR_GAS_GIANT)
			{
				if (worldDoc.GetCell<std::string>("pl_orbper", primary.preplacedWorldPlanetDBIndex[currentIndex]) != "~")
				{
					if (worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) > (0.1 * JUPITER_MASS_IN_EARTH_MASS) && worldDoc.GetCell<double>("pl_orbper", primary.preplacedWorldPlanetDBIndex[currentIndex]) < 10)
					{
		//				Determine the gas giant size class
						if (worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) <= 100)																									{worldSizeClass = SC_SMALL_GAS_GIANT;}
						else if (worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) > 100 && worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) <= 600)	{worldSizeClass = SC_MEDIUM_GAS_GIANT;}
						else																																																{worldSizeClass = SC_LARGE_GAS_GIANT;}
					}
				}
	//			For terrestrial worlds
				else
				{
					if 		(worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) >= 2 /*&& worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) < 10*/)	{worldSizeClass = SC_TERRESTRIAL_PLANET_LARGE;}
					else if (worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) < 2 && worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) >= 0.8)		{worldSizeClass = SC_TERRESTRIAL_PLANET_STANDARD;}
					else if (worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) < 0.8 && worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) >= 0.1)		{worldSizeClass = SC_TERRESTRIAL_PLANET_SMALL;}
					else																																																	{worldSizeClass = SC_TERRESTRIAL_PLANET_TINY;}
				}
			}
		}
	}

//	If there are no gas giants in the system
	else
	{
		if (worldDoc.GetCell<std::string>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) != "~")
		{
			if 		(worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) >= 2 /*&& worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) < 10*/)	{worldSizeClass = SC_TERRESTRIAL_PLANET_LARGE;}
			else if (worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) < 2 && worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) >= 0.8)		{worldSizeClass = SC_TERRESTRIAL_PLANET_STANDARD;}
			else if (worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) < 0.8 && worldDoc.GetCell<float>("pl_bmasse", primary.preplacedWorldPlanetDBIndex[currentIndex]) >= 0.1)		{worldSizeClass = SC_TERRESTRIAL_PLANET_SMALL;}
			else																																																	{worldSizeClass = SC_TERRESTRIAL_PLANET_TINY;}
		}
	}

	return worldSizeClass;
}

star_t fillOrbits(star_t& primary, rapidcsv::Document& worldDoc, bool randomSystem)
{
//	gasGiantPlacementRoll modifier should the gas giant fall inside the snow line radius
	const int SNOWLINE_RADIUS_MODIFIER = 4;
//	std::cout << "\nEntered fillOrbits" << std::endl;
//	Dice roll for gas giant placement
	int gasGiantPlacementRoll = 0;
//	Index location of the first orbit beyond the snow line radius
	int firstOrbitPastSnowLine = 0;
//	Roll dice for gas giant size
	int gasGiantSizeRoll = 0;
//	The size of the gas giant
	char gasGiantSize = 0;
//	Roll dice for the contents of the orbit
	int orbitContentsRoll = 0;
//	Modifier for orbitContentsRoll
	int orbitContentsRollModifier = 0;
//	The contents of the orbit
	char orbitalContents = 0;

	if (randomSystem == false)
	{
		if (primary.numberOfCSVPlanets != 0)
		{
			primary = checkForCSVWorld(primary, worldDoc);
		}
	}

//	orbitalRadiusArray indices that are preplaced worlds
//	int currentWorldIndex = 0;
	if (randomSystem == false)
	{
//		For each orbit in the system
		for (int i = 0; i < primary.numberOfOrbits; i++)
		{
//			For each value in the preplacedWorldIndex
			for (int j = 0; j < primary.numberOfCSVPlanets; j++)
			{
				if (primary.preplacedWorldIndex[j] == i)
				{
//					primary.preplacedWorldIndex[currentWorldIndex] = i;
		//			Determine the size class of the world at this index
					primary.sizeClassArray[i] = csv_determineWorldSizeClass(primary, worldDoc, j);
//					currentWorldIndex++;
				}

//				Otherwise, set primary.sizeClassArray[i] to SC_EMPTY_ORBIT
				else {primary.sizeClassArray[i] = SC_EMPTY_ORBIT;}
			}
		}
	}
//	Find the first orbit past the snow line radius
	for (int index = 0; index < primary.numberOfOrbits; index++)
	{
		if (primary.orbitalRadiusArray[index] >= primary.snowLineRadius)
		{
//			Assign the current index
			firstOrbitPastSnowLine = index;
		//	std::cout << "\nfirstOrbitPastSnowLine == " << firstOrbitPastSnowLine << std::endl;
//			Break from the for loop
			break;
		}
	}

//	std::cout << "gasGiantArrangement == " << GGA_S_LOOKUP_TABLE[int(primary.gasGiantArrangement)] << std::endl;

//	Place gas giants
//	If the system's gas giant arrangement is "Conventional Gas Giant"
	if (primary.gasGiantArrangement == GGA_CONVENTIONAL_GAS_GIANT)
	{
//		Iterate through the orbits for the gas giants
		for (int index = 0; index < primary.numberOfOrbits; index++)
		{
//			Flag to continue if the current index is preplaced
			bool indexIsPreplaced = false;
//			Check if the current index is preplaced
			for (int j = 0; j < primary.numberOfCSVPlanets; j++)
			{
				if (index == primary.preplacedWorldIndex[j])
				{
					indexIsPreplaced = true;
					break;
				}
			}

//			Skip current index if true
			if (indexIsPreplaced == true)	{continue;}

//			"Conventional Gas Giant" is not rolled for orbits inside the snow line radius
			if (primary.orbitalRadiusArray[index] >= primary.snowLineRadius)
			{
//				Roll 3d6 for the presence of a gas giant
				gasGiantPlacementRoll = diceRoller(6, 3);

//				Check if the placement roll succeeded
				if (gasGiantPlacementRoll <= 15)
				{
//					Roll dice for gas giant size
//					Add the snow line radius modifier
					if (index == firstOrbitPastSnowLine) {gasGiantSizeRoll += SNOWLINE_RADIUS_MODIFIER;}
					gasGiantSizeRoll = diceRoller(6, 3);
//					Get the gas giant's size
					gasGiantSize = getGasGiantSize(gasGiantSizeRoll + SNOWLINE_RADIUS_MODIFIER);
					primary.sizeClassArray[index] = gasGiantSize;
//					primary.orbitalRadiusArray[index] = primary.orbitalRadiusArray[index];
				}
			}

			else
			{
//					Roll for orbital contents
				orbitContentsRoll = diceRoller(6, 3);
//					Get modifier
				orbitContentsRollModifier = getOrbitContentsRollModifier(primary, index);
//					Add modifier to roll
				orbitContentsRoll += orbitContentsRollModifier;
//					Get orbital contents
				orbitalContents = orbitContentsTable(orbitContentsRoll);
//					Place orbital contents in worldArray
				primary.sizeClassArray[index] = orbitalContents;
//					Place corresponding orbital radius in worldArray
//				primary.orbitalRadiusArray[index] = primary.orbitalRadiusArray[index];
			}

		}

/*
//			Iterate through the orbits for the rest of the worlds
		for (int index = 0; index < primary.numberOfOrbits; index++)
		{
//				If the current orbit is empty
			if (primary.sizeClassArray[index] == SC_EMPTY_ORBIT)
			{
//					Roll for orbital contents
				orbitContentsRoll = diceRoller(6, 3);
//					Get modifier
				orbitContentsRollModifier = getOrbitContentsRollModifier(primary, index);
//					Add modifier to roll
				orbitContentsRoll += orbitContentsRollModifier;
//					Get orbital contents
				orbitalContents = orbitContentsTable(orbitContentsRoll);
//					Place orbital contents in worldArray
				primary.sizeClassArray[index] = orbitalContents;
//					Place corresponding orbital radius in worldArray
//				primary.orbitalRadiusArray[index] = primary.orbitalRadiusArray[index];
			}
		}
		*/
	}

//	If the system's gas giant arrangement is "Eccentric Gas Giant"
	else if (primary.gasGiantArrangement == GGA_ECCENTRIC_GAS_GIANT)
	{
//			Iterate through the orbits for the gas giants
			for (int index = 0; index < primary.numberOfOrbits; index++)
			{
//				Flag to continue if the current index is preplaced
				bool indexIsPreplaced = false;
//				Check if the current index is preplaced
				for (int j = 0; j < primary.numberOfCSVPlanets; j++)
				{
					if (index == primary.preplacedWorldIndex[j])
					{
						indexIsPreplaced = true;
						break;
					}
				}

//				Skip current index if true
				if (indexIsPreplaced == true)	{continue;}
//				Roll 3d6 for the presence of a gas giant
				gasGiantPlacementRoll = diceRoller(6, 3);

//				If the orbit is outside the snow line
				if (primary.orbitalRadiusArray[index] >= primary.snowLineRadius)
				{
//					Check if the placement roll succeeded
					if (gasGiantPlacementRoll <= 14)
					{
//						Roll dice for gas giant size
//						Add the snow line radius modifier
						if (index == firstOrbitPastSnowLine) {gasGiantSizeRoll += SNOWLINE_RADIUS_MODIFIER;}
						gasGiantSizeRoll = diceRoller(6, 3);
//						Get the gas giant's size
						gasGiantSize = getGasGiantSize(gasGiantSizeRoll);
						primary.sizeClassArray[index] = gasGiantSize;
						primary.orbitalRadiusArray[index] = primary.orbitalRadiusArray[index];
					}
				}

//				If the orbit is inside the snow line
				else if (gasGiantPlacementRoll <= 8)
				{
//						Roll dice for gas giant size
					gasGiantSizeRoll = diceRoller(6, 3);
//						Get the gas giant's size
					gasGiantSize = getGasGiantSize(gasGiantSizeRoll + SNOWLINE_RADIUS_MODIFIER);
					primary.sizeClassArray[index] = gasGiantSize;
					primary.orbitalRadiusArray[index] = primary.orbitalRadiusArray[index];
				}

//				If the current orbit is empty
				else
				{
//					Roll for orbital contents
					orbitContentsRoll = diceRoller(6, 3);
//					Get modifier
					orbitContentsRollModifier = getOrbitContentsRollModifier(primary, index);
//					Add modifier to roll
					orbitContentsRoll += orbitContentsRollModifier;
//					Get orbital contents
					orbitalContents = orbitContentsTable(orbitContentsRoll);
//					Place orbital contents in worldArray
					primary.sizeClassArray[index] = orbitalContents;
//					Place corresponding orbital radius in worldArray
					primary.orbitalRadiusArray[index] = primary.orbitalRadiusArray[index];
				}

			}

/*
//			Iterate through the orbits for the rest of the worlds
			for (int index = 0; index < primary.numberOfOrbits; index++)
			{
//				If the current orbit is empty
				if (primary.sizeClassArray[index] == SC_EMPTY_ORBIT)
				{
//					Roll for orbital contents
					orbitContentsRoll = diceRoller(6, 3);
//					Get modifier
					orbitContentsRollModifier = getOrbitContentsRollModifier(primary, index);
//					Add modifier to roll
					orbitContentsRoll += orbitContentsRollModifier;
//					Get orbital contents
					orbitalContents = orbitContentsTable(orbitContentsRoll);
//					Place orbital contents in worldArray
					primary.sizeClassArray[index] = orbitalContents;
//					Place corresponding orbital radius in worldArray
					primary.orbitalRadiusArray[index] = primary.orbitalRadiusArray[index];
				}
			}
			*/
		}

//	If the system's gas giant arrangement is "Epistellar Gas Giant"
	else if (primary.gasGiantArrangement == GGA_EPISTELLAR_GAS_GIANT)
	{
//			Iterate through the orbits for the gas giants
			for (int index = 0; index < primary.numberOfOrbits; index++)
			{
//				Flag to continue if the current index is preplaced
				bool indexIsPreplaced = false;
//				Check if the current index is preplaced
				for (int j = 0; j < primary.numberOfCSVPlanets; j++)
				{
					if (index == primary.preplacedWorldIndex[j])
					{
						indexIsPreplaced = true;
						break;
					}
				}

//				Skip current index if true
				if (indexIsPreplaced == true)	{continue;}
//				Roll 3d6 for the presence of a gas giant
				gasGiantPlacementRoll = diceRoller(6, 3);

//				If the orbit is outside the snow line
				if (primary.orbitalRadiusArray[index] >= primary.snowLineRadius)
				{
//					Check if the placement roll succeeded
					if (gasGiantPlacementRoll <= 14)
					{
//						Roll dice for gas giant size
						gasGiantSizeRoll = diceRoller(6, 3);
//						Add the snow line radius modifier
						if (index == firstOrbitPastSnowLine) {gasGiantSizeRoll += SNOWLINE_RADIUS_MODIFIER;}
//						Get the gas giant's size
						gasGiantSize = getGasGiantSize(gasGiantSizeRoll);
						primary.sizeClassArray[index] = gasGiantSize;
						primary.orbitalRadiusArray[index] = primary.orbitalRadiusArray[index];
					}
				}

//				If the orbit is inside the snow line
				else if (gasGiantPlacementRoll <= 6)
				{
				//						Roll dice for gas giant size
					gasGiantSizeRoll = diceRoller(6, 3);
//						Get the gas giant's size
					gasGiantSize = getGasGiantSize(gasGiantSizeRoll + SNOWLINE_RADIUS_MODIFIER);
					primary.sizeClassArray[index] = gasGiantSize;
					primary.orbitalRadiusArray[index] = primary.orbitalRadiusArray[index];
				}

//				If the current orbit is empty
				else
				{
//					Roll for orbital contents
					orbitContentsRoll = diceRoller(6, 3);
//					Get modifier
					orbitContentsRollModifier = getOrbitContentsRollModifier(primary, index);
//					Add modifier to roll
					orbitContentsRoll += orbitContentsRollModifier;
//					Get orbital contents
					orbitalContents = orbitContentsTable(orbitContentsRoll);
//					Place orbital contents in worldArray
					primary.sizeClassArray[index] = orbitalContents;
//					Place corresponding orbital radius in worldArray
					primary.orbitalRadiusArray[index] = primary.orbitalRadiusArray[index];
				}
			}

/*
//			Iterate through the orbits for the rest of the worlds
			for (int index = 0; index < primary.numberOfOrbits; index++)
			{
//				If the current orbit is empty
				if (primary.sizeClassArray[index] == SC_EMPTY_ORBIT)
				{
//					Roll for orbital contents
					orbitContentsRoll = diceRoller(6, 3);
//					Get modifier
					orbitContentsRollModifier = getOrbitContentsRollModifier(primary, index);
//					Add modifier to roll
					orbitContentsRoll += orbitContentsRollModifier;
//					Get orbital contents
					orbitalContents = orbitContentsTable(orbitContentsRoll);
//					Place orbital contents in worldArray
					primary.sizeClassArray[index] = orbitalContents;
//					Place corresponding orbital radius in worldArray
					primary.orbitalRadiusArray[index] = primary.orbitalRadiusArray[index];
				}
			}
			*/
		}

//	If the system's gas giant arrangement is "No Gas Giant"
	else if (primary.gasGiantArrangement == GGA_NO_GAS_GIANT)
	{
	//	std::cout << "Entered no gas giant if loop" << std::endl;
//		Iterate through the orbits for the rest of the worlds
		for (int index = 0; index < primary.numberOfOrbits; index++)
		{
			if (index == 0) {std::cout << "Entered for loop" << std::endl;}
//			Flag to continue if the current index is preplaced
//			By default the index is not preplaced
			bool indexIsPreplaced = false;
//			Check if the current index is preplaced
			for (int j = 0; j < primary.numberOfCSVPlanets; j++)
			{
				if (index == primary.preplacedWorldIndex[j])
				{
					indexIsPreplaced = true;
					break;
				}
			}
		//	std::cout << "indexIsPreplaced == " << indexIsPreplaced << std::endl;
//			Skip current index if true
			if (indexIsPreplaced == true)	{continue;}

//			If the current orbit is empty
			if (primary.sizeClassArray[index] == SC_EMPTY_ORBIT)
			{
			//	std::cout << "primary.sizeClassArray[" << index << "] == SC_EMPTY_ORBIT" << std::endl;
//				Roll for orbital contents
				orbitContentsRoll = diceRoller(6, 3);
			//	std::cout << "orbitContentsRoll == " << orbitContentsRoll << std::endl;
//				Get modifier
				orbitContentsRollModifier = getOrbitContentsRollModifier(primary, index);
			//	std::cout << "orbitContentsRollModifier == " << orbitContentsRollModifier << std::endl;
//				Add modifier to roll
				orbitContentsRoll += orbitContentsRollModifier;
			//	std::cout << "orbitContentsRoll + orbitContentsRollModifier == " << orbitContentsRoll << std::endl;
//				Get orbital contents
				orbitalContents = orbitContentsTable(orbitContentsRoll);
			//	std::cout << "orbitContentsRoll == " << orbitContentsRoll << std::endl;
//				Place orbital contents in worldArray
				primary.sizeClassArray[index] = orbitalContents;
//				Place corresponding orbital radius in worldArray
				primary.orbitalRadiusArray[index] = primary.orbitalRadiusArray[index];
			}
		}
	}

	return primary;
}
