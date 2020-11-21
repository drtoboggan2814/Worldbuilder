//	Constant declarations
#include "declarations/constants/climateTypeConstants.h"

char worldClimateTable(int surfaceTemperature)
{
	char worldClimateType;
	if 		(surfaceTemperature <  244) 							{worldClimateType = CT_FROZEN;}
	else if (surfaceTemperature >= 244 && surfaceTemperature < 255) {worldClimateType = CT_VERY_COLD;}
	else if (surfaceTemperature >= 255 && surfaceTemperature < 266) {worldClimateType = CT_COLD;}
	else if (surfaceTemperature >= 266 && surfaceTemperature < 278) {worldClimateType = CT_CHILLY;}
	else if (surfaceTemperature >= 278 && surfaceTemperature < 289) {worldClimateType = CT_COOL;}
	else if (surfaceTemperature >= 289 && surfaceTemperature < 300) {worldClimateType = CT_NORMAL;}
	else if (surfaceTemperature >= 300 && surfaceTemperature < 311) {worldClimateType = CT_WARM;}
	else if (surfaceTemperature >= 311 && surfaceTemperature < 322) {worldClimateType = CT_TROPICAL;}
	else if (surfaceTemperature >= 322 && surfaceTemperature < 333) {worldClimateType = CT_HOT;}
	else if (surfaceTemperature >= 333 && surfaceTemperature < 344) {worldClimateType = CT_VERY_HOT;}
	else if (surfaceTemperature >  344) 							{worldClimateType = CT_INFERNAL;}

	return worldClimateType;
}
