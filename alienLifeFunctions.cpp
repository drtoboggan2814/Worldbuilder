//	C++ libraries
#include <cmath>

//	Constant declarations
#include "declarations/constants/worldTypeConstants.h"

constexpr char NE_NOLIFE = 0;
constexpr char NE_PROTOZOA = 1;
constexpr char NE_METAZOA = 2;
constexpr char NE_SIMPLEANIMALS = 3;
constexpr char NE_COMPLEXANIMALS = 4;

//	Return the native native ecosphere level of the world
char getNativeEcosphere(char worldType, float starSystemAge, int diceRoll, float hydrographicCoverage)
{
//	Initialize return value
	char nativeEcosphere = NE_NOLIFE;
	int rollModifier = 0;
	bool worldIsGardenOrOcean = worldType == WT_STANDARD_GARDEN || worldType == WT_STANDARD_OCEAN || worldType == WT_LARGE_GARDEN || worldType == WT_LARGE_OCEAN;

//	A world needs to have some surface liquids or be an ice world to have life
	bool unacceptableWorldType = worldType == WT_ASTEROID_BELT || worldType == WT_TINY_ROCK || worldType == WT_SMALL_ROCK || worldType == WT_STANDARD_CHTHONIAN || worldType == WT_LARGE_CHTHONIAN;
	if (hydrographicCoverage == 0 || unacceptableWorldType)	{return NE_NOLIFE;}

//	If the world is a garden or ocean
	if (worldIsGardenOrOcean)	{rollModifier += 2;}

//	rollModifier += floor(starSystemAge / 0.5);
	rollModifier += floor(starSystemAge);
	diceRoll += rollModifier;

//	Dice roll table
	if (diceRoll <= 13)	{return NE_NOLIFE;}
	else if (diceRoll >= 14 && diceRoll <= 16)	{return NE_PROTOZOA;}
	else if (diceRoll == 17 || diceRoll == 18)	{return NE_METAZOA;}
	else if (diceRoll == 19 || diceRoll == 20)	{return NE_SIMPLEANIMALS;}
	else if (diceRoll >= 21)					{return NE_COMPLEXANIMALS;}
//	else										{return NE_NOLIFE;}
}
