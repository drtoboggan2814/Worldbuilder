//	Gas giants
#include <cstdint>
//	Generate the number of moonlets in the gas giant's first family

int8_t getFirstFamily(float distanceToPrimary);

//	See how visible the ring system is

//	0 is not visible, 1 can be seen through a telescope, 2 is comparable to Saturn

int8_t getRingSystemVisibility(int moonlets);

int8_t getSecondFamily(float distanceToPrimary);

int8_t getThirdFamily(float distanceToPrimary);

int8_t getTerrestrialMajorMoons(float distanceToPrimary, const char& worldType);

int8_t getTerrestrialMoonlets(float distanceToPrimary, const char& worldType);

//	Determine the size of the major moon

int8_t moonSizeTable();
