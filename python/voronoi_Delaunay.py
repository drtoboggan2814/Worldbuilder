import numpy as np
import pandas as pd
from scipy.spatial import Voronoi, voronoi_plot_2d, Delaunay
import matplotlib.pyplot as plt

starDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/output/star_t_db - Copy.csv", dtype = {"uniqueID":object}, usecols = ["uniqueID", "cartesianX", "cartesianY", "cartesianZ"])

points = np.zeros((len(starDF["cartesianX"]), 2))
points[:, 0] = starDF["cartesianX"]
points[:, 1] = starDF["cartesianY"]
#	points[:, 2] = starDF["cartesianZ"]

vor = Voronoi(points)
tri = Delaunay(points)
fig_V = voronoi_plot_2d(vor)

fig_D_tri = plt.triplot(points[:,0], points[:,1], tri.simplices)
fig_D = plt.plot(points[:,0], points[:,1], 'o')

plt.show()
