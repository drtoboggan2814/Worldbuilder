#ifndef STAR_T
#define STAR_T

//	C++ Libraries
//	#include <string>

//	Structure declarations
#include "world_t.h"

//using namespace std;

struct star_t
{
//	Luminosity class
//	V = main sequence
//	IV = subgiant
//	III = giant
//	D = white dwarf
	char luminosityClass;

//	Which star in the system is this?
	int starNumber;

	float stellarMass;
	float stellarAge;
	float stellarLuminosity;
	float stellarTemperature;
	float stellarRadius;

//	For stellarEvolutionTableConstants
	int starType;
	float tableTemperature;
	float lMin;
	float lMax;
	float mSpan;
	float sSpan;
	float gSpan;

//	For locateOrbitalZones
	float innerLimitRadius;
	float outerLimitRadius;
	float snowLineRadius;
//	Only applies to multiple-star systems
	float averageOrbitalRadius;
	float orbitalEccentricity;
	float minSeparationToCompanion;
	float maxSeparationToCompanion;
	float innerForbiddenZone;
	float outerForbiddenZone;

//	For the actual planetary system
//	The number of orbital slots around the star
	int numberOfOrbits;
//	Stores the size class of each world
	char sizeClassArray[32];
//	Stores the orbital radius around the primary of each world
	float orbitalRadiusArray[32];
//	The index value of the orbital slot closest to the primary
	int firstWorldIndex;
//	Record the object in each of the world's orbital slots
	world_t worldArray[32];

/*
//	This array holds the orbits of each planet in the system
	planetaryOrbitsArray_t planetaryOrbits;
	worldArray_t worldArray;
*/
//	Star's escape velocity
	double escapeVelocity;

	char gasGiantArrangement;
	bool firstGasGiantPresent;
	float firstGasGiantOrbitalRadius;

//	If the star is a companion
	float stellarOrbitalPeriod;

};

#endif
