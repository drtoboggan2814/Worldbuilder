import pandas as pd
import wikipedia as wp
import numpy as np
import re

#	Function retrieve the appropriate data for each field
#	def getStarSystemData(page_df, system_df, componentIndex, componentColumns, componentIndexNames):


#	Function to get the index of the desired variable
def getDfIndex(df, variable):
#	Find index
	anyResult = df.eq(variable).any(axis = 1)
#	Retrieve the integer value of the index
	variableIndex = anyResult[anyResult == True].index
#	Return the value
	return variableIndex

#	Function to count number of components in the system
def getComponentCount(df, systemName):
#	Maximum number of stars in system is 3
#	Look for a C component
	if (df.eq(systemName + " C").any(axis = None)):
		componentCount = 3
		componentColumns = [systemName + " A", systemName + " B", systemName + " C"]
	elif (df.eq(systemName + "C").any(axis = None)):
		componentCount = 3
		componentColumns = [systemName + "A", systemName + "B", systemName + "C"]
#	Look for B component
	elif (df.eq(systemName + " B").any(axis = None)):
		componentCount = 2
		componentColumns = [systemName + " A", systemName + " B"]
	elif (df.eq(systemName + "B").any(axis = None)):
		componentCount = 2
		componentColumns = [systemName + "A", systemName + "B"]
	elif (df.eq(systemName + "A").any(axis = None)):
		componentCount = 1
		componentColumns = [systemName + "A"]
#	Else
	else:
		componentCount = 1
		componentColumns = [systemName + " A"]
#	Return componentCount
#	print (componentColumns)
	return componentCount, componentColumns

#	Function to replace Greek characters with Latin
def greekToLatin(df):
#	Alpha
	df.replace(to_replace = {r'α+':'Alpha'}, regex=True, inplace=True)

#	Function to remove any units
def removeUnits(df):
	junkUnits = r"(\sGyr|\sK|\b\sd\b|\sdays|\syr|billion|years|million|AU)"
	df.replace(to_replace = {junkUnits:''}, regex=True, inplace=True)
	return df

#	Function to remove extraneous characters
def cleanStrings(df):
	junkStrings = [r"\[\d+\]+", r"\[.+\]+", r"\(.+\)+", r"\w☉+", r"″+", r"≈+", r"MJup+"]
	for string in junkStrings:
		df.replace(to_replace = {string:''}, regex=True, inplace=True)
#	Remove whitespace
	df[df.columns] = df.apply(lambda x: x.str.strip())
	return df

#	Function to get details from a star's page
def getStarDetails(pageName):
#	print (pageName)
#	Get page html
	pageHTML = wp.page(pageName).html().encode("utf-16")
#	Create df out of infobox
	page_df = pd.read_html(pageHTML)[0]

#	Remove units
	page_df = removeUnits(page_df)
#	Clean strings
	page_df = cleanStrings(page_df)
#	Get componentCount and column names
	componentCount, componentColumns = getComponentCount(page_df, pageName)
#	Initialize the index labels
	componentIndexNames = ["Mass", "Age", "Temperature", "Radius", "Rotation", "Semi-major axis", "Eccentricity", "Period"]
#	Create df for system
	system_df = pd.DataFrame(np.zeros((len(componentIndexNames), componentCount)), columns = componentColumns, index = componentIndexNames)

	duplicateCount = 0
#	Fill system_df
#	Find index locations of all relevant variables
	for variableName in componentIndexNames:
		x = getDfIndex(page_df, variableName)

#		If the length of x is larger than componentCount
		if (len(x) > componentCount):
#			If componentCount is even
			if (componentCount % 2 == 0):
#				Maximum size of componentCount should be 3
				x = [x[0], x[2]]
			else:
				x = [x[0], x[2], x[4]]
#		print (x)
#		Loop through list returned from x
#		Retrieve the value at that index and column from page_df
#		Assign to system_df
		tempIndex = 0
		if (variableName == "Age" or variableName == "Semi-major axis" or variableName == "Eccentricity" or variableName == "Period"):
			validVariableNameFlag = True
		else:
			validVariableNameFlag = False
		for y in x:
#			z is equal to the value at row y, column 1
			z = page_df.at[y, 1]
#			print ("len(x) = ", len(x))
#			print (z)
#			If the length of "Age" is 1
			if (variableName == "Age" and len(x) == 1):
				system_df.loc[variableName] = z
#			If the variable name is any of the other valid names, length is one, and is not "Age"
			elif (validVariableNameFlag == True and len(x) == 1 and variableName != "Age"):
#				print (componentCount)
#				If there is only one star in system
				if (componentCount == 1):
#					print ("componentCount == 1")
					system_df.loc[variableName] = z
#				Otherwise
				else:
#					print ("componentCount is greater than 1")
#					Column 0 = NaN
					system_df.loc[variableName, componentColumns[0]] = np.nan
#					print ("system_df.loc[variableName, componentColumns[0]] = ", system_df.loc[variableName, componentColumns[0]])
#					All others equal z
					system_df.loc[variableName, componentColumns[1]] = z
#					print ("system_df.loc[variableName, componentColumns[1]] = ", system_df.loc[variableName, componentColumns[1]])

#			If there are two components
			elif (validVariableNameFlag == True and len(x) == 2):
#				Set primary to NaN
				system_df.loc[variableName, componentColumns[0]] = np.nan
#				Assign the first value to the first companion
				if (y == x[0]):
					system_df.loc[variableName, componentColumns[1]] = z
#				Assign the second value to the second companion
				elif (y == x[1]):
					system_df.loc[variableName, componentColumns[2]] = z
#			Else if the list is empty
			elif (validVariableNameFlag == True and len(x) == 0):
				system_df.loc[variableName] = np.nan
#			Otherwise, set equal to z
			else:
				system_df.loc[variableName, componentColumns[tempIndex]] = z
#				print ("validVariableNameFlag == False, tempIndex = ", tempIndex)
			tempIndex += 1
#			system_df.loc[variableName, componentColumns[tempIndex]] = z
#	Create tolerance rows
#	Loop through rows
	for row in componentIndexNames:
#		Create a temporary row with the appropriate values
		tempRow = system_df.xs(row, 0)
#		Remove comma separators
		tempRow = tempRow.astype("str")
		tempRow = tempRow.str.replace(u'\xa0', u' ')
		tempRow = tempRow.str.replace(",", "")
#		Partition the values along ±
		tempRow = tempRow.str.partition("±")
#		Partition the values along |
#		tempRow = tempRow.str.partition("|")
#		Drop the ± column
		tempRow = tempRow.drop(1, 1)
#		print ("tempRow:", tempRow)
#		Loop through tempRow[0]
		for label, content in tempRow[0].items():
#			Find minus sign
			if (content.find(r"−") != -1):
#				print ("Label: " + label)
#				print (tempRow.loc[label, 0])
#				Split string
				newContent = re.split(r"[\+−]", content)
#				Assign definite value to tempRow[0]
				tempRow[0].loc[label] = newContent[0]
#				Average values
				newContent = (float(newContent[1]) + float(newContent[2])) / 2
#				Assign new value to tempRow[2]
				tempRow[2].loc[label] = str(newContent)
#				print ("tempRow[2]:", tempRow[2])
#			Find tilde
			if (content.find("~") != -1):
				newContent = re.split(r"[~–]", content)
#				Assign definite value to tempRow[0]
				tempRow[0].loc[label] = newContent[0]
#				Average values
				newContent = (float(newContent[1]) + float(newContent[2])) / 2
#				Assign new value to tempRow[2]
				tempRow[2].loc[label] = str(newContent)
#			Find dash
			if (content.find("-") != -1):
				newContent = re.split(r"-", content)
				print (len(tempRow))
				if (len(tempRow) == 1):
					tempRow[0].loc[label] = (float(newContent[0]) + float(newContent[1])) / 2
				else:
#					Assign definite value to tempRow[0]
					tempRow[0].loc[label] = newContent[0]
#					Average values
					newContent = (float(newContent[1]) + float(newContent[2])) / 2
#					Assign new value to tempRow[2]
					tempRow[2].loc[label] = str(newContent)

				print (newContent)

#		Set all empty and NaN's to 0
		tempRow = tempRow.replace("", 0)
		tempRow = tempRow.replace(np.nan, 0)
#		Convert all values to float
		tempRow = tempRow.astype("float")

		system_df.loc[row] = tempRow[0]
#		Rename tempRow to row + Tolerance
		defName = ("Definite", row)
		defName = " ".join(defName)
		tolName = (row, "Tolerance")
		tolName = " ".join(tolName)
#		print (newName)
		tempRow.columns = [defName, tolName]
#		Append tempRow[2] to system_df
		system_df = system_df.append(tempRow[tolName])
#	Reindex system_df
	newIndex = ["Mass", "Mass Tolerance", "Age", "Age Tolerance", "Temperature", "Temperature Tolerance", "Radius", "Radius Tolerance", "Rotation", "Rotation Tolerance", "Semi-major axis", "Semi-major axis Tolerance", "Eccentricity", "Eccentricity Tolerance", "Period", "Period Tolerance"]
	system_df = system_df.reindex(newIndex)
	print (system_df)
	return system_df



#	Get html
html = wp.page("List of nearest stars and brown dwarfs").html().encode("utf-16")
#	Column name list
columnNames = ["System", "Star", "Distance", "Stellar class", "Apparent", "Absolute", "Right Ascension", "Declination", "Parallax (mas (±err))", "Discovery date", "Notes and additional references"]
#	Create dataframe
df = pd.read_html(html)[1]
#	Drop bottom two rows
df = df.drop([len(df) - 1, len(df) - 2])

#	Display all rows
#	pd.set_option("display.max_rows", None)
#	Display all columns
#	pd.set_option("display.max_columns", None)

#	Remove Wikipedia references
#	df.replace(to_replace = {r'\[\d+\]+':''}, regex=True, inplace=True)
#	Remove [note #]
#	df.replace(to_replace = {r'\[note\s\d+\]':''}, regex=True, inplace=True)
#	Remove parentheses
#	df.replace(to_replace = {r'\(.+\)+':''}, regex=True, inplace=True)

#	Clean strings
df = cleanStrings(df)
#	Convert characters
greekToLatin(df)

#	Assign columnNames to the df's columns
df.columns = columnNames

#	Create a temporary df called tempDistance
tempDistance = df.xs("Distance", 1)
#	Partition each string at ±
tempDistance = tempDistance.str.partition("±")
#	Drop the ± column
tempDistance = tempDistance.drop(1, 1)

#	Drop original Distance column
df = df.drop("Distance", 1)
#	Insert new Distance column
df.insert(2, "Distance", tempDistance[0])
#	Insert Tolerance column
df.insert(3, "Distance Tolerance", tempDistance[2])

#	Get systems from System column
wikiPageList = df.xs("System", 1)
#	Set Proxima Centauri's system to itself
wikiPageList.at[1] = df.at[1, "Star"]
#	Remove duplicates
wikiPageList = wikiPageList.drop_duplicates()
#	Print wikiPageList
#	print (wikiPageList)
wikiPageDataArray = []
#for item in wikiPageList:
#	wikiPageDataArray.append(getStarDetails(item))
#	print (wikiPageList)
getStarDetails(wikiPageList[7])
#print (wikiPageDataArray)
