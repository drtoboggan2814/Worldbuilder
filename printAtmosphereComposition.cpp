/*
#include <string>
#include <iostream>
#include <iomanip>

#include "declarations/structures/moon_t.h"
#include "declarations/structures/world_t.h"

using namespace std;

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
	string chlorineOrFluorine_s = (atmosphereComposition.chlorineOrFluorine == 1) ? "Present" : "Absent";
//	String representation of lowOxygen
	string lowOxygen_s = (atmosphereComposition.lowOxygen == 1) ? "True" : "False";
//	String representation of highOxygen
	string highOxygen_s = (atmosphereComposition.highOxygen == 1) ? "True" : "False";
//	String representation of organicToxins
	string organicToxins_s = (atmosphereComposition.organicToxins == 1) ? "Present" : "Absent";
//	String representation of sulfurCompounds
	string sulfurCompounds_s = (atmosphereComposition.sulfurCompounds == 1) ? "Present" : "Absent";
//	String representation of suffocating
	string suffocating_s = (atmosphereComposition.suffocating == 1) ? "True" : "False";
//	String representation of highCarbonDioxide
	string highCarbonDioxide_s = (atmosphereComposition.highCarbonDioxide == 1) ? "True" : "False";
//	String representation of inertGases
	string inertGases_s = (atmosphereComposition.inertGases == 1) ? "Present" : "Absent";
//	String representation of nitrogenCompounds
	string nitrogenCompounds_s = (atmosphereComposition.nitrogenCompounds == 1) ? "Present" : "Absent";
//	String representation of pollutants
	string pollutants_s = (atmosphereComposition.pollutants == 1) ? "Present" : "Absent";
//	String representation of corrosive
	string corrosive_s = (atmosphereComposition.corrosive == 1) ? "True" : "False";

//	Print atmosphere composition
//	This should match up with printWorld
	cout << left << setw(40) << "Toxicity:" 			<< toxicity_s 			<< endl;
	cout << left << setw(40) << "Chlorine or fluorine:" << chlorineOrFluorine_s << endl;
	cout << left << setw(40) << "Low oxygen:" 			<< lowOxygen_s 			<< endl;
	cout << left << setw(40) << "High oxygen" 			<< highOxygen_s 		<< endl;
	cout << left << setw(40) << "Organic toxins:" 		<< organicToxins_s 		<< endl;
	cout << left << setw(40) << "Sulfur compounds:" 	<< sulfurCompounds_s 	<< endl;
	cout << left << setw(40) << "Suffocating:" 			<< suffocating_s 		<< endl;
	cout << left << setw(40) << "High carbon dioxide:" 	<< highCarbonDioxide_s 	<< endl;
	cout << left << setw(40) << "Inert gases:" 			<< inertGases_s 		<< endl;
	cout << left << setw(40) << "Nitrogen compounds:" 	<< nitrogenCompounds_s 	<< endl;
	cout << left << setw(40) << "Pollutants:" 			<< pollutants_s 		<< endl;
	cout << left << setw(40) << "Corrosive:" 			<< corrosive_s 			<< endl;
}
*/
