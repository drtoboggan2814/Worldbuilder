//	This function checks what identifiers are present in starDoc and assigns them to the star
//	C++ libraries
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <tuple>

//	Third party libraries
#include "declarations/third_party/rapidcsv.h"

std::tuple<int, int, int, int, std::string, std::string> getStarIDFromCSV(rapidcsv::Document& starDoc, int currentCSVIndex)
{
//	If there is no entry for a numeric ID, assign it to the maximum value of int
//	If the string ID's are blank, they will be assigned ""
	int hipIndex 		= (starDoc.GetCell<std::string>("hip", currentCSVIndex) == "") ? std::numeric_limits<int>::max() : starDoc.GetCell<int>("hip", currentCSVIndex);
	std::cout << "hipIndex == " << hipIndex << std::endl;
	int hygIndex 		= (starDoc.GetRowName(currentCSVIndex) == "") ? std::numeric_limits<int>::max() : std::stoi(starDoc.GetRowName(currentCSVIndex));
	std::cout << "hygIndex == " << hygIndex << std::endl;
	int hdIndex 		= (starDoc.GetCell<std::string>("hd", currentCSVIndex) == "") ? std::numeric_limits<int>::max() : starDoc.GetCell<int>("hd", currentCSVIndex);
	std::cout << "hdIndex == " << hdIndex << std::endl;
	int hrIndex 		= (starDoc.GetCell<std::string>("hr", currentCSVIndex) == "") ? std::numeric_limits<int>::max() : starDoc.GetCell<int>("hr", currentCSVIndex);
	std::cout << "hrIndex == " << hrIndex << std::endl;
	std::string glieseIndex	= starDoc.GetCell<std::string>("gl", currentCSVIndex);
	std::cout << "glieseIndex == " << glieseIndex << std::endl;
	std::string properName		= starDoc.GetCell<std::string>("proper", currentCSVIndex);
	std::cout << "properName == " << properName << std::endl;

	return std::make_tuple(hipIndex, hygIndex, hdIndex, hrIndex, glieseIndex, properName);
}
