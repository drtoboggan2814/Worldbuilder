#include "../structures/star_t.h"
//	This functions returns a string representing the size of the gas giant
char getGasGiantSize(const int& diceRoll);

//	This function returns a string representing the non-gas giant contents of the orbit
char orbitContentsTable(const int& orbitContentsRoll);

//	This function checks which modifiers should be applied to orbitContentsRoll
//	currentIndex is the current index of the for loop iterating through the orbits
char csv_determineWorldSizeClass(star_t& primary, rapidcsv::Document& worldDoc, const int& currentIndex);
int getOrbitContentsRollModifier(star_t& primary, const int& currentIndex);

star_t fillOrbits(star_t& primary, rapidcsv::Document& worldDoc, const bool& randomSystem);
