//	C++ libraries
#include <string>

//	Constant declarations
#include "declarations/constants/worldTypeConstants.h"

using namespace std;

//	This function checks if there is a garden world present in the system
bool gardenWorldChecker(char worldType)
{
	if (worldType == WT_STANDARD_GARDEN || worldType == WT_LARGE_GARDEN)
	{
		return true;
	}

	else
	{
		return false;
	}
}
