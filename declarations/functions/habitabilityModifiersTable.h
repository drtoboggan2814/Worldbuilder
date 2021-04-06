#include <cstdint>
#include <tuple>
#include "../structures/atmosphericComposition_t.h"
std::tuple<int, char, bool> habitabilityModifiersTable(char worldType, float atmosphereMass, float hydrographicCoverage, float atmosphericPressure, int surfaceTemperature, atmosphericComposition_t atmosphereCompositionArray);
