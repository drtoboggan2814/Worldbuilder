#include <string>

using namespace std;

string worldClimateTable(int surfaceTemperature)
{
	string worldClimateType;
	if 		(surfaceTemperature <  244) 							{worldClimateType = "Frozen";}
	else if (surfaceTemperature >= 244 && surfaceTemperature < 255) {worldClimateType = "Very Cold";}
	else if (surfaceTemperature >= 255 && surfaceTemperature < 266) {worldClimateType = "Cold";}
	else if (surfaceTemperature >= 266 && surfaceTemperature < 278) {worldClimateType = "Chilly";}
	else if (surfaceTemperature >= 278 && surfaceTemperature < 289) {worldClimateType = "Cool";}
	else if (surfaceTemperature >= 289 && surfaceTemperature < 300) {worldClimateType = "Normal";}
	else if (surfaceTemperature >= 300 && surfaceTemperature < 311) {worldClimateType = "Warm";}
	else if (surfaceTemperature >= 311 && surfaceTemperature < 322) {worldClimateType = "Tropical";}
	else if (surfaceTemperature >= 322 && surfaceTemperature < 333) {worldClimateType = "Hot";}
	else if (surfaceTemperature >= 333 && surfaceTemperature < 344) {worldClimateType = "Very Hot";}
	else if (surfaceTemperature >  344) 							{worldClimateType = "Infernal";}
	
	return worldClimateType;
}