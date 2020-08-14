//	C++ libraries
#include <iostream>
#include <string>
#include <iomanip>
#include <math.h>

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
	bool worldTypeCanHaveAtmosphere = moon.worldType != "Asteroid Belt" && moon.worldType != "Tiny (Ice)" && moon.worldType != "Tiny (Rock)" && moon.worldType != "Tiny (Sulfur)" && moon.worldType != "Small (Hadean)" && moon.worldType != "Small (Rock)" && moon.worldType != "Standard (Hadean)" && moon.worldType != "Standard (Chthonian)" && moon.worldType != "Large (Chthonian)";
	cout << left << setw(48) << "World type:" 									<< moon.worldType 					  					  << endl;
	cout << left << setw(48) << "Orbital radius:" 								<< left << setw(16) << moon.orbitalRadius 					<< "planetary diameters"	<< endl;
	cout << left << setw(48) << "Orbital period:" 								<< left << setw(16) << moon.orbitalPeriod 			 		<< "days"					<< endl;
	cout << left << setw(48) << "Orbital eccentricity:"							<< moon.orbitalEccentricity 			<< endl;
	cout << left << setw(48) << "Minimum separation to primary:"				<< left << setw(16) << moon.minimumSeparation 				<< "planetary diameters"	<< endl;
	cout << left << setw(48) << "Maximum separation to primary:"				<< left << setw(16) << moon.maximumSeparation 				<< "planetary diameters"	<< endl;
	cout << left << setw(48) << "Apparent orbital cycle as seen from planet:"	<< left << setw(16) << moon.apparentSatelliteOrbitalCycle	<<	"hours" << endl;
	if (moon.worldType != "Asteroid Belt") 										{cout << left << setw(48) << "Rotation period:" 						   << left << setw(16) << moon.rotationPeriod 				  << "hours" << endl;}
	if (moon.retrogradeOrNot == true /*&& moon.worldType != "Asteroid Belt"*/) 	{cout << left << setw(48) << "Moon has a retrograde rotation" 			   << endl;}
	if (moon.worldType != "Asteroid Belt" && !(isinf(moon.apparentDayLength)))	{cout << left << setw(48) << "Apparent day length:" 					   << left << setw(16) << moon.apparentDayLength 			  << "hours" << endl;}
	else if (isinf(moon.apparentDayLength))										{cout << left << setw(48) << "No apparent day"							   << endl;}
	if (moon.worldType != "Asteroid Belt") 										{cout << left << setw(48) << "Axial tilt:" 								   << left << setw(16) << moon.axialTilt 					  << "degrees" << endl;}
	if (moon.resonantOrNot == true && moon.worldType != "Asteroid Belt")		{cout << left << setw(48) << "Moon is in a resonant orbit" 				   << endl;}
	if (moon.tidalLockedOrNot == true && moon.worldType != "Asteroid Belt")		{cout << left << setw(48) << "Moon is tidal locked" 					   << endl;}
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
	if (moon.worldType != "Asteroid Belt") 										{cout << left << setw(48) << "Moon density:" 							   << left << setw(16) << moon.worldDensity 				  << "Earth densities" << endl;}
	if (moon.worldType != "Asteroid Belt") 										{cout << left << setw(48) << "Moon diameter:" 							   << left << setw(16) << moon.worldDiameter 				  << "Earth diameters" << endl;}
	if (moon.worldType != "Asteroid Belt") 										{cout << left << setw(48) << "Surface gravity:" 						   << left << setw(16) << moon.surfaceGravity 				  << "Earth gravities" << endl;}
	if (moon.worldType != "Asteroid Belt") 										{cout << left << setw(48) << "Moon mass:" 								   << left << setw(16) << moon.worldMass 					  << "Earth masses" << endl;}
	if (worldTypeCanHaveAtmosphere == true) 									{cout << left << setw(48) << "Atmospheric pressure:" 					   << left << setw(16) << moon.atmosphericPressure		 	  << "standard atmospheres" << endl;}
	if (moon.worldType != "Asteroid Belt") 										{cout << left << setw(48) << "Minimum molecular weight retained:"		   << left << setw(16) << moon.minimumMolecularWeightRetained << "grams per mole" << endl;}
	if (moon.worldType != "Asteroid Belt") 										{cout << left << setw(48) << "Volcanic activity level:"					   << moon.volcanicActivityLevel 		  << endl;}
	if (moon.worldType != "Asteroid Belt") 										{cout << left << setw(48) << "Tectonic activity level:"					   << moon.tectonicActivityLevel 		  << endl;}
																				 cout << left << setw(48) << "Resource value modifier:" 				   << moon.resourceValueModifier 		  << endl;
																				 cout << left << setw(48) << "Habitability modifier:" 					   << moon.habitabilityModifier 		  << endl;

}

//	This function prints information about the world in question to the console
void printWorld(world_t world, string sizeClass)
{
	bool worldTypeCanHaveAtmosphere = world.worldType != "Asteroid Belt" && world.worldType != "Tiny (Ice)" && world.worldType != "Tiny (Rock)" && world.worldType != "Tiny (Sulfur)" && world.worldType != "Small (Hadean)" && world.worldType != "Small (Rock)" && world.worldType != "Standard (Hadean)" && world.worldType != "Standard (Chthonian)" && world.worldType != "Large (Chthonian)";
	cout << left << setw(48) << "World type:" 						<< world.worldType << endl;
	cout << left << setw(48) << "Orbital radius:" 					<< left << setw(16) << world.orbitalRadius << "au's" << endl;
	cout << left << setw(48) << "Orbital period:" 					<< left << setw(16) << "years" << world.orbitalPeriod << endl;
	cout << left << setw(48) << "Orbital eccentricity:" 			<< world.orbitalEccentricity << endl;
	cout << left << setw(48) << "Minimum separation to primary:" 	<< left << setw(16) << world.minimumSeparation << "au's" << endl;
	cout << left << setw(48) << "Maximum separation to primary:" 	<< left << setw(16) << world.maximumSeparation << "au's" << endl;
	if (world.worldType != "Asteroid Belt") 										{cout << left << setw(48) << "Rotation period:" 					<< left << setw(16) << world.rotationPeriod << "hours" << endl;}
	if (world.retrogradeOrNot == true /*&& world.worldType != "Asteroid Belt"*/) 	{cout << left << setw(48) << "World has a retrograde rotation" 		<< endl;}
	if (world.worldType != "Asteroid Belt" && !(isinf(world.apparentDayLength)))	{cout << left << setw(48) << "Apparent day length:" 				<< left << setw(16) << world.apparentDayLength << "hours" << endl;}
	else if (isinf(world.apparentDayLength))										{cout << left << setw(48) << "No apparent day" << endl;}
	if (world.worldType != "Asteroid Belt") 										{cout << left << setw(48) << "Axial tilt:" 							<< left << setw(16) << world.axialTilt << "degrees" << endl;}
	if (world.resonantOrNot == true && world.worldType != "Asteroid Belt")			{cout << left << setw(48) << "World is in a resonant orbit" 		<< endl;}
	if (world.tidalLockedOrNot == true && world.worldType != "Asteroid Belt")		{cout << left << setw(48) << "World is tidal locked" 				<< endl;}
	if (world.worldType != "Asteroid Belt")											{cout << left << setw(48) << "Escape velocity:"						<< left << setw(16) << world.escapeVelocity << "m/s" << endl;}
	if (world.worldType != "Asteroid Belt") 										{cout << left << setw(48) << "Number of major moons:" 				<< world.numberOfMajorMoons 			<< endl;}
	if (world.worldType != "Asteroid Belt") 										{cout << left << setw(48) << "Number of moonlets:" 					<< world.terrestrialMoonlet 			<< endl;}
//		Physical attributes
//		cout << left << setw(48) << "Size class:" << sizeClass << endl;
//		cout << left << setw(48) << "Overall type:" << world.overallType 											<< endl;
	if (worldTypeCanHaveAtmosphere == true) 								{cout << left << setw(48) << "Atmosphere mass:" 					<< left << setw(16) << world.atmosphereMass << "Earth atmospheres" << endl;}
//		Print the composition of the world's atmosphere (if it has one)
	if (world.atmosphereMass != 0) 												{printAtmosphereComposition(world.worldAtmosphereComposition);}
//		Resume printing the world's details
	if (worldTypeCanHaveAtmosphere == true) 								{cout << left << setw(48) << "Hydrographic coverage:" 				<< world.hydrographicCoverage 			<< "%" << endl;}
	cout << left << setw(48) << "Surface temperature:" 				<< left << setw(16) << world.surfaceTemperature << "Kelvin" << endl;
	if (worldTypeCanHaveAtmosphere == true) 								{cout << left << setw(48) << "Greenhouse factor:" 					<< world.greenhouseFactor 				<< endl;}
	cout << left << setw(48) << "Absorption factor:" 				<< world.absorptionFactor << endl;
	cout << left << setw(48) << "Blackbody temperature:" 			<< left << setw(16) << world.blackbodyTemperature << "Kelvin" << endl;
	if (world.worldType != "Asteroid Belt") 									{cout << left << setw(48) << "World density:" 						<< left << setw(16) << world.worldDensity 					<< "Earth densities" << endl;}
	if (world.worldType != "Asteroid Belt") 									{cout << left << setw(48) << "World diameter:" 						<< left << setw(16) << world.worldDiameter 					<< "Earth diameters" << endl;}
	if (world.worldType != "Asteroid Belt") 									{cout << left << setw(48) << "Surface gravity:" 					<< left << setw(16) << world.surfaceGravity 				<< "Earth gravities" << endl;}
	if (world.worldType != "Asteroid Belt") 									{cout << left << setw(48) << "World mass:" 							<< left << setw(16) << world.worldMass 						<< "Earth masses" << endl;}
	if (worldTypeCanHaveAtmosphere == true) 									{cout << left << setw(48) << "Atmospheric pressure:" 				<< left << setw(16) << world.atmosphericPressure		 	<< "standard atmospheres" << endl;}
	if (world.worldType != "Asteroid Belt") 									{cout << left << setw(48) << "Minimum molecular weight retained:"	<< left << setw(16) << world.minimumMolecularWeightRetained << "grams per mole" << endl;}
	if (world.worldType != "Asteroid Belt") 									{cout << left << setw(48) << "Volcanic activity level:"	<< world.volcanicActivityLevel << endl;}
	if (world.worldType != "Asteroid Belt") 									{cout << left << setw(48) << "Tectonic activity level:"	<< world.tectonicActivityLevel << endl;}
	cout << left << setw(48) << "Resource value modifier:" 			<< world.resourceValueModifier << endl;
	cout << left << setw(48) << "Habitability modifier:" 			<< world.habitabilityModifier << endl;

	for (int i = 0; i < world.numberOfMajorMoons; i++)
	{
		cout << "\nMoon " << i + 1 << endl;
		printMoon(world.majorMoonArray[i]);
	}
}

//	Print the characteristics of a star
void printStar(star_t star, int numberOfStars)
{
	cout << setw(48) << left << "\nStar:" << left << setw(16) << star.starNumber << endl;
	cout << setw(48) << left << "Stellar mass:" << left << setw(16) << star.stellarMass << " solar masses" << endl;
	cout << setw(48) << left << "Stellar age:" << left << setw(16) << star.stellarAge << " billion years" << endl;
//	cout << setw(48) << left << "Luminosity class:" << star.luminosityClass << endl;
	cout << setw(48) << left << "Stellar luminosity:" << left << setw(16) << star.stellarLuminosity << " solar luminosities" << endl;
	cout << setw(48) << left << "Stellar temperature:" << left << setw(16) << star.stellarTemperature << " Kelvin" << endl;
	cout << setw(48) << left << "Stellar radius:" << left << setw(16) << star.stellarRadius << " au's" << endl;
	cout << setw(48) << left << "Spectral type:" << left << setw(16) << SPECTRAL_TYPE_LOOKUP_TABLE[star.starType] << " " << star.luminosityClass << endl;
	cout << setw(48) << left << "Inner limit radius:" << left << setw(16) << star.innerLimitRadius << " au's" << endl;
	cout << setw(48) << left << "Outer limit radius:" << left << setw(16) << star.outerLimitRadius << " au's" << endl;
	cout << setw(48) << left << "Snow line radius:" << left << setw(16) << star.snowLineRadius << " au's" << endl;
	cout << setw(48) << left << "Gas giant arrangement:" << left << setw(16) << star.gasGiantArrangement << endl;

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
	for (int index = 0; index < star.numberOfOrbits; index++)
	{
//		cout << "Worldbuilder for loop reached" << endl;
//		If the world is not a gas giant or empty
//		if (star.sizeClassArray[index] != "Small Gas Giant" && star.sizeClassArray[index] != "Medium Gas Giant" && star.sizeClassArray[index] != "Large Gas Giant" && star.sizeClassArray[index] != "Empty Orbit")
		bool validWorldType = star.worldArray[index].worldType == "Asteroid Belt" || star.worldArray[index].worldType == "Standard (Garden)" || star.worldArray[index].worldType == "Standard (Ocean)" || star.worldArray[index].worldType == "Large (Garden)" || star.worldArray[index].worldType == "Large (Ocean)" || star.worldArray[index].worldType == "Standard (Ammonia)" || star.worldArray[index].worldType == "Standard (Greenhouse)" || star.worldArray[index].worldType == "Large (Ammonia)" || star.worldArray[index].worldType == "Large (Greenhouse)" || star.worldArray[index].worldType == "Tiny (Ice)" || star.worldArray[index].worldType == "Small (Hadean)" || star.worldArray[index].worldType == "Small (Ice)" || star.worldArray[index].worldType == "Standard (Hadean)" || star.worldArray[index].worldType == "Standard (Ice)" || star.worldArray[index].worldType == "Large (Ice)" || star.worldArray[index].worldType == "Tiny (Rock)" || star.worldArray[index].worldType == "Tiny (Sulfur)" || star.worldArray[index].worldType == "Small (Rock)" || star.worldArray[index].worldType == "Standard (Chthonian)" || star.worldArray[index].worldType == "Large (Chthonian)" || star.worldArray[index].worldType == "Small Gas Giant" || star.worldArray[index].worldType == "Medium Gas Giant" || star.worldArray[index].worldType == "Large Gas Giant";
		if (validWorldType == true)
		{
//			cout << "Worldbuilder if loop reached" << endl;
//			Run worldBuilder_ADVANCED
			cout << "\nWorld " << index + 1 << endl;
			printWorld(star.worldArray[index], star.sizeClassArray[index]);
		}
//		cout << "For loop ended" << endl;
	}
}

//	Print the characteristics of a star system
void printStarSystem(starSystem_t starSystem)
{
	cout << "Star system" << endl;
	cout << "Number of stars:" << starSystem.numberOfStars << endl;

	for (int i = 0; i < starSystem.numberOfStars; i++)
	{
		printStar(starSystem.stars[i], starSystem.numberOfStars);
	}
}
