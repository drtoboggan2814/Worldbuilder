#include <tuple>


//	This function returns the day face modifier

float tideLockedDayFaceModifierTable(string pressureCategory);

//	This function returns the night face modifier
float tideLockedNightFaceModifierTable(string pressureCategory);

//	The effect of tidal forces on the pressure category of the atmosphere
string tideLockedFinalAtmosphereTable(string pressureCategory);

//	This function acts as a lookup table for the hydrographic coverage modifier
float tideLockedHydrographicCoverageModifier(string pressureCategory);

//	This function takes the effects of a tidally locked world on a world's
//	atmosphere and hydrographic coverage into account
std::tuple<float, string, float> tideLockedWorldEffects(bool tidalLockedOrNot, float surfaceTemperature, string atmosphericPressureCategory, float atmosphericPressure, float atmosphereMass, float surfaceGravity, string worldType, float hydrographicCoverage);

//	This function checks to see if the world is in a stable resonant pattern,
//	rather than being tide-locked
std::tuple<bool, float> resonantWorldEffects(float orbitalEccentricity, bool tidalLockedOrNot, float orbitalPeriod, float apparentDayLength);
