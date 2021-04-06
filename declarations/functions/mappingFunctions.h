#include <cstdint>

char getHexesPerSide(float worldDiameter);

int getTotalHexCount(char hexesPerSide);

int getUWPHydrographic(float hydrographicCoverage);

int getUWPSize(float worldDiameter, char worldType);

int getTectonicPlateCount(float worldDiameter, float hydrographicCoverage, char worldType);

int getTectonicPlateSize (int averagePlateSize, int variance, int remainingHexes, bool lastPlate);
//	int getTectonicPlateSize(float worldDiameter, int remainingHexes, bool lastPlate, char worldType);

char getTectonicPlateMovementType();

int getWaterHexCount(int totalHexCount, float hydrographicCoverage);

int getLandHexCount(int totalHexCount, int waterHexCount);

char getMajorOceans(int diceRoll);

char getMinorOceans(int diceRoll);

char getSmallSeas(int diceRoll);

char getScatteredLakes(int diceRoll);

char getMajorContinents(int diceRoll);

char getMinorContinents(int diceRoll);

char getMajorIslands(int diceRoll);

char getArchipelagoes(int diceRoll);
