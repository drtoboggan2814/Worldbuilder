//	This function returns the stellar characteristics outlined in the stellar
//	evolution table

#include <iostream>

using namespace std;
//	Constant declarations
#include "declarations/constants/stellarEvolutionTableConstants.h"

//	Structure declarations
#include "declarations/structures/world_t.h"
#include "declarations/structures/star_t.h"

star_t determineStellarCharacteristics(star_t star)
{
//	Iterate through stellarEvolutionTableConstants for the star's type
	for (int i = 0; i < 34; i++)
	{
/*		cout << "Spectral type integer = " << i << endl;
//		Calculate the differences between the entry and its neighboring values
		float lesserDifference;
		float greaterDifference;
		if (i == 0)
		{
			cout << "i == 0" << endl;
			lesserDifference = 0;
			greaterDifference = stellarEvolutionTable[1][0];
		}

		else if (i >= 1 && i < 33)
		{
			cout << "i is between 1 and 33" << endl;
			lesserDifference = (stellarEvolutionTable[i][0] - stellarEvolutionTable[i - 1][0]) / 2;
			greaterDifference = (stellarEvolutionTable[i + 1][0] - stellarEvolutionTable[i][0]) / 2;
		}

		else
		{
			cout << " i == 33" << endl;
			lesserDifference = (stellarEvolutionTable[i][0] - stellarEvolutionTable[i - 1][0]) / 2;
			greaterDifference = stellarEvolutionTable[i][0];
		}

		cout << "lesserDifference = " << lesserDifference << endl;

		cout << "greaterDifference = " << greaterDifference << endl;
*/
//		Calculate the interpolation ratio
		float interpolationRatio = star.stellarMass / stellarEvolutionTable[i][0];
//		cout << "interpolationRatio" << interpolationRatio << endl;
//		If the star's mass is greater than or equal to half the difference between the i entry and the i - 1 entry
//		and if the star's mass is less than half the difference between the i + 1 entry and the i entry

//		If the mass is less than 0.1
		if (star.stellarMass < 0.1)
		{
//			cout << "WORKING" << endl;
//			cout << "i = " << i << endl;
//			cout << "interpolationRatio = " << interpolationRatio << endl;

//			Assign the star type
			star.starType = stellarEvolutionTable[i][1];

//			Modify table entries with the interpolation ratio
			star.tableTemperature = stellarEvolutionTable[i][2] * interpolationRatio;
//			cout << "star.tableTemperature = " << star.tableTemperature << endl;
			star.lMin = stellarEvolutionTable[i][3] * interpolationRatio;
//			cout << "star.lMin = " << star.lMin << endl;
			star.lMax = stellarEvolutionTable[i][4] * interpolationRatio;
//			cout << "star.lMax = " << star.lMax << endl;
			star.mSpan = stellarEvolutionTable[i][5] * interpolationRatio;
//			cout << "star.mSpan = " << star.mSpan << endl;
			star.sSpan = stellarEvolutionTable[i][6] * interpolationRatio;
//			cout << "star.sSpan = " << star.sSpan << endl;
			star.gSpan = stellarEvolutionTable[i][7] * interpolationRatio;
//			cout << "star.gSpan = " << star.gSpan << endl;

//				Determine luminosity class and make any necessary changes
			if 		(star.stellarAge <= star.mSpan) 																			{star.luminosityClass = "V";}
			else if (star.stellarAge > star.mSpan && star.stellarAge <= (star.sSpan + star.mSpan)) 								{star.luminosityClass = "IV";}
			else if (star.stellarAge > (star.sSpan + star.mSpan) && star.stellarAge <= (star.mSpan + star.sSpan + star.gSpan)) 	{star.luminosityClass = "III";}
			else																			 									{star.luminosityClass = "D";}


//			Break
			break;
		}

		else if (i == 33)
		{
			if (star.stellarMass >= stellarEvolutionTable[i][0])
			{
//				cout << "WORKING" << endl;
//				cout << "i = " << i << endl;
//				cout << "interpolationRatio = " << interpolationRatio << endl;

	//			Assign the star type
				star.starType = stellarEvolutionTable[i][1];

	//			Modify table entries with the interpolation ratio
				star.tableTemperature = stellarEvolutionTable[i][2] * interpolationRatio;
//				cout << "star.tableTemperature = " << star.tableTemperature << endl;
				star.lMin = stellarEvolutionTable[i][3] * interpolationRatio;
//				cout << "star.lMin = " << star.lMin << endl;
				star.lMax = stellarEvolutionTable[i][4] * interpolationRatio;
//				cout << "star.lMax = " << star.lMax << endl;
				star.mSpan = stellarEvolutionTable[i][5] * interpolationRatio;
//				cout << "star.mSpan = " << star.mSpan << endl;
				star.sSpan = stellarEvolutionTable[i][6] * interpolationRatio;
//				cout << "star.sSpan = " << star.sSpan << endl;
				star.gSpan = stellarEvolutionTable[i][7] * interpolationRatio;
//				cout << "star.gSpan = " << star.gSpan << endl;

//				Determine luminosity class and make any necessary changes
				if 		(star.stellarAge <= star.mSpan) 																			{star.luminosityClass = "V";}
				else if (star.stellarAge > star.mSpan && star.stellarAge <= (star.sSpan + star.mSpan)) 								{star.luminosityClass = "IV";}
				else if (star.stellarAge > (star.sSpan + star.mSpan) && star.stellarAge <= (star.mSpan + star.sSpan + star.gSpan)) 	{star.luminosityClass = "III";}
				else																			 									{star.luminosityClass = "D";}


	//			Break
				break;
			}
		}

		else if (star.stellarMass >= stellarEvolutionTable[i][0] && (star.stellarMass < stellarEvolutionTable[i + 1][0]))
		{
//			cout << "i = " << i << endl;
//			cout << "interpolationRatio = " << interpolationRatio << endl;
//			Assign the star type
			star.starType = stellarEvolutionTable[i][1];

//			Modify table entries with the interpolation ratio
			star.tableTemperature = stellarEvolutionTable[i][2] * interpolationRatio;
//			cout << "star.tableTemperature = " << star.tableTemperature << endl;
			star.lMin = stellarEvolutionTable[i][3] * interpolationRatio;
//			cout << "star.lMin = " << star.lMin << endl;
			star.lMax = stellarEvolutionTable[i][4] * interpolationRatio;
//			cout << "star.lMax = " << star.lMax << endl;
			star.mSpan = stellarEvolutionTable[i][5] * interpolationRatio;
//			cout << "star.mSpan = " << star.mSpan << endl;
			star.sSpan = stellarEvolutionTable[i][6] * interpolationRatio;
//			cout << "star.sSpan = " << star.sSpan << endl;
			star.gSpan = stellarEvolutionTable[i][7] * interpolationRatio;
//			cout << "star.gSpan = " << star.gSpan << endl;

//				Determine luminosity class
			if 		(star.stellarAge <= star.mSpan) 																			{star.luminosityClass = "V";}
			else if (star.stellarAge > star.mSpan && star.stellarAge <= (star.sSpan + star.mSpan)) 								{star.luminosityClass = "IV";}
			else if (star.stellarAge > (star.sSpan + star.mSpan) && star.stellarAge <= (star.mSpan + star.sSpan + star.gSpan)) 	{star.luminosityClass = "III";}
			else																			 									{star.luminosityClass = "D";}

//			Break
			break;
		}
	}

	return star;
}
