//	This function returns the ratio between orbits
float orbitalSpacingTable();

//	Get the orbital radius of the first world
float getOrbitalRadius(float outermostLegalDistance);

//	This function returns the orbital
star_t placePlanetaryOrbits(star_t primary, int numberOfStars, float companionAInnerForbiddenZone, float companionAOuterForbiddenZone, float companionBInnerForbiddenZone, float companionBOuterForbiddenZone, float companionAOrbitalRadius, float companionBOrbitalRadius);
