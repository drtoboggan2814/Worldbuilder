//	This structure defines the parameters used for the function worldBuilder
#ifndef WORLDBUILDERPARAMETERS_T
#define WORLDBUILDERPARAMETERS_T

//	Structure declarations
#include "../star_t.h"

struct worldBuilderParameters_t
{
	//	Preset bools
	//	Orbital parameters
	bool eccentricityPresent;
	bool inclinationPresent;
	bool orbitalPeriodPresent;
	bool semiMajorAxisPresent;

	//	Physical parameters
	bool densityPresent;
	bool fluxPresent;
	bool massPreset;
	bool radiusPreset;
	bool temperaturePreset;

	//	Type parameters
	bool sizeClassPresent;
	bool worldTypePresent;

	//	Original parameters
	char sizeClass;
	float averageOrbitalRadius;
	star_t primary;
};

#endif
