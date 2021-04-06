/*
	This file defines tectonicPlate_t, a structure that describes a tectonic
	plate on a terrestrial world.
*/

#ifndef TECTONICPLATE_MOON_T
#define TECTONICPLATE_MOON_T

//	C++ libraries
#include <cstdint>

struct tectonicPlate_moon_t
{
	int tectonicPlateSize;
	char tectonicPlateMovementType;

	int uniqueMoonletID;
	int parentWorldID;
	int primaryStarID;
	int starSystemID;
};

#endif
