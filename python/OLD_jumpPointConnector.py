#	This program reads in jumpPoint_t_db.csv and connects jump points to other
#	stars.  Stars within a multiple=star system can connect to each other, but
#	an individual star's jump points cannot.

import math
import numpy as np
import pandas as pd
from random import randint
import re
import time

#def checkCondition(radiusDiceRoll, distanceBetweenPoints):
#	conditionOne	= (distanceBetweenPoints <= 1)
#	conditionTwo	= (distanceBetweenPoints > 1) and (distanceBetweenPoints <= 2)
#	conditionThree	= (distanceBetweenPoints > 2) and (distanceBetweenPoints <= 3)
#	conditionFour	= (distanceBetweenPoints > 3) and (distanceBetweenPoints <= 4)


#	conditionOne	= (radiusDiceRoll == 1) and (distanceBetweenPoints <= 1)
#	conditionTwo	= (radiusDiceRoll == 2) and (distanceBetweenPoints > 1) and (distanceBetweenPoints <= 2)
#	conditionThree	= (radiusDiceRoll == 3) and (distanceBetweenPoints > 2) and (distanceBetweenPoints <= 3)
#	conditionFour	= (radiusDiceRoll == 4) and (distanceBetweenPoints > 3) and (distanceBetweenPoints <= 4)
#	conditionFive	= (radiusDiceRoll == 5) and (distanceBetweenPoints > 4) and (distanceBetweenPoints <= 5)
#	conditionSix	= (radiusDiceRoll == 6) and (distanceBetweenPoints > 5) and (distanceBetweenPoints <= 6)
#	conditionSeven	= (radiusDiceRoll == 7) and (distanceBetweenPoints > 6) and (distanceBetweenPoints <= 7)
#	conditionEight	= (radiusDiceRoll == 8) and (distanceBetweenPoints > 7) and (distanceBetweenPoints <= 8)
#	if (conditionOne or conditionTwo or conditionThree or conditionFour):# or conditionFive or conditionSix or conditionSeven or conditionEight):
#		return True
#	else:
#		return False

def checkSeriesLength(series, lengthValue):
	return len(series) == lengthValue

def oneDDistanceCalculator(a, b):
	return math.sqrt(pow(b - a, 2))

def printStatus(string, variable):
	print (f"{string} == {variable}")

#	Calculate the distance between two points in space
def distanceCalculator(x1, x2, y1, y2, z1, z2):
	xDiff, yDiff, zDiff = x2 - x1, y2 - y1, z2 - z1
	xPow, yPow, zPow = np.power(xDiff, 2), np.power(yDiff, 2), np.power(zDiff, 2)
	calcDist = np.zeros(len(xDiff))
	calcDist = np.power(xPow + yPow + zPow, 0.5)

	return calcDist

def filterProspectivePoint_1(jpDF, prospectivePoint_1, pointIndex_0):
	NOPOINTFOUND = 10000
#	Check if all points in prospectivePoint_1 are np.nan
	allPointsNan = np.all(np.isnan(jpDF.loc[prospectivePoint_1.index, "connectingJumpPoint"]))
	printStatus("allPointsNan", allPointsNan)
#	Get points with the same starID
	sameStarJumpPoints = jpDF["uniqueID"].loc[jpDF["uniqueID"].str.startswith(str(jpDF.at[pointIndex_0, "starID"]))]
#	Drop point_0 from sameStarJumpPoints
	point_0_uniqueID = jpDF.at[pointIndex_0, "uniqueID"]
	point_0_starID = jpDF.at[pointIndex_0, "starID"]
	sameStarJumpPoints = sameStarJumpPoints.drop(pointIndex_0)
#	Check if connectingJumpPoint in prospectivePoint_1 matches point_0's starID
	conflictingStarPoints = jpDF.loc[prospectivePoint_1.index, "connectingStarID"]
	printStatus("conflictingStarPoints", conflictingStarPoints)
	printStatus("conflictingStarPoints", type(conflictingStarPoints))
	if (len(conflictingStarPoints) > 0):
		printStatus("type(conflictingStarPoints[0])", type(conflictingStarPoints.values[0]))
#	Drop jump points that equal point_0's starID
	printStatus('jpDF.at[pointIndex_0, "starID"]', jpDF.at[pointIndex_0, "starID"])
	printStatus('type(jpDF.at[pointIndex_0, "starID"])', type(jpDF.at[pointIndex_0, "starID"]))
	conflictingStarPoints = conflictingStarPoints.loc[conflictingStarPoints != float(point_0_starID)]
#	Drop jump points that do not equal nan
	conflictingStarPoints = conflictingStarPoints.loc[np.isnan(conflictingStarPoints)]
	printStatus("conflictingStarPoints", conflictingStarPoints)
#	If there are no valid jump points left over, return NOPOINTFOUND (greater than the length of jpDF)
	printStatus("len(conflictingStarPoints)", len(conflictingStarPoints))
	if (len(conflictingStarPoints) == 0):
		return NOPOINTFOUND
#	Get the value at the top of conflictingStarPoints
	else:
		pointIndex_1 = conflictingStarPoints.index[0]
		return pointIndex_1

def getProspectivePoint_1(calcDist_Series, searchRadius):
	return calcDist_Series[(calcDist_Series <= searchRadius) & (calcDist_Series > 0)]

def assignPointData(jpDF, pointIndex_0, pointIndex_1, distanceBetweenPoints):
	connectingID = jpDF.at[pointIndex_1, "uniqueID"]
	connectingStarID = jpDF.at[pointIndex_1, "starID"]
	jpDF.at[pointIndex_0, "connectingJumpPoint"] = connectingID
	jpDF.at[pointIndex_0, "connectingStarID"] = connectingStarID
	jpDF.at[pointIndex_0, "distanceToConnectingPoint"] = distanceBetweenPoints
	jpDF.at[pointIndex_1, "connectingJumpPoint"] = jpDF.at[pointIndex_0, "uniqueID"]
	jpDF.at[pointIndex_1, "connectingStarID"] = jpDF.at[pointIndex_0, "starID"]
	jpDF.at[pointIndex_1, "distanceToConnectingPoint"] = distanceBetweenPoints

	return jpDF

def jumpPointConnector():
	NOPOINTFOUND = 10000
#	Read in jumpPoint_t_db.csv
	jpDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/output/jumpPoint_t_db.csv", encoding = "cp1252", usecols = ["uniqueID", "connectingJumpPoint", "cartesianX", "cartesianY", "cartesianZ", "distanceToConnectingPoint"], dtype = {"uniqueID" : object})
#	Set uniqueID to string
	jpDF["uniqueID"] = jpDF["uniqueID"].astype(str)
#	Insert starID as a column between uniqueID and connectingJumpPoint
	jpDF.insert(jpDF.columns.get_loc("connectingJumpPoint"), "starID", jpDF["uniqueID"].str.slice(0, 5))
#	Insert connectingStarID as a column between connectingJumpPoint and cartesianX
	jpDF.insert(jpDF.columns.get_loc("connectingJumpPoint"), "connectingStarID", np.nan)
#	Set connectingJumpPoint to np.nan
	jpDF["connectingJumpPoint"] = np.nan
#	Index for the current point 0
	pointIndex_0 = 0
	MAXPOINTINDEX = len(jpDF["uniqueID"]) -2
#	Convert cartesian components to np array
	cartesianCoordinatesDF = jpDF[jpDF.columns[jpDF.columns.get_loc("cartesianX"):(jpDF.columns.get_loc("cartesianZ") + 1)]]
	CARTESIANX_NP_COL, CARTESIANY_NP_COL, CARTESIANZ_NP_COL = 0, 1, 2
	cartesianCoordinatesDF = cartesianCoordinatesDF.values
#	Loop through jpDF with point_0
	for point_0 in jpDF.iterrows():
		printStatus("pointIndex_0", pointIndex_0)
#		Get cartesian coordinates for point_0
#		x2, y2, and z2 are all points after point_0
		x1, y1, z1 = cartesianCoordinatesDF[pointIndex_0, CARTESIANX_NP_COL], cartesianCoordinatesDF[pointIndex_0, CARTESIANY_NP_COL], cartesianCoordinatesDF[pointIndex_0, CARTESIANZ_NP_COL]
		x2, y2, z2 = cartesianCoordinatesDF[pointIndex_0:, CARTESIANX_NP_COL], cartesianCoordinatesDF[pointIndex_0:, CARTESIANY_NP_COL], cartesianCoordinatesDF[pointIndex_0:, CARTESIANZ_NP_COL]
#		Calculate the distance
		calcDist_NP = distanceCalculator(x1, x2, y1, y2, z1, z2)
#		Convert calcDist to a series
		calcDist_Series = pd.Series(calcDist_NP)
#		Find points within the search radius
#		print (cartesianCoordinatesDF)
		searchRadius = 1
		prospectivePoint_1 = getProspectivePoint_1(calcDist_Series, searchRadius)
#		Check if prospectivePoint_1 is empty
		noProspectivePoint_1 = len(prospectivePoint_1) == 0
#		If no prospective points are found, increase searchRadius until one is found
		if (noProspectivePoint_1):
			while (noProspectivePoint_1):
				searchRadius += 1
				prospectivePoint_1 = getProspectivePoint_1(calcDist_Series, searchRadius)
				pointIndex_1 = filterProspectivePoint_1(jpDF, prospectivePoint_1, pointIndex_0)
				noProspectivePoint_1 = len(prospectivePoint_1) == 0 or pointIndex_1 == NOPOINTFOUND

#		If there are prospective jump points
		if (not noProspectivePoint_1):
#			printStatus("prospectivePoint_1", prospectivePoint_1)
			printStatus("prospectivePoint_1.index", prospectivePoint_1.index)
#			If no valid point is found
			if (pointIndex_1 == NOPOINTFOUND):
				searchRadius += 1
				if (pointIndex_0 != 0):
					pointIndex_0 -= 1
				continue
			else:
				printStatus("pointIndex_1", pointIndex_1)
				point_1_uniqueID = jpDF.at[pointIndex_1, "uniqueID"]
#				printStatus("")
				distanceBetweenPoints = calcDist_Series[pointIndex_1]
#				printStatus("distanceBetweenPoints", distanceBetweenPoints)
				jpDF = assignPointData(jpDF, pointIndex_0, pointIndex_1, distanceBetweenPoints)
				print("\n")
#		checkConnectingJumpPointForNan(prospectivePoint_1, jpDF["connectingJumpPoint"])
		pointIndex_0 += 1
		if (pointIndex_0 == MAXPOINTINDEX):
			break

	jpDF.to_csv("/media/MAGI_II/Projects/Worldbuilder/output/jumpPoint_t_db_out.csv", index = True)


def OLD_jumpPointConnector():
#	Read in jumpPoint_t_db.csv
	jpDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/output/jumpPoint_t_db.csv", encoding = "cp1252", dtype = {"uniqueID" : object})
#	Get the id numbers for each jump point
	jpIDNumbers = jpDF["uniqueID"].astype(str)
#	Get the star numbers for each jump point
#	print (jpIDNumbers[0])
#	starIdNumbers = np.zeros(len(jpIDNumbers), dtype = np.int32)
	starIdNumbers = jpIDNumbers.str.slice(0, 5)#.astype(np.int32)

#	Turn the coordinate columns into a new dataframe
	cartesianCoordinatesDF = jpDF[jpDF.columns[6:9]]
#	cartesianCoordinatesDF = jpDF.columns[6:9]
#	Convert the df into an np array
	cartesianCoordinatesDF = cartesianCoordinatesDF.values
#	Loop through cartesianCoordinatesDF
#	Index for the current point
	jpDF[["connectingJumpPoint"]] = np.nan
	pointIndex = 0
	MAXPOINTINDEX = 512#len(jpIDNumbers)
#	print (MAXPOINTINDEX / 2)
	for point in cartesianCoordinatesDF:
#		Print the unique ID's for all the jump points that share this point's starID
		print (jpDF.iat[pointIndex, 0])
		print (f"pointIndex == {pointIndex}")
		pointUniqueID = jpIDNumbers.iat[pointIndex]
		print (f"pointUniqueID == {pointUniqueID}")
		pointUniqueID_lastDigit = int(pointUniqueID) % 10
		print (f"pointUniqueID_lastDigit == {pointUniqueID_lastDigit}")
		pointStarID = starIdNumbers.iat[pointIndex]
		print (f"pointStarID == {pointStarID}")
#		Select the unique ID's of the points with the same star ID as the current Point
		sameStarJumpPoints = jpDF["uniqueID"].loc[jpDF["uniqueID"].str.startswith(str(pointStarID))]
#		Select the unique ID's of the points with the same starID as the current
#		Point, but not Point
		sameStarJumpPoints = sameStarJumpPoints.loc[sameStarJumpPoints != pointUniqueID]
#		If point's value for connectingJumpPoint is equal to np.nan and the pointIndex is not 1
		if (not np.isnan(jpDF.at[pointIndex, "connectingJumpPoint"]) and pointIndex != 1):
#			print (jpDF.at[pointIndex, "connectingJumpPoint"])
			pointIndex += 1
			continue
#		Roll 1d4 for the initial search radius
		originalSearchR = randint(1, 4)
		x1, y1, z1 = jpDF.at[pointIndex, "cartesianX"], jpDF.at[pointIndex, "cartesianY"], jpDF.at[pointIndex, "cartesianZ"]
		x2, y2, z2 = jpDF.loc[pointIndex:, "cartesianX"], jpDF.loc[pointIndex:, "cartesianY"], jpDF.loc[pointIndex:, "cartesianZ"]
#		Finish distance calculation
		calcDist = distanceCalculator(x1, x2, y1, y2, z1, z2)
#		Convert to pandas series
		calcDistSeries = pd.Series(calcDist)
#		Search radii
		searchR1 = originalSearchR - 1
		searchR2 = originalSearchR
#		Initially, decrement
		searchIncrementer = -1
#		Used to break out of the while loop
		matchFound = False
		while (not matchFound):
#			Find the values where the conditions are met
			result = calcDistSeries.loc[(calcDistSeries < searchR2) & (calcDistSeries > searchR1)]
			resultLength = len(result)
	#		emptyConnectionCond = jpDF.at[result.index[0], "connectingJumpPoint"] == np.nan
			if (searchR1 == -1):
				searchIncrementer = 1
				searchR1 = originalSearchR
				searchR2 = originalSearchR + 1

#			If no points are found, expand the search radius
			if (checkSeriesLength(result, 0)):
#				print ("Nothing found within radii")
				searchR1 += searchIncrementer
				searchR2 += searchIncrementer

#			If the jump point ids match
			elif (jpDF.at[result.index[0], "connectingJumpPoint"] == jpDF.iat[pointIndex, 0]):
#				print (f"jpDF.iat[result.index[0], 1]" == {jpDF.iat[result.index[0], 1]})
#				print (f"jpDF.iat[pointIndex, 0] == {jpDF.iat[pointIndex, 0]}")
#				print ("Nothing found within radii")
				searchR1 += searchIncrementer
				searchR2 += searchIncrementer

#			If the distance to the found point is the same as the last iterated point
			elif (pointIndex != 0 and result.iat[0] == jpDF.at[pointIndex - 1, "distanceToConnectingPoint"]):
#				print ("Current distance matches previous")
				searchR1 += searchIncrementer
				searchR2 += searchIncrementer

#			If a point is found
			else:
				print ("A point has been found")
				resultIndex = 0
				distanceBetweenPoints = result.iat[resultIndex]
				print (f"distanceBetweenPoints == {distanceBetweenPoints}")
#				If there are multiple jump points in Point's system
				sameStarJumpPoints_index_length = len(sameStarJumpPoints.index)
				print (f"sameStarJumpPoints_index_length == {sameStarJumpPoints_index_length}")
				if (len(sameStarJumpPoints.index) > 1):
#					Create an np array to hold the distances at each jump point
					sameStarJumpPoint_distance_series = np.zeros(len(sameStarJumpPoints.index))
					sameStarJumpPoint_index = 0
#					For each point in the series sameStarJumpPoints, retrieve the index
					for sameStarJumpPoint in sameStarJumpPoints.index:
						sameStarJumpPoint_distance = jpDF.at[sameStarJumpPoint, "distanceToConnectingPoint"]
						sameStarJumpPoint_distance_series[sameStarJumpPoint_index] = sameStarJumpPoint_distance
						sameStarJumpPoint_index += 1
					print (f"sameStarJumpPoint_distance_series == {sameStarJumpPoint_distance_series}")
#					If any previous jump point in the system matches distanceBetweenPoints. return True
					distanceBetweenPointsMatchesSeries = np.where(sameStarJumpPoint_distance_series[sameStarJumpPoint_distance_series == distanceBetweenPoints], True, False)
					distanceBetweenPointsMatchesSeries_all_nan = np.all(np.where(np.isnan(sameStarJumpPoint_distance_series), True, False))
					print (f"distanceBetweenPointsMatchesSeries_all_nan == {distanceBetweenPointsMatchesSeries_all_nan}")
					distanceBetweenPointsMatchesSeries = np.any(distanceBetweenPointsMatchesSeries) and (not distanceBetweenPointsMatchesSeries_all_nan)
#					If there are multiple jump points in the prospective system, go through them and make sure that
#					While distanceBetweenPoints still matches any point in sameStarJumpPoint_distance_series
					if (distanceBetweenPointsMatchesSeries):
						print (f"distanceBetweenPointsMatchesSeries == True")
						while (distanceBetweenPointsMatchesSeries):
	#						If the length of result is greater than 1
							if (resultLength > 1):
								print ("Result length is greater than 1")
	#							Increment resultIndex
								resultIndex += 1

	#							Ensure that resultIndex is within bounds
								if (resultIndex < resultLength):
									print ("resultIndex is less than resultLength")
	#								Get distanceBetweenPoints for the prospective connecting point
									distanceBetweenPoints = result.iat[resultIndex]
	#								Check distanceBetweenPointsMatchesSeries again
									distanceBetweenPointsMatchesSeries = np.where(sameStarJumpPoint_distance_series[sameStarJumpPoint_distance_series == distanceBetweenPoints], True, False)
									distanceBetweenPointsMatchesSeries = np.any(distanceBetweenPointsMatchesSeries)
									if (not distanceBetweenPointsMatchesSeries):
		#								Assign data
										jpDF = assignPointData(jpDF, result, pointUniqueID, distanceBetweenPoints, pointIndex)
										matchFound = True
										if (matchFound):
											break
	#							If resultIndex is out of bounds
								else:
									print ("resultIndex is out of bounds")
									searchR1 += searchIncrementer
									searchR2 += searchIncrementer
									break

#							If resultIndex is out of bounds
							else:
								print ("resultIndex is out of bounds")
								searchR1 += searchIncrementer
								searchR2 += searchIncrementer
								break
					else:
						jpDF = assignPointData(jpDF, result, pointUniqueID, distanceBetweenPoints, pointIndex)
						matchFound = True
						if (matchFound):
							break

				else:
					jpDF = assignPointData(jpDF, result, pointUniqueID, distanceBetweenPoints, pointIndex)
					matchFound = True
					if (matchFound):
						break

		pointIndex += 1
		print (f"pointIndex == {pointIndex}\n")
		if (pointIndex >= MAXPOINTINDEX - 2):
			break
#	jpDF.to_csv("/media/MAGI_II/Projects/Worldbuilder/output/jumpPoint_t_db.csv", index = True)

def old():
#	Turn row i in jpDB into a slice of the numpy array that jpDB has been turned into
	indexValue = 0
	for i in jpDB.values:
		print (i[0])
#		Make sure that the jump point is unconnected
		if (np.isnan(i[1])):
#			print ("i[0] is nan")
#			indexValue += 1
			rowsChecked = 0
#			if (indexValue == 10):
#				break
#		Iterate through jpDB
#		Turn row j in jpDB into a slice of the numpy array that jpDB has been turned into
			searchRadius = 1
			matchFound = False
			while (not matchFound and searchRadius < 12):
				for j in jpDB.values:
	#				print (j[0])
	#				print("Entered j loop")
	#				If an available jump point is found
#					xDistance = oneDDistanceCalculator(i[6], j[6])
#					yDistance = oneDDistanceCalculator(i[7], j[7])
#					zDistance = oneDDistanceCalculator(i[8], j[8])
					if ((np.isnan(j[1]) and (i[0] != j[0]))):
	#					print ("j is nan")
	#					Get distance between points
	#					print(f'i[0] == {i[0]}	j[0] == {j[0]}')
						distanceBetweenPoints = distanceCalculator(j[6], i[6], j[7], i[7], j[8], i[8])
	#					print(f'x1 == {i[6]}	x2 == {j[6]}')
	#					print(f'distanceBetweenPoints == {distanceBetweenPoints}')
						rowsChecked += 1
	#						If the
						if (distanceBetweenPoints <= searchRadius and distanceBetweenPoints > 0):
							i[1], j[1] = j[0], i[0]
							i[13], j[13] = distanceBetweenPoints, distanceBetweenPoints
							print(f'rowsChecked == {rowsChecked}')
							matchFound = True
							break
				searchRadius += 1
		else:
			continue


#	jpDB.to_csv("/media/MAGI_II/Projects/Worldbuilder/output/jumpPoint_t_db.csv", index = True)



jumpPointConnector()
#ax = 10.3742
#ay = 0.030419
#az = -28.0091
#bx = 30.207
#by = 0.105644
#bz = 9.22846
#start_time = time.time()
#distanceCalculator(bx, ax, by, ay, bz, az)
#print("--- %s seconds ---" % (time.time() - start_time))

#jpDB = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/output/jumpPoint_t_db.csv", encoding = "cp1252", dtype = {"uniqueID" : object})
#print(jpDB)
