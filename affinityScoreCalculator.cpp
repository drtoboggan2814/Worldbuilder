#include <cstdint>
int affinityScoreCalculator(int resourceValueModifier, int habitabilityModifier)
{
	int affinityScore = resourceValueModifier + habitabilityModifier;
	return affinityScore;
}
