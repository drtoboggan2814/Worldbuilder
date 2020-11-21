#	Library declarations
import math
import numpy as np
from matplotlib import pyplot as plt

#	Constants
EARTH_GRAV = 9.80665

#	Unit conversions
AU_IN_M = 149597870700

#	Basic metric conversions
KG_TO_G = 1000
G_TO_KG = 0.001
M_TO_KM = 0.001
KM_TO_M = 1000

#	Basic time conversions
HOUR_TO_DAY = 1 / 24
DAY_TO_HOUR = 24
HOUR_TO_SEC = 3600
DAY_TO_SEC = 86400

#	Transit time given distance and desired acceleration
def transit_time_d_a (d, a):
	transit_time = 2 * math.sqrt(d / a)
	return transit_time

#	Transit time given distance, acceleration, and acceleration time
def transit_time_d_a_t (d, a, t):
	transit_time = ((d - (a * t * t)) / (a * t)) + (2 * t)
	return transit_time

#	acceleration given distance and desired transit time
def acceleration_d_t (d, t):
	acceleration = (4 * d) / (t * t)
	return acceleration

#	Basic Brachistochrone dV
def brach_dV_d_a (d, a):
	dV = 2 * math.sqrt(d * a)
	return dV

#	dV expended given time and acceleration
def dV_expended_t_a (t, a):
	dV = t * a
	return dV

#	a = 0.3 * EARTH_GRAV
a = np.arange (0.1, 1, 0.1)
d = 32 * AU_IN_M
#	d = np.arange (1, 64, 1)
#	t = 6 * DAY_TO_SEC
t = np.arange ((1 / 24), 30, (1 / 24))

#	print (transit_time_d_a(d, a) / DAY_TO_SEC)
#	print (transit_time_d_a_t(d, a, t) / DAY_TO_SEC)
#	print (2 * dV_expended_t_a(t, a) / KM_TO_M)

time_d_a = transit_time_d_a(d, a)
print (time_d_a)
