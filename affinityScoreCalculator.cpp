int affinityScoreCalculator(int resourceValueModifier, int habitabilityModifier)
{
	int affinityScore;
	affinityScore = resourceValueModifier + habitabilityModifier;
	return affinityScore;
}