#include <random>
#include <chrono>

using namespace std;
//	Initialize random seed
//	auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
random_device seed;
mt19937 gen(seed());
