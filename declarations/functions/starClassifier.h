#ifndef STARCLASSIFIER
#define STARCLASSIFIER

//	C++ libraries
#include <string>
#include <tuple>

//	Structure declarations
#include "../structures/star_t.h"

std::tuple<int, int, int> getStarColor(std::string harvardLetter, char yerkesIndex, int intNumericValue);


//	Lookup physical parameters
float lookupStellarMass(std::string harvardLetter, char yerkesIndex);
float lookupStellarRadius(std::string harvardLetter, char yerkesIndex);
float lookupStellarTemperature(std::string harvardLetter, char yerkesIndex);

//	Determine stellar parameters
std::tuple<float, float, float, int, int, int> extrapolateStellarParameters(int currentCSVIndex, rapidcsv::Document& starDoc, std::string harvardLetter, std::string yerkesClassification, bool floatOrIntNumericValue, bool massPreset, bool radiusPreset, bool tempPreset, float floatNumericValue, int intNumericValue);

//	Determine Harvard classification
std::string getHarvardLetter(std::string starType);

//	Loop through index tables to find a match
std::string checkYerkesIndexTable(int index);

//	Get Yerkes classification
std::string getYerkesClassification(std::string harvardLetter, double originalLuminosity);

//	Get numeric value
char getNumericValue(std::string yerkesClassification, double originalLuminosity);

//	This function completes stellar classification and determines physical parameters
std::tuple<std::string, std::string, float, bool> completeStellarClassification(std::string starType, double originalLuminosity, bool massPreset, bool radiusPreset, bool tempPreset);

#endif
