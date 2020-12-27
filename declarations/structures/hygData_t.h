#ifndef HYGDATA_T
#define HYGDATA_T
//	This struct represents data extracted from the HYG catalog

//	C++ Libraries
#include <string>

struct hygData_t
{
	std::string hygID;
	std::string hipID;
	std::string hdID;
	std::string hrID;
	std::string glID;
	std::string bfID;
	std::string rightAscension;
	std::string declination;
	std::string properName;
	std::string distance;
	std::string pm_ra;
	std::string pm_dec;
	std::string visMag;
	std::string avsMag;
	std::string spectralType;
	std::string colorIndex;
	std::string xCoord;
	std::string yCoord;
	std::string zCoord;
	std::string vXCoord;
	std::string vYCoord;
	std::string vZCoord;
	std::string raRad;
	std::string decRad;
	std::string pmRaRad;
	std::string pmDecRad;
	std::string bayerVal;
	std::string flamVal;
	std::string constellation;
	std::string component;
	std::string componentPrimary;
	std::string systemID;
	std::string luminosity;
	std::string varID;
	std::string varMin;
	std::string varMax;
};

#endif
