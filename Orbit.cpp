#include "Orbit.h"

Orbit::Orbit()
{
	setMass(1.90 * pow(10, 27));
	setXVel(0);
	setYVel(0);

	setType(ORBIT);
	star = NULL;
	radius = 0;
	error = 0;
}

void Orbit::setPosition(double x, double y)
{
	setXPos(x * 10000000000);
	setYPos(y * 10000000000);
}

void Orbit::setRadius(double newRadius)
{
	radius = newRadius;
}

void Orbit::setAcc(double newAcc)
{
	acc = newAcc;
}

void Orbit::setError(double newError)
{
	error = newError;
}

void Orbit::setInOrbit(bool newInOrbit)
{
	inOrbit = newInOrbit;
}

double Orbit::getRadius()
{
	return radius;
}

double Orbit::getAcc()
{
	return acc;
}

double Orbit::getError()
{
	return error;
}

bool Orbit::getInOrbit()
{
	return inOrbit;
}

Star * Orbit::getStar()
{
	return star;
}

void Orbit::setStar(Star * newStar)
{
	star = newStar;
}

void Orbit::calculateVelocity() //establishes initial velocity of Orbit type based off distance from Star/Giant
{
	if (star != NULL)
	{
		double distance = sqrt(pow(this->getXPos() - star->getXPos(), 2) + pow(this->getYPos() - star->getYPos(), 2));
		double velocityMagnitude = sqrt((6.674 * pow(10, -11) * star->getMass()) / distance); //velocity calculated by setting centriptal force = gravitational force
		double acc = 6.674 * pow(10, -11) * star->getMass() / pow(distance, 2);
		setRadius(distance); //radius used as measurement of error for adjusting orbital path
		setAcc(acc); //acceleration used as measure of error from orbital path
		double theta = atan2(this->getYPos() - star->getYPos(), this->getXPos() - star->getXPos());
		setXVel(cos((PI / 2) - theta) * velocityMagnitude);
		setYVel(sin((PI / 2) - theta) * -1 * velocityMagnitude);
	}
}
