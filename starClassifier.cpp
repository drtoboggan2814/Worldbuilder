
//	Third party libraries
#include "declarations/third_party/rapidcsv.h"

//	C++ libraries
#include <iostream>
#include <math.h>
#include <regex>
#include <string>

//	Structure declarations
#include "declarations/structures/star_t.h"

//	Function declarations
#include "declarations/functions/floatRNG.h"

//	Constant declarations
#include "declarations/constants/stellarclassificationTable.h"

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

//	Lookup physical parameters
float lookupStellarMass(std::string harvardLetter, uint8_t yerkesIndex)
{
//	Initialize return value
	float stellarMass;
	switch (harvardLetter)
	{
		case "O": stellarMass = STELLARCLASSIFICATIONTABLE_O_MASS[yerkesIndex]; break;
		case "B": stellarMass = STELLARCLASSIFICATIONTABLE_B_MASS[yerkesIndex]; break;
		case "A": stellarMass = STELLARCLASSIFICATIONTABLE_A_MASS[yerkesIndex]; break;
		case "F": stellarMass = STELLARCLASSIFICATIONTABLE_F_MASS[yerkesIndex]; break;
		case "G": stellarMass = STELLARCLASSIFICATIONTABLE_G_MASS[yerkesIndex]; break;
		case "K": stellarMass = STELLARCLASSIFICATIONTABLE_K_MASS[yerkesIndex]; break;
		case "M": stellarMass = STELLARCLASSIFICATIONTABLE_M_MASS[yerkesIndex]; break;
		case "D": stellarMass = STELLARCLASSIFICATIONTABLE_D_MASS[intNumericValue]; break;
	}

	return stellarMass;
}

float lookupStellarRadius(std::string harvardLetter, uint8_t yerkesIndex)
{
//	Initialize return value
	float stellarRadius;
	switch (harvardLetter)
	{
		case "O": stellarRadius = STELLARCLASSIFICATIONTABLE_O_RADIUS[yerkesIndex]; break;
		case "B": stellarRadius = STELLARCLASSIFICATIONTABLE_B_RADIUS[yerkesIndex]; break;
		case "A": stellarRadius = STELLARCLASSIFICATIONTABLE_A_RADIUS[yerkesIndex]; break;
		case "F": stellarRadius = STELLARCLASSIFICATIONTABLE_F_RADIUS[yerkesIndex]; break;
		case "G": stellarRadius = STELLARCLASSIFICATIONTABLE_G_RADIUS[yerkesIndex]; break;
		case "K": stellarRadius = STELLARCLASSIFICATIONTABLE_K_RADIUS[yerkesIndex]; break;
		case "M": stellarRadius = STELLARCLASSIFICATIONTABLE_M_RADIUS[yerkesIndex]; break;
		case "D": stellarRadius = STELLARCLASSIFICATIONTABLE_D_RADIUS[intNumericValue]; break;
	}

	return stellarRadius;
}

float lookupStellarTemperature(std::string harvardLetter, uint8_t yerkesIndex)
{
//	Initialize return value
	float stellarTemperature;
	switch (harvardLetter)
	{
		case "O": stellarTemperature = STELLARCLASSIFICATIONTABLE_O_TEMP[yerkesIndex]; break;
		case "B": stellarTemperature = STELLARCLASSIFICATIONTABLE_B_TEMP[yerkesIndex]; break;
		case "A": stellarTemperature = STELLARCLASSIFICATIONTABLE_A_TEMP[yerkesIndex]; break;
		case "F": stellarTemperature = STELLARCLASSIFICATIONTABLE_F_TEMP[yerkesIndex]; break;
		case "G": stellarTemperature = STELLARCLASSIFICATIONTABLE_G_TEMP[yerkesIndex]; break;
		case "K": stellarTemperature = STELLARCLASSIFICATIONTABLE_K_TEMP[yerkesIndex]; break;
		case "M": stellarTemperature = STELLARCLASSIFICATIONTABLE_M_TEMP[yerkesIndex]; break;
		case "D": stellarTemperature = STELLARCLASSIFICATIONTABLE_D_TEMP[intNumericValue]; break;
	}

	return stellarTemperature;
}


//	Determine stellar parameters
star_t extrapolateStellarParameters(star_t newStar, std::string harvardLetter, std::string yerkesClassification, bool floatOrIntNumericValue, bool massPreset, bool radiusPreset, bool tempPreset, float floatNumericValue, uint8_t intNumericValue)
{
//	Check parameters
//	std::cout << "harvardLetter = " << harvardLetter << std::endl;
//	std::cout << "numericValue = " << numericValue << std::endl;
//	std::cout << "yerkesClassification = " << yerkesClassification << std::endl;

//	Generate variance

//	Initialize Yerkes index
	uint8_t yerkesIndex;

//	If numericValue is a float
	if (floatOrIntNumericValue == false)
	{
		intNumericValue = rint(floatNumericValue);
//		Initialize multiplier
		float floatMultiplier = (intNumericValue >= floatNumericValue) ? floatNumericValue - (intNumericValue - 1) : floatNumericValue - intNumericValue;
	}

//	Otherwise
	switch (yerkesClassification)
	{
		case "Ia":	yerkesIndex = YERKESCLASSIFICATIONINDEX_IA[intNumericValue]; break;
		case "Ib":	yerkesIndex = YERKESCLASSIFICATIONINDEX_IB[intNumericValue]; break;
		case "II":	yerkesIndex = YERKESCLASSIFICATIONINDEX_II[intNumericValue]; break;
		case "III":	yerkesIndex = YERKESCLASSIFICATIONINDEX_III[intNumericValue]; break;
		case "IV":	yerkesIndex = YERKESCLASSIFICATIONINDEX_IV[intNumericValue]; break;
		case "V":	yerkesIndex = YERKESCLASSIFICATIONINDEX_V[intNumericValue]; break;
		case "sd":	yerkesIndex = YERKESCLASSIFICATIONINDEX_SD[intNumericValue]; break;
	}

//	Check preset flags
	if (massPreset == false)
	{
		float massVariance = floatRNG(-0.05, 0.05);
		newStar.stellarMass = lookupStellarMass(harvardLetter, yerkesIndex);
		if (floatOrIntNumericValue == false)	{newStar.stellarMass += (newStar.stellarMass * floatMultiplier);}
		newStar.stellarMass += (newStar.stellarMass * massVariance);
	}

//	Check preset flags
	if (radiusPreset == false)
	{
		float radiusVariance = floatRNG(-0.05, 0.05);
		newStar.stellarRadius = lookupStellarRadius(harvardLetter, yerkesIndex);
		if (floatOrIntNumericValue == false)	{newStar.stellarRadius += (newStar.stellarRadius * floatMultiplier);}
		newStar.stellarRadius += (newStar.stellarRadius * radiusVariance);
	}

//	Check preset flags
	if (tempPreset == false)
	{
		float temperatureVariance = floatRNG(-0.05, 0.05);
		newStar.stellarTemperature = lookupStellarTemperature(harvardLetter, yerkesIndex);
		if (floatOrIntNumericValue == false)	{newStar.stellarTemperature += (newStar.stellarTemperature * floatMultiplier);}
		newStar.stellarTemperature += (newStar.stellarTemperature * temperatureVariance);
	}

	return newStar;
}

//	Determine Harvard classification
std::string getHarvardLetter(std::string starType)
{
//	Check starType
//	std::cout << "starType = " << starType << std::endl;

//	Harvard classification letter
	std::string harvardLetter;

//	Check for O
	if 		(std::regex_search(starType, "\bO") == true)	{harvardLetter = "O";}

//	Check for B
	else if (std::regex_search(starType, "\bB") == true)	{harvardLetter = "B";}

//	Check for A
	else if (std::regex_search(starType, "\bA") == true)	{harvardLetter = "A";}

//	Check for F
	else if (std::regex_search(starType, "\bF") == true)	{harvardLetter = "F";}

//	Check for G
	else if (std::regex_search(starType, "\bG") == true)	{harvardLetter = "G";}

//	Check for K
	else if (std::regex_search(starType, "\bK") == true)	{harvardLetter = "K";}

//	Check for M
	else if (std::regex_search(starType, "\bM") == true)	{harvardLetter = "M";}

//	Check for D
	else if (std::regex_search(starType, "\bD") == true)	{harvardLetter = "D";}

// Check for error
	else
	{
		std::cout << "ERROR: starType == " << starType << std::endl;
	}

	return harvardLetter;
}

//	Loop through index tables to find a match
std::string checkYerkesIndexTable(uint8_t index)
{
//	Check index value
//	std::cout << "Yerkes index value = " << index << std::endl;
//	Initialize return value
	std::string yerkesClassification;
//	Flag to break out of for loop
	bool matchFound;
//	Loop through index tables
	for (uint8_t i = 0; i < 10; i++)
	{
		switch (index)
		{
			case YERKESCLASSIFICATIONINDEX_IA[i]: 	yerkesClassification = "Ia"; matchFound = true; break;
			case YERKESCLASSIFICATIONINDEX_IB[i]: 	yerkesClassification = "Ib"; matchFound = true; break;
			case YERKESCLASSIFICATIONINDEX_II[i]: 	yerkesClassification = "II"; matchFound = true; break;
			case YERKESCLASSIFICATIONINDEX_III[i]: 	yerkesClassification = "III"; matchFound = true; break;
			case YERKESCLASSIFICATIONINDEX_IV[i]: 	yerkesClassification = "IV"; matchFound = true; break;
			case YERKESCLASSIFICATIONINDEX_V[i]: 	yerkesClassification = "V"; matchFound = true; break;
			case YERKESCLASSIFICATIONINDEX_SD[i]: 	yerkesClassification = "sd"; matchFound = true; break;
		}
//		Break if matchFound == true
		if (matchFound == true) {break;}
	}

	return yerkesClassification;
}

//	Get Yerkes classification
std::string getYerkesClassification(std::string harvardLetter, double originalLuminosity)
{
//	Check parameters
//	std::cout << "harvardLetter = " << harvardLetter << std::endl;
//	std::cout << "originalLuminosity = " << originalLuminosity << std::endl;

//	Initialize return value
	std::string yerkesClassification;
//	Loop through the Harvard classification's table
	for (uint8_t i = 0; i < STELLARCLASSIFICATIONTABLE_X_OBAFGKM; i++)
	{
//		Check for O
		if (harvardLetter == "O")
		{
//			If the luminosity is close enough
			if (rint (originalLuminosity / STELLARCLASSIFICATIONTABLE_O_LUMINOSITY[i]) == 1)
			{
				yerkesClassification = checkYerkesIndexTable(i);
				return yerkesClassification;
			}
		}

//		Check for B
		else if (harvardLetter == "B")
		{
//			If the luminosity is close enough
			if (rint (originalLuminosity / STELLARCLASSIFICATIONTABLE_B_LUMINOSITY[i]) == 1)
			{
				yerkesClassification = checkYerkesIndexTable(i);
				return yerkesClassification;
			}
		}

//		Check for A
		else if (harvardLetter == "A")
		{
//			If the luminosity is close enough
			if (rint (originalLuminosity / STELLARCLASSIFICATIONTABLE_A_LUMINOSITY[i]) == 1)
			{
				yerkesClassification = checkYerkesIndexTable(i);
				return yerkesClassification;
			}
		}

//		Check for F
		else if (harvardLetter == "F")
		{
//			If the luminosity is close enough
			if (rint (originalLuminosity / STELLARCLASSIFICATIONTABLE_F_LUMINOSITY[i]) == 1)
			{
				yerkesClassification = checkYerkesIndexTable(i);
				return yerkesClassification;
			}
		}

//		Check for G
		else if (harvardLetter == "G")
		{
//			If the luminosity is close enough
			if (rint (originalLuminosity / STELLARCLASSIFICATIONTABLE_G_LUMINOSITY[i]) == 1)
			{
				yerkesClassification = checkYerkesIndexTable(i);
				return yerkesClassification;
			}
		}

//		Check for K
		else if (harvardLetter == "K")
		{
//			If the luminosity is close enough
			if (rint (originalLuminosity / STELLARCLASSIFICATIONTABLE_K_LUMINOSITY[i]) == 1)
			{
				yerkesClassification = checkYerkesIndexTable(i);
				return yerkesClassification;
			}
		}

//		Check for M
		else if (harvardLetter == "M")
		{
//			If the luminosity is close enough
			if (rint (originalLuminosity / STELLARCLASSIFICATIONTABLE_M_LUMINOSITY[i]) == 1)
			{
				yerkesClassification = checkYerkesIndexTable(i);
				return yerkesClassification;
			}
		}

//		Check for D
		else if (harvardLetter == "D")
		{
			std::cout << "White dwarves have no Yerkes classification" << std::endl;
			yerkesClassification = "";
			return yerkesClassification;
		}

//		No Harvard letter found
		else
		{
			std::cout << "No Harvard match found" << std::endl;
			break;
		}
	}
}

//	Get numeric value
uint8_t getNumericValue(std::string yerkesClassification, double originalLuminosity)
{
//	Check for parameter errors
	if (std::regex_search(yerkesClassification, YERKESREGEX) != true)
	{
		std::cout << "No Yerkes classification passed" << std::endl;
		return 0;
	}

	if (originalLuminosity == 0)
	{
		std::cout << "originalLuminosity == 0" << std::endl;
		return 0;
	}

//	Initialize return value
	uint8_t numericValue;
//	Initialize tables to use
	float luminosity_YTable[10];
	float luminosity_HYTable[10];

//	Determine Harvard and Yerkes index table
	for (uint8_t i = 0; i < YERKESCLASSIFCATIONINDEX_LENGTH; i++)
	{
		switch (yerkesClassification)
		{
			case "Ia":	luminosity_YTable[i] = YERKESCLASSIFICATIONINDEX_IA[i]; break;
			case "Ib":	luminosity_YTable[i] = YERKESCLASSIFICATIONINDEX_IB[i]; break;
			case "II":	luminosity_YTable[i] = YERKESCLASSIFICATIONINDEX_II[i]; break;
			case "III":	luminosity_YTable[i] = YERKESCLASSIFICATIONINDEX_III[i]; break;
			case "IV":	luminosity_YTable[i] = YERKESCLASSIFICATIONINDEX_IV[i]; break;
			case "V":	luminosity_YTable[i] = YERKESCLASSIFICATIONINDEX_V[i]; break;
			case "sd":	luminosity_YTable[i] = YERKESCLASSIFICATIONINDEX_SD[i]; break;
		}

		switch (harvardLetter)
		{
			case "O": luminosity_HYTable[i] = STELLARCLASSIFICATIONTABLE_O_LUMINOSITY[luminosity_YTable[i]]; break;
			case "B": luminosity_HYTable[i] = STELLARCLASSIFICATIONTABLE_B_LUMINOSITY[luminosity_YTable[i]]; break;
			case "A": luminosity_HYTable[i] = STELLARCLASSIFICATIONTABLE_A_LUMINOSITY[luminosity_YTable[i]]; break;
			case "F": luminosity_HYTable[i] = STELLARCLASSIFICATIONTABLE_F_LUMINOSITY[luminosity_YTable[i]]; break;
			case "G": luminosity_HYTable[i] = STELLARCLASSIFICATIONTABLE_G_LUMINOSITY[luminosity_YTable[i]]; break;
			case "K": luminosity_HYTable[i] = STELLARCLASSIFICATIONTABLE_K_LUMINOSITY[luminosity_YTable[i]]; break;
			case "M": luminosity_HYTable[i] = STELLARCLASSIFICATIONTABLE_M_LUMINOSITY[luminosity_YTable[i]]; break;
			case "D": luminosity_HYTable[i] = STELLARCLASSIFICATIONTABLE_D_LUMINOSITY[i]; break;
		}
	}

//	Loop through luminosity_HYTable
	if (originalLuminosity <= luminosity_HYTable[0])	{numericValue = 0;}
	else
	{
		for (uint8_t i = 1; i < YERKESCLASSIFCATIONINDEX_LENGTH; i++)
		{
			if (luminosity_HYTable[i - 1] <= originalLuminosity && originalLuminosity < luminosity_HYTable[i])	{numericValue = i;}
			else																								{numericValue = 9;}
		}
	}

//	Return numericValue
	return numericValue;
}

//	This function completes stellar classification and determines physical parameters
star_t completeStellarClassification(std::string starType, double originalLuminosity, bool massPreset, bool radiusPreset, bool tempPreset)
{
//	Check parameters
//	std::cout << "starType = " << starType << std::endl;
//	std::cout << "originalLuminosity = " << originalLuminosity << std::endl;

//	Initialize return value
	star_t newStar;

//	Check for Yerkes classification
	std::smatch yerkesMatch;
	yerkesPresent = std::regex_search(starType, yerkesMatch, YERKESREGEX);

//	Check for numeric value
	std::smatch numericMatch;
	numberPresent = std::regex_search(starType, numericMatch, NUMERICREGEX);
	bool floatOrIntNumericValue;

//	Check for Harvard letter
	std::smatch harvardMatch
	harvardPresent = std::regex_search(starType, harvardMatch, HARVARDREGEX);

//	Initialize return values
	std::string harvardLetter;
	std::string yerkesClassification;
	float numericValue;

//	Start with Harvard classification
	if (harvardPresent == false)
	{
//		Call getHarvardLetter
		harvardLetter = getHarvardLetter(starType);
	}

//	Extract Harvard letter if present
	else{harvardLetter = harvardMatch.str(0);}

//	If there is no Yerkes classification
	if (yerkesPresent == false)
	{
//		Call getYerkesClassification
		yerkesClassification = getYerkesClassification(harvardLetter, originalLuminosity);
	}

//	Extract Yerkes classification if present
	else	{yerkesClassification = yerkesMatch.str(0);}

//	If there is no numeric value
	if (numberPresent == false)
	{
		numericValue = getNumericValue(yerkesClassification, originalLuminosity);
		floatOrIntNumericValue = true;
	}

//	Extract numeric value if present
	else
	{
		numericValue = numericMatch.str(0);
		floatOrIntNumericValue = false;
	}

//	Determine physical parameters
	newStar = extrapolateStellarParameters(newStar, harvardLetter, yerkesClassification, floatOrIntNumericValue, massPreset, radiusPreset, tempPreset, numericValue, numericValue);
//	Assign classification
	newStar.harvardLetter = harvardLetter;
	newStar.yerkesClassification = yerkesClassification;
	newStar.numericValue = numericValue;

//	Return newStar
	return newStar;
}
