//	Gas giants
#include <cstdint>
//	Generate the number of moonlets in the gas giant's first family

int8_t getFirstFamily(const float& distanceToPrimary);

//	See how visible the ring system is

//	0 is not visible, 1 can be seen through a telescope, 2 is comparable to Saturn

int8_t getRingSystemVisibility(const int& moonlets);

int8_t getSecondFamily(const float& distanceToPrimary);

int8_t getThirdFamily(const float& distanceToPrimary);

int8_t getTerrestrialMajorMoons(const float& distanceToPrimary, const char& worldType);

int8_t getTerrestrialMoonlets(const float& distanceToPrimary, const char& worldType);

//	Determine the size of the major moon

int8_t moonSizeTable();
