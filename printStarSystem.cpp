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

using namespace std;

const string SPECTRAL_TYPE_LOOKUP_TABLE[34] = {"M7", "M6", "M5", "M4", "M4", "M3", "M2", "M1", "M0", "K8", "K6", "K5", "K4", "K2", "K0", "G8", "G6", "G4", "G2", "G1", "G0", "F9", "F8", "F7", "F6", "F5", "F4", "F3", "F2", "F0", "A9", "A7", "A6", "A5"};

//	This function prints information regarding the composition of the world's
//	atmosphere to the console
void printAtmosphereComposition(atmosphericComposition_t atmosphereComposition)
{
//	String representation of the atmosphere's toxicity
	string toxicity_s;
//	Convert the integer representation of the atmosphere's toxicity to a string
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

//	String representation of chlorineOrFluorine
	string chlorineOrFluorine_s = (atmosphereComposition.chlorineOrFluorine == 1) ? "Present" :"Absent";
//	String representation of lowOxygen
	string lowOxygen_s = (atmosphereComposition.lowOxygen == 1) ? "True" :"False";
//	String representation of highOxygen
	string highOxygen_s = (atmosphereComposition.highOxygen == 1) ? "True" :"False";
//	String representation of organicToxins
	string organicToxins_s = (atmosphereComposition.organicToxins == 1) ? "Present" :"Absent";
//	String representation of sulfurCompounds
	string sulfurCompounds_s = (atmosphereComposition.sulfurCompounds == 1) ? "Present" :"Absent";
//	String representation of suffocating
	string suffocating_s = (atmosphereComposition.suffocating == 1) ? "True" :"False";
//	String representation of highCarbonDioxide
	string highCarbonDioxide_s = (atmosphereComposition.highCarbonDioxide == 1) ? "True" :"False";
//	String representation of inertGases
	string inertGases_s = (atmosphereComposition.inertGases == 1) ? "Present" :"Absent";
//	String representation of nitrogenCompounds
	string nitrogenCompounds_s = (atmosphereComposition.nitrogenCompounds == 1) ? "Present" :"Absent";
//	String representation of pollutants
	string pollutants_s = (atmosphereComposition.pollutants == 1) ? "Present" :"Absent";
//	String representation of corrosive
	string corrosive_s = (atmosphereComposition.corrosive == 1) ? "True" :"False";

//	Print atmosphere composition
//	This should match up with printWorld
	cout << left << setw(48) << "Toxicity:" 			<< toxicity_s 			<< endl;
	cout << left << setw(48) << "Chlorine or fluorine:" << chlorineOrFluorine_s << endl;
	cout << left << setw(48) << "Low oxygen:" 			<< lowOxygen_s 			<< endl;
	cout << left << setw(48) << "High oxygen" 			<< highOxygen_s 		<< endl;
	cout << left << setw(48) << "Organic toxins:" 		<< organicToxins_s 		<< endl;
	cout << left << setw(48) << "Sulfur compounds:" 	<< sulfurCompounds_s 	<< endl;
	cout << left << setw(48) << "Suffocating:" 			<< suffocating_s 		<< endl;
	cout << left << setw(48) << "High carbon dioxide:" 	<< highCarbonDioxide_s 	<< endl;
	cout << left << setw(48) << "Inert gases:" 			<< inertGases_s 		<< endl;
	cout << left << setw(48) << "Nitrogen compounds:" 	<< nitrogenCompounds_s 	<< endl;
	cout << left << setw(48) << "Pollutants:" 			<< pollutants_s 		<< endl;
	cout << left << setw(48) << "Corrosive:" 			<< corrosive_s 			<< endl;
}

void printMoon(moon_t moon)
{
	bool worldTypeCanHaveAtmosphere = moon.worldType != WT_ASTEROID_BELT && moon.worldType != WT_TINY_ICE && moon.worldType != WT_TINY_SULFUR && moon.worldType != WT_TINY_SULFUR && moon.worldType != WT_SMALL_HADEAN && moon.worldType != WT_SMALL_ROCK && moon.worldType != WT_STANDARD_HADEAN && moon.worldType != WT_STANDARD_CHTHONIAN && moon.worldType != WT_LARGE_CHTHONIAN;
	cout << left << setw(48) << "World type:" 									<< WT_S_LOOKUP_TABLE[moon.worldType] 					  					  << endl;
	cout << left << setw(48) << "Orbital radius:" 								<< left << setw(16) << moon.orbitalRadius 					<< "planetary diameters"	<< endl;
	cout << left << setw(48) << "Orbital period:" 								<< left << setw(16) << moon.orbitalPeriod 			 		<< "days"					<< endl;
	cout << left << setw(48) << "Orbital eccentricity:"							<< moon.orbitalEccentricity 			<< endl;
	cout << left << setw(48) << "Minimum separation to primary:"				<< left << setw(16) << moon.minimumSeparation 				<< "planetary diameters"	<< endl;
	cout << left << setw(48) << "Maximum separation to primary:"				<< left << setw(16) << moon.maximumSeparation 				<< "planetary diameters"	<< endl;
	cout << left << setw(48) << "Apparent orbital cycle as seen from planet:"	<< left << setw(16) << moon.apparentSatelliteOrbitalCycle	<<	"hours" << endl;
	if (moon.worldType != WT_ASTEROID_BELT) 										{cout << left << setw(48) << "Rotation period:" 						   << left << setw(16) << moon.rotationPeriod 				  << "hours" << endl;}
	if (moon.retrogradeOrNot == true /*&& moon.worldType != WT_ASTEROID_BELT*/) 	{cout << left << setw(48) << "Moon has a retrograde rotation" 			   << endl;}
	cout << left << setw(48) << "Equatorial rotation velocity:" 						<< left << setw(16) << moon.equatorialRotationVelocity 					<< "m/s" << endl;
	if (moon.worldType != WT_ASTEROID_BELT && !(isinf(moon.apparentDayLength)))	{cout << left << setw(48) << "Apparent day length:" 					   << left << setw(16) << moon.apparentDayLength 			  << "hours" << endl;}
	else if (isinf(moon.apparentDayLength))										{cout << left << setw(48) << "No apparent day"							   << endl;}
	if (moon.worldType != WT_ASTEROID_BELT) 										{cout << left << setw(48) << "Axial tilt:" 								   << left << setw(16) << (int)moon.axialTilt 					  << "degrees" << endl;}
	if (moon.resonantOrNot == true && moon.worldType != WT_ASTEROID_BELT)		{cout << left << setw(48) << "Moon is in a resonant orbit" 				   << endl;}
	if (moon.tidalLockedOrNot == true && moon.worldType != WT_ASTEROID_BELT)		{cout << left << setw(48) << "Moon is tidal locked" 					   << endl;}
	cout << left << setw(48) << "Escape velocity:"								<< left << setw(16) << moon.escapeVelocity					<<	"m/s" << endl;
	if (worldTypeCanHaveAtmosphere == true) 									{cout << left << setw(48) << "Atmosphere mass:" 						   << left << setw(16) << moon.atmosphereMass 				  << "Earth atmospheres" << endl;}
//		Print the composition of the world's atmosphere (if it has one)
	if (moon.atmosphereMass != 0) 												{printAtmosphereComposition(moon.worldAtmosphereComposition);}
//		Resume printing the world's details
	if (worldTypeCanHaveAtmosphere == true) 									{cout << left << setw(48) << "Hydrographic coverage:" 					   << moon.hydrographicCoverage 		  << "%" << endl;}
																				 cout << left << setw(48) << "Surface temperature:" 					   << left << setw(16) << moon.surfaceTemperature 			  << "Kelvin" << endl;
	if (worldTypeCanHaveAtmosphere == true) 									{cout << left << setw(48) << "Greenhouse factor:" 						   << moon.greenhouseFactor 			  << endl;}
																				 cout << left << setw(48) << "Absorption factor:" 						   << moon.absorptionFactor 			  << endl;
																				 cout << left << setw(48) << "Blackbody temperature:" 					   << left << setw(16) << moon.blackbodyTemperature 		  << "Kelvin" << endl;
	if (moon.worldType != WT_ASTEROID_BELT) 										{cout << left << setw(48) << "Moon density:" 							   << left << setw(16) << moon.worldDensity 				  << "Earth densities" << endl;}
	if (moon.worldType != WT_ASTEROID_BELT) 										{cout << left << setw(48) << "Moon diameter:" 							   << left << setw(16) << moon.worldDiameter 				  << "Earth diameters" << endl;}
	if (moon.worldType != WT_ASTEROID_BELT) 										{cout << left << setw(48) << "Surface gravity:" 						   << left << setw(16) << moon.surfaceGravity 				  << "Earth gravities" << endl;}
	if (moon.worldType != WT_ASTEROID_BELT) 										{cout << left << setw(48) << "Moon mass:" 								   << left << setw(16) << moon.worldMass 					  << "Earth masses" << endl;}
	if (worldTypeCanHaveAtmosphere == true) 									{cout << left << setw(48) << "Atmospheric pressure:" 					   << left << setw(16) << moon.atmosphericPressure		 	  << "standard atmospheres" << endl;}
	if (moon.worldType != WT_ASTEROID_BELT) 										{cout << left << setw(48) << "Minimum molecular weight retained:"		   << left << setw(16) << moon.minimumMolecularWeightRetained << "grams per mole" << endl;}
	if (moon.worldType != WT_ASTEROID_BELT) 										{cout << left << setw(48) << "Volcanic activity level:"					   << VAL_S_LOOKUP_TABLE[moon.volcanicActivityLevel] 		  << endl;}
	if (moon.worldType != WT_ASTEROID_BELT) 										{cout << left << setw(48) << "Tectonic activity level:"					   << TAL_S_LOOKUP_TABLE[moon.tectonicActivityLevel] 		  << endl;}
																				 cout << left << setw(48) << "Resource value modifier:" 				   << (int)moon.resourceValueModifier		  << endl;
																				 cout << left << setw(48) << "Habitability modifier:" 					   << (int)moon.habitabilityModifier		  << endl;

}

//	This function prints information about the world in question to the console
void printWorld(world_t world, char sizeClass)
{
	bool isGasGiant = (world.worldType == WT_SMALL_GAS_GIANT || world.worldType == WT_MEDIUM_GAS_GIANT || world.worldType == WT_LARGE_GAS_GIANT) ? 1 : 0;
	bool worldTypeCanHaveAtmosphere = world.worldType != WT_ASTEROID_BELT && world.worldType != WT_TINY_ICE && world.worldType != WT_TINY_SULFUR && world.worldType != WT_TINY_SULFUR && world.worldType != WT_SMALL_HADEAN && world.worldType != WT_SMALL_ROCK && world.worldType != WT_STANDARD_HADEAN && world.worldType != WT_STANDARD_CHTHONIAN && world.worldType != WT_LARGE_CHTHONIAN;
	cout << left << setw(48) << "World type:" 						<< WT_S_LOOKUP_TABLE[world.worldType] << endl;
	cout << left << setw(48) << "Orbital radius:" 					<< left << setw(16) << world.orbitalRadius << "au's" << endl;
	cout << left << setw(48) << "Orbital period:" 					<< left << setw(16) << world.orbitalPeriod << "years" << endl;
	cout << left << setw(48) << "Orbital eccentricity:" 			<< world.orbitalEccentricity << endl;
	cout << left << setw(48) << "Minimum separation to primary:" 	<< left << setw(16) << world.minimumSeparation << "au's" << endl;
	cout << left << setw(48) << "Maximum separation to primary:" 	<< left << setw(16) << world.maximumSeparation << "au's" << endl;
	if (world.worldType != WT_ASTEROID_BELT) 										{cout << left << setw(48) << "Rotation period:" 					<< left << setw(16) << world.rotationPeriod << "hours" << endl;}
	if (world.retrogradeOrNot == true /*&& world.worldType != WT_ASTEROID_BELT*/) 	{cout << left << setw(48) << "World has a retrograde rotation" 		<< endl;}
	if (world.worldType != WT_ASTEROID_BELT && !(isinf(world.apparentDayLength)))	{cout << left << setw(48) << "Apparent day length:" 				<< left << setw(16) << world.apparentDayLength << "hours" << endl;}
	else if (isinf(world.apparentDayLength))										{cout << left << setw(48) << "No apparent day" << endl;}
	if (world.worldType != WT_ASTEROID_BELT) 										{cout << left << setw(48) << "Axial tilt:" 							<< left << setw(16) << (int)world.axialTilt << "degrees" << endl;}
	if (world.worldType != WT_ASTEROID_BELT) 										{cout << left << setw(48) << "Surface irradiance:" 								   << left << setw(16) << world.surfaceIrradiance 					  << "W/m^2" << endl;}
	if (world.resonantOrNot == true && world.worldType != WT_ASTEROID_BELT)			{cout << left << setw(48) << "World is in a resonant orbit" 		<< endl;}
	if (world.tidalLockedOrNot == true && world.worldType != WT_ASTEROID_BELT)		{cout << left << setw(48) << "World is tidal locked" 				<< endl;}
	if (world.worldType != WT_ASTEROID_BELT)											{cout << left << setw(48) << "Escape velocity:"						<< left << setw(16) << world.escapeVelocity << "m/s" << endl;}
	if (world.worldType != WT_ASTEROID_BELT) 										{cout << left << setw(48) << "Number of major moons:" 				<< (int)world.numberOfMajorMoons 			<< endl;}
	if (world.worldType != WT_ASTEROID_BELT) 										{cout << left << setw(48) << "Number of moonlets:" 					<< (int)world.terrestrialMoonlet 			<< endl;}
//		Physical attributes
		cout << left << setw(48) << "Size class:" << SC_S_LOOKUP_TABLE[(int)world.sizeClass] << endl;
//		cout << left << setw(48) << "Overall type:" << world.overallType 											<< endl;
	if (worldTypeCanHaveAtmosphere == true && !isGasGiant) 								{cout << left << setw(48) << "Atmosphere mass:" 					<< left << setw(16) << world.atmosphereMass << "Earth atmospheres" << endl;}
//		Print the composition of the world's atmosphere (if it has one)
	if (world.atmosphereMass != 0 && !isGasGiant) 												{printAtmosphereComposition(world.worldAtmosphereComposition);}
//		Resume printing the world's details
	if (worldTypeCanHaveAtmosphere == true && !isGasGiant) 								{cout << left << setw(48) << "Hydrographic coverage:" 				<< left << setw(16)	<< world.hydrographicCoverage * 100	<< "%" << endl;}
	if (!isGasGiant)	{cout << left << setw(48) << "Surface temperature:" 				<< left << setw(16) << world.surfaceTemperature << "Kelvin" << endl;}
	if (worldTypeCanHaveAtmosphere == true && !isGasGiant) 								{cout << left << setw(48) << "Greenhouse factor:" 					<< world.greenhouseFactor 				<< endl;}
	cout << left << setw(48) << "Absorption factor:" 				<< world.absorptionFactor << endl;
	cout << left << setw(48) << "Blackbody temperature:" 			<< left << setw(16) << world.blackbodyTemperature << "Kelvin" << endl;
	if (world.worldType != WT_ASTEROID_BELT) 									{cout << left << setw(48) << "World density:" 						<< left << setw(16) << world.worldDensity 					<< "Earth densities" << endl;}
	if (world.worldType != WT_ASTEROID_BELT) 									{cout << left << setw(48) << "World diameter:" 						<< left << setw(16) << world.worldDiameter 					<< "Earth diameters | " << world.worldDiameter * EARTH_RADIUS_IN_KM * 2 << " km" << endl;}
	if (world.worldType != WT_ASTEROID_BELT) 									{cout << left << setw(48) << "Total surface area:" 						<< left << setw(16) << world.totalSurfaceArea 					<< "km^2" << endl;}
	if (world.worldType != WT_ASTEROID_BELT && world.hydrographicCoverage != 0) {cout << left << setw(48) << "Liquid surface area:" 						<< left << setw(16) << world.liquidSurfaceArea 					<< "km^2" << endl;}
	if (world.worldType != WT_ASTEROID_BELT && world.hydrographicCoverage != 0) {cout << left << setw(48) << "Land surface area:" 						<< left << setw(16) << world.landSurfaceArea 					<< "km^2" << endl;}
	if (world.worldType != WT_ASTEROID_BELT) 									{cout << left << setw(48) << "Surface gravity:" 					<< left << setw(16) << world.surfaceGravity 				<< "Earth gravities" << endl;}
	if (world.worldType != WT_ASTEROID_BELT) 									{cout << left << setw(48) << "World mass:" 							<< left << setw(16) << world.worldMass 						<< "Earth masses" << endl;}
	if (worldTypeCanHaveAtmosphere == true && !isGasGiant) 									{cout << left << setw(48) << "Atmospheric pressure:" 				<< left << setw(16) << world.atmosphericPressure		 	<< "standard atmospheres" << endl;}
	if (world.worldType != WT_ASTEROID_BELT) 									{cout << left << setw(48) << "Minimum molecular weight retained:"	<< left << setw(16) << world.minimumMolecularWeightRetained << "grams per mole" << endl;}
	if (world.worldType != WT_ASTEROID_BELT && !isGasGiant) 									{cout << left << setw(48) << "Volcanic activity level:"	<< VAL_S_LOOKUP_TABLE[world.volcanicActivityLevel] << endl;}
	if (world.worldType != WT_ASTEROID_BELT && !isGasGiant) 									{cout << left << setw(48) << "Tectonic activity level:"	<< TAL_S_LOOKUP_TABLE[world.tectonicActivityLevel] << endl;}
	cout << left << setw(48) << "Resource value modifier:" 			<< (int)world.resourceValueModifier << endl;
	cout << left << setw(48) << "Habitability modifier:" 			<< (int)world.habitabilityModifier << endl;
	if (world.worldType != WT_ASTEROID_BELT) 									{cout << left << setw(48) << "Equatorial rotation velocity:" 						<< left << setw(16) << world.equatorialRotationVelocity 					<< "m/s" << endl;}

	if (world.numberOfMajorMoons != 0)
	{
		for (int i = 0; i < world.numberOfMajorMoons; i++)
		{
			cout << "\nMoon " << i + 1 << endl;
			printMoon(world.majorMoonArray[i]);
		}
	}
}

//	Print the characteristics of a star
void printStar(star_t star, char numberOfStars)
{
	cout << setw(48) << left << "\nStar:" << left << setw(16) << (int)star.starNumber << endl;
	cout << setw(48) << left << "Stellar mass:" << left << setw(16) << star.stellarMass << " solar masses" << endl;
//	cout << setw(48) << left << "Stellar age:" << left << setw(16) << star.stellarAge << " billion years" << endl;
//	cout << setw(48) << left << "Luminosity class:" << star.luminosityClass << endl;
	cout << setw(48) << left << "Stellar luminosity:" << left << setw(16) << star.stellarLuminosity << " solar luminosities" << endl;
	cout << setw(48) << left << "Stellar temperature:" << left << setw(16) << star.stellarTemperature << " Kelvin" << endl;
	cout << setw(48) << left << "Stellar radius:" << left << setw(16) << star.stellarRadius << " au's" << endl;
//	cout << left << setw(48) << "Equatorial rotation velocity:" 						<< left << setw(16) << star.equatorialRotationVelocity 					<< "m/s" << endl;}
	cout << setw(48) << left << "Spectral type:" << left << setw(16) << SPECTRAL_TYPE_LOOKUP_TABLE[star.starType] << " " << star.luminosityClass << endl;
	cout << setw(48) << left << "Inner limit radius:" << left << setw(16) << star.innerLimitRadius << " au's" << endl;
	cout << setw(48) << left << "Outer limit radius:" << left << setw(16) << star.outerLimitRadius << " au's" << endl;
	cout << setw(48) << left << "Snow line radius:" << left << setw(16) << star.snowLineRadius << " au's" << endl;
	cout << setw(48) << left << "Gas giant arrangement:" << left << setw(16) << GGA_S_LOOKUP_TABLE[star.gasGiantArrangement] << endl;

	if (numberOfStars != 1)
	{
		cout << setw(48) << left << "Inner forbidden zone:" << left << setw(16) << star.innerForbiddenZone << " au's" << endl;
		cout << setw(48) << left << "Outer forbidden zone:" << left << setw(16) << star.outerForbiddenZone << " au's" << endl;
		if (star.starNumber != 0)
		{
			cout << setw(48) << left << "Average orbital radius:" << left << setw(16) << star.averageOrbitalRadius << " au's" << endl;
			cout << setw(48) << left << "Orbital eccentricity:" << left << setw(16) << star.orbitalEccentricity << endl;
			cout << setw(48) << left << "Minimum separation to primary:" << left << setw(16) << star.minSeparationToCompanion << " au's" << endl;
			cout << setw(48) << left << "Maximum separation to primary:" << left << setw(16) << star.maxSeparationToCompanion << " au's" << endl;
			cout << setw(48) << left << "Orbital period around primary:" << left << setw(16) << star.stellarOrbitalPeriod << " years" << endl;
		}
	}

//	Print the worlds around the star
	for (int index = 0; index < star.sizeClassIndex; index++)
	{
//		cout << "index = " << index << endl;
//		cout << "sizeClassArray[" << index << "] = " << SC_S_LOOKUP_TABLE[(int)star.sizeClassArray[index]] << endl;
//		cout << "Worldbuilder for loop reached" << endl;
//		If the world is not a gas giant or empty
//		if (star.sizeClassArray[index] != WT_SMALL_GAS_GIANT && star.sizeClassArray[index] != WT_MEDIUM_GAS_GIANT && star.sizeClassArray[index] != WT_LARGE_GAS_GIANT && star.sizeClassArray[index] != SC_EMPTY_ORBIT)
/*		bool validWorldType = star.worldArray[index].worldType == WT_ASTEROID_BELT || star.worldArray[index].worldType == WT_STANDARD_GARDEN || star.worldArray[index].worldType == WT_STANDARD_OCEAN || star.worldArray[index].worldType == WT_LARGE_GARDEN || star.worldArray[index].worldType == WT_LARGE_OCEAN || star.worldArray[index].worldType == WT_STANDARD_AMMONIA || star.worldArray[index].worldType == WT_STANDARD_GREENHOUSE || star.worldArray[index].worldType == WT_LARGE_AMMONIA || star.worldArray[index].worldType == WT_LARGE_GREENHOUSE || star.worldArray[index].worldType == WT_TINY_ICE || star.worldArray[index].worldType == WT_SMALL_HADEAN || star.worldArray[index].worldType == WT_SMALL_ICE || star.worldArray[index].worldType == WT_STANDARD_HADEAN || star.worldArray[index].worldType == WT_STANDARD_ICE || star.worldArray[index].worldType == WT_LARGE_ICE || star.worldArray[index].worldType == WT_TINY_SULFUR || star.worldArray[index].worldType == WT_TINY_SULFUR || star.worldArray[index].worldType == WT_SMALL_ROCK || star.worldArray[index].worldType == WT_STANDARD_CHTHONIAN || star.worldArray[index].worldType == WT_LARGE_CHTHONIAN || star.worldArray[index].worldType == WT_SMALL_GAS_GIANT || star.worldArray[index].worldType == WT_MEDIUM_GAS_GIANT || star.worldArray[index].worldType == WT_LARGE_GAS_GIANT;
		if (!validWorldType) {cout << "Empty Orbit" << endl;}
*///		if (/*validWorldType == true && */star.sizeClassArray[index] != SC_EMPTY_ORBIT)
//		{
//			cout << "Worldbuilder if loop reached" << endl;
//			Run worldBuilder_ADVANCED
			cout << "\nWorld " << index /*+ 1*/ << endl;
			printWorld(star.worldArray[index], star.sizeClassArray[index]);
	//	}
//		cout << "For loop ended" << endl;
	}
}

//	Print the characteristics of a star system
void printStarSystem(starSystem_t starSystem)
{
	cout << "Debug information" << endl;
	cout << "struct starSystem_t = " << sizeof(starSystem_t) << endl;
	cout << "struct star_t = " << sizeof(star_t) << endl;
	cout << "struct world_t = " << sizeof(world_t) << endl;
	cout << "struct moon_t = " << sizeof(moon_t) << endl << endl;
	cout << "Star system" << endl;
	cout << "Number of stars:" << (int)starSystem.numberOfStars << endl;

	for (int i = 0; i < starSystem.numberOfStars; i++)
	{
		printStar(starSystem.stars[i], starSystem.numberOfStars);
	}
}
