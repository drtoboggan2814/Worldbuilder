//	C++ libraries
#include <string>

//	Constant declarations
#include "declarations/constants/worldTypeConstants.h"

using namespace std;

char worldTypeTable(int result, char overallType)
{
	char worldType;

	if 		(result == 3  && overallType == OT_HOSTILE) {worldType = WT_STANDARD_CHTHONIAN	;}
	else if (result == 4  && overallType == OT_HOSTILE) {worldType = WT_STANDARD_CHTHONIAN	;}
	else if (result == 5  && overallType == OT_HOSTILE) {worldType = WT_STANDARD_GREENHOUSE	;}
	else if (result == 6  && overallType == OT_HOSTILE) {worldType = WT_STANDARD_GREENHOUSE	;}
	else if (result == 7  && overallType == OT_HOSTILE) {worldType = WT_TINY_SULFUR			;}
	else if (result == 8  && overallType == OT_HOSTILE) {worldType = WT_TINY_SULFUR			;}
	else if (result == 9  && overallType == OT_HOSTILE) {worldType = WT_TINY_SULFUR			;}
	else if (result == 10 && overallType == OT_HOSTILE) {worldType = WT_STANDARD_AMMONIA	;}
	else if (result == 11 && overallType == OT_HOSTILE) {worldType = WT_STANDARD_AMMONIA	;}
	else if (result == 12 && overallType == OT_HOSTILE) {worldType = WT_STANDARD_AMMONIA	;}
	else if (result == 13 && overallType == OT_HOSTILE) {worldType = WT_LARGE_AMMONIA		;}
	else if (result == 14 && overallType == OT_HOSTILE) {worldType = WT_LARGE_AMMONIA		;}
	else if (result == 15 && overallType == OT_HOSTILE) {worldType = WT_LARGE_GREENHOUSE	;}
	else if (result == 16 && overallType == OT_HOSTILE) {worldType = WT_LARGE_GREENHOUSE	;}
	else if (result == 17 && overallType == OT_HOSTILE) {worldType = WT_LARGE_CHTHONIAN		;}
	else if (result == 18 && overallType == OT_HOSTILE) {worldType = WT_LARGE_CHTHONIAN		;}

	else if (result == 3  && overallType == OT_BARREN ) {worldType = WT_SMALL_HADEAN		;}
	else if (result == 4  && overallType == OT_BARREN ) {worldType = WT_SMALL_ICE			;}
	else if (result == 5  && overallType == OT_BARREN ) {worldType = WT_SMALL_ROCK			;}
	else if (result == 6  && overallType == OT_BARREN ) {worldType = WT_SMALL_ROCK			;}
	else if (result == 7  && overallType == OT_BARREN ) {worldType = WT_TINY_SULFUR			;}
	else if (result == 8  && overallType == OT_BARREN ) {worldType = WT_TINY_SULFUR			;}
	else if (result == 9  && overallType == OT_BARREN ) {worldType = WT_TINY_ICE			;}
	else if (result == 10 && overallType == OT_BARREN ) {worldType = WT_TINY_ICE			;}
	else if (result == 11 && overallType == OT_BARREN ) {worldType = WT_ASTEROID_BELT			;}
	else if (result == 12 && overallType == OT_BARREN ) {worldType = WT_ASTEROID_BELT			;}
	else if (result == 13 && overallType == OT_BARREN ) {worldType = WT_STANDARD_OCEAN		;}
	else if (result == 14 && overallType == OT_BARREN ) {worldType = WT_STANDARD_OCEAN		;}
	else if (result == 15 && overallType == OT_BARREN ) {worldType = WT_STANDARD_ICE		;}
	else if (result == 16 && overallType == OT_BARREN ) {worldType = WT_STANDARD_HADEAN		;}
	else if (result == 17 && overallType == OT_BARREN ) {worldType = WT_LARGE_OCEAN			;}
	else if (result == 18 && overallType == OT_BARREN ) {worldType = WT_LARGE_ICE			;}

	else if (result == 3  && overallType == OT_GARDEN ) {worldType = WT_STANDARD_GARDEN		;}
	else if (result == 4  && overallType == OT_GARDEN ) {worldType = WT_STANDARD_GARDEN		;}
	else if (result == 5  && overallType == OT_GARDEN ) {worldType = WT_STANDARD_GARDEN		;}
	else if (result == 6  && overallType == OT_GARDEN ) {worldType = WT_STANDARD_GARDEN		;}
	else if (result == 7  && overallType == OT_GARDEN ) {worldType = WT_STANDARD_GARDEN		;}
	else if (result == 8  && overallType == OT_GARDEN ) {worldType = WT_STANDARD_GARDEN		;}
	else if (result == 9  && overallType == OT_GARDEN ) {worldType = WT_STANDARD_GARDEN		;}
	else if (result == 10 && overallType == OT_GARDEN ) {worldType = WT_STANDARD_GARDEN		;}
	else if (result == 11 && overallType == OT_GARDEN ) {worldType = WT_STANDARD_GARDEN		;}
	else if (result == 12 && overallType == OT_GARDEN ) {worldType = WT_STANDARD_GARDEN		;}
	else if (result == 13 && overallType == OT_GARDEN ) {worldType = WT_STANDARD_GARDEN		;}
	else if (result == 14 && overallType == OT_GARDEN ) {worldType = WT_STANDARD_GARDEN		;}
	else if (result == 15 && overallType == OT_GARDEN ) {worldType = WT_STANDARD_GARDEN		;}
	else if (result == 16 && overallType == OT_GARDEN ) {worldType = WT_STANDARD_GARDEN		;}
	else if (result == 17 && overallType == OT_GARDEN ) {worldType = WT_LARGE_GARDEN		;}
	else if (result == 18 && overallType == OT_GARDEN ) {worldType = WT_LARGE_GARDEN		;}

	return worldType;
}
