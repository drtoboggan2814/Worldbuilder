/*
	These functions determine the characteristics of the gas giant closest to
	the primary in this system.
*/

//	C++ libraries
#include <string>
#include <tuple>

//	Third party
#include "../third_party/rapidcsv.h"

char gasGiantArrangementTable();

bool csv_starWorldMatch(rapidcsv::Document& worldDoc, std::string hipIndex, std::string hdIndex, std::string glieseIndex, std::string properName, int i);

bool csv_checkForConventionalGasGiant(float snowLineRadius, rapidcsv::Document& worldDoc, int firstWorldIndex, int numberOfPlanets);

bool csv_checkForEccentricGasGiant(rapidcsv::Document& worldDoc, int firstWorldDocIndex, int numberOfPlanets);

bool csv_checkForEpistellarGasGiant(rapidcsv::Document& worldDoc, int firstWorldDocIndex, int numberOfPlanets);

int csv_determineNumberOfCSVPlanets(rapidcsv::Document& worldDoc, int firstWorldDocIndex);

std::tuple<int, bool, char, float, int> csv_determineGasGiantArrangement(star_t primary, rapidcsv::Document& starDoc, rapidcsv::Document& worldDoc, float snowLineRadius, std::string hipIndex, std::string hdIndex, std::string glieseIndex, std::string properName, int currentCSVIndex);

//	This function returns the orbital radius of the first gas giant in the system
float placeFirstGasGiant(float snowLineRadius, char gasGiantType, float innerLimitRadius);
