//	C++ libraries
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <math.h>
#include <random>
#include <string>
#include <time.h>

//	Constant declarations
#include "constants/absorptionFactorConstants.h"
#include "constants/atmosphericPressureCategoryConstants.h"
#include "constants/gasGiantArrangementConstants.h"
#include "constants/greenhouseFactorConstants.h"
#include "constants/luminosityClassConstants.h"
#include "constants/mappingConstants.h"
#include "constants/miscConstants.h"
#include "constants/sizeClassConstants.h"
#include "constants/stringConstants.h"
#include "constants/tectonicActivityLevelConstants.h"
#include "constants/unitConversions.h"
#include "constants/universalConstants.h"
#include "constants/volcanicActivityLevelConstants.h"
#include "constants/worldTypeConstants.h"

//	Structure declarations
#include "structures/atmosphericComposition_t.h"
#include "structures/marginalAtmosphere_t.h"
#include "structures/moon_t.h"
#include "structures/moonlet_t.h"
#include "structures/orbitalSeparation_t.h"
#include "structures/world_t.h"
#include "structures/star_t.h"
#include "structures/starSystem_t.h"

//	Third party
#include "third_party/rapidcsv.h"

//	Function declarations
//	Utility
#include "functions/diceRoller.h"
#include "functions/floatRNG.h"

//	World and moon design
#include "functions/absorptionFactorLookup.h"
#include "functions/atmosphereComposition.h"
#include "functions/atmosphereMassGenerator.h"
#include "functions/atmosphericPressureCalculator.h"
#include "functions/atmosphericPressureCategoriesTable.h"
#include "functions/blackbodyCorrectionCalculator.h"
#include "functions/blackbodyTemperatureCalculator.h"
#include "functions/companionStarOrbits.h"
#include "functions/generateWorldDetails.h"
#include "functions/greenhouseFactorLookup.h"
#include "functions/habitabilityModifiersTable.h"
#include "functions/hydrographicCoverageCalculator.h"
#include "functions/locateOrbitalZones.h"
#include "functions/mappingFunctions.h"
#include "functions/minimumMolecularWeightRetainedCalculator.h"
#include "functions/overallTypeTable.h"
#include "functions/placeMoons.h"
#include "functions/placeMoonOrbits.h"
#include "functions/placePlanetaryOrbits.h"
#include "functions/placeWorlds.h"
#include "functions/placingFirstPlanets.h"
#include "functions/printStarSystem.h"
#include "functions/printWorld.h"
#include "functions/resourceDeterminator.h"
#include "functions/specialCases.h"
#include "functions/surfaceGravityCalculator.h"
#include "functions/surfaceTemperatureTable.h"
#include "functions/worldDensityTable.h"
#include "functions/worldDiameterCalculator.h"
#include "functions/worldMassCalculator.h"
#include "functions/worldTypeTable.h"

//	Star design
#include "functions/stellarMassTable.h"
#include "functions/stellarAgeTable.h"
#include "functions/determineStellarCharacteristics.h"
#include "functions/calculateStellarTemperature.h"
#include "functions/calculateStellarLuminosity.h"
#include "functions/determineStarRadius.h"
#include "functions/getStarIDFromCSV.h"
#include "functions/solarPowerFunctions.h"
#include "functions/starClassifier.h"

//	Star system design
#include "functions/determineStarNumber.h"
