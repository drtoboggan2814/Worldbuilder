#ifndef JUMPPOINTFUNCTIONS
#define JUMPPOINTFUNCTIONS

//	Structure declarations
#include "../structures/star_t.h"

int getNumberOfJumpPoints();
float jumpPointOrbitalSpacingTable();
star_t assignJumpPointDetails(star_t& primary, int i, int jumpPointArrayIndex, bool belowSnowLine);
star_t placeJumpPointOrbits(star_t& primary);

#endif
