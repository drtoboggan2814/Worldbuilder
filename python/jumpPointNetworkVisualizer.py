import networkx as nx
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

jpDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/jpDF_out_max_8_3pc.csv", dtype = {"uniqueID":object, "starID":object, "connectingPointID":object, "connectingStarID":object})
colorsDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/python/colors.csv")
#	jpDF = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/jpDF_out_max_8_3pc.csv", dtype = {"uniqueID":object, "starID":object, "connectingPointID":object, "connectingStarID":object, "starSystemID":object})
colorsDict = dict(zip(colorsDF["colorIndex"], colorsDF["rgbValue"]))
nodeList = jpDF[["starID", "cartesianX", "cartesianY", "cartesianZ"]].drop_duplicates()
nodeList["colorValue"] = np.nan
nodeList["roundedZ"] = nodeList["cartesianZ"].round(0)
for key in colorsDict:
	nodeList["colorValue"].loc[nodeList["roundedZ"] == int(key)] = colorsDict[key]

nodePositions = nodeList.rename(columns = {"cartesianX":"x", "cartesianY":"y"})
nodePositions = dict(zip(nodeList["starID"], zip(nodePositions["x"], nodePositions["y"])))
nodePositions_3D = nodeList.rename(columns = {"cartesianX":"x", "cartesianY":"y", "cartesianZ":"z"})
nodePositions_3D = dict(zip(nodeList["starID"], zip(nodePositions_3D["x"], nodePositions_3D["y"], nodePositions_3D["z"])))
#	nodeList = nodeList.set_index("starID")
#	nodePositions = nodeList[["cartesianX", "cartesianY"]]
#	nodePositionsDict = dict(zip(nodeList["starID"], [nodePositions.index["x"], nodePositions["y"]]))
#	print(nodeList)
g = nx.from_pandas_edgelist(jpDF, "starID", "connectingStarID", edge_attr="distanceToConnectingPoint")

#	print (nodeList)
#	nx.set_node_attributes(g, nodeList)
#	print(g.nodes(data = True))
#	print (nodePositions)
plt.figure()
nx.draw(g, pos = nodePositions, node_size=20, node_color=nodeList["colorValue"].tolist())
plt.show()
