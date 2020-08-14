#include "declarations/constants/absorptionFactorConstants.h"
#include <string>

using namespace std;

float absorptionFactorLookup(string worldType, float hydrographicCoverage)
{
	float af;

	if 		(worldType == "Asteroid Belt") 																																														{af = af_AsteroidBelt;}
	else if (worldType == "Tiny (Ice)") 																																														{af = af_Tiny_Ice;}
	else if (worldType == "Tiny (Sulfur)") 																																														{af = af_Tiny_Sulfur;}
	else if (worldType == "Tiny (Rock)") 																																														{af = af_Tiny_Rock;}
	else if (worldType == "Small (Hadean)") 																																													{af = af_Small_Hadean;}
	else if (worldType == "Small (Ice)") 																																														{af = af_Small_Ice;}
	else if (worldType == "Small (Rock)") 																																														{af = af_Small_Rock;}
	else if (worldType == "Standard (Hadean)") 																																													{af = af_Standard_Hadean;}
	else if (worldType == "Standard (Ammonia)" 		|| worldType == "Large (Ammonia)")																																			{af = af_StandardLarge_Ammonia;}
	else if (worldType == "Standard (Ice)" 			|| worldType == "Large (Ice)") 																																				{af = af_StandardLarge_Ice;}
	else if (worldType == "Standard (Ocean)" 		|| worldType == "Large (Ocean)" 	|| worldType == "Standard (Garden)" || worldType == "Large (Garden)" && hydrographicCoverage <= 0.2) 									{af = af_StandardLarge_OceanGarden_00;}
	else if (worldType == "Standard (Ocean)" 		|| worldType == "Large (Ocean)" 	|| worldType == "Standard (Garden)" || worldType == "Large (Garden)" && hydrographicCoverage > 0.2 && hydrographicCoverage <= 0.5) 		{af = af_StandardLarge_OceanGarden_01;}
	else if (worldType == "Standard (Ocean)" 		|| worldType == "Large (Ocean)" 	|| worldType == "Standard (Garden)" || worldType == "Large (Garden)" && hydrographicCoverage > 0.5 && hydrographicCoverage <= 0.9) 		{af = af_StandardLarge_OceanGarden_02;}
	else if (worldType == "Standard (Ocean)" 		|| worldType == "Large (Ocean)" 	|| worldType == "Standard (Garden)" || worldType == "Large (Garden)" && hydrographicCoverage > 0.9) 									{af = af_StandardLarge_OceanGarden_03;}
	else if (worldType == "Standard (Chthonian)" 	|| worldType == "Large (Chthonian)")																																		{af = af_StandardLarge_Chthonian;}
	else if (worldType == "Standard (Greenhouse)" 	|| worldType == "Large (Greenhouse)")																																		{af = af_StandardLarge_Greenhouse;}

	return af;
}
