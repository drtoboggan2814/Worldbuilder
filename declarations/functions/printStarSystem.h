#include "../structures/atmosphericComposition_t.h"
#include "../structures/moon_t.h"
#include "../structures/star_t.h"
#include "../structures/starSystem_t.h"
#include "../structures/world_t.h"

void printAtmosphereComposition(const atmosphericComposition_t& atmosphereComposition);

void printMoon(const moon_t& moon);

void printWorld(world_t world, char sizeClass);

//	Print the characteristics of a star
void printStar(star_t star);

//	Print the characteristics of a star system
void printStarSystem(const starSystem_t& starSystem);
