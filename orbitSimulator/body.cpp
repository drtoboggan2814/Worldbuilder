#include "../declarations/classes/body.h"
#include <string>

class Body
{
	private:
		std::string name;
		double xVec, yVec, mass;

	public:
//		Constructor
		Body (std::string, double, double, double);
//		Setters
		void set_name(std::string nameInput) {name = nameInput;}

		void set_xVec (double xVecInput) {xVec = xVecInput;}

		void set_yVec (double yVecInput) {yVec = yVecInput;}

		void set_mass (double massInput) {mass = massInput;}

//		Getters
		std::string get_name ()	{return name;}

		double get_xVec () {return xVec;}

		double get_yVec () {return yVec;}

		double get_mass () {return mass;}
}
