//	This structure has been replaced by orbitalRadiusArray in star_t

#ifndef PLANETARYORBITSARRAY_T
#define PLANETARYORBITSARRAY_T


struct planetaryOrbitsArray_t
{
//	Can a structure have a flexible array?
	float planetaryOrbitsArray[32];
	int firstWorldIndex;
};

#endif
