#include <tuple>

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
char determineWorldType_ADVANCED(char sizeClass, float blackbodyTemperature, int moonStatus, float stellarMass, float stellarAge, bool gasGiantTinySulfurPresent);

//	CLIMATE
//	This function calculates the world's average surface temperature
float averageSurfaceTemperature_ADVANCED(float blackbodyTemperature, float blackbodyCorrection);

//	WORLD SIZES
/*
	This function applies only to gas giants, as the original functions still apply
	to terrestrial worlds
*/
float getGasGiantMass(char gasGiantSize);
float getGasGiantDensity(char gasGiantSize);
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

float calculatePlanetaryOrbitalEccentricity(char worldType, char gasGiantArrangement, float snowLineRadius, float planetOrbitalRadius, float innerLimitRadius);

//	The following two functions return the minimum and maximum separations
//	between a planet and its primary, respectively
float calculatePlanetPrimaryMinimumSeparation(float planetOrbitalRadius, float planetaryOrbitalEccentricity);
float calculatePlanetPrimaryMaximumSeparation(float planetOrbitalRadius, float planetaryOrbitalEccentricity);
float calculateSatelliteOrbitalRadius(float planetDiameter, bool moonType, char gasGiantMoonType, float distanceToClosestMoon, int moonSize);
float calculateSatelliteOrbitalPeriod(float satelliteOrbitalRadius, float planetMass, float satteliteMass);
float calculateSatelliteOrbitalPeriod(float satelliteOrbitalRadius, float planetMass, float satteliteMass);
float calculateTidalForceOnSatelliteByPlanet(float planetMass, float satelliteDiameter, float satelliteOrbitalRadius);
float calculateTidalForceOnPlanetBySatellite(float satteliteMass, float planetDiameter, float satelliteOrbitalRadius);
float calculateTidalForceOnPlanetByPrimary(float solarMass, float planetDiameter, float planetOrbitalRadius);

//	This function can apply to both planets and satellites
float calculateTotalTidalEffect(float satelliteTidalForce, float primaryTidalForcee, float planetTidalForce, float starSystemAge, float worldMass);

//	Returns the modifier for the world's rotation period
int rotationPeriodTable(char worldType);

//	If the world's rotation period is especially slow, this table returns an appropriate rotation period
int specialRotationTable(int specialRotationTableRoll);

//	This function returns the planet's sidereal rotation in standard hours
float calculateRotationPeriod(float totalTidalEffect, float worldOrbitalPeriod, char worldType, bool tidalLockedOrNot);

//	This function determines if a world's rotation is retrograde
bool checkForRetrogradeRotation(bool satelliteOrPlanet);

//	This function can return the length of a day on a planet or satellite or the
//	satellite's apprent orbital cycle as seen from the planet it orbits
float determineLocalCalendar(float rotationPeriod, bool retrogradeOrNot, bool satelliteOrPlanet, float worldOrbitalPeriod, bool satelliteDayLengthOrOrbitalCycle, float parentPlanetOrbitalPeriod);
//	This table returns the world's axial tilt in degrees
int axialTiltTable(int diceRoll);

//	If the roll for the world's axial tilt is 17 or 18, use this table
int extendedAxialTiltTable(int diceRoll);

//	This function uses the two tables above and returns the world's axial tilt
int calculateAxialTilt();

//	GEOLOGIC ACTIVITY
char volcanicActivityTable(char worldType, float surfaceGravity, float worldAge, bool satelliteOrPlanet, int numberOfMajorMoons, char parentWorldType);

//	This function checks for the effects of volcanic activity on the atmospheres
//	of garden worlds
atmosphericComposition_t volcanicActivityEffectOnGardenWorld(char volcanicActivityLevel, char worldType, atmosphericComposition_t worldAtmosphereComposition);

//	This function serves as a lookup table for the world's tectonic activity
char tectonicActivtyTable(int diceRoll);

//	Returns the level of tectonic activity of the world
char getTectonicActivity(char worldType, char volcanicActivityLevel, float hydrographicCoverage, bool satelliteOrPlanet, int numberOfMajorMoons);

//	This function applies the effects of geologic activity on the world's
//	habitability and resource value modifiers
std::tuple<int, int> effectsOfGeologicActivity(char volcanicActivityLevel, char tectonicActivityLevel, int resourceValueModifier, int habitabilityModifier);
double getEscapeVelocity(double escapeMass, double distanceToCenterOfMass);
