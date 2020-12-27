//	These functions only apply to advanced worldbuilding
//	Therefore, all functions in this file will end with _ADVANCED

//	C++ libraries
#include <cmath>
#include <cstdint>
#include <iostream>
//	#include <string>
#include <tuple>

//	Constant declarations
#include "declarations/constants/gasGiantArrangementConstants.h"
#include "declarations/constants/gasGiantSizeTableConstants.h"
#include "declarations/constants/planetaryOrbitalEccentricityTableConstants.h"
#include "declarations/constants/miscConstants.h"
#include "declarations/constants/sizeClassConstants.h"
#include "declarations/constants/stringConstants.h"
#include "declarations/constants/tectonicActivityLevelConstants.h"
#include "declarations/constants/volcanicActivityLevelConstants.h"
#include "declarations/constants/unitConversions.h"
#include "declarations/constants/universalConstants.h"
#include "declarations/constants/worldTypeConstants.h"

//	Structure declarations
#include "declarations/structures/world_t.h"

//	Function declarations
#include "declarations/functions/diceRoller.h"
#include "declarations/functions/floatRNG.h"

//	using namespace std;

//	BLACKBODY TEMPERATURE
//	Calculate the blackbody temperature of the world and its moons (if any)
float calculateBlackbodyTemperature_ADVANCED(float stellarLuminosity, float averageOrbitalRadius)
{
	float blackbodyTemperature = 278 * (pow(stellarLuminosity, 1/4)) / sqrt(averageOrbitalRadius);
	return blackbodyTemperature;
}

//	DESIGNATE WORLD TYPES
/*
	This functions returns the worldType given the size class from orbitContentsTable
	its blackbody temperature, and whether it is not a moon (moonStatus = 0),
	orbits a terrestrial world (moonStatus = 1), or it orbits a gas giant
	(moonStatus = 2)
*/
char determineWorldType_ADVANCED(const char& sizeClass, float blackbodyTemperature, const char& moonStatus, float stellarMass, float stellarAge, const bool& gasGiantTinySulfurPresent)
{
	char worldType = 0;
//	cout << "Size class = " << SC_S_LOOKUP_TABLE[(int )sizeClass] << endl;

	if (sizeClass == SC_TERRESTRIAL_PLANET_TINY)
	{
		if (blackbodyTemperature <= 140)
		{
			if (gasGiantTinySulfurPresent == false)
				{
					int diceRoll = diceRoller(6, 1);
					worldType = (diceRoll > 3) ? WT_TINY_SULFUR : WT_TINY_ICE;
				}

			else {worldType = WT_TINY_ICE;}
		}

		else 																{worldType = WT_TINY_SULFUR;}
	}

	else if (sizeClass == SC_TERRESTRIAL_PLANET_SMALL)
	{
		if 		(blackbodyTemperature <= 80) 								{worldType = WT_SMALL_HADEAN;}
		else if (blackbodyTemperature >= 81 && blackbodyTemperature <= 140) {worldType = WT_SMALL_ICE;}
		else 																{worldType = WT_SMALL_ROCK;}
	}

	else if (sizeClass == SC_TERRESTRIAL_PLANET_STANDARD)
	{
		if 		(blackbodyTemperature <= 80)								{worldType = WT_STANDARD_HADEAN;}
		else if (blackbodyTemperature >= 81 && blackbodyTemperature <= 150) {worldType = WT_STANDARD_ICE	;}
		else if (blackbodyTemperature >= 151 && blackbodyTemperature <= 230)
		{
			worldType = (stellarMass <= 0.65) ? WT_STANDARD_AMMONIA : WT_STANDARD_ICE;
		}
		else if (blackbodyTemperature >= 231 && blackbodyTemperature <= 240) {worldType = WT_STANDARD_ICE	;}
		else if (blackbodyTemperature >= 241 && blackbodyTemperature <= 320)
		{
			int diceRoll = diceRoller(6, 3);
//			Add 1 to the dice roll for every 500 million years of the star's age
			int variance = floor(stellarAge / 500000000);
//			Up to a maximum of +10
			variance = (variance > 10) ? 10 : variance;
			diceRoll += variance;
//			Standard (Garden) on a roll of 18 or higher; Standard (Ocean) otherwise
			worldType = (diceRoll >= 18) ? WT_STANDARD_GARDEN : WT_STANDARD_OCEAN;
		}
		else if (blackbodyTemperature >= 81 && blackbodyTemperature <= 150) {worldType = WT_STANDARD_GREENHOUSE	;}
		else																{worldType = WT_STANDARD_CHTHONIAN;}
	}

	else if (sizeClass == SC_TERRESTRIAL_PLANET_LARGE)
	{
		if 		(blackbodyTemperature <= 150)								{worldType = WT_LARGE_ICE;}
		else if (blackbodyTemperature >= 151 && blackbodyTemperature <= 230)
		{
			worldType = (stellarMass <= 0.65) ? WT_LARGE_AMMONIA : WT_LARGE_ICE;
		}
		else if (blackbodyTemperature >= 231 && blackbodyTemperature <= 240) {worldType = WT_LARGE_ICE	;}
		else if (blackbodyTemperature >= 241 && blackbodyTemperature <= 320)
		{
			int diceRoll = diceRoller(6, 3);
//			Add 1 to the dice roll for every 500 million years of the star's age
			int variance = floor(stellarAge / 500000000);
//			Up to a maximum of +5
			variance = (variance > 5) ? 5 : variance;
			diceRoll += variance;
//			Standard (Garden) on a roll of 18 or higher; Standard (Ocean) otherwise
			worldType = (diceRoll >= 18) ? WT_LARGE_GARDEN : WT_LARGE_OCEAN;
		}
		else if (blackbodyTemperature >= 321 && blackbodyTemperature <= 500) {worldType = WT_LARGE_GREENHOUSE;}
		else																 {worldType = WT_LARGE_CHTHONIAN;}
	}

//	For asteroid belts and gas giants
	else if (sizeClass == SC_ASTEROID_BELT)
	{
		worldType = WT_ASTEROID_BELT;
	}

	else if (sizeClass == SC_SMALL_GAS_GIANT)
	{
		worldType = WT_SMALL_GAS_GIANT;
	}

	else if (sizeClass == SC_MEDIUM_GAS_GIANT)
	{
		worldType = WT_MEDIUM_GAS_GIANT;
	}

	else if (sizeClass == SC_LARGE_GAS_GIANT)
	{
		worldType = WT_LARGE_GAS_GIANT;
	}

	else if (sizeClass == SC_EMPTY_ORBIT)
	{
		worldType = WT_EMPTY_ORBIT;
	}

	return worldType;
}

//	CLIMATE
//	This function calculates the world's average surface temperature
float averageSurfaceTemperature_ADVANCED(float blackbodyTemperature, float blackbodyCorrection)
{
	float averageSurfaceTemperature = blackbodyCorrection * blackbodyTemperature;
	return averageSurfaceTemperature;
}

//	WORLD SIZES
/*
	This function applies only to gas giants, as the original functions still apply
	to terrestrial worlds
*/
float getGasGiantMass(const char& gasGiantSize)
{
	int diceRoll = diceRoller(6, 3);
	float gasGiantMass = 0;
	float massVariance = floatRNG(-0.5, 0.5);
//	int tableIndex, tableIndexPlusMinus;

	float tableInUse[9];

	if 		(gasGiantSize == WT_SMALL_GAS_GIANT ) {for (int  i = 0; i < 9; i++) {tableInUse[i] = SMALLMASSTABLE[i] ;}}
	else if (gasGiantSize == WT_MEDIUM_GAS_GIANT) {for (int  i = 0; i < 9; i++) {tableInUse[i] = MEDIUMMASSTABLE[i];}}
	else 										 {for (int  i = 0; i < 9; i++) {tableInUse[i] = LARGEMASSTABLE[i] ;}}

	if 		(diceRoll <= 8					) {gasGiantMass = tableInUse[0];}
	else if (diceRoll >= 9 && diceRoll <= 10) {gasGiantMass = tableInUse[1];}
	else if (diceRoll == 11					) {gasGiantMass = tableInUse[2];}
	else if (diceRoll == 11					) {gasGiantMass = tableInUse[3];}
	else if (diceRoll == 11					) {gasGiantMass = tableInUse[4];}
	else if (diceRoll == 11					) {gasGiantMass = tableInUse[5];}
	else if (diceRoll == 11					) {gasGiantMass = tableInUse[6];}
	else if (diceRoll == 11					) {gasGiantMass = tableInUse[7];}
	else									  {gasGiantMass = tableInUse[8];}

//	tableIndexPlusMinus = massVariance < 0 ? -1 : 1;
	gasGiantMass += massVariance * gasGiantMass;

	return gasGiantMass;
}

float getGasGiantDensity(const char& gasGiantSize)
{
	int diceRoll = diceRoller(6, 3);
	float gasGiantDensity = 0;
	float densityVariance = floatRNG(-0.1, 0.1);

	float tableInUse[9];

	if 		(gasGiantSize == WT_SMALL_GAS_GIANT ) {for (int  i = 0; i < 9; i++) {tableInUse[i] = SMALLDENSITYTABLE[i] ;}}
	else if (gasGiantSize == WT_MEDIUM_GAS_GIANT) {for (int  i = 0; i < 9; i++) {tableInUse[i] = MEDIUMDENSITYTABLE[i];}}
	else 										 {for (int  i = 0; i < 9; i++) {tableInUse[i] = LARGEDENSITYTABLE[i] ;}}

	if 		(diceRoll <= 8					) {gasGiantDensity = tableInUse[0];}
	else if (diceRoll >= 9 && diceRoll <= 10) {gasGiantDensity = tableInUse[1];}
	else if (diceRoll == 11					) {gasGiantDensity = tableInUse[2];}
	else if (diceRoll == 11					) {gasGiantDensity = tableInUse[3];}
	else if (diceRoll == 11					) {gasGiantDensity = tableInUse[4];}
	else if (diceRoll == 11					) {gasGiantDensity = tableInUse[5];}
	else if (diceRoll == 11					) {gasGiantDensity = tableInUse[6];}
	else if (diceRoll == 11					) {gasGiantDensity = tableInUse[7];}
	else									  {gasGiantDensity = tableInUse[8];}

	gasGiantDensity += gasGiantDensity * densityVariance;

	return gasGiantDensity;
}

float getGasGiantDiameter(float gasGiantMass, float gasGiantDensity)
{
	float gasGiantDiameter = cbrt(gasGiantMass / gasGiantDensity);
	return gasGiantDiameter;
}

//	DYNAMIC PARAMETERS
/*
	This function only applies systems with more than one star
	If there are three or more stars, then the stars that have already had their
	orbital periods calculated are treated as one star that the next star outwards
	orbits
*/
float calculateStellarOrbitalPeriod(float averageOrbitalRadius, float solarMassSum)
{
	float stellarOrbitalPeriod = sqrt(pow(averageOrbitalRadius, 3) / solarMassSum);
	return stellarOrbitalPeriod;
}

//	This function returns a planet's orbital period around its primary
float calculatePlanetaryOrbitalPeriod(float planetOrbitalRadius, float stellarMass, float planetMass)
{
	const float EARTHTOSOLARMASS = 0.000003;
	float planetaryOrbitalPeriod = sqrt(pow(planetOrbitalRadius, 3) / (stellarMass + planetMass * EARTHTOSOLARMASS));
	return planetaryOrbitalPeriod;
}

//	This function returns the world's orbital eccentricity, with a variance added on
float planetaryOrbitalEccentricityTable(int diceRoll)
{
	float planetaryOrbitalEccentricity = 0;
	float variance = floatRNG(-0.05, 0.05);
	int constantTableIndex = 0;

	if 		(diceRoll <= 3					 ) {planetaryOrbitalEccentricity = eccentricityConstants[0 ]; constantTableIndex = 0 ;}
	else if (diceRoll >= 4 	&& diceRoll <= 6 ) {planetaryOrbitalEccentricity = eccentricityConstants[1 ]; constantTableIndex = 1 ;}
	else if (diceRoll >= 7 	&& diceRoll <= 9 ) {planetaryOrbitalEccentricity = eccentricityConstants[2 ]; constantTableIndex = 2 ;}
	else if (diceRoll == 10 || diceRoll == 11) {planetaryOrbitalEccentricity = eccentricityConstants[3 ]; constantTableIndex = 3 ;}
	else if (diceRoll == 12					 ) {planetaryOrbitalEccentricity = eccentricityConstants[4 ]; constantTableIndex = 4 ;}
	else if (diceRoll == 13					 ) {planetaryOrbitalEccentricity = eccentricityConstants[5 ]; constantTableIndex = 5 ;}
	else if (diceRoll == 14					 ) {planetaryOrbitalEccentricity = eccentricityConstants[6 ]; constantTableIndex = 6 ;}
	else if (diceRoll == 15					 ) {planetaryOrbitalEccentricity = eccentricityConstants[7 ]; constantTableIndex = 7 ;}
	else if (diceRoll == 16					 ) {planetaryOrbitalEccentricity = eccentricityConstants[8 ]; constantTableIndex = 8 ;}
	else if (diceRoll == 17					 ) {planetaryOrbitalEccentricity = eccentricityConstants[9 ]; constantTableIndex = 9 ;}
	else									   {planetaryOrbitalEccentricity = eccentricityConstants[10]; constantTableIndex = 10;}

	if 		(variance < 0					 ) {planetaryOrbitalEccentricity += variance * (eccentricityConstants[constantTableIndex] - eccentricityConstants[constantTableIndex - 1]);}
	else									   {planetaryOrbitalEccentricity += variance * (eccentricityConstants[constantTableIndex + 1] - eccentricityConstants[constantTableIndex]);}

	planetaryOrbitalEccentricity = (planetaryOrbitalEccentricity < 0.00001) ? 0 : planetaryOrbitalEccentricity;
	return planetaryOrbitalEccentricity;
}

float calculatePlanetaryOrbitalEccentricity(const char& worldType, const char& gasGiantArrangement, float snowLineRadius, float planetOrbitalRadius, float innerLimitRadius)
{
	int eccentricityRoll = diceRoller(6, 3);
	if (worldType == WT_SMALL_GAS_GIANT || worldType == WT_MEDIUM_GAS_GIANT || worldType == WT_LARGE_GAS_GIANT)
	{
		if 		(gasGiantArrangement == GGA_ECCENTRIC_GAS_GIANT 	&& planetOrbitalRadius <= snowLineRadius  ) {eccentricityRoll += 4 ;}
		else if (gasGiantArrangement == GGA_EPISTELLAR_GAS_GIANT 	&& planetOrbitalRadius <= innerLimitRadius) {eccentricityRoll += -6;}
		else if (gasGiantArrangement == GGA_CONVENTIONAL_GAS_GIANT										  ) {eccentricityRoll += -6;}
		else																							 	{eccentricityRoll += 0 ;}
	}

	float planetaryOrbitalEccentricity = planetaryOrbitalEccentricityTable(eccentricityRoll);
	return planetaryOrbitalEccentricity;
}

//	The following two functions return the minimum and maximum separations
//	between a planet and its primary, respectively
float calculatePlanetPrimaryMinimumSeparation(float planetOrbitalRadius, float planetaryOrbitalEccentricity)
{
	float minimumSeparation = (1 - planetaryOrbitalEccentricity) * planetOrbitalRadius;
	return minimumSeparation;
}

float calculatePlanetPrimaryMaximumSeparation(float planetOrbitalRadius, float planetaryOrbitalEccentricity)
{
	float maximumSeparation = (1 + planetaryOrbitalEccentricity) * planetOrbitalRadius;
	return maximumSeparation;
}

float calculateSatelliteOrbitalRadius(float planetDiameter, const bool& moonType, const char& gasGiantMoonType, float distanceToClosestMoon, const char& moonSize)
{
	float satelliteOrbitalRadius = 0;

//	For the moonlets of a gas giant's first family
	if (gasGiantMoonType == GGM_FIRST_FAMILY && moonType == MT_MOONLET)
	{
		satelliteOrbitalRadius = ((diceRoller(6, 1) + 4) / 4) * planetDiameter;
	}

//	For the major moons of a gas giant's second family
	else if (gasGiantMoonType == GGM_SECOND_FAMILY && moonType == MT_MOON)
	{
		do
		{
			int secondFamilyRoll = diceRoller(6, 3) + 3;
			satelliteOrbitalRadius = (secondFamilyRoll >= 15) ? secondFamilyRoll + diceRoller(6, 2) : satelliteOrbitalRadius;
			satelliteOrbitalRadius = (satelliteOrbitalRadius / 2) * planetDiameter;
		} while((satelliteOrbitalRadius - distanceToClosestMoon) <= planetDiameter);
	}

//	For the moonlets of a gas giant's third family
	else if (gasGiantMoonType == GGM_THIRD_FAMILY && moonType == MT_MOONLET)
	{
		satelliteOrbitalRadius = floatRNG(20, 400) * planetDiameter;
	}

//	For terrestrial major moons
	else if (moonType == MT_MOON)
	{
		do
		{
			int terrestrialMajorMoonRoll = diceRoller(6, 2);
			if 		(moonSize == -2) {terrestrialMajorMoonRoll += 2;}
			else if (moonSize == -1) {terrestrialMajorMoonRoll += 4;}
			else 					 {terrestrialMajorMoonRoll += 0;}

			satelliteOrbitalRadius = (terrestrialMajorMoonRoll * 2.5) * planetDiameter;
		} while((satelliteOrbitalRadius - distanceToClosestMoon) <= (5 * planetDiameter));
	}

//	For terrestrial moonlets
	else
	{
		int8_t terrestrialMoonletRoll = diceRoller(6, 1) + 4;
		satelliteOrbitalRadius = (terrestrialMoonletRoll / 4) * planetDiameter;
	}

	return satelliteOrbitalRadius;
}

float calculateSatelliteOrbitalPeriod(float satelliteOrbitalRadius, float planetMass, float satteliteMass)
{
//	0.166 is given by the errata, while the book gives 0.0588
	float satteliteOrbitalPeriod = 0.166 * sqrt(pow(satelliteOrbitalRadius, 3) / (planetMass + satteliteMass));
	return satteliteOrbitalPeriod;
}

float calculateTidalForceOnPlanetBySatellite(float satteliteMass, float planetDiameter, float satelliteOrbitalRadius)
{
//	22.3 * 10^6 is given by the errata, while the book gives 17.8 * 10^6
	float tidalForceExerted = ((22.3 * pow(10, 6)) * satteliteMass * planetDiameter) / pow(satelliteOrbitalRadius, 3);
	return tidalForceExerted;
}

float calculateTidalForceOnSatelliteByPlanet(float planetMass, float satelliteDiameter, float satelliteOrbitalRadius)
{
	float tidalForceExerted = ((17.8 * pow(10, 6)) * planetMass * satelliteDiameter) / pow(satelliteOrbitalRadius, 3);
	return tidalForceExerted;
}

float calculateTidalForceOnPlanetByPrimary(float solarMass, float planetDiameter, float planetOrbitalRadius)
{
	float tidalForceExerted = (0.46 * solarMass * planetDiameter) / pow(planetOrbitalRadius, 3);
	return tidalForceExerted;
}

//	This function can apply to both planets and satellites
float calculateTotalTidalEffect(float satelliteTidalForce, float primaryTidalForcee, float planetTidalForce, float starSystemAge, float worldMass)
{
	float totalTidalEffect = ((primaryTidalForcee + satelliteTidalForce + planetTidalForce) * starSystemAge) / worldMass;
	return totalTidalEffect;
}

//	Returns the modifier for the world's rotation period
int rotationPeriodTable(const char& worldType)
{
	int modifier = 0;
	if 		(worldType == WT_LARGE_GAS_GIANT || worldType == WT_MEDIUM_GAS_GIANT) 																																										{modifier = 0;}
	else if (worldType == WT_SMALL_GAS_GIANT || worldType == WT_LARGE_GARDEN || worldType == WT_LARGE_OCEAN || worldType == WT_LARGE_AMMONIA || worldType == WT_LARGE_GREENHOUSE || worldType == WT_LARGE_ICE || worldType == WT_LARGE_CHTHONIAN)  {modifier = 6;}
	else if (worldType == WT_STANDARD_ICE || worldType == WT_STANDARD_GARDEN || worldType == WT_STANDARD_OCEAN || worldType == WT_STANDARD_AMMONIA || worldType == WT_STANDARD_GREENHOUSE) 														{modifier = 10;}
	else if (worldType == WT_SMALL_ICE || worldType == WT_SMALL_HADEAN || worldType == WT_SMALL_ROCK) 																																				{modifier = 14;}
	else 																																																												{modifier = 18;}
	return modifier;
}

//	If the world's rotation period is especially slow, this table returns an appropriate rotation period
int specialRotationTable(int specialRotationTableRoll)
{
	int specialRotation = 0;
	if 		(specialRotationTableRoll == 7 ) {specialRotation = diceRoller(6, 1) * 2  ;}
	else if (specialRotationTableRoll == 8 ) {specialRotation = diceRoller(6, 1) * 5  ;}
	else if (specialRotationTableRoll == 9 ) {specialRotation = diceRoller(6, 1) * 10 ;}
	else if (specialRotationTableRoll == 10) {specialRotation = diceRoller(6, 1) * 20 ;}
	else if (specialRotationTableRoll == 11) {specialRotation = diceRoller(6, 1) * 50 ;}
	else									 {specialRotation = diceRoller(6, 1) * 100;}

	return specialRotation;
}

//	This function returns the planet's sidereal rotation in standard hours
float calculateRotationPeriod(float totalTidalEffect, float worldOrbitalPeriod, const char& worldType, const bool& tidalLockedOrNot)
{
	float rotationPeriod = 0;

//	If the world is tidally locked, then its rotation and orbital periods are equal
	if (tidalLockedOrNot == true) {rotationPeriod = worldOrbitalPeriod;}

	else
	{
		do
		{
//			Roll on rotationPeriodTable
			int rotationPeriodTableRoll = diceRoller(6, 3);
			int rotationPeriodModifier = rotationPeriodTable(worldType);

			if ((rotationPeriodTableRoll >= 16) || ((rotationPeriodModifier + rotationPeriodTableRoll) > 36))
			{
//					The world has an especially slow rotation period
				int specialRotationTableRoll = diceRoller(6, 2);
				rotationPeriod = (specialRotationTableRoll <= 6) ? rotationPeriod : specialRotationTable(specialRotationTableRoll);
			}

//			If the world's rotation period is longer than it would be if it were tidally locked,
//			then it is tidally locked
			if (rotationPeriod > worldOrbitalPeriod) {rotationPeriod =  worldOrbitalPeriod;}
			else									 {rotationPeriod += totalTidalEffect  ;}

//			Add or remove up to five days from the world's rotation period
			float variance = floatRNG(-120, 120);
			rotationPeriod += variance;

//		Make sure that the rotation period is greater than 0
		} while (rotationPeriod <= 0);
	}

	return rotationPeriod;
}

//	This function determines if a world's rotation is retrograde
bool checkForRetrogradeRotation(const bool& satelliteOrPlanet)
{
	bool retrogradeOrNot = false;
	int diceRoll = diceRoller(6, 3);

	if (satelliteOrPlanet == POM_PLANET) {retrogradeOrNot = (diceRoll >= 13) ? true : false;}
	else							   {retrogradeOrNot = (diceRoll >= 17) ? true : false;}

	return retrogradeOrNot;
}

//	This function can return the length of a day on a planet or satellite or the
//	satellite's apprent orbital cycle as seen from the planet it orbits
float determineLocalCalendar(float rotationPeriod, const bool& retrogradeOrNot, const bool& satelliteOrPlanet, float worldOrbitalPeriod, const bool& satelliteDayLengthOrOrbitalCycle, float parentPlanetOrbitalPeriod)
{
	float siderealPeriod = 0;
	float apparentLength = 0;
	float rotationPeriodTemp = rotationPeriod;
	const float YEARS_TO_DAYS = 365.26;
	const float DAYS_TO_HOURS = 24;
//	To calculate the length of a day on a planet in hours
	if (satelliteOrPlanet == POM_PLANET)
	{
		siderealPeriod = worldOrbitalPeriod * YEARS_TO_DAYS * DAYS_TO_HOURS;
		rotationPeriodTemp *= (retrogradeOrNot == true) ? -1 : 1;
		apparentLength = (siderealPeriod * rotationPeriodTemp) / (siderealPeriod - rotationPeriodTemp);
	}

//	To calculate the length of a day on a satellite
	else if (satelliteOrPlanet == POM_MOON && satelliteDayLengthOrOrbitalCycle == CALO_DAY_LENGTH)
	{
		siderealPeriod = parentPlanetOrbitalPeriod * YEARS_TO_DAYS * DAYS_TO_HOURS;
		rotationPeriodTemp *= (retrogradeOrNot == true) ? -1 : 1;
		apparentLength = (siderealPeriod * rotationPeriodTemp) / (siderealPeriod - rotationPeriodTemp);
	}

//	To calculate the apparent length of a moon's orbital cycle seen from the
//	planet's surface
	else if (satelliteDayLengthOrOrbitalCycle == CALO_ORBITAL_CYCLE)
	{
		siderealPeriod = worldOrbitalPeriod * YEARS_TO_DAYS * DAYS_TO_HOURS;
		rotationPeriodTemp = parentPlanetOrbitalPeriod * YEARS_TO_DAYS * DAYS_TO_HOURS;
		rotationPeriodTemp *= (retrogradeOrNot == true) ? -1 : 1;
		apparentLength = (siderealPeriod * rotationPeriodTemp) / (siderealPeriod - rotationPeriodTemp);
	}

	return apparentLength;
}

//	This table returns the world's axial tilt in degrees
int8_t axialTiltTable(int diceRoll)
{
	int8_t axialTilt = 0;
	if 		(diceRoll >= 3 	|| diceRoll <= 6 ) {axialTilt = 0  + (diceRoller(6, 2) - 2);}
	else if (diceRoll >= 7 	|| diceRoll <= 9 ) {axialTilt = 10 + (diceRoller(6, 2) - 2);}
	else if (diceRoll >= 10 || diceRoll <= 12) {axialTilt = 20 + (diceRoller(6, 2) - 2);}
	else if (diceRoll >= 13 || diceRoll <= 14) {axialTilt = 30 + (diceRoller(6, 2) - 2);}
	else									   {axialTilt = 40 + (diceRoller(6, 2) - 2);}

	return axialTilt;
}

//	If the roll for the world's axial tilt is 17 or 18, use this table
int8_t extendedAxialTiltTable(int diceRoll)
{
	int8_t axialTilt = 0;
	if 		(diceRoll == 1 || diceRoll == 2) {axialTilt = 50 + (diceRoller(6, 2) - 2);}
	else if (diceRoll == 3 || diceRoll == 4) {axialTilt = 60 + (diceRoller(6, 2) - 2);}
	else if (diceRoll == 5) 				 {axialTilt = 70 + (diceRoller(6, 2) - 2);}
	else 									 {axialTilt = 80 + (diceRoller(6, 2) - 2);}

	return axialTilt;
}

//	This function uses the two tables above and returns the world's axial tilt
int8_t calculateAxialTilt()
{
	int diceRoll = diceRoller(6, 3);
	int8_t axialTilt = (diceRoll >= 17) ? extendedAxialTiltTable(diceRoll) : axialTiltTable(diceRoll);
	return axialTilt;
}

//	GEOLOGIC ACTIVITY
char volcanicActivityTable(const char& worldType, float surfaceGravity, float worldAge, const bool& satelliteOrPlanet, const int8_t& numberOfMajorMoons, const char& parentWorldType)
{
	char volcanicActivityLevel = VAL_NONE;
//	If the world is terrestrial
	if (worldType != WT_SMALL_GAS_GIANT && worldType != WT_MEDIUM_GAS_GIANT && worldType != WT_LARGE_GAS_GIANT)
	{
		int volcanicActivityModifier = round((surfaceGravity / worldAge) * 40);
		int volcanicActivityRoll = diceRoller(6, 3);

//		For planets
		if (satelliteOrPlanet == POM_PLANET)
		{
//			With at least one major moon
			if (numberOfMajorMoons >= 1)
			{
//				For one major moon
				if (numberOfMajorMoons == 1) {volcanicActivityModifier += 5	;}
//				For more than one major moons
				else						 {volcanicActivityModifier += 10;}
			}
		}

		if (worldType == WT_TINY_SULFUR) {volcanicActivityModifier += 60;}

//		If the world is a major moon of a gas giant
		if (satelliteOrPlanet == POM_MOON && (parentWorldType == WT_SMALL_GAS_GIANT || parentWorldType == WT_MEDIUM_GAS_GIANT && parentWorldType == WT_LARGE_GAS_GIANT)) {volcanicActivityModifier += 5;}

		volcanicActivityRoll += volcanicActivityModifier;

		if 		(volcanicActivityRoll <= 16) 							   {volcanicActivityLevel = VAL_NONE;}
		else if (volcanicActivityRoll >= 17 && volcanicActivityRoll <= 20) {volcanicActivityLevel = VAL_LIGHT;}
		else if (volcanicActivityRoll >= 21 && volcanicActivityRoll <= 26) {volcanicActivityLevel = VAL_MODERATE;}
		else if (volcanicActivityRoll >= 27 && volcanicActivityRoll <= 70) {volcanicActivityLevel = VAL_HEAVY;}
		else															   {volcanicActivityLevel = VAL_EXTREME;}
	}


//	For gas giants
	else
	{
		volcanicActivityLevel = VAL_NONE;
	}
	return volcanicActivityLevel;
}

//	This function checks for the effects of volcanic activity on the atmospheres
//	of garden worlds
atmosphericComposition_t volcanicActivityEffectOnGardenWorld(const char& volcanicActivityLevel, const char& worldType, const atmosphericComposition_t& worldAtmosphereComposition)
{
	int checkForEffects = diceRoller(6, 3);
	int sulfurOrPollutants = diceRoller(6, 1);
	atmosphericComposition_t worldAtmosphereCompositionTemp = worldAtmosphereComposition;
	if (((checkForEffects <= 8 && volcanicActivityLevel == VAL_HEAVY) || (checkForEffects <= 14 && volcanicActivityLevel == VAL_EXTREME)) && (worldType == WT_LARGE_GARDEN || worldType == WT_STANDARD_GARDEN))
	{
		if 		(sulfurOrPollutants >= 1 && sulfurOrPollutants <= 2) {worldAtmosphereCompositionTemp.sulfurCompounds = 1;}
		else if (sulfurOrPollutants >= 3 && sulfurOrPollutants <= 4) {worldAtmosphereCompositionTemp.pollutants = 1;}
		else
		{
			worldAtmosphereCompositionTemp.sulfurCompounds = 1;
			worldAtmosphereCompositionTemp.pollutants = 1;
		}
	}

	return worldAtmosphereCompositionTemp;
}

//	This function serves as a lookup table for the world's tectonic activity
char tectonicActivtyTable(int diceRoll)
{
	char tectonicActivityLevel = 0;

	if 		(diceRoll <= 6					 ) {tectonicActivityLevel = TAL_NONE;}
	else if (diceRoll >= 7 	&& diceRoll <= 10) {tectonicActivityLevel = TAL_LIGHT;}
	else if (diceRoll >= 11 && diceRoll <= 14) {tectonicActivityLevel = TAL_MODERATE;}
	else if (diceRoll >= 15 && diceRoll <= 18) {tectonicActivityLevel = TAL_HEAVY;}
	else 									   {tectonicActivityLevel = TAL_EXTREME;}

	return tectonicActivityLevel;
}

//	Returns the level of tectonic activity of the world
char getTectonicActivity(const char& worldType, const char& volcanicActivityLevel, float hydrographicCoverage, const bool& satelliteOrPlanet, const int8_t& numberOfMajorMoons)
{
	char tectonicActivityLevel = TAL_NONE;

//	Gas giants, tiny worlds, and small worlds have no tectonic activity
	if (worldType == WT_SMALL_GAS_GIANT || worldType == WT_MEDIUM_GAS_GIANT || worldType == WT_LARGE_GAS_GIANT || worldType == WT_TINY_ICE || worldType == WT_TINY_SULFUR || worldType == WT_TINY_SULFUR || worldType == WT_SMALL_HADEAN || worldType == WT_SMALL_ICE || worldType == WT_SMALL_ROCK)
	{
		tectonicActivityLevel = TAL_NONE;
	}

//	For every other type of world
	else
	{
		int tectonicActivityTableRoll = diceRoller(6, 3);
		int tectonicActivityTableRollModifier = 0;

//		Effects of volcanic activity on tectonic activity
		if 		(volcanicActivityLevel == VAL_NONE) {tectonicActivityTableRollModifier += -8;}
		else if (volcanicActivityLevel == VAL_LIGHT) {tectonicActivityTableRollModifier += -4;}
		else if (volcanicActivityLevel == VAL_MODERATE) {tectonicActivityTableRollModifier += 0;}
		else if (volcanicActivityLevel == VAL_HEAVY) {tectonicActivityTableRollModifier += 4;}
		else if (volcanicActivityLevel == VAL_EXTREME) {tectonicActivityTableRollModifier += 8;}

//		The effect of liquid oceans on tectonic activity
		if (hydrographicCoverage == 0) {tectonicActivityTableRollModifier += -4;}
		else if (hydrographicCoverage <= 0.5) {tectonicActivityTableRollModifier += -2;}

//		The effect of major moons on tectonic activity
		if (satelliteOrPlanet == POM_PLANET && numberOfMajorMoons == 1) {tectonicActivityTableRollModifier += 2;}
		else if (satelliteOrPlanet == POM_PLANET && numberOfMajorMoons > 1) {tectonicActivityTableRollModifier += 4;}

		tectonicActivityTableRoll += tectonicActivityTableRollModifier;
		tectonicActivityLevel = tectonicActivtyTable(tectonicActivityTableRoll);
	}

	return tectonicActivityLevel;
}

//	This function applies the effects of geologic activity on the world's
//	habitability and resource value modifiers
tuple<int8_t, int8_t> effectsOfGeologicActivity(const char& volcanicActivityLevel, const char& tectonicActivityLevel, const int8_t& resourceValueModifier, const int8_t& habitabilityModifier)
{
	char volcanicActivityLevelTemp = volcanicActivityLevel;
	char tectonicActivityLevelTemp = tectonicActivityLevel;
	int8_t resourceValueModifierTemp = resourceValueModifier;
	int8_t habitabilityModifierTemp = habitabilityModifier;
	if 		(volcanicActivityLevelTemp == VAL_NONE	) {resourceValueModifierTemp += -2;}
	else if (volcanicActivityLevelTemp == VAL_LIGHT	) {resourceValueModifierTemp += -1;}
	else if (volcanicActivityLevelTemp == VAL_MODERATE) {resourceValueModifierTemp += 0 ;}
	else if (volcanicActivityLevelTemp == VAL_HEAVY	)
	{
		resourceValueModifierTemp += 1;
		habitabilityModifierTemp += -1;
	}
	else if (volcanicActivityLevelTemp == VAL_EXTREME)
	{
		resourceValueModifierTemp += 2;
		habitabilityModifierTemp += -2;
	}

	if 		(tectonicActivityLevelTemp == VAL_HEAVY  ) {habitabilityModifierTemp += -1;}
	else if (tectonicActivityLevelTemp == VAL_EXTREME) {habitabilityModifierTemp += -2;}

	return make_tuple(habitabilityModifierTemp, resourceValueModifierTemp);
}

//	Calculate the body's escape velocity
//	NOTE: This is not included in GURPS 4e Space
//	Parameters must be passed in terms of m and kg
double getEscapeVelocity(const double& escapeMass, const double& distanceToCenterOfMass)
{
//	v_e = sqrt((2*G*M) / r)
	double escapeVelocity = sqrt((2 * UNIVERSAL_GRAVITATIONAL_CONSTANT * escapeMass) / distanceToCenterOfMass);
	return escapeVelocity;
}

//	Determine the world's magnetic field strength
//	NOTE: This is from World Generation: Generic System & Planet Building Resources
//	magneticFieldStrength is returned as a factor of Earth's magnetic field strength
//	Since Earth's magnetic field strength is variable across the surface, so too is it on another world
//	If a detailed analysis is required, then a surface map of the world is needed
//	As a result, this only gives a rough estimate that is of minimal utility
float getMagneticField(float worldMass, float worldDensity, float rotationPeriod, float stellarAge, const char& worldType)
{
	float magFactor = 10 * (1 / sqrt(rotationPeriod / 24)) * (worldDensity * worldDensity) * (sqrt(worldMass) / stellarAge);
	magFactor = (worldType == WT_TINY_ICE || worldType == WT_SMALL_ICE || worldType == WT_STANDARD_ICE || worldType == WT_LARGE_ICE) ? magFactor * 0.5 : magFactor;

	float magneticFieldStrength = 0;
	int diceRoll = diceRoller(10, 1);
	if 		(magFactor < 0.05 || (magFactor >= 0.05 && magFactor < 0.5 && diceRoll < 6) || (diceRoll < 4 && magFactor >= 0.5 && magFactor < 1))																									{magneticFieldStrength = 0;}
	else if ((diceRoll >= 1 && diceRoll <= 3 && magFactor >= 1 && magFactor < 2) || ((diceRoll == 4 || diceRoll == 5) && magFactor >= 0.5 && magFactor < 1) || ((diceRoll == 6 || diceRoll == 7) && magFactor >= 0.05 && magFactor < 0.5))		{magneticFieldStrength = diceRoller(10, 1) * 0.001;}
	else if (((diceRoll == 4 || diceRoll == 5) && magFactor >= 1 && magFactor < 2) || ((diceRoll == 6 || diceRoll == 7) && magFactor >= 0.5 && magFactor < 1) || ((diceRoll == 8 || diceRoll == 9) && magFactor >= 0.05 && magFactor < 0.5))	{magneticFieldStrength = diceRoller(10, 1) * 0.002;}
	else if (((diceRoll == 6 || diceRoll == 7) && magFactor >= 1 && magFactor < 2) || ((diceRoll == 8 || diceRoll == 9) && magFactor >= 0.5 && magFactor < 1) || (diceRoll == 10 && magFactor >= 0.05 && magFactor < 0.5))						{magneticFieldStrength = diceRoller(10, 1) * 0.01;}
	else if ((diceRoll >= 1 && diceRoll <= 3 && magFactor >= 2 && magFactor < 4) || ((diceRoll == 8 || diceRoll == 9) && magFactor >= 1 && magFactor < 2) || (diceRoll == 10 && magFactor >= 0.5 && magFactor < 1))								{magneticFieldStrength = diceRoller(10, 1) * 0.05;}
	else if ((diceRoll >= 1 && diceRoll <= 3 && magFactor >= 4) || ((diceRoll == 4 || diceRoll == 5) && magFactor >= 2 && magFactor < 4) || (diceRoll == 10 && magFactor >= 1 && magFactor < 2))												{magneticFieldStrength = diceRoller(10, 1) * 0.1;}
	else if (((diceRoll == 4 || diceRoll == 5) && magFactor >= 4) || ((diceRoll == 6 || diceRoll == 7) && magFactor >= 2 && magFactor < 4))																										{magneticFieldStrength = diceRoller(10, 1) * 0.2;}
	else if (((diceRoll == 6 || diceRoll == 7) && magFactor >= 4) || ((diceRoll == 8 || diceRoll == 9) && magFactor >= 2 && magFactor < 4))																										{magneticFieldStrength = diceRoller(10, 1) * 0.3;}
	else if (((diceRoll == 8 || diceRoll == 9) && magFactor >= 4) || (diceRoll == 10 && magFactor >= 2 && magFactor < 4))																														{magneticFieldStrength = diceRoller(10, 1) * 0.5;}
	else																																																										{magneticFieldStrength = diceRoller(10, 1) * 1;}

	return magneticFieldStrength;
}
/*
//	NOTE: This is from Alternity Cosmos
float getMagneticField(float worldMass, float rotationPeriod, const char& worldType)
{
	float magneticFieldStrength = 0;
	if (worldMass < 0.03)
	{
		magneticFieldStrength = 0;
	}

	else if (worldMass >= 0.03 && worldMass < 0.3)
	{
		int diceRoll = diceRoller(6, 3);
		magneticFieldStrength = diceRoll > 3 ? floatRNG(0.01, 0.1) : 0;
	}

	else if (worldMass >= 0.3 && worldMass < 3)
	{
		magneticFieldStrength = rotationPeriod < 500 ? floatRNG(0.1, 10) : floatRNG(0.01, 0.1);
	}

	else if (worldType = WT_LARGE_CHTHONIAN)
	{

	}
}
*/

//	Determine the apparent size of a body as seen from another
//	The return value is the angular diameter of the body in the sky
//	NOTE: This is from Atomic Rockets
float apparentOrbitingBodySize(float bodyDiameter, float distanceFromBody)
{
//	This value is in arcseconds
	float angularDiameter = RAD_IN_ASEC * (bodyDiameter / distanceFromBody);
	return angularDiameter;
}

//	Determine the distance to the horizon
//	The return value is in meters
//	NOTE: This is not included in GURPS Space 4e
float calculateDistanceToHorizon(float worldDiameter, float distanceFromSurface)
{
	float distanceToHorizon = sqrt(worldDiameter * EARTH_RADIUS_IN_KM * 2 * KM_TO_M * distanceFromSurface);
	return distanceToHorizon;
}

//	Determine angular velocity
//	The return value is in m/s
//	NOTE: This is not included in GURPS Space 4e
float getEquatorialRotationVelocity(float diameter, float rotationPeriod)
{
	float radius = (diameter / 2) * EARTH_RADIUS_IN_KM * KM_TO_M;
	float angularVelocity = (2 * M_PI) / (rotationPeriod * HOUR_TO_SEC);
	float equatorialRotationVelocity = angularVelocity * radius;
	return equatorialRotationVelocity;
}

//	Determine total surface area
tuple<float, float, float> getSurfaceArea(float worldDiameter, float hydrographicCoverage)
{
	float totalSurfaceArea = 4 * M_PI * pow((worldDiameter / 2) * EARTH_RADIUS_IN_KM, 2);
	float liquidSurfaceArea = totalSurfaceArea * hydrographicCoverage;
	float landSurfaceArea = totalSurfaceArea - liquidSurfaceArea;
	return make_tuple(totalSurfaceArea, liquidSurfaceArea, landSurfaceArea);
}
