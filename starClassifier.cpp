

//	C++ libraries
#include <cstdint>
#include <iostream>
#include <math.h>
#include <regex>
#include <string>
#include <tuple>
//	#include <vector>

//	Structure declarations
#include "declarations/structures/star_t.h"

//	Function declarations
#include "declarations/functions/findClosestElement.h"
#include "declarations/functions/floatRNG.h"

//	Constant declarations
#include "declarations/constants/stellarClassificationTable.h"

//	Third party libraries
#include "declarations/third_party/rapidcsv.h"


/*
	*****************
	*	FIX THIS	*
	*****************
//	If spect == "~"
star_t extrapolateStellarClassification(double originalLuminosity)
{
//	Initialize new star
	star_t newStar;
//	Generate variance
	double massVariance = floatRNG(-0.05, 0.05);
	double radiusVariance = floatRNG(-0.05, 0.05);
	double temperatureVariance = floatRNG(-0.05, 0.05);
	bool matchFound = false;

//	Loop through stellarclassificationTable_luminosity until a match is found
//	do
//	{
		for (int lumIndex = 0; lumIndex < stellarclassificationTable_length; lumIndex++)
		{
//			If the constant luminosity divided by the .csv luminosity rounds to one
			if (rint(stellarclassificationTable_luminosity[lumIndex] / originalLuminosity) == 1)
			{
//				A match has been found
				matchFound = true;
//				Assign mass, radius, temperature, star type, and RGB
				newStar.stellarLuminosity 	= originalLuminosity;
				newStar.stellarMass 		= stellarClassificationTable_mass[lumIndex] + (stellarClassificationTable_mass[lumIndex] * massVariance);
				newStar.stellarRadius 		= stellarClassificationTable_radius[lumIndex] + (stellarClassificationTable_radius[lumIndex] * radiusVariance);
				newStar.stellarTemperature 	= stellarClassificationTable_temperature[lumIndex] + (stellarClassificationTable_temperature[lumIndex] * temperatureVariance);
				newStar.starType 			= stellarClassificationTable_string[lumIndex];
				newStar.starColor_r 		= starColorTable_r[lumIndex];
				newStar.starColor_g 		= starColorTable_g[lumIndex];
				newStar.starColor_b 		= starColorTable_b[lumIndex];
//				Break out of for loop
				break;
			}
//		}

//	} while(matchFound == false)
//	Return newStar
	return newStar;
}
*/

std::tuple<int, int, int> getStarColor(std::string harvardLetter, char yerkesIndex, int intNumericValue)
{
//	Initialize return values
	int colorR = 0, colorG = 0, colorB = 0;
	if 		(harvardLetter == HARVARDLETTER_O) {colorR = STELLARCLASSIFICATIONTABLE_O_R[yerkesIndex]; 		colorG = STELLARCLASSIFICATIONTABLE_O_G[yerkesIndex]; 		colorB = STELLARCLASSIFICATIONTABLE_O_B[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_B) {colorR = STELLARCLASSIFICATIONTABLE_B_R[yerkesIndex]; 		colorG = STELLARCLASSIFICATIONTABLE_B_G[yerkesIndex]; 		colorB = STELLARCLASSIFICATIONTABLE_B_B[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_A) {colorR = STELLARCLASSIFICATIONTABLE_A_R[yerkesIndex]; 		colorG = STELLARCLASSIFICATIONTABLE_A_G[yerkesIndex]; 		colorB = STELLARCLASSIFICATIONTABLE_A_B[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_F) {colorR = STELLARCLASSIFICATIONTABLE_F_R[yerkesIndex]; 		colorG = STELLARCLASSIFICATIONTABLE_F_G[yerkesIndex]; 		colorB = STELLARCLASSIFICATIONTABLE_F_B[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_G) {colorR = STELLARCLASSIFICATIONTABLE_G_R[yerkesIndex]; 		colorG = STELLARCLASSIFICATIONTABLE_G_G[yerkesIndex]; 		colorB = STELLARCLASSIFICATIONTABLE_G_B[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_K) {colorR = STELLARCLASSIFICATIONTABLE_K_R[yerkesIndex]; 		colorG = STELLARCLASSIFICATIONTABLE_K_G[yerkesIndex]; 		colorB = STELLARCLASSIFICATIONTABLE_K_B[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_M) {colorR = STELLARCLASSIFICATIONTABLE_M_R[yerkesIndex]; 		colorG = STELLARCLASSIFICATIONTABLE_M_G[yerkesIndex]; 		colorB = STELLARCLASSIFICATIONTABLE_M_B[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_D) {colorR = STELLARCLASSIFICATIONTABLE_D_R[intNumericValue]; 	colorG = STELLARCLASSIFICATIONTABLE_D_G[intNumericValue]; 	colorB = STELLARCLASSIFICATIONTABLE_D_B[intNumericValue];}

	return std::make_tuple(colorR, colorG, colorB);

}

//	Lookup physical parameters
float lookupStellarMass(std::string harvardLetter, char yerkesIndex, int intNumericValue)
{
//	Initialize return value
	float stellarMass = 0;
	if 		(harvardLetter == HARVARDLETTER_O) {stellarMass = STELLARCLASSIFICATIONTABLE_O_MASS[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_B) {stellarMass = STELLARCLASSIFICATIONTABLE_B_MASS[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_A) {stellarMass = STELLARCLASSIFICATIONTABLE_A_MASS[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_F) {stellarMass = STELLARCLASSIFICATIONTABLE_F_MASS[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_G) {stellarMass = STELLARCLASSIFICATIONTABLE_G_MASS[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_K) {stellarMass = STELLARCLASSIFICATIONTABLE_K_MASS[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_M) {stellarMass = STELLARCLASSIFICATIONTABLE_M_MASS[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_D) {stellarMass = STELLARCLASSIFICATIONTABLE_D_MASS[intNumericValue];}

	return stellarMass;
}

float lookupStellarRadius(std::string harvardLetter, char yerkesIndex, int intNumericValue)
{
//	Initialize return value
	float stellarRadius = 0;
	if 		(harvardLetter == HARVARDLETTER_O) {stellarRadius = STELLARCLASSIFICATIONTABLE_O_RADIUS[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_B) {stellarRadius = STELLARCLASSIFICATIONTABLE_B_RADIUS[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_A) {stellarRadius = STELLARCLASSIFICATIONTABLE_A_RADIUS[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_F) {stellarRadius = STELLARCLASSIFICATIONTABLE_F_RADIUS[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_G) {stellarRadius = STELLARCLASSIFICATIONTABLE_G_RADIUS[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_K) {stellarRadius = STELLARCLASSIFICATIONTABLE_K_RADIUS[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_M) {stellarRadius = STELLARCLASSIFICATIONTABLE_M_RADIUS[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_D) {stellarRadius = STELLARCLASSIFICATIONTABLE_D_RADIUS[intNumericValue];}

	return stellarRadius;
}

float lookupStellarTemperature(std::string harvardLetter, char yerkesIndex, int intNumericValue)
{
//	Initialize return value
	float stellarTemperature = 0;
	if 		(harvardLetter == HARVARDLETTER_O) {stellarTemperature = STELLARCLASSIFICATIONTABLE_O_TEMP[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_B) {stellarTemperature = STELLARCLASSIFICATIONTABLE_B_TEMP[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_A) {stellarTemperature = STELLARCLASSIFICATIONTABLE_A_TEMP[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_F) {stellarTemperature = STELLARCLASSIFICATIONTABLE_F_TEMP[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_G) {stellarTemperature = STELLARCLASSIFICATIONTABLE_G_TEMP[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_K) {stellarTemperature = STELLARCLASSIFICATIONTABLE_K_TEMP[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_M) {stellarTemperature = STELLARCLASSIFICATIONTABLE_M_TEMP[yerkesIndex];}
	else if (harvardLetter == HARVARDLETTER_D) {stellarTemperature = STELLARCLASSIFICATIONTABLE_D_TEMP[intNumericValue];}

	return stellarTemperature;
}


//	Determine stellar parameters
std::tuple<float, float, float, int, int, int> extrapolateStellarParameters(int currentCSVIndex, rapidcsv::Document& starDoc, std::string harvardLetter, std::string yerkesClassification, bool floatOrIntNumericValue, bool massPreset, bool radiusPreset, bool tempPreset, float floatNumericValue, int intNumericValue)
{
//	Check parameters
////	std::cout << "harvardLetter = " << harvardLetter << std::endl;
////	std::cout << "numericValue = " << numericValue << std::endl;
////	std::cout << "yerkesClassification = " << yerkesClassification << std::endl;

//	Initialize return values
	float stellarMass = 0;
	float stellarRadius = 0;
	float stellarTemperature = 0;
	int intNumericValueTemp = intNumericValue;
//	Initialize Yerkes index
	int yerkesIndex = 0;
//	Initialize multiplier
	float floatMultiplier = 0;

//	If numericValue is a float
	if (floatOrIntNumericValue == false)
	{
		intNumericValueTemp = rint(floatNumericValue);
//		Initialize multiplier
		floatMultiplier = (intNumericValueTemp >= floatNumericValue) ? floatNumericValue - (intNumericValueTemp - 1) : floatNumericValue - intNumericValueTemp;
	}

//	Otherwise
//	The constant tables are in descending order, so that the true index is (YERKESCLASSIFCATIONINDEX_LENGTH - (intNumericValue + 1))
//	Check for out of bounds
	int ascendantIndex = (intNumericValueTemp + 1) > YERKESCLASSIFCATIONINDEX_LENGTH ? YERKESCLASSIFCATIONINDEX_LENGTH : YERKESCLASSIFCATIONINDEX_LENGTH - (intNumericValueTemp + 1);
	ascendantIndex = YERKESCLASSIFCATIONINDEX_LENGTH - (intNumericValueTemp + 1);
	if 		(yerkesClassification == YERKESCLASSIFICATION_IA)		{yerkesIndex = YERKESCLASSIFICATIONINDEX_IA[ascendantIndex];}
	else if (yerkesClassification == YERKESCLASSIFICATION_IB)		{yerkesIndex = YERKESCLASSIFICATIONINDEX_IB[ascendantIndex];}
	else if (yerkesClassification == YERKESCLASSIFICATION_II)		{yerkesIndex = YERKESCLASSIFICATIONINDEX_II[ascendantIndex];}
	else if (yerkesClassification == YERKESCLASSIFICATION_III)		{yerkesIndex = YERKESCLASSIFICATIONINDEX_III[ascendantIndex];}
	else if (yerkesClassification == YERKESCLASSIFICATION_IV)		{yerkesIndex = YERKESCLASSIFICATIONINDEX_IV[ascendantIndex];}
	else if (yerkesClassification == YERKESCLASSIFICATION_V)		{yerkesIndex = YERKESCLASSIFICATIONINDEX_V[ascendantIndex];}
	else if (yerkesClassification == YERKESCLASSIFICATION_SD)		{yerkesIndex = YERKESCLASSIFICATIONINDEX_SD[ascendantIndex];}


//	Check preset flags
	if (massPreset == false)
	{
		float massVariance = floatRNG(-0.05, 0.05);
		stellarMass = lookupStellarMass(harvardLetter, yerkesIndex, ascendantIndex);
		if (floatOrIntNumericValue == false)	{stellarMass += (stellarMass * floatMultiplier);}
		stellarMass += (stellarMass * massVariance);
	}

	else
	{
		stellarMass = starDoc.GetCell<float>("mass", currentCSVIndex);
	}

//	Check preset flags
	if (radiusPreset == false)
	{
		float radiusVariance = floatRNG(-0.05, 0.05);
		stellarRadius = lookupStellarRadius(harvardLetter, yerkesIndex, ascendantIndex);
		if (floatOrIntNumericValue == false)	{stellarRadius += (stellarRadius * floatMultiplier);}
		stellarRadius += (stellarRadius * radiusVariance);
	}

	else
	{
		stellarRadius = starDoc.GetCell<float>("radius", currentCSVIndex);
	}

//	Check preset flags
	if (tempPreset == false)
	{
		float temperatureVariance = floatRNG(-0.05, 0.05);
		stellarTemperature = lookupStellarTemperature(harvardLetter, yerkesIndex, ascendantIndex);
		if (floatOrIntNumericValue == false)	{stellarTemperature += (stellarTemperature * floatMultiplier);}
		stellarTemperature += (stellarTemperature * temperatureVariance);
	}

	else
	{
		stellarTemperature = starDoc.GetCell<float>("temperature", currentCSVIndex);
	}

	int colorR = 0, colorG = 0, colorB = 0;
	std::tie (colorR, colorG, colorB) = getStarColor(harvardLetter, yerkesIndex, ascendantIndex);

	return std::make_tuple(stellarMass, stellarRadius, stellarTemperature, colorR, colorG, colorB);
}

//	Determine Harvard classification
std::string getHarvardLetter(std::string starType, bool harvardPresent)
{
//	Check starType
////	std::cout << "starType = " << starType << std::endl;

////	std::cout << "result when checking for K: " << std::regex_search(starType, std::regex("\\bK")) << std::endl;

//	Harvard classification letter
	std::string harvardLetter;

//	Check for O
	if 		(std::regex_search(starType, std::regex("\\bO")) == true)	{harvardLetter = HARVARDLETTER_O;}

//	Check for B
	else if (std::regex_search(starType, std::regex("\\bB")) == true)	{harvardLetter = HARVARDLETTER_B;}

//	Check for A
	else if (std::regex_search(starType, std::regex("\\bA")) == true)	{harvardLetter = HARVARDLETTER_A;}

//	Check for F
	else if (std::regex_search(starType, std::regex("\\bF")) == true)	{harvardLetter = HARVARDLETTER_F;}

//	Check for G
	else if (std::regex_search(starType, std::regex("\\bG")) == true)	{harvardLetter = HARVARDLETTER_G;}

//	Check for K
	else if (std::regex_search(starType, std::regex("\\bK")) == true)	{harvardLetter = HARVARDLETTER_K;}

//	Check for M
	else if (std::regex_search(starType, std::regex("\\bM")) == true)	{harvardLetter = HARVARDLETTER_M;}

//	Check for D
	else if (std::regex_search(starType, std::regex("\\bD")) == true)	{harvardLetter = HARVARDLETTER_D;}

// Check for error
	else
	{
	//	std::cout << "ERROR: starType == |" << starType << "|" << std::endl;
	}

	return harvardLetter;
}

//	Loop through index tables to find a match
std::string checkYerkesIndexTable(int index)
{
//	Check index value
////	std::cout << "Yerkes index value = " << index << std::endl;
//	Initialize return value
	std::string yerkesClassification;
//	Flag to break out of for loop
	bool matchFound = false;
//	Loop through index tables
	for (int i = 0; i < 10; i++)
	{
		if 		(index == YERKESCLASSIFICATIONINDEX_IA[i]) 	{yerkesClassification = YERKESCLASSIFICATION_IA;	break;}
		else if (index == YERKESCLASSIFICATIONINDEX_IB[i])	{yerkesClassification = YERKESCLASSIFICATION_IB;	break;}
		else if (index == YERKESCLASSIFICATIONINDEX_II[i])	{yerkesClassification = YERKESCLASSIFICATION_II;	break;}
		else if (index == YERKESCLASSIFICATIONINDEX_III[i])	{yerkesClassification = YERKESCLASSIFICATION_III;	break;}
		else if (index == YERKESCLASSIFICATIONINDEX_IV[i])	{yerkesClassification = YERKESCLASSIFICATION_IV;	break;}
		else if (index == YERKESCLASSIFICATIONINDEX_V[i])	{yerkesClassification = YERKESCLASSIFICATION_V;		break;}
		else if (index == YERKESCLASSIFICATIONINDEX_SD[i])	{yerkesClassification = YERKESCLASSIFICATION_SD;	break;}
	}

	return yerkesClassification;
}
/*
//	Get Yerkes classification
std::string getYerkesClassification(std::string harvardLetter, double originalLuminosity, bool yerkesPresent)
{
//	Check parameters
////	std::cout << "harvardLetter = " << harvardLetter << std::endl;
////	std::cout << "originalLuminosity = " << originalLuminosity << std::endl;

//	Initialize return value
	std::string yerkesClassification;
	float calcLum = 0;
	const int ROUNDEDVALUESVECTORSIZE = 8;
	std::vector <double> roundedValues(8);
	int roundedValuesIndex = 0;
//	std::cout << "\nEntered getYerkesClassification" << std::endl;
//	std::cout << "harvardLetter == " << harvardLetter << std::endl;
//	std::cout << "originalLuminosity == " << originalLuminosity << std::endl;
//	Loop through the Harvard classification's table
	for (int i = 0; i < STELLARCLASSIFICATIONTABLE_X_OBAFGKM; i++)
	{
//		Check for O
		if (harvardLetter == HARVARDLETTER_O)
		{
//			If the luminosity is close enough
			calcLum = originalLuminosity / STELLARCLASSIFICATIONTABLE_O_LUMINOSITY[i];
			if (ceil(calcLum) == 1 || floor(calcLum) == 1)
			{
				roundedValues.push_back(calcLum);
				yerkesClassification = checkYerkesIndexTable(i);
//				break;
			}
		}

//		Check for B
		else if (harvardLetter == HARVARDLETTER_B)
		{
//			If the luminosity is close enough
			calcLum = originalLuminosity / STELLARCLASSIFICATIONTABLE_B_LUMINOSITY[i];
			if (ceil(calcLum) == 1 || floor(calcLum) == 1)
			{
				roundedValues.push_back(calcLum);
				yerkesClassification = checkYerkesIndexTable(i);
//				break;
			}
		}

//		Check for A
		else if (harvardLetter == HARVARDLETTER_A)
		{
//			If the luminosity is close enough
			calcLum = originalLuminosity / STELLARCLASSIFICATIONTABLE_A_LUMINOSITY[i];
			if (ceil(calcLum) == 1 || floor(calcLum) == 1)
			{
				roundedValues.push_back(calcLum);
				yerkesClassification = checkYerkesIndexTable(i);
//				break;
			}
		}

//		Check for F
		else if (harvardLetter == HARVARDLETTER_F)
		{
//			If the luminosity is close enough
			calcLum = originalLuminosity / STELLARCLASSIFICATIONTABLE_F_LUMINOSITY[i];
			if (ceil(calcLum) == 1 || floor(calcLum) == 1)
			{
				roundedValues.push_back(calcLum);
				yerkesClassification = checkYerkesIndexTable(i);
//				break;
			}
		}

//		Check for G
		else if (harvardLetter == HARVARDLETTER_G)
		{
//			If the luminosity is close enough
			calcLum = originalLuminosity / STELLARCLASSIFICATIONTABLE_G_LUMINOSITY[i];
			if (ceil(calcLum) == 1 || floor(calcLum) == 1)
			{
				roundedValues.push_back(calcLum);
				yerkesClassification = checkYerkesIndexTable(i);
//				break;
			}
		}

//		Check for K
		else if (harvardLetter == HARVARDLETTER_K)
		{
//			If the luminosity is close enough
			calcLum = originalLuminosity / STELLARCLASSIFICATIONTABLE_K_LUMINOSITY[i];
			if (ceil(calcLum) == 1 || floor(calcLum) == 1)
			{
				roundedValues.push_back(calcLum);
				yerkesClassification = checkYerkesIndexTable(i);
//				break;
			}
		}

//		Check for M
		else if (harvardLetter == HARVARDLETTER_M)
		{
//			If the luminosity is close enough
			calcLum = originalLuminosity / STELLARCLASSIFICATIONTABLE_M_LUMINOSITY[i];
			if (ceil(calcLum) == 1 || floor(calcLum) == 1)
			{
				roundedValues.push_back(calcLum);
				yerkesClassification = checkYerkesIndexTable(i);
//				break;
			}
		}

//		Check for D
		else if (harvardLetter == HARVARDLETTER_D)
		{
		//	std::cout << "White dwarves have no Yerkes classification" << std::endl;
			yerkesClassification = YERKESCLASSIFICATION_BLANK;
			return yerkesClassification;
		}

//		If this is the last iteration
		if (i == STELLARCLASSIFICATIONTABLE_X_OBAFGKM - 1)
		{
			double tempValue = 0;
			for (int i = 0; i < roundedValues.size(); i++)
			{
	//		Check for out of bounds
				for (int j = i + 1; j < roundedValues.size(); j++)
				{
					tempValue = roundedValues[i];
					roundedValues[i] = roundedValues[j];
					roundedValues[j] = tempValue;
				}
			}
		}
	}
	int yerkesClassificationArrayIndex = findClosestElementDouble(roundedValues, ROUNDEDVALUESVECTORSIZE, 1);
	yerkesClassification = YERKESCLASSIFICATION_TABLE[yerkesClassificationArrayIndex];

	return yerkesClassification;
}
*/
//	Get numeric value
int getNumericValue(std::string yerkesClassification, std::string harvardLetter, double originalLuminosity, bool numberPresent)
{
/*
//	Check for parameter errors
	if (std::regex_search(yerkesClassification, YERKESREGEX) != true)
	{
	//	std::cout << "No Yerkes classification passed" << std::endl;
		return 0;
	}

	if (originalLuminosity == 0)
	{
	//	std::cout << "originalLuminosity == 0" << std::endl;
		return 0;
	}
*/
//	std::cout << "originalLuminosity == " << originalLuminosity << std::endl;

//	Initialize return value
	int numericValue = 0;
//	Initialize tables to use
	int luminosity_YTable[10] = {0};
	float luminosity_HYTable[10] = {0};

//	Determine Harvard and Yerkes index table
	for (int i = YERKESCLASSIFCATIONINDEX_LENGTH - 1; i > 0; i--)
	{
		if 		(yerkesClassification == YERKESCLASSIFICATION_IA)	{luminosity_YTable[i] = YERKESCLASSIFICATIONINDEX_IA[i];}
		else if (yerkesClassification == YERKESCLASSIFICATION_IB)	{luminosity_YTable[i] = YERKESCLASSIFICATIONINDEX_IB[i];}
		else if (yerkesClassification == YERKESCLASSIFICATION_II)	{luminosity_YTable[i] = YERKESCLASSIFICATIONINDEX_II[i];}
		else if (yerkesClassification == YERKESCLASSIFICATION_III)	{luminosity_YTable[i] = YERKESCLASSIFICATIONINDEX_III[i];}
		else if (yerkesClassification == YERKESCLASSIFICATION_IV)	{luminosity_YTable[i] = YERKESCLASSIFICATIONINDEX_IV[i];}
		else if (yerkesClassification == YERKESCLASSIFICATION_V)	{luminosity_YTable[i] = YERKESCLASSIFICATIONINDEX_V[i];}
		else if (yerkesClassification == YERKESCLASSIFICATION_SD)	{luminosity_YTable[i] = YERKESCLASSIFICATIONINDEX_SD[i];}

		if 		(harvardLetter == HARVARDLETTER_O) 	{luminosity_HYTable[i] = STELLARCLASSIFICATIONTABLE_O_LUMINOSITY[luminosity_YTable[i]];}
		else if (harvardLetter == HARVARDLETTER_B)	{luminosity_HYTable[i] = STELLARCLASSIFICATIONTABLE_B_LUMINOSITY[luminosity_YTable[i]];}
		else if (harvardLetter == HARVARDLETTER_A)	{luminosity_HYTable[i] = STELLARCLASSIFICATIONTABLE_A_LUMINOSITY[luminosity_YTable[i]];}
		else if (harvardLetter == HARVARDLETTER_F)	{luminosity_HYTable[i] = STELLARCLASSIFICATIONTABLE_F_LUMINOSITY[luminosity_YTable[i]];}
		else if (harvardLetter == HARVARDLETTER_G)	{luminosity_HYTable[i] = STELLARCLASSIFICATIONTABLE_G_LUMINOSITY[luminosity_YTable[i]];}
		else if (harvardLetter == HARVARDLETTER_K)	{luminosity_HYTable[i] = STELLARCLASSIFICATIONTABLE_K_LUMINOSITY[luminosity_YTable[i]];}
		else if (harvardLetter == HARVARDLETTER_M)	{luminosity_HYTable[i] = STELLARCLASSIFICATIONTABLE_M_LUMINOSITY[luminosity_YTable[i]];}
		else if (harvardLetter == HARVARDLETTER_D)	{luminosity_HYTable[i] = STELLARCLASSIFICATIONTABLE_D_LUMINOSITY[i];}
	}
//	std::cout << "luminosity_HYTable[0] == " << luminosity_HYTable[YERKESCLASSIFCATIONINDEX_LENGTH - 1] << std::endl;
//	If originalLuminosity is less than or equal to the smallest value for the Harvard letter, set numericValue to 0
	if 		(originalLuminosity <= luminosity_HYTable[YERKESCLASSIFCATIONINDEX_LENGTH - 1])	{numericValue = 0;}
//	If originalLuminosity is greater than or equal to the largest possible value for the Harvard letter, set numericValue to 9.99
	else if (originalLuminosity >= luminosity_HYTable[0])									{numericValue = 9;}
//	If originalLuminosity is greater than the smallest value
//	Loop through luminosity_HYTable
	else
	{
		for (int i = YERKESCLASSIFCATIONINDEX_LENGTH - 1; i > 0; i--)
		{
			if (luminosity_HYTable[i - 1] <= originalLuminosity && originalLuminosity < luminosity_HYTable[i])	{numericValue = i; break;}
		}
	}
//	Return numericValue
	return numericValue;
}

//	This function completes stellar classification and determines physical parameters
std::tuple<std::string, std::string, float, bool> completeStellarClassification(std::string starType, double originalLuminosity, bool massPreset, bool radiusPreset, bool tempPreset)
{
//	Check parameters
//	std::cout << "starType = " << starType << std::endl;
////	std::cout << "originalLuminosity = " << originalLuminosity << std::endl;
//	Initialize return values
	std::string harvardLetter;
	std::string yerkesClassification;
	float numericValue = 0;

//	Check for Harvard letter
	std::smatch harvardMatch;
	bool harvardPresent = std::regex_search(starType, harvardMatch, HARVARDREGEX);
	if 		(harvardPresent)	{harvardLetter = harvardMatch.str(0);}
//	If there is no Harvard classification, then the star will need to be generated randomly
	else								{harvardLetter = getHarvardLetter(starType, harvardPresent);}
//	Check for Yerkes classification
	std::smatch yerkesMatch;
	bool yerkesPresent = std::regex_search(starType, yerkesMatch, YERKESREGEX);
	if 		(yerkesPresent)	{yerkesClassification = yerkesMatch.str(0);}
//	else							{yerkesClassification = getYerkesClassification(harvardLetter, originalLuminosity, yerkesPresent);}
//	Check for numeric value
	std::smatch numberMatch;
	bool numberPresent = std::regex_search(starType, numberMatch, NUMERICREGEX);
	if 		(numberPresent)	{numericValue = std::stof(numberMatch.str(0));}
	else							{numericValue = getNumericValue(yerkesClassification, harvardLetter, originalLuminosity, numberPresent);}
	bool floatOrIntNumericValue = false;

////	std::cout << "newStar was set" << std::endl;
//	Assign classification
	harvardLetter 			= harvardLetter;
	yerkesClassification 	= yerkesClassification;
	numericValue 			= numericValue;

//	Return newStar
	return std::make_tuple(harvardLetter, yerkesClassification, numericValue, floatOrIntNumericValue);
}
