#ifndef STARSYSTEM_T
#define STARSYSTEM_T

#include "star_t.h"

struct starSystem_t
{
	char numberOfStars;
	star_t stars[3];
	float systemAge;
	bool gardenWorldPresent;
};

#endif
