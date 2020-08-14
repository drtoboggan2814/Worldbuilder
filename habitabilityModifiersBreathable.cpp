#include <string>

using namespace std;

int habitabilityModifiersBreathable(string pressureCategory, bool breathable)
{
	int habitabilityModifier;

	if 		(breathable == false																			) {habitabilityModifier = 0;}
	else if (breathable == true && pressureCategory == "Very Thin"											) {habitabilityModifier = 1;}
	else if (breathable == true && pressureCategory == "Thin"												) {habitabilityModifier = 2;}
	else if (breathable == true && pressureCategory == "Standard" 		|| pressureCategory == "Dense"		) {habitabilityModifier = 3;}
	else if (breathable == true && pressureCategory == "Very Dense" 	|| pressureCategory == "Superdense"	) {habitabilityModifier = 1;}
	else																									  {habitabilityModifier = 0;}
	return habitabilityModifier;
}
