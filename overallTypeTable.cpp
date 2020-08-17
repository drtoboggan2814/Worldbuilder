//	This function determines the world's overall type and returns it as a string
//	Constant declarations
#include "declarations/constants/worldTypeConstants.h"

//	#include <string>
//	using namespace std;

char overallTypeTable(int rng)
{
	char overallType;

	if 		(rng <= 7			 ) {overallType = OT_HOSTILE;}
	else if (7 < rng && rng < 14 ) {overallType = OT_BARREN ;}
	else if (13 < rng && rng < 19) {overallType = OT_GARDEN ;}

	return overallType;
}
