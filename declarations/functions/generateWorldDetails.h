#include <cstdint>
#include <tuple>
#include "../structures/atmosphericComposition_t.h"
//	BLACKBODY TEMPERATURE
//	Calculate the blackbody temperature of the world and its moons (if any)
float calculateBlackbodyTemperature_ADVANCED(float stellarLuminosity, float averageOrbitalRadius);

//	DESIGNATE WORLD TYPES
/*
	This functions returns the worldType given the size class from orbitContentsTable
	its blackbody temperature, and whether it is not a moon (moonStatus = 0),
	orbits a terrestrial world (moonStatus = 1), or it orbits a gas giant
	(moonStatus = 2)
*/
char determineWorldType_ADVANCED(const char& sizeClass, const float& blackbodyTemperature, const char& moonStatus, const float& stellarMass, const float& stellarAge, const bool& gasGiantTinySulfurPresent);

//	CLIMATE
//	This function calculates the world's average surface temperature
float averageSurfaceTemperature_ADVANCED(const float& blackbodyTemperature, const float& blackbodyCorrection);

//	WORLD SIZES
/*
	This function applies only to gas giants, as the original functions still apply
	to terrestrial worlds
*/
float getGasGiantMass(const char& gasGiantSize);
float getGasGiantDensity(const char& gasGiantSize);
float getGasGiantDiameter(const float& gasGiantMass, const float& gasGiantDensity);

//	DYNAMIC PARAMETERS
/*
	This function only applies systems with more than one star
	If there are three or more stars, then the stars that have already had their
	orbital periods calculated are treated as one star that the next star outwards
	orbits
*/
float calculateStellarOrbitalPeriod(const float& averageOrbitalRadius, const float& solarMassSum);

//	This function returns a planet's orbital period around its primary
float calculatePlanetaryOrbitalPeriod(const float& planetOrbitalRadius, const float& stellarMass, const float& planetMass);

//	This function returns the world's orbital eccentricity, with a variance added on
float planetaryOrbitalEccentricityTable();

float calculatePlanetaryOrbitalEccentricity(const char& worldType, const char& gasGiantArrangement, const float& snowLineRadius, const float& planetOrbitalRadius, const float& innerLimitRadius);

//	The following two functions return the minimum and maximum separations
//	between a planet and its primary, respectively
float calculatePlanetPrimaryMinimumSeparation(const float& planetOrbitalRadius, const float& planetaryOrbitalEccentricity);
float calculatePlanetPrimaryMaximumSeparation(const float& planetOrbitalRadius, const float& planetaryOrbitalEccentricity);
float calculateSatelliteOrbitalRadius(const float& planetDiameter, const bool& moonType, const char& gasGiantMoonType, const float& distanceToClosestMoon, const char& moonSize);
float calculateSatelliteOrbitalPeriod(const float& satelliteOrbitalRadius, const float& planetMass, const float& satteliteMass);
float calculateSatelliteOrbitalPeriod(const float& satelliteOrbitalRadius, const float& planetMass, const float& satteliteMass);
float calculateTidalForceOnSatelliteByPlanet(const float& planetMass, const float& satelliteDiameter, const float& satelliteOrbitalRadius);
float calculateTidalForceOnPlanetBySatellite(const float& satteliteMass, const float& planetDiameter, const float& satelliteOrbitalRadius);
float calculateTidalForceOnPlanetByPrimary(const float& solarMass, const float& planetDiameter, const float& planetOrbitalRadius);

//	This function can apply to both planets and satellites
float calculateTotalTidalEffect(const float& satelliteTidalForce, const float& primaryTidalForcee, const float& planetTidalForce, const float& starSystemAge, const float& worldMass);

//	Returns the modifier for the world's rotation period
int rotationPeriodTable(const char& worldType);

//	If the world's rotation period is especially slow, this table returns an appropriate rotation period
int specialRotationTable(const int& specialRotationTableRoll);

//	This function returns the planet's sidereal rotation in standard hours
float calculateRotationPeriod(const float& totalTidalEffect, const float& worldOrbitalPeriod, const char& worldType, const bool& tidalLockedOrNot);

//	This function determines if a world's rotation is retrograde
bool checkForRetrogradeRotation(const bool& satelliteOrPlanet);

//	This function can return the length of a day on a planet or satellite or the
//	satellite's apprent orbital cycle as seen from the planet it orbits
float determineLocalCalendar(const float& rotationPeriod, const bool& retrogradeOrNot, const bool& satelliteOrPlanet, const float& worldOrbitalPeriod, const bool& satelliteDayLengthOrOrbitalCycle, const float& parentPlanetOrbitalPeriod);
//	This table returns the world's axial tilt in degrees
int8_t axialTiltTable(const int& diceRoll);

//	If the roll for the world's axial tilt is 17 or 18, use this table
int8_t extendedAxialTiltTable(const int& diceRoll);

//	This function uses the two tables above and returns the world's axial tilt
int8_t calculateAxialTilt();

//	GEOLOGIC ACTIVITY
char volcanicActivityTable(const char& worldType, const float& surfaceGravity, const float& worldAge, const bool& satelliteOrPlanet, const int8_t& numberOfMajorMoons, const char& parentWorldType);

//	This function checks for the effects of volcanic activity on the atmospheres
//	of garden worlds
atmosphericComposition_t volcanicActivityEffectOnGardenWorld(const char& volcanicActivityLevel, const char& worldType, const atmosphericComposition_t& worldAtmosphereComposition);

//	This function serves as a lookup table for the world's tectonic activity
char tectonicActivtyTable(const int& diceRoll);

//	Returns the level of tectonic activity of the world
char getTectonicActivity(const char& worldType, const char& volcanicActivityLevel, const float& hydrographicCoverage, const bool& satelliteOrPlanet, const int8_t& numberOfMajorMoons);

//	This function applies the effects of geologic activity on the world's
//	habitability and resource value modifiers
std::tuple<int8_t, int8_t> effectsOfGeologicActivity(const char& volcanicActivityLevel, const char& tectonicActivityLevel, const int8_t& resourceValueModifier, const int8_t& habitabilityModifier);
double getEscapeVelocity(const double& escapeMass, const double& distanceToCenterOfMass);
float getMagneticField(const float& worldMass, const float& worldDensity, const float& rotationPeriod, const float& stellarAge, const char& worldType);
float apparentOrbitingBodySize(const float& bodyDiameter, const float& distanceFromBody);
float calculateDistanceToHorizon(const float& worldDiameter, const float& distanceFromSurface);
float getEquatorialRotationVelocity(const float& diameter, const float& rotationPeriod);
std::tuple<float, float, float> getSurfaceArea(const float& worldDiameter, const float& hydrographicCoverage);
