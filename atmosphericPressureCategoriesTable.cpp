//	Constant declarations
#include "declarations/constants/atmosphericPressureCategoryConstants.h"

//	Function declarations
#include "declarations/functions/floatRNG.h"

float getNewAtmosphericPressure(char pressureCategory)
{
	float newAtmosphericPressure;
	if (pressureCategory == APC_NONE)			{newAtmosphericPressure = 0;}
	else if (pressureCategory == APC_TRACE)		{newAtmosphericPressure = floatRNG(0.000001, 0.00999);}
	else if (pressureCategory == APC_VERY_THIN)	{newAtmosphericPressure = floatRNG(0.01, 0.5);}

	return newAtmosphericPressure;
}

char atmosphericPressureCategoriesTable(float atmosphericPressure)
{
	char pressureCategory;
	if 		(atmosphericPressure == 0								  ) {pressureCategory = APC_NONE;}
	else if	(atmosphericPressure < 	0.01 && atmosphericPressure > 0	  ) {pressureCategory = APC_TRACE;}
	else if (atmosphericPressure >= 0.01 && atmosphericPressure <= 0.5) {pressureCategory = APC_VERY_THIN;}
	else if (atmosphericPressure >= 0.51 && atmosphericPressure <= 0.8) {pressureCategory = APC_THIN;}
	else if (atmosphericPressure >= 0.81 && atmosphericPressure <= 1.2) {pressureCategory = APC_STANDARD;}
	else if (atmosphericPressure >= 1.21 && atmosphericPressure <= 1.5) {pressureCategory = APC_DENSE;}
	else if (atmosphericPressure >= 1.51 && atmosphericPressure <= 10 )	{pressureCategory = APC_VERY_DENSE;}
	else if (atmosphericPressure >	10								  ) {pressureCategory = APC_SUPERDENSE;}

	return pressureCategory;
}
