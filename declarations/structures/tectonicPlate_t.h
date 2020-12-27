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
	uint8_t tectonicPlateSize;
	uint8_t tectonicPlateMovementType;
};

#endif
