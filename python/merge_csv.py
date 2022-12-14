import numpy as np
import pandas as pd

def combine_csv(df_out, df_in):



#	df_result = pd.DataFrame(columns=(df_out.columns.append(df_in.columns)).unique())
#	df_result.to_csv("df3.csv", index_label = False, mode = "a")
#	del (df_in)
#	df_out = df_out.merge(df_in, how = "outer", on = "oidref", suffixes = (None, None))
#	df_out = df_out.merge(df_in, how = "outer")
	df_out = df_out.combine_first(df_in)
	return df_out

def main():
	pathList_in = ["L:\Downloads\mesDiameter_mean.csv", "L:\Downloads\\flux_mean.csv", "L:\Downloads\mesFe_h_mean.csv", "L:\Downloads\mesISO_mean.csv", "L:\Downloads\mesPM_mean.csv", "L:\Downloads\mesSpT_mean.csv", "L:\Downloads\mesVelocities_mean.csv"]
	dist_path = "L:\Downloads\mesDistance_mean.csv"
	path_out = "L:\Downloads\combinedData.csv"
	df_out = pd.read_csv(dist_path, index_col = "oidref")

	for path_in in pathList_in:
		df_in = pd.read_csv(path_in, index_col = "oidref")
		n = 1000
		list_df = [df_in[i:i+n] for i in range(0,df_in.shape[0],n)]
#		list_df = np.array_split(df_in, 1000)
		for dFrame in list_df:
			df_out = combine_csv(df_out, dFrame)

		df_out.to_csv(path_out)

main()
