import numpy as np
import pandas as pd
import re

def printStatus(string, variable):
	print (f"{string} == {variable}")

def main():
#	Load in .csv's
#	starSystemDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/starSystem_t_db.csv", dtype = {"uniqueID":object})
#	starDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/star_t_db_final.csv", dtype = {"uniqueID":object})
#	worldDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/world_t_db_final.csv", dtype = {"uniqueID":object})
#	moonDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/moon_t_db.csv", dtype = {"uniqueID":object})
#	jpDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/jpDF_out_max_8_3pc.csv", dtype = {"uniqueID":object, "starID":object, "connectingPointID":object, "connectingStarID":object})

	starSystemDF = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/starSystem_t_db.csv", dtype = {"uniqueID":object})
	starDF = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/star_t_db_final.csv", dtype = {"uniqueID":object, "starSystemID":object})
	worldDF = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/world_t_db_final.csv", dtype = {"uniqueID":object, "starID":object, "starSystemID":object})
#	moonDF = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/moon_t_db.csv", dtype = {"uniqueID":object})
#	jpDF = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/jpDF_out_max_8_3pc.csv", dtype = {"uniqueID":object, "starID":object, "connectingPointID":object, "connectingStarID":object, "starSystemID":object})


#	Loop through starSystemDF
	starSystemIndex = 0
	starIndex = 0
	worldIndex = 0
	moonIndex = 0
	jumpPointIndex = 0
	for starSystem in starSystemDF.values:
#		printStatus("starSystemIndex", starSystemIndex)
#		Star system level
		starSystemID = starSystem[starSystemDF.columns.get_loc("uniqueID")]
#		printStatus("starSystemID", starSystemID)
#		starSystemID_Trunc = re.sub(starSystemID[4:], '', starSystemID)
		starSystemID_Trunc = starSystemID[:4]
#		printStatus("starSystemID_Trunc", starSystemID_Trunc)
		starArray = starDF.loc[starDF["uniqueID"].str.startswith(starSystemID_Trunc)]
#		printStatus("starArray", starArray)
#		loop through stars
		for star in starArray.values:
#			printStatus("starIndex", starIndex)
			starID = star[starDF.columns.get_loc("uniqueID")]
			printStatus("starID", starID)
#			starID_Trunc = re.sub(starID[5:], '', starID)
			starID_Trunc = starID[:5]
#			printStatus("starID_Trunc", starID_Trunc)
#			Assgin starSystemID
			starDF.at[starIndex, "starSystemID"] = starSystemID
#			printStatus("starSystemID", starSystemID)
#			printStatus('starDF.at[starIndex, "starSystemID"]', str(starDF.at[starIndex, "starSystemID"]))
#			Get worlds
			worldArray = worldDF.loc[worldDF["uniqueID"].str.startswith(starID_Trunc)]
#			Loop through worlds

			for world in worldArray.values:
#				printStatus("worldIndex", worldIndex)
				worldID = world[worldDF.columns.get_loc("uniqueID")]
#				printStatus("worldID", worldID)
#				printStatus("worldID[6:]", worldID[:6])
#				printStatus("worldID[7:]", worldID[:7])
#				worldID_Trunc = re.sub(worldID[7:], '', worldID)
				worldID_Trunc = worldID[:7]
#				printStatus("worldID_Trunc", worldID_Trunc)
				worldDF.at[worldIndex, "starSystemID"] = starSystemID#.values[0][-2]
				worldDF.at[worldIndex, "starID"] = starID#.values[0][-2]
#				printStatus("starID[:4]", starID[:4])
#				worldDF.at[worldIndex, "uniqueID"] = starID[:4] + worldID[-5:]
#				Get moons
#				moonArray = moonDF.loc[moonDF["uniqueID"].str.startswith(worldID_Trunc)]
#				Loop through moons
#				for moon in moonArray.values:
#					printStatus("moonIndex", moonIndex)
#					moonDF.at[moonIndex, "starSystemID"] = starSystemID
#					moonDF.at[moonIndex, "starID"] = starID
#					moonDF.at[moonIndex, "worldID"] = worldID
#					moonIndex += 1
				worldIndex += 1

#			Get jump points
#			jumpPointArray = jpDF.loc[jpDF["uniqueID"].str.startswith(starID_Trunc)]
#			printStatus("starSystemID", starSystemID)
#			for jumpPoint in jumpPointArray.values:
#				printStatus("starSystemID", starSystemID)
#				jpDF.at[jumpPointIndex, "starSystemID"] = starSystemID
#				jumpPointIndex += 1
			starIndex += 1
		starSystemIndex += 1
#	starSystemDF.to_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/starSystem_t_db.csv", index = False)
#	starDF.to_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/star_t_db_final.csv", index = False)
#	worldDF.to_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/world_t_db_final.csv", index = False)
#	moonDF.to_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/moon_t_db.csv", index = False)
#	jpDF.to_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/jpDF_out_max_8_3pc.csv", index = False)

#	starSystemDF.to_csv("Z:/Projects/Worldbuilder/finalOutput/starSystem_t_db.csv", index = False)
#	starDF.to_csv("Z:/Projects/Worldbuilder/finalOutput/star_t_db_final.csv", index = False)
	worldDF.to_csv("Z:/Projects/Worldbuilder/finalOutput/world_t_db_final.csv", index = False)
#	moonDF.to_csv("Z:/Projects/Worldbuilder/finalOutput/moon_t_db.csv", index = False)
#	jpDF.to_csv("Z:/Projects/Worldbuilder/finalOutput/jpDF_out_max_8_3pc.csv", index = False)

main()
