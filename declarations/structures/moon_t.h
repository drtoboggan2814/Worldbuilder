#ifndef MOON_T
#define MOON_T

#include <cstdint>
#include "atmosphericComposition_t.h"
#include "tectonicPlate_t.h"


//	This structure describes a moon orbiting a larger world

struct moon_t
{
//	Corresponds to the "Moon Size Table" on page 112
//	-3 corresponds to "Three size classes smaller"
//	-2 corresponds to "Two size classes smaller"
//	-1 corresponds to "One size class smaller"
	int8_t moonSizeClass;
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
	int8_t axialTilt;
	bool resonantOrNot;
	float atmosphericMass;
	bool tidalLockedOrNot;
	float atmosphereMass;
	float hydrographicCoverage;
	float surfaceTemperature;
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
	int8_t resourceValueModifier;
	int8_t habitabilityModifier;
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
	uint8_t hexesPerSide;
	uint16_t totalHexes;
	uint16_t waterHexCount;
	uint16_t landHexCount;
	uint8_t numberOfMajorOceans;
	uint8_t numberOfMinorOceans;
	uint8_t numberOfSmallSeas;
	uint8_t numberOfScatteredLakes;
	uint8_t numberOfMajorContinents;
	uint8_t numberOfMinorContinents;
	uint8_t numberOfMajorIslands;
	uint8_t numberOfArchipelagoes;
//	Tectonic plates
	uint8_t tectonicPlateCount;
	tectonicPlate_t tectonicPlateArray[16];

};

#endif
