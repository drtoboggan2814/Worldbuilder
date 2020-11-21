#include <cstdint>
int affinityScoreCalculator(int8_t resourceValueModifier, int8_t habitabilityModifier)
{
	int affinityScore;
	affinityScore = resourceValueModifier + habitabilityModifier;
	return affinityScore;
}
