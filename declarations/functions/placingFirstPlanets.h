/*
	These functions determine the characteristics of the gas giant closest to
	the primary in this system.
*/

//	C++ libraries
#include <tuple>

//	Third party
#include "../third_party/rapidcsv.h"

char gasGiantArrangementTable();

bool csv_starWorldMatch(star_t star, rapidcsv::Document& worldDoc);

bool csv_checkForConventionalGasGiant(float snowLineRadius, rapidcsv::Document& worldDoc, int firstWorldIndex, int numberOfPlanets);

bool csv_checkForEccentricGasGiant(rapidcsv::Document& worldDoc, int firstWorldDocIndex, int numberOfPlanets);

bool csv_checkForEpistellarGasGiant(rapidcsv::Document& worldDoc, int firstWorldDocIndex, int numberOfPlanets);

int csv_determineNumberOfCSVPlanets(rapidcsv::Document& worldDoc, int firstWorldDocIndex);

std::tuple<int, bool, char, float, int> csv_determineGasGiantArrangement(star_t star, rapidcsv::Document& worldDoc);

//	This function returns the orbital radius of the first gas giant in the system
float placeFirstGasGiant(float snowLineRadius, char gasGiantType);
