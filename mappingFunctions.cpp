//	This file declares functions used for world mapping
//	NOTE: These are based off the mapping rules from 2300 AD and Traveller: The New Era - World Tamer's Handbook

//	C++ libraries
#include <cstdint>
#include <cmath>
#include <iostream>

//	Constant declarations
#include "declarations/constants/mappingConstants.h"
#include "declarations/constants/unitConversions.h"
#include "declarations/constants/worldTypeConstants.h"

//	Function declarations
#include "declarations/functions/diceRoller.h"

//	Return the number of hexes per triangle side
//	2300AD
char getHexesPerSide(float worldDiameter)
{
	int worldSize = round((worldDiameter * EARTH_RADIUS_IN_KM * 2) / 1000);
	char hexesPerSide = worldSize > 19 ? 19 : WORLDSIZE_TRIANGLESIZE_LOOKUP_TABLE[worldSize];
	return hexesPerSide;
}

//	Return the total number of hexes on the map
int getTotalHexCount(char hexesPerSide)
{
	int totalHexCount = WORLD_MAP_TOTAL_HEXES[hexesPerSide];
	return totalHexCount;
}

//	Return the Traveller UWP size code for the world
//	This function is used by getTectonicPlateCount, and applies only to terrestrial worlds
int getUWPSize(float worldDiameter, char worldType)
{
//	Initialize return value
	int uwpSize = 0;
//	Convert worldDiameter to km
	float worldDiameterKM = worldDiameter * EARTH_RADIUS_IN_KM * 2;

	if 		(worldType == WT_ASTEROID_BELT || worldType == WT_SMALL_GAS_GIANT || worldType == WT_MEDIUM_GAS_GIANT || worldType == WT_LARGE_GAS_GIANT) {uwpSize = 0;}
	else if (worldDiameter < 2400)	{uwpSize = 1;}
	else if (worldDiameter >= 2400 	&& worldDiameter < 4000)	{uwpSize = 2;}
	else if (worldDiameter >= 4000 	&& worldDiameter < 5600)	{uwpSize = 3;}
	else if (worldDiameter >= 5600 	&& worldDiameter < 7200)	{uwpSize = 4;}
	else if (worldDiameter >= 7200 	&& worldDiameter < 8800)	{uwpSize = 5;}
	else if (worldDiameter >= 8800 	&& worldDiameter < 10400)	{uwpSize = 6;}
	else if (worldDiameter >= 10400 && worldDiameter < 12000)	{uwpSize = 7;}
	else if (worldDiameter >= 12000 && worldDiameter < 13600)	{uwpSize = 8;}
	else if (worldDiameter >= 13600 && worldDiameter < 15200)	{uwpSize = 9;}
	else if (worldDiameter >= 15200 && worldDiameter < 16800)	{uwpSize = 10;}
	else if (worldDiameter >= 16800 && worldDiameter < 18400)	{uwpSize = 11;}
	else														{uwpSize = 12;}

	return uwpSize;
}

//	Return the Traveller UWP hydrographic code for the world
//	This function is used by getTectonicPlateCount, and applies only to terrestrial worlds
int getUWPHydrographic(float hydrographicCoverage)
{
//	Initialize return value
	int uwpHydrographic = 0;

	if 		(hydrographicCoverage < 0.06)									{uwpHydrographic = 0;}
	else if (hydrographicCoverage >= 0.06 && hydrographicCoverage < 0.15)	{uwpHydrographic = 1;}
	else if (hydrographicCoverage >= 0.16 && hydrographicCoverage < 0.25)	{uwpHydrographic = 2;}
	else if (hydrographicCoverage >= 0.26 && hydrographicCoverage < 0.35)	{uwpHydrographic = 3;}
	else if (hydrographicCoverage >= 0.36 && hydrographicCoverage < 0.45)	{uwpHydrographic = 4;}
	else if (hydrographicCoverage >= 0.46 && hydrographicCoverage < 0.55)	{uwpHydrographic = 5;}
	else if (hydrographicCoverage >= 0.56 && hydrographicCoverage < 0.65)	{uwpHydrographic = 6;}
	else if (hydrographicCoverage >= 0.66 && hydrographicCoverage < 0.75)	{uwpHydrographic = 7;}
	else if (hydrographicCoverage >= 0.76 && hydrographicCoverage < 0.85)	{uwpHydrographic = 8;}
	else if (hydrographicCoverage >= 0.86 && hydrographicCoverage < 0.95)	{uwpHydrographic = 9;}
	else																	{uwpHydrographic = 10;}

	return uwpHydrographic;
}


//	Return the number of tectonic plates on the world
int getTectonicPlateCount(float worldDiameter, float hydrographicCoverage, char worldType)
{
	int diceRoll = diceRoller(6, 2);
//	std::cout << "diceRoll == " << diceRoll << std::endl;
	int uwpHydrographic = getUWPHydrographic(hydrographicCoverage);
//	std::cout << "uwpHydrographic == " << uwpHydrographic << std::endl;
	int uwpSize = getUWPSize(worldDiameter, worldType);
//	std::cout << "uwpSize == " << uwpSize << std::endl;
	int tectonicPlateCount = (uwpHydrographic - uwpSize) + diceRoll;
//	std::cout << "tectonicPlateCount == " << int(tectonicPlateCount) << std::endl;
//	A planet needs at least one tectonic plate
	tectonicPlateCount = tectonicPlateCount <= 0 ? 1 : tectonicPlateCount;
	return tectonicPlateCount;
}

//	This is not taken from any sources
int getTectonicPlateSize (int averagePlateSize, int variance, int remainingHexes, bool lastPlate)
{
//	Determine variance sign
	bool coinflip = diceRoller(2, 1);
	int newVariance = coinflip ? diceRoller(6, 1) : -1 * diceRoller(6, 1);
//	If this is the last plate and the number of remaining hexes is less than the sum of the average plate size and the variance,
//	the size of the plate is equal to the number of remaining hexes.
	int tectonicPlateSize = (remainingHexes <= (averagePlateSize + variance)) && lastPlate ? remainingHexes : averagePlateSize + variance;
	return tectonicPlateSize;
}

/*
//	Return the size (in hexes) of the tectonic plate
int getTectonicPlateSize(float worldDiameter, int remainingHexes, bool lastPlate, char worldType)
{
	const int TECTONIC_PLATE_SIZE_COEFFICIENT[6] = {5, 10, 15, 20, 25, 30};
	int diceRoll = diceRoller(6, 1);
	int tectonicPlateSize = lastPlate ? remainingHexes : 2 * getUWPSize(worldDiameter, worldType) * TECTONIC_PLATE_SIZE_COEFFICIENT[diceRoll - 1];
	return tectonicPlateSize;
}
*/

//	Return the tectonic plate movement
char getTectonicPlateMovementType()
{
	int diceRoll = diceRoller(6, 2);
	char tectonicPlateMovementType = 0;
	if (diceRoll <= 5)						{tectonicPlateMovementType = TPMT_CONVERGING;}
	else if (diceRoll > 5 && diceRoll <= 8)	{tectonicPlateMovementType = TPMT_TRAVERSING;}
	else									{tectonicPlateMovementType = TPMT_DIVERGING;}

	return tectonicPlateMovementType;
}

//	Return the total number of water hexes
int getWaterHexCount(int totalHexCount, float hydrographicCoverage)
{
	int waterHexCount = int(round(totalHexCount * hydrographicCoverage));
	return waterHexCount;
}

//	Return the total number of land hexes
int getLandHexCount(int totalHexCount, int waterHexCount)
{
	int landHexCount = totalHexCount - waterHexCount;
	return landHexCount;
}

//	Mapping water hexes
//	Return the number of major oceans
char getMajorOceans(int diceRoll)
{
	char numberOfMajorOceans = 0;
	if 		(diceRoll <= 6)		{numberOfMajorOceans = 0;}
	else if (diceRoll >= 19)	{numberOfMajorOceans = 1;}
	else						{numberOfMajorOceans = diceRoller(6, 1) - MAJOR_OCEAN_ADDITION_COEFFICIENT[diceRoll - 1 - 16];}

	numberOfMajorOceans = (numberOfMajorOceans < 0) || (numberOfMajorOceans > 6) ? 0 : numberOfMajorOceans;

	return numberOfMajorOceans;
}

//	Return the number of minor oceans
char getMinorOceans(int diceRoll)
{
	char numberOfMinorOceans = 0;
	if 		(diceRoll <= 6)		{numberOfMinorOceans = 0;}
	else						{numberOfMinorOceans = diceRoller(6, MINOR_OCEAN_MULTIPLIER_COEFFICIENT[diceRoll - 1 - 16]) - MINOR_OCEAN_ADDITION_COEFFICIENT[diceRoll - 1 - 16];}

	numberOfMinorOceans = (numberOfMinorOceans < 0) || (numberOfMinorOceans > 15) ? 0 : numberOfMinorOceans;

	return numberOfMinorOceans;
}

//	Return the number of small seas
char getSmallSeas(int diceRoll)
{
	char numberOfSmallSeas = 0;
	if 		(diceRoll < 5)	{numberOfSmallSeas = 0;}
	else if (diceRoll == 5)	{numberOfSmallSeas = diceRoller(6, 1) - 3;}
	else if (diceRoll == 6)	{numberOfSmallSeas = diceRoller(6, 2) - 3;}
	else					{numberOfSmallSeas = diceRoller(6, 3) - 3;}

	numberOfSmallSeas = (numberOfSmallSeas < 0) || (numberOfSmallSeas > 15) ? 0 : numberOfSmallSeas;

	return numberOfSmallSeas;
}

//	Return the number of scattered lakes
char getScatteredLakes(int diceRoll)
{
	char numberOfScatteredLakes = 0;
	if 		(diceRoll < 3)						{numberOfScatteredLakes = 0;}
	else if (diceRoll == 3 || diceRoll == 4)	{numberOfScatteredLakes = 1;}
	else										{numberOfScatteredLakes = diceRoller(6, 2);}

	return numberOfScatteredLakes;
}

//	Mapping land hexes
//	NOTE: "Mapping Land Hexes" in Traveller: The New Era - World Tamer's Handbook starts at 16 and ends at 36
//	Ensure that this is factored into the diceRoll
//	Return the number of major continents
char getMajorContinents(int diceRoll)
{
	char numberOfMajorContinents = 0;
	if (diceRoll < 31)	{numberOfMajorContinents = diceRoller(6, MAJOR_CONTINENT_MULTIPLIER_COEFFICIENT[diceRoll - 1 - 16]) + MAJOR_CONTINENT_ADDITION_COEFFICIENT[diceRoll - 1 - 16];}
	else						{numberOfMajorContinents = 0;}

	numberOfMajorContinents = (numberOfMajorContinents < 0) || (numberOfMajorContinents > 13) ? 0 : numberOfMajorContinents;

	return numberOfMajorContinents;
}

//	Return the number of minor continents
char getMinorContinents(int diceRoll)
{
	char numberOfMinorContinents = 0;
	if (diceRoll < 31)	{numberOfMinorContinents = diceRoller(6, MINOR_CONTINENT_MULTIPLIER_COEFFICIENT[diceRoll - 1 - 16 - 16]) + MINOR_CONTINENT_ADDITION_COEFFICIENT[diceRoll - 1 - 16];}
	else						{numberOfMinorContinents = 0;}

	numberOfMinorContinents = (numberOfMinorContinents < 0) || (numberOfMinorContinents > 18) ? 0 : numberOfMinorContinents;

	return numberOfMinorContinents;
}

//	Return the number of major islands
char getMajorIslands(int diceRoll)
{
	char numberOfMajorIslands = 0;
	if 		(diceRoll < 30)	{numberOfMajorIslands = diceRoller(6, 3) - 3;}
	else if (diceRoll == 30)	{numberOfMajorIslands = diceRoller(6, 2);}
	else if (diceRoll == 31)	{numberOfMajorIslands = diceRoller(6, 1) - 3;}
	else							{numberOfMajorIslands = 0;}

	numberOfMajorIslands = (numberOfMajorIslands < 0) || (numberOfMajorIslands > 15) ? 0 : numberOfMajorIslands;

	return numberOfMajorIslands;
}

//	Return the number of archipelagoes
char getArchipelagoes(int diceRoll)
{
	char numberOfArchipelagoes = 0;
	if 		(diceRoll < 32)							{numberOfArchipelagoes = diceRoller(6, 2);}
	else if (diceRoll < 35 && diceRoll > 31)	{numberOfArchipelagoes = 1;}
	else													{numberOfArchipelagoes = 0;}

	numberOfArchipelagoes = (numberOfArchipelagoes < 0) || (numberOfArchipelagoes > 12) ? 0 : numberOfArchipelagoes;

	return numberOfArchipelagoes;
}
