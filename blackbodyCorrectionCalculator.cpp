//	Calculate the world's blackbody correction, takes the world type's
//	absorption factor, greenhouse factor, and atmospheric mass as parameters.
float blackbodyCorrectionCalculator(const float& af, const float& gf, const float& atmosphereMass)
{
	float blackbodyCorrection = af * (1 + (atmosphereMass * gf));
	return blackbodyCorrection;
}
