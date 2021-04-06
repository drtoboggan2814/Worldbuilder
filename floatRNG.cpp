//#include "declarations/functions/rngSeed.h"
#include <random>
#include <chrono>
#include <iostream>

using namespace std;
/*
float floatRNG(float lower, float upper)
{
//	Create distribution from lower to upper
/*
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<float> rngGen(lower, upper);
	float result = rngGen(rd);

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator (seed);
	uniform_real_distribution<float> result(lower, upper);
//	cout << "floatRNG = " << result(generator) << endl;
	return result(generator);
}
*/

std::default_random_engine & global_urng()
{
	static std::default_random_engine u{};
	return u;
}

void randomize()
{
	static std::random_device rd{};
	global_urng().seed(rd());
}

float floatRNG(float lower, float upper)
{
	static std::uniform_real_distribution<> d{};
	using parm_t = decltype(d)::param_type;
	return d(global_urng(), parm_t{lower, upper});
}
