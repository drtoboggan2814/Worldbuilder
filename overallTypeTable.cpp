//	This function determines the world's overall type and returns it as a string
#include <string>

using namespace std;

string overallTypeTable(int rng)
{
	string overallType;

	if 		(rng <= 7			 ) {overallType = "Hostile";}
	else if (7 < rng && rng < 14 ) {overallType = "Barren" ;}
	else if (13 < rng && rng < 19) {overallType = "Garden" ;}

	return overallType;
}
