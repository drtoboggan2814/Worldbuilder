#ifndef STRINGCONSTANTS
#define STRINGCONSTANTS

#include <string>

//	This file defines string constants for printing purposes

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

//	Tectonic activity level strings
const std::string TAL_NONE_S = "None";
const std::string TAL_LIGHT_S = "Light";
const std::string TAL_MODERATE_S = "Moderate";
const std::string TAL_HEAVY_S = "Heavy";
const std::string TAL_EXTREME_S = "Extreme";

//	Tectonic activity level lookup table
const std::string TAL_S_LOOKUP_TABLE[5] = {TAL_NONE_S, TAL_LIGHT_S, TAL_MODERATE_S, TAL_HEAVY_S, TAL_EXTREME_S};

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

#endif
