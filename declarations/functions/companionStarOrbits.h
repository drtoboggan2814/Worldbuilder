#include "../structures/starSystem_t.h"
#include "../structures/star_t.h"
float getRadiusMultiplier(int diceRoll);

float getEccentricity(int diceRoll);

star_t orbitalSeparationTable(const char& numberOfStars, int companionStar, star_t& primary, const bool& gardenWorldPresent);

starSystem_t companionStarOrbits(starSystem_t& starSystem);
