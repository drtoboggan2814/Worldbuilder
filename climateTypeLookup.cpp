//	Constant declarations
#include "declarations/constants/climateTypeConstants.h"

char climateTypeLookup(int surfaceTemperature)
{
	char climateType;

	if 		(surfaceTemperature <  244							   ) {climateType = CT_FROZEN	;}
	else if (surfaceTemperature >= 244 && surfaceTemperature <= 255) {climateType = CT_VERY_COLD	;}
	else if (surfaceTemperature >= 255 && surfaceTemperature <= 266) {climateType = CT_COLD		;}
	else if (surfaceTemperature >= 266 && surfaceTemperature <= 278) {climateType = CT_CHILLY	;}
	else if (surfaceTemperature >= 278 && surfaceTemperature <= 289) {climateType = CT_COOL		;}
	else if (surfaceTemperature >= 289 && surfaceTemperature <= 300) {climateType = CT_NORMAL	;}
	else if (surfaceTemperature >= 300 && surfaceTemperature <= 311) {climateType = CT_WARM		;}
	else if (surfaceTemperature >= 311 && surfaceTemperature <= 322) {climateType = CT_TROPICAL	;}
	else if (surfaceTemperature >= 322 && surfaceTemperature <= 333) {climateType = CT_HOT		;}
	else if (surfaceTemperature >= 333 && surfaceTemperature <= 344) {climateType = CT_VERY_HOT	;}
	else if (surfaceTemperature >  344							   ) {climateType = CT_INFERNAL	;}

	return climateType;
}
