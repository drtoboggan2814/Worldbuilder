//	C++ libraries
#include <string>
#include <iostream>

//	Constant declarations
#include "declarations/constants/gasGiantArrangementConstants.h"
#include "declarations/constants/sizeClassConstants.h"

//	Structure declarations
#include "declarations/structures/world_t.h"
#include "declarations/structures/star_t.h"

//	Function declarations
#include "declarations/functions/diceRoller.h"

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
int getOrbitContentsRollModifier(star_t primary, int currentIndex)
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
	int finalModifier;

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

star_t fillOrbits(star_t primary)
{
//	gasGiantPlacementRoll modifier should the gas giant fall inside the snow line radius
	const int SNOWLINE_RADIUS_MODIFIER = 4;

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

//	Find the first orbit past the snow line radius
	for (int index = 0; index < primary.numberOfOrbits; index++)
	{
		if (primary.orbitalRadiusArray[index] >= primary.snowLineRadius)
		{
//			Assign the current index
			firstOrbitPastSnowLine = index;
//			Break from the for loop
			break;
		}
	}

//	Place gas giants
//	If the system's gas giant arrangement is "Conventional Gas Giant"
	if (primary.gasGiantArrangement == GGA_CONVENTIONAL_GAS_GIANT)
	{
//			Iterate through the orbits for the gas giants
		for (int index = 0; index < primary.numberOfOrbits; index++)
		{
//				"Conventional Gas Giant" is not rolled for orbits inside the snow line radius
			if (primary.orbitalRadiusArray[index] >= primary.snowLineRadius)
			{
//					Roll 3d6 for the presence of a gas giant
				gasGiantPlacementRoll = diceRoller(6, 3);
//					Add the snow line radius modifier
				if (index == firstOrbitPastSnowLine) {gasGiantPlacementRoll += SNOWLINE_RADIUS_MODIFIER;}

//					Check if the placement roll succeeded
				if (gasGiantPlacementRoll <= 15)
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

//	If the system's gas giant arrangement is "Eccentric Gas Giant"
	else if (primary.gasGiantArrangement == GGA_ECCENTRIC_GAS_GIANT)
	{
//			Iterate through the orbits for the gas giants
			for (int index = 0; index < primary.numberOfOrbits; index++)
			{
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
//		Iterate through the orbits for the rest of the worlds
		for (int index = 0; index < primary.numberOfOrbits; index++)
		{
//			If the current orbit is empty
			if (primary.sizeClassArray[index] == SC_EMPTY_ORBIT)
			{
//				Roll for orbital contents
				orbitContentsRoll = diceRoller(6, 3);
//				Get modifier
				orbitContentsRollModifier = getOrbitContentsRollModifier(primary, index);
//				Add modifier to roll
				orbitContentsRoll += orbitContentsRollModifier;
//				Get orbital contents
				orbitalContents = orbitContentsTable(orbitContentsRoll);
//				Place orbital contents in worldArray
				primary.sizeClassArray[index] = orbitalContents;
//				Place corresponding orbital radius in worldArray
				primary.orbitalRadiusArray[index] = primary.orbitalRadiusArray[index];
			}
		}
	}

	return primary;
}
