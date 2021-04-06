//	This function checks what identifiers are present in starDoc and assigns them to the star
//	C++ libraries
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <tuple>

//	Constants
#include "declarations/constants/stringConstants.h"

//	Third party libraries
#include "declarations/third_party/rapidcsv.h"

std::string getStarConstellationGenitive(std::string starConstellation)
{
	if 		(starConstellation == "And")	{return CON_S_GEN_AND;}
	else if (starConstellation == "Ant")	{return CON_S_GEN_ANT;}
	else if (starConstellation == "Aps")	{return CON_S_GEN_APS;}
	else if (starConstellation == "Aqr")	{return CON_S_GEN_AQR;}
	else if (starConstellation == "Aql")	{return CON_S_GEN_AQL;}
	else if (starConstellation == "Ara")	{return CON_S_GEN_ARA;}
	else if (starConstellation == "Ari")	{return CON_S_GEN_ARI;}
	else if (starConstellation == "Aur")	{return CON_S_GEN_AUR;}
	else if (starConstellation == "Boo")	{return CON_S_GEN_BOO;}
	else if (starConstellation == "Cae")	{return CON_S_GEN_CAE;}
	else if (starConstellation == "Cam")	{return CON_S_GEN_CAM;}
	else if (starConstellation == "Cnc")	{return CON_S_GEN_CNC;}
	else if (starConstellation == "CVn")	{return CON_S_GEN_CVN;}
	else if (starConstellation == "CMa")	{return CON_S_GEN_CMA;}
	else if (starConstellation == "CMi")	{return CON_S_GEN_CMI;}
	else if (starConstellation == "Cap")	{return CON_S_GEN_CAP;}
	else if (starConstellation == "Car")	{return CON_S_GEN_CAR;}
	else if (starConstellation == "Cas")	{return CON_S_GEN_CAS;}
	else if (starConstellation == "Cen")	{return CON_S_GEN_CEN;}
	else if (starConstellation == "Cep")	{return CON_S_GEN_CEP;}
	else if (starConstellation == "Cet")	{return CON_S_GEN_CET;}
	else if (starConstellation == "Cha")	{return CON_S_GEN_CHA;}
	else if (starConstellation == "Cir")	{return CON_S_GEN_CIR;}
	else if (starConstellation == "Col")	{return CON_S_GEN_COL;}
	else if (starConstellation == "Com")	{return CON_S_GEN_COM;}
	else if (starConstellation == "CrA")	{return CON_S_GEN_CRA;}
	else if (starConstellation == "CrB")	{return CON_S_GEN_CRB;}
	else if (starConstellation == "Crv")	{return CON_S_GEN_CRV;}
	else if (starConstellation == "Crt")	{return CON_S_GEN_CRT;}
	else if (starConstellation == "Cru")	{return CON_S_GEN_CRU;}
	else if (starConstellation == "Cyg")	{return CON_S_GEN_CYG;}
	else if (starConstellation == "Del")	{return CON_S_GEN_DEL;}
	else if (starConstellation == "Dor")	{return CON_S_GEN_DOR;}
	else if (starConstellation == "Dra")	{return CON_S_GEN_DRA;}
	else if (starConstellation == "Equ")	{return CON_S_GEN_EQU;}
	else if (starConstellation == "Eri")	{return CON_S_GEN_ERI;}
	else if (starConstellation == "For")	{return CON_S_GEN_FOR;}
	else if (starConstellation == "Gem")	{return CON_S_GEN_GEM;}
	else if (starConstellation == "Gru")	{return CON_S_GEN_GRU;}
	else if (starConstellation == "Her")	{return CON_S_GEN_HER;}
	else if (starConstellation == "Hor")	{return CON_S_GEN_HOR;}
	else if (starConstellation == "Hya")	{return CON_S_GEN_HYA;}
	else if (starConstellation == "Hyi")	{return CON_S_GEN_HYI;}
	else if (starConstellation == "Ind")	{return CON_S_GEN_IND;}
	else if (starConstellation == "Lac")	{return CON_S_GEN_LAC;}
	else if (starConstellation == "Leo")	{return CON_S_GEN_LEO;}
	else if (starConstellation == "LMi")	{return CON_S_GEN_LMI;}
	else if (starConstellation == "Lep")	{return CON_S_GEN_LEP;}
	else if (starConstellation == "Lib")	{return CON_S_GEN_LIB;}
	else if (starConstellation == "Lup")	{return CON_S_GEN_LUP;}
	else if (starConstellation == "Lyn")	{return CON_S_GEN_LYN;}
	else if (starConstellation == "Lyr")	{return CON_S_GEN_LYR;}
	else if (starConstellation == "Men")	{return CON_S_GEN_MEN;}
	else if (starConstellation == "Mic")	{return CON_S_GEN_MIC;}
	else if (starConstellation == "Mon")	{return CON_S_GEN_MON;}
	else if (starConstellation == "Mus")	{return CON_S_GEN_MUS;}
	else if (starConstellation == "Nor")	{return CON_S_GEN_NOR;}
	else if (starConstellation == "Oct")	{return CON_S_GEN_OCT;}
	else if (starConstellation == "Oph")	{return CON_S_GEN_OPH;}
	else if (starConstellation == "Ori")	{return CON_S_GEN_ORI;}
	else if (starConstellation == "Pav")	{return CON_S_GEN_PAV;}
	else if (starConstellation == "Peg")	{return CON_S_GEN_PEG;}
	else if (starConstellation == "Per")	{return CON_S_GEN_PER;}
	else if (starConstellation == "Phe")	{return CON_S_GEN_PHE;}
	else if (starConstellation == "Pic")	{return CON_S_GEN_PIC;}
	else if (starConstellation == "Psc")	{return CON_S_GEN_PSC;}
	else if (starConstellation == "PsA")	{return CON_S_GEN_PSA;}
	else if (starConstellation == "Pup")	{return CON_S_GEN_PUP;}
	else if (starConstellation == "Pyx")	{return CON_S_GEN_PYX;}
	else if (starConstellation == "Ret")	{return CON_S_GEN_RET;}
	else if (starConstellation == "Sge")	{return CON_S_GEN_SGE;}
	else if (starConstellation == "Sgr")	{return CON_S_GEN_SGR;}
	else if (starConstellation == "Sco")	{return CON_S_GEN_SCO;}
	else if (starConstellation == "Scl")	{return CON_S_GEN_SCL;}
	else if (starConstellation == "Sct")	{return CON_S_GEN_SCT;}
	else if (starConstellation == "Ser")	{return CON_S_GEN_SER;}
	else if (starConstellation == "Sex")	{return CON_S_GEN_SEX;}
	else if (starConstellation == "Tau")	{return CON_S_GEN_TAU;}
	else if (starConstellation == "Tel")	{return CON_S_GEN_TEL;}
	else if (starConstellation == "Tri")	{return CON_S_GEN_TRI;}
	else if (starConstellation == "TrA")	{return CON_S_GEN_TRA;}
	else if (starConstellation == "Tuc")	{return CON_S_GEN_TUC;}
	else if (starConstellation == "UMa")	{return CON_S_GEN_UMA;}
	else if (starConstellation == "UMi")	{return CON_S_GEN_UMI;}
	else if (starConstellation == "Vel")	{return CON_S_GEN_VEL;}
	else if (starConstellation == "Vir")	{return CON_S_GEN_VIR;}
	else if (starConstellation == "Vol")	{return CON_S_GEN_VOL;}
	else if (starConstellation == "Vul")	{return CON_S_GEN_VUL;}

}

std::tuple<int, int, int, int, std::string, std::string, std::string, std::string> getStarIDFromCSV(rapidcsv::Document& starDoc, int currentCSVIndex, std::string starConstellation)
{
//	If there is no entry for a numeric ID, assign it 0
//	If the string ID's are blank, they will be assigned ""
	int hipIndex 		= (starDoc.GetCell<std::string>("hip", currentCSVIndex) == "") ? 0 : starDoc.GetCell<int>("hip", currentCSVIndex);
	std::cout << "hipIndex == " << hipIndex << std::endl;
	int hygIndex 		= (starDoc.GetRowName(currentCSVIndex) == "") ? 0 : std::stoi(starDoc.GetRowName(currentCSVIndex));
	std::cout << "hygIndex == " << hygIndex << std::endl;
	int hdIndex 		= (starDoc.GetCell<std::string>("hd", currentCSVIndex) == "") ? 0 : starDoc.GetCell<int>("hd", currentCSVIndex);
	std::cout << "hdIndex == " << hdIndex << std::endl;
	int hrIndex 		= (starDoc.GetCell<std::string>("hr", currentCSVIndex) == "") ? 0 : starDoc.GetCell<int>("hr", currentCSVIndex);
	std::cout << "hrIndex == " << hrIndex << std::endl;
	std::string glieseIndex	= starDoc.GetCell<std::string>("gl", currentCSVIndex) == "" ? "" : starDoc.GetCell<std::string>("gl", currentCSVIndex);
	std::cout << "glieseIndex == " << glieseIndex << std::endl;
	std::string properName		= starDoc.GetCell<std::string>("proper", currentCSVIndex) == "" ? "" : starDoc.GetCell<std::string>("proper", currentCSVIndex);
	std::cout << "properName == " << properName << std::endl;
	std::string bayerDesignation = (starDoc.GetCell<std::string>("bayer", currentCSVIndex) == "") ? "" : starDoc.GetCell<std::string>("bayer", currentCSVIndex) + " " + getStarConstellationGenitive(starConstellation);
	std::cout << "bayerDesignation == " << bayerDesignation << std::endl;
	std::string flamsteedDesignation = (starDoc.GetCell<std::string>("fla", currentCSVIndex) == "") ? "" : starDoc.GetCell<std::string>("fla", currentCSVIndex) + " " + getStarConstellationGenitive(starConstellation);
	std::cout << "flamsteedDesignation == " << flamsteedDesignation << std::endl;

	return std::make_tuple(hipIndex, hygIndex, hdIndex, hrIndex, glieseIndex, properName, bayerDesignation, flamsteedDesignation);
}
