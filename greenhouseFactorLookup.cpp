#include "declarations/constants/greenhouseFactorConstants.h"
#include <string>

using namespace std;

float greenhouseFactorLookup(string worldType, float hydrographicCoverage)
{
	float gf;

	if 		(worldType == "Asteroid Belt") 																																														{gf = gf_AsteroidBelt;}
	else if (worldType == "Tiny (Ice)") 																																														{gf = gf_Tiny_Ice;}
	else if (worldType == "Tiny (Sulfur)") 																																														{gf = gf_Tiny_Sulfur;}
	else if (worldType == "Tiny (Rock)") 																																														{gf = gf_Tiny_Rock;}
	else if (worldType == "Small (Hadean)") 																																													{gf = gf_Small_Hadean;}
	else if (worldType == "Small (Ice)") 																																														{gf = gf_Small_Ice;}
	else if (worldType == "Small (Rock)") 																																														{gf = gf_Small_Rock;}
	else if (worldType == "Standard (Hadean)") 																																													{gf = gf_Standard_Hadean;}
	else if (worldType == "Standard (Ammonia)" 		|| worldType == "Large (Ammonia)")																																			{gf = gf_StandardLarge_Ammonia;}
	else if (worldType == "Standard (Ice)" 			|| worldType == "Large (Ice)") 																																				{gf = gf_StandardLarge_Ice;}
	else if (worldType == "Standard (Ocean)" 		|| worldType == "Large (Ocean)" 	|| worldType == "Standard (Garden)" || worldType == "Large (Garden)" && hydrographicCoverage <= 0.2) 									{gf = gf_StandardLarge_OceanGarden_00;}
	else if (worldType == "Standard (Ocean)" 		|| worldType == "Large (Ocean)" 	|| worldType == "Standard (Garden)" || worldType == "Large (Garden)" && hydrographicCoverage > 0.2 && hydrographicCoverage <= 0.5) 		{gf = gf_StandardLarge_OceanGarden_01;}
	else if (worldType == "Standard (Ocean)" 		|| worldType == "Large (Ocean)" 	|| worldType == "Standard (Garden)" || worldType == "Large (Garden)" && hydrographicCoverage > 0.5 && hydrographicCoverage <= 0.9) 		{gf = gf_StandardLarge_OceanGarden_02;}
	else if (worldType == "Standard (Ocean)" 		|| worldType == "Large (Ocean)" 	|| worldType == "Standard (Garden)" || worldType == "Large (Garden)" && hydrographicCoverage > 0.9) 									{gf = gf_StandardLarge_OceanGarden_03;}
	else if (worldType == "Standard (Chthonian)" 	|| worldType == "Large (Chthonian)")																																		{gf = gf_StandardLarge_Chthonian;}
	else if (worldType == "Standard (Greenhouse)" 	|| worldType == "Large (Greenhouse)")																																		{gf = gf_StandardLarge_Greenhouse;}

	return gf;
}
