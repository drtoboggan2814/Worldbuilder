#ifndef MOONLET_T
#define MOONLET_T

#include <string>

using namespace std;

struct moonlet_t
{
	float orbitalRadius;
	int uniqueMoonletID;
	int parentWorldID;
	int primaryStarID;
	int starSystemID;
};

#endif
