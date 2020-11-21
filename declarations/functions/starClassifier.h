#ifndef STARCLASSIFIER
#define STARCLASSIFIER

//	C++ libraries
#include <string>

//	Structure declarations
#include "../structures/star_t.h"

//	Lookup physical parameters
float lookupStellarMass(std::string harvardLetter, uint8_t yerkesIndex);
float lookupStellarRadius(std::string harvardLetter, uint8_t yerkesIndex);
float lookupStellarTemperature(std::string harvardLetter, uint8_t yerkesIndex);

//	Determine stellar parameters
star_t extrapolateStellarParameters(star_t newStar, std::string harvardLetter, std::string yerkesClassification, bool floatOrIntNumericValue, bool massPreset, bool radiusPreset, bool tempPreset, float floatNumericValue, uint8_t intNumericValue);

//	Determine Harvard classification
std::string getHarvardLetter(std::string starType);

//	Loop through index tables to find a match
std::string checkYerkesIndexTable(uint8_t index);

//	Get Yerkes classification
std::string getYerkesClassification(std::string harvardLetter, double originalLuminosity);

//	Get numeric value
uint8_t getNumericValue(std::string yerkesClassification, double originalLuminosity);

//	This function completes stellar classification and determines physical parameters
star_t completeStellarClassification(std::string starType, double originalLuminosity, bool massPreset, bool radiusPreset, bool tempPreset);

#endif
