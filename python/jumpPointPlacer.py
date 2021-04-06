import numpy as np
import pandas as pd
from random import randint
import re
import time

rng = np.random.default_rng(12345)


def printStatus(string, variable):
	print (f"{string} == {variable}")

#	Determine the distance coefficient based on the star's Harvard letter
def getJPDistanceCoefficient(harvardLetter):
	SUBTRACTION_COEFFICIENT = 20
	if 		(harvardLetter == "O")	:	return (24)
	elif 	(harvardLetter == "B")	:	return (20)
	elif 	(harvardLetter == "D")	:	return (16)
	elif 	(harvardLetter == "A")	:	return (12)
	elif 	(harvardLetter == "F")	:	return (8)
	elif 	(harvardLetter == "G")	:	return (4)
	elif 	(harvardLetter == "K")	:	return (2)
	else							:	return (1)

#	Determine the jump points's distance from the primary
def getJPDistance(harvardLetter):
	diceRoll = rng.integers(low=0, high=20, size=1)[0]
#	printStatus("diceRoll", diceRoll)
	diceRoll *= 3
#	printStatus("diceRoll", diceRoll)
	distance = diceRoll + getJPDistanceCoefficient(harvardLetter)
#	Convert to au
	distance *= 0.1202
	return distance

#	Determine the degree of the arc
def getJPArc():
	return randint(0, 360)

#	Determine if the location of the jump point conflicts with any world
def checkJPLocation(jpDistance, smaArray):
#	Loop through the smaArray
#	smaArray_index = 0
#	cond1 = (jpDistance <= (1.1 * smaArray.values)).any()
#	printStatus()
#	cond2 = (jpDistance >= (0.9 * smaArray.values)).any()
#	printStatus("smaArray.values", smaArray.values)
	jpLocationOK = ~(jpDistance <= (1.1 * smaArray.values)).any() and (jpDistance >= (0.9 * smaArray.values)).any()
#	jpLocationOK = cond1 and cond2
#	for orbit in smaArray:
#		If jpDistance is within 0.9 to 1.1 of the orbit, jpLocationOK is False
#		Otherwise, default to True
#		printStatus("orbit", orbit)
#		if (jpDistance <= (1.1 * orbit) and jpDistance >= (0.9 * orbit)):
#			jpLocationOK = False
#			break
	return jpLocationOK

#	Assign data to jpDF
def assignJumpPointLocation(jpDF, distance, angle, csvPointIndex):
	jpDF.at[csvPointIndex, "distanceToPrimary"] = distance
	jpDF.at[csvPointIndex, "arc"] = angle
	return jpDF

#	Place jump points
def placeJumpPointOrbits(harvardLetter, smaArray, numberOfJumpPoints, csvPointIndex, jpDF):
#	printStatus("csvPointIndex", csvPointIndex)
#	For each jump point
#	time_placeJumpPoint = time.time()
	for jumpPoint in range(int(numberOfJumpPoints)):
#		Get distance
		distance = getJPDistance(harvardLetter)
#		printStatus("distance", distance)
#		Get angle
		angle = getJPArc()
#		printStatus("angle", angle)
#		Check if location is OK
		jpLocationOK = checkJPLocation(distance, smaArray)
#		printStatus("jpLocationOK", jpLocationOK)
#		If the location is not OK
		if (jpLocationOK):
#			Reroll distance until location is OK
			while (~jpLocationOK):
				distance = getJPDistance(harvardLetter)
#				printStatus("distance", distance)
				jpLocationOK = checkJPLocation(distance, smaArray)
				if (jpLocationOK):
					break
#		Assign data
		jpDF = assignJumpPointLocation(jpDF, distance, angle, csvPointIndex)
#		Increment csvPointIndex
		csvPointIndex += 1

#	printStatus("time_placeJumpPoint", (time.time() - time_placeJumpPoint))
	return jpDF, csvPointIndex


def main():
#	Read in .csv's
#	starDF = pd.read_csv("star_t_db - Copy.csv", dtype = {"uniqueID":object})
#	jpDF = pd.read_csv("jpDF_out_max_8_3pc.csv", dtype = {"uniqueID":object, "starID":object, "connectingPointID":object, "connectingStarID":object})
#	worldDF = pd.read_csv("world_t_db - Copy.csv", dtype = {"uniqueID":object})
	time_starDF = time.time()
	starDF = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/star_t_db_final.csv", dtype = {"uniqueID":object})
	printStatus("starDF time", (time.time() - time_starDF))
	time_jpDF = time.time()
	jpDF = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/jpDF_out_max_8_3pc.csv", dtype = {"uniqueID":object, "starID":object, "connectingPointID":object, "connectingStarID":object, "starSystemID":object})
	printStatus("jpDF time", (time.time() - time_jpDF))
	time_worldDF = time.time()
	worldDF = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/world_t_db_final.csv", dtype = {"uniqueID":object}, usecols = {"uniqueID", "orbitalRadius"})
	printStatus("worldDF time", (time.time() - time_worldDF))
#	Index for jpDF
	csvPointIndex = 0
#	Index for starDF
	starIndex = 0
#	Iterate through star_t_db
	time_starLoop = time.time()
	for star in starDF.values:
		time_starLoop = time.time()
		printStatus("starIndex", starIndex)
#		Get the star's ID
		starID = star[starDF.columns.get_loc("uniqueID")]
#		Truncate starID for matching
		starID_Trunc = re.sub(starID[5:], '', starID)
#		Get harvard letter
		harvardLetter = star[starDF.columns.get_loc("harvardLetter")]
#		Get number of jump points
		numberOfJumpPoints = star[starDF.columns.get_loc("numberOfJumpPoints")]
#		Find worlds around star
		worldIndex = 0
#		worldArray = worldDF["uniqueID"].loc[worldDF["uniqueID"].str.startswith(starID_Trunc)]
		worldArray = worldDF.loc[worldDF["uniqueID"].str.startswith(starID_Trunc)]
#		printStatus("worldArray", worldArray)
		smaArray = worldArray["orbitalRadius"]
#		printStatus("smaArray", smaArray)
		jpDF, csvPointIndex = placeJumpPointOrbits(harvardLetter, smaArray, numberOfJumpPoints, csvPointIndex, jpDF)
		starIndex += 1
		printStatus("starLoop time", (time.time() - time_starLoop))
#		if (starIndex == 1):
#			break
	jpDF.to_csv("Z:/Projects/Worldbuilder/finalOutput/jpDF_out_max_8_3pc.csv", index = False)

main()
