/*
	This file defines tectonicPlate_t, a structure that describes a tectonic
	plate on a terrestrial world.
*/

#ifndef TECTONICPLATE_T
#define TECTONICPLATE_T

//	C++ libraries
#include <cstdint>

struct tectonicPlate_t
{
	int tectonicPlateSize;
	char tectonicPlateMovementType;

//	This applies to both moons and worlds
	int parentMoonID;
	int parentWorldID;
	int primaryStarID;
	int starSystemID;
};

#endif
