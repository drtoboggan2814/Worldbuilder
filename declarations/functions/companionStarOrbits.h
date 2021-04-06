#ifndef COMPANIONSTARORBITS
#define COMPANIONSTARORBITS

#include "../structures/starSystem_t.h"
#include "../structures/star_t.h"
float getRadiusMultiplier(int diceRoll);

float getEccentricity(int diceRoll);

star_t orbitalSeparationTable(char numberOfStars, int companionStar, star_t& primary, bool gardenWorldPresent);

starSystem_t companionStarOrbits(starSystem_t& starSystem);

#endif
