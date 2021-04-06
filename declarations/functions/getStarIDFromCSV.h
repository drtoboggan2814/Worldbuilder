#ifndef GETSTARIDFROMCSV
#define GETSTARIDFROMCSV
//	C++ libraries
#include <string>
#include <tuple>

//	Third party libraries
#include "../third_party/rapidcsv.h"

std::tuple<int, int, int, int, std::string, std::string, std::string, std::string> getStarIDFromCSV(rapidcsv::Document& starDoc, int currentCSVIndex, std::string starConstellation);
#endif
