#include "declarations/constants/climateMinConstants.h"
#include <string>
using namespace std;

int climateMinLookup(string worldType)
{
	int min;
	
	if 		(worldType == "Asteroid Belt") 													{min = min_AsteroidBelt;}
	else if (worldType == "Tiny (Ice)" || worldType == "Tiny (Sulfur)") 					{min = min_Tiny_IceorSulfur;}
	else if (worldType == "Tiny (Rock)") 													{min = min_Tiny_Rock;}
	else if (worldType == "Small (Hadean)") 												{min = min_Small_Hadean;}
	else if (worldType == "Small (Ice)") 													{min = min_Small_Ice;}
	else if (worldType == "Small (Rock)") 													{min = min_Small_Rock;}
	else if (worldType == "Standard (Hadean)") 												{min = min_Standard_Hadean;}
	else if (worldType == "Standard (Ammonia)") 											{min = min_Standard_Ammonia;}
	else if (worldType == "Standard (Ice)") 												{min = min_Standard_Ice;}
	else if (worldType == "Standard (Ocean)" || worldType == "Standard (Garden)") 			{min = min_Standard_OceanorGarden;}
	else if (worldType == "Standard (Greenhouse)" || worldType == "Standard (Chthonian)")	{min = min_Standard_GreenhouseorChthonian;}
	else if (worldType == "Large (Ammonia)") 												{min = min_Large_Ammonia;}
	else if (worldType == "Large (Ice)") 													{min = min_Large_Ice;}
	else if (worldType == "Large (Ocean)" || worldType == "Large (Garden)") 				{min = min_Large_OceanorGarden;}
	else if (worldType == "Large (Greenhouse)" || worldType == "Large (Chthonian)") 		{min = min_Large_GreenhouseorChthonian;}

	return min;
}
