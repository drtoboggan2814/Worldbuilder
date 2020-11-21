#include <string>

#include "declarations/structures/marginalAtmosphere_t.h"

using namespace std;

marginalAtmosphere_t marginalAtmosphereTable(int marginalAtmosphereRNG)
{
//	Initialize the marginal atmopshere array
	marginalAtmosphere_t marginalAtmosphere;

	int i = 0;
	if (marginalAtmosphereRNG == 3 || marginalAtmosphereRNG == 4)
	{
		marginalAtmosphere.marginalAtmosphereArray[0] = 1;
		for (i = 1; i < 9; i++) {marginalAtmosphere.marginalAtmosphereArray[i] = 0;}
	}

	else if (marginalAtmosphereRNG == 5 || marginalAtmosphereRNG == 6)
	{
		marginalAtmosphere.marginalAtmosphereArray[0] = 0;
		marginalAtmosphere.marginalAtmosphereArray[1] = 1;
		for (i = 2; i < 9; i ++) {marginalAtmosphere.marginalAtmosphereArray[i] = 0;}
	}

	else if (marginalAtmosphereRNG == 7)
	{
		for (i = 0; i < 2; i ++) {marginalAtmosphere.marginalAtmosphereArray[i] = 0;}
		marginalAtmosphere.marginalAtmosphereArray[2] = 1;
		for (i = 3; i < 9; i ++) {marginalAtmosphere.marginalAtmosphereArray[i] = 0;}
	}

	else if (marginalAtmosphereRNG == 8 || marginalAtmosphereRNG == 9)
	{
		for (i = 0; i < 3; i ++) {marginalAtmosphere.marginalAtmosphereArray[i] = 0;}
		marginalAtmosphere.marginalAtmosphereArray[3] = 1;
		for (i = 4; i < 9; i ++) {marginalAtmosphere.marginalAtmosphereArray[i] = 0;}
	}

	else if (marginalAtmosphereRNG == 10 || marginalAtmosphereRNG == 11)
	{
		for (i = 0; i < 4; i ++) {marginalAtmosphere.marginalAtmosphereArray[i] = 0;}
		marginalAtmosphere.marginalAtmosphereArray[4] = 1;
		for (i = 5; i < 9; i ++) {marginalAtmosphere.marginalAtmosphereArray[i] = 0;}
	}

	else if (marginalAtmosphereRNG == 12 || marginalAtmosphereRNG == 13)
	{
		for (i = 0; i < 5; i ++) {marginalAtmosphere.marginalAtmosphereArray[i] = 0;}
		marginalAtmosphere.marginalAtmosphereArray[5] = 1;
		for (i = 6; i < 9; i ++) {marginalAtmosphere.marginalAtmosphereArray[i] = 0;}
	}

	else if (marginalAtmosphereRNG == 14)
	{
		for (i = 0; i < 6; i ++) {marginalAtmosphere.marginalAtmosphereArray[i] = 0;}
		marginalAtmosphere.marginalAtmosphereArray[6] = 1;
		for (i = 7; i < 9; i ++) {marginalAtmosphere.marginalAtmosphereArray[i] = 0;}
	}

	else if (marginalAtmosphereRNG == 15 || marginalAtmosphereRNG == 16)
	{
		for (i = 0; i < 7; i ++) {marginalAtmosphere.marginalAtmosphereArray[i] = 0;}
		marginalAtmosphere.marginalAtmosphereArray[7] = 1;
		for (i = 8; i < 9; i ++) {marginalAtmosphere.marginalAtmosphereArray[i] = 0;}
	}

	else
	{
		for (i = 0; i < 9; i ++) {marginalAtmosphere.marginalAtmosphereArray[i] = 0;}
		marginalAtmosphere.marginalAtmosphereArray[9] = 1;
	}

	return marginalAtmosphere;
}
