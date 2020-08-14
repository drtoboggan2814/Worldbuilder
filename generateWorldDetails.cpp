//	These functions only apply to advanced worldbuilding
//	Therefore, all functions in this file will end with _ADVANCED
//	C++ libraries
#include <cmath>
#include <iostream>
#include <string>
#include <tuple>

//	Constant declarations
#include "declarations/constants/gasGiantSizeTableConstants.h"
#include "declarations/constants/planetaryOrbitalEccentricityTableConstants.h"
#include "declarations/constants/universalConstants.h"

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
string determineWorldType_ADVANCED(string sizeClass, float blackbodyTemperature, int moonStatus, float stellarMass, float stellarAge, bool gasGiantTinySulfurPresent)
{
	string worldType;

	if (sizeClass == "Terrestrial Planet (Tiny)")
	{
		if (blackbodyTemperature <= 140)
		{
			if (gasGiantTinySulfurPresent == false)
				{
					int diceRoll = diceRoller(6, 1);
					worldType = (diceRoll > 3) ? "Tiny (Sulfur)" : "Tiny (Ice)";
				}

			else {worldType = "Tiny (Ice)";}
		}

		else 																{worldType = "Tiny (Rock)";}
	}

	else if (sizeClass == "Terrestrial Planet (Small)")
	{
		if 		(blackbodyTemperature <= 80) 								{worldType = "Small (Hadean)";}
		else if (blackbodyTemperature >= 81 && blackbodyTemperature <= 140) {worldType = "Small (Ice)";}
		else 																{worldType = "Small (Rock)";}
	}

	else if (sizeClass == "Terrestrial Planet (Standard)")
	{
		if 		(blackbodyTemperature <= 80)								{worldType = "Standard (Hadean)";}
		else if (blackbodyTemperature >= 81 && blackbodyTemperature <= 150) {worldType = "Standard (Ice)"	;}
		else if (blackbodyTemperature >= 151 && blackbodyTemperature <= 230)
		{
			worldType = (stellarMass <= 0.65) ? "Standard (Ammonia)" : "Standard (Ice)";
		}
		else if (blackbodyTemperature >= 231 && blackbodyTemperature <= 240) {worldType = "Standard (Ice)"	;}
		else if (blackbodyTemperature >= 241 && blackbodyTemperature <= 320)
		{
			int diceRoll = diceRoller(6, 3);
//			Add 1 to the dice roll for every 500 million years of the star's age
			int variance = floor(stellarAge / 500000000);
//			Up to a maximum of +10
			variance = (variance > 10) ? 10 : variance;
			diceRoll += variance;
//			Standard (Garden) on a roll of 18 or higher; Standard (Ocean) otherwise
			worldType = (diceRoll >= 18) ? "Standard (Garden)" : "Standard (Ocean)";
		}
		else if (blackbodyTemperature >= 81 && blackbodyTemperature <= 150) {worldType = "Standard (Greenhouse)"	;}
		else																{worldType = "Standard (Chthonian)";}
	}

	else if (sizeClass == "Terrestrial Planet (Large)")
	{
		if 		(blackbodyTemperature <= 150)								{worldType = "Large (Ice)";}
		else if (blackbodyTemperature >= 151 && blackbodyTemperature <= 230)
		{
			worldType = (stellarMass <= 0.65) ? "Large (Ammonia)" : "Large (Ice)";
		}
		else if (blackbodyTemperature >= 231 && blackbodyTemperature <= 240) {worldType = "Large (Ice)"	;}
		else if (blackbodyTemperature >= 241 && blackbodyTemperature <= 320)
		{
			int diceRoll = diceRoller(6, 3);
//			Add 1 to the dice roll for every 500 million years of the star's age
			int variance = floor(stellarAge / 500000000);
//			Up to a maximum of +5
			variance = (variance > 5) ? 5 : variance;
			diceRoll += variance;
//			Standard (Garden) on a roll of 18 or higher; Standard (Ocean) otherwise
			worldType = (diceRoll >= 18) ? "Large (Garden)" : "Large (Ocean)";
		}
		else if (blackbodyTemperature >= 321 && blackbodyTemperature <= 500) {worldType = "Large (Greenhouse)";}
		else																 {worldType = "Large (Chthonian)";}
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
float getGasGiantMass(string gasGiantSize)
{
	int diceRoll = diceRoller(6, 3);
	float gasGiantMass;
	float massVariance = floatRNG(-0.5, 0.5);
//	int tableIndex, tableIndexPlusMinus;

	float tableInUse[9];

	if 		(gasGiantSize == "Small Gas Giant" ) {for (int i = 0; i < 9; i++) {tableInUse[i] = smallMassTable[i] ;}}
	else if (gasGiantSize == "Medium Gas Giant") {for (int i = 0; i < 9; i++) {tableInUse[i] = mediumMassTable[i];}}
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

float getGasGiantDensity(string gasGiantSize)
{
	int diceRoll = diceRoller(6, 3);
	float gasGiantDensity;
	float densityVariance = floatRNG(-0.1, 0.1);

	float tableInUse[9];

	if 		(gasGiantSize == "Small Gas Giant" ) {for (int i = 0; i < 9; i++) {tableInUse[i] = smallDensityTable[i] ;}}
	else if (gasGiantSize == "Medium Gas Giant") {for (int i = 0; i < 9; i++) {tableInUse[i] = mediumDensityTable[i];}}
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

float calculatePlanetaryOrbitalEccentricity(string worldType, string gasGiantArrangement, float snowLineRadius, float planetOrbitalRadius, float innerLimitRadius)
{
	int eccentricityRoll = diceRoller(6, 3);
	if (worldType == "Small Gas Giant" || worldType == "Medium Gas Giant" || worldType == "Large Gas Giant")
	{
		if 		(gasGiantArrangement == "Eccentric Gas Giant" 	&& planetOrbitalRadius <= snowLineRadius  ) {eccentricityRoll += 4 ;}
		else if (gasGiantArrangement == "Epistellar Gas Giant" 	&& planetOrbitalRadius <= innerLimitRadius) {eccentricityRoll += -6;}
		else if (gasGiantArrangement == "Conventional Gas Giant"										  ) {eccentricityRoll += -6;}
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

float calculateSatelliteOrbitalRadius(float planetDiameter, string moonType, string gasGiantMoonType, float distanceToClosestMoon, int moonSize)
{
	float satelliteOrbitalRadius;

//	For the moonlets of a gas giant's first family
	if (gasGiantMoonType == "First Family" && moonType == "Moonlet")
	{
		satelliteOrbitalRadius = ((diceRoller(6, 1) + 4) / 4) * planetDiameter;
	}

//	For the major moons of a gas giant's second family
	else if (gasGiantMoonType == "Second Family" && moonType == "Major moon")
	{
		do
		{
			int secondFamilyRoll = diceRoller(6, 3) + 3;
			satelliteOrbitalRadius = (secondFamilyRoll >= 15) ? secondFamilyRoll + diceRoller(6, 2) : satelliteOrbitalRadius;
			satelliteOrbitalRadius = (satelliteOrbitalRadius / 2) * planetDiameter;
		} while((satelliteOrbitalRadius - distanceToClosestMoon) <= planetDiameter);
	}

//	For the moonlets of a gas giant's third family
	else if (gasGiantMoonType == "Third Family" && moonType == "Moonlet")
	{
		satelliteOrbitalRadius = floatRNG(20, 400) * planetDiameter;
	}

//	For terrestrial major moons
	else if (moonType == "Major moon")
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
int rotationPeriodTable(string worldType)
{
	int modifier;
	if 		(worldType == "Large Gas Giant" || worldType == "Medium Gas Giant") 																																										{modifier = 0;}
	else if (worldType == "Small Gas Giant" || worldType == "Large (Garden)" || worldType == "Large (Ocean)" || worldType == "Large (Ammonia)" || worldType == "Large (Greenhouse)" || worldType == "Large (Ice)" || worldType == "Large (Chthonian)")  {modifier = 6;}
	else if (worldType == "Standard (Ice)" || worldType == "Standard (Garden)" || worldType == "Standard (Ocean)" || worldType == "Standard (Ammonia)" || worldType == "Standard (Greenhouse)") 														{modifier = 10;}
	else if (worldType == "Small (Ice)" || worldType == "Small (Hadean)" || worldType == "Small (Rock)") 																																				{modifier = 14;}
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
float calculateRotationPeriod(float totalTidalEffect, float worldOrbitalPeriod, string worldType, bool tidalLockedOrNot)
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
bool checkForRetrogradeRotation(string satelliteOrPlanet)
{
	bool retrogradeOrNot;
	int diceRoll = diceRoller(6, 3);

	if (satelliteOrPlanet == "Planet") {retrogradeOrNot = (diceRoll >= 13) ? true : false;}
	else							   {retrogradeOrNot = (diceRoll >= 17) ? true : false;}

	return retrogradeOrNot;
}

//	This function can return the length of a day on a planet or satellite or the
//	satellite's apprent orbital cycle as seen from the planet it orbits
float determineLocalCalendar(float rotationPeriod, bool retrogradeOrNot, string satelliteOrPlanet, float worldOrbitalPeriod, string satelliteDayLengthOrOrbitalCycle, float parentPlanetOrbitalPeriod)
{
	float siderealPeriod, apparentLength;
	const float YEARS_TO_DAYS = 365.26;
	const float DAYS_TO_HOURS = 24;
//	To calculate the length of a day on a planet in hours
	if (satelliteOrPlanet == "Planet")
	{
		siderealPeriod = worldOrbitalPeriod * YEARS_TO_DAYS * DAYS_TO_HOURS;
		rotationPeriod *= (retrogradeOrNot == true) ? -1 : 1;
		apparentLength = (siderealPeriod * rotationPeriod) / (siderealPeriod - rotationPeriod);
	}

//	To calculate the length of a day on a satellite
	else if (satelliteOrPlanet == "Moon" && satelliteDayLengthOrOrbitalCycle == "Day Length")
	{
		siderealPeriod = parentPlanetOrbitalPeriod * YEARS_TO_DAYS * DAYS_TO_HOURS;
		rotationPeriod *= (retrogradeOrNot == true) ? -1 : 1;
		apparentLength = (siderealPeriod * rotationPeriod) / (siderealPeriod - rotationPeriod);
	}

//	To calculate the apparent length of a moon's orbital cycle seen from the
//	planet's surface
	else if (satelliteDayLengthOrOrbitalCycle == "Orbital Cycle")
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
string volcanicActivityTable(string worldType, float surfaceGravity, float worldAge, string satelliteOrPlanet, int numberOfMajorMoons, string parentWorldType)
{
	string volcanicActivityLevel;
//	If the world is terrestrial
	if (worldType != "Small Gas Giant" && worldType != "Medium Gas Giant" && worldType != "Large Gas Giant")
	{
		int volcanicActivityModifier = round((surfaceGravity / worldAge) * 40);
		int volcanicActivityRoll = diceRoller(6, 3);

//		For planets
		if (satelliteOrPlanet == "Planet")
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

		if (worldType == "Tiny (Sulfur") {volcanicActivityModifier += 60;}

//		If the world is a major moon of a gas giant
		if (satelliteOrPlanet == "Satellite" && (parentWorldType == "Small Gas Giant" || parentWorldType == "Medium Gas Giant" && parentWorldType == "Large Gas Giant")) {volcanicActivityModifier += 5;}

		volcanicActivityRoll += volcanicActivityModifier;

		if 		(volcanicActivityRoll <= 16) 							   {volcanicActivityLevel = "None"	  ;}
		else if (volcanicActivityRoll >= 17 && volcanicActivityRoll <= 20) {volcanicActivityLevel = "Light"	  ;}
		else if (volcanicActivityRoll >= 21 && volcanicActivityRoll <= 26) {volcanicActivityLevel = "Moderate";}
		else if (volcanicActivityRoll >= 27 && volcanicActivityRoll <= 70) {volcanicActivityLevel = "Heavy"	  ;}
		else															   {volcanicActivityLevel = "Extreme" ;}
	}


//	For gas giants
	else
	{
		volcanicActivityLevel = "None";
	}
	return volcanicActivityLevel;
}

//	This function checks for the effects of volcanic activity on the atmospheres
//	of garden worlds
atmosphericComposition_t volcanicActivityEffectOnGardenWorld(string volcanicActivityLevel, string worldType, atmosphericComposition_t worldAtmosphereComposition)
{
	int checkForEffects = diceRoller(6, 3);
	int sulfurOrPollutants = diceRoller(6, 1);

	if (((checkForEffects <= 8 && volcanicActivityLevel == "Heavy") || (checkForEffects <= 14 && volcanicActivityLevel == "Extreme")) && (worldType == "Large (Garden)" || worldType == "Standard (Garden)"))
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
string tectonicActivtyTable(int diceRoll)
{
	string tectonicActivityLevel;

	if 		(diceRoll <= 6					 ) {tectonicActivityLevel = "None"	 ;}
	else if (diceRoll >= 7 	&& diceRoll <= 10) {tectonicActivityLevel = "Light"	 ;}
	else if (diceRoll >= 11 && diceRoll <= 14) {tectonicActivityLevel = "Moderate";}
	else if (diceRoll >= 15 && diceRoll <= 18) {tectonicActivityLevel = "Heavy"	 ;}
	else 									   {tectonicActivityLevel = "Extreme" ;}

	return tectonicActivityLevel;
}

//	Returns the level of tectonic activity of the world
string getTectonicActivity(string worldType, string volcanicActivityLevel, float hydrographicCoverage, string satelliteOrPlanet, int numberOfMajorMoons)
{
	string tectonicActivityLevel;

//	Gas giants, tiny worlds, and small worlds have no tectonic activity
	if (worldType == "Small Gas Giant" || worldType == "Medium Gas Giant" || worldType == "Large Gas Giant" || worldType == "Tiny (Ice)" || worldType == "Tiny (Rock)" || worldType == "Tiny (Sulfur)" || worldType == "Small (Hadean)" || worldType == "Small (Ice)" || worldType == "Small (Rock)")
	{
		tectonicActivityLevel = "None";
	}

//	For every other type of world
	else
	{
		int tectonicActivityTableRoll = diceRoller(6, 3);
		int tectonicActivityTableRollModifier;

//		Effects of volcanic activity on tectonic activity
		if (volcanicActivityLevel == "None") {tectonicActivityTableRollModifier += -8;}
		else if (volcanicActivityLevel == "Light") {tectonicActivityTableRollModifier += -4;}
		else if (volcanicActivityLevel == "Moderate") {tectonicActivityTableRollModifier += 0;}
		else if (volcanicActivityLevel == "Heavy") {tectonicActivityTableRollModifier += 4;}
		else if (volcanicActivityLevel == "Extreme") {tectonicActivityTableRollModifier += 8;}

//		The effect of liquid oceans on tectonic activity
		if (hydrographicCoverage == 0) {tectonicActivityTableRollModifier += -4;}
		else if (hydrographicCoverage <= 0.5) {tectonicActivityTableRollModifier += -2;}

//		The effect of major moons on tectonic activity
		if (satelliteOrPlanet == "Planet" && numberOfMajorMoons == 1) {tectonicActivityTableRollModifier += 2;}
		else if (satelliteOrPlanet == "Planet" && numberOfMajorMoons > 1) {tectonicActivityTableRollModifier += 4;}

		tectonicActivityTableRoll += tectonicActivityTableRollModifier;
		tectonicActivityLevel = tectonicActivtyTable(tectonicActivityTableRoll);
	}

	return tectonicActivityLevel;
}

//	This function applies the effects of geologic activity on the world's
//	habitability and resource value modifiers
tuple<int, int> effectsOfGeologicActivity(string volcanicActivityLevel, string tectonicActivityLevel, int resourceValueModifier, int habitabilityModifier)
{
	if 		(volcanicActivityLevel == "None"	) {resourceValueModifier += -2;}
	else if (volcanicActivityLevel == "Light"	) {resourceValueModifier += -1;}
	else if (volcanicActivityLevel == "Moderate") {resourceValueModifier += 0 ;}
	else if (volcanicActivityLevel == "Heavy"	)
	{
		resourceValueModifier += 1;
		habitabilityModifier += -1;
	}
	else if (volcanicActivityLevel == "Extreme")
	{
		resourceValueModifier += 2;
		habitabilityModifier += -2;
	}

	if 		(tectonicActivityLevel == "Heavy"  ) {habitabilityModifier += -1;}
	else if (tectonicActivityLevel == "Extreme") {habitabilityModifier += -2;}

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
