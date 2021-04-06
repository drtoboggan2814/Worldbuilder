import numpy as np
import pandas as pd
from random import randint
import re

rng = np.random.default_rng(12345)


#def printStatus(str string, variable):
#	print (f"{string} == {variable}")

#	Determine the distance coefficient based on the star's Harvard letter
cdef int getJPDistanceCoefficient(str harvardLetter):
	cdef int SUBTRACTION_COEFFICIENT = 20
	if 		(harvardLetter == "O")	:	return (24)
	elif 	(harvardLetter == "B")	:	return (20)
	elif 	(harvardLetter == "D")	:	return (16)
	elif 	(harvardLetter == "A")	:	return (12)
	elif 	(harvardLetter == "F")	:	return (8)
	elif 	(harvardLetter == "G")	:	return (4)
	elif 	(harvardLetter == "K")	:	return (2)
	else							:	return (1)

#	Determine the jump points's distance from the primary
cdef double getJPDistance(str harvardLetter):
	cdef int diceRoll = rng.integers(low=0, high=20, size=1)[0]
#	printStatus("diceRoll", diceRoll)
	diceRoll *= 3
#	printStatus("diceRoll", diceRoll)
	cdef double distance = diceRoll + getJPDistanceCoefficient(harvardLetter)
#	Convert to au
	distance *= 0.1202
	return distance

#	Determine the degree of the arc
cdef int def getJPArc():
	cdef int arc = rng.integers(low=0, high=360, size=1)[0]
	return arc

#	Determine if the location of the jump point conflicts with any world
cdef bool checkJPLocation(double jpDistance, double[:] smaArray):
#	Loop through the smaArray
	cdef int smaArray_index = 0
	cdef bool jpLocationOK = True
	cdef double orbit
	for orbit in smaArray:
#		If jpDistance is within 0.9 to 1.1 of the orbit, jpLocationOK is False
#		Otherwise, default to True
#		printStatus("orbit", orbit)
		if (jpDistance <= (1.1 * orbit) and jpDistance >= (0.9 * orbit)):
			jpLocationOK = False
			break
	return jpLocationOK

#	Assign data to jpDF
def assignJumpPointLocation(jpDF, distance, angle, csvPointIndex):
	jpDF.at[csvPointIndex, "distanceToPrimary"] = distance
	jpDF.at[csvPointIndex, "arc"] = angle
	return jpDF

#	Place jump points
def placeJumpPointOrbits(str harvardLetter, double[:] smaArray, int numberOfJumpPoints, int csvPointIndex, jpDF):
#	printStatus("csvPointIndex", csvPointIndex)
#	For each jump point
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
		if (~jpLocationOK):
#			Reroll distance until location is OK
			while (~jpLocationOK):
				distance = getJPDistance(harvardLetter)
				jpLocationOK = checkJPLocation(distance, smaArray)
				if (jpLocationOK):
					break
#		Assign data
		jpDF = assignJumpPointLocation(jpDF, distance, angle, csvPointIndex)
#		Increment csvPointIndex
		csvPointIndex += 1
	return jpDF, csvPointIndex


def main():
#	Read in .csv's
#	starDF = pd.read_csv("star_t_db - Copy.csv", dtype = {"uniqueID":object})
#	jpDF = pd.read_csv("jpDF_out_max_8_3pc.csv", dtype = {"uniqueID":object, "starID":object, "connectingPointID":object, "connectingStarID":object})
#	worldDF = pd.read_csv("world_t_db - Copy.csv", dtype = {"uniqueID":object})
	starDF = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/star_t_db_final.csv", dtype = {"uniqueID":object})
	jpDF = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/jpDF_out_max_8_3pc.csv", dtype = {"uniqueID":object, "starID":object, "connectingPointID":object, "connectingStarID":object, "starSystemID":object})
	worldDF = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/world_t_db_final.csv", dtype = {"uniqueID":object})
#	Index for jpDF
	csvPointIndex = 0
#	Index for starDF
	starIndex = 0
#	Iterate through star_t_db
	for star in starDF.values:
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
#		if (starIndex == 1):
#			break
	jpDF.to_csv("Z:/Projects/Worldbuilder/finalOutput/jpDF_out_max_8_3pc.csv", index = False)

main()
