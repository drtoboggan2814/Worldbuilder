#include <string>

using namespace std;

int habitabilityModifiersBreathableClimate(string climateType, bool breathable)
{
	int habitabilityModifier;

	if (breathable == true)
	{
		if 		(climateType == "Cold"																											  ) {habitabilityModifier = 1;}
		else if (climateType == "Chilly" || climateType == "Cool" || climateType == "Normal" || climateType == "Warm" || climateType == "Tropical") {habitabilityModifier = 2;}
		else if (climateType == "Hot"																											  )	{habitabilityModifier = 1;}
		else																																		{habitabilityModifier = 0;}
	}

	else {habitabilityModifier = 0;}

	return habitabilityModifier;
}
