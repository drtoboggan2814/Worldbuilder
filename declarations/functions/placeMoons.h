//	Gas giants

//	Generate the number of moonlets in the gas giant's first family

int getFirstFamily(float distanceToPrimary);

//	See how visible the ring system is

//	0 is not visible, 1 can be seen through a telescope, 2 is comparable to Saturn

int getRingSystemVisibility(int moonlets);

int getSecondFamily(float distanceToPrimary);

int getThirdFamily(float distanceToPrimary);

int getTerrestrialMajorMoons(float distanceToPrimary, string worldType);

int getTerrestrialMoonlets(float distanceToPrimary, string worldType);

//	Determine the size of the major moon

int moonSizeTable();
