//	This file defines constants representing components of a Voidstriker ship

//	Hardpoints
const int HP_LIGHT = 0;
const int HP_MEDIUM = 1;
const int HP_HEAVY = 2;
const int HP_MAIN = 3;

//	Weapons
//	Slugthrowers
const int ST_CHAINGUNS[4][3] =
{
//	Hardpoint,	cost,	additional hardpoint cost
	HP_LIGHT, 	7,		0,
	HP_MEDIUM,	11,		0,
	HP_HEAVY,	21,		0,
	HP_LIGHT,	5,		0
};

const int ST_RAILGUNS[3, 3] =
{
//	Hardpoint,	cost,	additional hardpoint cost
	HP_LIGHT,	13,		0,
	HP_HEAVY,	26,		0,
	HP_MAIN,	39,		10
};

const int ST_COILGUNS[3, 3] =
{
//	Hardpoint,	cost,	additional hardpoint cost
	HP_LIGHT,	16,		0,
	HP_HEAVY,	38,		0,
	HP_MAIN,	96,		24
};

//	Lasers
const int L_LASERS[3, 3] =
{
//	Hardpoint,	cost,	additional hardpoint cost
	HP_LIGHT,	4,		0,
	HP_MEDIUM,	8,		0,
	HP_HEAVY,	16,		0
};

const int L_TURBOLASERS[3, 3] =
{
//	Hardpoint,	cost,	additional hardpoint cost
	HP_LIGHT,	8,		0,
	HP_MEDIUM,	19,		0,
	HP_HEAVY,	41,		0
};

const int L_PULSELASERS[4, 3] =
{
//	Hardpoint,	cost,	additional hardpoint cost
	HP_MEDIUM,	27,		0,
	HP_HEAVY,	58,		0,
	HP_MAIN,	91,		23,
	HP_LIGHT,	6,		0
};

const int L_BEAMLASERS[6, 3] =
{
//	Hardpoint,	cost,	additional hardpoint cost
	HP_MEDIUM,	32,		0,
	HP_MEDIUM,	53,		0,
	HP_HEAVY,	70,		0,
	HP_HEAVY,	118,	0,
	HP_MAIN,	149,	38,
	HP_LIGHT,	10,		0
};

//	Energy weapons
const int EW_PARTICLEBEAMS[4, 3] =
{
//	Hardpoint,	cost,	additional hardpoint cost
	HP_MEDIUM,	22,		0,
	HP_HEAVY,	61,		0,
	HP_MAIN,	97,		25,
	HP_LIGHT,	9,		0
};

const int EW_PLASMAGUNS[4, 3] =
{
//	Hardpoint,	cost,	additional hardpoint cost
	HP_LIGHT,	10,		0,
	HP_MEDIUM,	20,		0,
	HP_MEDIUM,	23,		0,
	HP_HEAVY,	49,		0
};

const int EW_FUSIONCANNON[3, 3] =
{
//	Hardpoint,	cost,	additional hardpoint cost
	HP_MEDIUM,	33,		0,
	HP_HEAVY,	52,		0,
	HP_MAIN,	118,	30
};

//	Ordnance
const int O_SWARMERS[12, 3] =
{
//	Hardpoint,	cost,	additional hardpoint cost
	HP_LIGHT,	3,		0,
	HP_MEDIUM,	8,		0,
	HP_HEAVY,	31,		0,
	HP_LIGHT,	5,		0,
	HP_MEDIUM,	15,		0,
	HP_HEAVY,	57,		0,
	HP_LIGHT,	8,		0,
	HP_MEDIUM,	25,		0,
	HP_HEAVY,	99,		0,
	HP_LIGHT,	15,		0,
	HP_MEDIUM,	48,		0,
	HP_HEAVY,	190,	0
}

const int O_ROCKETS[4, 3] =
{
//	Hardpoint,	cost,	additional hardpoint cost
	HP_LIGHT,	4,		0,
	HP_MEDIUM,	16,		0,
	HP_LIGHT,	5,		0,
	HP_MEDIUM,	18,		0
};

const int O_MISSILES[12, 3] =
{
//	Hardpoint,	cost,	additional hardpoint cost
	HP_LIGHT,	6,		0,
	HP_MEDIUM,	15,		0,
	HP_HEAVY,	40,		0
};

const int O_TORPEDOES[12, 3] =
{
//	Hardpoint,	cost,	additional hardpoint cost
	HP_LIGHT,	23,		0,
	HP_MEDIUM,	57,		0,
	HP_HEAVY,	130,	0,
	HP_LIGHT,	38,		0,
	HP_MEDIUM,	94,		0,
	HP_HEAVY,	215,	0,
	HP_LIGHT,	65,		0,
	HP_MEDIUM,	163,	0,
	HP_HEAVY,	373,	0,
	HP_HEAVY,	24,		0
};

const int O_BOMBS[5, 3] =
{
//	Hardpoint,	cost,	additional hardpoint cost
	HP_HEAVY,	12,		0,
	HP_LIGHT,	9,		0,
	HP_LIGHT,	11,		0,
	HP_LIGHT,	32,		0,
	HP_LIGHT,	33,		0
};

//	Exotic weapons
const int X_FUSIONTORPEDOES[3, 3] =
{
//	Hardpoint,	cost,	additional hardpoint cost
	HP_MEDIUM,	22,		0,
	HP_HEAVY,	53,		0,
	HP_MAIN,	112,	28
};

const int X_VORTEXMINE[1, 3] =
{
//	Hardpoint,	cost,	additional hardpoint cost
		HP_LIGHT,	42,		0
};

const int X_FUSIONTORPEDOES[3, 3] =
{
//	Hardpoint,	cost,	additional hardpoint cost
	HP_MAIN,	27,		0,
	HP_MAIN,	38,		0,
	HP_MAIN,	71,		0
};

//	Thruster table
const int THRUSTER_TABLE[18, 2] =
{
//	Cost,	hardpoint cost
	2,		0,
	3,		10,
	5,		20,
	7,		10,
	9,		20,
	12,		30,
	4,		5,
	6,		15,
	10,		25,
	11,		18,
	14,		28,
	20,		38,
	7,		10,
	11,		20,
	19,		30,
	17,		25,
	23,		35,
	35,		45
}
