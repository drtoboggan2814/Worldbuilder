#ifndef STARSYSTEM_T
#define STARSYSTEM_T

//	c++ libraries
#include <cstdint>

#include "star_t.h"

struct starSystem_t
{
	uint8_t numberOfStars;
	star_t stars[3];
	float systemAge;
	bool gardenWorldPresent;
};

#endif
