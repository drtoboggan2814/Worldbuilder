from collections import deque
import json
from math import sqrt, cos, pi
import numpy as np
import pandas as pd
import time

def printStatus(string, variable):
	print (f"{string} == {variable}")

def distanceCalculator(x1, x2, y1, y2, z1, z2):
	distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2))
	return distance

def checkStarIdentifiers(starDF, input):
	if (input[3:] != ""):
		hdInput = input[3:] + ".0"
	else:
		hdInput = input

	if (input[4:] != ""):
		hipInput = input[4:] + ".0"
		hygInput = input[4:] + ".0"
	else:
		hipInput = hygInput = input

	uniqueID	= starDF[starDF["uniqueID"] == input]["uniqueID"]

	properName 	= starDF[starDF["properName"] == input]["properName"]

	hygID		= starDF[starDF["hygIndex"] == hygInput]["hygIndex"]

	hipID		= starDF[starDF["hipIndex"] == hipInput]["hipIndex"]

	hdID 		= starDF[starDF["hdIndex"] == hdInput]["hdIndex"]

	glieseID 	= starDF[starDF["glieseIndex"] == input]["glieseIndex"]

	bayerID 	= starDF[starDF["bayerDesignation"] == input]["bayerDesignation"]

	flamsteedID = starDF[starDF["flamsteedDesignation"] == input]["flamsteedDesignation"]

	return uniqueID, properName, hygID, hipID, hdID, glieseID, bayerID, flamsteedID

def getStarName(starDF, uniqueID):
#	printStatus("uniqueID", uniqueID)
	properName 	= starDF[starDF["uniqueID"] == uniqueID]["properName"]
#	printStatus("properName", properName)
	hygID		= starDF[starDF["uniqueID"] == uniqueID]["hygIndex"]
#	printStatus("hygID", hygID)
	hipID		= starDF[starDF["uniqueID"] == uniqueID]["hipIndex"]
#	printStatus("hipID", hipID)
	hdID 		= starDF[starDF["uniqueID"] == uniqueID]["hdIndex"]
#	printStatus("hdID", hdID)
	glieseID 	= starDF[starDF["uniqueID"] == uniqueID]["glieseIndex"]
#	printStatus("glieseID", glieseID)
	bayerID 	= starDF[starDF["uniqueID"] == uniqueID]["bayerDesignation"]
#	printStatus("bayerID", bayerID)
	flamsteedID = starDF[starDF["uniqueID"] == uniqueID]["flamsteedDesignation"]
#	printStatus("flamsteedID", flamsteedID)

	if (len(properName.values) > 0 and ~properName.isnull().values.any()):
		return properName.values[0]
	elif (len(bayerID.values) > 0 and ~bayerID.isnull().values.any()):
		return bayerID.values[0]
	elif (len(glieseID.values) > 0 and ~glieseID.isnull().values.any()):
		return glieseID.values[0]
	elif (len(flamsteedID.values) > 0 and ~flamsteedID.isnull().values.any()):
		return flamsteedID.values[0]
	elif (len(hdID.values) > 0 and ~hdID.isnull().values.any() and np.all((hdID.values == 0))):
#		if (hdID.values[0][:-2] > 0):
		return "HD " + hdID.values[0][:-2]
	elif (len(hipID.values) > 0 and ~hipID.isnull().values.any() and ~np.all((hipID.values == 0))):
#		if (int(hipID.values[0][:-2]) > 0):
		return "HIP " + hipID.values[0][:-2]
	elif (len(hygID.values) > 0 and ~hygID.isnull().values.any()):
#		if (int(hygID.values[0][:-2]) > 0):
		return "HYG " + hygID.values[0][:-2]
	else:
		return uniqueID

def getStarUniqueID(starDF, input):
#	printStatus("flamsteedID", flamsteedID)
	uniqueID, properName, hygID, hipID, hdID, glieseID, bayerID, flamsteedID = checkStarIdentifiers(starDF, input)

	if (input[3:] != ""):
		hdInput = input[3:] + ".0"
	else:
		hdInput = input

	if (input[4:] != ""):
		hipInput = input[4:] + ".0"
		hygInput = input[4:] + ".0"
	else:
		hipInput = hygInput = input

	if (uniqueID.any() == input):
		result = starDF[starDF["uniqueID"] == input]["uniqueID"]
		return result.values[0]
	elif (properName.any() == input):
		result = starDF[starDF["properName"] == input]["uniqueID"]
		return result.values[0]
	elif (hygID.any() == hygInput):
		result = starDF[starDF["hygIndex"] == hygInput]["uniqueID"]
		return result.values[0]
	elif (hipID.any() == hipInput):
		result = starDF[starDF["hipIndex"] == hipInput]["uniqueID"]
		return result.values[0]
	elif (hdID.any() == hdInput):
		result = starDF[starDF["hdIndex"] == hdInput]["uniqueID"]
		return result.values[0]
	elif (glieseID.any() == input):
		result = starDF[starDF["glieseIndex"] == input]["uniqueID"]
		return result.values[0]
	elif (bayerID.any() == input):
		result = starDF[starDF["bayerDesignation"] == input]["uniqueID"]
		return result.values[0]
	elif (flamsteedID.any() == input):
		result = starDF[starDF["flamsteedDesignation"] == input]["uniqueID"]
		return result.values[0]
	else:
		print("No match found")

def buildAdjacencyDictionary(starDF, jpDF):
#	Declare adjacency dictionary
	adjacencyDict = {}
#	Loop through starDF
	for star in starDF.values:
#		Get unique ID
		starUniqueID = star[starDF.columns.get_loc("uniqueID")]

#		Get series of all adjacent stars
		adjacencySeries_Destination = jpDF.loc[jpDF["connectingStarID"] == starUniqueID]["starID"].values

#		Fill adjacency dictionary
		adjacencyDict[starUniqueID] = adjacencySeries_Destination.tolist()

	return adjacencyDict

def getPolarDistance(r1, r2, arc1, arc2):
	return sqrt(pow(r1, 2) + pow(r2, 2) - (2 * r1 * r2 * cos(arc2 - arc1)))

def getApparentDistanceTraveled(jpDF, pointList):
	lastPoint = pointList[-1]
	distanceTraveled = 0
	maxVal = len(pointList) - 2
	if (len(pointList) > 2):
		for i in range(1, maxVal, 2):
			r1, r2 = jpDF.loc[jpDF["uniqueID"] == pointList[i], "distanceToPrimary"].values[0], jpDF.loc[jpDF["uniqueID"] == pointList[i + 1], "distanceToPrimary"].values[0]
			arc1, arc2 = jpDF.loc[jpDF["uniqueID"] == pointList[i], "arc"].values[0], jpDF.loc[jpDF["uniqueID"] == pointList[i + 1], "arc"].values[0]
#			printStatus("arc1", arc1)
			distanceTraveled = getPolarDistance(r1, r2, arc1, arc2) + distanceTraveled
#			printStatus("getPolarDistance(r1, r2, arc1, arc2)", getPolarDistance(r1, r2, arc1, arc2))
#	printStatus("distanceTraveled (au)", distanceTraveled)
	return distanceTraveled

def getStellarDistanceTraveled(starDF, shortestPath):
#	printStatus("shortestPath", shortestPath)
	lastStar = shortestPath[-1]
	distanceTraveled = 0
	for i in range(0, len(shortestPath) - 1, 1):
		x1, y1, z1 = starDF.loc[starDF["uniqueID"] == shortestPath[i], "cartesianX"].values[0], starDF.loc[starDF["uniqueID"] == shortestPath[i], "cartesianY"].values[0], starDF.loc[starDF["uniqueID"] == shortestPath[i], "cartesianZ"].values[0]
		x2, y2, z2 = starDF.loc[starDF["uniqueID"] == shortestPath[i + 1], "cartesianX"].values[0], starDF.loc[starDF["uniqueID"] == shortestPath[i + 1], "cartesianY"].values[0], starDF.loc[starDF["uniqueID"] == shortestPath[i + 1], "cartesianZ"].values[0]
		distanceTraveled = distanceTraveled + distanceCalculator(x1, x2, y1, y2, z1, z2)
#	printStatus("distanceTraveled (pc)", distanceTraveled)
	return distanceTraveled

def getJumpPointsUsed(starDF, jpDF, shortestPath):
	pointList = []
	firstPoint = jpDF.loc[(jpDF["starID"] == shortestPath[0]) & (jpDF["connectingStarID"] == shortestPath[1]), "uniqueID"].values[0]
	pointList.append(firstPoint)
	lastPoint = jpDF.loc[(jpDF["starID"] == shortestPath[-1]) & (jpDF["connectingStarID"] == shortestPath[-2]), "uniqueID"].values[0]
	for i in range(1, len(shortestPath) - 2):
		point0 = jpDF.loc[(jpDF["starID"] == shortestPath[i]) & (jpDF["connectingStarID"] == shortestPath[i - 1]), "uniqueID"].values[0]
		point1 = jpDF.loc[(jpDF["starID"] == shortestPath[i]) & (jpDF["connectingStarID"] == shortestPath[i + 1]), "uniqueID"].values[0]
		pointList.append(point0)
		pointList.append(point1)
	pointList.append(lastPoint)
#	printStatus("pointList", pointList)
	return pointList

#	From
#	https://pythoninwonderland.wordpress.com/2017/03/18/how-to-implement-breadth-first-search-in-python/
def bfsShortestPath(graph, origin, destination):
#	Track explored nodes
	explored = []
#	Track paths to be checked
	queue = [[origin]]
#	Check if origin == destination
	if (origin == destination):
		return "Origin == destination"

#	Loop through queue until all possible paths have been checked
	while queue:
#		Pop the first path from the queue
		path = queue.pop(0)
#		path = deque(queue[0])
#		Get the last node from the path
		node = path[-1]
#		If the current node is unexplored
		if node not in explored:
			neighbors = graph[node]
#			Go through all neighbor nodes, construct a new path and push it into the queue
			for neighbor in neighbors:
				newPath = list(path)
				newPath.append(neighbor)
				queue.append(newPath)
#				Return path if neighbor is destination
				if (neighbor == destination):
					return newPath
#				Mark node as explored
				explored.append(node)
	return "No path found"

def getTransitTime(acc, accTime, distance):
	return ((distance - (acc * pow(accTime, 2))) / (acc * accTime)) + (2 * accTime)

def main():
#	Load starDF
	time_starDF = time.time()
	starDF = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/star_t_db_final.csv", dtype = {"uniqueID":object, "properName":object, "hygIndex":object, "hipIndex":object, "hdIndex":object, "glieseIndex":object, "bayerDesignation":object, "flamsteedDesignation":object})
#	printStatus("starDF time", (time.time() - time_starDF))
#	starDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/star_t_db_final.csv", dtype = {"uniqueID":object, "properName":object, "hygIndex":object, "hipIndex":object, "hdIndex":object, "glieseIndex":object, "bayerDesignation":object, "flamsteedDesignation":object})
#	Load jpDF
	time_jpDF = time.time()
	jpDF = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/jpDF_out_max_8_3pc.csv", dtype = {"uniqueID":object, "starID":object, "connectingPointID":object, "connectingStarID":object})
#	printStatus("jpDF time", (time.time() - time_jpDF))
#	jpDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/jpDF_out_max_8_3pc.csv", dtype = {"uniqueID":object, "starID":object, "connectingPointID":object, "connectingStarID":object})
#	Load adjacencyDict
	time_adjacencyDict = time.time()
	with open("Z:/Projects/Worldbuilder/finalOutput/adjacencyDict.json", "r") as f:
#	with open("/media/MAGI_II/Projects/Worldbuilder/finalOutput/adjacencyDict.json", "r") as f:
		adjacencyDict = json.load(f)
#	printStatus("adjacencyDict time", (time.time() - time_adjacencyDict))
#	Input star name

	startUniqueID = getStarUniqueID(starDF, "Sol")
	destUniqueID = getStarUniqueID(starDF, "NN 3870")
#	adjacencyDict = buildAdjacencyDictionary(starDF, jpDF)
	time_shortestPath = time.time()
	shortestPath = bfsShortestPath(adjacencyDict, startUniqueID, destUniqueID)

	astU = 149597870700
	acceleration = 2.048
	accTime = 86400 * 7
	dV = acceleration * accTime * 2

#	printStatus("shortestPath time", (time.time() - time_shortestPath))
#	printStatus("shortestPath", shortestPath)
#	Display shortest path
	if (shortestPath != "No path found"):
		realDistance = getStellarDistanceTraveled(starDF, shortestPath)
		pointList = getJumpPointsUsed(starDF, jpDF, shortestPath)
		apparentDistance = getApparentDistanceTraveled(jpDF, pointList)
		transitTime = getTransitTime(acceleration, accTime, apparentDistance * astU) / 86400
		numberOfJumps = len(shortestPath) - 1
		printStatus("numberOfJumps", numberOfJumps)
		printStatus("transitTime (d)", transitTime)
		printStatus("dV (km/s)", dV / 1000)
		for index, star in enumerate(shortestPath):
#			print(star)
			shortestPath[index] = getStarName(starDF, star)

	print(shortestPath)
#	printStatus("getStarName(starDF, {shortestPath[0]})", getStarName(starDF, shortestPath[0]))


main()
