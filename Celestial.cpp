#include "Celestial.h"

Celestial::Celestial()
{
	pNext = NULL;
	mass = 0;
	xVel = 0;
	yVel = 0;
	xAcc = 0;
	yAcc = 0;

	buddy = NULL;

	marker = 0;
	destroyed = 0;
}

void Celestial::move() //update position and velocity based off the previously calculated acceleration for each object
{
	if (type != GIANT)
	{
		int time = 500000; //aribtary value for optimal performance/visualization within scene
		//delta d = v * t + 0.5 * a * t^2
		double deltaX = (xVel * time) + (.5 * xAcc * time * time);
		double deltaY = (yVel * time) + (.5 * yAcc * time * time);
		//new position = old position + delta d
		xPos += deltaX;
		yPos += deltaY;
		//v = a * t
		xVel += xAcc * time;
		yVel += yAcc * time;
	}
}

Body * Celestial::getBuddy()
{
	return buddy;
}

void Celestial::setBuddy(Body * newBuddy)
{
	buddy = newBuddy;
}

void Celestial::calculate(Celestial * other) //calculate every pTempInner's acceleration relative to pTemp
{
	if (type != GIANT) //Giant type will not move
	{
		//calculate distance and angle of other Celestial object
		double distance = sqrt(pow(other->getXPos() - xPos, 2) + pow(other->getYPos() - yPos, 2));
		double theta = atan2(other->getYPos() - yPos, other->getXPos() - xPos);
		//calculate acceleration Object should experience based off F = ma = G * m1 * m2 / d^2
		double acc = 6.674 * pow(10, -11) * other->getMass() / pow(distance, 2);
		//add calculated acceleration to current value (sum of forces is additive)
		xAcc += acc * cos(theta);
		yAcc += acc * sin(theta);
	}
}

double Celestial::getMass()
{
	return mass;
}

double Celestial::getXPos()
{
	return xPos;
}

double Celestial::getYPos()
{
	return yPos;
}

double Celestial::getXAcc()
{
	return xAcc;
}

double Celestial::getYAcc()
{
	return yAcc;
}

CelestialKind Celestial::getType()
{
	return type;
}

void Celestial::setMass(double newMass)
{
	mass = newMass;
}

void Celestial::setXPos(double newXPos)
{
	xPos = newXPos;
}

void Celestial::setYPos(double newYPos)
{
	yPos = newYPos;
}

void Celestial::setXVel(double newXVel)
{
	xVel = newXVel;
}

void Celestial::setYVel(double newYVel)
{
	yVel = newYVel;
}

void Celestial::setXAcc(double newXAcc)
{
	xAcc = newXAcc;
}

void Celestial::setYAcc(double newYAcc)
{
	yAcc = newYAcc;
}

void Celestial::setType(CelestialKind newType)
{
	type = newType;
}

Celestial * Celestial::getPNext()
{
	return pNext;
}

void Celestial::setPNext(Celestial *newPNext)
{
	pNext = newPNext;
}

int Celestial::getMarker()
{
	return marker;
}

void Celestial::setMarker(int newMarker)
{
	marker = newMarker;
}

int Celestial::getDestroyed()
{
	return destroyed;
}

void Celestial::setDestroyed(int newDestroyed)
{
	destroyed = newDestroyed;
}
