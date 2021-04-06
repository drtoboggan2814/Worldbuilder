//	C++ libraries
#include <string>
#include <tuple>

//	Constant declarations
#include "declarations/constants/gasGiantArrangementConstants.h"
#include "declarations/constants/unitConversions.h"
#include "declarations/constants/universalConstants.h"

//	Function declarations
#include "declarations/functions/diceRoller.h"

//	Structure declarations
#include "declarations/structures/star_t.h"

//	Third party
#include "declarations/third_party/rapidcsv.h"

/*
	These functions determine the characteristics of the gas giant closest to
	the primary in this system.
*/

char gasGiantArrangementTable()
{
	int diceRoll = diceRoller(6, 3);

	if (diceRoll <= 10) {return GGA_NO_GAS_GIANT;}
	else if (diceRoll == 11 || diceRoll == 12) {return GGA_CONVENTIONAL_GAS_GIANT;}
	else if (diceRoll == 13 || diceRoll == 14) {return GGA_ECCENTRIC_GAS_GIANT;}
	else {return GGA_EPISTELLAR_GAS_GIANT;}
}

//	This function returns the orbital radius of the first gas giant in the system
float placeFirstGasGiant(float snowLineRadius, char gasGiantType, float innerLimitRadius)
{
//	Initialize return value
	float gasGiantOrbitalRadius = 0;
	int diceRoll = 0;
	if (gasGiantType == GGA_CONVENTIONAL_GAS_GIANT)
	{
		diceRoll = diceRoller(6, 2) - 2;
		gasGiantOrbitalRadius = ((0.05 * diceRoll) + 1) * snowLineRadius;
	}

	else if (gasGiantType == GGA_ECCENTRIC_GAS_GIANT)
	{
		diceRoll = diceRoller(6, 1);
		gasGiantOrbitalRadius = (diceRoll * 0.125) * snowLineRadius;
	}

	else
	{
		diceRoll = diceRoller(6, 3);
		gasGiantOrbitalRadius = (diceRoll * 0.1) * innerLimitRadius;
	}

	return gasGiantOrbitalRadius;
}


//	Check worldDoc and starDoc for a match
bool csv_starWorldMatch(rapidcsv::Document& worldDoc, std::string hipIndex, std::string hdIndex, std::string glieseIndex, std::string properName, int i)
{
//	Initialize return value
	bool matchFound = false;
//	Star identifiers converted to strings
	std::string hipString 	= "HIP " + hipIndex;
	std::string hdString	= "HD "	 + hdIndex;
//	Find firstWorldDocIndex
//	for (int i = 0; i < WORLDDOC_LENGTH; i++)
//	{
		if (worldDoc.GetCell<std::string>("hip_name", i) == (hipString) || worldDoc.GetCell<std::string>("hd_name", i) == (hdString) || worldDoc.GetCell<std::string>("hostname", i) == glieseIndex || worldDoc.GetCell<std::string>("hostname", i) == properName)	{matchFound = true;/* break;*/}
//		else																																																																{return false;}
//	}

	return matchFound;
}

//	Check for conventional gas giant
bool csv_checkForConventionalGasGiant(float snowLineRadius, rapidcsv::Document& worldDoc, int firstWorldIndex, int numberOfPlanets)
{
//	Initialize return value
	bool arrangementIsConventional = false;
//	Check each planet
	for (int i = firstWorldIndex; i < (firstWorldIndex + numberOfPlanets); i++)
	{
//		Check if the world's semiMajorAxis is greater than the star's snow line
		if (i < WORLDDOC_LENGTH)
		{
			std::cout << "csv_checkForConventionalGasGiant i == " << i << std::endl;
			if (worldDoc.GetCell<std::string>("pl_orbsmax", i) != "" && worldDoc.GetCell<std::string>("pl_orbsmax", i) != "~")
			{
				if (worldDoc.GetCell<float>("pl_orbsmax", i) >= snowLineRadius)
				{
					arrangementIsConventional = true;
					break;
				}
			}
		}
	}

	return arrangementIsConventional;

}

//	Check for eccentric Jupiter (eccentric gas giant)
//	Source:  Wittenmyer; Endl, Michael; Cochran, William D.; Levison, Harold F. (2007). "Dynamical and Observational Constraints on Additional Planets in Highly Eccentric Planetary Systems". The Astronomical Journal. 134 (3): 1276–1284.
bool csv_checkForEccentricGasGiant(rapidcsv::Document& worldDoc, int firstWorldDocIndex, int numberOfPlanets)
{
//	Initialize return value
	bool arrangementIsEccentric = false;
//	std::cout << "firstWorldDocIndex == " << firstWorldDocIndex << std::endl;
//	std::cout << "numberOfPlanets == " << numberOfPlanets << std::endl;
//	Check each planet
	for (int i = firstWorldDocIndex; i < (firstWorldDocIndex + numberOfPlanets); i++)
	{
//		Check if the eccentricity is greater than 0.6
	//	std::cout << "i == " << i << std::endl;
	//	Check if pl_orbeccen has a valid value
		if (worldDoc.GetCell<std::string>("pl_orbeccen", i) != "~")
		{
			if (worldDoc.GetCell<float>("pl_orbeccen", i) >= 0.6)
			{
				arrangementIsEccentric = true;
				break;
			}
		}
	}

	return arrangementIsEccentric;
}

//	Check for hot Jupiter (Epistellar gas giant)
//	Source:  Wang, Ji; Fischer, Debra A.; Horch, Elliott P.; Huang, Xu (2015). "On the Occurrence Rate of Hot Jupiters in Different Stellar Environments". The Astrophysical Journal. 799 (2): 229.
bool csv_checkForEpistellarGasGiant(rapidcsv::Document& worldDoc, int firstWorldDocIndex, int numberOfPlanets)
{
//	Initialize return value
	bool arrangementIsEpistellar = false;
//	Check each planet
	for (int i = firstWorldDocIndex; i < (firstWorldDocIndex + numberOfPlanets); i++)
	{
//		Check if the mass is greater than one tenth of Jupiter's and that the orbital period is less than ten days
//		Check if pl_bmasse and pl_orbper have valid values
		if (worldDoc.GetCell<std::string>("pl_bmasse", i) != "~" && worldDoc.GetCell<std::string>("pl_orbper", i) != "~")
		{
			if (worldDoc.GetCell<float>("pl_bmasse", i) > (0.1 * JUPITER_MASS_IN_EARTH_MASS) && worldDoc.GetCell<float>("pl_orbper", i) < 10)
			{
				arrangementIsEpistellar = true;
				break;
			}
		}
	}

	return arrangementIsEpistellar;
}

//	Determine the number of planets that orbit a star generated from a .csv
int csv_determineNumberOfCSVPlanets(rapidcsv::Document& worldDoc, int firstWorldDocIndex)
{
//	Initialize return value
	int numberOfPlanets = 0;

//	Check each world and if the next index is out of bounds
	if (worldDoc.GetCell<std::string>("pl_letter", firstWorldDocIndex) == "b")
	{
		numberOfPlanets = 1;
		if ((firstWorldDocIndex + 1) < WORLDDOC_LENGTH)
		{
			if (worldDoc.GetCell<std::string>("pl_letter", firstWorldDocIndex + 1) == "c")
			{
				numberOfPlanets = 2;
				if ((firstWorldDocIndex + 2) < WORLDDOC_LENGTH)
				{
					if (worldDoc.GetCell<std::string>("pl_letter", firstWorldDocIndex + 2) == "d")
					{
						numberOfPlanets = 3;
						if ((firstWorldDocIndex + 3) < WORLDDOC_LENGTH)
						{
							if (worldDoc.GetCell<std::string>("pl_letter", firstWorldDocIndex + 3) == "e")
							{
								numberOfPlanets = 4;
								if ((firstWorldDocIndex + 4) < WORLDDOC_LENGTH)
								{
									if (worldDoc.GetCell<std::string>("pl_letter", firstWorldDocIndex + 4) == "f")
									{
										numberOfPlanets = 5;
										if ((firstWorldDocIndex + 5) < WORLDDOC_LENGTH)
										{
											if (worldDoc.GetCell<std::string>("pl_letter", firstWorldDocIndex + 5) == "g")
											{
												numberOfPlanets = 6;
												if ((firstWorldDocIndex + 6) < WORLDDOC_LENGTH)
												{
													if (worldDoc.GetCell<std::string>("pl_letter", firstWorldDocIndex + 6) == "h")
													{
														numberOfPlanets = 7;
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return numberOfPlanets;
}

//	Determine the gas giant arrangement of a star generated from a .csv
std::tuple<int, bool, char, float, int> csv_determineGasGiantArrangement(star_t primary, rapidcsv::Document& starDoc, rapidcsv::Document& worldDoc, float snowLineRadius, std::string hipIndex, std::string hdIndex, std::string glieseIndex, std::string properName, int currentCSVIndex)
{
//	The first index for the star in worldDoc
	int firstWorldDocIndex = 0;
//	Number of planets for the star in worldDoc is 0 by default
	int numberOfPlanets = 0;

//	Initialize return values
	int planetDBIndex = 0;
	bool firstGasGiantPresent = false;
	char gasGiantArrangement = GGA_NO_GAS_GIANT;
	float firstGasGiantOrbitalRadius = 0;

//	Loop through worldDoc
	for (int i = 0; i < WORLDDOC_LENGTH; i++)
	{
//		Find firstWorldDocIndex
		if (csv_starWorldMatch(worldDoc, hipIndex, hdIndex, glieseIndex, properName, i) == true)
		{
//			Assign firstWorldDocIndex
			firstWorldDocIndex = i;
//			Assign numberOfPlanets
			numberOfPlanets = csv_determineNumberOfCSVPlanets(worldDoc, firstWorldDocIndex);
//			Check for hot Jupiter
			if 		(csv_checkForEpistellarGasGiant(worldDoc, firstWorldDocIndex, numberOfPlanets) == true || starDoc.GetCell<std::string>("gasGiantArrangement", currentCSVIndex) == "1")
			{
				planetDBIndex = i;
				firstGasGiantPresent = true;
				gasGiantArrangement = GGA_EPISTELLAR_GAS_GIANT;
				firstGasGiantOrbitalRadius = (worldDoc.GetCell<std::string>("pl_orbsmax", i) == "") ? placeFirstGasGiant(snowLineRadius, gasGiantArrangement, primary.innerLimitRadius) : worldDoc.GetCell<float>("pl_orbsmax", i);
				break;
			}
//			Check for eccentric gas giant
			else if (csv_checkForEccentricGasGiant(worldDoc, firstWorldDocIndex, numberOfPlanets) == true || starDoc.GetCell<std::string>("gasGiantArrangement", currentCSVIndex) == "2")
			{
				planetDBIndex = i;
				firstGasGiantPresent = true;
				gasGiantArrangement = GGA_ECCENTRIC_GAS_GIANT;
				firstGasGiantOrbitalRadius = (worldDoc.GetCell<std::string>("pl_orbsmax", i) == "") ? placeFirstGasGiant(snowLineRadius, gasGiantArrangement, primary.innerLimitRadius) : worldDoc.GetCell<float>("pl_orbsmax", i);
				break;
			}
//			Check for conventional gas giant
			else if (csv_checkForConventionalGasGiant(snowLineRadius, worldDoc, firstWorldDocIndex, numberOfPlanets) || starDoc.GetCell<std::string>("gasGiantArrangement", currentCSVIndex) == "3")
			{
				planetDBIndex = i;
				firstGasGiantPresent = true;
				gasGiantArrangement = GGA_CONVENTIONAL_GAS_GIANT;
				firstGasGiantOrbitalRadius = (worldDoc.GetCell<std::string>("pl_orbsmax", i) == "") ? placeFirstGasGiant(snowLineRadius, gasGiantArrangement, primary.innerLimitRadius) : worldDoc.GetCell<float>("pl_orbsmax", i);
				break;
			}
//			Otherwise, there are no gas giants in the system
			else
			{
				firstGasGiantPresent = false;
				firstGasGiantOrbitalRadius = 0;
				gasGiantArrangement = GGA_NO_GAS_GIANT;
				break;
			}
		}
	}

	return std::make_tuple(planetDBIndex, firstGasGiantPresent, gasGiantArrangement, firstGasGiantOrbitalRadius, numberOfPlanets);
}
