//	Calculate the world's blackbody correction, takes the world type's
//	absorption factor, greenhouse factor, and atmospheric mass as parameters.
float blackbodyCorrectionCalculator(float af, float gf, float atmosphereMass)
{
	float blackbodyCorrection = af * (1 + (atmosphereMass * gf));
	return blackbodyCorrection;
}
