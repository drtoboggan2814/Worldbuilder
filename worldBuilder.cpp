//	This holds the main function of the GURPS Space 4e worldbuilding process
//	This follows the steps outlined in the book

//	Boost libraries
//	#include <boost/python.hpp>

//	C++ libraries
#include <iostream>

//	#include <string>
#include <cstdint>
#include <cstdlib>
#include <time.h>
#include <limits>
#include <math.h>
#include <random>

//	Constant declarations
#include "declarations/constants/gasGiantArrangementConstants.h"
#include "declarations/constants/luminosityClassConstants.h"
#include "declarations/constants/mappingConstants.h"
#include "declarations/constants/miscConstants.h"
#include "declarations/constants/sizeClassConstants.h"
#include "declarations/constants/stringConstants.h"
#include "declarations/constants/unitConversions.h"
#include "declarations/constants/universalConstants.h"
#include "declarations/constants/worldTypeConstants.h"

//	Structure declarations
#include "declarations/structures/atmosphericComposition_t.h"
#include "declarations/structures/marginalAtmosphere_t.h"
#include "declarations/structures/moon_t.h"
#include "declarations/structures/moonlet_t.h"
#include "declarations/structures/orbitalSeparation_t.h"
#include "declarations/structures/world_t.h"
#include "declarations/structures/star_t.h"
#include "declarations/structures/starSystem_t.h"

//	Third party
#include "declarations/third_party/rapidcsv.h"

//	Function declarations
//	Utility
#include "declarations/functions/diceRoller.h"
#include "declarations/functions/floatRNG.h"

//	World and moon design
#include "declarations/functions/absorptionFactorLookup.h"
#include "declarations/functions/atmosphereComposition.h"
#include "declarations/functions/atmosphereMassGenerator.h"
#include "declarations/functions/atmosphericPressureCalculator.h"
#include "declarations/functions/atmosphericPressureCategoriesTable.h"
#include "declarations/functions/blackbodyCorrectionCalculator.h"
#include "declarations/functions/blackbodyTemperatureCalculator.h"
#include "declarations/functions/companionStarOrbits.h"
#include "declarations/functions/generateWorldDetails.h"
#include "declarations/functions/greenhouseFactorLookup.h"
#include "declarations/functions/habitabilityModifiersTable.h"
#include "declarations/functions/hydrographicCoverageCalculator.h"
#include "declarations/functions/locateOrbitalZones.h"
#include "declarations/functions/mappingFunctions.h"
#include "declarations/functions/minimumMolecularWeightRetainedCalculator.h"
#include "declarations/functions/overallTypeTable.h"
#include "declarations/functions/placeMoons.h"
#include "declarations/functions/placeMoonOrbits.h"
#include "declarations/functions/placePlanetaryOrbits.h"
#include "declarations/functions/placeWorlds.h"
#include "declarations/functions/placingFirstPlanets.h"
#include "declarations/functions/printStarSystem.h"
#include "declarations/functions/printWorld.h"
#include "declarations/functions/resourceDeterminator.h"
#include "declarations/functions/specialCases.h"
#include "declarations/functions/surfaceGravityCalculator.h"
#include "declarations/functions/surfaceTemperatureTable.h"
#include "declarations/functions/worldDensityTable.h"
#include "declarations/functions/worldDiameterCalculator.h"
#include "declarations/functions/worldMassCalculator.h"
#include "declarations/functions/worldTypeTable.h"

//	Star design
#include "declarations/functions/stellarMassTable.h"
#include "declarations/functions/stellarAgeTable.h"
#include "declarations/functions/determineStellarCharacteristics.h"
#include "declarations/functions/calculateStellarTemperature.h"
#include "declarations/functions/calculateStellarLuminosity.h"
#include "declarations/functions/determineStarRadius.h"
#include "declarations/functions/getStarIDFromCSV.h"
#include "declarations/functions/solarPowerFunctions.h"
#include "declarations/functions/starClassifier.h"

//	Star system design
#include "declarations/functions/determineStarNumber.h"


//	#include "declarations/functions/runPython.h"

//	using namespace std;

/*
//	RNG stuff
typedef std::mt19937 MyRNG;
uint32_t seed_val;
MyRNG rng;
*/

/*
//	Basic World Design Sequence
world_t worldBuilder()
{
//	Initialize the world
	world_t world;

//	Step 2: World Type
//	Get overall type
	world.overallType = overallTypeTable(diceRoller(6, 3));
//	Get world type
	world.worldType = worldTypeTable(diceRoller(6, 3), world.overallType);

//	Step 3: Atmosphere
//	Calculate the world's atmospheric mass (as a proportion of Earth's atmospheric mass)
	world.atmosphereMass = atmosphereMassGenerator(world.worldType);
//	Determine the atmosphere's composition
	world.worldAtmosphereComposition = atmosphereComposition(world.worldType);

//	Step 4: Hydrographic Coverage
//	Determine the world's Hydrographic coverage
	world.hydrographicCoverage = hydrographicCoverageCalculator(world.worldType);

//	Step 5: Climate
//	Determine the world's surface temperature (K)
	world.surfaceTemperature = surfaceTemperatureTable(world.worldType);
//	Determine the world's greenhouse factor
	world.greenhouseFactor = greenhouseFactorLookup(world.worldType, world.hydrographicCoverage);
//	Determine the world's absorption factor
	world.absorptionFactor = absorptionFactorLookup(world.worldType, world.hydrographicCoverage);
//	Determine the world's blackbody correction
	world.blackbodyCorrection = blackbodyCorrectionCalculator(world.absorptionFactor, world.greenhouseFactor, world.atmosphereMass);
//	Determine the world's blackbody temperature (K)
	world.blackbodyTemperature = blackbodyTemperatureCalculator(world.blackbodyCorrection, world.surfaceTemperature);

//	Step 6: World Size
//	NOTE: This step does not apply to the worldType WT_ASTEROID_BELT, and will
//	return zero for all functions in this section
//	Determine the world's density (as a proportion of Earth's density)
	world.worldDensity = worldDensityTable(world.worldType);
//	Determine the world's diameter
	world.worldDiameter = worldDiameterCalculator(world.blackbodyTemperature, world.worldDensity, world.worldType);
//	Determine the world's surface gravity
	world.surfaceGravity = surfaceGravityCalculator(world.worldDensity, world.worldDiameter);
//	Determine the world's mass
	world.worldMass = worldMassCalculator(world.worldDensity, world.worldDiameter);
//	Determine the world's atmospheric pressure
	world.atmosphericPressure = atmosphericPressureCalculator(world.atmosphereMass, world.surfaceGravity, world.worldType);
//	Determine the world's minimum molecular weight retained
	world.minimumMolecularWeightRetained = minimumMolecularWeightRetainedCalculator(world.blackbodyTemperature, world.worldDiameter, world.worldDensity, world.worldType);

//	Step 7: Resources and Habitability
//	Determine the world's resource value modifier
	world.resourceValueModifier = resourceDeterminator(world.worldType);
//	Determine the world's habitability modifier
	world.habitabilityModifier = habitabilityModifiersTable(world.worldType, world.atmosphereMass, world.hydrographicCoverage, world.atmosphericPressure, world.surfaceTemperature, world.worldAtmosphereComposition);

//	Return the rolled world
	return world;
}
*/

//	No confirmed exomoons
moon_t moonBuilder(star_t primary, moon_t moon, world_t planet)
{
//	Calculate blackbody temperature
	moon.blackbodyTemperature = calculateBlackbodyTemperature_ADVANCED(primary.stellarLuminosity, moon.orbitalRadius);
//	Determine world type
	if (planet.sizeClass == SC_SMALL_GAS_GIANT || planet.sizeClass == SC_MEDIUM_GAS_GIANT || planet.sizeClass == SC_LARGE_GAS_GIANT)
	{
		moon.worldType = determineWorldType_ADVANCED(moon.sizeClass, moon.blackbodyTemperature, 2, primary.stellarMass, primary.stellarAge, planet.gasGiantTinySulfurPresent);
	}

	else
	{
		moon.worldType = determineWorldType_ADVANCED(moon.sizeClass, moon.blackbodyTemperature, 1, primary.stellarMass, primary.stellarAge, planet.gasGiantTinySulfurPresent);
	}

//	Calculate the world's atmospheric mass (as a proportion of Earth's atmospheric mass)
	moon.atmosphereMass = atmosphereMassGenerator(moon.worldType);
//	Determine the atmosphere's composition
	moon.worldAtmosphereComposition = atmosphereComposition(moon.worldType);
//	Determine the world's Hydrographic coverage
	moon.hydrographicCoverage = hydrographicCoverageCalculator(moon.worldType);
//	Determine the world's greenhouse factor
	moon.greenhouseFactor = greenhouseFactorLookup(moon.worldType, moon.hydrographicCoverage);
//	Determine the world's absorption factor
	moon.absorptionFactor = absorptionFactorLookup(moon.worldType, moon.hydrographicCoverage);
//	Determine the world's blackbody correction
	moon.blackbodyCorrection = blackbodyCorrectionCalculator(moon.absorptionFactor, moon.greenhouseFactor, moon.atmosphereMass);
//	Determine the world's average surface temperature
	moon.surfaceTemperature = averageSurfaceTemperature_ADVANCED(moon.blackbodyTemperature, moon.blackbodyCorrection);

//	Step 29: World Sizes
//	Determine the world's density (as a proportion of Earth's density)
	moon.worldDensity = worldDensityTable(moon.worldType);
//	Determine the world's diameter
	moon.worldDiameter = worldDiameterCalculator(moon.blackbodyTemperature, moon.worldDensity, moon.worldType);
//	Calculate surface area
	tie(moon.totalSurfaceArea, moon.liquidSurfaceArea, moon.landSurfaceArea) = getSurfaceArea(moon.worldDiameter, moon.hydrographicCoverage);
//	Determine the world's surface gravity
	moon.surfaceGravity = surfaceGravityCalculator(moon.worldDensity, moon.worldDiameter);
//	Determine the world's atmospheric pressure
	moon.atmosphericPressure = atmosphericPressureCalculator(moon.atmosphereMass, moon.surfaceGravity, moon.worldType);
//	Determine the world's mass
	moon.worldMass = worldMassCalculator(moon.worldDensity, moon.worldDiameter);
//	Determine the planet's orbital eccentricity
	moon.orbitalEccentricity = calculatePlanetaryOrbitalEccentricity(moon.worldType, primary.gasGiantArrangement, primary.snowLineRadius, moon.orbitalRadius, primary.innerLimitRadius);
//	Determine the minimum separation from the primary
	moon.minimumSeparation = calculatePlanetPrimaryMinimumSeparation(moon.orbitalRadius, moon.orbitalEccentricity);
//	Determine the world's escape velocity
	moon.escapeVelocity = getEscapeVelocity(moon.worldMass * EARTH_MASS_IN_KG, (moon.worldDiameter / 2) * (EARTH_RADIUS_IN_KM * KM_TO_M));
//	Determine the maximum separation from the primary
	moon.maximumSeparation = calculatePlanetPrimaryMaximumSeparation(moon.orbitalRadius, moon.orbitalEccentricity);
	moon.tidalForceOnSatelliteByPlanet = calculateTidalForceOnSatelliteByPlanet(moon.worldMass, moon.worldDiameter, moon.orbitalRadius);

	moon.orbitalPeriod = calculateSatelliteOrbitalPeriod(moon.orbitalRadius, planet.worldDiameter, moon.worldMass);

//	Calculate the total tidal effect on the moon
	moon.totalTidalEffect = calculateTotalTidalEffect(0, 0, moon.tidalForceOnSatelliteByPlanet, primary.stellarAge, moon.worldMass);
//	Determine if the world is tidal locked
	moon.tidalLockedOrNot = (moon.totalTidalEffect >= 50) ? true : false;
//	Calculate the world's sidereal rotation in standard hours
	moon.rotationPeriod = calculateRotationPeriod(moon.totalTidalEffect, moon.orbitalPeriod, moon.worldType, moon.tidalLockedOrNot);
//	Determine if the world has a retrograde rotation
	moon.retrogradeOrNot = checkForRetrogradeRotation(POM_MOON);
	moon.equatorialRotationVelocity = getEquatorialRotationVelocity(moon.worldDiameter, moon.rotationPeriod);
	moon.apparentDayLength = determineLocalCalendar(moon.rotationPeriod, moon.retrogradeOrNot, POM_MOON, moon.orbitalPeriod, CALO_DAY_LENGTH, planet.orbitalPeriod);
	moon.apparentSatelliteOrbitalCycle = determineLocalCalendar(moon.rotationPeriod, moon.retrogradeOrNot, POM_MOON, moon.orbitalPeriod, CALO_ORBITAL_CYCLE, planet.orbitalPeriod);
//	Calculate the world's axial tilt
	moon.axialTilt = calculateAxialTilt();
//	Determine the world's volcanic activity
//	NOTE: This function takes two additional arguments for moons, but I wanted to test what happens if nothing is passed
	moon.volcanicActivityLevel = volcanicActivityTable(moon.worldType, moon.surfaceGravity, primary.stellarAge, POM_MOON, 0, planet.worldType);
//	Determine the effect the world's volcanic activity has on the world's atmosphere
	moon.worldAtmosphereComposition = volcanicActivityEffectOnGardenWorld(moon.volcanicActivityLevel, moon.worldType, moon.worldAtmosphereComposition);
//	Determine the world's tectonic activity
	moon.tectonicActivityLevel = getTectonicActivity(moon.worldType, moon.volcanicActivityLevel, moon.hydrographicCoverage, POM_MOON, 0);
//	Determine the effect of tectonic and volcanic activity on the world's habitability and resources
	tie(moon.habitabilityModifier, moon.resourceValueModifier) = effectsOfGeologicActivity(moon.volcanicActivityLevel, moon.tectonicActivityLevel, moon.habitabilityModifier, moon.resourceValueModifier);
//	Determine the world's minimum molecular weight retained
	moon.minimumMolecularWeightRetained = minimumMolecularWeightRetainedCalculator(moon.blackbodyTemperature, moon.worldDiameter, moon.worldDensity, moon.worldType);
	moon.atmosphericPressureCategory = atmosphericPressureCategoriesTable(moon.atmosphericPressure);
//	If the world is tide locked
	if (moon.tidalLockedOrNot == true)
	{
		tie(moon.atmosphericPressure, moon.atmosphericPressureCategory, moon.hydrographicCoverage) = tideLockedWorldEffects(moon.tidalLockedOrNot, moon.surfaceTemperature, moon.atmosphericPressureCategory, moon.atmosphericPressure, moon.atmosphericMass, moon.surfaceGravity, moon.worldType, moon.hydrographicCoverage);
	}
//	Check if the world is in a resonant orbit
//	If so, determine the effects that has on the world
	tie(moon.resonantOrNot, moon.apparentDayLength) = resonantWorldEffects(moon.orbitalEccentricity, moon.tidalLockedOrNot, moon.orbitalPeriod, moon.apparentDayLength);
//	Get the moon's magnetic field strength
	moon.magneticFieldStrength = getMagneticField(moon.worldMass, moon.worldDensity, moon.rotationPeriod, primary.stellarAge, moon.worldType);

//	Mapping the moon
//	Get the number of hexes per moon triangle side
	moon.hexesPerSide = getHexesPerSide(moon.worldDiameter);
//	Get the total number of hexes on the moon
	moon.totalHexes = getTotalHexCount(moon.hexesPerSide);
//	Get the number of tectonic plates
	moon.tectonicPlateCount = getTectonicPlateCount(moon.worldDiameter, moon.hydrographicCoverage);
//	Describe the tectonic plates
	for (int i = 0; i < moon.tectonicPlateCount; i++)
	{
		moon.tectonicPlateArray[i].tectonicPlateSize = getTectonicPlateSize(moon.worldDiameter);
		moon.tectonicPlateArray[i].tectonicPlateMovementType = getTectonicPlateMovementType();
	}
//	Get the number of water hexes
	moon.waterHexCount = getWaterHexCount(moon.totalHexes, moon.hydrographicCoverage);
//	Get the number of land hexes
	moon.landHexCount = getLandHexCount(moon.totalHexes, moon.waterHexCount);
//	Determine the number of each hex type
	if (moon.hydrographicCoverage = 0)
	{
		moon.numberOfMajorOceans 		= 0;
		moon.numberOfMinorOceans 		= 0;
		moon.numberOfSmallSeas 			= 0;
		moon.numberOfScatteredLakes 	= 0;
		moon.numberOfMajorContinents 	= 0;
		moon.numberOfMinorContinents 	= 0;
		moon.numberOfMajorIslands 		= 0;
		moon.numberOfArchipelagoes 		= 0;

	}
//	If the planet has water
	else
	{
//		Hex type dice roll and hydrographicCoverage modifier
		int hexDiceRoll 				= diceRoller(6, 1) + (3 * int(ceil(moon.hydrographicCoverage * 10)));
		moon.numberOfMajorOceans 		= getMajorOceans(hexDiceRoll);
		moon.numberOfMinorOceans 		= getMinorOceans(hexDiceRoll);
		moon.numberOfSmallSeas 			= getSmallSeas(hexDiceRoll);
		moon.numberOfScatteredLakes 	= getScatteredLakes(hexDiceRoll);
		moon.numberOfMajorContinents 	= getMajorContinents(hexDiceRoll);
		moon.numberOfMinorContinents 	= getMinorContinents(hexDiceRoll);
		moon.numberOfMajorIslands 		= getMajorIslands(hexDiceRoll);
		moon.numberOfArchipelagoes 		= getArchipelagoes(hexDiceRoll);
	}


	return moon;

}

//	Advanced world design sequence
//	This function applies only to terrestrial worlds
//	21/11/2020: Modified to add .csv support
world_t worldBuilder_ADVANCED(char sizeClass, float averageOrbitalRadius, star_t primary, rapidcsv::Document& worldDoc, int worldArrayIndex, bool randomWorld)
{
//	Initialize world
	world_t world = primary.worldArray[worldArrayIndex];
	if (randomWorld == true)	{world.planetDBIndex = std::numeric_limits<int>::max();}
/*	if (sizeClass == SC_ASTEROID_BELT)
	{
		std::cout << "sizeClass = SC_ASTEROID_BELT" << std::endl;
		std::cout << "averageOrbitalRadius = " << averageOrbitalRadius << std::endl;
	}
*/
	std::cout << "\nEnterd worldBuilder_ADVANCED" << std::endl;
//	Assign semi-major axis
	world.orbitalRadius = averageOrbitalRadius;
	std::cout << "randomWorld == " << randomWorld << std::endl;
	std::cout << "world.orbitalRadius == " << world.orbitalRadius << std::endl;
//	Calculate blackbody temperature
	world.blackbodyTemperature = calculateBlackbodyTemperature_ADVANCED(primary.stellarLuminosity, world.orbitalRadius);
//	world.blackbodyTemperature = (worldDoc.GetCell<std::string>("pl_eqt", world.planetDBIndex) != "" && randomWorld == false) ? worldDoc.GetCell<float>("pl_eqt", world.planetDBIndex) : calculateBlackbodyTemperature_ADVANCED(primary.stellarLuminosity, world.orbitalRadius);
	std::cout << "world.blackbodyTemperature == " << world.blackbodyTemperature << std::endl;
	world.sizeClass = sizeClass;

//	Assign the orbital radius
	world.orbitalRadius = averageOrbitalRadius;
//	Check if the orbital slot is empty
	if (sizeClass == SC_EMPTY_ORBIT)
	{
		world.emptyOrNot = true;
		world.worldType = WT_EMPTY_ORBIT;
	}

//	For gas giants
	else if (sizeClass == SC_SMALL_GAS_GIANT || sizeClass == SC_MEDIUM_GAS_GIANT || sizeClass == SC_LARGE_GAS_GIANT)
	{
//		World is present
		world.emptyOrNot == false;
//		Determine world type
		world.worldType = determineWorldType_ADVANCED(sizeClass, world.blackbodyTemperature, 0, primary.stellarMass, primary.stellarAge, false);
		std::cout << "world.worldType == " << WT_S_LOOKUP_TABLE[world.worldType] << std::endl;
		std::cout << "world.planetDBIndex == " << world.planetDBIndex << std::endl;
//		Determine world mass
//		If the mass is not provided
		if (randomWorld == true || worldDoc.GetCell<std::string>("pl_bmasse", world.planetDBIndex) == "")
		{
			std::cout << "Mass is not provided" << std::endl;
//			If the density is not provided
			if (randomWorld == true || worldDoc.GetCell<std::string>("pl_dens", world.planetDBIndex) == "")
			{
				std::cout << "density is not provided" << std::endl;
//				If the radius is not provided
				if (randomWorld == true || worldDoc.GetCell<std::string>("pl_rade", world.planetDBIndex) == "")
				{
					std::cout << "radius is not provided" << std::endl;
					world.worldDensity = getGasGiantDensity(world.sizeClass);
					world.worldMass = getGasGiantMass(world.sizeClass);
					world.worldDiameter = getGasGiantDiameter(world.worldMass, world.worldDensity);
				}

//				If the radius is provided
				else
				{
					std::cout << "Radius is provided" << std::endl;
					world.worldDiameter = worldDoc.GetCell<float>("pl_rade", world.planetDBIndex) * 2;
					world.worldDensity = getGasGiantDensity(world.sizeClass);
					world.worldMass = worldMassCalculator(world.worldDensity, world.worldDiameter);
				}
			}

//			If the density is provided
			else
			{
				std::cout << "Density is provided" << std::endl;
//				If the radius is not provided
				if (randomWorld == true || worldDoc.GetCell<std::string>("pl_rade", world.planetDBIndex) == "")
				{
					std::cout << "radius is not provided" << std::endl;
					world.worldDensity = worldDoc.GetCell<float>("pl_dens", world.planetDBIndex) / EARTH_DENSITY_IN_GRAMS_PER_CUBIC_CM;
					world.worldDiameter = std::cbrt(world.worldMass / world.worldDensity);
					world.worldMass = worldMassCalculator(world.worldDensity, world.worldDiameter);
				}

//				If the radius is provided
				else
				{
					std::cout << "Radius is provided" << std::endl;
					world.worldDiameter = worldDoc.GetCell<float>("pl_rade", world.planetDBIndex) * 2;
					world.worldDensity = worldDoc.GetCell<float>("pl_dens", world.planetDBIndex) / EARTH_DENSITY_IN_GRAMS_PER_CUBIC_CM;
					world.worldMass = worldMassCalculator(world.worldDensity, world.worldDiameter);
				}
			}
		}

//		If the mass is provided
		else
		{
			std::cout << "Mass is provided" << std::endl;
//			If the density is not provided
			if (worldDoc.GetCell<std::string>("pl_dens", world.planetDBIndex) == "")
			{
				std::cout << "density is not provided" << std::endl;
//				If the radius is not provided
				if (worldDoc.GetCell<std::string>("pl_rade", world.planetDBIndex) == "")
				{
					std::cout << "radius is not provided" << std::endl;
					world.worldMass = worldDoc.GetCell<float>("pl_bmasse", world.planetDBIndex);
					world.worldDiameter = getGasGiantDiameter(world.worldMass, world.worldDensity);
					world.worldDensity = world.worldMass / std::pow(world.worldDiameter, 3);
				}

//				If the radius is provided
				else
				{
					std::cout << "Radius is provided" << std::endl;
					world.worldMass = worldDoc.GetCell<float>("pl_bmasse", world.planetDBIndex);
					world.worldDiameter = worldDoc.GetCell<float>("pl_rade", world.planetDBIndex) * 2;
					world.worldDensity = world.worldMass / std::pow(world.worldDiameter, 3);
				}
			}

//			If the density is provided
			else
			{
				std::cout << "Density is provided" << std::endl;
//				If the radius is not provided
				if (worldDoc.GetCell<std::string>("pl_rade", world.planetDBIndex) == "")
				{
					std::cout << "radius is not provided" << std::endl;
					world.worldDensity = worldDoc.GetCell<float>("pl_dens", world.planetDBIndex) / EARTH_DENSITY_IN_GRAMS_PER_CUBIC_CM;
					world.worldMass = worldDoc.GetCell<float>("pl_bmasse", world.planetDBIndex);
					world.worldDiameter = std::cbrt(world.worldMass / world.worldDensity);
				}

//				If the radius is provided
				else
				{
					std::cout << "Radius is provided" << std::endl;
					world.worldDiameter = worldDoc.GetCell<float>("pl_rade", world.planetDBIndex) * 2;
					world.worldDensity = worldDoc.GetCell<float>("pl_dens", world.planetDBIndex) / EARTH_DENSITY_IN_GRAMS_PER_CUBIC_CM;
					world.worldMass = worldDoc.GetCell<float>("pl_bmasse", world.planetDBIndex);
				}
			}
		}

//		For mapping
		world.totalSurfaceArea = 0;
		world.liquidSurfaceArea = 0;
		world.landSurfaceArea = 0;
//		Determine surface gravity at cloud tops
		world.surfaceGravity = surfaceGravityCalculator(world.worldDensity, world.worldDiameter);
//		Determine orbital period
		world.orbitalPeriod = (randomWorld == true || worldDoc.GetCell<std::string>("pl_orbper", world.planetDBIndex) == "") ? calculatePlanetaryOrbitalPeriod(world.orbitalRadius, primary.stellarMass, world.worldMass) : worldDoc.GetCell<float>("pl_orbper", world.planetDBIndex);
//		Determine orbital eccentricity
		world.orbitalEccentricity = (randomWorld == true || worldDoc.GetCell<std::string>("pl_orbeccen", world.planetDBIndex) == "") ? calculatePlanetaryOrbitalEccentricity(world.worldType, primary.gasGiantArrangement, primary.snowLineRadius, world.orbitalRadius, primary.innerLimitRadius) : worldDoc.GetCell<float>("pl_orbeccen", world.planetDBIndex);
//		Determine minimum separation from primary
		world.minimumSeparation = calculatePlanetPrimaryMinimumSeparation(world.orbitalRadius, world.orbitalEccentricity);
//		Determine maximum separation from primary
		world.maximumSeparation = calculatePlanetPrimaryMaximumSeparation(world.orbitalRadius, world.orbitalEccentricity);
//		Determine the world's escape velocity
		world.escapeVelocity = getEscapeVelocity(world.worldMass * EARTH_MASS_IN_KG, (world.worldDiameter / 2) * (EARTH_RADIUS_IN_KM * KM_TO_M));
//		Calculate the world's sidereal rotation in standard hours
		world.rotationPeriod = calculateRotationPeriod(world.totalTidalEffect, world.orbitalPeriod, world.worldType, world.tidalLockedOrNot);
//		std::cout << "Got to rotationPeriod" << std::endl;
//		Determine if the world has a retrograde rotation
		world.retrogradeOrNot = checkForRetrogradeRotation(POM_PLANET);
		world.equatorialRotationVelocity = getEquatorialRotationVelocity(world.worldDiameter, world.rotationPeriod);
		world.surfaceIrradiance = solarPowerAtDistance(primary.stellarRadius, world.orbitalRadius, primary.energyRadiated);
//		Determine number of moons
		world.firstFamilyMoonlets = getFirstFamily(world.orbitalRadius);
		world.secondFamilyMajorMoons = getSecondFamily(world.orbitalRadius);
		world.thirdFamilyMoonlets = getThirdFamily(world.orbitalRadius);
//		Local calendar
//		A negative value for apparent day length is valid even if the world's rotation is not retrograde
//		This means that the primary will rise in the west and set in the east
		world.apparentDayLength = determineLocalCalendar(world.rotationPeriod, world.retrogradeOrNot, POM_PLANET, world.orbitalPeriod, CALO_DAY_LENGTH, 0);
//		std::cout << "Got to apparentDayLength" << std::endl;

//		Calculate the world's axial tilt
		world.axialTilt = calculateAxialTilt();
//		std::cout << "Got to axialTilt" << std::endl;
//		Determine the world's minimum molecular weight retained
		world.minimumMolecularWeightRetained = minimumMolecularWeightRetainedCalculator(world.blackbodyTemperature, world.worldDiameter, world.worldDensity, world.worldType);
//		If the world is tide locked
		if (world.tidalLockedOrNot == true)
		{
			tie(world.atmosphericPressure, world.atmosphericPressureCategory, world.hydrographicCoverage) = tideLockedWorldEffects(world.tidalLockedOrNot, world.surfaceTemperature, world.atmosphericPressureCategory, world.atmosphericPressure, world.atmosphereMass, world.surfaceGravity, world.worldType, world.hydrographicCoverage);
		}
//		Check if the world is in a resonant orbit
//		If so, determine the effects that has on the world
		tie(world.resonantOrNot, world.apparentDayLength) = resonantWorldEffects(world.orbitalEccentricity, world.tidalLockedOrNot,	world.orbitalPeriod, world.apparentDayLength);

//		Generate moonlets in the first family
		for (int8_t i = 0; i < world.firstFamilyMoonlets; i++)
		{
			world.firstFamilyMoonletArray[i].orbitalRadius = placeMoonOrbits(world.worldDiameter, 0, 1);
		}
		std::cout << "world.secondFamilyMajorMoons == " << int(world.secondFamilyMajorMoons) << std::endl;
//		Generate major moons in second family
		if (world.secondFamilyMajorMoons > 0)
		{
			for (int i = 0; i < int(world.secondFamilyMajorMoons); i++)
			{
//				std::cout << "secondFamilyMajorMoons = " << (int)world.secondFamilyMajorMoons << std::endl;
//				std::cout << "i = " << (int)i << std::endl;
				world.majorMoonArray[i].moonSizeClass = moonSizeTable();
//				std::cout << "set moonSizeClass" << std::endl;
				world.majorMoonArray[i].orbitalRadius = placeMoonOrbits(world.worldDiameter, world.majorMoonArray[i].moonSizeClass, 2);
//				std::cout << "set orbitalRadius" << std::endl;
				if (i != 0)
				{
	//				Iterate through all previous moons
					for (int8_t j = 0; j < i; j++)
					{
//						std::cout << "abs(world.majorMoonArray[i].orbitalRadius - world.majorMoonArray[j].orbitalRadius) = " << abs(world.majorMoonArray[i].orbitalRadius - world.majorMoonArray[j].orbitalRadius) << std::endl;
//						std::cout << "worldDiameter = " << world.worldDiameter << std::endl;
//						std::cout << "j = " << (int)j << std::endl;
	//					If the distance between moon i and any of the previous moons is less than the planet's diameter
						if (abs(world.majorMoonArray[i].orbitalRadius - world.majorMoonArray[j].orbitalRadius) < world.worldDiameter)
						{
	//						Decrement by one and repeat
							i += -1;
							break;
						}
					}
				}

//				Determine the moon's sizeClass
				if (world.majorMoonArray[i].moonSizeClass == -3) {world.majorMoonArray[i].sizeClass = SC_TERRESTRIAL_PLANET_TINY;}
				else if (world.majorMoonArray[i].moonSizeClass == -2)	{world.majorMoonArray[i].sizeClass = SC_TERRESTRIAL_PLANET_SMALL;}
				else {world.majorMoonArray[i].sizeClass = SC_TERRESTRIAL_PLANET_STANDARD;}
//				std::cout << "set sizeClass" << std::endl;
	//			Run worldBuilder_ADVANCED for each moon
				world.majorMoonArray[i] = moonBuilder(primary, world.majorMoonArray[i], world);
//				std::cout << "built moon" << std::endl;
			}
//			std::cout << "finished moonbuilding" << std::endl;
		}
//		Generate moonlets in the third family
		for (int i = 0; i < world.thirdFamilyMoonlets; i++)
		{
			world.thirdFamilyMoonletArray[i].orbitalRadius = placeMoonOrbits(world.worldDiameter, 0, 3);
		}

//		Get the world's magnetic field strength
//		std::cout << "about to set magneticFieldStrength" << std::endl;
		world.magneticFieldStrength = getMagneticField(world.worldMass, world.worldDensity, world.rotationPeriod, primary.stellarAge, world.worldType);
//		std::cout << "set magneticFieldStrength" << std::endl;
		world.numberOfMajorOceans 		= 0;
		world.numberOfMinorOceans 		= 0;
		world.numberOfSmallSeas 		= 0;
		world.numberOfScatteredLakes 	= 0;
		world.numberOfMajorContinents 	= 0;
		world.numberOfMinorContinents 	= 0;
		world.numberOfMajorIslands 		= 0;
		world.numberOfArchipelagoes 	= 0;
	}

//	For terrestrial worlds
	else
	{
//		World is present
		world.emptyOrNot == false;
//		Calculate blackbody temperature
		std::cout << "Got to blackbody temperature" << std::endl;
//		world.blackbodyTemperature = calculateBlackbodyTemperature_ADVANCED(primary.stellarLuminosity, world.orbitalRadius);
//		Determine world type
		world.worldType = determineWorldType_ADVANCED(sizeClass, world.blackbodyTemperature, 0, primary.stellarMass, primary.stellarAge, false);
		std::cout << "world.worldType == " << WT_S_LOOKUP_TABLE[world.worldType] << std::endl;
		std::cout << "world.planetDBIndex == " << world.planetDBIndex << std::endl;

		std::cout << "worldType = " << world.worldType << std::endl;
		std::cout << "Got to worldType" << std::endl;
//		Place major moons

//		Step 26: Atmosphere
//		Calculate the world's atmospheric mass (as a proportion of Earth's atmospheric mass)
		world.atmosphereMass = atmosphereMassGenerator(world.worldType);
		std::cout << "Got to atmosphereMass" << std::endl;
//		Determine the atmosphere's composition
		world.worldAtmosphereComposition = atmosphereComposition(world.worldType);
		std::cout << "Got to worldAtmosphereComposition" << std::endl;

//		Step 27: Hydrographic Coverage
//		Determine the world's Hydrographic coverage
//		Even an ocean world can have no water if it is tidal locked
		world.hydrographicCoverage = hydrographicCoverageCalculator(world.worldType);
		std::cout << "Got to worldAtmosphereComposition" << std::endl;

//		Step 28: Climate
//		Determine the world's greenhouse factor
		world.greenhouseFactor = greenhouseFactorLookup(world.worldType, world.hydrographicCoverage);
		std::cout << "Got to greenhouseFactor" << std::endl;
//		Determine the world's absorption factor
		world.absorptionFactor = absorptionFactorLookup(world.worldType, world.hydrographicCoverage);
		std::cout << "Got to absorptionFactor" << std::endl;
//		Determine the world's blackbody correction
		world.blackbodyCorrection = blackbodyCorrectionCalculator(world.absorptionFactor, world.greenhouseFactor, world.atmosphereMass);
		std::cout << "Got to blackbodyCorrection" << std::endl;
//		Determine the world's average surface temperature
		world.surfaceTemperature = averageSurfaceTemperature_ADVANCED(world.blackbodyTemperature, world.blackbodyCorrection);
		std::cout << "Got to surfaceTemperature" << std::endl;

//		Step 29: World Sizes
//		Determine the world's mass, density, and diameter

//		If the mass is not provided
		if (randomWorld == true || worldDoc.GetCell<std::string>("pl_bmasse", world.planetDBIndex) == "")
		{
			std::cout << "Mass is not provided" << std::endl;
//			If the density is not provided
			if (randomWorld == true || worldDoc.GetCell<std::string>("pl_dens", world.planetDBIndex) == "")
			{
				std::cout << "density is not provided" << std::endl;
//				If the radius is not provided
				if (randomWorld == true || worldDoc.GetCell<std::string>("pl_rade", world.planetDBIndex) == "")
				{
					std::cout << "radius is not provided" << std::endl;
					world.worldDensity = worldDensityTable(world.worldType);
					world.worldDiameter = worldDiameterCalculator(world.blackbodyTemperature, world.worldDensity, world.worldType);
					world.worldMass = worldMassCalculator(world.worldDensity, world.worldDiameter);
				}

//				If the radius is provided
				else
				{
					std::cout << "Radius is provided" << std::endl;
					world.worldDiameter = worldDoc.GetCell<float>("pl_rade", world.planetDBIndex) * 2;
					world.worldDensity = worldDensityTable(world.worldType);
					world.worldMass = worldMassCalculator(world.worldDensity, world.worldDiameter);
				}
			}

//			If the density is provided
			else
			{
				std::cout << "Density is provided" << std::endl;
//				If the radius is not provided
				if (randomWorld == true || worldDoc.GetCell<std::string>("pl_rade", world.planetDBIndex) == "")
				{
					std::cout << "radius is not provided" << std::endl;
					world.worldDensity = worldDoc.GetCell<float>("pl_dens", world.planetDBIndex) / EARTH_DENSITY_IN_GRAMS_PER_CUBIC_CM;
					world.worldDiameter = std::cbrt(world.worldMass / world.worldDensity);
					world.worldMass = worldMassCalculator(world.worldDensity, world.worldDiameter);
				}

//				If the radius is provided
				else
				{
					std::cout << "Radius is provided" << std::endl;
					world.worldDiameter = worldDoc.GetCell<float>("pl_rade", world.planetDBIndex) * 2;
					world.worldDensity = worldDoc.GetCell<float>("pl_dens", world.planetDBIndex) / EARTH_DENSITY_IN_GRAMS_PER_CUBIC_CM;
					world.worldMass = worldMassCalculator(world.worldDensity, world.worldDiameter);
				}
			}
		}

//		If the mass is provided
		else
		{
			std::cout << "Mass is provided" << std::endl;
//			If the density is not provided
			if (worldDoc.GetCell<std::string>("pl_dens", world.planetDBIndex) == "")
			{
				std::cout << "density is not provided" << std::endl;
//				If the radius is not provided
				if (worldDoc.GetCell<std::string>("pl_rade", world.planetDBIndex) == "")
				{
					std::cout << "radius is not provided" << std::endl;
					world.worldMass = worldDoc.GetCell<float>("pl_bmasse", world.planetDBIndex);
					world.worldDiameter = worldDiameterCalculator(world.blackbodyTemperature, world.worldDensity, world.worldType);
					world.worldDensity = world.worldMass / std::pow(world.worldDiameter, 3);
				}

//				If the radius is provided
				else
				{
					std::cout << "Radius is provided" << std::endl;
					world.worldMass = worldDoc.GetCell<float>("pl_bmasse", world.planetDBIndex);
					world.worldDiameter = worldDoc.GetCell<float>("pl_rade", world.planetDBIndex) * 2;
					world.worldDensity = world.worldMass / std::pow(world.worldDiameter, 3);
				}
			}

//			If the density is provided
			else
			{
				std::cout << "Density is provided" << std::endl;
//				If the radius is not provided
				if (worldDoc.GetCell<std::string>("pl_rade", world.planetDBIndex) == "")
				{
					std::cout << "radius is not provided" << std::endl;
					world.worldDensity = worldDoc.GetCell<float>("pl_dens", world.planetDBIndex) / EARTH_DENSITY_IN_GRAMS_PER_CUBIC_CM;
					world.worldMass = worldDoc.GetCell<float>("pl_bmasse", world.planetDBIndex);
					world.worldDiameter = std::cbrt(world.worldMass / world.worldDensity);
				}

//				If the radius is provided
				else
				{
					std::cout << "Radius is provided" << std::endl;
					world.worldDiameter = worldDoc.GetCell<float>("pl_rade", world.planetDBIndex) * 2;
					world.worldDensity = worldDoc.GetCell<float>("pl_dens", world.planetDBIndex) / EARTH_DENSITY_IN_GRAMS_PER_CUBIC_CM;
					world.worldMass = worldDoc.GetCell<float>("pl_bmasse", world.planetDBIndex);
				}
			}
		}

		std::cout << "world.worldMass == " << world.worldMass << std::endl;
		std::cout << "Got to worldDiameter" << std::endl;
//		Calculate surface area
		tie(world.totalSurfaceArea, world.liquidSurfaceArea, world.landSurfaceArea) = getSurfaceArea(world.worldDiameter, world.hydrographicCoverage);
//		Determine the world's surface gravity
		world.surfaceGravity = surfaceGravityCalculator(world.worldDensity, world.worldDiameter);
		std::cout << "Got to surfaceGravity" << std::endl;
//		Determine the world's atmospheric pressure
		world.atmosphericPressure = atmosphericPressureCalculator(world.atmosphereMass, world.surfaceGravity, world.worldType);

//		Step 30: Dynamic Parameters
		world.orbitalPeriod = (randomWorld == true || worldDoc.GetCell<std::string>("pl_orbper", world.planetDBIndex) == "") ? calculatePlanetaryOrbitalPeriod(world.orbitalRadius, primary.stellarMass, world.worldMass) : worldDoc.GetCell<float>("pl_orbper", world.planetDBIndex);
		std::cout << "Got to orbitalPeriod" << std::endl;
//		Determine the planet's orbital eccentricity
		world.orbitalEccentricity = (randomWorld == true || worldDoc.GetCell<std::string>("pl_orbeccen", world.planetDBIndex) == "") ? calculatePlanetaryOrbitalEccentricity(world.worldType, primary.gasGiantArrangement, primary.snowLineRadius, world.orbitalRadius, primary.innerLimitRadius) : worldDoc.GetCell<float>("pl_orbeccen", world.planetDBIndex);
		std::cout << "Got to orbitalEccentricity" << std::endl;
//		Determine the minimum separation from the primary
		world.minimumSeparation = calculatePlanetPrimaryMinimumSeparation(world.orbitalRadius, world.orbitalEccentricity);
		std::cout << "Got to minimumSeparation" << std::endl;
//		Determine the maximum separation from the primary
		world.maximumSeparation = calculatePlanetPrimaryMaximumSeparation(world.orbitalRadius, world.orbitalEccentricity);
		std::cout << "Got to maximumSeparation" << std::endl;
//		Determine the world's escape velocity
		world.escapeVelocity = getEscapeVelocity(world.worldMass * EARTH_MASS_IN_KG, (world.worldDiameter / 2) * (EARTH_RADIUS_IN_KM * KM_TO_M));

		world.numberOfMajorMoons = getTerrestrialMajorMoons(world.orbitalRadius, world.worldType);
		world.numberOfMajorMoons = (world.numberOfMajorMoons < 0) ? 0 : world.numberOfMajorMoons;
		std::cout << "Got to numberOfMajorMoons" << std::endl;
//		Place moonlets
		world.terrestrialMoonlet = getTerrestrialMoonlets(world.orbitalRadius, world.worldType);
		std::cout << "Got to terrestrialMoonlet" << std::endl;

//		Generate major moons
		if (world.worldType != WT_ASTEROID_BELT && world.numberOfMajorMoons != 0)
		{
			for (int i = 0; i < world.numberOfMajorMoons; i++)
			{
//				Determine the size of the moon
				world.majorMoonArray[i].moonSizeClass = moonSizeTable();
//				Determine the orbital radius of the moon
				world.majorMoonArray[i].orbitalRadius = placeMoonOrbits(world.worldDiameter, world.majorMoonArray[i].moonSizeClass, 0);
//				Check if any of the moons orbit within 5 planetary diameters of each other
//				For any moon but the first
				if (i != 0)
				{
//					Iterate through all previous moons
					for (int j = 0; j < i; j++)
					{
//						If the distance between moon i and any of the previous moons is less than 5 times the planet's diameter
						if (abs(world.majorMoonArray[i].orbitalRadius - world.majorMoonArray[j].orbitalRadius) < (5 * world.worldDiameter))
						{
//							std::cout << "majorMoonArray[" << i << "].orbital radius = " << world.majorMoonArray[i].orbitalRadius << std::endl;
//							std::cout << "majorMoonArray[" << j << "].orbital radius = " << world.majorMoonArray[j].orbitalRadius << std::endl;
//							std::cout << " 5 * planetDiameter = " << 5 * world.worldDiameter << std::endl;
//							std::cout << "i - j = " << world.majorMoonArray[i].orbitalRadius - world.majorMoonArray[j].orbitalRadius << std::endl;
//							Decrement by one and repeat
							i += -1;
							break;
						}
					}
				}

//				Determine the moon's sizeClass
				if (sizeClass == SC_EMPTY_ORBIT || sizeClass == SC_TERRESTRIAL_PLANET_SMALL || (sizeClass == SC_TERRESTRIAL_PLANET_STANDARD && world.majorMoonArray[i].moonSizeClass < -1) || ((sizeClass == SC_TERRESTRIAL_PLANET_LARGE || sizeClass == WT_SMALL_GAS_GIANT || sizeClass == WT_MEDIUM_GAS_GIANT || sizeClass == WT_LARGE_GAS_GIANT) && world.majorMoonArray[i].moonSizeClass == -3)) {world.majorMoonArray[i].sizeClass = SC_TERRESTRIAL_PLANET_TINY;}
				else if ((sizeClass == SC_TERRESTRIAL_PLANET_STANDARD && world.majorMoonArray[i].moonSizeClass == -1) || ((sizeClass == SC_TERRESTRIAL_PLANET_LARGE || sizeClass == WT_SMALL_GAS_GIANT || sizeClass == WT_MEDIUM_GAS_GIANT || sizeClass == WT_LARGE_GAS_GIANT) && world.majorMoonArray[i].moonSizeClass == -2))	{world.majorMoonArray[i].sizeClass = SC_TERRESTRIAL_PLANET_SMALL;}
				else {world.majorMoonArray[i].sizeClass = SC_TERRESTRIAL_PLANET_STANDARD;}

//				Run worldBuilder_ADVANCED for each moon
				world.majorMoonArray[i] = moonBuilder(primary, world.majorMoonArray[i], world);
			}
		}
//		Set the initial tidal force by satellites to zero
		world.tidalForceOnPlanetBySatellite = 0;
		for (int i = 0; i < world.numberOfMajorMoons; i++)
		{
			world.tidalForceOnPlanetBySatellite += calculateTidalForceOnPlanetBySatellite(world.majorMoonArray[i].worldMass, world.worldDiameter, world.majorMoonArray[i].orbitalRadius);
//			Since the world in question is a planet, set tidalForceOnSatelliteByPlanet to 0
			world.tidalForceOnSatelliteByPlanet = 0;
		}
//		Calculate the tidal force exerted on the planet by its primary
		std::cout << "primary.stellarMass == " << primary.stellarMass << std::endl;
		std::cout << "world.worldDiameter == " << world.worldDiameter << std::endl;
		std::cout << "world.orbitalRadius == " << world.orbitalRadius << std::endl;
		world.tidalForceOnPlanetByPrimary = calculateTidalForceOnPlanetByPrimary(primary.stellarMass, world.worldDiameter, world.orbitalRadius);
		std::cout << "Got to tidalForceOnPlanetByPrimary" << std::endl;


//		Calculate the total tidal effect on the planet
		world.totalTidalEffect = calculateTotalTidalEffect(world.tidalForceOnPlanetBySatellite, world.tidalForceOnPlanetByPrimary, world.tidalForceOnSatelliteByPlanet, primary.stellarAge, world.worldMass);
		std::cout << "Got to totalTidalEffect" << std::endl;
//		Determine if the world is tidal locked
		world.tidalLockedOrNot = (world.totalTidalEffect >= 50) ? true : false;
		std::cout << "Got to tidalLockedOrNot" << std::endl;

//		Calculate the world's sidereal rotation in standard hours
		world.rotationPeriod = calculateRotationPeriod(world.totalTidalEffect, world.orbitalPeriod, world.worldType, world.tidalLockedOrNot);
		std::cout << "Got to rotationPeriod" << std::endl;
//		Determine if the world has a retrograde rotation
		world.retrogradeOrNot = checkForRetrogradeRotation(POM_PLANET);
		std::cout << "Got to retrogradeOrNot" << std::endl;
		world.equatorialRotationVelocity = getEquatorialRotationVelocity(world.worldDiameter, world.rotationPeriod);
		world.surfaceIrradiance = solarPowerAtDistance(primary.stellarRadius, world.orbitalRadius, primary.energyRadiated);
//		Local calendar
//		A negative value for apparent day length is valid even if the world's rotation is not retrograde
//		This means that the primary will rise in the west and set in the east
		world.apparentDayLength = determineLocalCalendar(world.rotationPeriod, world.retrogradeOrNot, POM_PLANET, world.orbitalPeriod, CALO_DAY_LENGTH, 0);
		std::cout << "Got to apparentDayLength" << std::endl;

//		Calculate the world's axial tilt
		world.axialTilt = calculateAxialTilt();
		std::cout << "Got to axialTilt" << std::endl;

//		Determine the world's volcanic activity
//		NOTE: This function takes two additional arguments for moons, but I wanted to test what happens if nothing is passed
		world.volcanicActivityLevel = volcanicActivityTable(world.worldType, world.surfaceGravity, primary.stellarAge, POM_PLANET, world.numberOfMajorMoons, 0);
		std::cout << "Volcanic activity level: " << world.volcanicActivityLevel << std::endl;
		std::cout << "Got to volcanicActivityLevel" << std::endl;
//		Determine the effect the world's volcanic activity has on the world's atmosphere
		world.worldAtmosphereComposition = volcanicActivityEffectOnGardenWorld(world.volcanicActivityLevel, world.worldType, world.worldAtmosphereComposition);
		std::cout << "Got to volcanicActivityEffectOnGardenWorld" << std::endl;
//		Determine the world's tectonic activity
		world.tectonicActivityLevel = getTectonicActivity(world.worldType, world.volcanicActivityLevel, world.hydrographicCoverage, POM_PLANET, world.numberOfMajorMoons);
		std::cout << "Got to tectonicActivityLevel" << std::endl;
//		Determine the effect of tectonic and volcanic activity on the world's habitability and resources
		tie(world.habitabilityModifier, world.resourceValueModifier) = effectsOfGeologicActivity(world.volcanicActivityLevel, world.tectonicActivityLevel, world.habitabilityModifier, world.resourceValueModifier);
		std::cout << "Got to effectsOfGeologicActivity" << std::endl;

//		Determine the world's minimum molecular weight retained
		world.minimumMolecularWeightRetained = minimumMolecularWeightRetainedCalculator(world.blackbodyTemperature, world.worldDiameter, world.worldDensity, world.worldType);
		world.atmosphericPressureCategory = atmosphericPressureCategoriesTable(world.atmosphericPressure);
//		If the world is tide locked
		if (world.tidalLockedOrNot == true)
		{
			tie(world.atmosphericPressure, world.atmosphericPressureCategory, world.hydrographicCoverage) = tideLockedWorldEffects(world.tidalLockedOrNot, world.surfaceTemperature, world.atmosphericPressureCategory, world.atmosphericPressure, world.atmosphereMass, world.surfaceGravity, world.worldType, world.hydrographicCoverage);
		}
		std::cout << "Got to tideLockedWorldEffects" << std::endl;
//		Check if the world is in a resonant orbit
//		If so, determine the effects that has on the world
		tie(world.resonantOrNot, world.apparentDayLength) = resonantWorldEffects(world.orbitalEccentricity, world.tidalLockedOrNot,	world.orbitalPeriod, world.apparentDayLength);
		std::cout << "Got to resonantWorldEffects" << std::endl;
//		Get the world's magnetic field strength
		world.magneticFieldStrength = getMagneticField(world.worldMass, world.worldDensity, world.rotationPeriod, primary.stellarAge, world.worldType);

//		Mapping the world
//		Asteroid belts have no maps
		if (world.worldType != WT_ASTEROID_BELT)
		{
//			Get the number of hexes per world triangle side
			world.hexesPerSide = getHexesPerSide(world.worldDiameter);
//			Get the total number of hexes on the world
			world.totalHexes = getTotalHexCount(world.hexesPerSide);
//			Get the number of tectonic plates
			world.tectonicPlateCount = getTectonicPlateCount(world.worldDiameter, world.hydrographicCoverage);
//			Describe the tectonic plates
			for (int i = 0; i < world.tectonicPlateCount; i++)
			{
				world.tectonicPlateArray[i].tectonicPlateSize = getTectonicPlateSize(world.worldDiameter);
				world.tectonicPlateArray[i].tectonicPlateMovementType = getTectonicPlateMovementType();
			}
//			Get the number of water hexes
			world.waterHexCount = getWaterHexCount(world.totalHexes, world.hydrographicCoverage);
//			Get the number of land hexes
			world.landHexCount = getLandHexCount(world.totalHexes, world.waterHexCount);
//			Determine the number of each hex type
			if (world.hydrographicCoverage = 0)
			{
				world.numberOfMajorOceans 		= 0;
				world.numberOfMinorOceans 		= 0;
				world.numberOfSmallSeas 		= 0;
				world.numberOfScatteredLakes 	= 0;
				world.numberOfMajorContinents 	= 0;
				world.numberOfMinorContinents 	= 0;
				world.numberOfMajorIslands 		= 0;
				world.numberOfArchipelagoes 	= 0;

			}
//			If the planet has water
			else
			{
//				Hex type dice roll and hydrographicCoverage modifier
				int hexDiceRoll 				= diceRoller(6, 1) + (3 * int(ceil(world.hydrographicCoverage * 10)));
				world.numberOfMajorOceans 		= getMajorOceans(hexDiceRoll);
				world.numberOfMinorOceans 		= getMinorOceans(hexDiceRoll);
				world.numberOfSmallSeas 		= getSmallSeas(hexDiceRoll);
				world.numberOfScatteredLakes 	= getScatteredLakes(hexDiceRoll);
				world.numberOfMajorContinents 	= getMajorContinents(hexDiceRoll);
				world.numberOfMinorContinents 	= getMinorContinents(hexDiceRoll);
				world.numberOfMajorIslands 		= getMajorIslands(hexDiceRoll);
				world.numberOfArchipelagoes 	= getArchipelagoes(hexDiceRoll);
			}

		}

		else
		{
			world.numberOfMajorOceans 		= 0;
			world.numberOfMinorOceans 		= 0;
			world.numberOfSmallSeas 		= 0;
			world.numberOfScatteredLakes 	= 0;
			world.numberOfMajorContinents 	= 0;
			world.numberOfMinorContinents 	= 0;
			world.numberOfMajorIslands 		= 0;
			world.numberOfArchipelagoes 	= 0;
		}

	}

/*
	if (world.worldType == WT_ASTEROID_BELT)
	{
		std::cout << "worldType = WT_ASTEROID_BELT" << std::endl;
		std::cout << "averageOrbitalRadius = " << world.orbitalRadius << std::endl;
	}
*/
	std::cout << "Got to return world" << std::endl;
	return world;
}


//	Star design sequence
star_t starBuilder(star_t star, starSystem_t starSystem, int companionStar, float companionAInnerForbiddenZone, float companionAOuterForbiddenZone, float companionBInnerForbiddenZone, float companionBOuterForbiddenZone, float companionAOrbitalRadius, float companionBOrbitalRadius, rapidcsv::Document& starDoc, int currentCSVIndex, bool randomSystem, rapidcsv::Document& worldDoc)
{
//	Which star is this?
	star.starNumber = companionStar;
//	std::cout << "starNumber == " << (int)star.starNumber << std::endl;
//	Determine the star's age
	star.stellarAge = starSystem.systemAge;

//	Determine randomStar
	bool randomStar = (randomSystem == true || starDoc.GetCell<std::string>("spect", currentCSVIndex) == "~") ? true : false;

//	Determine the star's physical parameters
//	If a random star is to be rolled
	if (randomStar == true)
	{
//		std::cout << "randomStar is true and its if loop has been entered" << std::endl;
//		std::cout << "Star " << (int)star.starNumber << std::endl;
//		std::cout << "star.innerForbiddenZone == " << star.innerForbiddenZone << std::endl;
//		std::cout << "star.outerForbiddenZone == " << star.outerForbiddenZone << std::endl;
//		std::cout << "star.minSeparationToCompanion == " << star.minSeparationToCompanion << std::endl;
//		std::cout << "star.maxSeparationToCompanion == " << star.maxSeparationToCompanion << std::endl;

//		If the star is random, all worlds are random
//		randomWorld = true;
//		Determine the star's mass
		if (randomSystem == true || (randomSystem == false && starDoc.GetCell<std::string>("mass", currentCSVIndex) == "~"))	{star.stellarMass = stellarMassTable();}
		else																													{star.stellarMass = starDoc.GetCell<float>("mass", currentCSVIndex);}
//		std::cout << "stellarMass = " << star.stellarMass << std::endl;

//		Check if star.stellarAge == 0
//		Not sure why this is here 25/11/2020
//		if (star.stellarAge == 0) {star.stellarAge = stellarAgeTable(starSystem.gardenWorldPresent);}
//		std::cout << "stellarAge = " << star.stellarAge << std::endl;

//		Determine the star's characteristics
		star = determineStellarCharacteristics(star);

//		Determine the star's temperature
		star.stellarTemperature = calculateStellarTemperature(star.luminosityClass, star.stellarMass, star.stellarAge, star.sSpan, star.tableTemperature);
//		std::cout << "stellarTemperature = " << star.stellarTemperature << std::endl;
//		Determine the star's luminosity
		star.stellarLuminosity = (randomSystem == true) ? calculateStellarLuminosity(star.luminosityClass, star.stellarAge, star.mSpan, star.lMax, star.lMin) : starDoc.GetCell<float>("lum", currentCSVIndex);
//		std::cout << "stellarLuminosity = " << star.stellarLuminosity << std::endl;
//		If the star is a white dwarf, modify the star's mass and reset the star's starType
		if (star.luminosityClass == LC_D)
		{
			int whiteDwarfMassRoll = diceRoller(6, 2) - 2;
			star.stellarMass = (whiteDwarfMassRoll * 0.05) + 0.9 + floatRNG(-0.05, 0.05);
			star.starClassification = "D" + std::to_string(50400 / star.stellarTemperature);
		}

//		Determine the radius of the star
		if (randomSystem == true || (randomSystem == false && starDoc.GetCell<std::string>("radius", currentCSVIndex) == "~"))		{star.stellarRadius = determineStarRadius(star.luminosityClass, star.stellarLuminosity, star.stellarTemperature);}
		else																														{star.stellarRadius = starDoc.GetCell<float>("radius", currentCSVIndex);}

//		Determine the equatorial rotation velocity of the star
//		star.equatorialRotationVelocity = getEquatorialRotationVelocity(star.stellarRadius * 2, star.rotation)
//		std::cout << "\nStar " << (int)star.starNumber << " is about to exit the first randomStar if loop" << std::endl;
//		std::cout << "star.innerForbiddenZone == " << star.innerForbiddenZone << std::endl;
//		std::cout << "star.outerForbiddenZone == " << star.outerForbiddenZone << std::endl;
//		std::cout << "star.minSeparationToCompanion == " << star.minSeparationToCompanion << std::endl;
//		std::cout << "star.maxSeparationToCompanion == " << star.maxSeparationToCompanion << std::endl;

	}

//	If the star is from a .csv
	else
	{
//		randomWorld = false;
//		Assign identifiers
		std::tie(star.hipIndex, star.hygIndex, star.hdIndex, star.hrIndex, star.glieseIndex, star.properName) = getStarIDFromCSV(starDoc, currentCSVIndex);
//		Assign luminosity
//		std::cout << "\nStar physical characteristics" << std::endl;
		star.stellarLuminosity = starDoc.GetCell<double>("lum", currentCSVIndex);
//		std::cout << "star.stellarLuminosity == " << star.stellarLuminosity << std::endl;
//		Boolean parameters for completeStellarClassification
		bool massPreset 		= starDoc.GetCell<std::string>("mass", currentCSVIndex) 		== "~" ? false : true;
		bool radiusPreset 		= starDoc.GetCell<std::string>("radius", currentCSVIndex) 		== "~" ? false : true;
		bool temperaturePreset 	= starDoc.GetCell<std::string>("temperature", currentCSVIndex) 	== "~" ? false : true;
//		Determine the star's MK classification and its mass, radius, and temperature
		bool floatOrIntNumericValue;
		std::tie(star.harvardLetter, star.yerkesClassification, star.numericValue, floatOrIntNumericValue) = completeStellarClassification(starDoc.GetCell<std::string>("spect", currentCSVIndex), star.stellarLuminosity, massPreset, radiusPreset, temperaturePreset);
//		std::cout << "\ncompleteStellarClassification has just returned with these values:" << std::endl;
//		std::cout << "star.harvardLetter == " << star.harvardLetter << std::endl;
//		std::cout << "star.yerkesClassification == " << star.yerkesClassification << std::endl;
//		std::cout << "star.numericValue == " << star.numericValue << "\n" << std::endl;
//		Determine the star's physical parameters
		std::tie(star.stellarMass, star.stellarRadius, star.stellarTemperature) = extrapolateStellarParameters(currentCSVIndex, starDoc, star.harvardLetter, star.yerkesClassification, floatOrIntNumericValue, massPreset, radiusPreset, temperaturePreset, star.numericValue, star.numericValue);
//		If mass, radius, or temperature are preset
//		star.stellarMass 		= massPreset 		? starDoc.GetCell<float>("mass", currentCSVIndex) 			: star.stellarMass;
//		std::cout << "star.stellarMass == " << star.stellarMass << std::endl;
//		star.stellarRadius 		= radiusPreset 		? starDoc.GetCell<float>("radius", currentCSVIndex) 		: star.stellarRadius;
//		std::cout << "star.stellarRadius == " << star.stellarRadius << std::endl;
//		star.stellarTemperature = temperaturePreset ? starDoc.GetCell<float>("temperature", currentCSVIndex)	: star.stellarTemperature;
//		std::cout << "star.stellarTemperature == " << star.stellarTemperature << std::endl;
	}

//	Calculate the energy radiated by the star
	star.energyRadiated = (randomStar == true) ? stefanBoltzmannCalculator(star.tableTemperature) : stefanBoltzmannCalculator(star.stellarTemperature);

//	Determine the escape velocity of the star
	star.escapeVelocity = getEscapeVelocity(star.stellarMass * SOL_MASS_IN_KG, star.stellarRadius * SOL_RADIUS_IN_KM);
//	std::cout << "stellarRadius = " << star.stellarRadius << std::endl;
//	Determine the orbital zones of the star
//	Determine the star's inner limit radius
	star.innerLimitRadius = getInnerLimitRadius(star.stellarMass, star.stellarLuminosity);
//	std::cout << "innerLimitRadius = " << star.innerLimitRadius << std::endl;
//	Determine the star's outer limit radius
	star.outerLimitRadius = getOuterLimitRadius(star.stellarMass);
//	std::cout << "outerLimitRadius = " << star.outerLimitRadius << std::endl;

//	Determine the star's snow line
//	If the star is from a .csv, use the formula found in the "Solar System Regions" section of Atomic Rockets's Worldbuilding page
	star.snowLineRadius = (randomStar == true) ? getSnowLine(star.lMin) : sqrt(star.stellarLuminosity / 0.025);
//	std::cout << "snow line radius = " << star.snowLineRadius << std::endl;

/*
	25/11/2020
	This section is redundant, as starSystemBuilder determines orbital parameters
//	Determine characteristics for multiple star systems
//	If the system has one star
	if (starSystem.numberOfStars == 1)
	{
		star.orbitalEccentricity = 0;
		star.averageOrbitalRadius = 0;
		star.minSeparationToCompanion = 0;
		star.maxSeparationToCompanion = 0;
	}

//	If the system has more than one star
	else
	{
//		If generating a random star
		if (randomStar == true)
		{
			star = orbitalSeparationTable(starSystem.numberOfStars, companionStar, star, starSystem.gardenWorldPresent);
		}

//		If generating from a .csv
		else
		{
//			Check if orbital parameters are present
//			If the semi
		}
	}

//	std::cout << "innerForbiddenZone = " << star.innerForbiddenZone << std::endl;
//	std::cout << "outerForbiddenZone = " << star.outerForbiddenZone << std::endl;
*/
//	Number of planets that match this star in worldDoc
	int numberOfCSVPlanets;
//	Determine the details of the star's first gas giant
	if (randomStar == true)
	{
//		Determine the star's gas giant arrangement
		star.gasGiantArrangement = gasGiantArrangementTable();
//		std::cout << "gasGiantArrangement = " << star.gasGiantArrangement << std::endl;

//		If there is no gas giant
		if (star.gasGiantArrangement == GGA_NO_GAS_GIANT)
		{
			star.firstGasGiantOrbitalRadius = 0;
			star.firstGasGiantPresent = false;
		}

//		If there is a gas giant
		else
		{
			star.firstGasGiantOrbitalRadius = placeFirstGasGiant(star.snowLineRadius, star.gasGiantArrangement);
			star.firstGasGiantPresent = true;
		}
	}

//	If the star is generated from a .csv
	else
	{
//		Check worldDoc for any gas giants
		std::tie(star.worldArray[0].planetDBIndex, star.firstGasGiantPresent, star.gasGiantArrangement, star.firstGasGiantOrbitalRadius, star.numberOfCSVPlanets) = csv_determineGasGiantArrangement(star, worldDoc);
//		Check again with default function if GGA_NO_GAS_GIANT is returned
		if (star.gasGiantArrangement == GGA_NO_GAS_GIANT)
		{	//		Determine the star's gas giant arrangement
			star.gasGiantArrangement = gasGiantArrangementTable();
			//		std::cout << "gasGiantArrangement = " << star.gasGiantArrangement << std::endl;

			//		If there is no gas giant
			if (star.gasGiantArrangement == GGA_NO_GAS_GIANT)
			{
				star.firstGasGiantOrbitalRadius = 0;
				star.firstGasGiantPresent = false;
			}

			//		If there is a gas giant
			else
			{
				star.firstGasGiantOrbitalRadius = placeFirstGasGiant(star.snowLineRadius, star.gasGiantArrangement);
				star.firstGasGiantPresent = true;
			}
		}
	}
	std::cout << "gasGiantArrangement == " << star.gasGiantArrangement << std::endl;
	if (star.firstGasGiantPresent == true) {cout << "star.firstGasGiantPresent = TRUE" << std::endl;}
	else if (star.firstGasGiantPresent == false) {cout << "star.firstGasGiantPresent = FALSE" << std::endl;}

	std::cout << "star.firstGasGiantPresent = " << star.firstGasGiantPresent << std::endl;

//	Determine the sequence of orbital radii for the star's planetary system
//	std::cout << "\nIn two lines placePlanetaryOrbits will be entered" << std::endl;
//	std::cout << "innerLimitRadius = " << star.innerLimitRadius << std::endl;
//	std::cout << "outerLimitRadius = " << star.outerLimitRadius << std::endl;
	star = placePlanetaryOrbits(star, worldDoc, randomStar, starSystem.numberOfStars, companionAInnerForbiddenZone, companionAOuterForbiddenZone, companionBInnerForbiddenZone, companionBOuterForbiddenZone, companionAOrbitalRadius, companionBOrbitalRadius);

//	std::cout << "star.numberOfOrbits = " << star.numberOfOrbits << std::endl;



//	Populate orbital slots
//	sizeClassArray has an array of strings that categorize the world in that orbital slot
//	worldBuilder_ADVANCED is then run for each world
	star = fillOrbits(star, worldDoc, randomSystem);

/*
//	Print worlds
	if (star.numberOfOrbits != 0)
	{
		for (int index = 0; index < star.numberOfOrbits; index++)
		{
//			std::cout << "star.sizeClassArray[" << index << "] = " << star.sizeClassArray[index] << std::endl;
		}
	}
*/
//	for (int i = 0; i < star.numberOfOrbits; i++) {cout << "star.sizeClassArray[" << i << "] = " << star.sizeClassArray[i] << std::endl;}
/*	for (int i = 0; i < 7; i++)
	{
		std::cout << "star.preplacedWorldIndex[" << i << "] == " << star.preplacedWorldIndex[i] << std::endl;
	}
*/
//	Build the worlds around the star
	star.sizeClassIndex = 0;
	std::cout << "\nstar.numberOfOrbits == " << star.numberOfOrbits << "\n" << std::endl;
	for (int index = 0; index < star.numberOfOrbits; index++)
	{
		std::cout << "Worldbuilder for loop reached" << std::endl;
//		If the world is not a gas giant or empty
//		if (star.sizeClassArray[index] != WT_SMALL_GAS_GIANT && star.sizeClassArray[index] != WT_MEDIUM_GAS_GIANT && star.sizeClassArray[index] != WT_LARGE_GAS_GIANT && star.sizeClassArray[index] != SC_EMPTY_ORBIT)
//		if (star.sizeClassArray[index] == SC_ASTEROID_BELT || star.sizeClassArray[index] == SC_EMPTY_ORBIT || star.sizeClassArray[index] == SC_TERRESTRIAL_PLANET_SMALL || star.sizeClassArray[index] == SC_TERRESTRIAL_PLANET_STANDARD || star.sizeClassArray[index] == SC_TERRESTRIAL_PLANET_LARGE)
//		std::string sizeClassString = star.sizeClassArray[index];
		std::cout << "star.sizeClassArray[" << index << "] = " << star.sizeClassArray[index] << std::endl;

		if (star.sizeClassArray[index] != SC_EMPTY_ORBIT)
		{
//			Assign randomWorld
//			randomWorld is true by default, but if the current index matches a value in star.preplacedWorldIndex randomWorld is false
			bool randomWorld = true;
			if (star.numberOfCSVPlanets > 0)
			{
				for (int i = 0; i < star.numberOfCSVPlanets; i++)
				{
					if (index == star.preplacedWorldIndex[i])	{randomWorld = false; break;}
				}
			}
			std::cout << "Worldbuilder if loop reached" << std::endl;
			std::cout << "star.orbitalRadiusArray[" << index << "] == " << star.orbitalRadiusArray[index] << std::endl;
			std::cout << "randomWorld == " << randomWorld << std::endl;
//			Run worldBuilder_ADVANCED
			star.worldArray[star.sizeClassIndex] = worldBuilder_ADVANCED(star.sizeClassArray[index], star.orbitalRadiusArray[index], star, worldDoc, index/*, 0, 0, "", POM_PLANET*/, randomWorld);
			star.sizeClassIndex += 1;
		}
		std::cout << "For loop ended" << std::endl;
	}
//	std::cout << "star.sizeClassIndex = " << (int)star.sizeClassIndex << std::endl;

//	Assign star.starClassification
	if (star.harvardLetter == "D")
	{
		star.starClassification = star.harvardLetter + std::to_string(star.numericValue);
	}

	else if (star.yerkesClassification == "sd")
	{
		star.starClassification = star.yerkesClassification + star.harvardLetter + std::to_string(star.numericValue);
	}

	else
	{
		star.starClassification = star.harvardLetter + std::to_string(star.numericValue) + star.yerkesClassification;
	}


//	Return the star
	std::cout << "\nStar " << (int)star.starNumber << " is about to be returned" << std::endl;
	std::cout << "star.innerForbiddenZone == " << star.innerForbiddenZone << std::endl;
	std::cout << "star.outerForbiddenZone == " << star.outerForbiddenZone << std::endl;
	std::cout << "star.minSeparationToCompanion == " << star.minSeparationToCompanion << std::endl;
	std::cout << "star.maxSeparationToCompanion == " << star.maxSeparationToCompanion << std::endl;
	return star;
}

//	Star system design sequence
//	randomSystem checks if the system to be rolled is to be a fictional randomized system or one based off of data from HYG
//	starDoc is the .csv file containing the HYG database
//	worldDoc is the .csv file containing the planet database
//	currentCSVIndex is the .csv index value of the current system
starSystem_t starSystemBuilder(bool randomSystem, rapidcsv::Document& starDoc, int currentCSVIndex, rapidcsv::Document& worldDoc)
{
//	Initialize the star system
	starSystem_t starSystem = {0};
//	This value is temporary
	starSystem.gardenWorldPresent = false;


//	If a random star system is to be rolled
	if (randomSystem == true)
	{
//		Determine the number of stars in the system
		starSystem.numberOfStars = determineStarNumber();
//		std::cout << "numberOfStars = " << int(starSystem.numberOfStars) << std::endl;
//		Determine the orbits of the companion stars
		starSystem = companionStarOrbits(starSystem);


		starSystem.systemAge = stellarAgeTable(starSystem.gardenWorldPresent);
//		Build the system's stars
//		For each star in the system
		for (int i = 0; i < starSystem.numberOfStars; i++)
		{
//			i is passed so that the forbidden zones can use it as a counter of the current star being worked on
//			For binary systems
			if 		(i == 0 && starSystem.numberOfStars == 2) {starSystem.stars[0] = starBuilder(starSystem.stars[0], starSystem, i, starSystem.stars[1].innerForbiddenZone, starSystem.stars[1].outerForbiddenZone, 0, 0, starSystem.stars[1].averageOrbitalRadius, 0, starDoc, currentCSVIndex, randomSystem, worldDoc);}
			else if (i == 1 && starSystem.numberOfStars == 2) {starSystem.stars[1] = starBuilder(starSystem.stars[1], starSystem, i, starSystem.stars[0].innerForbiddenZone, starSystem.stars[0].outerForbiddenZone, 0, 0, starSystem.stars[0].averageOrbitalRadius, 0, starDoc, currentCSVIndex, randomSystem, worldDoc);}

//			For trinary syst, random Systems
			else if (i == 0 && starSystem.numberOfStars == 3) {starSystem.stars[0] = starBuilder(starSystem.stars[0], starSystem, i, starSystem.stars[1].innerForbiddenZone, starSystem.stars[1].outerForbiddenZone, starSystem.stars[2].innerForbiddenZone, starSystem.stars[2].outerForbiddenZone, starSystem.stars[1].averageOrbitalRadius, starSystem.stars[2].averageOrbitalRadius, starDoc, currentCSVIndex, randomSystem, worldDoc);}
			else if (i == 1 && starSystem.numberOfStars == 3) {starSystem.stars[1] = starBuilder(starSystem.stars[1], starSystem, i, starSystem.stars[0].innerForbiddenZone, starSystem.stars[0].outerForbiddenZone, starSystem.stars[2].innerForbiddenZone, starSystem.stars[2].outerForbiddenZone, starSystem.stars[0].averageOrbitalRadius, starSystem.stars[2].averageOrbitalRadius, starDoc, currentCSVIndex, randomSystem, worldDoc);}
			else if (i == 2 && starSystem.numberOfStars == 3) 				{starSystem.stars[2] = starBuilder(starSystem.stars[2], starSystem, i, starSystem.stars[0].innerForbiddenZone, starSystem.stars[0].outerForbiddenZone, starSystem.stars[1].innerForbiddenZone, starSystem.stars[1].outerForbiddenZone, starSystem.stars[0].averageOrbitalRadius, starSystem.stars[1].averageOrbitalRadius, starDoc, currentCSVIndex, randomSystem, worldDoc);}

//			For single stars
			else {starSystem.stars[i] = starBuilder(starSystem.stars[0], starSystem, i, 0, 0, 0, 0, 0, 0, starDoc, currentCSVIndex, randomSystem, worldDoc);}
			std::cout << "star " << i << " was returned successfully" << std::endl;
		}

//		std::cout << "\ncompanionStarOrbits and starBuilder have been called" << std::endl;
//		std::cout << "starSystem.stars[0].innerForbiddenZone = " << starSystem.stars[0].innerForbiddenZone << std::endl;
//		std::cout << "starSystem.stars[0].outerForbiddenZone = " << starSystem.stars[0].outerForbiddenZone << std::endl;
//		std::cout << "starSystem.stars[1].innerForbiddenZone = " << starSystem.stars[1].innerForbiddenZone << std::endl;
//		std::cout << "starSystem.stars[1].outerForbiddenZone = " << starSystem.stars[1].outerForbiddenZone << std::endl;
//		std::cout << "starSystem.stars[2].innerForbiddenZone = " << starSystem.stars[2].innerForbiddenZone << std::endl;
//		std::cout << "starSystem.stars[2].outerForbiddenZone = " << starSystem.stars[2].outerForbiddenZone << std::endl;
//		std::cout << "starSystem.stars[0].minSeparationToCompanion = " << starSystem.stars[0].minSeparationToCompanion << std::endl;
//		std::cout << "starSystem.stars[0].maxSeparationToCompanion = " << starSystem.stars[0].maxSeparationToCompanion << std::endl;
//		std::cout << "starSystem.stars[1].minSeparationToCompanion = " << starSystem.stars[1].minSeparationToCompanion << std::endl;
//		std::cout << "starSystem.stars[1].maxSeparationToCompanion = " << starSystem.stars[1].maxSeparationToCompanion << std::endl;
//		std::cout << "starSystem.stars[2].minSeparationToCompanion = " << starSystem.stars[2].minSeparationToCompanion << std::endl;
//		std::cout << "starSystem.stars[2].maxSeparationToCompanion = " << starSystem.stars[2].maxSeparationToCompanion << std::endl << std::endl;
//		Calculate stellar orbital periods
		starSystem.stars[0].stellarOrbitalPeriod = 0;

//		For multiple star systems
		if (starSystem.numberOfStars != 1)
		{
//			std::cout << "Trinary system if loop reached" << std::endl;
			starSystem.stars[1].stellarOrbitalPeriod = sqrt(pow(starSystem.stars[1].averageOrbitalRadius, 3) / (starSystem.stars[0].stellarMass + starSystem.stars[1].stellarMass));
			starSystem.stars[2].stellarOrbitalPeriod = sqrt(pow(starSystem.stars[2].averageOrbitalRadius, 3) / (starSystem.stars[0].stellarMass + starSystem.stars[1].stellarMass + starSystem.stars[2].stellarMass));
		}


	}

//	If the system is to be generated from a .csv
	else
	{
//		Determine the number of stars in the system
//		std::cout << "currentCSVIndex == " << currentCSVIndex << std::endl;
		int comp1 = starDoc.GetCell<int>("comp", currentCSVIndex);
		int comp2 = starDoc.GetCell<int>("comp", currentCSVIndex + 1);
		int comp3 = starDoc.GetCell<int>("comp", currentCSVIndex + 2);
		starSystem.numberOfStars = csv_DetermineStarCount(comp1, comp2, comp3);
//		std::cout << "starSystem.numberOfStars == " << unsigned(starSystem.numberOfStars) << std::endl;
//		The primary has no orbital period
		starSystem.stars[0].stellarOrbitalPeriod = 0;

//		If the system has two or more stars
		if (starSystem.numberOfStars > 1)
		{
//			If orbital parameters are not given
			if (starDoc.GetCell<std::string>("semiMajorAxis", currentCSVIndex + 1) == "~")
			{
				starSystem = companionStarOrbits(starSystem);
			}

//			Otherwise
			else
			{
//				For binary systems
				if (starSystem.numberOfStars == 2)
				{
//					Companion's orbital parameters
					starSystem.stars[1].orbitalEccentricity = starDoc.GetCell<float>("eccentricity", currentCSVIndex + 1);
					starSystem.stars[1].stellarOrbitalPeriod = starDoc.GetCell<float>("period", currentCSVIndex + 1);
					starSystem.stars[1].averageOrbitalRadius = starDoc.GetCell<float>("semiMajorAxis", currentCSVIndex + 1);
					starSystem.stars[1].minSeparationToCompanion = (1 - starSystem.stars[1].orbitalEccentricity) * starSystem.stars[1].averageOrbitalRadius;
					starSystem.stars[1].maxSeparationToCompanion = (1 + starSystem.stars[1].orbitalEccentricity) * starSystem.stars[1].averageOrbitalRadius;
					starSystem.stars[1].innerForbiddenZone = starSystem.stars[1].minSeparationToCompanion / 3;
					starSystem.stars[1].outerForbiddenZone = starSystem.stars[1].maxSeparationToCompanion * 3;

//					Primary's orbital parameters
					starSystem.stars[0].minSeparationToCompanion = starSystem.stars[1].minSeparationToCompanion;
					starSystem.stars[0].maxSeparationToCompanion = starSystem.stars[1].maxSeparationToCompanion;
					starSystem.stars[0].innerForbiddenZone = starSystem.stars[1].innerForbiddenZone;
					starSystem.stars[0].outerForbiddenZone = starSystem.stars[1].outerForbiddenZone;
				}

//				For trinary systems
				else
				{
//					Second companion's orbital parameters
					starSystem.stars[2].orbitalEccentricity = starDoc.GetCell<float>("eccentricity", currentCSVIndex + 2);
					starSystem.stars[2].stellarOrbitalPeriod = starDoc.GetCell<float>("period", currentCSVIndex + 2);
					starSystem.stars[2].averageOrbitalRadius = starDoc.GetCell<float>("semiMajorAxis", currentCSVIndex + 2);
					starSystem.stars[2].minSeparationToCompanion = (1 - starSystem.stars[2].orbitalEccentricity) * starSystem.stars[2].averageOrbitalRadius;
					starSystem.stars[2].maxSeparationToCompanion = (1 + starSystem.stars[2].orbitalEccentricity) * starSystem.stars[2].averageOrbitalRadius;
					starSystem.stars[2].innerForbiddenZone = starSystem.stars[2].minSeparationToCompanion / 3;
					starSystem.stars[2].outerForbiddenZone = starSystem.stars[2].maxSeparationToCompanion * 3;

//					First companion's orbital parameters
					starSystem.stars[1].orbitalEccentricity = starDoc.GetCell<float>("eccentricity", currentCSVIndex + 1);
					starSystem.stars[1].stellarOrbitalPeriod = starDoc.GetCell<float>("period", currentCSVIndex + 1);
					starSystem.stars[1].averageOrbitalRadius = starDoc.GetCell<float>("semiMajorAxis", currentCSVIndex + 1);
					starSystem.stars[1].minSeparationToCompanion = (1 - starSystem.stars[1].orbitalEccentricity) * starSystem.stars[1].averageOrbitalRadius;
					starSystem.stars[1].maxSeparationToCompanion = (1 + starSystem.stars[1].orbitalEccentricity) * starSystem.stars[1].averageOrbitalRadius;
					starSystem.stars[1].innerForbiddenZone = starSystem.stars[1].minSeparationToCompanion / 3;
					starSystem.stars[1].outerForbiddenZone = starSystem.stars[1].maxSeparationToCompanion * 3;

//					Primary's orbital parameters
					starSystem.stars[0].innerForbiddenZone = starSystem.stars[1].innerForbiddenZone;
					starSystem.stars[0].outerForbiddenZone = starSystem.stars[1].outerForbiddenZone;
				}
			}
		}

//		For single star systems
		else
		{
			starSystem.stars[0].orbitalEccentricity = 0;
			starSystem.stars[0].stellarOrbitalPeriod = 0;
			starSystem.stars[0].averageOrbitalRadius = 0;
			starSystem.stars[0].minSeparationToCompanion = 0;
			starSystem.stars[0].maxSeparationToCompanion = 0;
			starSystem.stars[0].innerForbiddenZone = 0;
			starSystem.stars[0].outerForbiddenZone = 0;
		}

//		Determine the age of the system
//		if (starDoc.GetCell<std::string>("stellarAge", currentCSVIndex) == "")	{std::cout << "stellarAge is blank" << std::endl;}
		starSystem.systemAge = (starDoc.GetCell<std::string>("stellarAge", currentCSVIndex) == "") ? stellarAgeTable(starSystem.gardenWorldPresent) : starDoc.GetCell<float>("stellarAge", currentCSVIndex);
//		std::cout << "csv's stellarAge == " << starSystem.systemAge << std::endl;

//		Build the system's stars
//		For each star in the system
		for (int i = 0; i < starSystem.numberOfStars; i++)
		{
//			i is passed so that the forbidden zones can use it as a counter of the current star being worked on
//			std::cout << "starBuilder i == " << i << std::endl;
//			For binary systems
			if 		(i == 0 && starSystem.numberOfStars == 2) {starSystem.stars[0] = starBuilder(starSystem.stars[0], starSystem, i, starSystem.stars[1].innerForbiddenZone, starSystem.stars[1].outerForbiddenZone, 0, 0, starSystem.stars[1].averageOrbitalRadius, 0, starDoc, currentCSVIndex, randomSystem, worldDoc);}
			else if (i == 1 && starSystem.numberOfStars == 2) {starSystem.stars[1] = starBuilder(starSystem.stars[1], starSystem, i, starSystem.stars[0].innerForbiddenZone, starSystem.stars[0].outerForbiddenZone, 0, 0, starSystem.stars[0].averageOrbitalRadius, 0, starDoc, currentCSVIndex, randomSystem, worldDoc);}

//			For trinary systems
			else if (i == 0 && starSystem.numberOfStars == 3) {starSystem.stars[0] = starBuilder(starSystem.stars[0], starSystem, i, starSystem.stars[1].innerForbiddenZone, starSystem.stars[1].outerForbiddenZone, starSystem.stars[2].innerForbiddenZone, starSystem.stars[2].outerForbiddenZone, starSystem.stars[1].averageOrbitalRadius, starSystem.stars[2].averageOrbitalRadius, starDoc, currentCSVIndex, randomSystem, worldDoc);}
			else if (i == 1 && starSystem.numberOfStars == 3) {starSystem.stars[1] = starBuilder(starSystem.stars[1], starSystem, i, starSystem.stars[0].innerForbiddenZone, starSystem.stars[0].outerForbiddenZone, starSystem.stars[2].innerForbiddenZone, starSystem.stars[2].outerForbiddenZone, starSystem.stars[0].averageOrbitalRadius, starSystem.stars[2].averageOrbitalRadius, starDoc, currentCSVIndex, randomSystem, worldDoc);}
			else if (i == 2 && starSystem.numberOfStars == 3) {starSystem.stars[2] = starBuilder(starSystem.stars[2], starSystem, i, starSystem.stars[0].innerForbiddenZone, starSystem.stars[0].outerForbiddenZone, starSystem.stars[1].innerForbiddenZone, starSystem.stars[1].outerForbiddenZone, starSystem.stars[0].averageOrbitalRadius, starSystem.stars[1].averageOrbitalRadius, starDoc, currentCSVIndex, randomSystem, worldDoc);}
//			For single stars
			else {starSystem.stars[i] = starBuilder(starSystem.stars[0], starSystem, i, 0, 0, 0, 0, 0, 0, starDoc, currentCSVIndex, randomSystem, worldDoc);}
		}

//		Calculate stellar orbital periods
		starSystem.stars[0].stellarOrbitalPeriod = 0;

//		For multiple star systems
		if (starSystem.numberOfStars != 1)
		{
//			std::cout << "Trinary system if loop reached" << std::endl;
			starSystem.stars[1].stellarOrbitalPeriod = sqrt(pow(starSystem.stars[1].averageOrbitalRadius, 3) / (starSystem.stars[0].stellarMass + starSystem.stars[1].stellarMass));
			starSystem.stars[2].stellarOrbitalPeriod = sqrt(pow(starSystem.stars[2].averageOrbitalRadius, 3) / (starSystem.stars[0].stellarMass + starSystem.stars[1].stellarMass + starSystem.stars[2].stellarMass));
		}

	}
	return starSystem;
}

int main()
{
//	for (int i = 0; i < 100; i++)
//	{
	std::string randomSystemString;
	std::cout << "Generate a random system or one from a .csv? ";
	std::getline(cin, randomSystemString);
	bool randomSystem = randomSystemString == "random" ? true : false;
	rapidcsv::Document worldDoc("planetDB.csv", rapidcsv::LabelParams(0, 0));
	rapidcsv::Document starDoc("out_blanks_filled.csv", rapidcsv::LabelParams(0, 0));
//	starSystem_t starSystem = starSystemBuilder(true, starDoc, 0, worldDoc);
//	Generate and print the first ten systems after Sol
	for (int i = 1; i < 4; i++)
	{
		std::cout << "\nmain i == " << i << std::endl;
		starSystem_t starSystem = starSystemBuilder(randomSystem, starDoc, i, worldDoc);
		printStarSystem(starSystem);
		std::cout << "\nFinished printStarSystem" << std::endl;
	}
//	}
//	int starID = 32263;
//	getStarData(starID);
//	runPython(2, {"multiply.py", 2, 3})
	return 0;
}
