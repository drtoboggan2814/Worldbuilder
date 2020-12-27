/*
	These functions determine the characteristics of the gas giant closest to
	the primary in this system.
*/

//	C++ libraries
#include <tuple>

//	Third party
#include "../third_party/rapidcsv.h"

char gasGiantArrangementTable();

bool csv_starWorldMatch(star_t& star, rapidcsv::Document& worldDoc);

bool csv_checkForConventionalGasGiant(const float& snowLineRadius, rapidcsv::Document& worldDoc, const int& firstWorldIndex, const int& numberOfPlanets);

bool csv_checkForEccentricGasGiant(rapidcsv::Document& worldDoc, const int& firstWorldDocIndex, const int& numberOfPlanets);

bool csv_checkForEpistellarGasGiant(rapidcsv::Document& worldDoc, const int& firstWorldDocIndex, const int& numberOfPlanets);

int csv_determineNumberOfCSVPlanets(rapidcsv::Document& worldDoc, const int& firstWorldDocIndex);

std::tuple<int, bool, char, float, int> csv_determineGasGiantArrangement(star_t& star, rapidcsv::Document& worldDoc);

//	This function returns the orbital radius of the first gas giant in the system
float placeFirstGasGiant(const float& snowLineRadius, const char& gasGiantType);
