//	C++ libraries
#include <string>

//	Structure declarations
#include "declarations/structures/marginalAtmosphere_t.h"
#include "declarations/structures/moon_t.h"
#include "declarations/structures/world_t.h"

//	Function declarations
#include "declarations/functions/diceRoller.h"
#include "declarations/functions/floatRNG.h"

using namespace std;

//	This function creates orbital slots for a planet's major moons
float placeMoonOrbits(float planetDiameter, int moonSizeClass, int family)
{
	float orbitalRadius;
	int moonOrbitModifier = 0;
	int moonOrbitRoll = diceRoller(6, 2);

//	For moons of terrestrial worlds
	if (family == 0)
	{
		if 		(moonSizeClass == -2) {moonOrbitModifier += 2;}
		else if (moonSizeClass == -1) {moonOrbitModifier += 4;}
		orbitalRadius = (moonOrbitRoll + moonOrbitModifier) * 2.5 * planetDiameter;
	}

//	For first family moonlets
	else if (family == 1)
	{
		orbitalRadius = ((diceRoller(6, 1) + 4) / 4) * planetDiameter;
	}

//	For second family moons
	else if (family == 2)
	{
		int secondFamilyRoll = diceRoller(6, 3) + 3;
		orbitalRadius = (secondFamilyRoll >= 15) ? secondFamilyRoll + diceRoller(6, 2) : orbitalRadius;
		orbitalRadius = (orbitalRadius / 2) * planetDiameter;
	}

//	For third family moonlets
	else
	{
		orbitalRadius = 0;
//		orbitalRadius = floatRNG(20, 400) * planetDiameter;
	}

	return orbitalRadius;
}
