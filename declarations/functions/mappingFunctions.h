#include <cstdint>

uint8_t getHexesPerSide(const float& worldDiameter);

uint16_t getTotalHexCount(const uint8_t& hexesPerSide);

uint8_t getUWPHydrographic(const float& hydrographicCoverage);

uint8_t getUWPSize(const float& worldDiameter);

uint8_t getTectonicPlateCount(const float& worldDiameter, const float& hydrographicCoverage);

uint8_t getTectonicPlateSize(const float& worldDiameter);

uint8_t getTectonicPlateMovementType();

uint16_t getWaterHexCount(const uint16_t& totalHexCount, const float& hydrographicCoverage);

uint16_t getLandHexCount(const uint16_t& totalHexCount, const uint16_t& waterHexCount);

uint8_t getMajorOceans(const int& diceRoll);

uint8_t getMinorOceans(const int& diceRoll);

uint8_t getSmallSeas(const int& diceRoll);

uint8_t getScatteredLakes(const int& diceRoll);

uint8_t getMajorContinents(const int& diceRoll);

uint8_t getMinorContinents(const int& diceRoll);

uint8_t getMajorIslands(const int& diceRoll);

uint8_t getArchipelagoes(const int& diceRoll);
