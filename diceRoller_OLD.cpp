//	This function rolls a given number of dice with a number of given number of sides
//	The total of the dice is then returned
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



int diceRoller_OLD(int dieNum, int dieCount)
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
	int result = 0;
	int resultArray[dieCount];
	for (int i = 0; i < dieCount; i++)
	{
//		cout << "diceroll = " << result << endl;

		resultArray[i] = diceRoll(generator);
		if (i == dieCount - 1) {break;}
	}

	for (int i = 0; i < dieCount; i++)
	{
		result += resultArray[i];
	}
	return result;
}
