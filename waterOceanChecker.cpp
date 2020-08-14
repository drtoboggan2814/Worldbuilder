#include <string>

using namespace std;

bool waterOceanChecker(string worldType, float hydrographicCoverage)
{
	bool liquidWater;
	
	if 		(worldType == "Standard (Ice)" 	 || worldType == "Large (Ice)"		) {liquidWater = true ;}
	else if (worldType == "Standard (Ocean)" || worldType == "Standard (Garden)") {liquidWater = true ;}
	else if (worldType == "Large (Ocean)" 	 || worldType == "Large (Garden)"	) {liquidWater = true ;}
	else																		  {liquidWater = false;}
	
	return liquidWater;
}