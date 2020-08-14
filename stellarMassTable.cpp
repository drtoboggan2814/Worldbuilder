//	This calculates the mass of the star, and returns the mass and a variance

#include "declarations/functions/diceRoller.h"
#include "declarations/functions/floatRNG.h"

float stellarMassTable()
{
	int firstRoll, secondRoll;
	float stellarMass, variance;

	variance = floatRNG(-0.025, 0.025);
	firstRoll 	= diceRoller(6, 3);
	secondRoll 	= diceRoller(6, 3);

	if 		(firstRoll == 3)
	{
		if 		(secondRoll >= 3  && secondRoll <= 10) {stellarMass = 2.00;}
		else if (secondRoll >= 11 && secondRoll <= 18) {stellarMass = 1.90;}
	}

	else if (firstRoll == 4)
	{
		if		(secondRoll >= 3  && secondRoll <= 8 ) {stellarMass = 1.80;}
		else if (secondRoll >= 9  && secondRoll <= 11) {stellarMass = 1.70;}
		else if (secondRoll >= 12 && secondRoll <= 18) {stellarMass = 1.60;}
	}

	else if (firstRoll == 5)
	{
		if 		(secondRoll >= 3  && secondRoll <= 7 ) {stellarMass = 1.5 ;}
		else if (secondRoll >= 8  && secondRoll <= 10) {stellarMass = 1.45;}
		else if (secondRoll >= 11 && secondRoll <= 12) {stellarMass = 1.40;}
		else if (secondRoll >= 13 && secondRoll <= 18) {stellarMass = 1.35;}
	}

	else if (firstRoll == 6)
	{
		if 		(secondRoll >= 3  && secondRoll <= 7 ) {stellarMass = 1.30;}
		else if (secondRoll >= 8  && secondRoll <= 9 ) {stellarMass = 1.25;}
		else if (secondRoll == 10					 ) {stellarMass = 1.20;}
		else if (secondRoll >= 11 && secondRoll <= 12) {stellarMass = 1.15;}
		else if (secondRoll >= 13 && secondRoll <= 18) {stellarMass = 1.10;}
	}

	else if (firstRoll == 7)
	{
		if		(secondRoll >= 3  && secondRoll <= 7 ) {stellarMass = 1.05;}
		else if (secondRoll >= 9  && secondRoll <= 9 ) {stellarMass = 1.00;}
		else if (secondRoll == 10					 ) {stellarMass = 0.95;}
		else if (secondRoll >= 11 && secondRoll <= 12) {stellarMass = 0.90;}
		else if (secondRoll >= 13 && secondRoll <= 18) {stellarMass = 0.85;}
	}

	else if (firstRoll == 8)
	{
		if 		(secondRoll >= 3  && secondRoll <= 7 ) {stellarMass = 0.80;}
		else if (secondRoll >= 8  && secondRoll <= 9 ) {stellarMass = 0.75;}
		else if (secondRoll == 10					 ) {stellarMass = 0.70;}
		else if (secondRoll >= 11 && secondRoll <= 12) {stellarMass = 0.65;}
		else if (secondRoll >= 13 && secondRoll <= 18) {stellarMass = 0.60;}
	}

	else if (firstRoll == 9)
	{
		if		(secondRoll >= 3  && secondRoll <= 8 ) {stellarMass = 0.55;}
		else if (secondRoll >= 9  && secondRoll <= 11) {stellarMass = 0.50;}
		else if (secondRoll >= 12 && secondRoll <= 18) {stellarMass = 0.45;}
	}

	else if (firstRoll == 10)
	{
		if		(secondRoll >= 3  && secondRoll <= 8 ) {stellarMass = 0.40;}
		else if (secondRoll >= 9  && secondRoll <= 11) {stellarMass = 0.35;}
		else if (secondRoll >= 12 && secondRoll <= 18) {stellarMass = 0.30;}
	}

	else if (firstRoll == 11)
	{
		stellarMass = 0.25;
	}

	else if (firstRoll == 12)
	{
		stellarMass = 0.20;
	}

	else if (firstRoll == 13)
	{
		stellarMass = 0.15;
	}

	else
	{
		stellarMass = 0.10;
	}

//	Add the variance
	stellarMass = stellarMass + (stellarMass * variance);
	return stellarMass;
}
