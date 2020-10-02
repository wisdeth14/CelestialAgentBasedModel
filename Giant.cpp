#include "Giant.h"

Giant::Giant()
{
	setMass(1.99 * 100 * pow(10, 30));
	setXVel(0);
	setYVel(0);

	setType(GIANT);
}

void Giant::setPosition(double x, double y)
{
	//setRect(x - 13, y - 13, 26, 26);
	setXPos(x * 10000000000);
	setYPos(y * 10000000000);
}
