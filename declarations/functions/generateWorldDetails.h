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
char determineWorldType_ADVANCED(const char& sizeClass, float blackbodyTemperature, const char& moonStatus, float stellarMass, float stellarAge, const bool& gasGiantTinySulfurPresent);

//	CLIMATE
//	This function calculates the world's average surface temperature
float averageSurfaceTemperature_ADVANCED(float blackbodyTemperature, float blackbodyCorrection);

//	WORLD SIZES
/*
	This function applies only to gas giants, as the original functions still apply
	to terrestrial worlds
*/
float getGasGiantMass(const char& gasGiantSize);
float getGasGiantDensity(const char& gasGiantSize);
float getGasGiantDiameter(float gasGiantMass, float gasGiantDensity);

//	DYNAMIC PARAMETERS
/*
	This function only applies systems with more than one star
	If there are three or more stars, then the stars that have already had their
	orbital periods calculated are treated as one star that the next star outwards
	orbits
*/
float calculateStellarOrbitalPeriod(float averageOrbitalRadius, float solarMassSum);

//	This function returns a planet's orbital period around its primary
float calculatePlanetaryOrbitalPeriod(float planetOrbitalRadius, float stellarMass, float planetMass);

//	This function returns the world's orbital eccentricity, with a variance added on
float planetaryOrbitalEccentricityTable();

float calculatePlanetaryOrbitalEccentricity(const char& worldType, const char& gasGiantArrangement, float snowLineRadius, float planetOrbitalRadius, float innerLimitRadius);

//	The following two functions return the minimum and maximum separations
//	between a planet and its primary, respectively
float calculatePlanetPrimaryMinimumSeparation(float planetOrbitalRadius, float planetaryOrbitalEccentricity);
float calculatePlanetPrimaryMaximumSeparation(float planetOrbitalRadius, float planetaryOrbitalEccentricity);
float calculateSatelliteOrbitalRadius(float planetDiameter, const bool& moonType, const char& gasGiantMoonType, float distanceToClosestMoon, const char& moonSize);
float calculateSatelliteOrbitalPeriod(float satelliteOrbitalRadius, float planetMass, float satteliteMass);
float calculateSatelliteOrbitalPeriod(float satelliteOrbitalRadius, float planetMass, float satteliteMass);
float calculateTidalForceOnSatelliteByPlanet(float planetMass, float satelliteDiameter, float satelliteOrbitalRadius);
float calculateTidalForceOnPlanetBySatellite(float satteliteMass, float planetDiameter, float satelliteOrbitalRadius);
float calculateTidalForceOnPlanetByPrimary(float solarMass, float planetDiameter, float planetOrbitalRadius);

//	This function can apply to both planets and satellites
float calculateTotalTidalEffect(float satelliteTidalForce, float primaryTidalForcee, float planetTidalForce, float starSystemAge, float worldMass);

//	Returns the modifier for the world's rotation period
int rotationPeriodTable(const char& worldType);

//	If the world's rotation period is especially slow, this table returns an appropriate rotation period
int specialRotationTable(int specialRotationTableRoll);

//	This function returns the planet's sidereal rotation in standard hours
float calculateRotationPeriod(float totalTidalEffect, float worldOrbitalPeriod, const char& worldType, const bool& tidalLockedOrNot);

//	This function determines if a world's rotation is retrograde
bool checkForRetrogradeRotation(const bool& satelliteOrPlanet);

//	This function can return the length of a day on a planet or satellite or the
//	satellite's apprent orbital cycle as seen from the planet it orbits
float determineLocalCalendar(float rotationPeriod, const bool& retrogradeOrNot, const bool& satelliteOrPlanet, float worldOrbitalPeriod, const bool& satelliteDayLengthOrOrbitalCycle, float parentPlanetOrbitalPeriod);
//	This table returns the world's axial tilt in degrees
int8_t axialTiltTable(int diceRoll);

//	If the roll for the world's axial tilt is 17 or 18, use this table
int8_t extendedAxialTiltTable(int diceRoll);

//	This function uses the two tables above and returns the world's axial tilt
int8_t calculateAxialTilt();

//	GEOLOGIC ACTIVITY
char volcanicActivityTable(const char& worldType, float surfaceGravity, float worldAge, const bool& satelliteOrPlanet, int8_t numberOfMajorMoons, const char& parentWorldType);

//	This function checks for the effects of volcanic activity on the atmospheres
//	of garden worlds
atmosphericComposition_t volcanicActivityEffectOnGardenWorld(const char& volcanicActivityLevel, const char& worldType, const atmosphericComposition_t& worldAtmosphereComposition);

//	This function serves as a lookup table for the world's tectonic activity
char tectonicActivtyTable(int diceRoll);

//	Returns the level of tectonic activity of the world
char getTectonicActivity(const char& worldType, const char& volcanicActivityLevel, float hydrographicCoverage, const bool& satelliteOrPlanet, int8_t numberOfMajorMoons);

//	This function applies the effects of geologic activity on the world's
//	habitability and resource value modifiers
std::tuple<int8_t, int8_t> effectsOfGeologicActivity(const char& volcanicActivityLevel, const char& tectonicActivityLevel, int8_t resourceValueModifier, int8_t habitabilityModifier);
double getEscapeVelocity(const double& escapeMass, const double& distanceToCenterOfMass);
float getMagneticField(float worldMass, float worldDensity, float rotationPeriod, float stellarAge, const char& worldType);
float apparentOrbitingBodySize(float bodyDiameter, float distanceFromBody);
float calculateDistanceToHorizon(float worldDiameter, float distanceFromSurface);
float getEquatorialRotationVelocity(float diameter, float rotationPeriod);
std::tuple<float, float, float> getSurfaceArea(float worldDiameter, float hydrographicCoverage);
