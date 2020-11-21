//	C++ libraries
#include <iostream>
#include <string>

//	Third party libraries
#include "declarations/third_party/rapidcsv.h"

//	Function declarations
#include "declarations/functions/starClassifier.h"

int main()
{
	const int OUT_BLANKS_FILLED_LENGTH = 4797;
//	Read in out_blanks_filled.csv
	rapidcsv::Document doc("out_blanks_filled.csv", rapidcsv::LabelParams(0, 0));

//	Read each row
	for (int i = 0; i < OUT_BLANKS_FILLED_LENGTH; i++)
	{
//		Get data from cells
		std::string starType = doc.GetCell<std::string>("spect", i);
		double originalLuminosity = doc.GetCell<double>("lum", i);
		bool massPreset 	= (doc.GetCell<std::string>("mass", i) == "~") ? false : true;
		bool radiusPreset 	= (doc.GetCell<std::string>("radius", i) == "~") ? false : true;
		bool tempPreset 	= (doc.GetCell<std::string>("temperature", i) == "~") ? false : true;
		int componentNumber = doc.GetCell<int>("comp", i);

//		If spect is empty

		std::cout << doc.GetCell<std::string>("proper", i) << std::endl;
	}



	return 0;
}
