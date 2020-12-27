#include <cstdint>

uint8_t getHexesPerSide(float worldDiameter);

uint16_t getTotalHexCount(uint8_t hexesPerSide);

uint8_t getUWPHydrographic(float hydrographicCoverage);

uint8_t getUWPSize(float worldDiameter);

uint8_t getTectonicPlateCount(float worldDiameter, float hydrographicCoverage);

uint8_t getTectonicPlateSize(float worldDiameter);

uint8_t getTectonicPlateMovementType();

uint16_t getWaterHexCount(const uint16_t& totalHexCount, float hydrographicCoverage);

uint16_t getLandHexCount(const uint16_t& totalHexCount, const uint16_t& waterHexCount);

uint8_t getMajorOceans(int diceRoll);

uint8_t getMinorOceans(int diceRoll);

uint8_t getSmallSeas(int diceRoll);

uint8_t getScatteredLakes(int diceRoll);

uint8_t getMajorContinents(int diceRoll);

uint8_t getMinorContinents(int diceRoll);

uint8_t getMajorIslands(int diceRoll);

uint8_t getArchipelagoes(int diceRoll);
