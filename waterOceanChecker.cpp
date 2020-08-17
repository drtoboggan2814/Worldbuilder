//	C++ libraries
#include <string>

//	Constant declarations
#include "declarations/constants/worldTypeConstants.h"

using namespace std;

bool waterOceanChecker(char worldType, float hydrographicCoverage)
{
	bool liquidWater;

	if 		(worldType == WT_STANDARD_ICE 	 || worldType == WT_LARGE_ICE		) {liquidWater = true ;}
	else if (worldType == WT_STANDARD_OCEAN || worldType == WT_STANDARD_GARDEN) {liquidWater = true ;}
	else if (worldType == WT_LARGE_OCEAN 	 || worldType == WT_LARGE_GARDEN	) {liquidWater = true ;}
	else																		  {liquidWater = false;}

	return liquidWater;
}
