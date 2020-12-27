#IFNDEF VOIDSTRIKERSHIP_T
#DEFINE VOIDSTRIKERSHIP_T

//	C++ libraries
#include <string>

//	This structure is used to create a ship using rules from Voidstriker
struct voidstrikerShip_t
{
	std::string shipName;
	int8_t numAction;
	int8_t thrustRatioNumerator;
	int8_t thrustRatioDenominator;
	int8_t thrusterType;
	int8_t targetSize;
	int16_t constructionValue;
	std::string className;
	int8_t troops;
	int8_t hangarCraftNum;
	int8_t jumpSpeed;
	int8_t jumpActions;
	std::string raceName;
	int16_t cargo;
	int8_t burnNum;
	int8_t shieldType;
	int8_t shieldNum;
	int8_t ewNum;

//	Armor table
	int8_t armorTable[10][20];
//	Structure table
	char structureTable[5][20];
//	Frame table
	int8_t frameTable[2][20];

//	Weapons
//	First column is weapon type and second is quantity
	int8_t weaponTable[16][2];
//	Facing column for weapon table
	int8_t facingTable[16];
}
