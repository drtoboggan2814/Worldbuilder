#ifndef EXPORTTOCSV
#define EXPORTTOCSV

#include <tuple>
#include "../third_party/rapidcsv.h"

//	Structs
#include "../structures/moon_t.h"
#include "../structures/tectonicPlate_t.h"
#include "../structures/world_t.h"
#include "../structures/star_t.h"
#include "../structures/starSystem_t.h"


std::string uniqueIDCreator(char idType, int uniqueID);

void exportJumpPointToCSV(const star_t& primary, int i, std::string parentID, const jumpPoint_t& jumpPoint, int jumpPointIndex);
/*
void exportMoonletToCSV(int i, int worldID, const moonlet_t& moonlet, rapidcsv::Document moonletExport, int moonletIndex);
*/
int exportMoonToCSV(int i, int worldID, const moon_t& moon, int moonIndex);

std::tuple <int, int> exportPlanetToCSV(int i, int starID, const world_t& world, int worldIndex, int moonIndex);

std::tuple <int, int, int> exportStarToCSV(int starIndex, int starSystemID, const star_t& star, int worldIndex, int moonIndex, int jumpPointIndex);

std::tuple <int, int, int, int> exportStarSystemToCSV(const starSystem_t& starSystem, int starSystemIndex, int starIndex, int worldIndex, int moonIndex, int jumpPointIndex);

void starSystemCSVHeader();
void starCSVHeader();
void worldCSVHeader();
void moonCSVHeader();
void jumpPointCSVHeader();


#endif
