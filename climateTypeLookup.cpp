#include <string>

using namespace std;

string climateTypeLookup(int surfaceTemperature)
{
	string climateType;
	
	if 		(surfaceTemperature <  244							   ) {climateType = "Frozen"	;}
	else if (surfaceTemperature >= 244 && surfaceTemperature <= 255) {climateType = "Very Cold"	;}
	else if (surfaceTemperature >= 255 && surfaceTemperature <= 266) {climateType = "Cold"		;}
	else if (surfaceTemperature >= 266 && surfaceTemperature <= 278) {climateType = "Chilly"	;}
	else if (surfaceTemperature >= 278 && surfaceTemperature <= 289) {climateType = "Cool"		;}
	else if (surfaceTemperature >= 289 && surfaceTemperature <= 300) {climateType = "Normal"	;}
	else if (surfaceTemperature >= 300 && surfaceTemperature <= 311) {climateType = "Warm"		;}
	else if (surfaceTemperature >= 311 && surfaceTemperature <= 322) {climateType = "Tropical"	;}
	else if (surfaceTemperature >= 322 && surfaceTemperature <= 333) {climateType = "Hot"		;}
	else if (surfaceTemperature >= 333 && surfaceTemperature <= 344) {climateType = "Very Hot"	;}
	else if (surfaceTemperature >  344							   ) {climateType = "Infernal"	;}
	
	return climateType;
}