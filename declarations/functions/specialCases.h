#include <tuple>


//	This function returns the day face modifier

float tideLockedDayFaceModifierTable(char pressureCategory);

//	This function returns the night face modifier
float tideLockedNightFaceModifierTable(char pressureCategory);

//	The effect of tidal forces on the pressure category of the atmosphere
char tideLockedFinalAtmosphereTable(char pressureCategory);

//	This function acts as a lookup table for the hydrographic coverage modifier
float tideLockedHydrographicCoverageModifier(char pressureCategory);

//	This function takes the effects of a tidally locked world on a world's
//	atmosphere and hydrographic coverage into account
std::tuple<float, char, float, float, float> tideLockedWorldEffects(bool tidalLockedOrNot, float surfaceTemperature, char atmosphericPressureCategory, float atmosphericPressure, float atmosphereMass, float surfaceGravity, char worldType, float hydrographicCoverage);

//	This function checks to see if the world is in a stable resonant pattern,
//	rather than being tide-locked
std::tuple<bool, float> resonantWorldEffects(float orbitalEccentricity, bool tidalLockedOrNot, float orbitalPeriod, float apparentDayLength);
