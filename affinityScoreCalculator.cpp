#include <cstdint>
int affinityScoreCalculator(const int8_t& resourceValueModifier, const int8_t& habitabilityModifier)
{
	int affinityScore;
	affinityScore = resourceValueModifier + habitabilityModifier;
	return affinityScore;
}
