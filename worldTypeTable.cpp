#include <string>

using namespace std;

string worldTypeTable(int result, string overallType)
{
	string worldType;
	
	if 		(result == 3  && overallType == "Hostile") {worldType = "Standard (Chthonian)"	;}
	else if (result == 4  && overallType == "Hostile") {worldType = "Standard (Chthonian)"	;}
	else if (result == 5  && overallType == "Hostile") {worldType = "Standard (Greenhouse)"	;}
	else if (result == 6  && overallType == "Hostile") {worldType = "Standard (Greenhouse)"	;}
	else if (result == 7  && overallType == "Hostile") {worldType = "Tiny (Sulfur)"			;}
	else if (result == 8  && overallType == "Hostile") {worldType = "Tiny (Sulfur)"			;}
	else if (result == 9  && overallType == "Hostile") {worldType = "Tiny (Sulfur)"			;}
	else if (result == 10 && overallType == "Hostile") {worldType = "Standard (Ammonia)"	;}
	else if (result == 11 && overallType == "Hostile") {worldType = "Standard (Ammonia)"	;}
	else if (result == 12 && overallType == "Hostile") {worldType = "Standard (Ammonia)"	;}
	else if (result == 13 && overallType == "Hostile") {worldType = "Large (Ammonia)"		;}
	else if (result == 14 && overallType == "Hostile") {worldType = "Large (Ammonia)"		;}
	else if (result == 15 && overallType == "Hostile") {worldType = "Large (Greenhouse)"	;}
	else if (result == 16 && overallType == "Hostile") {worldType = "Large (Greenhouse)"	;}
	else if (result == 17 && overallType == "Hostile") {worldType = "Large (Chthonian)"		;}
	else if (result == 18 && overallType == "Hostile") {worldType = "Large (Chthonian)"		;}
	
	else if (result == 3  && overallType == "Barren" ) {worldType = "Small (Hadean)"		;}
	else if (result == 4  && overallType == "Barren" ) {worldType = "Small (Ice)"			;}
	else if (result == 5  && overallType == "Barren" ) {worldType = "Small (Rock)"			;}
	else if (result == 6  && overallType == "Barren" ) {worldType = "Small (Rock)"			;}
	else if (result == 7  && overallType == "Barren" ) {worldType = "Tiny (Rock)"			;}
	else if (result == 8  && overallType == "Barren" ) {worldType = "Tiny (Rock)"			;}
	else if (result == 9  && overallType == "Barren" ) {worldType = "Tiny (Ice)"			;}
	else if (result == 10 && overallType == "Barren" ) {worldType = "Tiny (Ice)"			;}
	else if (result == 11 && overallType == "Barren" ) {worldType = "Asteroid Belt"			;}
	else if (result == 12 && overallType == "Barren" ) {worldType = "Asteroid Belt"			;}
	else if (result == 13 && overallType == "Barren" ) {worldType = "Standard (Ocean)"		;}
	else if (result == 14 && overallType == "Barren" ) {worldType = "Standard (Ocean)"		;}
	else if (result == 15 && overallType == "Barren" ) {worldType = "Standard (Ice)"		;}
	else if (result == 16 && overallType == "Barren" ) {worldType = "Standard (Hadean)"		;}
	else if (result == 17 && overallType == "Barren" ) {worldType = "Large (Ocean)"			;}
	else if (result == 18 && overallType == "Barren" ) {worldType = "Large (Ice)"			;}
	
	else if (result == 3  && overallType == "Garden" ) {worldType = "Standard (Garden)"		;}
	else if (result == 4  && overallType == "Garden" ) {worldType = "Standard (Garden)"		;}
	else if (result == 5  && overallType == "Garden" ) {worldType = "Standard (Garden)"		;}
	else if (result == 6  && overallType == "Garden" ) {worldType = "Standard (Garden)"		;}
	else if (result == 7  && overallType == "Garden" ) {worldType = "Standard (Garden)"		;}
	else if (result == 8  && overallType == "Garden" ) {worldType = "Standard (Garden)"		;}
	else if (result == 9  && overallType == "Garden" ) {worldType = "Standard (Garden)"		;}
	else if (result == 10 && overallType == "Garden" ) {worldType = "Standard (Garden)"		;}
	else if (result == 11 && overallType == "Garden" ) {worldType = "Standard (Garden)"		;}
	else if (result == 12 && overallType == "Garden" ) {worldType = "Standard (Garden)"		;}
	else if (result == 13 && overallType == "Garden" ) {worldType = "Standard (Garden)"		;}
	else if (result == 14 && overallType == "Garden" ) {worldType = "Standard (Garden)"		;}
	else if (result == 15 && overallType == "Garden" ) {worldType = "Standard (Garden)"		;}
	else if (result == 16 && overallType == "Garden" ) {worldType = "Standard (Garden)"		;}
	else if (result == 17 && overallType == "Garden" ) {worldType = "Large (Garden)"		;}
	else if (result == 18 && overallType == "Garden" ) {worldType = "Large (Garden)"		;}
	
	return worldType;
}