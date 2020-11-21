/*
#include <string>
#include <iostream>
#include <iomanip>

#include "declarations/structures/atmosphericComposition_t.h"
#include "declarations/structures/moon_t.h"
#include "declarations/structures/world_t.h"

#include "declarations/functions/printAtmosphereComposition.h"

using namespace std;

//	This function prints information about the world in question to the console
void printWorld(world_t world)
{
//	Print the world's details
//	Astronomical attributes
	cout << left << setw(32) << "Orbital radius:" << world.orbitalRadius << endl;
	cout << left << setw(32) << "Orbital period:" << world.orbitalPeriod << endl;
	cout << left << setw(32) << "Orbital eccentricity:" << world.orbitalEccentricity << endl;
	cout << left << setw(32) << "Minimum separation to primary:" << world.minimumSeparation << endl;
	cout << left << setw(32) << "Maximum separation to primary:" << world.maximumSeparation << endl;
	cout << left << setw(32) << "Rotation period:" << world.rotationPeriod << endl;
	if (world.retrogradeOrNot == true) {cout << left << setw(32) << "World has a retrograde rotation" << endl;}
	cout << left << setw(32) << "Apparent day length:" << world.apparentDayLength << endl;
	cout << left << setw(32) << "Axial tilt:" << world.axialTilt << endl;
	if (world.resonantOrNot == true) {cout << left << setw(32) << "World is in a resonant orbit" << endl;}
	if (world.tidalLockedOrNot == true) {cout << left << setw(32) << "World is tidal locked" << endl;}
	cout << left << setw(32) << "Number of major moons:" << world.numberOfMajorMoons << endl;
	cout << left << setw(32) << "Number of moonlets:" << world.terrestrialMoonlet << endl;
//	Physical attributes
	cout << left << setw(32) << "\nOverall type:" << world.overallType 											<< endl;
	cout << left << setw(32) << "World type:" << world.worldType 												<< endl;
	cout << left << setw(32) << "Atmosphere mass:" << world.atmosphereMass 										<< endl;
//	Print the composition of the world's atmosphere (if it has one)
	if (world.atmosphereMass != 0) {printAtmosphereComposition(world.worldAtmosphereComposition);}
//	Resume printing the world's details
	cout << left << setw(32) << "Hydrographic coverage:" << world.hydrographicCoverage 							<< endl;
	cout << left << setw(32) << "Surface temperature:" << world.surfaceTemperature 								<< endl;
	cout << left << setw(32) << "Greenhouse factor:" << world.greenhouseFactor 									<< endl;
	cout << left << setw(32) << "Absorption factor:" << world.absorptionFactor 									<< endl;
	cout << left << setw(32) << "Blackbody temperature:" << world.blackbodyTemperature 							<< endl;
	cout << left << setw(32) << "World density:" << world.worldDensity 											<< endl;
	cout << left << setw(32) << "World diameter:" << world.worldDiameter 										<< endl;
	cout << left << setw(32) << "Surface gravity:" << world.surfaceGravity 										<< endl;
	cout << left << setw(32) << "World mass:" << world.worldMass 												<< endl;
	cout << left << setw(32) << "Atmospheric pressure:" << world.atmosphericPressure 							<< endl;
	cout << left << setw(32) << "Minimum molecular weight retained:" << world.minimumMolecularWeightRetained 	<< endl;
	cout << left << setw(32) << "Resource value modifier:" << world.resourceValueModifier 						<< endl;
	cout << left << setw(32) << "Habitability modifier:" << world.habitabilityModifier 							<< endl;
}
*/
