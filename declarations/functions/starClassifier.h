#ifndef STARCLASSIFIER
#define STARCLASSIFIER

//	C++ libraries
#include <string>
#include <tuple>

//	Structure declarations
#include "../structures/star_t.h"

//	Lookup physical parameters
float lookupStellarMass(std::string& harvardLetter, const char& yerkesIndex);
float lookupStellarRadius(std::string& harvardLetter, const char& yerkesIndex);
float lookupStellarTemperature(std::string& harvardLetter, const char& yerkesIndex);

//	Determine stellar parameters
std::tuple<float, float, float> extrapolateStellarParameters(int currentCSVIndex, rapidcsv::Document& starDoc, std::string harvardLetter, std::string yerkesClassification, bool floatOrIntNumericValue, bool massPreset, bool radiusPreset, bool tempPreset, float floatNumericValue, int intNumericValue);

//	Determine Harvard classification
std::string getHarvardLetter(std::string& starType);

//	Loop through index tables to find a match
std::string checkYerkesIndexTable(int index);

//	Get Yerkes classification
std::string getYerkesClassification(std::string& harvardLetter, const double& originalLuminosity);

//	Get numeric value
uint8_t getNumericValue(std::string& yerkesClassification, const double& originalLuminosity);

//	This function completes stellar classification and determines physical parameters
std::tuple<std::string, std::string, float, bool> completeStellarClassification(std::string starType, const double& originalLuminosity, bool massPreset, bool radiusPreset, bool tempPreset);

#endif
