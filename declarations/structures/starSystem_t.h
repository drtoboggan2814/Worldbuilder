#ifndef STARSYSTEM_T
#define STARSYSTEM_T

//	c++ libraries
#include <cstdint>

#include "star_t.h"

struct starSystem_t
{
	char numberOfStars;
	star_t stars[3];
	float systemAge;
	bool gardenWorldPresent;

//	Cartesian components
	float cartesianX;
	float cartesianY;
	float cartesianZ;
	float cartesianVelocityX;
	float cartesianVelocityY;
	float cartesianVelocityZ;

//	Identification
	int uniqueStarSystemID;
};

#endif
