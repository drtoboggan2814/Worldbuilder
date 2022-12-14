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
		void set_name(std::string nameInput);

		void set_xVec (double xVecInput);

		void set_yVec (double yVecInput);

		void set_mass (double massInput);

//		Getters
		std::string get_name ();

		double get_xVec ();

		double get_yVec ();

		double get_mass ();

}
