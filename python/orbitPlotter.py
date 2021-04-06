import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import re

#	Calculate the orbit's ellipse
def getEllipse(sMA, ecc):
	theta = np.linspace(0, 2 * np.pi, 360)
	r = (sMA * (1 - ecc**2)) / (1 + ecc * np.cos(theta))
	return r


def main():
	theta = np.linspace(0, 2 * np.pi, 360)
#	Read in .csv's
	starDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/star_t_db_final.csv", dtype = {"uniqueID":object})
	worldDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/world_t_db_final.csv", dtype = {"uniqueID":object})
	jpDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/jpDF_out_max_8_3pc.csv", dtype = {"uniqueID":object, "starID":object, "connectingPointID":object, "connectingStarID":object})

#	Iterate through starDF
	starIndex = 0
	csv_worldIndex = 0
	csv_jpIndex = 0
	for star in starDF.values:
#		Create plot
		fig = plt.figure()
		ax = fig.add_subplot(projection="polar", facecolor="lightgoldenrodyellow")
#		Get starID
		starID = star[starDF.columns.get_loc("uniqueID")]
#		Truncate starID for matching
		starID_Trunc = re.sub(starID[5:], '', starID)
#		Get number of worlds and jump points
		numberOfWorlds = star[starDF.columns.get_loc("numberOfPlanets")]
		numberOfJumpPoints = star[starDF.columns.get_loc("numberOfJumpPoints")]

#		Get worlds
		worldArray = worldDF.loc[worldDF["uniqueID"].str.startswith(starID_Trunc)]
#		Get semi major axes
		smaArray = worldArray["orbitalRadius"]
#		Get eccentricity values
		eccArray = worldArray["orbitalEccentricity"]
#		Get planet names
		nameArray = worldArray["planetName"]
#		Get world orbits
		for sma, ecc, name in zip(smaArray[-6:], eccArray[-6:], nameArray[-6:]):
			ellipse = getEllipse(sma, ecc)
			ax.plot(theta, ellipse, label = name)
		ax.tick_params(grid_color="palegoldenrod")
#		Get jump points
		jpArray = jpDF.loc[jpDF["uniqueID"].str.startswith(starID_Trunc)]
#		Get jump point locations
		locationArray = jpArray["distanceToPrimary"]
		arcArray = jpArray["arc"]
#		Get jump point positions
		for location, arc in zip(locationArray, arcArray):
			thetaPoint = (arc / (180 * np.pi))
#			ax.scatter(arc, location, c = 'r')

		starIndex += 1
		if (starIndex == 1):
			break
	ax.legend(loc = "lower left")
#	ax.set_rscale('log')
	plt.show()



main()
