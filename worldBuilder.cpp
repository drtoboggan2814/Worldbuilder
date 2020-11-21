//	This holds the main function of the GURPS Space 4e worldbuilding process
//	This follows the steps outlined in the book

//	Boost libraries
//	#include <boost/python.hpp>

//	C++ libraries
#include <iostream>

//	#include <string>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <random>

//	Constant declarations
#include "declarations/constants/gasGiantArrangementConstants.h"
#include "declarations/constants/luminosityClassConstants.h"
#include "declarations/constants/miscConstants.h"
#include "declarations/constants/sizeClassConstants.h"
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
#include "declarations/functions/solarPowerFunctions.h"

//	Star system design
#include "declarations/functions/determineStarNumber.h"

	#include "declarations/functions/readFromHYGCSV.h"
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

	return moon;

}

//	Advanced world design sequence
//	This function applies only to terrestrial worlds
world_t worldBuilder_ADVANCED(char sizeClass, float averageOrbitalRadius, star_t primary/*, float planetMass, float parentPlanetOrbitalPeriod, char parentWorldType, string planetOrMoon*/)
{
//	Initialize world
	world_t world = {0};
/*	if (sizeClass == SC_ASTEROID_BELT)
	{
		cout << "sizeClass = SC_ASTEROID_BELT" << endl;
		cout << "averageOrbitalRadius = " << averageOrbitalRadius << endl;
	}
*/
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
//		Calculate blackbody temperature
		world.blackbodyTemperature = calculateBlackbodyTemperature_ADVANCED(primary.stellarLuminosity, world.orbitalRadius);
//		Determine world type
		world.worldType = determineWorldType_ADVANCED(sizeClass, world.blackbodyTemperature, 0, primary.stellarMass, primary.stellarAge, false);
//		Determine world mass
		world.worldMass = getGasGiantMass(world.worldType);
//		cout << "worldMass = " << world.worldMass << endl;
//		Determine world density
		world.worldDensity = getGasGiantDensity(world.worldType);
//		Determine world diameter
		world.worldDiameter = getGasGiantDiameter(world.worldMass, world.worldDensity);
		world.totalSurfaceArea = 0;
		world.liquidSurfaceArea = 0;
		world.landSurfaceArea = 0;
//		Determine surface gravity at cloud tops
		world.surfaceGravity = surfaceGravityCalculator(world.worldDensity, world.worldDiameter);
//		Determine orbital period
		world.orbitalPeriod = calculatePlanetaryOrbitalPeriod(world.orbitalRadius, primary.stellarMass, world.worldMass);
//		Determine orbital eccentricity
		world.orbitalEccentricity = calculatePlanetaryOrbitalEccentricity(world.worldType, primary.gasGiantArrangement, primary.snowLineRadius, world.orbitalRadius, primary.innerLimitRadius);
//		Determine minimum separation from primary
		world.minimumSeparation = calculatePlanetPrimaryMinimumSeparation(world.orbitalRadius, world.orbitalEccentricity);
//		Determine maximum separation from primary
		world.maximumSeparation = calculatePlanetPrimaryMaximumSeparation(world.orbitalRadius, world.orbitalEccentricity);
//		Determine the world's escape velocity
		world.escapeVelocity = getEscapeVelocity(world.worldMass * EARTH_MASS_IN_KG, (world.worldDiameter / 2) * (EARTH_RADIUS_IN_KM * KM_TO_M));
//		Calculate the world's sidereal rotation in standard hours
		world.rotationPeriod = calculateRotationPeriod(world.totalTidalEffect, world.orbitalPeriod, world.worldType, world.tidalLockedOrNot);
//		cout << "Got to rotationPeriod" << endl;
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
//		cout << "Got to apparentDayLength" << endl;

//		Calculate the world's axial tilt
		world.axialTilt = calculateAxialTilt();
//		cout << "Got to axialTilt" << endl;
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

//		Generate major moons in second family
		if (world.secondFamilyMajorMoons != 0)
		{
			for (int8_t i = 0; i < world.secondFamilyMajorMoons; i++)
			{
//				cout << "secondFamilyMajorMoons = " << (int)world.secondFamilyMajorMoons << endl;
//				cout << "i = " << (int)i << endl;
				world.majorMoonArray[i].moonSizeClass = moonSizeTable();
//				cout << "set moonSizeClass" << endl;
				world.majorMoonArray[i].orbitalRadius = placeMoonOrbits(world.worldDiameter, world.majorMoonArray[i].moonSizeClass, 2);
//				cout << "set orbitalRadius" << endl;
				if (i != 0)
				{
	//				Iterate through all previous moons
					for (int8_t j = 0; j < i; j++)
					{
//						cout << "abs(world.majorMoonArray[i].orbitalRadius - world.majorMoonArray[j].orbitalRadius) = " << abs(world.majorMoonArray[i].orbitalRadius - world.majorMoonArray[j].orbitalRadius) << endl;
//						cout << "worldDiameter = " << world.worldDiameter << endl;
//						cout << "j = " << (int)j << endl;
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
//				cout << "set sizeClass" << endl;
	//			Run worldBuilder_ADVANCED for each moon
				world.majorMoonArray[i] = moonBuilder(primary, world.majorMoonArray[i], world);
//				cout << "built moon" << endl;
			}
//			cout << "finished moonbuilding" << endl;
		}
//		Generate moonlets in the third family
		for (int i = 0; i < world.thirdFamilyMoonlets; i++)
		{
			world.thirdFamilyMoonletArray[i].orbitalRadius = placeMoonOrbits(world.worldDiameter, 0, 3);
		}

//		Get the world's magnetic field strength
//		cout << "about to set magneticFieldStrength" << endl;
		world.magneticFieldStrength = getMagneticField(world.worldMass, world.worldDensity, world.rotationPeriod, primary.stellarAge, world.worldType);
//		cout << "set magneticFieldStrength" << endl;
	}

	else
	{
//		World is present
		world.emptyOrNot == false;
//		Calculate blackbody temperature
//		cout << "Got to blackbody temperature" << endl;
		world.blackbodyTemperature = calculateBlackbodyTemperature_ADVANCED(primary.stellarLuminosity, world.orbitalRadius);
//		Determine world type
		world.worldType = determineWorldType_ADVANCED(sizeClass, world.blackbodyTemperature, 0, primary.stellarMass, primary.stellarAge, false);
//		cout << "worldType = " << world.worldType << endl;
//		cout << "Got to worldType" << endl;
//		Place major moons

//		Step 26: Atmosphere
//		Calculate the world's atmospheric mass (as a proportion of Earth's atmospheric mass)
		world.atmosphereMass = atmosphereMassGenerator(world.worldType);
//		cout << "Got to atmosphereMass" << endl;
//		Determine the atmosphere's composition
		world.worldAtmosphereComposition = atmosphereComposition(world.worldType);
//		cout << "Got to worldAtmosphereComposition" << endl;

//		Step 27: Hydrographic Coverage
//		Determine the world's Hydrographic coverage
		world.hydrographicCoverage = hydrographicCoverageCalculator(world.worldType);
//		cout << "Got to worldAtmosphereComposition" << endl;

//		Step 28: Climate
//		Determine the world's greenhouse factor
		world.greenhouseFactor = greenhouseFactorLookup(world.worldType, world.hydrographicCoverage);
//		cout << "Got to greenhouseFactor" << endl;
//		Determine the world's absorption factor
		world.absorptionFactor = absorptionFactorLookup(world.worldType, world.hydrographicCoverage);
//		cout << "Got to absorptionFactor" << endl;
//		Determine the world's blackbody correction
		world.blackbodyCorrection = blackbodyCorrectionCalculator(world.absorptionFactor, world.greenhouseFactor, world.atmosphereMass);
//		cout << "Got to blackbodyCorrection" << endl;
//		Determine the world's average surface temperature
		world.surfaceTemperature = averageSurfaceTemperature_ADVANCED(world.blackbodyTemperature, world.blackbodyCorrection);
//		cout << "Got to surfaceTemperature" << endl;

//		Step 29: World Sizes
//		Determine the world's density (as a proportion of Earth's density)
		world.worldDensity = worldDensityTable(world.worldType);
//		cout << "Got to worldDensity" << endl;
//		Determine the world's diameter
		world.worldDiameter = worldDiameterCalculator(world.blackbodyTemperature, world.worldDensity, world.worldType);
//		cout << "Got to worldDiameter" << endl;
//		Calculate surface area
		tie(world.totalSurfaceArea, world.liquidSurfaceArea, world.landSurfaceArea) = getSurfaceArea(world.worldDiameter, world.hydrographicCoverage);
//		Determine the world's surface gravity
		world.surfaceGravity = surfaceGravityCalculator(world.worldDensity, world.worldDiameter);
//		cout << "Got to surfaceGravity" << endl;
//		Determine the world's atmospheric pressure
		world.atmosphericPressure = atmosphericPressureCalculator(world.atmosphereMass, world.surfaceGravity, world.worldType);
//		Determine the world's mass
		world.worldMass = worldMassCalculator(world.worldDensity, world.worldDiameter);
//		cout << "Got to worldMass" << endl;

//		Step 30: Dynamic Parameters
		world.orbitalPeriod = calculatePlanetaryOrbitalPeriod(world.orbitalRadius, primary.stellarMass, world.worldMass);
//		cout << "Got to orbitalPeriod" << endl;
//		Determine the planet's orbital eccentricity
		world.orbitalEccentricity = calculatePlanetaryOrbitalEccentricity(world.worldType, primary.gasGiantArrangement, primary.snowLineRadius, world.orbitalRadius, primary.innerLimitRadius);
//		cout << "Got to orbitalEccentricity" << endl;
//		Determine the minimum separation from the primary
		world.minimumSeparation = calculatePlanetPrimaryMinimumSeparation(world.orbitalRadius, world.orbitalEccentricity);
//		cout << "Got to minimumSeparation" << endl;
//		Determine the maximum separation from the primary
		world.maximumSeparation = calculatePlanetPrimaryMaximumSeparation(world.orbitalRadius, world.orbitalEccentricity);
//		cout << "Got to maximumSeparation" << endl;
//		Determine the world's escape velocity
		world.escapeVelocity = getEscapeVelocity(world.worldMass * EARTH_MASS_IN_KG, (world.worldDiameter / 2) * (EARTH_RADIUS_IN_KM * KM_TO_M));

		world.numberOfMajorMoons = getTerrestrialMajorMoons(world.orbitalRadius, world.worldType);
		world.numberOfMajorMoons = (world.numberOfMajorMoons < 0) ? 0 : world.numberOfMajorMoons;
//		cout << "Got to numberOfMajorMoons" << endl;
//		Place moonlets
		world.terrestrialMoonlet = getTerrestrialMoonlets(world.orbitalRadius, world.worldType);
//		cout << "Got to terrestrialMoonlet" << endl;

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
//							cout << "majorMoonArray[" << i << "].orbital radius = " << world.majorMoonArray[i].orbitalRadius << endl;
//							cout << "majorMoonArray[" << j << "].orbital radius = " << world.majorMoonArray[j].orbitalRadius << endl;
//							cout << " 5 * planetDiameter = " << 5 * world.worldDiameter << endl;
//							cout << "i - j = " << world.majorMoonArray[i].orbitalRadius - world.majorMoonArray[j].orbitalRadius << endl;
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
		world.tidalForceOnPlanetByPrimary = calculateTidalForceOnPlanetByPrimary(primary.stellarMass, world.worldDiameter, world.orbitalRadius);
//		cout << "Got to tidalForceOnPlanetByPrimary" << endl;


//		Calculate the total tidal effect on the planet
		world.totalTidalEffect = calculateTotalTidalEffect(world.tidalForceOnPlanetBySatellite, world.tidalForceOnPlanetByPrimary, world.tidalForceOnSatelliteByPlanet, primary.stellarAge, world.worldMass);
//		cout << "Got to totalTidalEffect" << endl;
//		Determine if the world is tidal locked
		world.tidalLockedOrNot = (world.totalTidalEffect >= 50) ? true : false;
//		cout << "Got to tidalLockedOrNot" << endl;

//		Calculate the world's sidereal rotation in standard hours
		world.rotationPeriod = calculateRotationPeriod(world.totalTidalEffect, world.orbitalPeriod, world.worldType, world.tidalLockedOrNot);
//		cout << "Got to rotationPeriod" << endl;
//		Determine if the world has a retrograde rotation
		world.retrogradeOrNot = checkForRetrogradeRotation(POM_PLANET);
//		cout << "Got to retrogradeOrNot" << endl;
		world.equatorialRotationVelocity = getEquatorialRotationVelocity(world.worldDiameter, world.rotationPeriod);
		world.surfaceIrradiance = solarPowerAtDistance(primary.stellarRadius, world.orbitalRadius, primary.energyRadiated);
//		Local calendar
//		A negative value for apparent day length is valid even if the world's rotation is not retrograde
//		This means that the primary will rise in the west and set in the east
		world.apparentDayLength = determineLocalCalendar(world.rotationPeriod, world.retrogradeOrNot, POM_PLANET, world.orbitalPeriod, CALO_DAY_LENGTH, 0);
//		cout << "Got to apparentDayLength" << endl;

//		Calculate the world's axial tilt
		world.axialTilt = calculateAxialTilt();
//		cout << "Got to axialTilt" << endl;

//		Determine the world's volcanic activity
//		NOTE: This function takes two additional arguments for moons, but I wanted to test what happens if nothing is passed
		world.volcanicActivityLevel = volcanicActivityTable(world.worldType, world.surfaceGravity, primary.stellarAge, POM_PLANET, world.numberOfMajorMoons, 0);
//		cout << "Volcanic activity level: " << world.volcanicActivityLevel << endl;
//		cout << "Got to volcanicActivityLevel" << endl;
//		Determine the effect the world's volcanic activity has on the world's atmosphere
		world.worldAtmosphereComposition = volcanicActivityEffectOnGardenWorld(world.volcanicActivityLevel, world.worldType, world.worldAtmosphereComposition);
//		cout << "Got to volcanicActivityEffectOnGardenWorld" << endl;
//		Determine the world's tectonic activity
		world.tectonicActivityLevel = getTectonicActivity(world.worldType, world.volcanicActivityLevel, world.hydrographicCoverage, POM_PLANET, world.numberOfMajorMoons);
//		cout << "Got to tectonicActivityLevel" << endl;
//		Determine the effect of tectonic and volcanic activity on the world's habitability and resources
		tie(world.habitabilityModifier, world.resourceValueModifier) = effectsOfGeologicActivity(world.volcanicActivityLevel, world.tectonicActivityLevel, world.habitabilityModifier, world.resourceValueModifier);
//		cout << "Got to effectsOfGeologicActivity" << endl;

//		Determine the world's minimum molecular weight retained
		world.minimumMolecularWeightRetained = minimumMolecularWeightRetainedCalculator(world.blackbodyTemperature, world.worldDiameter, world.worldDensity, world.worldType);
		world.atmosphericPressureCategory = atmosphericPressureCategoriesTable(world.atmosphericPressure);
//		If the world is tide locked
		if (world.tidalLockedOrNot == true)
		{
			tie(world.atmosphericPressure, world.atmosphericPressureCategory, world.hydrographicCoverage) = tideLockedWorldEffects(world.tidalLockedOrNot, world.surfaceTemperature, world.atmosphericPressureCategory, world.atmosphericPressure, world.atmosphereMass, world.surfaceGravity, world.worldType, world.hydrographicCoverage);
		}
//		cout << "Got to tideLockedWorldEffects" << endl;
//		Check if the world is in a resonant orbit
//		If so, determine the effects that has on the world
		tie(world.resonantOrNot, world.apparentDayLength) = resonantWorldEffects(world.orbitalEccentricity, world.tidalLockedOrNot,	world.orbitalPeriod, world.apparentDayLength);
//		cout << "Got to resonantWorldEffects" << endl;
//		Get the world's magnetic field strength
		world.magneticFieldStrength = getMagneticField(world.worldMass, world.worldDensity, world.rotationPeriod, primary.stellarAge, world.worldType);
	}

/*
	if (world.worldType == WT_ASTEROID_BELT)
	{
		cout << "worldType = WT_ASTEROID_BELT" << endl;
		cout << "averageOrbitalRadius = " << world.orbitalRadius << endl;
	}
*/
//	cout << "Got to return world" << endl;
	return world;
}


//	Star design sequence
star_t starBuilder(starSystem_t starSystem, int companionStar, float companionAInnerForbiddenZone, float companionAOuterForbiddenZone, float companionBInnerForbiddenZone, float companionBOuterForbiddenZone, float companionAOrbitalRadius, float companionBOrbitalRadius, float inputLuminosity = 0)
{
//	Initialize the star
	star_t star = {0};

//	Which star is this?
	star.starNumber = companionStar;

//	Determine the star's mass
	star.stellarMass = stellarMassTable();
//	cout << "stellarMass = " << star.stellarMass << endl;
//	Determine the star's age
	star.stellarAge = starSystem.systemAge;
//	Check if star.stellarAge == 0
	if (star.stellarAge == 0) {star.stellarAge = stellarAgeTable(starSystem.gardenWorldPresent);}
//	cout << "stellarAge = " << star.stellarAge << endl;
//	Determine the star's characteristics
	star = determineStellarCharacteristics(star);
//	Calculate the energy radiated by the star
	star.energyRadiated = stefanBoltzmannCalculator(star.tableTemperature);
//	Determine the star's temperature
	star = calculateStellarTemperature(star);
//	cout << "stellarTemperature = " << star.stellarTemperature << endl;
//	Determine the star's luminosity
	star = calculateStellarLuminosity(star);
//	cout << "stellarLuminosity = " << star.stellarLuminosity << endl;
//	If the star is a white dwarf, modify the star's mass and reset the star's starType
	if (star.luminosityClass == LC_D)
	{
		int whiteDwarfMassRoll = diceRoller(6, 2) - 2;
		star.stellarMass = (whiteDwarfMassRoll * 0.05) + 0.9 + floatRNG(-0.05, 0.05);
	}

//	Determine the radius of the star
	star = determineStarRadius(star);
//	Determine the equatorial rotation velocity of the star
//	star.equatorialRotationVelocity = getEquatorialRotationVelocity(star.stellarRadius * 2, star.rotation)
//	Determine the escape velocity of the star
	star.escapeVelocity = getEscapeVelocity(star.stellarMass * SOL_MASS_IN_KG, star.stellarRadius * SOL_RADIUS_IN_KM);
//	cout << "stellarRadius = " << star.stellarRadius << endl;
//	Determine the orbital zones of the star
//	Determine the star's inner limit radius
	star.innerLimitRadius = getInnerLimitRadius(star.stellarMass, star.stellarLuminosity);
//	cout << "innerLimitRadius = " << star.innerLimitRadius << endl;
//	Determine the star's outer limit radius
	star.outerLimitRadius = getOuterLimitRadius(star.stellarMass);
//	cout << "outerLimitRadius = " << star.outerLimitRadius << endl;
//	Determine the star's snow line
	star.snowLineRadius = getSnowLine(star.lMin);
//	cout << "snow line radius = " << star.snowLineRadius << endl;

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
//	else
	{
		star = orbitalSeparationTable(starSystem.numberOfStars, companionStar, star, starSystem.gardenWorldPresent);
	}

//	cout << "innerForbiddenZone = " << star.innerForbiddenZone << endl;
//	cout << "outerForbiddenZone = " << star.outerForbiddenZone << endl;

//	Determine the star's gas giant arrangement
	star.gasGiantArrangement = gasGiantArrangementTable();
//	cout << "gasGiantArrangement = " << star.gasGiantArrangement << endl;

//	If there is no gas giant
	if (star.gasGiantArrangement == GGA_NO_GAS_GIANT)
	{
		star.firstGasGiantOrbitalRadius = 0;
		star.firstGasGiantPresent = false;
	}

//	If there is a gas giant
	else
	{
		star.firstGasGiantOrbitalRadius = placeFirstGasGiant(star.snowLineRadius, star.gasGiantArrangement);
		star.firstGasGiantPresent = true;
	}

//	if (star.firstGasGiantPresent == true) {cout << "star.firstGasGiantPresent = TRUE" << endl;}
//	else if (star.firstGasGiantPresent == false) {cout << "star.firstGasGiantPresent = FALSE" << endl;}

//	cout << "star.firstGasGiantPresent = " << star.firstGasGiantPresent << endl;

//	Determine the sequence of orbital radii for the star's planetary system
	star = placePlanetaryOrbits(star, starSystem.numberOfStars, companionAInnerForbiddenZone, companionAOuterForbiddenZone, companionBInnerForbiddenZone, companionBOuterForbiddenZone, companionAOrbitalRadius, companionBOrbitalRadius);

//	cout << "star.numberOfOrbits = " << star.numberOfOrbits << endl;



//	Populate orbital slots
//	sizeClassArray has an array of strings that categorize the world in that orbital slot
//	worldBuilder_ADVANCED is then run for each world
	star = fillOrbits(star);

/*
//	Print worlds
	if (star.numberOfOrbits != 0)
	{
		for (int index = 0; index < star.numberOfOrbits; index++)
		{
//			cout << "star.sizeClassArray[" << index << "] = " << star.sizeClassArray[index] << endl;
		}
	}
*/
//	for (int i = 0; i < star.numberOfOrbits; i++) {cout << "star.sizeClassArray[" << i << "] = " << star.sizeClassArray[i] << endl;}

//	Build the worlds around the star
	star.sizeClassIndex = 0;
	for (int index = 0; index < star.numberOfOrbits; index++)
	{
//		cout << "Worldbuilder for loop reached" << endl;
//		If the world is not a gas giant or empty
//		if (star.sizeClassArray[index] != WT_SMALL_GAS_GIANT && star.sizeClassArray[index] != WT_MEDIUM_GAS_GIANT && star.sizeClassArray[index] != WT_LARGE_GAS_GIANT && star.sizeClassArray[index] != SC_EMPTY_ORBIT)
//		if (star.sizeClassArray[index] == SC_ASTEROID_BELT || star.sizeClassArray[index] == SC_EMPTY_ORBIT || star.sizeClassArray[index] == SC_TERRESTRIAL_PLANET_SMALL || star.sizeClassArray[index] == SC_TERRESTRIAL_PLANET_STANDARD || star.sizeClassArray[index] == SC_TERRESTRIAL_PLANET_LARGE)
//		std::string sizeClassString = star.sizeClassArray[index];
//		cout << "star.sizeClassArray[" << index << "] = " << +star.sizeClassArray[index] << endl;

		if (star.sizeClassArray[index] != SC_EMPTY_ORBIT)
		{
//			cout << "Worldbuilder if loop reached" << endl;
//			Run worldBuilder_ADVANCED
			star.worldArray[star.sizeClassIndex] = worldBuilder_ADVANCED(star.sizeClassArray[index], star.orbitalRadiusArray[index], star/*, 0, 0, "", POM_PLANET*/);
			star.sizeClassIndex += 1;
		}
//		cout << "For loop ended" << endl;
	}
//	cout << "star.sizeClassIndex = " << (int)star.sizeClassIndex << endl;

//	Return the star
	return star;
}

//	Star system design sequence
starSystem_t starSystemBuilder()
{
//	Initialize the star system
	starSystem_t starSystem = {0};

//	Determine the number of stars in the system
	starSystem.numberOfStars = determineStarNumber();
//	cout << "numberOfStars = " << starSystem.numberOfStars << endl;
//	Determine the orbits of the companion stars
	starSystem = companionStarOrbits(starSystem);
//	This value is temporary
	starSystem.gardenWorldPresent = false;
	starSystem.systemAge = stellarAgeTable(starSystem.gardenWorldPresent);
//	Build the system's stars
//	For each star in the system
	for (int i = 0; i < starSystem.numberOfStars; i++)
	{
//		i is passed so that the forbidden zones can use it as a counter of the current star being worked on
//		For binary systems
		if 		(i == 0 && starSystem.numberOfStars == 2) {starSystem.stars[0] = starBuilder(starSystem, i, starSystem.stars[1].innerForbiddenZone, starSystem.stars[1].outerForbiddenZone, 0, 0, starSystem.stars[1].averageOrbitalRadius, 0);}
		else if (i == 1 && starSystem.numberOfStars == 2) {starSystem.stars[1] = starBuilder(starSystem, i, starSystem.stars[0].innerForbiddenZone, starSystem.stars[0].outerForbiddenZone, 0, 0, starSystem.stars[0].averageOrbitalRadius, 0);}

//		For trinary systems
		else if (i == 0 && starSystem.numberOfStars == 3) {starSystem.stars[0] = starBuilder(starSystem, i, starSystem.stars[1].innerForbiddenZone, starSystem.stars[1].outerForbiddenZone, starSystem.stars[2].innerForbiddenZone, starSystem.stars[2].outerForbiddenZone, starSystem.stars[1].averageOrbitalRadius, starSystem.stars[2].averageOrbitalRadius);}
		else if (i == 1 && starSystem.numberOfStars == 3) {starSystem.stars[1] = starBuilder(starSystem, i, starSystem.stars[0].innerForbiddenZone, starSystem.stars[0].outerForbiddenZone, starSystem.stars[2].innerForbiddenZone, starSystem.stars[2].outerForbiddenZone, starSystem.stars[0].averageOrbitalRadius, starSystem.stars[2].averageOrbitalRadius);}
		else if (i == 2 && starSystem.numberOfStars == 3) {starSystem.stars[2] = starBuilder(starSystem, i, starSystem.stars[0].innerForbiddenZone, starSystem.stars[0].outerForbiddenZone, starSystem.stars[1].innerForbiddenZone, starSystem.stars[1].outerForbiddenZone, starSystem.stars[0].averageOrbitalRadius, starSystem.stars[1].averageOrbitalRadius);}

//		For single stars
		else {starSystem.stars[i] = starBuilder(starSystem, i, 0, 0, 0, 0, 0, 0);}
	}

//	Calculate stellar orbital periods
	starSystem.stars[0].stellarOrbitalPeriod = 0;

//	For trinary systems
	if (starSystem.numberOfStars != 1)
	{
//		cout << "Trinary system if loop reached" << endl;
		starSystem.stars[1].stellarOrbitalPeriod = sqrt(pow(starSystem.stars[1].averageOrbitalRadius, 3) / (starSystem.stars[0].stellarMass + starSystem.stars[1].stellarMass));
		starSystem.stars[2].stellarOrbitalPeriod = sqrt(pow(starSystem.stars[2].averageOrbitalRadius, 3) / (starSystem.stars[0].stellarMass + starSystem.stars[1].stellarMass + starSystem.stars[2].stellarMass));
	}

	return starSystem;
}

int main()
{
//	for (int i = 0; i < 100; i++)
//	{
	starSystem_t starSystem = starSystemBuilder();
	printStarSystem(starSystem);
//	}
//	int starID = 32263;
//	getStarData(starID);
//	runPython(2, {"multiply.py", 2, 3})
	return 0;
}
