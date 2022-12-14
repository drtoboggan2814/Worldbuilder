import numpy as np
import pandas as pd

starDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/out_blanks_filled.csv")
brownDwarfDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/brownDwarfList.csv")

starDF = starDF.round({"x":4, "y":4, "z":4})
brownDwarfDF = brownDwarfDF.round({"x":4, "y":4, "z":4})

starDFIndex = 0
for star in starDF.values:
	matchingBrownDwarf = brownDwarfDF.loc[(brownDwarfDF["x"] == star[starDF.columns.get_loc("x")]) & (brownDwarfDF["M?"] == "x")]
	if (matchingBrownDwarf.size != 0):
		print (matchingBrownDwarf)
	starDFIndex += 1
	if (starDFIndex == 5000):
		break
