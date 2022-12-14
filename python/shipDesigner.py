import math
import numpy as np
import pandas as pd

def printStatus(string, variable):
	print (f"{string} == {variable}")

def getMassFlow(force_N, vE):
#	Fusion efficiency
	n_f = 1
#	Thermal efficiency
	n_thermal = 0.75
#	Energy from 1 kg of D + H^3
	e_H3_D_TJ_kg = 353.23

	p_therm_W = pow(force_N, 2) / (n_f * (force_N / vE))
	p_therm_TW = p_therm_W / pow(10, 12)

	printStatus("p_therm_TW", p_therm_TW)

	m_dot_kg_s = pow(force_N, 2) / (n_f * p_therm_W)
	m_dot_fuel_kg_s = (p_therm_TW / n_thermal) / e_H3_D_TJ_kg
	m_dot_prop_kg_s = m_dot_kg_s - m_dot_fuel_kg_s

	fuelFraction = m_dot_fuel_kg_s / m_dot_kg_s
	propFraction = m_dot_prop_kg_s / m_dot_kg_s

	return (m_dot_fuel_kg_s, m_dot_prop_kg_s, fuelFraction, propFraction)

def getNonInertMass(fuelFraction, propFraction, m_ship_pt_t):
	m_fuel_t = fuelFraction * m_ship_pt_t
	m_H3_t = (2 / 3) * m_fuel_t
	m_D_t = (1 / 3) * m_fuel_t

	m_prop_t = propFraction * m_ship_pt_t

	return (m_fuel_t, m_H3_t, m_D_t, m_prop_t)

def getBoostMass(m_ship_kg, dV_boost_m_s, fP_W, vE_boost):
	f_boost_N = (2 * fP_W) / vE_boost
	r_boost = math.exp(dV_boost_m_s / ((2 * fP_W) / f_boost_N))
	m_total_kg_final = (r_boost * m_ship_kg)
	m_boost_kg_final = m_total_kg_final - m_ship_kg

	return (m_boost_kg_final, m_total_kg_final, r_boost, f_boost_N)

def getOptimalvE(dV):
	return dV * (1 / math.log(4))

def get_vE(vE = None, dV = None, R = 1, f = None, fP = None):
	if (vE != None):
		return vE
	elif (dV != None and (R != None and R != 1)):
		return (dV / math.log(R))
	elif (f != None and fP != None):
		return (2 * fP) / f
	else:
		return None

def get_dV(dV = None, vE = None, R = 1):
	if (dV != None):
		return dV
	elif (vE != None and (R != None and R != 1)):
		return vE * math.log(R)
	else:
		return None

def get_fP(fP = None, f = None, vE = None):
	if (fP != None):
		return fP
	elif (f != None and vE != None):
		return (f * vE) / 2
	else:
		return None

def get_R(R = None, mass_empty = None, mass_full = None, dV = None, vE = None):
	if (R != None and R != 1):
		return R
	elif (mass_empty != None and mass_full != None):
		return mass_full / mass_empty
	elif (dV != None and vE != None):
		return math.exp(dV / vE)
	else:
		return None

def get_f(f = None, mass_full = None, accel = None, vE = None, fP = None):
	if (f != None):
		return f
	elif (mass_full != None and accel != None):
		return mass_full * accel
	elif (vE != None and fP != None):
		return (2 * fP) / vE
	else:
		return None

def get_mass_kg(mass_input, f_N = None, accel = None, vol_ship = None, d_ship_kg_m_3 = None):
	if (mass_input != None):
		return mass_input
	elif (f_N != None and accel != None):
		return f_N / accel
	elif (vol_ship != None and d_ship_kg_m_3 != None):
		return d_ship_kg_m_3 * vol_ship
	else:
		return None

def get_final_dV(dV_input_m_s, R = None, mass_empty = None, mass_full = None, f_N = None, accel = None, fP_W = None, vE = None):
	R = get_R(R = R, mass_empty = mass_empty, mass_full = mass_full)
	f_N = get_f(f = f_N, mass_full = mass_full, accel = accel, fP = fP_W, vE = vE)
	fP_W = get_fP(fP = fP_W)
	vE = get_Ve(vE = vE, R = R, f = f_N, fP = fP_W)

	dV_output_m_s = get_dV(vE = vE, R = R)
	return dV_output_m_s

def get_final_vE(vE_input, R = None, dV_input_m_s = None, f_N = None, fP_W = None, mass_empty = None, mass_full = None, accel = None):
	R = get_R(R = R, mass_empty = mass_empty, mass_full = mass_full)
	f_N = get_f(f = f_N, mass_full = mass_full, accel = accel)
	fP_W = get_fP(fP = fP_W)
	dV = get_dV(dV = dV_input_m_s, vE = vE_input, R = R)

	vE_output = get_vE(vE = vE_input, dV = dV, R = R, f = f_N, fP = fP_W)
	return vE_output

def shipDesigner(dV_cruise_m_s, dV_boost_m_s, thrust_multiplier, a_cruise, a_boost, vE_cruise, vE_boost, vol_ship, d_ship_kg_m_3, m_ship_kg, f_cruise_N, f_boost_N, fP_W, r_cruise, r_boost, m_ship_i_kg, m_ship_pt_kg, m_boost_kg):
	while_loop_conditions = [dV_cruise_m_s, dV_boost_m_s, vE_cruise, vE_boost, m_ship_kg, m_boost_kg, f_cruise_N, f_boost_N, fP_W, r_cruise, r_boost]
	while_flag = any(x is None for x in while_loop_conditions)
	while (while_flag):
	#	Check for dV
		if (dV_cruise_m_s is None):
			dV_cruise_m_s = get_final_dV(dV_input_m_s = dV_cruise_m_s, R = r_cruise, mass_empty = m_ship_i_kg, mass_full = m_ship_kg, f_N = f_cruise_N, accel = a_cruise, fP_W = fP_W, vE = vE_cruise)
		printStatus("dV_cruise_m_s", dV_cruise_m_s)
		if (dV_boost_m_s is None):
			if (not(m_ship_kg is None or m_boost_kg is None)):
				mass_full = m_boost_kg + m_ship_kg
			else:
				mass_full = None
			dV_boost_m_s = get_final_dV(dV_input_m_s = dV_boost_m_s, R = r_boost, mass_empty = m_ship_i_kg, mass_full = mass_full, f_N = f_boost_N, accel = a_boost, fP_W = fP_W, vE = vE_boost)
		printStatus("dV_boost_m_s", dV_boost_m_s)

	#	Check for vE
		if (vE_cruise is None):
			vE_cruise = get_final_vE(vE_input = vE_cruise, R = r_cruise, dV_input_m_s = dV_cruise_m_s, f_N = f_cruise_N, fP_W = fP_W, mass_empty = m_ship_i_kg, mass_full = m_ship_i_kg, accel = a_cruise)
		printStatus("vE_cruise", vE_cruise)
		if (vE_boost is None):
			if (not(m_ship_kg is None or m_boost_kg is None)):
				mass_full = m_boost_kg + m_ship_kg
			else:
				mass_full = None
			vE_boost = get_vE(vE = vE_boost, dV = dV_boost_m_s, R = r_boost, f = f_boost_N, fP = fP_W)
			# vE_boost = get_final_vE(vE_input = vE_boost, R = r_boost, dV_input_m_s = dV_boost_m_s, f_N = f_boost_N, fP_W = fP_W, mass_empty = m_ship_i_kg, mass_full = mass_full, accel = a_boost)
		printStatus("vE_boost", vE_boost)

	#	Check for mass
		if (m_ship_kg is None):
			m_ship_kg = get_mass_kg(mass_input = m_ship_kg, f_N = f_cruise_N, accel = a_cruise, vol_ship = vol_ship, d_ship_kg_m_3 = d_ship_kg_m_3)
		printStatus("m_ship_kg", m_ship_kg)
		if (m_boost_kg is None):
			m_boost_kg = get_mass_kg(mass_input = m_boost_kg, f_N = f_boost_N, accel = a_boost, vol_ship = None, d_ship_kg_m_3 = None)
		printStatus("m_boost_kg", m_boost_kg)

	#	Check for force
		if (f_cruise_N is None):
			f_cruise_N = get_f(f = f_cruise_N, mass_full = m_ship_kg, accel = a_cruise, vE = vE_cruise, fP = fP_W)
		printStatus("f_cruise_N", f_cruise_N)
		if (f_boost_N is None):
			if (not(m_ship_kg is None or m_boost_kg is None)):
				f_boost_N = get_f(f = f_boost_N, mass_full = m_ship_kg + m_boost_kg, accel = a_boost, vE = vE_boost, fP = fP_W)
		printStatus("f_boost_N", f_boost_N)

	#	Check for thrust power
		if (fP_W is None):
			f_temp_N = None
			if (f_cruise_N != None):
				f_temp_N = f_cruise_N
			elif (f_boost_N != None):
				f_temp_N = f_boost_N

			vE_temp = None
			if (vE_cruise != None):
				vE_temp = vE_cruise
			elif (vE_boost != None):
				vE_temp = vE_boost

			fP_W = get_fP(fP = fP_W, f = f_temp_N, vE = vE_temp)
		printStatus("fP_W", fP_W)

	#	Check for mass ratios
		if (r_cruise is None):
			r_cruise = get_R(R = r_cruise, mass_empty = m_ship_i_kg, mass_full = m_ship_kg, dV = dV_cruise_m_s, vE = vE_cruise)
		printStatus("r_cruise", r_cruise)
		if (r_boost is None):
			r_boost = get_R(R = r_boost, mass_empty = m_ship_kg, mass_full = m_boost_kg, dV = dV_boost_m_s, vE = vE_boost)
		printStatus("r_boost", r_boost)
		print("\n")
# #	Input dV's
# 	dV_cruise_km_s = 1024
# 	dV_cruise_m_s = dV_cruise_km_s * 1000
# 	dV_boost_km_s = dV_cruise_km_s / 4
# 	dV_boost_m_s = dV_boost_km_s * 1000
#
# #	Acceleration (m/s^2)
# 	EARTH_GRAV = 9.81
# 	thrust_multiplier = 1 / 2
# 	a_cruise = EARTH_GRAV * thrust_multiplier
# 	a_boost = a_cruise * 4
#
# #	Exhaust velocity (m/s)
# 	vE_cruise = getOptimalvE(dV_cruise_m_s) * thrust_multiplier
# 	vE_boost = getOptimalvE(dV_boost_m_s) * thrust_multiplier
#
	printStatus("vE_cruise", vE_cruise)
	printStatus("vE_boost", vE_boost)
#
# #	Ship characteristics
# 	vol_ship = 28160.1893492277
# #	Density (t/m^3)
# 	d_ship = 0.25
# #	Total ship mass
# 	m_ship_t = vol_ship * d_ship
# 	m_ship_kg = m_ship_t * 1000
#
# 	# m_ship_t = 3084.4642857142857142857142857143
# 	# m_ship_kg = m_ship_t * 1000
#
	printStatus("m_ship_t", m_ship_t)
#
# #	Thrust
# 	f_cruise_N = m_ship_kg * a_cruise
# 	f_cruise_MN = f_cruise_N / 1000000
#
	printStatus("f_cruise_MN", f_cruise_MN)
#
# 	f_boost_N = m_ship_kg * a_boost
# 	f_boost_MN = f_boost_N / 1000000
#
# #	Thrust power
# 	fP_W = (vE_cruise * f_cruise_N) / 2
# 	fP_TW = fP_W / pow(10, 12)
#
	printStatus("fP_TW", fP_TW)
#
# #	Mass ratio
# 	r_cruise = math.exp(dV_cruise_m_s / vE_cruise)
# 	r_boost = math.exp(dV_boost_m_s / vE_boost)
#
#
#
# #	Mass of inert ship and propellant + fuel
# 	# m_ship_i_t = m_ship_t / r_cruise
# 	m_ship_i_t = 3084.4642857142857142857142857143
# 	m_ship_pt_t = m_ship_t - m_ship_i_t
# 	r_cruise = m_ship_t / m_ship_i_t
	printStatus("m_ship_i_t", m_ship_i_t)
	printStatus("m_ship_pt_t", m_ship_pt_t)
	printStatus("r_cruise", r_cruise)
#	Cruise characteristics
	(m_dot_fuel_cruise_kg_s, m_dot_prop_cruise_kg_s, fuelFraction_cruise, propFraction_cruise) = getMassFlow(f_cruise_N, vE_cruise)
	(m_fuel_cruise_t, m_H3_cruise_t, m_D_cruise_t, m_prop_cruise_t) = getNonInertMass(fuelFraction_cruise, propFraction_cruise, m_ship_pt_t)
#	Boost characteristics
	(m_boost_kg_final, m_total_kg_final, r_boost, f_final_N) = getBoostMass(m_ship_kg, dV_boost_m_s, fP_W, vE_boost)
	(m_dot_fuel_boost_kg_s, m_dot_prop_boost_kg_s, fuelFraction_boost, propFraction_boost) = getMassFlow(f_boost_N, vE_boost)
	(m_fuel_boost_t, m_H3_boost_t, m_D_boost_t, m_prop_boost_t) = getNonInertMass(fuelFraction_boost, propFraction_boost, m_boost_kg_final)

	printStatus("m_dot_fuel_cruise_kg_s", m_dot_fuel_cruise_kg_s)
	printStatus("m_dot_prop_cruise_kg_s", m_dot_prop_cruise_kg_s)
	printStatus("fuelFraction_cruise", fuelFraction_cruise)
	printStatus("propFraction_cruise", propFraction_cruise)

	printStatus("m_fuel_cruise_t", m_fuel_cruise_t)
	printStatus("m_H3_cruise_t", m_H3_cruise_t)
	printStatus("m_D_cruise_t", m_D_cruise_t)
	printStatus("m_prop_cruise_t", m_prop_cruise_t)

	printStatus("m_boost_kg_final", m_boost_kg_final)
	printStatus("m_total_kg_final", m_total_kg_final)
	printStatus("r_boost", r_boost)
	printStatus("f_final_N", f_final_N)

	printStatus("m_fuel_boost_t", m_fuel_boost_t)
	printStatus("m_H3_boost_t", m_H3_boost_t)
	printStatus("m_D_boost_t", m_D_boost_t)
	printStatus("m_prop_boost_t", m_prop_boost_t)

	printStatus("m_boost_kg_final", m_boost_kg_final)
	printStatus("m_total_kg_final", m_total_kg_final)
	printStatus("r_boost", r_boost)
	printStatus("f_final_N", f_final_N)

def main():
	shipDesigner_options = dict(
		dV_cruise_m_s = 1024 * 1000,
		dV_boost_m_s = 128 * 1000,
		thrust_multiplier = 1,
		a_cruise = 3,
		a_boost = 6,
		vE_cruise = None,
		vE_boost = None,
		vol_ship = 28160.1893492277,
		d_ship_kg_m_3 = 250,
		m_ship_kg = None,
		m_boost_kg = None,
		f_cruise_N = None,
		f_boost_N = None,
		fP_W = None,
		r_cruise = None,
		r_boost = None,
		m_ship_i_kg = 3084.4642857142857142857142857143 * 1000,
		m_ship_pt_kg = None
	)
	shipDesigner(**shipDesigner_options)
main()
