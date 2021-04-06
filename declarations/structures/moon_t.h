#ifndef MOON_T
#define MOON_T

//	C++ libraries
#include <cstdint>
#include <string>

//	Structures
#include "atmosphericComposition_t.h"
#include "tectonicPlate_t.h"


//	This structure describes a moon orbiting a larger world

struct moon_t
{
//	Corresponds to the "Moon Size Table" on page 112
//	-3 corresponds to "Three size classes smaller"
//	-2 corresponds to "Two size classes smaller"
//	-1 corresponds to "One size class smaller"
	int moonSizeClass;
	char sizeClass;
	char worldType;
	float orbitalRadius;
	float orbitalPeriod;
	float orbitalEccentricity;
	float minimumSeparation;
	float maximumSeparation;
	float rotationPeriod;
	bool retrogradeOrNot;
	float apparentDayLength;
	float blackbodyCorrection;
	float apparentSatelliteOrbitalCycle;
	int axialTilt;
	bool resonantOrNot;
	float atmosphericMass;
	bool tidalLockedOrNot;
	float atmosphereMass;
	float hydrographicCoverage;
	float surfaceTemperature;
	float dayFaceAverageTemperature;
	float nightFaceAverageTemperature;
	float greenhouseFactor;
	float absorptionFactor;
	float blackbodyTemperature;
	float worldDensity;
	float worldDiameter;
	float surfaceGravity;
//	The world's magnetic field strength in term of Earth's
	float magneticFieldStrength;
	float worldMass;
	char volcanicActivityLevel;
	char tectonicActivityLevel;
	float atmosphericPressure;
	atmosphericComposition_t worldAtmosphereComposition;
	float minimumMolecularWeightRetained;
	int resourceValueModifier;
	int habitabilityModifier;
	char climateType;
	bool breathable;
	float tidalForceOnSatelliteByPlanet;
	float totalTidalEffect;
	char atmosphericPressureCategory;
//	Moon's escape velocity
	float escapeVelocity;
	float equatorialRotationVelocity;
//	Average surface area (not every world will be mapped)
	float totalSurfaceArea;
//	Land surface area
	float landSurfaceArea;
//	Liquid surface area
	float liquidSurfaceArea;

//	Mapping information
	char hexesPerSide;
	int totalHexes;
	int waterHexCount;
	int landHexCount;
	char numberOfMajorOceans;
	char numberOfMinorOceans;
	char numberOfSmallSeas;
	char numberOfScatteredLakes;
	char numberOfMajorContinents;
	char numberOfMinorContinents;
	char numberOfMajorIslands;
	char numberOfArchipelagoes;
//	Tectonic plates
	int tectonicPlateCount;
	tectonicPlate_t tectonicPlateArray[16];

//	Identification
//	Unique identifier for the moon
	std::string moonName;
	int uniqueMoonID;
	int parentWorldID;
	int primaryStarID;
	int starSystemID;

//	Life
	char nativeEcosphere;

};

#endif
