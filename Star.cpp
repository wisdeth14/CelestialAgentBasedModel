#include "Star.h"

Star::Star()
{
	setMass(1.99 * 99.9 * pow(10, 30));
	setXVel(0);
	setYVel(0);

	setType(STAR);
}

void Star::setPosition(double x, double y)
{
	setXPos(x * 10000000000);
	setYPos(y * 10000000000);
}
