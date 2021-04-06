#include <cstdint>
int habitabilityModfiersLiquidWaterOceans(float hydrographicCoverage)
{
	int habitabilityModifier = 0;

	if 		(hydrographicCoverage >= 0.01 && hydrographicCoverage <= 0.59) {habitabilityModifier = 1;}
	else if (hydrographicCoverage >= 0.6  && hydrographicCoverage <= 0.9 ) {habitabilityModifier = 2;}
	else if (hydrographicCoverage >= 0.91 && hydrographicCoverage <= 0.99) {habitabilityModifier = 1;}
	else 	 								   							   {habitabilityModifier = 0;}

	return habitabilityModifier;
}
