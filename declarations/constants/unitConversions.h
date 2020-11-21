//	Unit conversions
#include <math.h>

//	Convert the mass of the Earth into kg
const double EARTH_MASS_IN_KG = 5.97237 * pow(10, 24);
//	Source: https://ssd.jpl.nasa.gov/?planet_phys_par

//	Convert the equatorial radius of the Earth into km
const double EARTH_RADIUS_IN_KM = 6378.1366;
//	Source: http://asa.hmnao.com/static/files/2018/Astronomical_Constants_2018.pdf

//	Convert the mass of Sol into kg
const double SOL_MASS_IN_KG = 1988500 * pow(10, 24);
//	Source: https://nssdc.gsfc.nasa.gov/planetary/factsheet/sunfact.html

//	Convert the equatorial radius of Sol into km
const double SOL_RADIUS_IN_KM = 696000;
//	Source: http://asa.hmnao.com/static/files/2018/Astronomical_Constants_2018.pdf

//	Value of an au in m
const double AU_IN_M = 149597870700;
//	Source: http://asa.hmnao.com/static/files/2018/Astronomical_Constants_2018.pdf

//	Value of a radian in arcseconds
const double RAD_IN_ASEC = 3600 * (180 / M_PI);
//	Source: https://en.wikipedia.org/wiki/Angular_diameter

//	Length of a parsec
const double PARSEC_IN_LY = 3.2615638;
//	Source: Allen's Astrophyscial Quantities, 4E

//	Length of a light year
const double LY_IN_M = 9.460730472 * pow(10, 15);
//	Source: Allen's Astrophyscial Quantities, 4E

//	Energy conversions
const double J_TO_ERG = pow(10, 7);
const double ERG_TO_J = 1 / pow(10, 7);

//	Basic metric conversions
const float KG_TO_G = 1000;
const float G_TO_KG = 0.001;
const float M_TO_KM = 0.001;
const float KM_TO_M = 1000;

//	Basic time conversions
const float HOUR_TO_DAY = 1 / 24;
const float DAY_TO_HOUR = 24;
const float HOUR_TO_SEC = 3600;
