#ifndef WORLD_T
#define WORLD_T

#include <cstdint>
#include "atmosphericComposition_t.h"
#include "moonlet_t.h"
#include "moon_t.h"

//	#include <string>

//	using namespace std;

struct world_t
{
//	Is this a blank world (empty orbit)?
//	True if empty, false otherwise
	bool emptyOrNot;
	char sizeClass;
//	Overall attributes and GURPS scores

//	Describes the overall type the world is
	char overallType;
//	Describes the specific type of world it is
	char worldType;
//	The world's resource value modifier
	int8_t resourceValueModifier;
//	The world's habitability modifier
	int8_t habitabilityModifier;

//	Physical attributes
//	The world's density in terms of the Earth
	float worldDensity;
//	The world's diameter in terms of the Earth
	float worldDiameter;
//	The world's surface gravity in terms of Terran G's
	float surfaceGravity;
//	The world's mass in terms of the Earth's
	float worldMass;
//	The world's volcanic activity level
	char volcanicActivityLevel;
//	The world's tectonic activity level
	char tectonicActivityLevel;
//	The percentage of the world covered by liquid oceans
	float hydrographicCoverage;
//	The world's surface temperature in K
	float surfaceTemperature;
//	The world's blackbody correction
	float blackbodyCorrection;
//	The world's blackbody temperature in K
	float blackbodyTemperature;
//	The world's magnetic field strength in term of Earth's
	float magneticFieldStrength;
//	The equatorial rotation velocity in m/s
	float equatorialRotationVelocity;
//	The irradiance received at the top of the world's atmosphere
	float surfaceIrradiance;
//	Average surface area (not every world will be mapped)
	float totalSurfaceArea;
//	Land surface area
	float landSurfaceArea;
//	Liquid surface area
	float liquidSurfaceArea;

//	Atmosphere
//	The world's atmospheric mass in terms of the Earth's
	float atmosphereMass;
//	Describes the atmospheric composition
	atmosphericComposition_t worldAtmosphereComposition;
//	The world's greenhouse factor
	float greenhouseFactor;
//	The world's absorption factor
	float absorptionFactor;
//	The world's atmospheric pressure in terms of the Earth's
	float atmosphericPressure;
//	The category the world's atmosphere falls into
	char atmosphericPressureCategory;
//	The minimum molecular weight retained by the world
	float minimumMolecularWeightRetained;

//	Astronomical attributes
//	The orbital radius of the planet around its primary
	float orbitalRadius;
//	The orbital period of the world around its primary in years
	float orbitalPeriod;
//	The planet's orbital eccentricity
	float orbitalEccentricity;
//	The minimum separations from the primary in AU
	float minimumSeparation;
//	The maximum separations from the primary in AU
	float maximumSeparation;
//	The world's rotation period in hours
	float rotationPeriod;
//	Check if the world has a retrograde rotation
	bool retrogradeOrNot;
//	The length of an apparent day in hours
	float apparentDayLength;
//	The world's axial tilt in degrees
	int8_t axialTilt;
//	Is the world in a stable resonant pattern
	bool resonantOrNot;
//	Is the world tidally locked
	bool tidalLockedOrNot;
//	World's escape velocity
	float escapeVelocity;

//	Moons
//	The major moons of the world (maximum of 12)
	moon_t majorMoonArray[8];
//	The orbital radii of each major moon
	float majorMoonOrbitalRadiusArray[8];
//	The number of major moons
	int8_t numberOfMajorMoons;
//	The number of moonlets orbiting a terrestrial world
	int8_t terrestrialMoonlet;
//	The size class of the moon
	int8_t moonSizeClass;

//	For moons
//	The orbital radius of the moon around its planet
	float satelliteOrbitalRadius;
//	The apparent length of a satellite's orbital cycle as seen from the planet
	float apparentSatelliteOrbitalCycle;
//	The orbital period of the satellite
	float satelliteOrbitalPeriod;

//	Tidal effects
//	The tidal force exerted on the planet by the satellite
	float tidalForceOnPlanetBySatellite;
//	The tidal force exerted on the satellite by the planet
	float tidalForceOnSatelliteByPlanet;
//	The tidal force exerted on the planet by the primary
	float tidalForceOnPlanetByPrimary;
//	The total tidal effect
	float totalTidalEffect;

//	For gas giants
	int8_t firstFamilyMoonlets;
	int8_t secondFamilyMajorMoons;
	int8_t thirdFamilyMoonlets;
	int8_t ringSystemVisibility;
	bool gasGiantTinySulfurPresent;

	moonlet_t firstFamilyMoonletArray[12];
	moonlet_t thirdFamilyMoonletArray[6];

//	Mapping information
	uint8_t hexesPerSide;
	uint16_t totalHexes;
};

#endif
