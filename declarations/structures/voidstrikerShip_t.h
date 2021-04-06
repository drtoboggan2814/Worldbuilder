#IFNDEF VOIDSTRIKERSHIP_T
#DEFINE VOIDSTRIKERSHIP_T

//	C++ libraries
#include <string>

//	This structure is used to create a ship using rules from Voidstriker
struct voidstrikerShip_t
{
	std::string shipName;
	int numAction;
	int thrustRatioNumerator;
	int thrustRatioDenominator;
	int thrusterType;
	int targetSize;
	int16_t constructionValue;
	std::string className;
	int troops;
	int hangarCraftNum;
	int jumpSpeed;
	int jumpActions;
	std::string raceName;
	int16_t cargo;
	int burnNum;
	int shieldType;
	int shieldNum;
	int ewNum;

//	Armor table
	int armorTable[10][20];
//	Structure table
	char structureTable[5][20];
//	Frame table
	int frameTable[2][20];

//	Weapons
//	First column is weapon type and second is quantity
	int weaponTable[16][2];
//	Facing column for weapon table
	int facingTable[16];
}
