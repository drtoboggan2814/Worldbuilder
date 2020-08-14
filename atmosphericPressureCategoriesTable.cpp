#include <string>

using namespace std;

string atmosphericPressureCategoriesTable(float atmosphericPressure)
{
	string pressureCategory;
	if 		(atmosphericPressure == 0								  ) {pressureCategory = "None"		;}
	else if	(atmosphericPressure < 	0.01 && atmosphericPressure > 0	  ) {pressureCategory = "Trace"		;}
	else if (atmosphericPressure >= 0.01 && atmosphericPressure <= 0.5) {pressureCategory = "Very Thin"	;}
	else if (atmosphericPressure >= 0.51 && atmosphericPressure <= 0.8) {pressureCategory = "Thin"		;}
	else if (atmosphericPressure >= 0.81 && atmosphericPressure <= 1.2) {pressureCategory = "Standard"	;}
	else if (atmosphericPressure >= 1.21 && atmosphericPressure <= 1.5) {pressureCategory = "Dense"		;}
	else if (atmosphericPressure >= 1.51 && atmosphericPressure <= 10 )	{pressureCategory = "Very Dense";}
	else if (atmosphericPressure >	10								  ) {pressureCategory = "Superdense";}

	return pressureCategory;
}
