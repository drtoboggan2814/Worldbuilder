//	This function applies only to basic worldbuilding; geneerateWorldDetails.cpp
//	replaces this function
float blackbodyTemperatureCalculator(float blackbodyCorrection, int surfaceTemperature)
{
	float blackbodyTemperature = surfaceTemperature / blackbodyCorrection;
	return blackbodyTemperature;
}
