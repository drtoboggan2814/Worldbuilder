import numpy as np
import pandas as pd
from scipy.spatial import Voronoi, voronoi_plot_2d, Delaunay
import matplotlib.pyplot as plt
import matplotlib.path as path
import matplotlib as mpl
from math import sqrt
from mpl_toolkits.mplot3d import Axes3D
import re

def assignPointData(jpDF, csvPointIndex, pointUniqueID, starID, connectingStarID, connectingPointID, distanceBetweenPoints, x, y, z):
	jpDF.at[csvPointIndex, "uniqueID"] = pointUniqueID
	jpDF.at[csvPointIndex, "starID"] = starID
	jpDF.at[csvPointIndex, "connectingStarID"] = connectingStarID
	jpDF.at[csvPointIndex, "connectingPointID"] = connectingPointID
	jpDF.at[csvPointIndex, "distanceBetweenPoints"] = distanceBetweenPoints
	jpDF.at[csvPointIndex, "cartesianX"] = x
	jpDF.at[csvPointIndex, "cartesianY"] = y
	jpDF.at[csvPointIndex, "cartesianZ"] = z
	return jpDF

def createUniqueID(pointIndex, starUniqueID):
	pointUniqueID = str(pointIndex).rjust(2, "0")
#	Replace the last two digits in starUniqueID with pointUniqueID
	pointUniqueID = re.sub("..$", pointUniqueID, starUniqueID)
	return pointUniqueID

def distanceCalculator(x1, x2, y1, y2, z1, z2):
	distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2))
	return distance

def printStatus(string, variable):
	print (f"{string} == {variable}")

def findNeighbors(pointIndex, triangle):
	neighbors = list()
	for simplex in triangle.simplices:
		if pointIndex in simplex:
			neighbors.extend([simplex[i] for i in range(len(simplex)) if simplex[i] != pointIndex])
	return list(set(neighbors))


#	np.set_printoptions(threshold=np.inf)
#	Input
starDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/output/star_t_db - Copy.csv", dtype = {"uniqueID":object}, usecols = ["uniqueID", "cartesianX", "cartesianY", "cartesianZ"])
neighborsDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/output/neighbors_out.csv")
#	Output
jpDF_columnNames = ["uniqueID", "starID", "connectingPointID", "connectingStarID", "distanceToConnectingPoint", "cartesianX", "cartesianY", "cartesianZ"]
jpDF = pd.DataFrame(columns = jpDF_columnNames, dtype = object)
jpDF["cartesianX"], jpDF["cartesianY"], jpDF["cartesianZ"] = starDF["cartesianX"], starDF["cartesianY"], starDF["cartesianZ"]
#	print(jpDF.head)
#	Get the cartesian coordinates
xCoord, yCoord, zCoord = starDF["cartesianX"], starDF["cartesianY"], starDF["cartesianZ"]
points = np.zeros((len(xCoord), 3))
points[:, 0] = xCoord
points[:, 1] = yCoord
points[:, 2] = zCoord

#	Calculate Delaunay triangulation
tri = Delaunay(points)
starIndex = 0
csvPointIndex = 0
#	printStatus("starDF", starDF)
for star in starDF.values:
	printStatus("star[0]", star[0])
#	Get starUniqueID
	starUniqueID = star[0]
#	printStatus("starUniqueID", starUniqueID)
#	Get starID
	starID = re.sub(star[0][5:], '', star[0])
#	Get neighbors
	neighbors = neighborsDF.loc[starIndex]
#	Loop through each point in neighbors
	pointIndex = 1
	neighbors = neighbors[~np.isnan(neighbors)].astype(int)

#	Get the star's cartesian coordinates
	x1, y1, z1 = star[1], star[2], star[3]
#	printStatus("neighbors", neighbors)
	for point in neighbors:
		printStatus("point", int(point))
#		If the point has not been placed yet
		if (np.isnan(jpDF.at[csvPointIndex, "uniqueID"]))
	#		Convert pointIndex to a string and add a leading zero if necessary
			pointUniqueID = createUniqueID(pointIndex, starUniqueID)

	#		Get connectingStarID
			connectingStarID = starDF.values[int(neighbors[pointIndex - 1]), 0]
	#		printStatus("connectingStarID", connectingStarID)

	#		Get the neighbors of the prospective point
			pointNeighbors = neighborsDF.loc[int(point)]
			pointNeighbors = pointNeighbors[~np.isnan(pointNeighbors)].astype(int)
	#		printStatus("pointNeighbors", pointNeighbors)

	#		Determine which point connects to point_0
			pointNeighbors_point0Index = np.where(pointNeighbors == starIndex)[0][0]
			connectingPointID = createUniqueID(pointNeighbors_point0Index, connectingStarID)
	#		printStatus("connectingPointID", connectingPointID)

	#		Determine the distance between the points
			x2, y2, z2 = starDF.at[point, "cartesianX"], starDF.at[point, "cartesianY"], starDF.at[point, "cartesianZ"]
			distanceBetweenPoints = distanceCalculator(x1, x2, y1, y2, z1, z2)
			jpDF = assignPointData(jpDF, csvPointIndex, pointUniqueID, starID, connectingStarID, connectingPointID, distanceBetweenPoints, x1, y1, z1)
		pointIndex += 1
		csvPointIndex += 1
	starIndex += 1
	if (starIndex == 1):
		break

jpDF.to_csv("jpDF_out.csv")

#	plt.triplot(points[:,0], points[:,1], tri.simplices)
#	plt.plot(points[:,0], points[:,1], 'o')
#	plt.show()
#	vor = Voronoi(points)
#	fig = voronoi_plot_2d(vor)
#	plt.show()
