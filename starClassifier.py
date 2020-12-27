#	This program reads in hygdata_v3_sorted_32_parsec.csv
#	The stellar classification in the column "spect" is adjusted to give a
#	definite answer.  This can then be read into starBuilder.

import math
import numpy as np
import pandas as pd
import re



def vizier_HIP_output_00_func():

	#	Read in hygdata_v3_sorted_32_parsec.csv
	hyg_df = pd.read_csv("hygdata_v3_sorted_32_ps.csv", encoding = "cp1252")

	#	Get stellar classification
	#	For each star in the catalog, read in the stellar classifcation value
	#for starIndex in hyg_df.index:

	vizier_HIP_output_00_df = pd.read_csv("vizier_HIP_output_00.csv", encoding = "cp1252")

	#	Add empty columns to HYG df
	hyg_df["mass"] = np.nan
	hyg_df["mass_t"] = np.nan
	hyg_df["temperature"] = np.nan
	hyg_df["radius"] = np.nan
	hyg_df["radius_t"] = np.nan
	print(hyg_df.columns)
	print(vizier_HIP_output_00_df.columns)

	#count = 0
	#	Loop through vizier_HIP_output_00_df
	for index_V, row_V in vizier_HIP_output_00_df.iterrows():
		if (vizier_HIP_output_00_df.at[index_V, "M*"] == "NaN"):
			vizier_HIP_output_00_df.at[index_V, "M*"] = np.nan
		if (vizier_HIP_output_00_df.at[index_V, "e_M*"] == "NaN"):
			vizier_HIP_output_00_df.at[index_V, "e_M*"] = np.nan
		if (vizier_HIP_output_00_df.at[index_V, "Teff"] == "NaN"):
			vizier_HIP_output_00_df.at[index_V, "Teff"] = np.nan
		if (vizier_HIP_output_00_df.at[index_V, "R*"] == "NaN"):
			vizier_HIP_output_00_df.at[index_V, "R*"] = np.nan
		if (vizier_HIP_output_00_df.at[index_V, "e_R*"] == "NaN"):
			vizier_HIP_output_00_df.at[index_V, "e_R*"] = np.nan

	#	Loop through hyg_df
		for index_H, row_H in hyg_df.iterrows():
			if row_H["hip"] == row_V["HIP"]:
	#			count += 1)
				hyg_df.at[index_H, "mass"] = row_V["M*"]
				print("index_H:", index_H, "| mass:", hyg_df.at[index_H, "mass"])
				hyg_df.at[index_H, "mass_t"] = row_V["e_M*"]
				print("index_H:", index_H, "| mass_t:", hyg_df.at[index_H, "mass_t"])
				hyg_df.at[index_H, "temperature"] = row_V["Teff"]
				print("index_H:", index_H, "| temperature:", hyg_df.at[index_H, "temperature"])
				hyg_df.at[index_H, "radius"] = row_V["R*"]
				print("index_H:", index_H, "| radius:", hyg_df.at[index_H, "radius"])
				hyg_df.at[index_H, "radius_t"] = row_V["e_R*"]
				print("index_H:", index_H, "| radius_t:", hyg_df.at[index_H, "radius_t"])
	#	if (count == 10):
	#		break

#	Reads in the semi-major axis in arcsec and distance in parsec
#	Outputs semi-major axis in AU
def semiMajorAxisCalculator(arcsecSMA, distance):
#	Convert arcsec to degrees
	degSMA = arcsecSMA / 3600
#	Calculate semi-major axis
	semiMajorAxis = tan(degSMA / 2) * (2 * distance)
#	Convert semiMajorAxis to AU
	semiMajorAxis *= 206265

	return semiMajorAxis

def vizier_V_39_output_00_func():
#	Read in vizier_V_39_output_00.csv
	v_39_df = pd.read_csv("vizier_V_39_output_00.csv", encoding = "cp1252")
#	Read in out.csv
	out_df = pd.read_csv("out.csv", encoding = "cp1252")

#	Add empty columns to out_df
	out_df["semiMajorAxis"] = np.nan
	out_df["period"] = np.nan
	out_df["eccentricity"] = np.nan

	count = 0
#	Loop through out_df
	for index_OUT, row_OUT in out_df.iterrows():
	#	Loop through v_39_df
		for index_V_39, row_V_39 in v_39_df.iterrows():
		#	Check if right ascension and declination match
			if ((row_OUT["ra"] == row_V_39["_RAJ2000"]) and (row_OUT["dec"] == row_V_39["_DEJ2000"])):
				count += 1
				out_df.at[index_OUT, "semiMajorAxis"] = semiMajorAxisCalculator(row_V_39["Axis"], out_df.at[index_OUT, "dist"])
				print("index_OUT:", index_OUT, "| semiMajorAxis:", out_df.at[index_OUT, "semiMajorAxis"])
				outdf.at[index_OUT, "period"] = row_V_39["Period"]
				print("index_OUT:", index_OUT, "| period:", out_df.at[index_OUT, "period"])
				outdf.at[index_OUT, "eccentricity"] = row_V_39["Ecc"]
				print("index_OUT:", index_OUT, "| eccentricity:", out_df.at[index_OUT, "eccentricity"])
		if (count == 10):
			break

vizier_V_39_output_00_func()

#	hyg_df.to_csv("out.csv")
