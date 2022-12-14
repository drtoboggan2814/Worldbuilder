import numpy as np
import pandas as pd

def average_csv(path_in, path_out):
#	Read in csv
	inputDF = pd.read_csv(path_in, dtype = {"oidref":int})
#	Drop units
	inputDF.drop("unit", axis = 1, inplace = True)
#	Group and average
	outputDF = inputDF.groupby(["oidref"], dropna = False).mean()
	if (path_in == "L:\Downloads\mesSpT.csv"):
		inputDF = pd.read_csv(path_in, dtype = {"oidref":int, "sptype":object})
		stellarTypes = inputDF.groupby(["oidref"])["sptype"].agg(lambda x: pd.Series.mode(x)[0])
		outputDF["sptype"] = stellarTypes

#	Write output
	outputDF.to_csv(path_out)

def main():
	pathList_in = ["L:\Downloads\mesDiameter.csv", "L:\Downloads\\flux.csv", "L:\Downloads\mesFe_h.csv", "L:\Downloads\mesDistance.csv", "L:\Downloads\mesISO.csv", "L:\Downloads\mesPM.csv", "L:\Downloads\mesSpT.csv", "L:\Downloads\mesVelocities.csv"]
	pathList_out = ["L:\Downloads\mesDiameter_mean.csv", "L:\Downloads\\flux_mean.csv", "L:\Downloads\mesFe_h_mean.csv", "L:\Downloads\mesDistance_mean.csv", "L:\Downloads\mesISO_mean.csv", "L:\Downloads\mesPM_mean.csv", "L:\Downloads\mesSpT_mean.csv", "L:\Downloads\mesVelocities_mean.csv"]

	for x_in, x_out in zip(pathList_in, pathList_out):
		print (x_in, x_out)
		average_csv(x_in, x_out)

main()
