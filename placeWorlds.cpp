//	C++ libraries
#include <string>
#include <iostream>

//	Constant declarations
#include "declarations/constants/gasGiantArrangementConstants.h"
#include "declarations/constants/sizeClassConstants.h"
#include "declarations/constants/stringConstants.h"
#include "declarations/constants/unitConversions.h"

//	Structure declarations
#include "declarations/structures/world_t.h"
#include "declarations/structures/star_t.h"

//	Function declarations
#include "declarations/functions/diceRoller.h"

//	Third party
#include "declarations/third_party/rapidcsv.h"

using namespace std;

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
	else if (orbitContentsRoll == 7  || orbitContentsRoll == 8	) {return SC_EMPTY_ORBIT	 ;}
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

//	Check if the orbit is adjacent to a forbidden zone
	if (primary.orbitalRadiusArray[currentIndex + 1] >= primary.outerForbiddenZone || primary.orbitalRadiusArray[currentIndex - 1] <= primary.innerForbiddenZone										) {finalModifier += ADJACENT_TO_FORBIDDEN_ZONE		;}
//	cout << "First if succeeded" << endl;
//	Check if the next orbit outward contains a gas giant
	if (primary.sizeClassArray[currentIndex + 1] == SC_SMALL_GAS_GIANT || primary.sizeClassArray[currentIndex + 1] == SC_MEDIUM_GAS_GIANT || primary.sizeClassArray[currentIndex + 1] == SC_LARGE_GAS_GIANT) {finalModifier += NEXT_OUTWARD_ORBIT_IS_GAS_GIANT	;}
//	cout << "Second if succeeded" << endl;
//	Check if there is another orbit inward
	if (currentIndex != 0)
	{
//		Check if the next orbit inward contains a gas giant
		if (primary.sizeClassArray[currentIndex - 1] == SC_SMALL_GAS_GIANT || primary.sizeClassArray[currentIndex - 1] == SC_MEDIUM_GAS_GIANT || primary.sizeClassArray[currentIndex - 1] == SC_LARGE_GAS_GIANT) {finalModifier += NEXT_INWARD_ORBIT_IS_GAS_GIANT	;}
//		cout << "Third if succeeded" << endl;
//		Check if the orbit is adjacent to the inner or outer limit radii
		if (primary.orbitalRadiusArray[currentIndex + 1] >= primary.outerLimitRadius || primary.orbitalRadiusArray[currentIndex - 1] <= primary.innerLimitRadius											) {finalModifier += ADJACENT_TO_INNER_OR_OUTER_LIMIT;}
//		cout << "Fourth if succeeded" << endl;
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
	char worldSizeClass;

//	Check if the system has a gas giant
	if (primary.firstGasGiantPresent == true)
	{
//		Check for a conventional gas giant arrangement
		if (primary.gasGiantArrangement == GGA_CONVENTIONAL_GAS_GIANT)
		{
//			Conventional gas giant arrangements will only have gas giants outside of the snow line
			if (primary.orbitalRadiusArray[currentIndex] >= primary.snowLineRadius)
			{
//				Determine the gas giant size class
				if (worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) <= 100)																									{worldSizeClass = SC_SMALL_GAS_GIANT;}
				else if (worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) > 100 && worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) <= 600)	{worldSizeClass = SC_MEDIUM_GAS_GIANT;}
				else																																																{worldSizeClass = SC_LARGE_GAS_GIANT;}
			}

//			For terrestrial worlds
			else
			{
				if 		(worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) >= 2 /*&& worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) < 10*/)	{worldSizeClass = SC_TERRESTRIAL_PLANET_LARGE;}
				else if (worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) < 2 && worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) >= 0.8)		{worldSizeClass = SC_TERRESTRIAL_PLANET_STANDARD;}
				else if (worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) < 0.8 && worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) >= 0.1)		{worldSizeClass = SC_TERRESTRIAL_PLANET_SMALL;}
				else																																																	{worldSizeClass = SC_TERRESTRIAL_PLANET_TINY;}
			}
		}

//		Check for an eccentric gas giant arrangement
		else if (primary.gasGiantArrangement == GGA_ECCENTRIC_GAS_GIANT)
		{
//			An eccentric gas giant has an eccentricity greater than 0.6
			if (worldDoc.GetCell<float>("pl_orbeccen", primary.worldArray[currentIndex].planetDBIndex) >= 0.6)
			{
//				Determine the gas giant size class
				if (worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) <= 100)																									{worldSizeClass = SC_SMALL_GAS_GIANT;}
				else if (worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) > 100 && worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) <= 600)	{worldSizeClass = SC_MEDIUM_GAS_GIANT;}
				else																																																{worldSizeClass = SC_LARGE_GAS_GIANT;}
			}
//			For terrestrial worlds
			else
			{
				if 		(worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) >= 2 /*&& worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) < 10*/)	{worldSizeClass = SC_TERRESTRIAL_PLANET_LARGE;}
				else if (worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) < 2 && worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) >= 0.8)		{worldSizeClass = SC_TERRESTRIAL_PLANET_STANDARD;}
				else if (worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) < 0.8 && worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) >= 0.1)		{worldSizeClass = SC_TERRESTRIAL_PLANET_SMALL;}
				else																																																	{worldSizeClass = SC_TERRESTRIAL_PLANET_TINY;}
			}
		}

//		Check for an epistellar gas giant arrangement
		else if (primary.gasGiantArrangement == GGA_EPISTELLAR_GAS_GIANT)
		{
			if (worldDoc.GetCell<float>("pl_masse", primary.worldArray[currentIndex].planetDBIndex) > (0.1 * JUPITER_MASS_IN_EARTH_MASS) && worldDoc.GetCell<float>("pl_orbper", primary.worldArray[currentIndex].planetDBIndex) < 10)
			{
//				Determine the gas giant size class
				if (worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) <= 100)																									{worldSizeClass = SC_SMALL_GAS_GIANT;}
				else if (worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) > 100 && worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) <= 600)	{worldSizeClass = SC_MEDIUM_GAS_GIANT;}
				else																																																{worldSizeClass = SC_LARGE_GAS_GIANT;}
			}

//			For terrestrial worlds
			else
			{
				if 		(worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) >= 2 /*&& worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) < 10*/)	{worldSizeClass = SC_TERRESTRIAL_PLANET_LARGE;}
				else if (worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) < 2 && worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) >= 0.8)		{worldSizeClass = SC_TERRESTRIAL_PLANET_STANDARD;}
				else if (worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) < 0.8 && worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) >= 0.1)		{worldSizeClass = SC_TERRESTRIAL_PLANET_SMALL;}
				else																																																	{worldSizeClass = SC_TERRESTRIAL_PLANET_TINY;}
			}
		}
	}

//	If there are no gas giants in the system
	else
	{
		if 		(worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) >= 2 /*&& worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) < 10*/)	{worldSizeClass = SC_TERRESTRIAL_PLANET_LARGE;}
		else if (worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) < 2 && worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) >= 0.8)		{worldSizeClass = SC_TERRESTRIAL_PLANET_STANDARD;}
		else if (worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) < 0.8 && worldDoc.GetCell<float>("pl_bmasse", primary.worldArray[currentIndex].planetDBIndex) >= 0.1)		{worldSizeClass = SC_TERRESTRIAL_PLANET_SMALL;}
		else																																																	{worldSizeClass = SC_TERRESTRIAL_PLANET_TINY;}
	}

	return worldSizeClass;
}

star_t fillOrbits(star_t& primary, rapidcsv::Document& worldDoc, bool randomSystem)
{
//	gasGiantPlacementRoll modifier should the gas giant fall inside the snow line radius
	const int SNOWLINE_RADIUS_MODIFIER = 4;
	std::cout << "\nEntered fillOrbits" << std::endl;
//	Dice roll for gas giant placement
	int gasGiantPlacementRoll;
//	Index location of the first orbit beyond the snow line radius
	int firstOrbitPastSnowLine;
//	Roll dice for gas giant size
	int gasGiantSizeRoll;
//	The size of the gas giant
	char gasGiantSize;
//	Roll dice for the contents of the orbit
	int orbitContentsRoll;
//	Modifier for orbitContentsRoll
	int orbitContentsRollModifier;
//	The contents of the orbit
	char orbitalContents;

//	orbitalRadiusArray indices that are preplaced worlds
	int currentWorldIndex = 0;
	if (randomSystem == false)
	{
		for (int i = 0; i < primary.numberOfOrbits; i++)
		{
	//		If the system is non-random and the planet's name is not empty
			if (primary.worldArray[i].planetName != "")
			{
				primary.preplacedWorldIndex[currentWorldIndex] = i;
	//			Determine the size class of the world at this index
				primary.sizeClassArray[i] = csv_determineWorldSizeClass(primary, worldDoc, i);
				currentWorldIndex++;
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
			std::cout << "\nfirstOrbitPastSnowLine == " << firstOrbitPastSnowLine << std::endl;
//			Break from the for loop
			break;
		}
	}

	std::cout << "gasGiantArrangement == " << GGA_S_LOOKUP_TABLE[int(primary.gasGiantArrangement)] << std::endl;

//	Place gas giants
//	If the system's gas giant arrangement is "Conventional Gas Giant"
	if (primary.gasGiantArrangement == GGA_CONVENTIONAL_GAS_GIANT)
	{
//		Iterate through the orbits for the gas giants
		for (int index = 0; index < primary.numberOfOrbits; index++)
		{
//			Flag to continue if the current index is preplaced
			bool indexIsPreplaced;
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
//				Add the snow line radius modifier
				if (index == firstOrbitPastSnowLine) {gasGiantPlacementRoll += SNOWLINE_RADIUS_MODIFIER;}

//				Check if the placement roll succeeded
				if (gasGiantPlacementRoll <= 15)
				{
//					Roll dice for gas giant size
					gasGiantSizeRoll = diceRoller(6, 3);
//					Get the gas giant's size
					gasGiantSize = getGasGiantSize(gasGiantSizeRoll);
					primary.sizeClassArray[index] = gasGiantSize;
//					primary.orbitalRadiusArray[index] = primary.orbitalRadiusArray[index];
				}
			}
		}

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
	}

//	If the system's gas giant arrangement is "Eccentric Gas Giant"
	else if (primary.gasGiantArrangement == GGA_ECCENTRIC_GAS_GIANT)
	{
//			Iterate through the orbits for the gas giants
			for (int index = 0; index < primary.numberOfOrbits; index++)
			{
//				Flag to continue if the current index is preplaced
				bool indexIsPreplaced;
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
//					Add the snow line radius modifier
					if (index == firstOrbitPastSnowLine) {gasGiantPlacementRoll += SNOWLINE_RADIUS_MODIFIER;}
//					Check if the placement roll succeeded
					if (gasGiantPlacementRoll <= 14)
					{
//						Roll dice for gas giant size
						gasGiantSizeRoll = diceRoller(6, 3);
//						Get the gas giant's size
						gasGiantSize = getGasGiantSize(gasGiantSizeRoll);
						primary.sizeClassArray[index] = gasGiantSize;
						primary.orbitalRadiusArray[index] = primary.orbitalRadiusArray[index];
					}
				}

//				If the orbit is inside the snow line
				else
				{
					if (gasGiantPlacementRoll <= 8)
					{
//						Roll dice for gas giant size
						gasGiantSizeRoll = diceRoller(6, 3);
//						Get the gas giant's size
						gasGiantSize = getGasGiantSize(gasGiantSizeRoll);
						primary.sizeClassArray[index] = gasGiantSize;
						primary.orbitalRadiusArray[index] = primary.orbitalRadiusArray[index];
					}
				}
			}

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
		}

//	If the system's gas giant arrangement is "Epistellar Gas Giant"
	else if (primary.gasGiantArrangement == GGA_EPISTELLAR_GAS_GIANT)
	{
//			Iterate through the orbits for the gas giants
			for (int index = 0; index < primary.numberOfOrbits; index++)
			{
//				Flag to continue if the current index is preplaced
				bool indexIsPreplaced;
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
//					Add the snow line radius modifier
					if (index == firstOrbitPastSnowLine) {gasGiantPlacementRoll += SNOWLINE_RADIUS_MODIFIER;}
//					Check if the placement roll succeeded
					if (gasGiantPlacementRoll <= 14)
					{
//						Roll dice for gas giant size
						gasGiantSizeRoll = diceRoller(6, 3);
//						Get the gas giant's size
						gasGiantSize = getGasGiantSize(gasGiantSizeRoll);
						primary.sizeClassArray[index] = gasGiantSize;
						primary.orbitalRadiusArray[index] = primary.orbitalRadiusArray[index];
					}
				}

//				If the orbit is inside the snow line
				else
				{
					if (gasGiantPlacementRoll <= 6)
					{
//						Roll dice for gas giant size
						gasGiantSizeRoll = diceRoller(6, 3);
//						Get the gas giant's size
						gasGiantSize = getGasGiantSize(gasGiantSizeRoll);
						primary.sizeClassArray[index] = gasGiantSize;
						primary.orbitalRadiusArray[index] = primary.orbitalRadiusArray[index];
					}
				}
			}

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
		}

//	If the system's gas giant arrangement is "No Gas Giant"
	else if (primary.gasGiantArrangement == GGA_NO_GAS_GIANT)
	{
		std::cout << "Entered no gas giant if loop" << std::endl;
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
			std::cout << "indexIsPreplaced == " << indexIsPreplaced << std::endl;
//			Skip current index if true
			if (indexIsPreplaced == true)	{continue;}

//			If the current orbit is empty
			if (primary.sizeClassArray[index] == SC_EMPTY_ORBIT)
			{
				std::cout << "primary.sizeClassArray[" << index << "] == SC_EMPTY_ORBIT" << std::endl;
//				Roll for orbital contents
				orbitContentsRoll = diceRoller(6, 3);
				std::cout << "orbitContentsRoll == " << orbitContentsRoll << std::endl;
//				Get modifier
				orbitContentsRollModifier = getOrbitContentsRollModifier(primary, index);
				std::cout << "orbitContentsRollModifier == " << orbitContentsRollModifier << std::endl;
//				Add modifier to roll
				orbitContentsRoll += orbitContentsRollModifier;
				std::cout << "orbitContentsRoll + orbitContentsRollModifier == " << orbitContentsRoll << std::endl;
//				Get orbital contents
				orbitalContents = orbitContentsTable(orbitContentsRoll);
				std::cout << "orbitContentsRoll == " << orbitContentsRoll << std::endl;
//				Place orbital contents in worldArray
				primary.sizeClassArray[index] = orbitalContents;
//				Place corresponding orbital radius in worldArray
				primary.orbitalRadiusArray[index] = primary.orbitalRadiusArray[index];
			}
		}
	}

	return primary;
}
