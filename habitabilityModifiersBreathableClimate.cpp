//	Constant declarations
#include "declarations/constants/climateTypeConstants.h"

int habitabilityModifiersBreathableClimate(char climateType, bool breathable)
{
	int habitabilityModifier;

	if (breathable == true)
	{
		if 		(climateType == CT_COLD																											  ) {habitabilityModifier = 1;}
		else if (climateType == CT_CHILLY || climateType == CT_COOL || climateType == CT_NORMAL || climateType == CT_WARM || climateType == CT_TROPICAL) {habitabilityModifier = 2;}
		else if (climateType == CT_HOT																											  )	{habitabilityModifier = 1;}
		else																																		{habitabilityModifier = 0;}
	}

	else {habitabilityModifier = 0;}

	return habitabilityModifier;
}
