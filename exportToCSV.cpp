//	C++ libraries
#include <iomanip>
#include <string>
#include <tuple>
#include "declarations/third_party/CSVWriter.h"
#include "declarations/third_party/rapidcsv.h"

//	Constants
#include "declarations/constants/stringConstants.h"

//	Structs
#include "declarations/structures/jumpPoint_t.h"
#include "declarations/structures/moon_t.h"
#include "declarations/structures/world_t.h"
#include "declarations/structures/star_t.h"
#include "declarations/structures/starSystem_t.h"

const char UNIQUE_ID_STARSSYSTEM = 0;
const char UNIQUE_ID_STAR = 1;
const char UNIQUE_ID_WORLD = 2;
const char UNIQUE_ID_MOON = 3;
const char UNIQUE_ID_MOONLET = 4;
const char UNIQUE_ID_TECTONICPLATE = 5;


//	This file outlines functions to export this program's output to .csv's
/*
	This function takes the type of id to be generated and the current id to be
	generated with.
	Each object has a hexadecimal id given by
	____		 + _	  + __		+ _		 + _		 + _
	starSystem_t   star_T	world_t	  moon_t   moonlet_t   tectonicPlate_t
*/
std::string uniqueIDCreator(char idType, int uniqueID)
{
	std::string result;
	std::string newID = std::to_string(uniqueID);

	if (idType == UNIQUE_ID_STARSSYSTEM)
	{
		result = std::string (4 - newID.length(), '0') + newID;
	}

	else if (idType == UNIQUE_ID_WORLD)
	{
		result = std::string(2 - newID.length(), '0') + newID;
	}

	return result;
}

//	tectonicPlate is not modified, so it is passed as a const reference
void exportJumpPointToCSV(const star_t& primary, int i, std::string parentID, const jumpPoint_t& jumpPoint, int jumpPointIndex)
{
	std::string uniqueID = parentID + "000" + std::to_string(i + 1);
	CSVWriter csv(",");
	csv.newRow() << uniqueID
	<< ""
	<< jumpPoint.semiMajorAxis
	<< jumpPoint.eccentricity
	<< jumpPoint.minimumSeparation
	<< jumpPoint.maximumSeparation
	<< primary.cartesianX
	<< primary.cartesianY
	<< primary.cartesianZ
	<< primary.cartesianVelocityX
	<< primary.cartesianVelocityY
	<< primary.cartesianVelocityZ
	<< primary.distanceFromSol;
	csv.writeToFile("output/jumpPoint_t_db.csv", true);
}

void jumpPointCSVHeader()
{
	CSVWriter csv(",");
	csv.newRow() << "uniqueID"
	<< "connectingJumpPoint"
	<< "semiMajorAxis"
	<< "eccentricity"
	<< "minimumSeparation"
	<< "maximumSeparation"
	<< "cartesianX"
	<< "cartesianY"
	<< "cartesianZ"
	<< "cartesianVelocityX"
	<< "cartesianVelocityY"
	<< "cartesianVelocityZ"
	<< "distanceFromSol"
	<< "distanceToConnectingPoint";
	csv.writeToFile("output/jumpPoint_t_db.csv", true);
}

/*
void exportTectonicPlateWorldToCSV(int i, int worldID, const tectonicPlate_t& tectonicPlate, rapidcsv::Document tectonicPlateWorldExport, int tectonicPlateWorldIndex)
{
	std::string uniqueID = worldID + uniqueIDCreator(UNIQUE_ID_TECTONICPLATEWORLD, (i + 1));
	tectonicPlateWorldExport.SetCell(, tectonicPlateWorldIndex, "0" + uniqueID);
	tectonicPlateWorldExport.SetCell(, tectonicPlateWorldIndex, tectonicPlate.tectonicPlateSize);
	tectonicPlateWorldExport.SetCell(	, tectonicPlateWorldIndex, tectonicPlate.tectonicPlateMovementType);
}
*/
/*
//	moonlet is not modified, so it is passed as a const reference
void exportMoonletToCSV(int i, int worldID, const moonlet_t& moonlet, rapidcsv::Document moonletExport, int moonletIndex)
{
	std::string uniqueID = std::to_string(worldID) + uniqueIDCreator(UNIQUE_ID_MOONLET, (i + 1));
	moonletExport.SetCell(0, moonletIndex, "0" + uniqueID + "0");
}
*/
//	moon is not modified, so it is passed as a const reference
void exportMoonToCSV(int i, std::string worldID, const moon_t& moon, int moonIndex/*, int jumpPointIndex*/)
{
	std::string uniqueID = worldID + std::to_string(i + 1);
	CSVWriter csv(",");
	csv.newRow() << uniqueID + "00"
	<< moon.moonName
	<< SC_S_LOOKUP_TABLE[static_cast<int>(moon.sizeClass)]
	<< WT_S_LOOKUP_TABLE[static_cast<int>(moon.worldType)]
	<< static_cast<int>(moon.resourceValueModifier)
	<< static_cast<int>(moon.habitabilityModifier)
	<< CT_S_LOOKUP_TABLE[static_cast<int>(moon.climateType)]
	<< NE_S_LOOKUP_TABLE[static_cast<int>(moon.nativeEcosphere)]
	<< moon.breathable
	<< moon.worldDensity
	<< moon.worldDiameter
	<< moon.worldMass
	<< moon.surfaceGravity
	<< VAL_S_LOOKUP_TABLE[static_cast<int>(moon.volcanicActivityLevel)]
	<< TAL_S_LOOKUP_TABLE[static_cast<int>(moon.tectonicActivityLevel)]
	<< moon.hydrographicCoverage
	<< moon.surfaceTemperature
	<< moon.dayFaceAverageTemperature
	<< moon.nightFaceAverageTemperature
	<< moon.blackbodyCorrection
	<< moon.blackbodyTemperature
	<< moon.magneticFieldStrength
	<< moon.equatorialRotationVelocity
	<< moon.totalSurfaceArea
	<< moon.landSurfaceArea
	<< moon.liquidSurfaceArea
	<< moon.atmosphereMass
	<< static_cast<int>(moon.worldAtmosphereComposition.toxicity)
	<< static_cast<int>(moon.worldAtmosphereComposition.chlorineOrFluorine)
	<< static_cast<int>(moon.worldAtmosphereComposition.lowOxygen)
	<< static_cast<int>(moon.worldAtmosphereComposition.highOxygen)
	<< static_cast<int>(moon.worldAtmosphereComposition.organicToxins)
	<< static_cast<int>(moon.worldAtmosphereComposition.sulfurCompounds)
	<< static_cast<int>(moon.worldAtmosphereComposition.suffocating)
	<< static_cast<int>(moon.worldAtmosphereComposition.highCarbonDioxide)
	<< static_cast<int>(moon.worldAtmosphereComposition.inertGases)
	<< static_cast<int>(moon.worldAtmosphereComposition.nitrogenCompounds)
	<< static_cast<int>(moon.worldAtmosphereComposition.pollutants)
	<< static_cast<int>(moon.worldAtmosphereComposition.corrosive)
	<< moon.greenhouseFactor
	<< moon.absorptionFactor
	<< moon.atmosphericPressure
	<< APC_S_LOOKUP_TABLE[static_cast<int>(moon.atmosphericPressureCategory)]
	<< moon.minimumMolecularWeightRetained
	<< moon.orbitalRadius
	<< moon.orbitalPeriod
	<< moon.orbitalEccentricity
	<< moon.minimumSeparation
	<< moon.maximumSeparation
	<< moon.rotationPeriod
	<< moon.retrogradeOrNot
	<< moon.apparentDayLength
	<< static_cast<int>(moon.axialTilt)
	<< moon.resonantOrNot
	<< moon.tidalLockedOrNot
	<< moon.escapeVelocity
	<< moon.tidalForceOnSatelliteByPlanet
	<< moon.totalTidalEffect
	<< static_cast<int>(moon.hexesPerSide)
	<< static_cast<int>(moon.totalHexes)
	<< static_cast<int>(moon.waterHexCount)
	<< static_cast<int>(moon.landHexCount)
	<< static_cast<int>(moon.numberOfMajorOceans)
	<< static_cast<int>(moon.numberOfMinorOceans)
	<< static_cast<int>(moon.numberOfSmallSeas)
	<< static_cast<int>(moon.numberOfScatteredLakes)
	<< static_cast<int>(moon.numberOfMajorContinents)
	<< static_cast<int>(moon.numberOfMinorContinents)
	<< static_cast<int>(moon.numberOfMajorIslands)
	<< static_cast<int>(moon.numberOfArchipelagoes)
	<< static_cast<int>(moon.tectonicPlateCount);

	csv.writeToFile("output/moon_t_db.csv", true);
/*
	for (int i = 0; i < moon.tectonicPlateCount; i++)
	{
		exportTectonicPlateToCSV(i, uniqueID, moon.tectonicPlateArray[i], jumpPointIndex);
		jumpPointIndex++;
	}
*/
//	return jumpPointIndex;
}

void moonCSVHeader()
{
	CSVWriter csv(",");
	csv.newRow() << "uniqueID"
	<< "moonName"
	<< "sizeClass"
	<< "worldType"
	<< "resourceValueModifier"
	<< "habitabilityModifier"
	<< "nativeEcosphere"
	<< "climateType"
	<< "breathable"
	<< "worldDensity"
	<< "worldDiameter"
	<< "worldMass"
	<< "surfaceGravity"
	<< "volcanicActivityLevel"
	<< "tectonicActivityLevel"
	<< "hydrographicCoverage"
	<< "surfaceTemperature"
	<< "dayFaceAverageTemperature"
	<< "nightFaceAverageTemperature"
	<< "blackbodyCorrection"
	<< "blackbodyTemperature"
	<< "magneticFieldStrength"
	<< "equatorialRotationVelocity"
	<< "totalSurfaceArea"
	<< "landSurfaceArea"
	<< "liquidSurfaceArea"
	<< "atmosphereMass"
	<< "worldAtmosphereComposition.toxicity"
	<< "worldAtmosphereComposition.chlorineOrFluorine"
	<< "worldAtmosphereComposition.lowOxygen"
	<< "worldAtmosphereComposition.highOxygen"
	<< "worldAtmosphereComposition.organicToxins"
	<< "worldAtmosphereComposition.sulfurCompounds"
	<< "worldAtmosphereComposition.suffocating"
	<< "worldAtmosphereComposition.highCarbonDioxide"
	<< "worldAtmosphereComposition.inertGases"
	<< "worldAtmosphereComposition.nitrogenCompounds"
	<< "worldAtmosphereComposition.pollutants"
	<< "worldAtmosphereComposition.corrosive"
	<< "greenhouseFactor"
	<< "absorptionFactor"
	<< "atmosphericPressure"
	<< "atmosphericPressureCategory"
	<< "minimumMolecularWeightRetained"
	<< "orbitalRadius"
	<< "orbitalPeriod"
	<< "orbitalEccentricity"
	<< "minimumSeparation"
	<< "maximumSeparation"
	<< "rotationPeriod"
	<< "retrogradeOrNot"
	<< "apparentDayLength"
	<< "axialTilt"
	<< "resonantOrNot"
	<< "tidalLockedOrNot"
	<< "escapeVelocity"
	<< "tidalForceOnSatelliteByPlanet"
	<< "totalTidalEffect"
	<< "hexesPerSide"
	<< "totalHexes"
	<< "waterHexCount"
	<< "landHexCount"
	<< "numberOfMajorOceans"
	<< "numberOfMinorOceans"
	<< "numberOfSmallSeas"
	<< "numberOfScatteredLakes"
	<< "numberOfMajorContinents"
	<< "numberOfMinorContinents"
	<< "numberOfMajorIslands"
	<< "numberOfArchipelagoes"
	<< "tectonicPlateCount";

	csv.writeToFile("output/moon_t_db.csv", true);

}

//	world is not modified, so it is passed as a const reference
int exportPlanetToCSV(int i, std::string starID, const world_t& world, int worldIndex, int moonIndex)
{
	std::string uniqueID = starID + uniqueIDCreator(UNIQUE_ID_WORLD, (i + 1));
	//	Assign attributes
	CSVWriter csv(",");
	csv.newRow() << uniqueID + "000"
	<< world.planetDBIndex
	<< world.planetName
	<< SC_S_LOOKUP_TABLE[static_cast<int>(world.sizeClass)]
	<< world.randomWorld
	<< static_cast<int>(world.overallType)
	<< WT_S_LOOKUP_TABLE[static_cast<int>(world.worldType)]
	<< static_cast<int>(world.resourceValueModifier)
	<< static_cast<int>(world.habitabilityModifier)
	<< CT_S_LOOKUP_TABLE[static_cast<int>(world.climateType)]
	<< NE_S_LOOKUP_TABLE[static_cast<int>(world.nativeEcosphere)]
	<< world.breathable
	<< world.worldDensity
	<< world.worldDiameter
	<< world.worldMass
	<< world.surfaceGravity
	<< VAL_S_LOOKUP_TABLE[static_cast<int>(world.volcanicActivityLevel)]
	<< TAL_S_LOOKUP_TABLE[static_cast<int>(world.tectonicActivityLevel)]
	<< world.hydrographicCoverage
	<< world.surfaceTemperature
	<< world.dayFaceAverageTemperature
	<< world.nightFaceAverageTemperature
	<< world.blackbodyCorrection
	<< world.blackbodyTemperature
	<< world.magneticFieldStrength
	<< world.equatorialRotationVelocity
	<< world.surfaceIrradiance
	<< world.totalSurfaceArea
	<< world.landSurfaceArea
	<< world.liquidSurfaceArea
	<< world.atmosphereMass
	<< static_cast<int>(world.worldAtmosphereComposition.toxicity)
	<< static_cast<int>(world.worldAtmosphereComposition.chlorineOrFluorine)
	<< static_cast<int>(world.worldAtmosphereComposition.lowOxygen)
	<< static_cast<int>(world.worldAtmosphereComposition.highOxygen)
	<< static_cast<int>(world.worldAtmosphereComposition.organicToxins)
	<< static_cast<int>(world.worldAtmosphereComposition.sulfurCompounds)
	<< static_cast<int>(world.worldAtmosphereComposition.suffocating)
	<< static_cast<int>(world.worldAtmosphereComposition.highCarbonDioxide)
	<< static_cast<int>(world.worldAtmosphereComposition.inertGases)
	<< static_cast<int>(world.worldAtmosphereComposition.nitrogenCompounds)
	<< static_cast<int>(world.worldAtmosphereComposition.pollutants)
	<< static_cast<int>(world.worldAtmosphereComposition.corrosive)
	<< world.greenhouseFactor
	<< world.absorptionFactor
	<< world.atmosphericPressure
	<< APC_S_LOOKUP_TABLE[static_cast<int>(world.atmosphericPressureCategory)]
	<< world.minimumMolecularWeightRetained
	<< world.orbitalRadius
	<< world.orbitalPeriod
	<< world.orbitalEccentricity
	<< world.minimumSeparation
	<< world.maximumSeparation
	<< world.rotationPeriod
	<< world.retrogradeOrNot
	<< world.apparentDayLength
	<< static_cast<int>(world.axialTilt)
	<< world.resonantOrNot
	<< world.tidalLockedOrNot
	<< world.escapeVelocity
	<< static_cast<int>(world.numberOfMajorMoons)
	<< static_cast<int>(world.terrestrialMoonlet)
	<< world.tidalForceOnPlanetByPrimary
	<< world.totalTidalEffect
	<< static_cast<int>(world.firstFamilyMoonlets)
	<< static_cast<int>(world.secondFamilyMajorMoons)
	<< static_cast<int>(world.thirdFamilyMoonlets)
	<< static_cast<int>(world.ringSystemVisibility)
	<< world.gasGiantTinySulfurPresent
	<< static_cast<int>(world.hexesPerSide)
	<< static_cast<int>(world.totalHexes)
	<< static_cast<int>(world.waterHexCount)
	<< static_cast<int>(world.landHexCount)
	<< static_cast<int>(world.numberOfMajorOceans)
	<< static_cast<int>(world.numberOfMinorOceans)
	<< static_cast<int>(world.numberOfSmallSeas)
	<< static_cast<int>(world.numberOfScatteredLakes)
	<< static_cast<int>(world.numberOfMajorContinents)
	<< static_cast<int>(world.numberOfMinorContinents)
	<< static_cast<int>(world.numberOfMajorIslands)
	<< static_cast<int>(world.numberOfArchipelagoes)
	<< static_cast<int>(world.tectonicPlateCount);

	csv.writeToFile("output/world_t_db.csv", true);
/*
	for (int i = 0; i < world.tectonicPlateCount; i++)
	{
		exportTectonicPlateToCSV(i, (uniqueID + "0"), world.tectonicPlateArray[i], jumpPointIndex);
		jumpPointIndex++;
	}
*/
	for (int i = 0; i < world.numberOfMajorMoons; i++)
	{
		exportMoonToCSV(i, uniqueID, world.majorMoonArray[i], moonIndex);
		moonIndex++;
	}
/*
	for (int i = 0; i < world.terrestrialMoonlet; i++)
	{
		exportMoonletToCSV(i, std::stoi(uniqueID), world.moonlets[i], moonletExport, moonletIndex);
		moonletIndex++;
	}
*/
	return moonIndex;

}

void worldCSVHeader()
{
	CSVWriter csv(",");
	csv.newRow() << "uniqueID"
	<< "planetDBIndex"
	<< "planetName"
	<< "sizeClass"
	<< "randomWorld"
	<< "overallType"
	<< "worldType"
	<< "resourceValueModifier"
	<< "habitabilityModifier"
	<< "climateType"
	<< "nativeEcosphere"
	<< "breathable"
	<< "worldDensity"
	<< "worldDiameter"
	<< "worldMass"
	<< "surfaceGravity"
	<< "volcanicActivityLevel"
	<< "tectonicActivityLevel"
	<< "hydrographicCoverage"
	<< "surfaceTemperature"
	<< "dayFaceAverageTemperature"
	<< "nightFaceAverageTemperature"
	<< "blackbodyCorrection"
	<< "blackbodyTemperature"
	<< "magneticFieldStrength"
	<< "equatorialRotationVelocity"
	<< "surfaceIrradiance"
	<< "totalSurfaceArea"
	<< "landSurfaceArea"
	<< "liquidSurfaceArea"
	<< "atmosphereMass"
	<< "worldAtmosphereComposition.toxicity"
	<< "worldAtmosphereComposition.chlorineOrFluorine"
	<< "worldAtmosphereComposition.lowOxygen"
	<< "worldAtmosphereComposition.highOxygen"
	<< "worldAtmosphereComposition.organicToxins"
	<< "worldAtmosphereComposition.sulfurCompounds"
	<< "worldAtmosphereComposition.suffocating"
	<< "worldAtmosphereComposition.highCarbonDioxide"
	<< "worldAtmosphereComposition.inertGases"
	<< "worldAtmosphereComposition.nitrogenCompounds"
	<< "worldAtmosphereComposition.pollutants"
	<< "worldAtmosphereComposition.corrosive"
	<< "greenhouseFactor"
	<< "absorptionFactor"
	<< "atmosphericPressure"
	<< "atmosphericPressureCategory"
	<< "minimumMolecularWeightRetained"
	<< "orbitalRadius"
	<< "orbitalPeriod"
	<< "orbitalEccentricity"
	<< "minimumSeparation"
	<< "maximumSeparation"
	<< "rotationPeriod"
	<< "retrogradeOrNot"
	<< "apparentDayLength"
	<< "axialTilt"
	<< "resonantOrNot"
	<< "tidalLockedOrNot"
	<< "escapeVelocity"
	<< "numberOfMajorMoons"
	<< "terrestrialMoonlet"
	<< "tidalForceOnPlanetByPrimary"
	<< "totalTidalEffect"
	<< "firstFamilyMoonlets"
	<< "secondFamilyMajorMoons"
	<< "thirdFamilyMoonlets"
	<< "ringSystemVisibility"
	<< "gasGiantTinySulfurPresent"
	<< "hexesPerSid"
	<< "totalHexe"
	<< "waterHexCoun"
	<< "landHexCoun"
	<< "numberOfMajorOcean"
	<< "numberOfMinorOcean"
	<< "numberOfSmallSea"
	<< "numberOfScatteredLake"
	<< "numberOfMajorContinent"
	<< "numberOfMinorContinent"
	<< "numberOfMajorIsland"
	<< "numberOfArchipelagoes"
	<< "tectonicPlateCount";

	csv.writeToFile("output/world_t_db.csv", true);
}

//	star is not modified, so it is passed as a const reference
std::tuple <int, int, int> exportStarToCSV(int starIndex, std::string starSystemID, const star_t& star, int worldIndex, int moonIndex, int jumpPointIndex)
{
	std::string uniqueID = starSystemID + std::to_string(star.starNumber + 1);
//	Assign attributes
	CSVWriter csv(",");
	csv.newRow() << uniqueID + "00000"
	<< star.hygIndex
	<< star.hipIndex
	<< star.hdIndex
	<< star.glieseIndex
	<< star.properName
	<< star.bayerDesignation
	<< star.flamsteedDesignation
	<< star.starConstellation
	<< star.cartesianX
	<< star.cartesianY
	<< star.cartesianZ
	<< star.cartesianVelocityX
	<< star.cartesianVelocityY
	<< star.cartesianVelocityZ
	<< star.distanceFromSol
	<< static_cast<int>(star.starColor_r)
	<< static_cast<int>(star.starColor_g)
	<< static_cast<int>(star.starColor_b)
	<< star.harvardLetter
	<< star.yerkesClassification
	<< star.numericValue
	<< star.starClassification
	<< star.stellarOrbitalPeriod
	<< star.escapeVelocity
	<< star.numberOfCSVPlanets
	<< static_cast<int>(star.numberOfPlanets)
	<< static_cast<int>(star.starNumber)
	<< star.stellarMass
	<< star.stellarAge
	<< star.stellarLuminosity
	<< star.stellarTemperature
	<< star.stellarRadius
	<< star.equatorialRotationVelocity
	<< star.energyRadiated
	<< star.innerLimitRadius
	<< star.outerLimitRadius
	<< star.snowLineRadius
	<< star.averageOrbitalRadius
	<< star.orbitalEccentricity
	<< star.minSeparationToCompanion
	<< star.maxSeparationToCompanion
	<< star.innerForbiddenZone
	<< star.outerForbiddenZone
	<< star.numberofJumpPoints
	<< GGA_S_LOOKUP_TABLE[static_cast<int>(star.gasGiantArrangement)];

	csv.writeToFile("output/star_t_db.csv", true);

	for (int i = 0; i < star.numberOfPlanets; i++)
	{
		moonIndex = exportPlanetToCSV(i, uniqueID, star.worldArray[i], worldIndex, moonIndex);
		worldIndex++;
	}

	for (int i = 0; i < star.numberofJumpPoints; i++)
	{
		exportJumpPointToCSV(star, i, uniqueID, star.jumpPointArray[i], jumpPointIndex);
		jumpPointIndex++;
	}

	return make_tuple(worldIndex, moonIndex, jumpPointIndex);

}

void starCSVHeader()
{
	CSVWriter csv(",");
	csv.newRow() << "uniqueID"
	<< "hygIndex"
	<< "hipIndex"
	<< "hdIndex"
	<< "glieseIndex"
	<< "properName"
	<< "bayerDesignation"
	<< "flamsteedDesignation"
	<< "starConstellation"
	<< "cartesianX"
	<< "cartesianY"
	<< "cartesianZ"
	<< "cartesianVelocityX"
	<< "cartesianVelocityY"
	<< "cartesianVelocityZ"
	<< "distanceFromSol"
	<< "starColor_r"
	<< "starColor_g"
	<< "starColor_b"
	<< "harvardLetter"
	<< "yerkesClassification"
	<< "numericValue"
	<< "starClassification"
	<< "stellarOrbitalPeriod"
	<< "escapeVelocity"
	<< "numberOfCSVPlanets"
	<< "numberOfPlanets"
	<< "starNumber"
	<< "stellarMass"
	<< "stellarAge"
	<< "stellarLuminosity"
	<< "stellarTemperature"
	<< "stellarRadius"
	<< "equatorialRotationVelocity"
	<< "energyRadiated"
	<< "innerLimitRadius"
	<< "outerLimitRadius"
	<< "snowLineRadius"
	<< "averageOrbitalRadius"
	<< "orbitalEccentricity"
	<< "minSeparationToCompanion"
	<< "maxSeparationToCompanion"
	<< "innerForbiddenZone"
	<< "outerForbiddenZone"
	<< "numberofJumpPoints"
	<< "gasGiantArrangement";

	csv.writeToFile("output/star_t_db.csv", true);
}

//	starSystem is not modified, so it is passed as a const reference
std::tuple <int, int, int, int> exportStarSystemToCSV(const starSystem_t& starSystem, int starSystemIndex, int starIndex, int worldIndex, int moonIndex, int jumpPointIndex)
{
	std::string uniqueID = uniqueIDCreator(UNIQUE_ID_STARSSYSTEM, starSystemIndex);
//	Assign attributes
	CSVWriter csv(",");
	csv.newRow() << uniqueID + "000000"
	<< static_cast<int>(starSystem.numberOfStars)
	<< starSystem.systemAge
	<< starSystem.gardenWorldPresent
	<< starSystem.cartesianX
	<< starSystem.cartesianY
	<< starSystem.cartesianZ
	<< starSystem.cartesianVelocityX
	<< starSystem.cartesianVelocityY
	<< starSystem.cartesianVelocityZ;

	csv.writeToFile("output/starSystem_t_db.csv", true);

//	Assign stars
	for (int i = 0; i < starSystem.numberOfStars; i++)
	{
		std::tie(worldIndex, moonIndex, jumpPointIndex) = exportStarToCSV(starIndex, uniqueID, starSystem.stars[i], worldIndex, moonIndex, jumpPointIndex);
		starIndex++;
	}

	return make_tuple(starIndex, worldIndex, moonIndex, jumpPointIndex);
}

void starSystemCSVHeader()
{
	CSVWriter csv(",");
	csv.newRow() << "uniqueID"
	<< "numberOfStars"
	<< "systemAge"
	<< "gardenWorldPresent"
	<< "cartesianX"
	<< "cartesianY"
	<< "cartesianZ"
	<< "cartesianVelocityX"
	<< "cartesianVelocityY"
	<< "cartesianVelocityZ";

	csv.writeToFile("output/starSystem_t_db.csv", true);
}
