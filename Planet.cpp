#include "Planet.h"

Planet::Planet()
{
	setMass(1.90 * pow(10, 27));
	setXVel(0);
	setYVel(0);

	setType(PLANET);
}

void Planet::setPosition(double x, double y)
{
	//setRect(x - 5, y - 5, 10, 10);
	setXPos(x * 10000000000);
	setYPos(y * 10000000000);
}
