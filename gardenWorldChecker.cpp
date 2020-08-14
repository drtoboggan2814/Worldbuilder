#include <string>

using namespace std;

//	This function checks if there is a garden world present in the system
bool gardenWorldChecker(string worldType)
{
	if (worldType == "Standard (Garden)" || worldType == "Large (Garden)")
	{
		return true;
	}

	else
	{
		return false;
	}
}
