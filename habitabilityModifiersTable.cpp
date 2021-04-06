//	This function corresponds to "Determining Habitability and Affinity" in "Step 7: Resources and Habitability".

#include <cstdint>
#include <iostream>
#include <tuple>
//	Constant declarations
#include "declarations/constants/atmosphericPressureCategoryConstants.h"
#include "declarations/constants/worldTypeConstants.h"

//	Struct declarations
#include "declarations/structures/atmosphericComposition_t.h"

//	Function declarations
#include "declarations/functions/habitabilityModifiersLiquidWaterOceans.h"
#include "declarations/functions/habitabilityModifiersBreathable.h"
#include "declarations/functions/habitabilityModifiersBreathableClimate.h"
#include "declarations/functions/habitabilityModifiersNonBreathable.h"
#include "declarations/functions/waterOceanChecker.h"
#include "declarations/functions/climateTypeLookup.h"
#include "declarations/functions/breathableChecker.h"
#include "declarations/functions/atmosphericPressureCategoriesTable.h"

std::tuple<int, char, bool> habitabilityModifiersTable(char worldType, float atmosphereMass, float hydrographicCoverage, float atmosphericPressure, int surfaceTemperature, atmosphericComposition_t atmosphereCompositionArray)
{
	std::cout << "Entered habitabilityModifiersTable" << std::endl;
	//bool liquidWater = waterOceanChecker(worldType, hydrographicCoverage);
	char climateType = climateTypeLookup(surfaceTemperature);
	std::cout << "climateType == " << int(climateType) << std::endl;
	bool breathable = breathableChecker(atmosphereCompositionArray);
	std::cout << "breathable == " << breathable << std::endl;
	char pressureCategory = atmosphericPressureCategoriesTable(atmosphericPressure);
	std::cout << "pressureCategory == " << int(pressureCategory) << std::endl;

	int habitabilityModifier = 0;
	int breathableClimate = habitabilityModifiersBreathableClimate(climateType, breathable);
	std::cout << "breathableClimate == " << breathableClimate << std::endl;
	int breathableAtmosphere = breathable ? habitabilityModifiersBreathable(pressureCategory, breathable) : 0;
	std::cout << "breathableAtmosphere == " << breathableAtmosphere << std::endl;
	int nonBreathableAtmosphere = breathable ? 0 : habitabilityModifiersNonBreathable(pressureCategory, atmosphereCompositionArray);
	std::cout << "nonBreathableAtmosphere == " << nonBreathableAtmosphere << std::endl;
	int liquidWaterOceans = habitabilityModfiersLiquidWaterOceans(hydrographicCoverage);
	std::cout << "liquidWaterOceans == " << liquidWaterOceans << std::endl;

	habitabilityModifier = breathableClimate + breathableAtmosphere + nonBreathableAtmosphere + liquidWaterOceans;
	std::cout << "habitabilityModifier == " << habitabilityModifier << std::endl;

	return std::make_tuple(habitabilityModifier, climateType, (breathable && atmosphereMass != 0));

}
