#include <cstdlib>
int intRNG(int lower, int upper)
{
	int result;
	result = lower + (int) (rand()) / ((int (RAND_MAX/(upper - lower))));
	return result;
}