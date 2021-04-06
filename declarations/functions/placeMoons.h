//	Gas giants
#include <cstdint>
//	Generate the number of moonlets in the gas giant's first family

int getFirstFamily(float distanceToPrimary);

//	See how visible the ring system is

//	0 is not visible, 1 can be seen through a telescope, 2 is comparable to Saturn

int getRingSystemVisibility(int moonlets);

int getSecondFamily(float distanceToPrimary);

int getThirdFamily(float distanceToPrimary);

int getTerrestrialMajorMoons(float distanceToPrimary, char worldType);

int getTerrestrialMoonlets(float distanceToPrimary, char worldType);

//	Determine the size of the major moon

int moonSizeTable();
