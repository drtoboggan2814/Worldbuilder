#ifndef MAPPINGCONSTANTS
#define MAPPINGCONSTANTS

//	This takes the world size and returns the triangle side
//	Source: 2300 AD Core Rules
const char WORLDSIZE_TRIANGLESIZE_LOOKUP_TABLE[30] = {1, 1, 2, 3, 3, 4, 4, 5, 6, 6, 7, 8, 8, 9, 9, 10, 11, 11, 12, 13, 13, 14, 14, 15, 16, 16, 17, 18, 18, 19};

//	The number of whole hexagons in each triangle
//	n = x - 2
//	# of hexes = (n * (n + 1)) / 2
const int INTERIOR_HEXAGON_COUNT[19] = {0, 0, 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 66, 78, 91, 105, 120, 136, 153};

//	The number of incomplete hexagons along the sides of each triangle
const float EDGE_HEXAGON_COUNT[19] = {0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9, 9.5};

//	The total number of hexagons in the map depending on the hexes per triangle side
const int WORLD_MAP_TOTAL_HEXES[19] = {10, 20, 50, 100, 170, 260, 370, 500, 650, 820, 1010, 1220, 1450, 1700, 1970, 2260, 2570, 2900, 3250};

//	Multiplier for the total number of hexes
//	Traveller: The New Era - World Tamers Handbook has a total of 500 hexes fixed for each world
//	Each of these is one tenth of the total
const char TOTAL_WATER_HEX_MULTIPLIER[19] = {1, 1, 1, 1, 2, 3, 4, 5, 7, 8, 10, 12, 15, 17, 20, 23, 26, 29, 33};

//	Major ocean column addition coefficient
const int MAJOR_OCEAN_ADDITION_COEFFICIENT[21] = {0, 0, 0, 0, 0, 0, 4, 3, 2, 2, 1, 1, 1, 0, 0, 0, 1, 1, 1};
//	Minor ocean column multiplier coefficient
const int MINOR_OCEAN_MULTIPLIER_COEFFICIENT[21] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 1, 2, 3, 2, 3, 1, 1, 2, 3};
//	Minor ocean column addition coefficient
const int MINOR_OCEAN_ADDITION_COEFFICIENT[21] = {0, 0, 0, 0, 0, 0, 3, 2, 1, 1, 2, 1, 2, 3, 2, 3, 1, 2, 3};

//	Major continent addition coefficient
const int MAJOR_CONTINENT_ADDITION_COEFFICIENT[21] = {1, 1, 1, 0, 0, 0, 0, 0, 0, -1, -1, -1, -2, -3, -4, 0, 0, 0, 0, 0, 0};
//	Major continent multiplier coefficient
const int MAJOR_CONTINENT_MULTIPLIER_COEFFICIENT[21] = {2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
//	Minor continent addition coefficient
const int MINOR_CONTINENT_ADDITION_COEFFICIENT[21] = {-1, -2, 3, -1, -2, -3, -1, -2 , -3, 0, 0, 0, -1, -2, -3, 0, 0, 0, 0, 0, 0};
//	Minor continent multiplier coefficient
const int MINOR_CONTINENT_MULTIPLIER_COEFFICIENT[21] = {1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 1, 1, 0, 0, 0, 0, 0, 0};

//	Tectonic plate movement types
const char TPMT_CONVERGING = 0;
const char TPMT_TRAVERSING = 1;
const char TPMT_DIVERGING = 2;


#endif
