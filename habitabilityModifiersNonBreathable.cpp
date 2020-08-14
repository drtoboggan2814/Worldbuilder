#include <string>

#include "declarations/structures/atmosphericComposition_t.h"

using namespace std;

int habitabilityModifiersNonBreathable(string pressureCategory, atmosphericComposition_t atmosphereComposition)
{
	int habitabilityModifier = 0;

	if 		((pressureCategory == "Very Thin" || pressureCategory == "Trace") && (atmosphereComposition.toxicity > 0) && (atmosphereComposition.suffocating == 1) && (atmosphereComposition.corrosive == 1)) 	{habitabilityModifier = -2;}
	else if ((pressureCategory == "Very Thin" || pressureCategory == "Trace") && (atmosphereComposition.toxicity > 0) && (atmosphereComposition.suffocating == 1))											{habitabilityModifier = -1;}
	else																																																{habitabilityModifier =	 0;}

	return habitabilityModifier;
}
