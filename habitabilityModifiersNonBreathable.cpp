#include <cstdint>
//	Constant declarations
#include "declarations/constants/atmosphericPressureCategoryConstants.h"

//	Struct declarations
#include "declarations/structures/atmosphericComposition_t.h"

using namespace std;

int8_t habitabilityModifiersNonBreathable(char pressureCategory, atmosphericComposition_t atmosphereComposition)
{
	int8_t habitabilityModifier = 0;

	if 		((pressureCategory == APC_VERY_THIN || pressureCategory == APC_TRACE) && (atmosphereComposition.toxicity > 0) && (atmosphereComposition.suffocating == 1) && (atmosphereComposition.corrosive == 1)) 	{habitabilityModifier = -2;}
	else if ((pressureCategory == APC_VERY_THIN || pressureCategory == APC_TRACE) && (atmosphereComposition.toxicity > 0) && (atmosphereComposition.suffocating == 1))											{habitabilityModifier = -1;}
	else																																																{habitabilityModifier =	 0;}

	return habitabilityModifier;
}
