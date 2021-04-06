import numpy as np
import pandas as pd
from scipy.spatial import Voronoi, voronoi_plot_2d, Delaunay
import matplotlib.pyplot as plt
import matplotlib.path as path
import matplotlib as mpl
from math import sqrt
from mpl_toolkits.mplot3d import Axes3D
import re

def printStatus(string, variable):
	print (f"{string} == {variable}")

def findNeighbors(pointIndex, triangle):
	neighbors = list()
	for simplex in triangle.simplices:
		if pointIndex in simplex:
			neighbors.extend([simplex[i] for i in range(len(simplex)) if simplex[i] != pointIndex])
	return list(set(neighbors))

#	Read in starDF
starDF = pd.read_csv("star_t_db - Copy.csv", dtype = {"uniqueID":object}, usecols = ["uniqueID", "cartesianX", "cartesianY", "cartesianZ"])

#	Create neighbors_array
neighbors_array = np.zeros((len(starDF), 32), dtype = object)
neighbors_array[:] = np.NaN

#	Cartesian coordinates
xCoord, yCoord, zCoord = starDF["cartesianX"], starDF["cartesianY"], starDF["cartesianZ"]
points = np.zeros((len(xCoord), 3))
points[:, 0] = xCoord
points[:, 1] = yCoord
points[:, 2] = zCoord

#	Calculate Delaunay triangulation
tri = Delaunay(points)
starIndex = 0

for star in starDF.values:
	printStatus("starIndex", starIndex)
	neighbors = findNeighbors(starIndex, tri)
	neighbors_padded = np.zeros(32)
	neighbors_padded[:] = np.NaN
	neighbors_padded[:len(neighbors)] = neighbors
#	printStatus("neighbors_padded", neighbors_padded)
	neighbors_array[starIndex] = neighbors_padded
#	printStatus("neighbors_array", neighbors_array)
	starIndex += 1
#	if (starIndex == 2):
#		break

neighborsDF = pd.DataFrame(neighbors_array)
printStatus('neighborsDF', neighborsDF)
neighborsDF.to_csv("neighbors_out.csv", index = False, index_label = False, na_rep = "NULL")
