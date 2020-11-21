//	This file reads in data from hygdata_v3.csv for worldBuilder
//	C++ libraries
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

//	Constant declarations
#include "declarations/constants/unitConversions.h"

using namespace std;


void getStarData(int starID)
{
//	cout << "StarID:" << starID << endl;
//	Open the file
	fstream hygData;
	hygData.open("hygdata_v3_sorted_32_parsec.csv", ios::in);
//	cout << "Opened hygdata_v3.csv" << endl;
//	Read in data as a string vector
	vector<string> row;
	string line, word, temp;
//	cout << "Initialized vector and strings" << endl;

//	Earth is used as the origin for the coordinate system
//	This offsets it so that Sol is the origin
	const double EARTH_SOL_OFFSET = 0.000005;

	while (!hygData.eof())
	{
		row.clear();
//		cout << "Cleared row" << endl;
//		Read in row and store in line
		getline(hygData, line);
//		cout << (int)line << endl;
//		cout << (float)line << endl;
//		cout << (string)line << endl;
		if (line.length() == 0) {cout << "line is empty" << endl;}
//		cout << "Got line" << endl;
//		Break up words
		stringstream s(line);
//		cout << "Called stringstream" << endl;
//		Read every column and store in word
		while (getline(s, word, ','))
		{
//			Add row to a vector
			row.push_back(word);
//			cout << "Pushed back" << endl;
		}
//		cout << "Exited while loop" << endl;
//		Convert the first column to an integer for comparison and check if it
//		equals starID
//		cout << row << endl;
//		cout << typeid(stoi(row[0])).name() << endl;
/*		if (typeid(stoi(row[0])) == typeid(int))
		{
			cout << "row[0] == int" << endl;
		}

		else
		{
			cout << "row[0] != int" << endl;
		}
*/
//		cout << row[0].length() << endl;
//		cout << row[0] << endl;
//		int tempString = stoi(row[0]);
//		cout << stoi(row[0]) << endl;
//		cout << tempString << endl;
		try
		{
			if (stod(row[9]) * PARSEC_IN_LY <= 8)
			{
//				cout << "Entered if" << endl;
				cout << left << setw(48) << "Star ID: " << row[0] << endl;
				cout << left << setw(48) << "Proper name: " << row[6] << endl;
				cout << left << setw(48) << "Distance: " << row[9] << " parsecs | " << stod(row[9]) * PARSEC_IN_LY << " ly" << endl;
				cout << left << setw(48) << "Luminosity: " << row[33] << " solar luminosities" << endl;
//				Coordinates
				cout << left << setw(48) << "Coordinates: " << "(" << stod(row[17]) - EARTH_SOL_OFFSET << ", " << row[18] << ", " << row[19] << ")" << endl;
				cout << left << setw(48) << "Velocity components: " << "(" << row[20] << ", " << row[21] << ", " << row[22] << ") parsecs per year" << endl;
//				break;
			}
		}
		catch (const invalid_argument& ia)
		{
//			cerr << "Invalid argument: " << ia.what() << '\n';
		}

	}

}

/*
void getStarData(int starID)
{
//	Open the file
	ifstream file;
	string line;
	file.open("hygdata_v3.csv");
	while(!fin.eof())
	{
		if (line, line, )
	}
}
*/
