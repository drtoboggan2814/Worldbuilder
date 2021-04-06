import warnings
import numpy as np
import pandas as pd
from tabulate import tabulate
import time
warnings.simplefilter(action='ignore', category=FutureWarning)

def printStatus(string, variable):
	print (f"{string} == {variable}")

def getStarSystemID(inputUniqueID, starDF):
	starSystemID = starDF.loc[starDF["uniqueID"] == inputUniqueID]["starSystemID"].values[0]
	return starSystemID

def checkStarIdentifiers(starDF, input):
	if (input[3:] != ""):
		hdInput = input[3:]# + ".0"
	else:
		hdInput = input

	if (input[4:] != ""):
		hipInput = input[4:] + ".0"
		hygInput = input[4:] + ".0"
	else:
		hipInput = hygInput = input

	uniqueID	= starDF[starDF["uniqueID"] == input]["uniqueID"]

	properName 	= starDF[starDF["properName"] == input]["properName"]

	hygID		= starDF[starDF["hygIndex"] == hygInput]["hygIndex"]

	hipID		= starDF[starDF["hipIndex"] == hipInput]["hipIndex"]

	hdID 		= starDF[starDF["hdIndex"] == hdInput]["hdIndex"]

	glieseID 	= starDF[starDF["glieseIndex"] == input]["glieseIndex"]

	bayerID 	= starDF[starDF["bayerDesignation"] == input]["bayerDesignation"]

	flamsteedID = starDF[starDF["flamsteedDesignation"] == input]["flamsteedDesignation"]

	return uniqueID, properName, hygID, hipID, hdID, glieseID, bayerID, flamsteedID

def getStarName(starDF, uniqueID):
#	printStatus("uniqueID", uniqueID)
	properName 	= starDF[starDF["uniqueID"] == uniqueID]["properName"]
#	printStatus("properName", properName)
	hygID		= starDF[starDF["uniqueID"] == uniqueID]["hygIndex"]
#	printStatus("hygID", hygID)
	hipID		= starDF[starDF["uniqueID"] == uniqueID]["hipIndex"]
#	printStatus("hipID", hipID)
	hdID 		= starDF[starDF["uniqueID"] == uniqueID]["hdIndex"]
#	printStatus("hdID", hdID)
	glieseID 	= starDF[starDF["uniqueID"] == uniqueID]["glieseIndex"]
#	printStatus("glieseID", glieseID)
	bayerID 	= starDF[starDF["uniqueID"] == uniqueID]["bayerDesignation"]
#	printStatus("bayerID", bayerID)
	flamsteedID = starDF[starDF["uniqueID"] == uniqueID]["flamsteedDesignation"]
#	printStatus("flamsteedID", flamsteedID)

	if (len(properName.values) > 0 and ~properName.isnull().values.any()):
		return properName.values[0]
	elif (len(bayerID.values) > 0 and ~bayerID.isnull().values.any()):
		return bayerID.values[0]
	elif (len(glieseID.values) > 0 and ~glieseID.isnull().values.any()):
		return glieseID.values[0]
	elif (len(flamsteedID.values) > 0 and ~flamsteedID.isnull().values.any()):
		return flamsteedID.values[0]
	elif (len(hdID.values) > 0 and ~hdID.isnull().values.any() and np.all((hdID.values == 0))):
#		if (hdID.values[0][:-2] > 0):
		return "HD " + hdID.values[0]#[:-2]
	elif (len(hipID.values) > 0 and ~hipID.isnull().values.any() and ~np.all((hipID.values == 0))):
#		if (int(hipID.values[0][:-2]) > 0):
		return "HIP " + hipID.values[0][:-2]
	elif (len(hygID.values) > 0 and ~hygID.isnull().values.any()):
#		if (int(hygID.values[0][:-2]) > 0):
		return "HYG " + hygID.values[0][:-2]
	else:
		return uniqueID

def getStarUniqueID(starDF, input):
#	printStatus("flamsteedID", flamsteedID)
	uniqueID, properName, hygID, hipID, hdID, glieseID, bayerID, flamsteedID = checkStarIdentifiers(starDF, input)

	if (input[3:] != ""):
		hdInput = input[3:] + ".0"
	else:
		hdInput = input

	if (input[4:] != ""):
		hipInput = input[4:]# + ".0"
		hygInput = input[4:] + ".0"
	else:
		hipInput = hygInput = input

	if (uniqueID.any() == input):
		result = starDF[starDF["uniqueID"] == input]["uniqueID"]
		return result.values[0]
	elif (properName.any() == input):
		result = starDF[starDF["properName"] == input]["uniqueID"]
		return result.values[0]
	elif (hygID.any() == hygInput):
		result = starDF[starDF["hygIndex"] == hygInput]["uniqueID"]
		return result.values[0]
	elif (hipID.any() == hipInput):
		result = starDF[starDF["hipIndex"] == hipInput]["uniqueID"]
		return result.values[0]
	elif (hdID.any() == hdInput):
		result = starDF[starDF["hdIndex"] == hdInput]["uniqueID"]
		return result.values[0]
	elif (glieseID.any() == input):
		result = starDF[starDF["glieseIndex"] == input]["uniqueID"]
		return result.values[0]
	elif (bayerID.any() == input):
		result = starDF[starDF["bayerDesignation"] == input]["uniqueID"]
		return result.values[0]
	elif (flamsteedID.any() == input):
		result = starDF[starDF["flamsteedDesignation"] == input]["uniqueID"]
		return result.values[0]
	else:
		print("No match found")

def printSystemData(starSystemID, starSystemDF, starDF, worldDF, moonDF, jpDF):
	printStatus("starSystemID", starSystemID)
	starSystemArray = starSystemDF.loc[starSystemDF["uniqueID"] == starSystemID]
	starSystemArrayColumnDict = {"uniqueID":"Unique ID", "numberOfStars":"Number of stars", "systemAge":"System age (Gyr)", "gardenWorldPresent":"Garden world present", "cartesianX":"X (pc)", "cartesianY":"Y (pc)", "cartesianZ":"Z (pc)", "cartesianVelocityX":"vX (pc/yr)", "cartesianVelocityY":"vY (pc/yr)", "cartesianVelocityZ":"vZ (pc/yr)"}

	starArray 	= starDF.loc[starDF["starSystemID"] == starSystemID]
	starArrayColumnDict = {"uniqueID":"Unique ID", "hygIndex":"HYG index", "hipIndex":"HIP index", "hdIndex":"HD index", "glieseIndex":"Gliese index", "properName":"Proper name", "bayerDesignation":"Bayer designation", "flamsteedDesignation":"Flamsteed designation", "starConstellation":"Constellation", "cartesianX":"X (pc)", "cartesianY":"Y (pc)", "cartesianZ":"Z (pc)", "cartesianVelocityX":"vX (pc/yr)", "cartesianVelocityY":"vY (pc/yr)", "cartesianVelocityZ":"vZ (pc/yr)", "distanceFromSol":"Distance from Sol (pc)", "starColor_r":"Color (R)", "starColor_g":"Color (G)", "starColor_b":"Color (B)", "harvardLetter":"Harvard classification", "yerkesClassification":"Yerkes classification", "numericValue":"Numeric classification", "starClassification":"Star classification", "stellarOrbitalPeriod":"Orbital period (days)", "escapeVelocity":"Escape velocity (m/s)", "numberOfCSVPlanets":"Number of planets in exoplanet catalog", "numberOfPlanets":"Number of planets", "starNumber":"Star number", "stellarMass":"Mass (Solar masses)", "stellarAge":"Age (Gyr)", "stellarLuminosity":"Luminosity (Solar luminosity)", "stellarTemperature":"Temperature (K)", "stellarRadius":"Radius (Solar radius)", "equatorialRotationVelocity":"Equatorial rotation velocity (m/s)", "energyRadiated":"Power radiated (W)", "innerLimitRadius":"Inner limit radius (au)", "outerLimitRadius":"Outer limit radius (au)", "snowLineRadius":"Snow line radius (au)", "averageOrbitalRadius":"Semi-major axis (au)", "orbitalEccentricity":"Eccentricity", "minSeparationToCompanion":"Minimum separation (au)", "maxSeparationToCompanion":"Maximum separation (au)", "innerForbiddenZone":"Inner forbidden zone (au)", "outerForbiddenZone":"Outer forbidden zone (au)", "gasGiantArrangement":"Gas giant arrangement", "numberOfJumpPoints":"Number of jump points", "starSystemID":"Star system ID"}

	worldArray 	= worldDF.loc[worldDF["starSystemID"] == starSystemID]
	worldArrayColumnDict = {"uniqueID":"Unique ID", "planetDBIndex":"Planet DB index", "planetName":"Planet name", "sizeClass":"Size class", "randomWorld":"Random world", "worldType":"World type", "resourceValueModifier":"Resource value modifier", "habitabilityModifier":"Habitability modifier", "climateType":"Climate type", "nativeEcosphere":"Native ecosphere", "breathable":"Breathable", "worldDensity":"World density (Earth densities)", "worldDiameter":"World diameter (Earth diameters)", "worldMass":"World Mass (Earth masses)", "surfaceGravity":"Surface gravity (g's)", "volcanicActivityLevel":"Volcanic activity level", "tectonicActivityLevel":"Tectonic activity level", "hydrographicCoverage":"Hydrographic coverage (%)", "surfaceTemperature":"Surface temperature (K)", "dayFaceAverageTemperature":"Day face average temperature (K)", "nightFaceAverageTemperature":"Night face average temperature (K)", "blackbodyCorrection":"Blackbody correction", "blackbodyTemperature":"Blackbody temperature (K)", "magneticFieldStrength":"Magnetic field strength (Earth magnetic fields)", "equatorialRotationVelocity":"Equatorial rotation velocity (m/s)", "surfaceIrradiance":"Surface irradiance (W/m^2)", "totalSurfaceArea":"Total surface area (km^2)", "landSurfaceArea":"Land surface area (km^2)", "liquidSurfaceArea":"Liquid surface area (km^2)", "atmosphereMass":"Atmosphere mass (Earth atmospheres)", "worldAtmosphereComposition.toxicity":"Toxic atmosphere", "worldAtmosphereComposition.chlorineOrFluorine":"Chlorine or fluorine in atmosphere", "worldAtmosphereComposition.lowOxygen":"Low oxygen atmosphere", "worldAtmosphereComposition.highOxygen":"High oxygen atmosphere", "worldAtmosphereComposition.organicToxins":"Atmospheric organic toxins", "worldAtmosphereComposition.sulfurCompounds":"Sulfur compounds in atmosphere", "worldAtmosphereComposition.suffocating":"Suffocating atmosphere", "worldAtmosphereComposition.highCarbonDioxide":"High carbon dioxide atmosphere", "worldAtmosphereComposition.inertGases":"Inert gases in atmosphere", "worldAtmosphereComposition.nitrogenCompounds":"Nitrogen compounds in atmosphere", "worldAtmosphereComposition.pollutants":"Pollutants in atmosphere", "worldAtmosphereComposition.corrosive":"Corrosive atmosphere", "greenhouseFactor":"Greenhouse factor", "absorptionFactor":"Absorption factor", "atmosphericPressure":"Atmospheric pressure (Earth atmospheres)", "atmosphericPressureCategory":"Atmospheric pressure category", "minimumMolecularWeightRetained":"Minimum molecular wight retained (g/mol)", "orbitalRadius":"Semi-major axis (au)", "orbitalPeriod":"Orbital period (d)", "orbitalEccentricity":"Orbital eccentricity", "minimumSeparation":"Minimum separation (au)", "maximumSeparation":"Maximum separation (au)", "rotationPeriod":"Rotation period (days)", "retrogradeOrNot":"Retrograde orbit", "apparentDayLength":"Apparent day length (h)", "axialTilt":"Axial tilt (°)", "resonantOrNot":"Resonant orbit", "tidalLockedOrNot":"Tidal locked", "escapeVelocity":"Escape velocity (m/s)", "numberOfMajorMoons":"Number of major moons", "terrestrialMoonlet":"Number of moonlets", "tidalForceOnPlanetByPrimary":"Tidal force on world by primary", "totalTidalEffect":"Total tidal effect", "firstFamilyMoonlets":"First family moonlets", "secondFamilyMajorMoons":"Second family major moons", "thirdFamilyMoonlets":"Third family moonlets", "ringSystemVisibility":"Ring system visibility", "gasGiantTinySulfurPresent":"Tiny sulfur world present in gas giant system", "hexesPerSid":"Hexes per side", "totalHexe":"Total hexes", "waterHexCoun":"Water hexes", "landHexCoun":"Land hexes", "numberOfMajorOcean":"Major oceans", "numberOfMinorOcean":"Minor oceans", "numberOfSmallSea":"Small seas", "numberOfScatteredLake":"Scattered lakes", "numberOfMajorContinent":"Major continents", "numberOfMinorContinent":"Minor continents", "numberOfMajorIsland":"Major islands", "numberOfArchipelagoes":"Archipelagoes", "tectonicPlateCount":"Tectonic plates", "starSystemID":"Star system ID", "starID":"Star ID"}

	moonArray	= moonDF.loc[moonDF["starSystemID"] == starSystemID]
	moonArrayColumnDict = {"uniqueID":"Unique ID", "moonName":"Moon name", "sizeClass":"Size class", "worldType":"World type", "resourceValueModifier":"Resource value modifier", "habitabilityModifier":"Habitability modifier", "climateType":"Climate type", "nativeEcosphere":"Native ecosphere", "breathable":"Breathable", "worldDensity":"World density (Earth densities)", "worldDiameter":"World diameter (Earth diameters)", "worldMass":"World Mass (Earth masses)", "surfaceGravity":"Surface gravity (g's)", "volcanicActivityLevel":"Volcanic activity level", "tectonicActivityLevel":"Tectonic activity level", "hydrographicCoverage":"Hydrographic coverage (%)", "surfaceTemperature":"Surface temperature (K)", "dayFaceAverageTemperature":"Day face average temperature (K)", "nightFaceAverageTemperature":"Night face average temperature (K)", "blackbodyCorrection":"Blackbody correction", "blackbodyTemperature":"Blackbody temperature (K)", "magneticFieldStrength":"Magnetic field strength (Earth magnetic fields)", "equatorialRotationVelocity":"Equatorial rotation velocity (m/s)", "surfaceIrradiance":"Surface irradiance (W/m^2)", "totalSurfaceArea":"Total surface area (km^2)", "landSurfaceArea":"Land surface area (km^2)", "liquidSurfaceArea":"Liquid surface area (km^2)", "atmosphereMass":"Atmosphere mass (Earth atmospheres)", "worldAtmosphereComposition.toxicity":"Toxic atmosphere", "worldAtmosphereComposition.chlorineOrFluorine":"Chlorine or fluorine in atmosphere", "worldAtmosphereComposition.lowOxygen":"Low oxygen atmosphere", "worldAtmosphereComposition.highOxygen":"High oxygen atmosphere", "worldAtmosphereComposition.organicToxins":"Atmospheric organic toxins", "worldAtmosphereComposition.sulfurCompounds":"Sulfur compounds in atmosphere", "worldAtmosphereComposition.suffocating":"Suffocating atmosphere", "worldAtmosphereComposition.highCarbonDioxide":"High carbon dioxide atmosphere", "worldAtmosphereComposition.inertGases":"Inert gases in atmosphere", "worldAtmosphereComposition.nitrogenCompounds":"Nitrogen compounds in atmosphere", "worldAtmosphereComposition.pollutants":"Pollutants in atmosphere", "worldAtmosphereComposition.corrosive":"Corrosive atmosphere", "greenhouseFactor":"Greenhouse factor", "absorptionFactor":"Absorption factor", "atmosphericPressure":"Atmospheric pressure (Earth atmospheres)", "atmosphericPressureCategory":"Atmospheric pressure category", "minimumMolecularWeightRetained":"Minimum molecular wight retained (g/mol)", "orbitalRadius":"Semi-major axis (au)", "orbitalPeriod":"Orbital period (d)", "orbitalEccentricity":"Orbital eccentricity", "minimumSeparation":"Minimum separation (au)", "maximumSeparation":"Maximum separation (au)", "rotationPeriod":"Rotation period (days)", "retrogradeOrNot":"Retrograde orbit", "apparentDayLength":"Apparent day length (h)", "axialTilt":"Axial tilt (°)", "resonantOrNot":"Resonant orbit", "tidalLockedOrNot":"Tidal locked", "escapeVelocity":"Escape velocity (m/s)", "tidalForceOnSatelliteByPlanet":"Tidal force on satellite by planet", "totalTidalEffect":"Total tidal effect", "hexesPerSid":"Hexes per side", "totalHexe":"Total hexes", "waterHexCoun":"Water hexes", "landHexCoun":"Land hexes", "numberOfMajorOcean":"Major oceans", "numberOfMinorOcean":"Minor oceans", "numberOfSmallSea":"Small seas", "numberOfScatteredLake":"Scattered lakes", "numberOfMajorContinent":"Major continents", "numberOfMinorContinent":"Minor continents", "numberOfMajorIsland":"Major islands", "numberOfArchipelagoes":"Archipelagoes", "tectonicPlateCount":"Tectonic plates", "worldID":"World ID", "starSystemID":"Star system ID", "starID":"Star ID"}

	jpArray 	= jpDF.loc[jpDF["starSystemID"] == starSystemID]
	jpArrayColumnDict = {"uniqueID":"Unique ID", "starID":"Star ID", "connectingPointID":"Connecting jump point ID", "connectingStarID":"Connecting star ID", "distanceToConnectingPoint":"Distance to connecting jump point (pc)", "cartesianX":"X (pc)", "cartesianY":"Y (pc)", "cartesianZ":"Z (pc)", "starSystemID":"Star system ID", "distanceToPrimary":"Distance to primary (au)", "arc":"Bearing (°)"}

	pd.set_option('display.max_columns', 500)
	pd.set_option('display.colheader_justify', 'left')
	pd.set_option('display.precision', 2)
	pd.set_option('display.width', 1000)
#	print(worldArray)
	print("\n")
	jpArray.rename(columns = jpArrayColumnDict)
	worldArray.rename(columns = worldArrayColumnDict)
	arrayToPrint = worldArray
#	print (arrayToPrint)
	print(tabulate(arrayToPrint, headers = arrayToPrint.columns, tablefmt="pretty"))

def main():
#	Load .csv's

#	starSystemDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/starSystem_t_db.csv", dtype = {"uniqueID":object})
#	starDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/star_t_db_final.csv", dtype = {"uniqueID":object})
#	worldDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/world_t_db_final.csv", dtype = {"uniqueID":object})
#	moonDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/moon_t_db.csv", dtype = {"uniqueID":object})
#	jpDF = pd.read_csv("/media/MAGI_II/Projects/Worldbuilder/finalOutput/jpDF_out_max_8_3pc.csv", dtype = {"uniqueID":object, "starID":object, "connectingPointID":object, "connectingStarID":object})
	starSystemDF = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/starSystem_t_db.csv", dtype = {"uniqueID":object})
	starDF = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/star_t_db_final.csv", dtype = {"uniqueID":object, "starSystemID":object})
	worldDF = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/world_t_db_final.csv", dtype = {"uniqueID":object, "starSystemID":object, "starID":object})
	moonDF = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/moon_t_db.csv", dtype = {"uniqueID":object, "starSystemID":object, "starID":object, "worldID":object})
#	readTime = time.time()
	jpDF = pd.read_csv("Z:/Projects/Worldbuilder/finalOutput/jpDF_out_max_8_3pc.csv", dtype = {"uniqueID":object, "starID":object, "connectingPointID":object, "connectingStarID":object, "starSystemID":object})
#	print (time.time() - readTime)
	input = "Arcturus"
	inputUniqueID = getStarUniqueID(starDF, input)
	inputSystemID = getStarSystemID(inputUniqueID, starDF)
#	printStatus("inputSystemID", inputSystemID)
	printSystemData(inputSystemID, starSystemDF, starDF, worldDF, moonDF, jpDF)

main()
