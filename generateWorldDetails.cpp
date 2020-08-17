//	These functions only apply to advanced worldbuilding
//	Therefore, all functions in this file will end with _ADVANCED

//	C++ libraries
#include <cmath>
#include <iostream>
#include <string>
#include <tuple>

//	Constant declarations
#include "declarations/constants/gasGiantArrangementConstants.h"
#include "declarations/constants/gasGiantSizeTableConstants.h"
#include "declarations/constants/planetaryOrbitalEccentricityTableConstants.h"
#include "declarations/constants/miscConstants.h"
#include "declarations/constants/sizeClassConstants.h"
#include "declarations/constants/tectonicActivityLevelConstants.h"
#include "declarations/constants/volcanicActivityLevelConstants.h"
#include "declarations/constants/universalConstants.h"
#include "declarations/constants/worldTypeConstants.h"

//	Structure declarations
#include "declarations/structures/world_t.h"

//	Function declarations
#include "declarations/functions/diceRoller.h"
#include "declarations/functions/floatRNG.h"

using namespace std;

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
char determineWorldType_ADVANCED(char sizeClass, float blackbodyTemperature, int moonStatus, float stellarMass, float stellarAge, bool gasGiantTinySulfurPresent)
{
	char worldType;

	if (sizeClass == SC_EMPTY_ORBIT)
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
	else
	{
		worldType = sizeClass;
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
float getGasGiantMass(char gasGiantSize)
{
	int diceRoll = diceRoller(6, 3);
	float gasGiantMass;
	float massVariance = floatRNG(-0.5, 0.5);
//	int tableIndex, tableIndexPlusMinus;

	float tableInUse[9];

	if 		(gasGiantSize == WT_SMALL_GAS_GIANT ) {for (int i = 0; i < 9; i++) {tableInUse[i] = smallMassTable[i] ;}}
	else if (gasGiantSize == WT_MEDIUM_GAS_GIANT) {for (int i = 0; i < 9; i++) {tableInUse[i] = mediumMassTable[i];}}
	else 										 {for (int i = 0; i < 9; i++) {tableInUse[i] = largeMassTable[i] ;}}

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

float getGasGiantDensity(char gasGiantSize)
{
	int diceRoll = diceRoller(6, 3);
	float gasGiantDensity;
	float densityVariance = floatRNG(-0.1, 0.1);

	float tableInUse[9];

	if 		(gasGiantSize == WT_SMALL_GAS_GIANT ) {for (int i = 0; i < 9; i++) {tableInUse[i] = smallDensityTable[i] ;}}
	else if (gasGiantSize == WT_MEDIUM_GAS_GIANT) {for (int i = 0; i < 9; i++) {tableInUse[i] = mediumDensityTable[i];}}
	else 										 {for (int i = 0; i < 9; i++) {tableInUse[i] = largeDensityTable[i] ;}}

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
	float planetaryOrbitalEccentricity;
	float variance = floatRNG(-0.05, 0.05);
	int constantTableIndex;

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


	return planetaryOrbitalEccentricity;
}

float calculatePlanetaryOrbitalEccentricity(char worldType, char gasGiantArrangement, float snowLineRadius, float planetOrbitalRadius, float innerLimitRadius)
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

float calculateSatelliteOrbitalRadius(float planetDiameter, bool moonType, char gasGiantMoonType, float distanceToClosestMoon, int moonSize)
{
	float satelliteOrbitalRadius;

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
		int terrestrialMoonletRoll = diceRoller(6, 1) + 4;
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
int rotationPeriodTable(char worldType)
{
	int modifier;
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
	int specialRotation;
	if 		(specialRotationTableRoll == 7 ) {specialRotation = diceRoller(6, 1) * 2  ;}
	else if (specialRotationTableRoll == 8 ) {specialRotation = diceRoller(6, 1) * 5  ;}
	else if (specialRotationTableRoll == 9 ) {specialRotation = diceRoller(6, 1) * 10 ;}
	else if (specialRotationTableRoll == 10) {specialRotation = diceRoller(6, 1) * 20 ;}
	else if (specialRotationTableRoll == 11) {specialRotation = diceRoller(6, 1) * 50 ;}
	else									 {specialRotation = diceRoller(6, 1) * 100;}

	return specialRotation;
}

//	This function returns the planet's sidereal rotation in standard hours
float calculateRotationPeriod(float totalTidalEffect, float worldOrbitalPeriod, char worldType, bool tidalLockedOrNot)
{
	float rotationPeriod;

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
bool checkForRetrogradeRotation(bool satelliteOrPlanet)
{
	bool retrogradeOrNot;
	int diceRoll = diceRoller(6, 3);

	if (satelliteOrPlanet == POM_PLANET) {retrogradeOrNot = (diceRoll >= 13) ? true : false;}
	else							   {retrogradeOrNot = (diceRoll >= 17) ? true : false;}

	return retrogradeOrNot;
}

//	This function can return the length of a day on a planet or satellite or the
//	satellite's apprent orbital cycle as seen from the planet it orbits
float determineLocalCalendar(float rotationPeriod, bool retrogradeOrNot, bool satelliteOrPlanet, float worldOrbitalPeriod, bool satelliteDayLengthOrOrbitalCycle, float parentPlanetOrbitalPeriod)
{
	float siderealPeriod, apparentLength;
	const float YEARS_TO_DAYS = 365.26;
	const float DAYS_TO_HOURS = 24;
//	To calculate the length of a day on a planet in hours
	if (satelliteOrPlanet == POM_PLANET)
	{
		siderealPeriod = worldOrbitalPeriod * YEARS_TO_DAYS * DAYS_TO_HOURS;
		rotationPeriod *= (retrogradeOrNot == true) ? -1 : 1;
		apparentLength = (siderealPeriod * rotationPeriod) / (siderealPeriod - rotationPeriod);
	}

//	To calculate the length of a day on a satellite
	else if (satelliteOrPlanet == POM_MOON && satelliteDayLengthOrOrbitalCycle == CALO_DAY_LENGTH)
	{
		siderealPeriod = parentPlanetOrbitalPeriod * YEARS_TO_DAYS * DAYS_TO_HOURS;
		rotationPeriod *= (retrogradeOrNot == true) ? -1 : 1;
		apparentLength = (siderealPeriod * rotationPeriod) / (siderealPeriod - rotationPeriod);
	}

//	To calculate the apparent length of a moon's orbital cycle seen from the
//	planet's surface
	else if (satelliteDayLengthOrOrbitalCycle == CALO_ORBITAL_CYCLE)
	{
		siderealPeriod = worldOrbitalPeriod * YEARS_TO_DAYS * DAYS_TO_HOURS;
		rotationPeriod = parentPlanetOrbitalPeriod * YEARS_TO_DAYS * DAYS_TO_HOURS;
		rotationPeriod *= (retrogradeOrNot == true) ? -1 : 1;
		apparentLength = (siderealPeriod * rotationPeriod) / (siderealPeriod - rotationPeriod);
	}

	return apparentLength;
}

//	This table returns the world's axial tilt in degrees
int axialTiltTable(int diceRoll)
{
	int axialTilt;
	if 		(diceRoll >= 3 	|| diceRoll <= 6 ) {axialTilt = 0  + (diceRoller(6, 2) - 2);}
	else if (diceRoll >= 7 	|| diceRoll <= 9 ) {axialTilt = 10 + (diceRoller(6, 2) - 2);}
	else if (diceRoll >= 10 || diceRoll <= 12) {axialTilt = 20 + (diceRoller(6, 2) - 2);}
	else if (diceRoll >= 13 || diceRoll <= 14) {axialTilt = 30 + (diceRoller(6, 2) - 2);}
	else									   {axialTilt = 40 + (diceRoller(6, 2) - 2);}

	return axialTilt;
}

//	If the roll for the world's axial tilt is 17 or 18, use this table
int extendedAxialTiltTable(int diceRoll)
{
	int axialTilt;
	if 		(diceRoll == 1 || diceRoll == 2) {axialTilt = 50 + (diceRoller(6, 2) - 2);}
	else if (diceRoll == 3 || diceRoll == 4) {axialTilt = 60 + (diceRoller(6, 2) - 2);}
	else if (diceRoll == 5) 				 {axialTilt = 70 + (diceRoller(6, 2) - 2);}
	else 									 {axialTilt = 80 + (diceRoller(6, 2) - 2);}

	return axialTilt;
}

//	This function uses the two tables above and returns the world's axial tilt
int calculateAxialTilt()
{
	int diceRoll = diceRoller(6, 3);
	int axialTilt = (diceRoll >= 17) ? extendedAxialTiltTable(diceRoll) : axialTiltTable(diceRoll);
	return axialTilt;
}

//	GEOLOGIC ACTIVITY
char volcanicActivityTable(char worldType, float surfaceGravity, float worldAge, bool satelliteOrPlanet, int numberOfMajorMoons, char parentWorldType)
{
	char volcanicActivityLevel;
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
atmosphericComposition_t volcanicActivityEffectOnGardenWorld(char volcanicActivityLevel, char worldType, atmosphericComposition_t worldAtmosphereComposition)
{
	int checkForEffects = diceRoller(6, 3);
	int sulfurOrPollutants = diceRoller(6, 1);

	if (((checkForEffects <= 8 && volcanicActivityLevel == VAL_HEAVY) || (checkForEffects <= 14 && volcanicActivityLevel == VAL_EXTREME)) && (worldType == WT_LARGE_GARDEN || worldType == WT_STANDARD_GARDEN))
	{
		if 		(sulfurOrPollutants >= 1 && sulfurOrPollutants <= 2) {worldAtmosphereComposition.sulfurCompounds = 1;}
		else if (sulfurOrPollutants >= 3 && sulfurOrPollutants <= 4) {worldAtmosphereComposition.pollutants = 1;}
		else
		{
			worldAtmosphereComposition.sulfurCompounds = 1;
			worldAtmosphereComposition.pollutants = 1;
		}
	}

	return worldAtmosphereComposition;
}

//	This function serves as a lookup table for the world's tectonic activity
char tectonicActivtyTable(int diceRoll)
{
	char tectonicActivityLevel;

	if 		(diceRoll <= 6					 ) {tectonicActivityLevel = TAL_NONE;}
	else if (diceRoll >= 7 	&& diceRoll <= 10) {tectonicActivityLevel = TAL_LIGHT;}
	else if (diceRoll >= 11 && diceRoll <= 14) {tectonicActivityLevel = TAL_MODERATE;}
	else if (diceRoll >= 15 && diceRoll <= 18) {tectonicActivityLevel = TAL_HEAVY;}
	else 									   {tectonicActivityLevel = TAL_EXTREME;}

	return tectonicActivityLevel;
}

//	Returns the level of tectonic activity of the world
char getTectonicActivity(char worldType, char volcanicActivityLevel, float hydrographicCoverage, bool satelliteOrPlanet, int numberOfMajorMoons)
{
	char tectonicActivityLevel;

//	Gas giants, tiny worlds, and small worlds have no tectonic activity
	if (worldType == WT_SMALL_GAS_GIANT || worldType == WT_MEDIUM_GAS_GIANT || worldType == WT_LARGE_GAS_GIANT || worldType == WT_TINY_ICE || worldType == WT_TINY_SULFUR || worldType == WT_TINY_SULFUR || worldType == WT_SMALL_HADEAN || worldType == WT_SMALL_ICE || worldType == WT_SMALL_ROCK)
	{
		tectonicActivityLevel = TAL_NONE;
	}

//	For every other type of world
	else
	{
		int tectonicActivityTableRoll = diceRoller(6, 3);
		int tectonicActivityTableRollModifier;

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
tuple<int, int> effectsOfGeologicActivity(char volcanicActivityLevel, char tectonicActivityLevel, int resourceValueModifier, int habitabilityModifier)
{
	if 		(volcanicActivityLevel == VAL_NONE	) {resourceValueModifier += -2;}
	else if (volcanicActivityLevel == VAL_LIGHT	) {resourceValueModifier += -1;}
	else if (volcanicActivityLevel == VAL_MODERATE) {resourceValueModifier += 0 ;}
	else if (volcanicActivityLevel == VAL_HEAVY	)
	{
		resourceValueModifier += 1;
		habitabilityModifier += -1;
	}
	else if (volcanicActivityLevel == VAL_EXTREME)
	{
		resourceValueModifier += 2;
		habitabilityModifier += -2;
	}

	if 		(tectonicActivityLevel == VAL_HEAVY  ) {habitabilityModifier += -1;}
	else if (tectonicActivityLevel == VAL_EXTREME) {habitabilityModifier += -2;}

	return make_tuple(habitabilityModifier, resourceValueModifier);
}

//	Calculate the body's escape velocity
//	NOTE: This is not included in GURPS 4e Space
//	Parameters must be passed in terms of m and kg
double getEscapeVelocity(double escapeMass, double distanceToCenterOfMass)
{
//	v_e = sqrt((2*G*M) / r)
	double escapeVelocity = sqrt((2 * UNIVERSAL_GRAVITATIONAL_CONSTANT * escapeMass) / distanceToCenterOfMass);
	return escapeVelocity;
}
