import numpy as np
import matplotlib.pyplot as plt
import astropy.units as u
import astropy.constants as c
import sys
import time

class Body():
	def __init__(self, xVec, vVec, mass, name = None, hasUnits = True):
		self.name = name
		self.hasUnits = hasUnits
		if (self.hasUnits):
			self.mass = mass.cgs
			self.xVec = xVec.cgs.value
			self.vVec = vVec.cgs.value
		else:
			self.mass = mass
			self.xVec = xVec
			self.vVec = vVec

	def returnVec(self):
		return np.concatenate((self.xVec, self.vVec))

	def returnMass(self):
		if (self.hasUnits):
			return self.mass.cgs.value
		else:
			return self.mass

	def returnName(self):
		return self.name

class Simulation():
	def __init__(self, bodies, hasUnits = True):
		self.hasUnits = hasUnits
		self.bodies = bodies
		self.nBodies = len(self.bodies)
		self.nDim = 6
		self.quantVec = np.concatenate(np.array([i.returnVec() for i in self.bodies]))
		self.massVec = np.array([i.returnMass() for i in self.bodies])
		self.nameVec = np.array([i.returnName for i in self.bodies])

	def setDiffEq(self, calcDiffEqs, **kwargs):
		self.diffEqKwargs = kwargs
		self.calcDiffEqs = calcDiffEqs

	def rk4(self, t, dt):
		k1 = dt * self.calcDiffEqs(t, self.quantVec ,self.massVec, **self.diffEqKwargs)
		k2 = dt * self.calcDiffEqs(t + 0.5*dt,self.quantVec+0.5*k1, self.massVec, **self.diffEqKwargs)
		k3 = dt * self.calcDiffEqs(t + 0.5*dt,self.quantVec+0.5*k2, self.massVec, **self.diffEqKwargs)
		k4 = dt * self.calcDiffEqs(t + dt, self.quantVec + k2, self.massVec, **self.diffEqKwargs)

		yNew = self.quantVec + ((k1 + (2 * k2) + (2 * k3) + k4) / 6.0)

		return yNew

	def run(self, T, dt, t0 = 0):
		if not hasattr(self, "calcDiffEqs"):
				raise AttributeError("You must set a diff eq solver first.")
		if (self.hasUnits):
			try:
				_ = t0.unit
			except:
				t0 = (t0 * T.unit).cgs.value
			T = T.cgs.value
			dt = dt.cgs.value
		self.history = [self.quantVec]
		clockTime = t0
		nSteps = int((T- t0) / dt)
		startTime = time.time()
		for step in range(nSteps):
			sys.stdout.flush()
			sys.stdout.write("Integrating: step {} / {} | simulation time = {}".format(step, nSteps, round(clockTime, 3)) + "\r")
			yNew = self.rk4(0, dt)
			self.history.append(yNew)
			self.quantVec = yNew
			clockTime += dt
		runtime = time.time() - startTime
		print("\n")
		print("Simulation completed in {} seconds".format(runtime))
		self.history = np.array(self.history)

def nbodySolve(t, y, masses):
	nBodies = int(len(y) / 6)
	solvedVector = np.zeros(y.size)
	for i in range(nBodies):
		iOffset = i * 6
		for j in range(nBodies):
			jOffset = j * 6
			solvedVector[iOffset] = y[iOffset + 3]
			solvedVector[iOffset + 1] = y[iOffset + 4]
			solvedVector[iOffset + 2] = y[iOffset + 5]
			if i != j:
				dx = y[iOffset] - y[jOffset]
				dy = y[iOffset + 1] - y[jOffset + 1]
				dz = y[iOffset + 2] - y[jOffset + 2]
				r = (dx**2 + dy**2 + dz**2)**0.5
				ax = (-c.G.cgs * masses[j] / r**3) * dx
				ay = (-c.G.cgs * masses[j] / r**3) * dy
				az = (-c.G.cgs * masses[j] / r**3) * dz
				ax = ax.value
				ay = ay.value
				az = az.value
				solvedVector[iOffset+3] += ax
				solvedVector[iOffset+4] += ay
				solvedVector[iOffset+5] += az
	return solvedVector

def plotOrbits(nBodies, history):
	for i in range(nBodies):
		iOffset = i * 6
		plt.plot(history[:, iOffset], history[:, iOffset + 1])
		plt.plot(history[-1, iOffset], history[-1, iOffset + 1], 'o')
	plt.axis('equal')
	plt.show()

def main():

#	print (earth_momentum)

#	v_earth = - (moon_momentum / c.M_earth).to(u.km/u.s).value
	M_pluto = (1.303e22 * u.kg).cgs
	v_pluto = np.array([0, 4.743, 0]) * u.km/u.s
	pluto_momentum = M_pluto * v_pluto
	Pluto = Body(mass = M_pluto,
				xVec = np.array([39.482 * c.au.to(u.km).value, 0, 0]) * u.km,
				vVec = v_pluto,
				name = "Pluto")

	M_neptune = (1.02413e26 * u.kg).cgs
	v_neptune = np.array([0, 5.43, 0]) * u.km/u.s
	neptune_momentum = M_neptune * v_neptune
	Neptune = Body(mass = M_neptune,
				xVec = np.array([30.07 * c.au.to(u.km).value, 0, 0]) * u.km,
				vVec = v_neptune,
				name = "Neptune")

	M_uranus = (8.681e25 * u.kg).cgs
	v_uranus = np.array([0, 6.8, 0]) * u.km/u.s
	uranus_momentum = M_uranus * v_uranus
	Uranus = Body(mass = M_uranus,
				xVec = np.array([19.2184 * c.au.to(u.km).value, 0, 0]) * u.km,
				vVec = v_uranus,
				name = "Uranus")

	M_saturn = (5.6834e26 * u.kg).cgs
	v_saturn = np.array([0, 9.68, 0]) * u.km/u.s
	saturn_momentum = M_saturn * v_saturn
	Saturn = Body(mass = M_saturn,
				xVec = np.array([9.5826 * c.au.to(u.km).value, 0, 0]) * u.km,
				vVec = v_saturn,
				name = "Saturn")

	M_jupiter = c.M_jup
	v_jupiter = np.array([0, 13.07, 0]) * u.km/u.s
	jupiter_momentum = M_jupiter * v_jupiter
	Jupiter = Body(mass = M_jupiter,
				xVec = np.array([5.2044 * c.au.to(u.km).value, 0, 0]) * u.km,
				vVec = v_jupiter,
				name = "Jupiter")

	M_mars = (6.4171e23 * u.kg).cgs
	v_mars = np.array([0, 24.007, 0]) * u.km/u.s
	mars_momentum = M_mars * v_mars
	Mars = Body(mass = M_mars,
				xVec = np.array([227939200, 0, 0]) * u.km,
				vVec = v_mars,
				name = "Mars")

	v_earth = np.array([0, 29.78, 0]) * u.km/u.s
	earth_momentum = c.M_earth * v_earth
	Earth = Body(mass = c.M_earth.cgs,
				xVec = np.array([c.au.to(u.km).value,0,0]) * u.km,
#				vVec = np.array(v_earth)*u.km/u.s,
				vVec = v_earth,
				name = 'Earth')

#	v_earth = - (moon_momentum / c.M_earth).to(u.km/u.s).value
	M_moon = (7.347e22 * u.kg).cgs
#	v_moon = - (earth_momentum / M_moon).to(u.km/u.s)
	v_moon = (np.array([0, 1.022, 0]) * u.km/u.s) + v_earth
	moon_momentum = M_moon * v_moon
	Moon = Body(mass = M_moon,
				xVec = np.array([c.au.to(u.km).value + 3.84e5,0,0])*u.km,
#				vVec = np.array(v_moon)*u.km/u.s,
				vVec = v_moon,
				name = "Moon")

	M_venus = (4.8675e24 * u.kg).cgs
	v_venus = np.array([0, 35.02, 0]) * u.km/u.s
	venus_momentum = M_venus * v_venus
	Venus = Body(mass = M_venus,
				xVec = np.array([108208000 , 0, 0]) * u.km,
				vVec = v_venus,
				name = "Venus")

	M_mercury = (3.3011e23 * u.kg).cgs
	v_mercury = np.array([0, 47.36, 0]) * u.km/u.s
	mercury_momentum = M_mercury * v_mercury
	Mercury = Body(mass = M_mercury,
				xVec = np.array([57909050 , 0, 0]) * u.km,
				vVec = v_mercury,
				name = "Mercury")

	v_sun = -((pluto_momentum + uranus_momentum + neptune_momentum + saturn_momentum + jupiter_momentum + venus_momentum + earth_momentum + mars_momentum + mercury_momentum) / c.M_sun).to(u.km/u.s).value

	Sun	= Body(mass = c.M_sun.cgs,
				xVec = np.array([0, 0, 0]) * u.km,
				vVec = np.array(v_sun)*u.km/u.s,
				name = 'Sun')


#	M_moon = (7.347e22 * u.kg).cgs
#	v_moon = np.array([0,1.022,0]) * u.km/u.s
#	moon_momentum = M_moon * v_moon
	#calculate reciprocal momentum for Earth

#	Moon = Body(mass=M_moon,
#				xVec = np.array([u.au + 3.84e5,0,0])*u.km,
#				vVec = v_moon,
#				name='Moon')


	bodies = [Sun, Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune, Pluto, Moon]
	print (len(bodies))
	simulation = Simulation(bodies)
	simulation.setDiffEq(nbodySolve)
	simulation.run(30*u.d,5*u.d)
#	print(simulation.history)
	plotOrbits(len(bodies), simulation.history)

main()
