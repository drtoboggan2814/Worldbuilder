//	C++ libraries
#include <iostream>
#include <string>
#include <iomanip>
#include <math.h>

//	Constant declarations
#include "declarations/constants/gasGiantArrangementConstants.h"
#include "declarations/constants/luminosityClassConstants.h"
#include "declarations/constants/sizeClassConstants.h"
#include "declarations/constants/stringConstants.h"
#include "declarations/constants/unitConversions.h"
#include "declarations/constants/worldTypeConstants.h"

//	Function declarations
//#include "declarations/functions/printWorld.h"

//	Structure declarations
#include "declarations/structures/atmosphericComposition_t.h"
#include "declarations/structures/marginalAtmosphere_t.h"
#include "declarations/structures/moon_t.h"
#include "declarations/structures/moonlet_t.h"
#include "declarations/structures/orbitalSeparation_t.h"
#include "declarations/structures/world_t.h"
#include "declarations/structures/star_t.h"
#include "declarations/structures/starSystem_t.h"

//	This function prints information regarding the composition of the world's
//	atmosphere to the console
void printAtmosphereComposition(const atmosphericComposition_t& atmosphereComposition)
{
//	std::string representation of the atmosphere's toxicity
	std::string toxicity_s;
//	Convert the integer representation of the atmosphere's toxicity to a std::string
	switch (atmosphereComposition.toxicity)
	{
		case 0:
			toxicity_s = "Not toxic";
			break;
		case 1:
			toxicity_s = "Mildly toxic";
			break;
		case 2:
			toxicity_s = "Highly toxic";
			break;
		case 3:
			toxicity_s = "Lethally toxic";
			break;
	}

//	std::string representation of chlorineOrFluorine
	std::string chlorineOrFluorine_s = (atmosphereComposition.chlorineOrFluorine == 1) ? "Present" :"Absent";
//	std::string representation of lowOxygen
	std::string lowOxygen_s = (atmosphereComposition.lowOxygen == 1) ? "True" :"False";
//	std::string representation of highOxygen
	std::string highOxygen_s = (atmosphereComposition.highOxygen == 1) ? "True" :"False";
//	std::string representation of organicToxins
	std::string organicToxins_s = (atmosphereComposition.organicToxins == 1) ? "Present" :"Absent";
//	std::string representation of sulfurCompounds
	std::string sulfurCompounds_s = (atmosphereComposition.sulfurCompounds == 1) ? "Present" :"Absent";
//	std::string representation of suffocating
	std::string suffocating_s = (atmosphereComposition.suffocating == 1) ? "True" :"False";
//	std::string representation of highCarbonDioxide
	std::string highCarbonDioxide_s = (atmosphereComposition.highCarbonDioxide == 1) ? "True" :"False";
//	std::string representation of inertGases
	std::string inertGases_s = (atmosphereComposition.inertGases == 1) ? "Present" :"Absent";
//	std::string representation of nitrogenCompounds
	std::string nitrogenCompounds_s = (atmosphereComposition.nitrogenCompounds == 1) ? "Present" :"Absent";
//	std::string representation of pollutants
	std::string pollutants_s = (atmosphereComposition.pollutants == 1) ? "Present" :"Absent";
//	std::string representation of corrosive
	std::string corrosive_s = (atmosphereComposition.corrosive == 1) ? "True" :"False";

//	Print atmosphere composition
//	This should match up with printWorld
	std::cout << left << setw(48) << "Toxicity:" 			<< toxicity_s 			<< std::endl;
	std::cout << left << setw(48) << "Chlorine or fluorine:" << chlorineOrFluorine_s << std::endl;
	std::cout << left << setw(48) << "Low oxygen:" 			<< lowOxygen_s 			<< std::endl;
	std::cout << left << setw(48) << "High oxygen" 			<< highOxygen_s 		<< std::endl;
	std::cout << left << setw(48) << "Organic toxins:" 		<< organicToxins_s 		<< std::endl;
	std::cout << left << setw(48) << "Sulfur compounds:" 	<< sulfurCompounds_s 	<< std::endl;
	std::cout << left << setw(48) << "Suffocating:" 			<< suffocating_s 		<< std::endl;
	std::cout << left << setw(48) << "High carbon dioxide:" 	<< highCarbonDioxide_s 	<< std::endl;
	std::cout << left << setw(48) << "Inert gases:" 			<< inertGases_s 		<< std::endl;
	std::cout << left << setw(48) << "Nitrogen compounds:" 	<< nitrogenCompounds_s 	<< std::endl;
	std::cout << left << setw(48) << "Pollutants:" 			<< pollutants_s 		<< std::endl;
	std::cout << left << setw(48) << "Corrosive:" 			<< corrosive_s 			<< std::endl;
}

void printMoon(const moon_t& moon)
{
	bool worldTypeCanHaveAtmosphere = moon.worldType != WT_ASTEROID_BELT && moon.worldType != WT_TINY_ICE && moon.worldType != WT_TINY_SULFUR && moon.worldType != WT_TINY_SULFUR && moon.worldType != WT_SMALL_HADEAN && moon.worldType != WT_SMALL_ROCK && moon.worldType != WT_STANDARD_HADEAN && moon.worldType != WT_STANDARD_CHTHONIAN && moon.worldType != WT_LARGE_CHTHONIAN;
	std::cout << left << setw(48) << "World type:" 									<< WT_S_LOOKUP_TABLE[moon.worldType] 					  					  << std::endl;
	std::cout << left << setw(48) << "Orbital radius:" 								<< left << setw(16) << moon.orbitalRadius 					<< "planetary diameters"	<< std::endl;
	std::cout << left << setw(48) << "Orbital period:" 								<< left << setw(16) << moon.orbitalPeriod 			 		<< "days"					<< std::endl;
	std::cout << left << setw(48) << "Orbital eccentricity:"							<< moon.orbitalEccentricity 			<< std::endl;
	std::cout << left << setw(48) << "Minimum separation to primary:"				<< left << setw(16) << moon.minimumSeparation 				<< "planetary diameters"	<< std::endl;
	std::cout << left << setw(48) << "Maximum separation to primary:"				<< left << setw(16) << moon.maximumSeparation 				<< "planetary diameters"	<< std::endl;
	std::cout << left << setw(48) << "Apparent orbital cycle as seen from planet:"	<< left << setw(16) << moon.apparentSatelliteOrbitalCycle	<<	"hours" << std::endl;
	if (moon.worldType != WT_ASTEROID_BELT) 										{std::cout << left << setw(48) << "Rotation period:" 						   << left << setw(16) << moon.rotationPeriod 				  << "hours" << std::endl;}
	if (moon.retrogradeOrNot == true /*&& moon.worldType != WT_ASTEROID_BELT*/) 	{std::cout << left << setw(48) << "Moon has a retrograde rotation" 			   << std::endl;}
	std::cout << left << setw(48) << "Equatorial rotation velocity:" 						<< left << setw(16) << moon.equatorialRotationVelocity 					<< "m/s" << std::endl;
	if (moon.worldType != WT_ASTEROID_BELT && !(isinf(moon.apparentDayLength)))	{std::cout << left << setw(48) << "Apparent day length:" 					   << left << setw(16) << moon.apparentDayLength 			  << "hours" << std::endl;}
	else if (isinf(moon.apparentDayLength))										{std::cout << left << setw(48) << "No apparent day"							   << std::endl;}
	if (moon.worldType != WT_ASTEROID_BELT) 										{std::cout << left << setw(48) << "Axial tilt:" 								   << left << setw(16) << (int)moon.axialTilt 					  << "degrees" << std::endl;}
	if (moon.resonantOrNot == true && moon.worldType != WT_ASTEROID_BELT)		{std::cout << left << setw(48) << "Moon is in a resonant orbit" 				   << std::endl;}
	if (moon.tidalLockedOrNot == true && moon.worldType != WT_ASTEROID_BELT)		{std::cout << left << setw(48) << "Moon is tidal locked" 					   << std::endl;}
	std::cout << left << setw(48) << "Escape velocity:"								<< left << setw(16) << moon.escapeVelocity					<<	"m/s" << std::endl;
	if (worldTypeCanHaveAtmosphere == true) 									{std::cout << left << setw(48) << "Atmosphere mass:" 						   << left << setw(16) << moon.atmosphereMass 				  << "Earth atmospheres" << std::endl;}
//		Print the composition of the world's atmosphere (if it has one)
	if (moon.atmosphereMass != 0) 												{printAtmosphereComposition(moon.worldAtmosphereComposition);}
//		Resume printing the world's details
	if (worldTypeCanHaveAtmosphere == true) 									{std::cout << left << setw(48) << "Hydrographic coverage:" 					   << moon.hydrographicCoverage 		  << "%" << std::endl;}
																				 std::cout << left << setw(48) << "Surface temperature:" 					   << left << setw(16) << moon.surfaceTemperature 			  << "Kelvin" << std::endl;
	if (worldTypeCanHaveAtmosphere == true) 									{std::cout << left << setw(48) << "Greenhouse factor:" 						   << moon.greenhouseFactor 			  << std::endl;}
																				 std::cout << left << setw(48) << "Absorption factor:" 						   << moon.absorptionFactor 			  << std::endl;
																				 std::cout << left << setw(48) << "Blackbody temperature:" 					   << left << setw(16) << moon.blackbodyTemperature 		  << "Kelvin" << std::endl;
	if (moon.worldType != WT_ASTEROID_BELT) 										{std::cout << left << setw(48) << "Moon density:" 							   << left << setw(16) << moon.worldDensity 				  << "Earth densities" << std::endl;}
	if (moon.worldType != WT_ASTEROID_BELT) 										{std::cout << left << setw(48) << "Moon diameter:" 							   << left << setw(16) << moon.worldDiameter 				  << "Earth diameters" << std::endl;}
	if (moon.worldType != WT_ASTEROID_BELT) 										{std::cout << left << setw(48) << "Surface gravity:" 						   << left << setw(16) << moon.surfaceGravity 				  << "Earth gravities" << std::endl;}
	if (moon.worldType != WT_ASTEROID_BELT) 										{std::cout << left << setw(48) << "Moon mass:" 								   << left << setw(16) << moon.worldMass 					  << "Earth masses" << std::endl;}
	if (worldTypeCanHaveAtmosphere == true) 									{std::cout << left << setw(48) << "Atmospheric pressure:" 					   << left << setw(16) << moon.atmosphericPressure		 	  << "standard atmospheres" << std::endl;}
	if (moon.worldType != WT_ASTEROID_BELT) 										{std::cout << left << setw(48) << "Minimum molecular weight retained:"		   << left << setw(16) << moon.minimumMolecularWeightRetained << "grams per mole" << std::endl;}
	if (moon.worldType != WT_ASTEROID_BELT) 										{std::cout << left << setw(48) << "Volcanic activity level:"					   << VAL_S_LOOKUP_TABLE[moon.volcanicActivityLevel] 		  << std::endl;}
	if (moon.worldType != WT_ASTEROID_BELT) 										{std::cout << left << setw(48) << "Tectonic activity level:"					   << TAL_S_LOOKUP_TABLE[moon.tectonicActivityLevel] 		  << std::endl;}
																				 std::cout << left << setw(48) << "Resource value modifier:" 				   << (int)moon.resourceValueModifier		  << std::endl;
																				 std::cout << left << setw(48) << "Habitability modifier:" 					   << (int)moon.habitabilityModifier		  << std::endl;
	std::cout << "\nFinished printing moon" << std::endl;
}

//	This function prints information about the world in question to the console
void printWorld(const world_t& world, char sizeClass)
{
	bool isGasGiant = (world.worldType == WT_SMALL_GAS_GIANT || world.worldType == WT_MEDIUM_GAS_GIANT || world.worldType == WT_LARGE_GAS_GIANT) ? 1 : 0;
	bool worldTypeCanHaveAtmosphere = world.worldType != WT_ASTEROID_BELT && world.worldType != WT_TINY_ICE && world.worldType != WT_TINY_SULFUR && world.worldType != WT_TINY_SULFUR && world.worldType != WT_SMALL_HADEAN && world.worldType != WT_SMALL_ROCK && world.worldType != WT_STANDARD_HADEAN && world.worldType != WT_STANDARD_CHTHONIAN && world.worldType != WT_LARGE_CHTHONIAN;
	std::cout << left << setw(48) << "World type:" 						<< WT_S_LOOKUP_TABLE[world.worldType] << std::endl;
	std::cout << left << setw(48) << "Orbital radius:" 					<< left << setw(16) << world.orbitalRadius << "au's" << std::endl;
	std::cout << left << setw(48) << "Orbital period:" 					<< left << setw(16) << world.orbitalPeriod << "years" << std::endl;
	std::cout << left << setw(48) << "Orbital eccentricity:" 			<< world.orbitalEccentricity << std::endl;
	std::cout << left << setw(48) << "Minimum separation to primary:" 	<< left << setw(16) << world.minimumSeparation << "au's" << std::endl;
	std::cout << left << setw(48) << "Maximum separation to primary:" 	<< left << setw(16) << world.maximumSeparation << "au's" << std::endl;
	if (world.worldType != WT_ASTEROID_BELT) 										{std::cout << left << setw(48) << "Rotation period:" 					<< left << setw(16) << world.rotationPeriod << "hours" << std::endl;}
	if (world.retrogradeOrNot == true /*&& world.worldType != WT_ASTEROID_BELT*/) 	{std::cout << left << setw(48) << "World has a retrograde rotation" 		<< std::endl;}
	if (world.worldType != WT_ASTEROID_BELT && !(isinf(world.apparentDayLength)))	{std::cout << left << setw(48) << "Apparent day length:" 				<< left << setw(16) << world.apparentDayLength << "hours" << std::endl;}
	else if (isinf(world.apparentDayLength))										{std::cout << left << setw(48) << "No apparent day" << std::endl;}
	if (world.worldType != WT_ASTEROID_BELT) 										{std::cout << left << setw(48) << "Axial tilt:" 							<< left << setw(16) << (int)world.axialTilt << "degrees" << std::endl;}
	if (world.worldType != WT_ASTEROID_BELT) 										{std::cout << left << setw(48) << "Surface irradiance:" 								   << left << setw(16) << world.surfaceIrradiance 					  << "W/m^2" << std::endl;}
	if (world.resonantOrNot == true && world.worldType != WT_ASTEROID_BELT)			{std::cout << left << setw(48) << "World is in a resonant orbit" 		<< std::endl;}
	if (world.tidalLockedOrNot == true && world.worldType != WT_ASTEROID_BELT)		{std::cout << left << setw(48) << "World is tidal locked" 				<< std::endl;}
	if (world.worldType != WT_ASTEROID_BELT)											{std::cout << left << setw(48) << "Escape velocity:"						<< left << setw(16) << world.escapeVelocity << "m/s" << std::endl;}
	if (world.worldType != WT_ASTEROID_BELT) 										{std::cout << left << setw(48) << "Number of major moons:" 				<< (int)world.numberOfMajorMoons 			<< std::endl;}
	if (world.worldType != WT_ASTEROID_BELT) 										{std::cout << left << setw(48) << "Number of moonlets:" 					<< (int)world.terrestrialMoonlet 			<< std::endl;}
//		Physical attributes
		std::cout << left << setw(48) << "Size class:" << SC_S_LOOKUP_TABLE[(int)world.sizeClass] << std::endl;
//		std::cout << left << setw(48) << "Overall type:" << world.overallType 											<< std::endl;
	if (worldTypeCanHaveAtmosphere == true && !isGasGiant) 								{std::cout << left << setw(48) << "Atmosphere mass:" 					<< left << setw(16) << world.atmosphereMass << "Earth atmospheres" << std::endl;}
//		Print the composition of the world's atmosphere (if it has one)
	if (world.atmosphereMass != 0 && !isGasGiant) 												{printAtmosphereComposition(world.worldAtmosphereComposition);}
//		Resume printing the world's details
	if (worldTypeCanHaveAtmosphere == true && !isGasGiant) 								{std::cout << left << setw(48) << "Hydrographic coverage:" 				<< left << setw(16)	<< world.hydrographicCoverage * 100	<< "%" << std::endl;}
	if (!isGasGiant)	{std::cout << left << setw(48) << "Surface temperature:" 				<< left << setw(16) << world.surfaceTemperature << "Kelvin" << std::endl;}
	if (worldTypeCanHaveAtmosphere == true && !isGasGiant) 								{std::cout << left << setw(48) << "Greenhouse factor:" 					<< world.greenhouseFactor 				<< std::endl;}
	std::cout << left << setw(48) << "Absorption factor:" 				<< world.absorptionFactor << std::endl;
	std::cout << left << setw(48) << "Blackbody temperature:" 			<< left << setw(16) << world.blackbodyTemperature << "Kelvin" << std::endl;
	if (world.worldType != WT_ASTEROID_BELT) 									{std::cout << left << setw(48) << "World density:" 						<< left << setw(16) << world.worldDensity 					<< "Earth densities" << std::endl;}
	if (world.worldType != WT_ASTEROID_BELT) 									{std::cout << left << setw(48) << "World diameter:" 						<< left << setw(16) << world.worldDiameter 					<< "Earth diameters | " << world.worldDiameter * EARTH_RADIUS_IN_KM * 2 << " km" << std::endl;}
	if (world.worldType != WT_ASTEROID_BELT) 									{std::cout << left << setw(48) << "Total surface area:" 						<< left << setw(16) << world.totalSurfaceArea 					<< "km^2" << std::endl;}
	if (world.worldType != WT_ASTEROID_BELT && world.hydrographicCoverage != 0) {std::cout << left << setw(48) << "Liquid surface area:" 						<< left << setw(16) << world.liquidSurfaceArea 					<< "km^2" << std::endl;}
	if (world.worldType != WT_ASTEROID_BELT && world.hydrographicCoverage != 0) {std::cout << left << setw(48) << "Land surface area:" 						<< left << setw(16) << world.landSurfaceArea 					<< "km^2" << std::endl;}
	if (world.worldType != WT_ASTEROID_BELT) 									{std::cout << left << setw(48) << "Surface gravity:" 					<< left << setw(16) << world.surfaceGravity 				<< "Earth gravities" << std::endl;}
	if (world.worldType != WT_ASTEROID_BELT) 									{std::cout << left << setw(48) << "World mass:" 							<< left << setw(16) << world.worldMass 						<< "Earth masses" << std::endl;}
	if (worldTypeCanHaveAtmosphere == true && !isGasGiant) 									{std::cout << left << setw(48) << "Atmospheric pressure:" 				<< left << setw(16) << world.atmosphericPressure		 	<< "standard atmospheres" << std::endl;}
	if (world.worldType != WT_ASTEROID_BELT) 									{std::cout << left << setw(48) << "Minimum molecular weight retained:"	<< left << setw(16) << world.minimumMolecularWeightRetained << "grams per mole" << std::endl;}
	if (world.worldType != WT_ASTEROID_BELT && !isGasGiant) 									{std::cout << left << setw(48) << "Volcanic activity level:"	<< VAL_S_LOOKUP_TABLE[world.volcanicActivityLevel] << std::endl;}
	if (world.worldType != WT_ASTEROID_BELT && !isGasGiant) 									{std::cout << left << setw(48) << "Tectonic activity level:"	<< TAL_S_LOOKUP_TABLE[world.tectonicActivityLevel] << std::endl;}
	std::cout << left << setw(48) << "Resource value modifier:" 			<< (int)world.resourceValueModifier << std::endl;
	std::cout << left << setw(48) << "Habitability modifier:" 			<< (int)world.habitabilityModifier << std::endl;
	if (world.worldType != WT_ASTEROID_BELT) 									{std::cout << left << setw(48) << "Equatorial rotation velocity:" 						<< left << setw(16) << world.equatorialRotationVelocity 					<< "m/s" << std::endl;}

	if (world.numberOfMajorMoons != 0)
	{
		for (int i = 0; i < world.numberOfMajorMoons; i++)
		{
			std::cout << "\nMoon " << i + 1 << std::endl;
			printMoon(world.majorMoonArray[i]);
		}
	}
	std::cout << "\nFinished printing world" << std::endl;
}

//	Print the characteristics of a star
void printStar(const star_t& star, char numberOfStars)
{
	std::cout << setw(48) << left << "\nStar:" << left << setw(16) << (int)star.starNumber << std::endl;
	std::cout << setw(48) << left << "Stellar mass:" << left << setw(16) << star.stellarMass << " solar masses" << std::endl;
//	std::cout << setw(48) << left << "Stellar age:" << left << setw(16) << star.stellarAge << " billion years" << std::endl;
//	std::cout << setw(48) << left << "Luminosity class:" << star.luminosityClass << std::endl;
	std::cout << setw(48) << left << "Stellar luminosity:" << left << setw(16) << star.stellarLuminosity << " solar luminosities" << std::endl;
	std::cout << setw(48) << left << "Stellar temperature:" << left << setw(16) << star.stellarTemperature << " Kelvin" << std::endl;
	std::cout << setw(48) << left << "Stellar radius:" << left << setw(16) << star.stellarRadius << " au's" << std::endl;
//	std::cout << left << setw(48) << "Equatorial rotation velocity:" 						<< left << setw(16) << star.equatorialRotationVelocity 					<< "m/s" << std::endl;}
	std::cout << setw(48) << left << "Spectral type:" << left << setw(16) << star.starClassification << std::endl;
	std::cout << setw(48) << left << "Inner limit radius:" << left << setw(16) << star.innerLimitRadius << " au's" << std::endl;
	std::cout << setw(48) << left << "Outer limit radius:" << left << setw(16) << star.outerLimitRadius << " au's" << std::endl;
	std::cout << setw(48) << left << "Snow line radius:" << left << setw(16) << star.snowLineRadius << " au's" << std::endl;
	std::cout << setw(48) << left << "Gas giant arrangement:" << left << setw(16) << GGA_S_LOOKUP_TABLE[star.gasGiantArrangement] << std::endl;

	if (numberOfStars != 1)
	{
		std::cout << setw(48) << left << "Inner forbidden zone:" << left << setw(16) << star.innerForbiddenZone << " au's" << std::endl;
		std::cout << setw(48) << left << "Outer forbidden zone:" << left << setw(16) << star.outerForbiddenZone << " au's" << std::endl;
		if (star.starNumber != 0)
		{
			std::cout << setw(48) << left << "Average orbital radius:" << left << setw(16) << star.averageOrbitalRadius << " au's" << std::endl;
			std::cout << setw(48) << left << "Orbital eccentricity:" << left << setw(16) << star.orbitalEccentricity << std::endl;
			std::cout << setw(48) << left << "Minimum separation to primary:" << left << setw(16) << star.minSeparationToCompanion << " au's" << std::endl;
			std::cout << setw(48) << left << "Maximum separation to primary:" << left << setw(16) << star.maxSeparationToCompanion << " au's" << std::endl;
			std::cout << setw(48) << left << "Orbital period around primary:" << left << setw(16) << star.stellarOrbitalPeriod << " years" << std::endl;
		}
	}

//	Print the worlds around the star
	for (int index = 0; index < star.sizeClassIndex; index++)
	{
//		std::cout << "index = " << index << std::endl;
//		std::cout << "sizeClassArray[" << index << "] = " << SC_S_LOOKUP_TABLE[(int)star.sizeClassArray[index]] << std::endl;
//		std::cout << "Worldbuilder for loop reached" << std::endl;
//		If the world is not a gas giant or empty
//		if (star.sizeClassArray[index] != WT_SMALL_GAS_GIANT && star.sizeClassArray[index] != WT_MEDIUM_GAS_GIANT && star.sizeClassArray[index] != WT_LARGE_GAS_GIANT && star.sizeClassArray[index] != SC_EMPTY_ORBIT)
/*		bool validWorldType = star.worldArray[index].worldType == WT_ASTEROID_BELT || star.worldArray[index].worldType == WT_STANDARD_GARDEN || star.worldArray[index].worldType == WT_STANDARD_OCEAN || star.worldArray[index].worldType == WT_LARGE_GARDEN || star.worldArray[index].worldType == WT_LARGE_OCEAN || star.worldArray[index].worldType == WT_STANDARD_AMMONIA || star.worldArray[index].worldType == WT_STANDARD_GREENHOUSE || star.worldArray[index].worldType == WT_LARGE_AMMONIA || star.worldArray[index].worldType == WT_LARGE_GREENHOUSE || star.worldArray[index].worldType == WT_TINY_ICE || star.worldArray[index].worldType == WT_SMALL_HADEAN || star.worldArray[index].worldType == WT_SMALL_ICE || star.worldArray[index].worldType == WT_STANDARD_HADEAN || star.worldArray[index].worldType == WT_STANDARD_ICE || star.worldArray[index].worldType == WT_LARGE_ICE || star.worldArray[index].worldType == WT_TINY_SULFUR || star.worldArray[index].worldType == WT_TINY_SULFUR || star.worldArray[index].worldType == WT_SMALL_ROCK || star.worldArray[index].worldType == WT_STANDARD_CHTHONIAN || star.worldArray[index].worldType == WT_LARGE_CHTHONIAN || star.worldArray[index].worldType == WT_SMALL_GAS_GIANT || star.worldArray[index].worldType == WT_MEDIUM_GAS_GIANT || star.worldArray[index].worldType == WT_LARGE_GAS_GIANT;
		if (!validWorldType) {std::cout << "Empty Orbit" << std::endl;}
*///		if (/*validWorldType == true && */star.sizeClassArray[index] != SC_EMPTY_ORBIT)
//		{
//			std::cout << "Worldbuilder if loop reached" << std::endl;
//			Run worldBuilder_ADVANCED
			std::cout << "\nWorld " << index /*+ 1*/ << std::endl;
			printWorld(star.worldArray[index], star.sizeClassArray[index]);
	//	}
//		std::cout << "For loop ended" << std::endl;
	}

	std::cout << "\nFinished printing star" << std::endl;
}

//	Print the characteristics of a star system
void printStarSystem(const starSystem_t& starSystem)
{
	std::cout << "Debug information" << std::endl;
	std::cout << "struct starSystem_t = " << sizeof(starSystem_t) << std::endl;
	std::cout << "struct star_t = " << sizeof(star_t) << std::endl;
	std::cout << "struct world_t = " << sizeof(world_t) << std::endl;
	std::cout << "struct moon_t = " << sizeof(moon_t) << std::endl << std::endl;
	std::cout << "Star system" << std::endl;
	std::cout << "Number of stars:" << (int)starSystem.numberOfStars << std::endl;

	for (int i = 0; i < starSystem.numberOfStars; i++)
	{
		printStar(starSystem.stars[i], starSystem.numberOfStars);
	}

	std::cout << "\nFinished printing starSystem" << std::endl;
}
