//	This holds the main function of the GURPS Space 4e worldbuilding process
//	This follows the steps outlined in the book

//	Boost libraries
//	#include <boost/python.hpp>

//	C++ libraries
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <random>
#include <string>
#include <string.h>
#include <time.h>
#include <tuple>

//	Constant declarations
#include "declarations/constants/absorptionFactorConstants.h"
#include "declarations/constants/atmosphericPressureCategoryConstants.h"
#include "declarations/constants/gasGiantArrangementConstants.h"
#include "declarations/constants/greenhouseFactorConstants.h"
#include "declarations/constants/luminosityClassConstants.h"
#include "declarations/constants/mappingConstants.h"
#include "declarations/constants/miscConstants.h"
#include "declarations/constants/sizeClassConstants.h"
#include "declarations/constants/stringConstants.h"
#include "declarations/constants/tectonicActivityLevelConstants.h"
#include "declarations/constants/unitConversions.h"
#include "declarations/constants/universalConstants.h"
#include "declarations/constants/volcanicActivityLevelConstants.h"
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
#include "declarations/functions/exportToCSV.h"

//	World and moon design
#include "declarations/functions/absorptionFactorLookup.h"
#include "declarations/functions/alienLifeFunctions.h"
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
#include "declarations/functions/jumpPointFunctions.h"
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
char32_t seed_val;
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

star_t nameBodies(star_t& primary)
{
//	Loop through each world
	if (primary.numberOfPlanets != 0)
	{
		std::string planetLetters = "bcdefghijklmnopqrstuvwxyz";
		std::string moonDesignationArray[8] = {"i", "ii", "iii", "iv", "v", "vi", "vii", "viii"};
		int planetLetterIndex = 0;

//		Determine the star's name
		std::string starName;
		bool properNameStatus = primary.properName == "";
		std::cout << "properNameStatus == " << properNameStatus << std::endl;
		bool bayerStatus = primary.bayerDesignation == "";
		std::cout << "bayerStatus == " << bayerStatus << std::endl;
		bool flamsteedStatus = primary.flamsteedDesignation == "";
		std::cout << "flamsteedStatus == " << flamsteedStatus << std::endl;
		bool glieseStatus = primary.glieseIndex == "";
		std::cout << "glieseStatus == " << glieseStatus << std::endl;
		bool hdStatus = primary.hdIndex == 0;
		std::cout << "hdStatus == " << hdStatus << std::endl;
		bool hipStatus = primary.hipIndex == 0;
		std::cout << "hipStatus == " << hipStatus << std::endl;
		if (!hipStatus && hdStatus && glieseStatus && flamsteedStatus && bayerStatus && properNameStatus)				{starName = "HIP " + std::to_string(primary.hipIndex);}
		else if (!hdStatus && glieseStatus && flamsteedStatus && bayerStatus && properNameStatus)				{starName = "HD " + std::to_string(primary.hdIndex);}
		else if (!glieseStatus && flamsteedStatus && bayerStatus && properNameStatus)			{starName = primary.glieseIndex;}
		else if (!flamsteedStatus && bayerStatus && properNameStatus){starName = primary.flamsteedDesignation;}
		else if (!bayerStatus && properNameStatus)	{starName = primary.bayerDesignation;}
		else if (!properNameStatus)				{starName = primary.properName;}
		std::cout << "starName == " << starName << std::endl;
//		Loop backwards (outwards from the primary)
		for (int i = primary.numberOfPlanets - 1; i > -1; i--)
		{
//			Determine what kind of world the planet is
			bool worldIsTerrestrial = !(primary.worldArray[i].worldType == WT_ASTEROID_BELT || primary.worldArray[i].worldType == WT_SMALL_GAS_GIANT || primary.worldArray[i].worldType == WT_MEDIUM_GAS_GIANT || primary.worldArray[i].worldType == WT_LARGE_GAS_GIANT);
			bool worldIsGasGiant = (primary.worldArray[i].worldType == WT_SMALL_GAS_GIANT || primary.worldArray[i].worldType == WT_MEDIUM_GAS_GIANT || primary.worldArray[i].worldType == WT_LARGE_GAS_GIANT);
			bool worldIsAsteroidBelt = (primary.worldArray[i].worldType == WT_ASTEROID_BELT);

//			If the world is terrestrial or a gas giant
			if (!worldIsAsteroidBelt)
			{
				int moonLetterIndex = 0;
				primary.worldArray[i].planetName = (starName + " " + planetLetters[planetLetterIndex]);
				int numberOfMoons = worldIsGasGiant ? primary.worldArray[i].secondFamilyMajorMoons : primary.worldArray[i].numberOfMajorMoons;
				if (numberOfMoons != 0)
				{
					for (int j = numberOfMoons - 1; j > -1; j--)
					{
						primary.worldArray[i].majorMoonArray[j].moonName = primary.worldArray[i].planetName + " " + moonDesignationArray[moonLetterIndex];
						moonLetterIndex++;
					}
				}
				planetLetterIndex++;
			}

			else
			{
				primary.worldArray[i].planetName = "";
			}
		}
	}

	return primary;
}

//	No confirmed exomoons
moon_t moonBuilder(star_t& primary, moon_t& moon, world_t& planet)
{
	std::cout << "\nEntered moonBuilder" << std::endl;
//	Calculate blackbody temperature
	moon.blackbodyTemperature = calculateBlackbodyTemperature_ADVANCED(primary.stellarLuminosity, moon.orbitalRadius);
//	std::cout << "moon.blackbodyTemperature == " << moon.blackbodyTemperature << std::endl;
//	Determine world type
	if (planet.sizeClass == SC_SMALL_GAS_GIANT || planet.sizeClass == SC_MEDIUM_GAS_GIANT || planet.sizeClass == SC_LARGE_GAS_GIANT)
	{
		moon.worldType = determineWorldType_ADVANCED(moon.sizeClass, moon.blackbodyTemperature, 2, primary.stellarMass, primary.stellarAge, planet.gasGiantTinySulfurPresent);
	}
	else
	{
		moon.worldType = determineWorldType_ADVANCED(moon.sizeClass, moon.blackbodyTemperature, 1, primary.stellarMass, primary.stellarAge, planet.gasGiantTinySulfurPresent);
	}

//	std::cout << "moon.worldType == " << WT_S_LOOKUP_TABLE[moon.worldType] << std::endl;

//	Calculate the world's atmospheric mass (as a proportion of Earth's atmospheric mass)
	moon.atmosphereMass = atmosphereMassGenerator(moon.worldType);
//	std::cout << "moon.atmosphereMass == " << moon.atmosphereMass << std::endl;
//	Determine the atmosphere's composition
	moon.worldAtmosphereComposition = atmosphereComposition(moon.worldType);
//	Determine the world's Hydrographic coverage
	moon.hydrographicCoverage = hydrographicCoverageCalculator(moon.worldType);
//	std::cout << "moon.hydrographicCoverage == " << moon.hydrographicCoverage << std::endl;
//	Determine the world's greenhouse factor
	moon.greenhouseFactor = greenhouseFactorLookup(moon.worldType, moon.hydrographicCoverage);
//	std::cout << "moon.greenhouseFactor == " << moon.greenhouseFactor << std::endl;
//	Determine the world's absorption factor
	moon.absorptionFactor = absorptionFactorLookup(moon.worldType, moon.hydrographicCoverage);
//	std::cout << "moon.absorptionFactor == " << moon.absorptionFactor << std::endl;
//	Determine the world's blackbody correction
	moon.blackbodyCorrection = blackbodyCorrectionCalculator(moon.absorptionFactor, moon.greenhouseFactor, moon.atmosphereMass);
//	std::cout << "moon.blackbodyCorrection == " << moon.blackbodyCorrection << std::endl;
//	Determine the world's average surface temperature
	moon.surfaceTemperature = averageSurfaceTemperature_ADVANCED(moon.blackbodyTemperature, moon.blackbodyCorrection);
//	std::cout << "moon.surfaceTemperature == " << moon.surfaceTemperature << std::endl;

//	Step 29: World Sizes
//	Determine the world's density (as a proportion of Earth's density)
	moon.worldDensity = worldDensityTable(moon.worldType);
//	std::cout << "moon.worldDensity == " << moon.worldDensity << std::endl;
//	Determine the world's diameter
	moon.worldDiameter = worldDiameterCalculator(moon.blackbodyTemperature, moon.worldDensity, moon.worldType);
//	std::cout << "moon.worldDiameter == " << moon.worldDiameter << std::endl;
//	Calculate surface area
	tie(moon.totalSurfaceArea, moon.liquidSurfaceArea, moon.landSurfaceArea) = getSurfaceArea(moon.worldDiameter, moon.hydrographicCoverage);
//	std::cout << "moon.totalSurfaceArea == " << moon.totalSurfaceArea << std::endl;
//	std::cout << "moon.liquidSurfaceArea == " << moon.liquidSurfaceArea << std::endl;
//	std::cout << "moon.landSurfaceArea == " << moon.landSurfaceArea << std::endl;
//	Determine the world's surface gravity
	moon.surfaceGravity = surfaceGravityCalculator(moon.worldDensity, moon.worldDiameter);
//	std::cout << "moon.surfaceGravity == " << moon.surfaceGravity << std::endl;
//	Determine the world's atmospheric pressure
	moon.atmosphericPressure = atmosphericPressureCalculator(moon.atmosphereMass, moon.surfaceGravity, moon.worldType);
//	std::cout << "moon.atmosphericPressure == " << moon.atmosphericPressure << std::endl;
//	Determine the world's mass
	moon.worldMass = worldMassCalculator(moon.worldDensity, moon.worldDiameter);
//	std::cout << "moon.worldMass == " << moon.worldMass << std::endl;
//	Determine the planet's orbital eccentricity
	moon.orbitalEccentricity = calculatePlanetaryOrbitalEccentricity(moon.worldType, primary.gasGiantArrangement, primary.snowLineRadius, moon.orbitalRadius, primary.innerLimitRadius);
//	std::cout << "moon.orbitalEccentricity == " << moon.orbitalEccentricity << std::endl;
//	Determine the minimum separation from the primary
	moon.minimumSeparation = calculatePlanetPrimaryMinimumSeparation(moon.orbitalRadius, moon.orbitalEccentricity);
//	std::cout << "moon.minimumSeparation == " << moon.minimumSeparation << std::endl;
//	Determine the world's escape velocity
	moon.escapeVelocity = getEscapeVelocity(moon.worldMass * EARTH_MASS_IN_KG, (moon.worldDiameter / 2) * (EARTH_RADIUS_IN_KM * KM_TO_M));
//	std::cout << "moon.escapeVelocity == " << moon.escapeVelocity << std::endl;
//	Determine the maximum separation from the primary
	moon.maximumSeparation = calculatePlanetPrimaryMaximumSeparation(moon.orbitalRadius, moon.orbitalEccentricity);
//	std::cout << "moon.maximumSeparation == " << moon.maximumSeparation << std::endl;
	moon.tidalForceOnSatelliteByPlanet = calculateTidalForceOnSatelliteByPlanet(moon.worldMass, moon.worldDiameter, moon.orbitalRadius, planet.worldDiameter);
//	std::cout << "moon.tidalForceOnSatelliteByPlanet == " << moon.tidalForceOnSatelliteByPlanet << std::endl;

	moon.orbitalPeriod = calculateSatelliteOrbitalPeriod(moon.orbitalRadius, planet.worldDiameter, moon.worldMass);
//	std::cout << "moon.orbitalPeriod == " << moon.orbitalPeriod << std::endl;

//	Calculate the total tidal effect on the moon
	moon.totalTidalEffect = calculateTotalTidalEffect(0, 0, moon.tidalForceOnSatelliteByPlanet, primary.stellarAge, moon.worldMass);
//	std::cout << "moon.totalTidalEffect == " << moon.totalTidalEffect << std::endl;
//	Determine if the world is tidal locked
	moon.tidalLockedOrNot = (moon.totalTidalEffect >= 50) ? true : false;
//	std::cout << "moon.tidalLockedOrNot == " << moon.tidalLockedOrNot << std::endl;
//	Calculate the world's sidereal rotation in standard hours
	moon.rotationPeriod = calculateRotationPeriod(moon.totalTidalEffect, moon.orbitalPeriod, moon.worldType, moon.tidalLockedOrNot);
//	std::cout << "moon.rotationPeriod == " << moon.rotationPeriod << std::endl;
//	Determine if the world has a retrograde rotation
	moon.retrogradeOrNot = checkForRetrogradeRotation(POM_MOON);
//	std::cout << "moon.retrogradeOrNot == " << moon.retrogradeOrNot << std::endl;
	moon.equatorialRotationVelocity = getEquatorialRotationVelocity(moon.worldDiameter, moon.rotationPeriod);
//	std::cout << "moon.equatorialRotationVelocity == " << moon.equatorialRotationVelocity << std::endl;
	moon.apparentDayLength = determineLocalCalendar(moon.rotationPeriod, moon.retrogradeOrNot, POM_MOON, moon.orbitalPeriod, CALO_DAY_LENGTH, planet.orbitalPeriod);
//	std::cout << "moon.apparentDayLength == " << moon.apparentDayLength << std::endl;
	moon.apparentSatelliteOrbitalCycle = determineLocalCalendar(moon.rotationPeriod, moon.retrogradeOrNot, POM_MOON, moon.orbitalPeriod, CALO_ORBITAL_CYCLE, planet.orbitalPeriod);
//	std::cout << "moon.apparentSatelliteOrbitalCycle == " << moon.apparentSatelliteOrbitalCycle << std::endl;
//	Calculate the world's axial tilt
	moon.axialTilt = calculateAxialTilt();
//	std::cout << "moon.axialTilt == " << moon.axialTilt << std::endl;
//	Determine the world's volcanic activity
//	NOTE: This function takes two additional arguments for moons, but I wanted to test what happens if nothing is passed
	moon.volcanicActivityLevel = volcanicActivityTable(moon.worldType, moon.surfaceGravity, primary.stellarAge, POM_MOON, 0, planet.worldType);
//	std::cout << "moon.volcanicActivityLevel == " << moon.volcanicActivityLevel << std::endl;
//	Determine the effect the world's volcanic activity has on the world's atmosphere
	moon.worldAtmosphereComposition = volcanicActivityEffectOnGardenWorld(moon.volcanicActivityLevel, moon.worldType, moon.worldAtmosphereComposition);
//	Determine the world's tectonic activity
//	std::cout << "moon.habitabilityModifier == " << moon.habitabilityModifier << std::endl;
//	std::cout << "moon.resourceValueModifier == " << moon.resourceValueModifier << std::endl;
//	Determine the world's minimum molecular weight retained
	moon.minimumMolecularWeightRetained = minimumMolecularWeightRetainedCalculator(moon.blackbodyTemperature, moon.worldDiameter, moon.worldDensity, moon.worldType);
//	std::cout << "moon.minimumMolecularWeightRetained == " << moon.minimumMolecularWeightRetained << std::endl;
	moon.atmosphericPressureCategory = atmosphericPressureCategoriesTable(moon.atmosphericPressure);
//	std::cout << "moon.atmosphericPressureCategory == " << moon.atmosphericPressureCategory << std::endl;
//	If the world is tide locked
	tie(moon.resonantOrNot, moon.apparentDayLength) = resonantWorldEffects(moon.orbitalEccentricity, moon.tidalLockedOrNot, moon.orbitalPeriod, moon.apparentDayLength);
	char oldAtmosphericPressureCategory = moon.atmosphericPressureCategory;
	tie(moon.atmosphericPressure, moon.atmosphericPressureCategory, moon.hydrographicCoverage, moon.dayFaceAverageTemperature, moon.nightFaceAverageTemperature) = tideLockedWorldEffects(moon.tidalLockedOrNot, moon.surfaceTemperature, moon.atmosphericPressureCategory, moon.atmosphericPressure, moon.atmosphericMass, moon.surfaceGravity, moon.worldType, moon.hydrographicCoverage);
	moon.atmosphericPressure = oldAtmosphericPressureCategory != moon.atmosphericPressureCategory ? getNewAtmosphericPressure(moon.atmosphericPressureCategory) : moon.atmosphericPressureCategory;
	//	std::cout << "moon.atmosphericPressure == " << moon.atmosphericPressure << std::endl;
	//	std::cout << "moon.atmosphericPressureCategory == " << moon.atmosphericPressureCategory << std::endl;
	//	std::cout << "moon.hydrographicCoverage == " << moon.hydrographicCoverage << std::endl;

//	Check if the world is in a resonant orbit
//	If so, determine the effects that has on the world
	moon.tectonicActivityLevel = getTectonicActivity(moon.worldType, moon.volcanicActivityLevel, moon.hydrographicCoverage, POM_MOON, 0);
	//	std::cout << "moon.tectonicActivityLevel == " << moon.tectonicActivityLevel << std::endl;
	//	Determine the world's resource value modifier
	moon.resourceValueModifier = resourceDeterminator(moon.worldType);
	//	Determine the world's habitability modifier
	std::tie(moon.habitabilityModifier, moon.climateType, moon.breathable) = habitabilityModifiersTable(moon.worldType, moon.atmosphereMass, moon.hydrographicCoverage, moon.atmosphericPressure, moon.surfaceTemperature, moon.worldAtmosphereComposition);
	std::cout << "moon.habitabilityModifier == " << moon.habitabilityModifier << std::endl;
	//	Determine the effect of tectonic and volcanic activity on the world's habitability and resources
	int newResourceValueModifier = 0;
	int newHabitabilityModifier = 0;
	tie(newHabitabilityModifier, newResourceValueModifier) = effectsOfGeologicActivity(moon.volcanicActivityLevel, moon.tectonicActivityLevel, moon.habitabilityModifier, moon.resourceValueModifier);
	std::cout << "newHabitabilityModifier == " << newHabitabilityModifier << std::endl;
	moon.habitabilityModifier += newHabitabilityModifier;
	std::cout << "moon.habitabilityModifier == " << moon.habitabilityModifier << std::endl;
	moon.resourceValueModifier += newResourceValueModifier;
	moon.habitabilityModifier = moon.habitabilityModifier < -2 ? -2 : moon.habitabilityModifier;
	moon.resourceValueModifier = moon.resourceValueModifier < -5 ? -5 : moon.resourceValueModifier;
	moon.resourceValueModifier = moon.resourceValueModifier > 5 ? 5 : moon.resourceValueModifier;
//	std::cout << "moon.resonantOrNot == " << moon.resonantOrNot << std::endl;
//	std::cout << "moon.apparentDayLength == " << moon.apparentDayLength << std::endl;
//	Get the moon's magnetic field strength
	moon.magneticFieldStrength = getMagneticField(moon.worldMass, moon.worldDensity, moon.rotationPeriod, primary.stellarAge, moon.worldType);
//	std::cout << "moon.magneticFieldStrength == " << moon.magneticFieldStrength << std::endl;

//	Mapping the moon
//	Get the number of hexes per moon triangle side
	moon.hexesPerSide = getHexesPerSide(moon.worldDiameter);
//	std::cout << "moon.hexesPerSide == " << moon.hexesPerSide << std::endl;
//	Get the total number of hexes on the moon
	moon.totalHexes = getTotalHexCount(moon.hexesPerSide);
//	std::cout << "moon.totalHexes == " << moon.totalHexes << std::endl;
//	Get the number of tectonic plates
	moon.tectonicPlateCount = getTectonicPlateCount(moon.worldDiameter, moon.hydrographicCoverage, moon.worldType);
	std::cout << "moon.tectonicPlateCount == " << int(moon.tectonicPlateCount) << std::endl;
	//			Describe the tectonic plates
/*	int remainingHexes = moon.totalHexes;
	bool lastPlate = false;
	for (int i = 0; i < moon.tectonicPlateCount; i++)
	{
		lastPlate = (i == moon.tectonicPlateCount - 1) ? true : false;
		moon.tectonicPlateArray[i].tectonicPlateSize = getTectonicPlateSize(floor(moon.totalHexes / moon.tectonicPlateCount), (moon.tectonicPlateCount / 2), remainingHexes, lastPlate);
		remainingHexes -= moon.tectonicPlateArray[i].tectonicPlateSize;
		std::cout << "moon.tectonicPlateArray[" << i << "].tectonicPlateSize == " << int(moon.tectonicPlateArray[i].tectonicPlateSize) << std::endl;
		moon.tectonicPlateArray[i].tectonicPlateMovementType = getTectonicPlateMovementType();
		std::cout << "moon.tectonicPlateArray[" << i << "].tectonicPlateMovementType == "<< int(moon.tectonicPlateArray[i].tectonicPlateMovementType) << std::endl;
	}
	*/
//	Get the number of water hexes
	moon.waterHexCount = getWaterHexCount(moon.totalHexes, moon.hydrographicCoverage);
//	std::cout << "moon.waterHexCount == " << moon.waterHexCount << std::endl;
//	Get the number of land hexes
	moon.landHexCount = getLandHexCount(moon.totalHexes, moon.waterHexCount);
//	std::cout << "moon.landHexCount == " << moon.landHexCount << std::endl;
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

	moon.nativeEcosphere = getNativeEcosphere(moon.worldType, primary.stellarAge, diceRoller(6, 2), moon.hydrographicCoverage);

	std::cout << "Moon is about to be returned" << std::endl;
	return moon;

}

//	Advanced world design sequence
//	This function applies only to terrestrial worlds
//	21/11/2020: Modified to add .csv support
world_t worldBuilder_ADVANCED(world_t& world, char sizeClass, float averageOrbitalRadius, star_t& primary, rapidcsv::Document& worldDoc, int worldArrayIndex, bool randomWorld)
{
//	Initialize world
//	world_t world = primary.worldArray[worldArrayIndex];
//	world.planetDBIndex = randomWorld ? 0 : world.planetDBIndex;
/*	if (sizeClass == SC_ASTEROID_BELT)
	{
		std::cout << "sizeClass = SC_ASTEROID_BELT" << std::endl;
		std::cout << "averageOrbitalRadius = " << averageOrbitalRadius << std::endl;
	}
*/
	world.randomWorld = randomWorld;
	std::cout << "\nEntered worldBuilder_ADVANCED" << std::endl;
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

	else
	{
//		World is present
		world.emptyOrNot == false;
//		Calculate blackbody temperature
		std::cout << "Got to blackbody temperature" << std::endl;
//		world.blackbodyTemperature = calculateBlackbodyTemperature_ADVANCED(primary.stellarLuminosity, world.orbitalRadius);
//		Determine world type
		world.worldType = determineWorldType_ADVANCED(sizeClass, world.blackbodyTemperature, 0, primary.stellarMass, primary.stellarAge, false);
		bool worldIsTerrestrial = !(world.worldType == WT_ASTEROID_BELT || world.worldType == WT_SMALL_GAS_GIANT || world.worldType == WT_MEDIUM_GAS_GIANT || world.worldType == WT_LARGE_GAS_GIANT);
		bool worldIsGasGiant = (world.worldType == WT_SMALL_GAS_GIANT || world.worldType == WT_MEDIUM_GAS_GIANT || world.worldType == WT_LARGE_GAS_GIANT);
		bool worldIsAsteroidBelt = (world.worldType == WT_ASTEROID_BELT);

		std::cout << "world.worldType == " << WT_S_LOOKUP_TABLE[world.worldType] << std::endl;
		std::cout << "world.planetDBIndex == " << world.planetDBIndex << std::endl;

		std::cout << "worldType = " << world.worldType << std::endl;
		std::cout << "Got to worldType" << std::endl;
//		Place major moons

//		Step 26: Atmosphere
//		Calculate the world's atmospheric mass (as a proportion of Earth's atmospheric mass)
		world.atmosphereMass = worldIsTerrestrial ? atmosphereMassGenerator(world.worldType) : 0;
		std::cout << "Got to atmosphereMass" << std::endl;
//		Determine the atmosphere's composition
		world.worldAtmosphereComposition = atmosphereComposition(world.worldType);
		std::cout << "Got to worldAtmosphereComposition" << std::endl;

//		Step 27: Hydrographic Coverage
//		Determine the world's Hydrographic coverage
//		Even an ocean world can have no water if it is tidal locked
		world.hydrographicCoverage = worldIsTerrestrial ? hydrographicCoverageCalculator(world.worldType) : 0;
		std::cout << "world.hydrographicCoverage == " << world.hydrographicCoverage << std::endl;
		std::cout << "Got to worldAtmosphereComposition" << std::endl;

//		Step 28: Climate
//		Determine the world's greenhouse factor
		world.greenhouseFactor = worldIsTerrestrial ? greenhouseFactorLookup(world.worldType, world.hydrographicCoverage) : 0;
		std::cout << "Got to greenhouseFactor" << std::endl;
//		Determine the world's absorption factor
		world.absorptionFactor = worldIsTerrestrial ? absorptionFactorLookup(world.worldType, world.hydrographicCoverage) : 0;
		std::cout << "Got to absorptionFactor" << std::endl;
//		Determine the world's blackbody correction
		world.blackbodyCorrection = worldIsTerrestrial ? blackbodyCorrectionCalculator(world.absorptionFactor, world.greenhouseFactor, world.atmosphereMass) : 0;
		std::cout << "Got to blackbodyCorrection" << std::endl;
//		Determine the world's average surface temperature
		world.surfaceTemperature = worldIsTerrestrial ? averageSurfaceTemperature_ADVANCED(world.blackbodyTemperature, world.blackbodyCorrection) : 0;
		std::cout << "Got to surfaceTemperature" << std::endl;

//		Step 29: World Sizes
//		Determine the world's mass, density, and diameter

		if (!worldIsAsteroidBelt)
		{
	//		If the mass is not provided
			if (randomWorld == true || worldDoc.GetCell<std::string>("pl_bmasse", world.planetDBIndex) == "~")
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
						if (worldIsGasGiant)
						{
							world.worldDensity 	= getGasGiantDensity(world.worldType);
							world.worldMass 	= getGasGiantMass(world.worldType);
							world.worldDiameter = getGasGiantDiameter(world.worldMass, world.worldDensity);
						}

						else
						{
							world.worldDensity 	= worldDensityTable(world.worldType);
							world.worldDiameter = worldDiameterCalculator(world.blackbodyTemperature, world.worldDensity, world.worldType);
							world.worldMass 	= worldMassCalculator(world.worldDensity, world.worldDiameter);
						}
					}

	//				If the radius is provided
					else
					{
						std::cout << "Radius is provided" << std::endl;
						world.worldDiameter = worldDoc.GetCell<float>("pl_rade", world.planetDBIndex) * 2;
						world.worldDensity 	= worldIsGasGiant ? getGasGiantDensity(world.worldType) 						: worldDensityTable(world.worldType);
						world.worldMass 	= worldMassCalculator(world.worldDensity, world.worldDiameter);
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
						world.worldDensity 	= worldDoc.GetCell<float>("pl_dens", world.planetDBIndex) / EARTH_DENSITY_IN_GRAMS_PER_CUBIC_CM;
						world.worldDiameter = worldIsGasGiant ? getGasGiantDensity(world.worldType) : worldDensityTable(world.worldType);
						world.worldMass 	= worldMassCalculator(world.worldDensity, world.worldDiameter);
					}

	//				If the radius is provided
					else
					{
						std::cout << "Radius is provided" << std::endl;
						world.worldDiameter = worldDoc.GetCell<float>("pl_rade", world.planetDBIndex) * 2;
						world.worldDensity 	= worldDoc.GetCell<float>("pl_dens", world.planetDBIndex) / EARTH_DENSITY_IN_GRAMS_PER_CUBIC_CM;
						world.worldMass 	= worldMassCalculator(world.worldDensity, world.worldDiameter);
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
						world.worldMass 	= worldDoc.GetCell<float>("pl_bmasse", world.planetDBIndex);
						world.worldDensity 	= worldIsGasGiant ? getGasGiantDensity(world.worldType) : worldDensityTable(world.worldType);
						world.worldDiameter = worldIsGasGiant ? getGasGiantDiameter(world.worldMass, world.worldDensity) : worldDiameterCalculator(world.blackbodyTemperature, world.worldDensity, world.worldType);
					}

	//				If the radius is provided
					else
					{
						std::cout << "Radius is provided" << std::endl;
						world.worldMass 	= worldDoc.GetCell<float>("pl_bmasse", world.planetDBIndex);
						world.worldDiameter = worldDoc.GetCell<float>("pl_rade", world.planetDBIndex) * 2;
						world.worldDensity 	= world.worldMass / std::pow(world.worldDiameter, 3);
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
						world.worldDensity 	= worldDoc.GetCell<float>("pl_dens", world.planetDBIndex) / EARTH_DENSITY_IN_GRAMS_PER_CUBIC_CM;
						world.worldMass 	= worldDoc.GetCell<float>("pl_bmasse", world.planetDBIndex);
						world.worldDiameter = std::cbrt(world.worldMass / world.worldDensity);
					}

	//				If the radius is provided
					else
					{
						std::cout << "Radius is provided" << std::endl;
						world.worldDiameter = worldDoc.GetCell<float>("pl_rade", world.planetDBIndex) * 2;
						world.worldDensity 	= worldDoc.GetCell<float>("pl_dens", world.planetDBIndex) / EARTH_DENSITY_IN_GRAMS_PER_CUBIC_CM;
						world.worldMass 	= worldDoc.GetCell<float>("pl_bmasse", world.planetDBIndex);
					}
				}
			}
		}

		else
		{
			world.worldDensity 	= 0;
			world.worldMass 	= 0;
			world.worldDiameter = 0;
		}

		std::cout << "world.worldMass == " << world.worldMass << std::endl;
		std::cout << "Got to worldDiameter" << std::endl;
//		Calculate surface area
		tie(world.totalSurfaceArea, world.liquidSurfaceArea, world.landSurfaceArea) = worldIsTerrestrial ? getSurfaceArea(world.worldDiameter, world.hydrographicCoverage) : make_tuple(float(0), float(0), float(0));
//		Determine the world's surface gravity
		world.surfaceGravity = worldIsAsteroidBelt ? 0 : surfaceGravityCalculator(world.worldDensity, world.worldDiameter);
		std::cout << "Got to surfaceGravity" << std::endl;
//		Determine the world's atmospheric pressure
		world.atmosphericPressure = worldIsTerrestrial ? atmosphericPressureCalculator(world.atmosphereMass, world.surfaceGravity, world.worldType) : 0;

//		Step 30: Dynamic Parameters
		world.orbitalPeriod = (randomWorld == true || worldDoc.GetCell<std::string>("pl_orbper", world.planetDBIndex) == "~") ? calculatePlanetaryOrbitalPeriod(world.orbitalRadius, primary.stellarMass, world.worldMass) : worldDoc.GetCell<float>("pl_orbper", world.planetDBIndex);
		std::cout << "Got to orbitalPeriod" << std::endl;
//		Determine the planet's orbital eccentricity
		world.orbitalEccentricity = (randomWorld == true || worldDoc.GetCell<std::string>("pl_orbeccen", world.planetDBIndex) == "~") ? calculatePlanetaryOrbitalEccentricity(world.worldType, primary.gasGiantArrangement, primary.snowLineRadius, world.orbitalRadius, primary.innerLimitRadius) : worldDoc.GetCell<float>("pl_orbeccen", world.planetDBIndex);
		std::cout << "Got to orbitalEccentricity" << std::endl;
//		Determine the minimum separation from the primary
		world.minimumSeparation = calculatePlanetPrimaryMinimumSeparation(world.orbitalRadius, world.orbitalEccentricity);
		std::cout << "Got to minimumSeparation" << std::endl;
//		Determine the maximum separation from the primary
		world.maximumSeparation = calculatePlanetPrimaryMaximumSeparation(world.orbitalRadius, world.orbitalEccentricity);
		std::cout << "Got to maximumSeparation" << std::endl;
//		Determine the world's escape velocity
		world.escapeVelocity = worldIsAsteroidBelt ? 0 : getEscapeVelocity(world.worldMass * EARTH_MASS_IN_KG, (world.worldDiameter / 2) * (EARTH_RADIUS_IN_KM * KM_TO_M));

		world.numberOfMajorMoons = worldIsTerrestrial ? getTerrestrialMajorMoons(world.orbitalRadius, world.worldType) : 0;
		world.numberOfMajorMoons = (worldIsTerrestrial && (world.numberOfMajorMoons <= 0)) ? 0 : world.numberOfMajorMoons;
		std::cout << "Got to numberOfMajorMoons" << std::endl;
//		Place moonlets
		world.terrestrialMoonlet = worldIsTerrestrial ? getTerrestrialMoonlets(world.orbitalRadius, world.worldType) : 0;
		std::cout << "Got to terrestrialMoonlet" << std::endl;

		world.firstFamilyMoonlets 	 = worldIsGasGiant ? getFirstFamily(world.orbitalRadius)	 : 0;
		world.secondFamilyMajorMoons = worldIsGasGiant ? getSecondFamily(world.orbitalRadius) 	 : 0;
		world.thirdFamilyMoonlets 	 = worldIsGasGiant ? getThirdFamily(world.orbitalRadius)	 : 0;

		int moonNumberCondition = worldIsTerrestrial ? world.numberOfMajorMoons : world.secondFamilyMajorMoons;
//		Generate major moons
		if (!worldIsAsteroidBelt && (world.numberOfMajorMoons != 0 || world.secondFamilyMajorMoons != 0))
		{
			for (int i = 0; i < moonNumberCondition; i++)
			{
//				Set to true if the orbit is invalid
//				This prevents moonBuilder from being rerun constantly
//				bool breakFlag = false;
//				Determine the size of the moon
				world.majorMoonArray[i].moonSizeClass = moonSizeTable();
//				Determine the orbital radius of the moon
				int moonFamily = worldIsGasGiant ? 2 : 0;
				world.majorMoonArray[i].orbitalRadius = placeMoonOrbits(world.worldDiameter, world.majorMoonArray[i].moonSizeClass, moonFamily);
//				Check if any of the moons orbit within 5 planetary diameters of each other
//				For any moon but the first
//				if (breakFlag == true)	{break;}
//				Determine the moon's sizeClass
				if (((worldIsTerrestrial && !(sizeClass == SC_TERRESTRIAL_PLANET_LARGE)) && world.majorMoonArray[i].moonSizeClass < -1) || ((worldIsGasGiant || (sizeClass == SC_TERRESTRIAL_PLANET_LARGE)) && world.majorMoonArray[i].moonSizeClass == -3)) {world.majorMoonArray[i].sizeClass = SC_TERRESTRIAL_PLANET_TINY;}
				else if ((sizeClass == SC_TERRESTRIAL_PLANET_STANDARD && world.majorMoonArray[i].moonSizeClass == -1) || ((worldIsGasGiant || (sizeClass == SC_TERRESTRIAL_PLANET_LARGE)) && world.majorMoonArray[i].moonSizeClass == -2)) {world.majorMoonArray[i].sizeClass = SC_TERRESTRIAL_PLANET_SMALL;}
				else {world.majorMoonArray[i].sizeClass = SC_TERRESTRIAL_PLANET_STANDARD;}

//				Run worldBuilder_ADVANCED for each moon
				world.majorMoonArray[i] = moonBuilder(primary, world.majorMoonArray[i], world);
				if (i != 0)
				{
					//					Iterate through all previous moons
					for (int j = 0; j < i; j++)
					{
						//						If the distance between moon i and any of the previous moons is less than 5 times the planet's diameter
						bool terrestrialCondition = abs(world.majorMoonArray[i].orbitalRadius - world.majorMoonArray[j].orbitalRadius) < (5 * world.worldDiameter);
						bool gasGiantCondition = abs(world.majorMoonArray[i].orbitalRadius - world.majorMoonArray[j].orbitalRadius) < world.worldDiameter;
						if (!(worldIsGasGiant && gasGiantCondition) != !(worldIsTerrestrial && terrestrialCondition))
						{
							//							std::cout << "majorMoonArray[" << i << "].orbital radius = " << world.majorMoonArray[i].orbitalRadius << std::endl;
							//							std::cout << "majorMoonArray[" << j << "].orbital radius = " << world.majorMoonArray[j].orbitalRadius << std::endl;
							//							std::cout << " 5 * planetDiameter = " << 5 * world.worldDiameter << std::endl;
							//							std::cout << "i - j = " << world.majorMoonArray[i].orbitalRadius - world.majorMoonArray[j].orbitalRadius << std::endl;
							//							Decrement by one and repeat
							i--;
//							breakFlag = true;
//							break;
						}
					}
				}
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
		world.totalTidalEffect = worldIsAsteroidBelt ? 0 : calculateTotalTidalEffect(world.tidalForceOnPlanetBySatellite, world.tidalForceOnPlanetByPrimary, world.tidalForceOnSatelliteByPlanet, primary.stellarAge, world.worldMass);
		std::cout << "Got to totalTidalEffect" << std::endl;
//		Determine if the world is tidal locked
		world.tidalLockedOrNot = (world.totalTidalEffect >= 50) ? true : false;
		std::cout << "Got to tidalLockedOrNot" << std::endl;

//		Calculate the world's sidereal rotation in standard hours
		world.rotationPeriod = worldIsAsteroidBelt ? 0 : calculateRotationPeriod(world.totalTidalEffect, world.orbitalPeriod, world.worldType, world.tidalLockedOrNot);
		std::cout << "Got to rotationPeriod" << std::endl;
//		Determine if the world has a retrograde rotation
		world.retrogradeOrNot = checkForRetrogradeRotation(POM_PLANET);
		std::cout << "Got to retrogradeOrNot" << std::endl;
		world.equatorialRotationVelocity = worldIsAsteroidBelt ? 0 : getEquatorialRotationVelocity(world.worldDiameter, world.rotationPeriod);
		world.surfaceIrradiance = solarPowerAtDistance(primary.stellarRadius, world.orbitalRadius, primary.energyRadiated);
//		Local calendar
//		A negative value for apparent day length is valid even if the world's rotation is not retrograde
//		This means that the primary will rise in the west and set in the east
		world.apparentDayLength = worldIsAsteroidBelt ? 0 : determineLocalCalendar(world.rotationPeriod, world.retrogradeOrNot, POM_PLANET, world.orbitalPeriod, CALO_DAY_LENGTH, 0);
		std::cout << "Got to apparentDayLength" << std::endl;

//		Calculate the world's axial tilt
		world.axialTilt = calculateAxialTilt();
		std::cout << "Got to axialTilt" << std::endl;
		world.ringSystemVisibility = worldIsGasGiant ? getRingSystemVisibility(world.firstFamilyMoonlets) : 0;
//		Determine the world's volcanic activity
//		NOTE: This function takes two additional arguments for moons, but I wanted to test what happens if nothing is passed
		world.volcanicActivityLevel = worldIsTerrestrial ? volcanicActivityTable(world.worldType, world.surfaceGravity, primary.stellarAge, POM_PLANET, world.numberOfMajorMoons, 0) : VAL_NONE;
		std::cout << "Volcanic activity level: " << int(world.volcanicActivityLevel) << std::endl;
		std::cout << "Got to volcanicActivityLevel" << std::endl;
//		Determine the effect the world's volcanic activity has on the world's atmosphere
		world.worldAtmosphereComposition = worldIsTerrestrial ? volcanicActivityEffectOnGardenWorld(world.volcanicActivityLevel, world.worldType, world.worldAtmosphereComposition) : world.worldAtmosphereComposition;
		std::cout << "Got to volcanicActivityEffectOnGardenWorld" << std::endl;
//		Determine the world's tectonic activity
		world.tectonicActivityLevel = worldIsTerrestrial ? getTectonicActivity(world.worldType, world.volcanicActivityLevel, world.hydrographicCoverage, POM_PLANET, world.numberOfMajorMoons) : TAL_NONE;
		std::cout << "Got to tectonicActivityLevel" << std::endl;

//		Determine the world's minimum molecular weight retained
		world.minimumMolecularWeightRetained = minimumMolecularWeightRetainedCalculator(world.blackbodyTemperature, world.worldDiameter, world.worldDensity, world.worldType);
		world.atmosphericPressureCategory = worldIsTerrestrial ? atmosphericPressureCategoriesTable(world.atmosphericPressure) : APC_NONE;
//		If the world is tide locked
		char oldAtmosphericPressureCategory = world.atmosphericPressureCategory;
		tie(world.atmosphericPressure, world.atmosphericPressureCategory, world.hydrographicCoverage, world.dayFaceAverageTemperature, world.nightFaceAverageTemperature) = tideLockedWorldEffects(world.tidalLockedOrNot, world.surfaceTemperature, world.atmosphericPressureCategory, world.atmosphericPressure, world.atmosphereMass, world.surfaceGravity, world.worldType, world.hydrographicCoverage);
		world.atmosphericPressure = oldAtmosphericPressureCategory != world.atmosphericPressureCategory ? getNewAtmosphericPressure(world.atmosphericPressureCategory) : world.atmosphericPressureCategory;
		std::cout << "Got to tideLockedWorldEffects" << std::endl;
//		Check if the world is in a resonant orbit
//		If so, determine the effects that has on the world
		tie(world.resonantOrNot, world.apparentDayLength) = resonantWorldEffects(world.orbitalEccentricity, world.tidalLockedOrNot,	world.orbitalPeriod, world.apparentDayLength);
		std::cout << "Got to resonantWorldEffects" << std::endl;
		//	Determine the world's resource value modifier
		world.resourceValueModifier = resourceDeterminator(world.worldType);
		//	Determine the world's habitability modifier
		std::tie(world.habitabilityModifier, world.climateType, world.breathable) = worldIsTerrestrial ? habitabilityModifiersTable(world.worldType, world.atmosphereMass, world.hydrographicCoverage, world.atmosphericPressure, world.surfaceTemperature, world.worldAtmosphereComposition) : std::make_tuple(static_cast<int>(0), static_cast<char>(0), static_cast<bool>(0));
		//		Determine the effect of tectonic and volcanic activity on the world's habitability and resources
		int newResourceValueModifier = 0;
		int newHabitabilityModifier = 0;
		tie(newHabitabilityModifier, newResourceValueModifier) = worldIsTerrestrial ? effectsOfGeologicActivity(world.volcanicActivityLevel, world.tectonicActivityLevel, world.habitabilityModifier, world.resourceValueModifier) : make_tuple(world.habitabilityModifier, world.resourceValueModifier);
		world.habitabilityModifier += newHabitabilityModifier;
		world.resourceValueModifier +=newResourceValueModifier;
		world.habitabilityModifier = world.habitabilityModifier < -2 ? -2 : world.habitabilityModifier;
		world.resourceValueModifier = world.resourceValueModifier < -5 ? -5 : world.resourceValueModifier;
		world.resourceValueModifier = world.resourceValueModifier > 5 ? 5 : world.resourceValueModifier;
		std::cout << "Got to effectsOfGeologicActivity" << std::endl;
//		Get the world's magnetic field strength
		world.magneticFieldStrength = getMagneticField(world.worldMass, world.worldDensity, world.rotationPeriod, primary.stellarAge, world.worldType);
		world.nativeEcosphere = worldIsTerrestrial ? getNativeEcosphere(world.worldType, primary.stellarAge, diceRoller(6, 2), world.hydrographicCoverage) : NE_NOLIFE;

//		Mapping the world
//		Asteroid belts have no maps
		if (worldIsTerrestrial)
		{
//			Get the number of hexes per world triangle side
			world.hexesPerSide = getHexesPerSide(world.worldDiameter);
			std::cout << "world.hexesPerSide == " << world.hexesPerSide << std::endl;
//			Get the total number of hexes on the world
			world.totalHexes = getTotalHexCount(world.hexesPerSide);
			std::cout << "world.totalHexes == " << world.totalHexes << std::endl;
//			Get the number of tectonic plates
			world.tectonicPlateCount = getTectonicPlateCount(world.worldDiameter, world.hydrographicCoverage, world.worldType);
			std::cout << "world.tectonicPlateCount == " << int(world.tectonicPlateCount) << std::endl;
//			Describe the tectonic plates
/*			int remainingHexes = world.totalHexes;
			bool lastPlate = false;
			for (int i = 0; i < world.tectonicPlateCount; i++)
			{
				lastPlate = (i == world.tectonicPlateCount - 1) ? true : false;
				world.tectonicPlateArray[i].tectonicPlateSize = getTectonicPlateSize(floor(world.totalHexes / world.tectonicPlateCount), (world.tectonicPlateCount / 2), remainingHexes, lastPlate);
				remainingHexes -= world.tectonicPlateArray[i].tectonicPlateSize;
				std::cout << "world.tectonicPlateArray[" << i << "].tectonicPlateSize == " << int(world.tectonicPlateArray[i].tectonicPlateSize) << std::endl;
				world.tectonicPlateArray[i].tectonicPlateMovementType = getTectonicPlateMovementType();
				std::cout << "world.tectonicPlateArray[" << i << "].tectonicPlateMovementType == "<< int(world.tectonicPlateArray[i].tectonicPlateMovementType) << std::endl;
			}
			*/
//			Get the number of water hexes
			world.waterHexCount = getWaterHexCount(world.totalHexes, world.hydrographicCoverage);
//			Get the number of land hexes
			world.landHexCount = getLandHexCount(world.totalHexes, world.waterHexCount);
//			Determine the number of each hex type
			if (world.hydrographicCoverage == 0)
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
			world.hexesPerSide				= 0;
			world.totalHexes				= 0;
			world.tectonicPlateCount		= 0;
			world.waterHexCount				= 0;
			world.landHexCount				= 0;
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
star_t starBuilder(star_t& star, float starSystemAge, int numberOfStarsInSystem, int companionStar, float companionAInnerForbiddenZone, float companionAOuterForbiddenZone, float companionBInnerForbiddenZone, float companionBOuterForbiddenZone, float companionAOrbitalRadius, float companionBOrbitalRadius, rapidcsv::Document& starDoc, int currentCSVIndex, bool randomSystem, rapidcsv::Document& worldDoc)
{
	std::cout << "Entered starBuilder" << std::endl;
//	Which star is this?
	star.starNumber = companionStar;
//	std::cout << "starNumber == " << (int)star.starNumber << std::endl;
//	Determine the star's age
	star.stellarAge = starSystemAge;
	std::cout << "star.stellarAge == " << star.stellarAge << std::endl;
//	Determine randomStar
	bool randomStar = (randomSystem == true || starDoc.GetCell<std::string>("spect", currentCSVIndex) == "~") ? true : false;
	std::cout << "randomStar == " << randomStar << std::endl;
//	Determine the star's physical parameters
//	If a random star is to be rolled
	if (randomStar == true)
	{
/*
//		std::cout << "randomStar is true and its if loop has been entered" << std::endl;
//		std::cout << "Star " << (int)star.starNumber << std::endl;
//		std::cout << "star.innerForbiddenZone == " << star.innerForbiddenZone << std::endl;
//		std::cout << "star.outerForbiddenZone == " << star.outerForbiddenZone << std::endl;
//		std::cout << "star.minSeparationToCompanion == " << star.minSeparationToCompanion << std::endl;
//		std::cout << "star.maxSeparationToCompanion == " << star.maxSeparationToCompanion << std::endl;
*/
//		If the star is random, all worlds are random
//		randomWorld = true;
//		Determine the star's mass
		if (randomSystem == true || (randomSystem == false && starDoc.GetCell<std::string>("mass", currentCSVIndex) == "~"))	{star.stellarMass = stellarMassTable();}
		else																													{star.stellarMass = starDoc.GetCell<float>("mass", currentCSVIndex);}
//		std::cout << "stellarMass = " << star.stellarMass << std::endl;
/*
//		Check if star.stellarAge == 0
//		Not sure why this is here 25/11/2020
//		if (star.stellarAge == 0) {star.stellarAge = stellarAgeTable(starSystem.gardenWorldPresent);}
//		std::cout << "stellarAge = " << star.stellarAge << std::endl;
*/
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
/*
//		Determine the equatorial rotation velocity of the star
//		star.equatorialRotationVelocity = getEquatorialRotationVelocity(star.stellarRadius * 2, star.rotation)
//		std::cout << "\nStar " << (int)star.starNumber << " is about to exit the first randomStar if loop" << std::endl;
//		std::cout << "star.innerForbiddenZone == " << star.innerForbiddenZone << std::endl;
//		std::cout << "star.outerForbiddenZone == " << star.outerForbiddenZone << std::endl;
//		std::cout << "star.minSeparationToCompanion == " << star.minSeparationToCompanion << std::endl;
//		std::cout << "star.maxSeparationToCompanion == " << star.maxSeparationToCompanion << std::endl;
*/
	}

//	If the star is from a .csv
	else
	{
		std::cout << "\nStar physical characteristics" << std::endl;
//		randomWorld = false;
//		Assign identifiers
//		std::string properName;
//		std::string glieseIndex;
		if (starDoc.GetCell<std::string>("con", currentCSVIndex) != "")	{star.starConstellation = starDoc.GetCell<std::string>("con", currentCSVIndex);}
		std::cout << "constellation set" << std::endl;
		std::tie(star.hipIndex, star.hygIndex, star.hdIndex, star.hrIndex, star.glieseIndex, star.properName, star.bayerDesignation, star.flamsteedDesignation) = getStarIDFromCSV(starDoc, currentCSVIndex, star.starConstellation);
		std::cout << "got star id" << std::endl;
//		strcpy(star.glieseIndex, glieseIndex.c_str());
//		strcpy(star.properName, properName.c_str());
//		Assign luminosity
		star.stellarLuminosity = starDoc.GetCell<double>("lum", currentCSVIndex);
		std::cout << "star.stellarLuminosity == " << star.stellarLuminosity << std::endl;
//		Boolean parameters for completeStellarClassification
		bool massPreset 		= starDoc.GetCell<std::string>("mass", currentCSVIndex) 		== "~" || starDoc.GetCell<std::string>("mass", currentCSVIndex) 		== ""	? false : true;
		bool radiusPreset 		= starDoc.GetCell<std::string>("radius", currentCSVIndex) 		== "~" || starDoc.GetCell<std::string>("radius", currentCSVIndex) 		== ""	? false : true;
		bool temperaturePreset 	= starDoc.GetCell<std::string>("temperature", currentCSVIndex) 	== "~" || starDoc.GetCell<std::string>("temperature", currentCSVIndex) 	== ""	? false : true;
//		Determine the star's MK classification and its mass, radius, and temperature
		bool floatOrIntNumericValue;
		std::tie(star.harvardLetter, star.yerkesClassification, star.numericValue, floatOrIntNumericValue) = completeStellarClassification(starDoc.GetCell<std::string>("spect", currentCSVIndex), star.stellarLuminosity, massPreset, radiusPreset, temperaturePreset);
/*
		std::cout << "\ncompleteStellarClassification has just returned with these values:" << std::endl;
//		std::cout << "star.harvardLetter == " << star.harvardLetter << std::endl;
//		std::cout << "star.yerkesClassification == " << star.yerkesClassification << std::endl;
//		std::cout << "star.numericValue == " << star.numericValue << "\n" << std::endl;
*/
//		Determine the star's physical parameters
		std::tie(star.stellarMass, star.stellarRadius, star.stellarTemperature, star.starColor_r, star.starColor_g, star.starColor_b) = extrapolateStellarParameters(currentCSVIndex, starDoc, star.harvardLetter, star.yerkesClassification, floatOrIntNumericValue, massPreset, radiusPreset, temperaturePreset, star.numericValue, star.numericValue);
//		If mass, radius, or temperature are preset
/*
//		star.stellarMass 		= massPreset 		? starDoc.GetCell<float>("mass", currentCSVIndex) 			: star.stellarMass;
//		std::cout << "star.stellarMass == " << star.stellarMass << std::endl;
//		star.stellarRadius 		= radiusPreset 		? starDoc.GetCell<float>("radius", currentCSVIndex) 		: star.stellarRadius;
//		std::cout << "star.stellarRadius == " << star.stellarRadius << std::endl;
//		star.stellarTemperature = temperaturePreset ? starDoc.GetCell<float>("temperature", currentCSVIndex)	: star.stellarTemperature;
//		std::cout << "star.stellarTemperature == " << star.stellarTemperature << std::endl;
*/
//		Assign cartesian components
		star.cartesianX = starDoc.GetCell<float>("x", currentCSVIndex);
		star.cartesianY = starDoc.GetCell<float>("y", currentCSVIndex);
		star.cartesianZ = starDoc.GetCell<float>("z", currentCSVIndex);
		star.cartesianVelocityX = starDoc.GetCell<float>("vx", currentCSVIndex);
		star.cartesianVelocityY = starDoc.GetCell<float>("vy", currentCSVIndex);
		star.cartesianVelocityZ = starDoc.GetCell<float>("vz", currentCSVIndex);
	}

//	Calculate the energy radiated by the star
	star.energyRadiated = randomStar ? stefanBoltzmannCalculator(star.tableTemperature) : stefanBoltzmannCalculator(star.stellarTemperature);

//	Determine the escape velocity of the star
	star.escapeVelocity = getEscapeVelocity(star.stellarMass * SOL_MASS_IN_KG, star.stellarRadius * SOL_RADIUS_IN_KM);
	std::cout << "stellarRadius = " << star.stellarRadius << std::endl;
//	Determine the orbital zones of the star
//	Determine the star's inner limit radius
	star.innerLimitRadius = getInnerLimitRadius(star.stellarMass, star.stellarLuminosity);
//	std::cout << "innerLimitRadius = " << star.innerLimitRadius << std::endl;
//	Determine the star's outer limit radius
	star.outerLimitRadius = getOuterLimitRadius(star.stellarMass);
//	std::cout << "outerLimitRadius = " << star.outerLimitRadius << std::endl;

//	Determine the star's snow line
//	If the star is from a .csv, use the formula found in the "Solar System Regions" section of Atomic Rockets's Worldbuilding page
	star.snowLineRadius = randomStar ? getSnowLine(star.lMin) : getSnowLine(star.stellarLuminosity);
//	std::cout << "snow line radius = " << star.snowLineRadius << std::endl;
/*
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
			star.firstGasGiantOrbitalRadius = placeFirstGasGiant(star.snowLineRadius, star.gasGiantArrangement, star.innerLimitRadius);
			star.firstGasGiantPresent = true;
		}
	}

//	If the star is generated from a .csv
	else
	{
//		Assign distance from Sol
		star.distanceFromSol = starDoc.GetCell<float>("dist", currentCSVIndex);
//		Check worldDoc for any gas giants
		std::tie(star.worldArray[0].planetDBIndex, star.firstGasGiantPresent, star.gasGiantArrangement, star.firstGasGiantOrbitalRadius, star.numberOfCSVPlanets) = csv_determineGasGiantArrangement(star, starDoc, worldDoc, star.snowLineRadius, std::to_string(star.hipIndex), std::to_string(star.hdIndex), std::string(star.glieseIndex), star.properName, currentCSVIndex);
//		Check again with default function if GGA_NO_GAS_GIANT is returned
		if (star.gasGiantArrangement == GGA_NO_GAS_GIANT)
		{	//		Determine the star's gas giant arrangement
			int arrangementDiceRoll = diceRoller(6, 1);
			star.gasGiantArrangement = arrangementDiceRoll >= 3 ? gasGiantArrangementTable() : GGA_NO_GAS_GIANT;
			//		std::cout << "gasGiantArrangement = " << star.gasGiantArrangement << std::endl;

			//		If there is no gas giant
			if (star.gasGiantArrangement == GGA_NO_GAS_GIANT)
			{
				star.firstGasGiantOrbitalRadius = 0;
				star.firstGasGiantPresent = false;
			}

			else
			{
				star.firstGasGiantOrbitalRadius = placeFirstGasGiant(star.snowLineRadius, star.gasGiantArrangement, star.innerLimitRadius);
				star.firstGasGiantPresent = true;
			}
		}

		//		If there is a gas giant
		else
		{
			star.firstGasGiantOrbitalRadius = placeFirstGasGiant(star.snowLineRadius, star.gasGiantArrangement, star.innerLimitRadius);
			star.firstGasGiantPresent = true;
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
	star = placePlanetaryOrbits(star, worldDoc, randomStar, numberOfStarsInSystem, companionAInnerForbiddenZone, companionAOuterForbiddenZone, companionBInnerForbiddenZone, companionBOuterForbiddenZone, companionAOrbitalRadius, companionBOrbitalRadius);

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
	star.numberOfPlanets = 0;
	std::cout << "\nstar.numberOfOrbits == " << int (star.numberOfOrbits) << "\n" << std::endl;
	for (int index = 0; index < star.numberOfOrbits; index++)
	{
		std::cout << "Worldbuilder for loop reached" << std::endl;
//		If the world is not a gas giant or empty
//		if (star.sizeClassArray[index] != WT_SMALL_GAS_GIANT && star.sizeClassArray[index] != WT_MEDIUM_GAS_GIANT && star.sizeClassArray[index] != WT_LARGE_GAS_GIANT && star.sizeClassArray[index] != SC_EMPTY_ORBIT)
//		if (star.sizeClassArray[index] == SC_ASTEROID_BELT || star.sizeClassArray[index] == SC_EMPTY_ORBIT || star.sizeClassArray[index] == SC_TERRESTRIAL_PLANET_SMALL || star.sizeClassArray[index] == SC_TERRESTRIAL_PLANET_STANDARD || star.sizeClassArray[index] == SC_TERRESTRIAL_PLANET_LARGE)
//		std::string sizeClassString = star.sizeClassArray[index];
		std::cout << "star.sizeClassArray[" << index << "] = " << int (star.sizeClassArray[index]) << std::endl;

		if (star.sizeClassArray[index] != SC_EMPTY_ORBIT)
		{
			star.numberOfPlanets++;
//			Assign randomWorld
//			randomWorld is true by default, but if the current index matches a value in star.preplacedWorldIndex randomWorld is false
			bool randomWorld = true;
			if (star.numberOfCSVPlanets > 0)
			{
				for (int i = 0; i < star.numberOfCSVPlanets; i++)
				{
					if (index == star.preplacedWorldIndex[i])	{randomWorld = false; star.worldArray[star.sizeClassIndex].planetDBIndex = star.preplacedWorldPlanetDBIndex[i]; break;}
				}
			}
			std::cout << "Worldbuilder if loop reached" << std::endl;
			std::cout << "star.orbitalRadiusArray[" << index << "] == " << star.orbitalRadiusArray[index] << std::endl;
			std::cout << "randomWorld == " << randomWorld << std::endl;
//			Run worldBuilder_ADVANCED
//			Using sizeClassIndex
			star.worldArray[star.sizeClassIndex] = worldBuilder_ADVANCED(star.worldArray[star.sizeClassIndex], star.sizeClassArray[index], star.orbitalRadiusArray[index], star, worldDoc, index/*, 0, 0, "", POM_PLANET*/, randomWorld);
			star.sizeClassIndex++;
//			Using index
//			star.worldArray[index] = worldBuilder_ADVANCED(star.worldArray[index], star.sizeClassArray[index], star.orbitalRadiusArray[index], star, worldDoc, index/*, 0, 0, "", POM_PLANET*/, randomWorld);
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

	star = placeJumpPointOrbits(star);
	star = nameBodies(star);

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
starSystem_t starSystemBuilder(starSystem_t& starSystem, bool randomSystem, rapidcsv::Document& starDoc, int currentCSVIndex, rapidcsv::Document& worldDoc)
{
//	starSystem_t starSystem;
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
			if 		(i == 0 && starSystem.numberOfStars == 2) {starSystem.stars[0] = starBuilder(starSystem.stars[0], starSystem.numberOfStars, starSystem.systemAge, i, starSystem.stars[1].innerForbiddenZone, starSystem.stars[1].outerForbiddenZone, 0, 0, starSystem.stars[1].averageOrbitalRadius, 0, starDoc, currentCSVIndex, randomSystem, worldDoc);}
			else if (i == 1 && starSystem.numberOfStars == 2) {starSystem.stars[1] = starBuilder(starSystem.stars[1], starSystem.numberOfStars, starSystem.systemAge, i, starSystem.stars[0].innerForbiddenZone, starSystem.stars[0].outerForbiddenZone, 0, 0, starSystem.stars[0].averageOrbitalRadius, 0, starDoc, currentCSVIndex, randomSystem, worldDoc);}

//			For trinary syst, random Systems
			else if (i == 0 && starSystem.numberOfStars == 3) {starSystem.stars[0] = starBuilder(starSystem.stars[0], starSystem.numberOfStars, starSystem.systemAge, i, starSystem.stars[1].innerForbiddenZone, starSystem.stars[1].outerForbiddenZone, starSystem.stars[2].innerForbiddenZone, starSystem.stars[2].outerForbiddenZone, starSystem.stars[1].averageOrbitalRadius, starSystem.stars[2].averageOrbitalRadius, starDoc, currentCSVIndex, randomSystem, worldDoc);}
			else if (i == 1 && starSystem.numberOfStars == 3) {starSystem.stars[1] = starBuilder(starSystem.stars[1], starSystem.numberOfStars, starSystem.systemAge, i, starSystem.stars[0].innerForbiddenZone, starSystem.stars[0].outerForbiddenZone, starSystem.stars[2].innerForbiddenZone, starSystem.stars[2].outerForbiddenZone, starSystem.stars[0].averageOrbitalRadius, starSystem.stars[2].averageOrbitalRadius, starDoc, currentCSVIndex, randomSystem, worldDoc);}
			else if (i == 2 && starSystem.numberOfStars == 3) {starSystem.stars[2] = starBuilder(starSystem.stars[2], starSystem.numberOfStars, starSystem.systemAge, i, starSystem.stars[0].innerForbiddenZone, starSystem.stars[0].outerForbiddenZone, starSystem.stars[1].innerForbiddenZone, starSystem.stars[1].outerForbiddenZone, starSystem.stars[0].averageOrbitalRadius, starSystem.stars[1].averageOrbitalRadius, starDoc, currentCSVIndex, randomSystem, worldDoc);}

//			For single stars
			else {starSystem.stars[i] = starBuilder(starSystem.stars[0], starSystem.numberOfStars, starSystem.systemAge, i, 0, 0, 0, 0, 0, 0, starDoc, currentCSVIndex, randomSystem, worldDoc);}
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
		int comp1 = 0;
		int comp2 = 0;
		int comp3 = 0;
		comp1 = starDoc.GetCell<int>("comp", currentCSVIndex);
//		Check for out of bounds
		if ((currentCSVIndex + 1) < STARDOC_LENGTH)
		{
			comp2 = starDoc.GetCell<int>("comp", currentCSVIndex + 1);
			if ((currentCSVIndex + 2) < STARDOC_LENGTH)
			{
				comp3 = starDoc.GetCell<int>("comp", currentCSVIndex + 2);
			}
		}
		starSystem.numberOfStars = csv_DetermineStarCount(comp1, comp2, comp3);
//		std::cout << "starSystem.numberOfStars == " << unsigned(starSystem.numberOfStars) << std::endl;
//		The primary has no orbital period
		starSystem.stars[0].stellarOrbitalPeriod = 0;

//		If the system has two or more stars
		if (starSystem.numberOfStars > 1)
		{

//				For binary systems
			if (starSystem.numberOfStars == 2)
			{
//					Companion's orbital parameters
				bool eccentricityCheck = starDoc.GetCell<std::string>("eccentricity", currentCSVIndex + 1) != "~" && starDoc.GetCell<std::string>("eccentricity", currentCSVIndex + 1) != "";
				bool orbitalRadiusCheck = starDoc.GetCell<std::string>("semiMajorAxis", currentCSVIndex + 1) != "~" && starDoc.GetCell<std::string>("semiMajorAxis", currentCSVIndex + 1) != "";
				bool orbitalPeriodCheck = starDoc.GetCell<std::string>("period", currentCSVIndex + 1) != "~" && starDoc.GetCell<std::string>("period", currentCSVIndex + 1) != "";
				if (eccentricityCheck && orbitalRadiusCheck && orbitalPeriodCheck)
				{
					starSystem.stars[1].orbitalEccentricity = starDoc.GetCell<float>("eccentricity", currentCSVIndex + 1);
					starSystem.stars[1].averageOrbitalRadius = starDoc.GetCell<float>("semiMajorAxis", currentCSVIndex + 1);
					starSystem.stars[1].stellarOrbitalPeriod = starDoc.GetCell<float>("period", currentCSVIndex + 1);
					starSystem.stars[1].minSeparationToCompanion = (1 - starSystem.stars[1].orbitalEccentricity) * starSystem.stars[1].averageOrbitalRadius;
					starSystem.stars[1].maxSeparationToCompanion = (1 + starSystem.stars[1].orbitalEccentricity) * starSystem.stars[1].averageOrbitalRadius;
					starSystem.stars[1].innerForbiddenZone = starSystem.stars[1].minSeparationToCompanion / 3;
					starSystem.stars[1].outerForbiddenZone = starSystem.stars[1].maxSeparationToCompanion * 3;
				}

				else
				{
					starSystem.stars[1] = orbitalSeparationTable(starSystem.numberOfStars, 1, starSystem.stars[1], starSystem.gardenWorldPresent);
				}

//					Primary's orbital parameters
				starSystem.stars[0].minSeparationToCompanion = starSystem.stars[1].minSeparationToCompanion;
				starSystem.stars[0].maxSeparationToCompanion = starSystem.stars[1].maxSeparationToCompanion;
				starSystem.stars[0].innerForbiddenZone = starSystem.stars[1].innerForbiddenZone;
				starSystem.stars[0].outerForbiddenZone = starSystem.stars[1].outerForbiddenZone;
			}

//				For trinary systems
			else
			{
				bool eccentricityCheck = starDoc.GetCell<std::string>("eccentricity", currentCSVIndex + 2) != "~" && starDoc.GetCell<std::string>("eccentricity", currentCSVIndex + 2) != "";
				bool orbitalRadiusCheck = starDoc.GetCell<std::string>("semiMajorAxis", currentCSVIndex + 2) != "~" && starDoc.GetCell<std::string>("semiMajorAxis", currentCSVIndex + 2) != "";
				bool orbitalPeriodCheck = starDoc.GetCell<std::string>("period", currentCSVIndex + 2) != "~" && starDoc.GetCell<std::string>("period", currentCSVIndex + 2) != "";
				if (eccentricityCheck && orbitalRadiusCheck && orbitalPeriodCheck)
				{
//					Second companion's orbital parameters
					starSystem.stars[2].orbitalEccentricity = starDoc.GetCell<float>("eccentricity", currentCSVIndex + 2);
					starSystem.stars[2].stellarOrbitalPeriod = starDoc.GetCell<float>("period", currentCSVIndex + 2);
					starSystem.stars[2].averageOrbitalRadius = starDoc.GetCell<float>("semiMajorAxis", currentCSVIndex + 2);
					starSystem.stars[2].minSeparationToCompanion = (1 - starSystem.stars[2].orbitalEccentricity) * starSystem.stars[2].averageOrbitalRadius;
					starSystem.stars[2].maxSeparationToCompanion = (1 + starSystem.stars[2].orbitalEccentricity) * starSystem.stars[2].averageOrbitalRadius;
					starSystem.stars[2].innerForbiddenZone = starSystem.stars[2].minSeparationToCompanion / 3;
					starSystem.stars[2].outerForbiddenZone = starSystem.stars[2].maxSeparationToCompanion * 3;
				}

				else
				{
					starSystem.stars[2] = orbitalSeparationTable(starSystem.numberOfStars, 2, starSystem.stars[2], starSystem.gardenWorldPresent);
				}

				eccentricityCheck = starDoc.GetCell<std::string>("eccentricity", currentCSVIndex + 1) != "" && starDoc.GetCell<std::string>("eccentricity", currentCSVIndex + 1) != "~";
				orbitalRadiusCheck = starDoc.GetCell<std::string>("semiMajorAxis", currentCSVIndex + 1) != "" && starDoc.GetCell<std::string>("semiMajorAxis", currentCSVIndex + 1) != "~";
				orbitalPeriodCheck = starDoc.GetCell<std::string>("period", currentCSVIndex + 1) != "" && starDoc.GetCell<std::string>("period", currentCSVIndex + 1) != "~";

				if (eccentricityCheck && orbitalRadiusCheck && orbitalPeriodCheck)
				{
					starSystem.stars[1].orbitalEccentricity = starDoc.GetCell<float>("eccentricity", currentCSVIndex + 1);
					starSystem.stars[1].averageOrbitalRadius = starDoc.GetCell<float>("semiMajorAxis", currentCSVIndex + 1);
					starSystem.stars[1].stellarOrbitalPeriod = starDoc.GetCell<float>("period", currentCSVIndex + 1);
					starSystem.stars[1].minSeparationToCompanion = (1 - starSystem.stars[1].orbitalEccentricity) * starSystem.stars[1].averageOrbitalRadius;
					starSystem.stars[1].maxSeparationToCompanion = (1 + starSystem.stars[1].orbitalEccentricity) * starSystem.stars[1].averageOrbitalRadius;
					starSystem.stars[1].innerForbiddenZone = starSystem.stars[1].minSeparationToCompanion / 3;
					starSystem.stars[1].outerForbiddenZone = starSystem.stars[1].maxSeparationToCompanion * 3;
				}

				else
				{
					starSystem.stars[1] = orbitalSeparationTable(starSystem.numberOfStars, 1, starSystem.stars[1], starSystem.gardenWorldPresent);
				}

//				Primary's orbital parameters
				starSystem.stars[0].innerForbiddenZone = starSystem.stars[1].innerForbiddenZone;
				starSystem.stars[0].outerForbiddenZone = starSystem.stars[1].outerForbiddenZone;
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
		starSystem.systemAge = starSystem.systemAge >= 0 ? stellarAgeTable(starSystem.gardenWorldPresent) : starSystem.systemAge;
		std::cout << "csv's stellarAge == " << starSystem.systemAge << std::endl;

//		Build the system's stars
//		For each star in the system
		for (int i = 0; i < starSystem.numberOfStars; i++)
		{
//			i is passed so that the forbidden zones can use it as a counter of the current star being worked on
			std::cout << "starBuilder i == " << i << std::endl;
//			For binary systems
			if 		(i == 0 && starSystem.numberOfStars == 2) {starSystem.stars[0] = starBuilder(starSystem.stars[0], starSystem.systemAge, starSystem.numberOfStars, i, starSystem.stars[1].innerForbiddenZone, starSystem.stars[1].outerForbiddenZone, 0, 0, starSystem.stars[1].averageOrbitalRadius, 0, starDoc, currentCSVIndex, randomSystem, worldDoc);}
			else if (i == 1 && starSystem.numberOfStars == 2) {starSystem.stars[1] = starBuilder(starSystem.stars[1], starSystem.systemAge, starSystem.numberOfStars, i, starSystem.stars[0].innerForbiddenZone, starSystem.stars[0].outerForbiddenZone, 0, 0, starSystem.stars[0].averageOrbitalRadius, 0, starDoc, currentCSVIndex + 1, randomSystem, worldDoc);}

//			For trinary systems
			else if (i == 0 && starSystem.numberOfStars == 3) {starSystem.stars[0] = starBuilder(starSystem.stars[0], starSystem.systemAge, starSystem.numberOfStars, i, starSystem.stars[1].innerForbiddenZone, starSystem.stars[1].outerForbiddenZone, starSystem.stars[2].innerForbiddenZone, starSystem.stars[2].outerForbiddenZone, starSystem.stars[1].averageOrbitalRadius, starSystem.stars[2].averageOrbitalRadius, starDoc, currentCSVIndex, randomSystem, worldDoc);}
			else if (i == 1 && starSystem.numberOfStars == 3) {starSystem.stars[1] = starBuilder(starSystem.stars[1], starSystem.systemAge, starSystem.numberOfStars, i, starSystem.stars[0].innerForbiddenZone, starSystem.stars[0].outerForbiddenZone, starSystem.stars[2].innerForbiddenZone, starSystem.stars[2].outerForbiddenZone, starSystem.stars[0].averageOrbitalRadius, starSystem.stars[2].averageOrbitalRadius, starDoc, currentCSVIndex + 1, randomSystem, worldDoc);}
			else if (i == 2 && starSystem.numberOfStars == 3) {starSystem.stars[2] = starBuilder(starSystem.stars[2], starSystem.systemAge, starSystem.numberOfStars, i, starSystem.stars[0].innerForbiddenZone, starSystem.stars[0].outerForbiddenZone, starSystem.stars[1].innerForbiddenZone, starSystem.stars[1].outerForbiddenZone, starSystem.stars[0].averageOrbitalRadius, starSystem.stars[1].averageOrbitalRadius, starDoc, currentCSVIndex + 2, randomSystem, worldDoc);}
//			For single stars
			else {starSystem.stars[i] = starBuilder(starSystem.stars[i], starSystem.systemAge, starSystem.numberOfStars, i, 0, 0, 0, 0, 0, 0, starDoc, currentCSVIndex, randomSystem, worldDoc);}
			std::cout << "Star generated" << std::endl;
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

//		Assign cartesian components
		if (starSystem.numberOfStars == 1)
		{
			starSystem.cartesianX 			= starSystem.stars[0].cartesianX;
			starSystem.cartesianY 			= starSystem.stars[0].cartesianY;
			starSystem.cartesianZ 			= starSystem.stars[0].cartesianZ;
			starSystem.cartesianVelocityX 	= starSystem.stars[0].cartesianVelocityX;
			starSystem.cartesianVelocityY 	= starSystem.stars[0].cartesianVelocityY;
			starSystem.cartesianVelocityZ 	= starSystem.stars[0].cartesianVelocityZ;
		}

		else if (starSystem.numberOfStars == 2)
		{
			starSystem.cartesianX 			= (starSystem.stars[0].cartesianX 			+ starSystem.stars[1].cartesianX) 			;
			starSystem.cartesianY 			= (starSystem.stars[0].cartesianY 			+ starSystem.stars[1].cartesianY) 			;
			starSystem.cartesianZ 			= (starSystem.stars[0].cartesianZ 			+ starSystem.stars[1].cartesianZ) 			;
			starSystem.cartesianVelocityX 	= (starSystem.stars[0].cartesianVelocityX 	+ starSystem.stars[1].cartesianVelocityX)	;
			starSystem.cartesianVelocityY 	= (starSystem.stars[0].cartesianVelocityY 	+ starSystem.stars[1].cartesianVelocityY)	;
			starSystem.cartesianVelocityZ 	= (starSystem.stars[0].cartesianVelocityZ 	+ starSystem.stars[1].cartesianVelocityZ)	;
		}

		else
		{
			starSystem.cartesianX 			= (starSystem.stars[0].cartesianX 			+ starSystem.stars[1].cartesianX 			+ starSystem.stars[2].cartesianX) 			;
			starSystem.cartesianY 			= (starSystem.stars[0].cartesianY 			+ starSystem.stars[1].cartesianY 			+ starSystem.stars[2].cartesianY) 			;
			starSystem.cartesianZ 			= (starSystem.stars[0].cartesianZ 			+ starSystem.stars[1].cartesianZ 			+ starSystem.stars[2].cartesianZ) 			;
			starSystem.cartesianVelocityX 	= (starSystem.stars[0].cartesianVelocityX 	+ starSystem.stars[1].cartesianVelocityX 	+ starSystem.stars[2].cartesianVelocityX)	;
			starSystem.cartesianVelocityY 	= (starSystem.stars[0].cartesianVelocityY 	+ starSystem.stars[1].cartesianVelocityY 	+ starSystem.stars[2].cartesianVelocityY)	;
			starSystem.cartesianVelocityZ 	= (starSystem.stars[0].cartesianVelocityZ 	+ starSystem.stars[1].cartesianVelocityZ 	+ starSystem.stars[2].cartesianVelocityZ)	;
		}

	}
	std::cout << "starSystem is about to be returned" << std::endl;
	return starSystem;
}

int main()
{
	std::cout << "Debug information" << std::endl;
	std::cout << "struct atmosphericComposition_t = " << sizeof(atmosphericComposition_t) << std::endl << std::endl;
	std::cout << "struct moon_t = " << sizeof(moon_t) << std::endl << std::endl;
	std::cout << "struct moonlet_t = " << sizeof(moonlet_t) << std::endl << std::endl;
	std::cout << "struct star_t = " << sizeof(star_t) << std::endl;
	std::cout << "struct starSystem_t = " << sizeof(starSystem_t) << std::endl;
	std::cout << "struct tectonicPlate_t = " << sizeof(tectonicPlate_t) << std::endl << std::endl;
	std::cout << "struct world_t = " << sizeof(world_t) << std::endl;
//	for (int i = 0; i < 100; i++)
//	{
	std::string randomSystemString;
//	std::cout << "Generate a random system or one from a .csv? ";
//	std::getline(cin, randomSystemString);
//	bool randomSystem = randomSystemString == "random" ? true : false;
	bool randomSystem = false;
	rapidcsv::Document worldDoc("planetDB.csv", rapidcsv::LabelParams(0, 0));
	rapidcsv::Document starDoc("out_blanks_filled.csv", rapidcsv::LabelParams(0, 0));
/*
//	Output .csv's
	rapidcsv::Document starSystemExport("output/starSystem_t_db.csv", rapidcsv::LabelParams(0, 0));
	rapidcsv::Document starExport("output/star_t_db.csv", rapidcsv::LabelParams(0, 0));
	rapidcsv::Document worldExport("output/world_t_db.csv", rapidcsv::LabelParams(0, 0));
	rapidcsv::Document moonExport("output/moon_t_db.csv", rapidcsv::LabelParams(0, 0));
	rapidcsv::Document tectonicPlateExport("output/tectonicPlate_t_db.csv", rapidcsv::LabelParams(0, 0));
	*/
//	starSystem_t starSystem = starSystemBuilder(true, starDoc, 0, worldDoc);
//	Generate and print the first ten systems after Sol
//	Indices for export
	int starSystemIndex = 1;
	int starIndex = 0;
	int worldIndex = 0;
	int moonIndex = 0;
	int jumpPointIndex = 0;

	starSystemCSVHeader();
	starCSVHeader();
	worldCSVHeader();
	moonCSVHeader();
	jumpPointCSVHeader();
	int i = 1;
	while (i < STARDOC_LENGTH)
	{
		std::cout << "\nmain i == " << i << std::endl;
		starSystem_t* starSystemPtr = new starSystem_t;
		*starSystemPtr = starSystemBuilder(*starSystemPtr, randomSystem, starDoc, i, worldDoc);
		i += starSystemPtr->numberOfStars;
		std::tie(starIndex, worldIndex, moonIndex, jumpPointIndex) = exportStarSystemToCSV(*starSystemPtr, starSystemIndex, starIndex, worldIndex, moonIndex, jumpPointIndex);
		starSystemIndex++;
		delete starSystemPtr;
		starSystemPtr = nullptr;
		std::cout << "starSystemPtr deleted" << std::endl;
		std::cout << "main i == " << i << std::endl;
	}
/*
	for (int i = 1; i < STARDOC_LENGTH; i++)
	{
		std::cout << "\nmain i == " << i << std::endl;
//		starSystem_t starSystem = starSystemBuilder(starSystem, randomSystem, starDoc, i, worldDoc);

//		Create a pointer starSystemPtr of type starSystem_t that points to an address the size of starSystem_t
		starSystem_t* starSystemPtr = new starSystem_t;
//		Dereference starSystemPtr and assign the return value of starSystemBuilder to the address that starSystemPtr points to
		*starSystemPtr = starSystemBuilder(randomSystem, starDoc, i, worldDoc);
//		starSystem_t *ptr{new starSystem_t};
//		*ptr = starSystemBuilder(*ptr, randomSystem, starDoc, i, worldDoc);
//		starSystem_t *ptr = new starSystem_t;
//		ptr = starSystemBuilder(*ptr, randomSystem, starDoc, i, worldDoc)
//		starSystem_t *ptr{new starSystem_t {starSystemBuilder(*ptr, randomSystem, starDoc, i, worldDoc)}};
//		printStarSystem(*ptr);
		std::tie(starIndex, worldIndex, moonIndex, jumpPointIndex) = exportStarSystemToCSV(*starSystemPtr, starSystemIndex, starIndex, worldIndex, moonIndex, jumpPointIndex);
//		std::tie(starIndex, worldIndex, moonIndex, jumpPointIndex) = exportStarSystemToCSV(*ptr, starSystemIndex, starIndex, worldIndex, moonIndex, jumpPointIndex);
		starSystemIndex++;
		delete starSystemPtr;
		starSystemPtr = nullptr;
		std::cout << "starSystemPtr deleted" << std::endl;
		std::cout << "main i == " << i << std::endl;
//		ptr = nullptr;
//		std::cout << "\nFinished printStarSystem" << std::endl;
	}
	*/
	std::cout << "For loop exited" << std::endl;
//	}
//	int starID = 32263;
//	getStarData(starID);
//	runPython(2, {"multiply.py", 2, 3})
	return 0;
}
