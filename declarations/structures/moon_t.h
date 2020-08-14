#ifndef MOON_T
#define MOON_T

#include "atmosphericComposition_t.h"

#include <string>
using namespace std;

//	This structure describes a moon orbiting a larger world

struct moon_t
{
//	Corresponds to the "Moon Size Table" on page 112
//	-3 corresponds to "Three size classes smaller"
//	-2 corresponds to "Two size classes smaller"
//	-1 corresponds to "One size class smaller"
	int moonSizeClass;
	string sizeClass;
	string worldType;
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
	float axialTilt;
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
	float worldMass;
	string volcanicActivityLevel;
	string tectonicActivityLevel;
	float atmosphericPressure;
	atmosphericComposition_t worldAtmosphereComposition;
	float minimumMolecularWeightRetained;
	int resourceValueModifier;
	int habitabilityModifier;
	float tidalForceOnSatelliteByPlanet;
	float totalTidalEffect;
	string atmosphericPressureCategory;
//	Moon's escape velocity
	float escapeVelocity;
};

#endif
