#include "../structures/starSystem_t.h"
#include "../structures/star_t.h"
float getRadiusMultiplier(const int& diceRoll);

float getEccentricity(const int& diceRoll);

star_t orbitalSeparationTable(const char& numberOfStars, const int& companionStar, star_t& primary, const bool& gardenWorldPresent);

starSystem_t companionStarOrbits(starSystem_t& starSystem);
