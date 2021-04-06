#ifndef STRINGCONSTANTS
#define STRINGCONSTANTS

#include <string>

//	This file defines string constants for printing purposes
const std::string SPECTRAL_TYPE_LOOKUP_TABLE[34] = {"M7", "M6", "M5", "M4", "M4", "M3", "M2", "M1", "M0", "K8", "K6", "K5", "K4", "K2", "K0", "G8", "G6", "G4", "G2", "G1", "G0", "F9", "F8", "F7", "F6", "F5", "F4", "F3", "F2", "F0", "A9", "A7", "A6", "A5"};

//	Atmospheric pressure category strings
const std::string APC_NONE_S = "None";
const std::string APC_TRACE_S = "Trace";
const std::string APC_VERY_THIN_S = "Very Thin";
const std::string APC_THIN_S = "Thin";
const std::string APC_STANDARD_S = "Standard";
const std::string APC_DENSE_S = "Dense";
const std::string APC_VERY_DENSE_S = "Very Dense";
const std::string APC_SUPERDENSE_S = "Superdense";

//	Atmopsheric pressure category lookup table
const std::string APC_S_LOOKUP_TABLE[8] = {APC_NONE_S, APC_TRACE_S, APC_VERY_THIN_S, APC_THIN_S, APC_STANDARD_S, APC_DENSE_S, APC_VERY_DENSE_S, APC_SUPERDENSE_S};

//	Climate type strings
const std::string CT_FROZEN_S = "Frozen";
const std::string CT_VERY_COLD_S = "Very Cold";
const std::string CT_COLD_S = "Cold";
const std::string CT_CHILLY_S = "Chilly";
const std::string CT_COOL_S = "Cool";
const std::string CT_NORMAL_S = "Normal";
const std::string CT_WARM_S = "Warm";
const std::string CT_TROPICAL_S = "Tropical";
const std::string CT_HOT_S = "Hot";
const std::string CT_VERY_HOT_S = "Very Hot";
const std::string CT_INFERNAL_S = "Infernal";

//	Climate type lookup table
const std::string CT_S_LOOKUP_TABLE[11] = {CT_FROZEN_S, CT_VERY_COLD_S, CT_COLD_S, CT_CHILLY_S, CT_COOL_S, CT_NORMAL_S, CT_WARM_S, CT_TROPICAL_S, CT_HOT_S, CT_VERY_HOT_S, CT_INFERNAL_S};

//	Constellation names
const std::string CON_S_AND = "Andromeda";
const std::string CON_S_ANT = "Antlia";
const std::string CON_S_APS = "Apus";
const std::string CON_S_AQR = "Aquarius";
const std::string CON_S_AQL = "Aquila";
const std::string CON_S_ARA = "Ara";
const std::string CON_S_ARI = "Aries";
const std::string CON_S_AUR = "Auriga";
const std::string CON_S_BOO = "Boötes";
const std::string CON_S_CAE = "Caelum";
const std::string CON_S_CAM = "Camelopardalis";
const std::string CON_S_CNC = "Cancer";
const std::string CON_S_CVN = "Canes Venatici";
const std::string CON_S_CMA = "Canis Major";
const std::string CON_S_CMI = "Canis Minor";
const std::string CON_S_CAP = "Capricornus";
const std::string CON_S_CAR = "Carina";
const std::string CON_S_CAS = "Cassiopeia";
const std::string CON_S_CEN = "Centaurus";
const std::string CON_S_CEP = "Cepheus";
const std::string CON_S_CET = "Cetus";
const std::string CON_S_CHA = "Chamaeleon";
const std::string CON_S_CIR = "Circinus";
const std::string CON_S_COL = "Columba";
const std::string CON_S_COM = "Coma Berenices";
const std::string CON_S_CRA = "Corona Australis";
const std::string CON_S_CRB = "Corona Borealis";
const std::string CON_S_CRV = "Corvus";
const std::string CON_S_CRT = "Crater";
const std::string CON_S_CRU = "Crux";
const std::string CON_S_CYG = "Cygnus";
const std::string CON_S_DEL = "Delphinus";
const std::string CON_S_DOR = "Dorado";
const std::string CON_S_DRA = "Draco";
const std::string CON_S_EQU = "Equuleus";
const std::string CON_S_ERI = "Eridanus";
const std::string CON_S_FOR = "Fornax";
const std::string CON_S_GEM = "Gemini";
const std::string CON_S_GRU = "Grus";
const std::string CON_S_HER = "Hercules";
const std::string CON_S_HOR = "Horologium";
const std::string CON_S_HYA = "Hydra";
const std::string CON_S_HYI = "Hydrus";
const std::string CON_S_IND = "Indus";
const std::string CON_S_LAC = "Lacerta";
const std::string CON_S_LEO = "Leo";
const std::string CON_S_LMI = "Leo Minor";
const std::string CON_S_LEP = "Lepus";
const std::string CON_S_LIB = "Libra";
const std::string CON_S_LUP = "Lupus";
const std::string CON_S_LYN = "Lynx";
const std::string CON_S_LYR = "Lyra";
const std::string CON_S_MEN = "Mensa";
const std::string CON_S_MIC = "Microscopium";
const std::string CON_S_MON = "Monoceros";
const std::string CON_S_MUS = "Musca";
const std::string CON_S_NOR = "Norma";
const std::string CON_S_OCT = "Octans";
const std::string CON_S_OPH = "Ophiuchus";
const std::string CON_S_ORI = "Orion";
const std::string CON_S_PAV = "Pavo";
const std::string CON_S_PEG = "Pegasus";
const std::string CON_S_PER = "Perseus";
const std::string CON_S_PHE = "Phoenix";
const std::string CON_S_PIC = "Pictor";
const std::string CON_S_PSC = "Pisces";
const std::string CON_S_PSA = "Piscis Austrinus";
const std::string CON_S_PUP = "Puppis";
const std::string CON_S_PYX = "Pyxis";
const std::string CON_S_RET = "Reticulum";
const std::string CON_S_SGE = "Sagitta";
const std::string CON_S_SGR = "Sagittarius";
const std::string CON_S_SCO = "Scorpius";
const std::string CON_S_SCL = "Sculptor";
const std::string CON_S_SCT = "Scutum";
const std::string CON_S_SER = "Serpens";
const std::string CON_S_SEX = "Sextans";
const std::string CON_S_TAU = "Taurus";
const std::string CON_S_TEL = "Telescopium";
const std::string CON_S_TRI = "Triangulum";
const std::string CON_S_TRA = "Triangulum Australe";
const std::string CON_S_TUC = "Tucana";
const std::string CON_S_UMA = "Ursa Major";
const std::string CON_S_UMI = "Ursa Minor";
const std::string CON_S_VEL = "Vela";
const std::string CON_S_VIR = "Virgo";
const std::string CON_S_VOL = "Volans";
const std::string CON_S_VUL = "Vulpecula";

//	Constellation genitives
const std::string CON_S_GEN_AND = "Andromedae";
const std::string CON_S_GEN_ANT = "Antliae";
const std::string CON_S_GEN_APS = "Apodis";
const std::string CON_S_GEN_AQR = "Aquarii";
const std::string CON_S_GEN_AQL = "Aquilae";
const std::string CON_S_GEN_ARA = "Arae";
const std::string CON_S_GEN_ARI = "Arietis";
const std::string CON_S_GEN_AUR = "Aurigae";
const std::string CON_S_GEN_BOO = "Boötis";
const std::string CON_S_GEN_CAE = "Caeli";
const std::string CON_S_GEN_CAM = "Camelopardalis";
const std::string CON_S_GEN_CNC = "Cancri";
const std::string CON_S_GEN_CVN = "Canum Venaticorum";
const std::string CON_S_GEN_CMA = "Canis Majoris";
const std::string CON_S_GEN_CMI = "Canis Minoris";
const std::string CON_S_GEN_CAP = "Capricorni";
const std::string CON_S_GEN_CAR = "Carinae";
const std::string CON_S_GEN_CAS = "Cassiopeiae";
const std::string CON_S_GEN_CEN = "Centauri";
const std::string CON_S_GEN_CEP = "Cephei";
const std::string CON_S_GEN_CET = "Ceti";
const std::string CON_S_GEN_CHA = "Chamaeleontis";
const std::string CON_S_GEN_CIR = "Circini";
const std::string CON_S_GEN_COL = "Columbae";
const std::string CON_S_GEN_COM = "Comae Berenices";
const std::string CON_S_GEN_CRA = "Coronae Australis";
const std::string CON_S_GEN_CRB = "Coronae Borealis";
const std::string CON_S_GEN_CRV = "Corvi";
const std::string CON_S_GEN_CRT = "Crateris";
const std::string CON_S_GEN_CRU = "Crucis";
const std::string CON_S_GEN_CYG = "Cygni";
const std::string CON_S_GEN_DEL = "Delphini";
const std::string CON_S_GEN_DOR = "Doradus";
const std::string CON_S_GEN_DRA = "Draconis";
const std::string CON_S_GEN_EQU = "Equulei";
const std::string CON_S_GEN_ERI = "Eridani";
const std::string CON_S_GEN_FOR = "Fornacis";
const std::string CON_S_GEN_GEM = "Geminorum";
const std::string CON_S_GEN_GRU = "Gruis";
const std::string CON_S_GEN_HER = "Herculis";
const std::string CON_S_GEN_HOR = "Horologii";
const std::string CON_S_GEN_HYA = "Hydrae";
const std::string CON_S_GEN_HYI = "Hydri";
const std::string CON_S_GEN_IND = "Indi";
const std::string CON_S_GEN_LAC = "Lacertae";
const std::string CON_S_GEN_LEO = "Leonis";
const std::string CON_S_GEN_LMI = "Leonis Minoris";
const std::string CON_S_GEN_LEP = "Leporis";
const std::string CON_S_GEN_LIB = "Librae";
const std::string CON_S_GEN_LUP = "Lupi";
const std::string CON_S_GEN_LYN = "Lyncis";
const std::string CON_S_GEN_LYR = "Lyrae";
const std::string CON_S_GEN_MEN = "Mensae";
const std::string CON_S_GEN_MIC = "Microscopii";
const std::string CON_S_GEN_MON = "Monocerotis";
const std::string CON_S_GEN_MUS = "Muscae";
const std::string CON_S_GEN_NOR = "Normae";
const std::string CON_S_GEN_OCT = "Octantis";
const std::string CON_S_GEN_OPH = "Ophiuchi";
const std::string CON_S_GEN_ORI = "Orionis";
const std::string CON_S_GEN_PAV = "Pavonis";
const std::string CON_S_GEN_PEG = "Pegasi";
const std::string CON_S_GEN_PER = "Persei";
const std::string CON_S_GEN_PHE = "Phoenicis";
const std::string CON_S_GEN_PIC = "Pictoris";
const std::string CON_S_GEN_PSC = "Piscium";
const std::string CON_S_GEN_PSA = "Piscis Austrini";
const std::string CON_S_GEN_PUP = "Puppis";
const std::string CON_S_GEN_PYX = "Pyxidis";
const std::string CON_S_GEN_RET = "Reticuli";
const std::string CON_S_GEN_SGE = "Sagittae";
const std::string CON_S_GEN_SGR = "Sagittarii";
const std::string CON_S_GEN_SCO = "Scorpii";
const std::string CON_S_GEN_SCL = "Sculptoris";
const std::string CON_S_GEN_SCT = "Scuti";
const std::string CON_S_GEN_SER = "Serpentis";
const std::string CON_S_GEN_SEX = "Sextantis";
const std::string CON_S_GEN_TAU = "Tauri";
const std::string CON_S_GEN_TEL = "Telescopii";
const std::string CON_S_GEN_TRI = "Trianguli";
const std::string CON_S_GEN_TRA = "Trianguli Australis";
const std::string CON_S_GEN_TUC = "Tucanae";
const std::string CON_S_GEN_UMA = "Ursae Majoris";
const std::string CON_S_GEN_UMI = "Ursae Minoris";
const std::string CON_S_GEN_VEL = "Velorum";
const std::string CON_S_GEN_VIR = "Virginis";
const std::string CON_S_GEN_VOL = "Volantis";
const std::string CON_S_GEN_VUL = "Vulpeculae";



//	Gas giant arrangement strings
const std::string GGA_NO_GAS_GIANT_S = "No Gas Giant";
const std::string GGA_EPISTELLAR_GAS_GIANT_S = "Epistellar Gas Giant";
const std::string GGA_ECCENTRIC_GAS_GIANT_S = "Eccentric Gas Giant";
const std::string GGA_CONVENTIONAL_GAS_GIANT_S = "Conventional Gas Giant";

//	Gas giant arrangement lookup table
const std::string GGA_S_LOOKUP_TABLE[4] = {GGA_NO_GAS_GIANT_S, GGA_EPISTELLAR_GAS_GIANT_S, GGA_ECCENTRIC_GAS_GIANT_S, GGA_CONVENTIONAL_GAS_GIANT_S};

//	Overall type strings
const std::string OT_S_HOSTILE = "Hostile";
const std::string OT_S_BARREN = "Barren";
const std::string OT_S_GARDEN = "Garden";

//	Overall type lookup table
const std::string OT_S_LOOKUP_TABLE[3] = {OT_S_HOSTILE, OT_S_BARREN, OT_S_GARDEN};

//	Size class strings
const std::string SC_S_EMPTY_ORBIT = "Empty Orbit";
const std::string SC_S_ASTEROID_BELT = "Asteroid Belt";
const std::string SC_S_TERRESTRIAL_PLANET_TINY = "Terrestrial Planet (Tiny)";
const std::string SC_S_TERRESTRIAL_PLANET_SMALL = "Terrestrial Planet (Small)";
const std::string SC_S_TERRESTRIAL_PLANET_STANDARD = "Terrestrial Planet (Standard)";
const std::string SC_S_TERRESTRIAL_PLANET_LARGE = "Terrestrial Planet (Large)";
const std::string SC_S_SMALL_GAS_GIANT = "Small Gas Giant";
const std::string SC_S_MEDIUM_GAS_GIANT = "Medium Gas Giant";
const std::string SC_S_LARGE_GAS_GIANT = "Large Gas Giant";

//	Size class lookup table
const std::string SC_S_LOOKUP_TABLE[9] = {SC_S_EMPTY_ORBIT, SC_S_ASTEROID_BELT, SC_S_TERRESTRIAL_PLANET_TINY, SC_S_TERRESTRIAL_PLANET_SMALL, SC_S_TERRESTRIAL_PLANET_STANDARD, SC_S_TERRESTRIAL_PLANET_LARGE, SC_S_SMALL_GAS_GIANT, SC_S_MEDIUM_GAS_GIANT, SC_S_LARGE_GAS_GIANT};

//	Tectonic activity level strings
const std::string TAL_NONE_S = "None";
const std::string TAL_LIGHT_S = "Light";
const std::string TAL_MODERATE_S = "Moderate";
const std::string TAL_HEAVY_S = "Heavy";
const std::string TAL_EXTREME_S = "Extreme";

//	Tectonic activity level lookup table
const std::string TAL_S_LOOKUP_TABLE[5] = {TAL_NONE_S, TAL_LIGHT_S, TAL_MODERATE_S, TAL_HEAVY_S, TAL_EXTREME_S};

//	Tectonic plate movement types
const std::string TPMT_S_CONVERGING = "Converging";
const std::string TPMT_S_TRAVERSING = "Traversing";
const std::string TPMT_S_DIVERGING = "Diverging";

//	Tectonic plate movement type lookup table
const std::string TPMT_S_LOOKUP_TABLE[3] = {TPMT_S_CONVERGING, TPMT_S_TRAVERSING, TPMT_S_DIVERGING};

//	Volcanic activity level strings
const std::string VAL_NONE_S = "None";
const std::string VAL_LIGHT_S = "Light";
const std::string VAL_MODERATE_S = "Moderate";
const std::string VAL_HEAVY_S = "Heavy";
const std::string VAL_EXTREME_S = "Extreme";

//	Volcanic activity level lookup table
const std::string VAL_S_LOOKUP_TABLE[5] = {VAL_NONE_S, VAL_LIGHT_S, VAL_MODERATE_S, VAL_HEAVY_S, VAL_EXTREME_S};

//	World type strings
const std::string WT_ASTEROID_BELT_S = "Asteroid Belt";
const std::string WT_TINY_ICE_S = "Tiny (Ice)";
const std::string WT_TINY_SULFUR_S = "Tiny (Sulfur)";
const std::string WT_TINY_ROCK_S = "Tiny (Rock)";
const std::string WT_SMALL_HADEAN_S = "Small (Hadean)";
const std::string WT_SMALL_ICE_S = "Small (Ice)";
const std::string WT_SMALL_ROCK_S = "Small (Rock)";
const std::string WT_STANDARD_HADEAN_S = "Standard (Hadean)";
const std::string WT_STANDARD_AMMONIA_S = "Standard (Ammonia)";
const std::string WT_STANDARD_ICE_S = "Standard (Ice)";
const std::string WT_STANDARD_OCEAN_S = "Standard (Ocean)";
const std::string WT_STANDARD_GARDEN_S = "Standard (Garden)";
const std::string WT_STANDARD_GREENHOUSE_S = "Standard (Greenhouse)";
const std::string WT_STANDARD_CHTHONIAN_S = "Standard (Chthonian)";
const std::string WT_LARGE_AMMONIA_S = "Large (Ammonia)";
const std::string WT_LARGE_ICE_S = "Large (Ice)";
const std::string WT_LARGE_OCEAN_S = "Large (Ocean)";
const std::string WT_LARGE_GARDEN_S = "Large (Garden)";
const std::string WT_LARGE_GREENHOUSE_S = "Large (Greenhouse)";
const std::string WT_LARGE_CHTHONIAN_S = "Large (Chthonian)";
const std::string WT_SMALL_GAS_GIANT_S = "Small Gas Giant";
const std::string WT_MEDIUM_GAS_GIANT_S = "Medium Gas Giant";
const std::string WT_LARGE_GAS_GIANT_S = "Large Gas Giant";

//	World type lookup table
const std::string WT_S_LOOKUP_TABLE[23] = {WT_ASTEROID_BELT_S, WT_TINY_ICE_S, WT_TINY_SULFUR_S, WT_TINY_ROCK_S, WT_SMALL_HADEAN_S, WT_SMALL_ICE_S, WT_SMALL_ROCK_S, WT_STANDARD_HADEAN_S, WT_STANDARD_AMMONIA_S, WT_STANDARD_ICE_S, WT_STANDARD_OCEAN_S, WT_STANDARD_GARDEN_S, WT_STANDARD_GREENHOUSE_S, WT_STANDARD_CHTHONIAN_S, WT_LARGE_AMMONIA_S, WT_LARGE_ICE_S, WT_LARGE_OCEAN_S, WT_LARGE_GARDEN_S, WT_LARGE_GREENHOUSE_S, WT_LARGE_CHTHONIAN_S, WT_SMALL_GAS_GIANT_S, WT_MEDIUM_GAS_GIANT_S, WT_LARGE_GAS_GIANT_S};

//	Life
const std::string NE_NOLIFE_S = "No life";
const std::string NE_PROTOZOA_S = "Protozoa";
const std::string NE_METAZOA_S = "Metazoa";
const std::string NE_SIMPLEANIMALS_S = "Simple animals";
const std::string NE_COMPLEXANIMALS_S = "Complex animals";
const std::string NE_S_LOOKUP_TABLE[5] = {NE_NOLIFE_S, NE_PROTOZOA_S, NE_METAZOA_S, NE_SIMPLEANIMALS_S, NE_COMPLEXANIMALS_S};

#endif
