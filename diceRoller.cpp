//	This function rolls a die with a given number of sides

/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
*/
//	This uses  the Mersenne Twister as opposed to rand()
//#include "declarations/functions/rngSeed.h"
//#include <functional>
//extern MyRNG rng;
#include <random>
#include <iostream>
#include <chrono>
using namespace std;

int diceRNG(int dieNum)
{/*
	int diceArray[dieCount];
	int i;

	for (i = 0; i < dieCount; i++)
	{
		diceArray[i] = 0;
	}

	int sum = 0;

	for (i = 0; i < dieCount; i++)
	{
		diceArray[i] = 1 + (int) (dieNum * (rand() / (RAND_MAX + 1.0)));
		sum = sum + diceArray[i];
	}
*/
/*
	random_device rd;
	mt19937 gen(rd());
//	Create distribution from 1 to the number of sides the die has
	uniform_int_distribution<int> diceRoll(1, dieNum);
	int result = diceRoll(rd) * dieCount;
*/
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator (seed);
	uniform_int_distribution<int> diceRoll(1, dieNum);
	int result = diceRoll(generator);
//	cout << "diceRNG = " << result << endl;
	return result;
}

int diceRoller(int dieNum, int dieCount)
{
	if (dieNum == 0 || dieCount == 0) {return 0;}
	else
	{
		int result = 0;
		for (int i = 0; i < dieCount; i++)
		{
			result += diceRNG(dieNum);
			if (i == dieCount - 1) {break;}
		}
		return result;
	}
}
