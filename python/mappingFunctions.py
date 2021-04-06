import mappingConstants as mC
from math import ceil
import numpy as np
import pandas as pd
import printStatus as pS

rng = np.random.default_rng(12345)
def diceRoller(diceNumber, numberOfDice):
	diceRoll = rng.integers(low=numberOfDice, high=diceNumber, size=1)[0]
	return diceRoll

def getUWPSize(worldDiameter, worldType):
	uwpSize = 0
	worldDiameterKM = worldDiameter * mC.EARTH_RADIUS_IN_KM * 2

	if (worldType == mC.WT_ASTEROID_BELT or worldType == mC.WT_SMALL_GAS_GIANT or worldType == mC.WT_MEDIUM_GAS_GIANT or worldType == mC.WT_LARGE_GAS_GIANT):
		uwpSize = 0
	elif (worldDiameter < 2400):
		uwpSize = 1
	elif (worldDiameter >= 2400 and worldDiameter < 4000):
		uwpSize = 2
	elif (worldDiameter >= 4000 and worldDiameter < 5600):
		uwpSize = 3
	elif (worldDiameter >= 5600 and worldDiameter < 7200):
		uwpSize = 4
	elif (worldDiameter >= 7200 and worldDiameter < 8800):
		uwpSize = 5
	elif (worldDiameter >= 8800 and worldDiameter < 10400):
		uwpSize = 6
	elif (worldDiameter >= 10400 and worldDiameter < 12000):
		uwpSize = 7
	elif (worldDiameter >= 12000 and worldDiameter < 13600):
		uwpSize = 8
	elif (worldDiameter >= 13600 and worldDiameter < 15200):
		uwpSize = 9
	elif (worldDiameter >= 15200 and worldDiameter < 16800):
		uwpSize = 10
	elif (worldDiameter >= 16800 and worldDiameter < 18400):
		uwpSize = 11
	else:
		uwpSize = 12

	return uwpSize

def getUWPHydrographic(hydrographicCoverage):

	uwpHydrographic = 0

	if 	 (hydrographicCoverage < 0.06):
		uwpHydrographic = 0
	elif (hydrographicCoverage >= 0.06 and hydrographicCoverage < 0.15):
		uwpHydrographic = 1
	elif (hydrographicCoverage >= 0.16 and hydrographicCoverage < 0.25):
		uwpHydrographic = 2
	elif (hydrographicCoverage >= 0.26 and hydrographicCoverage < 0.35):
		uwpHydrographic = 3
	elif (hydrographicCoverage >= 0.36 and hydrographicCoverage < 0.45):
		uwpHydrographic = 4
	elif (hydrographicCoverage >= 0.46 and hydrographicCoverage < 0.55):
		uwpHydrographic = 5
	elif (hydrographicCoverage >= 0.56 and hydrographicCoverage < 0.65):
		uwpHydrographic = 6
	elif (hydrographicCoverage >= 0.66 and hydrographicCoverage < 0.75):
		uwpHydrographic = 7
	elif (hydrographicCoverage >= 0.76 and hydrographicCoverage < 0.85):
		uwpHydrographic = 8
	elif (hydrographicCoverage >= 0.86 and hydrographicCoverage < 0.95):
		uwpHydrographic = 9
	else:
		uwpHydrographic = 10

	return uwpHydrographic

def getMajorOceans(diceRoll):

	numberOfMajorOceans = 0
	if 		(diceRoll <= 6):
		numberOfMajorOceans = 0
	elif (diceRoll >= 19):
		numberOfMajorOceans = 1
	else:
		numberOfMajorOceans = diceRoller(6, 1) - mC.MAJOR_OCEAN_ADDITION_COEFFICIENT[diceRoll - 1 - 16]

	numberOfMajorOceans =  0 if ((numberOfMajorOceans < 0) or (numberOfMajorOceans > 6)) else numberOfMajorOceans

	return numberOfMajorOceans


def getMinorOceans(diceRoll):
	pS.printStatus("diceRoll", diceRoll)
	numberOfMinorOceans = 0
	if (diceRoll <= 6):
		numberOfMinorOceans = 0
	else:
		numberOfMinorOceans = diceRoller(6, mC.MINOR_OCEAN_MULTIPLIER_COEFFICIENT[diceRoll - 1 - 16]) - mC.MINOR_OCEAN_ADDITION_COEFFICIENT[diceRoll - 1 - 16]

	numberOfMinorOceans = 0 if ((numberOfMinorOceans < 0) or (numberOfMinorOceans > 15)) else numberOfMinorOceans

	return numberOfMinorOceans


def getSmallSeas(diceRoll):

	numberOfSmallSeas = 0
	if (diceRoll < 5):
		numberOfSmallSeas = 0
	elif (diceRoll == 5):
		numberOfSmallSeas = diceRoller(6, 1) - 3
	elif (diceRoll == 6):
		numberOfSmallSeas = diceRoller(6, 2) - 3
	else:
		numberOfSmallSeas = diceRoller(6, 3) - 3

	numberOfSmallSeas = 0 if ((numberOfSmallSeas < 0) or (numberOfSmallSeas > 15)) else numberOfSmallSeas

	return numberOfSmallSeas

def getScatteredLakes(diceRoll):

	numberOfScatteredLakes = 0
	if (diceRoll < 3):
		numberOfScatteredLakes = 0
	elif (diceRoll == 3 or diceRoll == 4):
		numberOfScatteredLakes = 1
	else:
		numberOfScatteredLakes = diceRoller(6, 2)

	return numberOfScatteredLakes


def getMajorContinents(diceRoll):

	numberOfMajorContinents = 0
	if (diceRoll < 31):
		numberOfMajorContinents = diceRoller(6, mC.MAJOR_CONTINENT_MULTIPLIER_COEFFICIENT[diceRoll - 1 - 16]) + mC.MAJOR_CONTINENT_ADDITION_COEFFICIENT[diceRoll - 1 - 16]
	else:
		numberOfMajorContinents = 0

	numberOfMajorContinents = 0 if ((numberOfMajorContinents < 0) or (numberOfMajorContinents > 13)) else numberOfMajorContinents

	return numberOfMajorContinents


def getMinorContinents(diceRoll):

	numberOfMinorContinents = 0
	if (diceRoll < 31):
		numberOfMinorContinents = diceRoller(6, mC.MINOR_CONTINENT_MULTIPLIER_COEFFICIENT[diceRoll - 1 - 16]) + mC.MINOR_CONTINENT_ADDITION_COEFFICIENT[diceRoll - 1 - 16]
	else:
		numberOfMinorContinents = 0

	numberOfMinorContinents = 0 if ((numberOfMinorContinents < 0) or (numberOfMinorContinents > 18)) else numberOfMinorContinents

	return numberOfMinorContinents


def getMajorIslands(diceRoll):

	numberOfMajorIslands = 0
	if (diceRoll < 30):
		numberOfMajorIslands = diceRoller(6, 3) - 3
	elif (diceRoll == 30):
		numberOfMajorIslands = diceRoller(6, 2)
	elif (diceRoll == 31):
		numberOfMajorIslands = diceRoller(6, 1) - 3
	else:
		numberOfMajorIslands = 0

	numberOfMajorIslands = 0 if ((numberOfMajorIslands < 0) or (numberOfMajorIslands > 15)) else numberOfMajorIslands

	return numberOfMajorIslands


def getArchipelagoes(diceRoll):

	numberOfArchipelagoes = 0
	if (diceRoll < 32):
		numberOfArchipelagoes = diceRoller(6, 2)
	elif (diceRoll < 35 and diceRoll > 31):
		numberOfArchipelagoes = 1
	else:
		numberOfArchipelagoes = 0

	numberOfArchipelagoes = 0 if ((numberOfArchipelagoes < 0) or (numberOfArchipelagoes > 12)) else numberOfArchipelagoes

	return numberOfArchipelagoes

def main():
	#	worldDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/world_t_db_final.csv", dtype = {"uniqueID":object})
	#	moonDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/moon_t_db.csv", dtype = {"uniqueID":object})

	worldDF = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/world_t_db_final.csv", dtype = {"uniqueID":object, "starID":object, "starSystemID":object})
	moonDF = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/moon_t_db.csv", dtype = {"uniqueID":object})

	worldIndex = 0
	for world in worldDF.values:
		hydrographicCoverage = world[worldDF.columns.get_loc("hydrographicCoverage")]
		pS.printStatus("hydrographicCoverage", hydrographicCoverage)
		if (~np.isnan(hydrographicCoverage)):
			hexDiceRoll = diceRoller(6, 1) + (3 * int(ceil(hydrographicCoverage * 10)))
			pS.printStatus("hexDiceRoll", hexDiceRoll)
			numberOfMajorOceans 		= getMajorOceans(hexDiceRoll)
			pS.printStatus("numberOfMajorOceans", numberOfMajorOceans)
			numberOfMinorOceans 		= getMinorOceans(hexDiceRoll)
			pS.printStatus("numberOfMinorOceans", numberOfMinorOceans)
			numberOfSmallSeas 			= getSmallSeas(hexDiceRoll)
			pS.printStatus("numberOfSmallSeas", numberOfSmallSeas)
			numberOfScatteredLakes 		= getScatteredLakes(hexDiceRoll)
			pS.printStatus("numberOfScatteredLakes", numberOfScatteredLakes)
			numberOfMajorContinents 	= getMajorContinents(hexDiceRoll)
			pS.printStatus("numberOfMajorContinents", numberOfMajorContinents)
			numberOfMinorContinents 	= getMinorContinents(hexDiceRoll)
			pS.printStatus("numberOfMinorContinents", numberOfMinorContinents)
			numberOfMajorIslands 		= getMajorIslands(hexDiceRoll)
			pS.printStatus("numberOfMajorIslands", numberOfMajorIslands)
			numberOfArchipelagoes 		= getArchipelagoes(hexDiceRoll)
			pS.printStatus("numberOfArchipelagoes", numberOfArchipelagoes)

			worldIndex += 1
			if (worldIndex == 10):
				break

	#	worldDF.to_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/world_t_db_final.csv", index = False)
	#	moonDF.to_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/moon_t_db.csv", index = False)

	#	worldDF.to_csv("Z:/Projects/Worldbuilder/finalOutput/world_t_db_final.csv", index = False)
	#	moonDF.to_csv("Z:/Projects/Worldbuilder/finalOutput/moon_t_db.csv", index = False)

main()
