//	This function corresponds to "Determining Habitability and Affinity" in "Step 7: Resources and Habitability".

#include <cstdint>
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

int8_t habitabilityModifiersTable(char worldType, float atmosphereMass, float hydrographicCoverage, float atmosphericPressure, int surfaceTemperature, atmosphericComposition_t atmosphereCompositionArray)
{
	//bool liquidWater = waterOceanChecker(worldType, hydrographicCoverage);
	char climateType = climateTypeLookup(surfaceTemperature);
	bool breathable = breathableChecker(atmosphereCompositionArray);
	char pressureCategory = atmosphericPressureCategoriesTable(atmosphericPressure);

	int8_t habitabilityModifier = 0;
	int8_t breathableClimate = habitabilityModifiersBreathableClimate(climateType, breathable);
	int8_t breathableAtmosphere = habitabilityModifiersBreathable(pressureCategory, breathable);
	int8_t nonBreathableAtmosphere = habitabilityModifiersNonBreathable(pressureCategory, atmosphereCompositionArray);
	int8_t liquidWaterOceans = habitabilityModfiersLiquidWaterOceans(hydrographicCoverage);

	habitabilityModifier = breathableClimate + breathableAtmosphere + nonBreathableAtmosphere + liquidWaterOceans;

	return habitabilityModifier;

}
