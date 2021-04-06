import numpy as np
import pandas as pd
from scipy.spatial import Delaunay
from math import sqrt
import re

MAX_ROUTE_DISTANCE = 3


def printStatus(string, variable):
	print (f"{string} == {variable}")

#def matchDistanceAndStarNeighbors(starNeighbors, distance):

def checkPointData(jpDF, csvPointIndex, pointUniqueID):
	pointOK = True
	conflictingPoint = jpDF.loc[jpDF["connectingPointID"] == pointUniqueID]["uniqueID"]
	if (len(conflictingPoint) != 0):
		printStatus('conflictingPoint', conflictingPoint.values[0])
		pointOK = False
	return pointOK

def assignDistanceExtremes(starDf, minDistance, maxDistance, starIndex):
	starDF.at[starIndex, "minDistance"] = minDistance
	starDF.at[starIndex, "maxDistance"] = maxDistance
	return starDF

def assignPointData(jpDF, csvPointIndex, pointUniqueID, starUniqueID, connectingStarID, connectingPointID, distanceBetweenPoints, x, y, z):
	jpDF.at[csvPointIndex, "uniqueID"] = pointUniqueID
	jpDF.at[csvPointIndex, "starID"] = starUniqueID
	jpDF.at[csvPointIndex, "connectingStarID"] = connectingStarID
	jpDF.at[csvPointIndex, "connectingPointID"] = connectingPointID
	jpDF.at[csvPointIndex, "distanceToConnectingPoint"] = distanceBetweenPoints
	jpDF.at[csvPointIndex, "cartesianX"] = x
	jpDF.at[csvPointIndex, "cartesianY"] = y
	jpDF.at[csvPointIndex, "cartesianZ"] = z
	return jpDF

def createUniqueID(pointIndex, starUniqueID):
	pointUniqueID = str(pointIndex).rjust(2, "0")
#	Replace the last two digits in starUniqueID with pointUniqueID
	pointUniqueID = re.sub("..$", pointUniqueID, starUniqueID)
	return pointUniqueID

def distanceCalculator_ARRAY(x1, x2, y1, y2, z1, z2):
	xDiff, yDiff, zDiff = x2 - x1, y2 - y1, z2 - z1
	xPow, yPow, zPow = np.power(xDiff, 2), np.power(yDiff, 2), np.power(zDiff, 2)
	calcDist = np.zeros(len(xDiff))
	calcDist = np.power(xPow + yPow + zPow, 0.5)

	return calcDist

def distanceCalculator(x1, x2, y1, y2, z1, z2):
	distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2))
	return distance


def findNeighbors(starDF, neighborsDF, starIndex, x1, y1, z1):
#	Get neighbors
	starNeighbors = neighborsDF.values[starIndex][~np.isnan(neighborsDF.values[starIndex])].astype(int)
#	Get uniqueIDs for each neighbor
	neighborStarUniqueID = starDF.loc[starNeighbors, "uniqueID"]
	x2, y2, z2 = starDF.loc[starNeighbors, "cartesianX"], starDF.loc[starNeighbors, "cartesianY"], starDF.loc[starNeighbors, "cartesianZ"]

#	Get distance from star to each neighbor
	distance = distanceCalculator_ARRAY(x1, x2, y1, y2, z1, z2)
#	Only keep routes within max route distance
	distance = distance[distance <= MAX_ROUTE_DISTANCE]
	starNeighbors_Series = pd.Series(starNeighbors)
	starNeighbors_Series = starNeighbors_Series[starNeighbors_Series.isin(distance.index)]
	starNeighbors_Series.reset_index(drop=True, inplace=True)
	distance.reset_index(drop=True, inplace=True)
	printStatus("distance", distance)

	return starNeighbors_Series, distance


def main():
#	Read in star_t_db
	star_t_db = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/star_t_db_final.csv", dtype = {"uniqueID":object})

#	Read in starSystem_t_db
	starSystem_t_db = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/starSystem_t_db.csv", dtype = {"uniqueID":object})

#	Create starDF
	starDF = pd.DataFrame()
	starDF["uniqueID"] = star_t_db["uniqueID"]
	starDF["starSystemID"] = starSystem_t_db["uniqueID"]
	starDF["cartesianX"] = star_t_db["cartesianX"]
	starDF["cartesianY"] = star_t_db["cartesianY"]
	starDF["cartesianZ"] = star_t_db["cartesianZ"]
	starDF["numberOfJumpPoints"] = np.nan

#	Read in neighbors
	neighborsDF = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/neighbors_out.csv")

#	Create jpDF
	jpDF_columnNames = ["uniqueID", "starID", "connectingPointID", "connectingStarID", "distanceToConnectingPoint", "cartesianX", "cartesianY", "cartesianZ"]
	jpDF = pd.DataFrame(columns = jpDF_columnNames, dtype = object)
	jpDF["cartesianX"], jpDF["cartesianY"], jpDF["cartesianZ"] = starDF["cartesianX"], starDF["cartesianY"], starDF["cartesianZ"]

#	Get cartesian coordinates
	points = np.zeros((len(jpDF["cartesianX"]), 3))
	points[:, 0] = starDF["cartesianX"]
	points[:, 1] = starDF["cartesianY"]
	points[:, 2] = starDF["cartesianZ"]


#	Calculate Delaunay triangulation
	tri = Delaunay(points)
	starIndex = 0
	csvPointIndex = 0

#	Loop through starDF
	for star in starDF.values:
#		Get star uniqueID
		starUniqueID = star[starDF.columns.get_loc("uniqueID")]
		printStatus("\nstarIndex", starIndex)
#		Get cartesian coordinates
		x1, y1, z1 = star[starDF.columns.get_loc("cartesianX")], star[starDF.columns.get_loc("cartesianY")], star[starDF.columns.get_loc("cartesianZ")]
#		Get cartesian coordinates
#		Find neighbors
		starNeighbors_Series, starDistance = findNeighbors(starDF, neighborsDF, starIndex, x1, y1, z1)
		printStatus('starNeighbors_Series', starNeighbors_Series)
#		Iterate through neighbors
		pointIndex = 1
		for point, distance in zip(starNeighbors_Series, starDistance):
#			Assign unique ID
			pointUniqueID = createUniqueID(pointIndex, starUniqueID)

#			Get cartesian coordinates
			x1_point, y1_point, z1_point = starDF.at[point, "cartesianX"], starDF.at[point, "cartesianY"], starDF.at[point, "cartesianZ"]

#			Get point neighbors
			pointNeighbors_Series, pointDistance = findNeighbors(starDF, neighborsDF, point, x1_point, y1_point, z1_point)

#			Get the star's index in pointNeighbors_Series
			star_0_index = pointNeighbors_Series[pointNeighbors_Series.values == starIndex].index[0]

#			Get connecting star ID
			connectingStarID = starDF.at[point, "uniqueID"]

#			Create unique ID for connecting point
			connectingPointID = createUniqueID(int(star_0_index) + 1, connectingStarID)

#			Assign data
			jpDF = assignPointData(jpDF, csvPointIndex, pointUniqueID, starUniqueID, connectingStarID, connectingPointID, distance, x1, y1, z1)

			pointIndex += 1
			csvPointIndex += 1


		starIndex += 1
#		if (starIndex == 100):
#			break

#	Export
	jpDF.to_csv("Z:/Projects/Worldbuilder/finalOutput/jpDF_out_max_8_3pc.csv", index = False)
	star_t_db["numberOfJumpPoints"] = starDF["numberOfJumpPoints"]
	star_t_db["starSystemID"] = starDF["starSystemID"]
	star_t_db.to_csv("Z:/Projects/Worldbuilder/finalOutput/star_t_db_final.csv", index = False)


main()
