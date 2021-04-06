#ifndef UNIVERSALCONSTANTS
#define UNIVERSALCONSTANTS

#include <math.h>

//	Universal constants
//	Also includes .csv lengths

const int WORLDDOC_LENGTH = 310;
const int STARDOC_LENGTH = 4289;

//	Universal gravitational constant G (m^3 kg^-1 s^-2)
const double UNIVERSAL_GRAVITATIONAL_CONSTANT = 6.67428 * pow(10, -11);
//	Source: http://asa.hmnao.com/static/files/2018/Astronomical_Constants_2018.pdf

//	Speed of light in a vacuum (m/s)
const double SPEED_OF_LIGHT = 299792458;
//	Source: http://asa.hmnao.com/static/files/2018/Astronomical_Constants_2018.pdf

//	Stefan-Boltzmann constant
//	In terms of W / (m^2 * K^-4)
const double STEFAN_BOLTZMANN_CONSTANT = 5.670374419 * pow(10, -8);
//	Source: https://physics.nist.gov/cgi-bin/cuu/Value?sigma

#endif
