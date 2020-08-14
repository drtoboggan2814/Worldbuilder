#include "declarations/constants/climateStepConstants.h"
#include <string>

using namespace std;

int climateStepLookup(string worldType)
{
	int step;

	if 		(worldType == "Asteroid Belt") 													{step = step_AsteroidBelt;}
	else if (worldType == "Tiny (Ice)" || worldType == "Tiny (Sulfur)") 					{step = step_Tiny_IceorSulfur;}
	else if (worldType == "Tiny (Rock)") 													{step = step_Tiny_Rock;}
	else if (worldType == "Small (Hadean)") 												{step = step_Small_Hadean;}
	else if (worldType == "Small (Ice)") 													{step = step_Small_Ice;}
	else if (worldType == "Small (Rock)") 													{step = step_Small_Rock;}
	else if (worldType == "Standard (Hadean)") 												{step = step_Standard_Hadean;}
	else if (worldType == "Standard (Ammonia)") 											{step = step_Standard_Ammonia;}
	else if (worldType == "Standard (Ice)") 												{step = step_Standard_Ice;}
	else if (worldType == "Standard (Ocean)" || worldType == "Standard (Garden)") 			{step = step_Standard_OceanorGarden;}
	else if (worldType == "Standard (Greenhouse)" || worldType == "Standard (Chthonian)")	{step = step_Standard_GreenhouseorChthonian;}
	else if (worldType == "Large (Ammonia)") 												{step = step_Large_Ammonia;}
	else if (worldType == "Large (Ice)") 													{step = step_Large_Ice;}
	else if (worldType == "Large (Ocean)" || worldType == "Large (Garden)") 				{step = step_Large_OceanorGarden;}
	else if (worldType == "Large (Greenhouse)" || worldType == "Large (Chthonian)") 		{step = step_Large_GreenhouseorChthonian;}

	return step;
}
