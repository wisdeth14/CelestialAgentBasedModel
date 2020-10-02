#include "Dwarf.h"

Dwarf::Dwarf()
{
	setMass(5.97 * pow(10, 24));
	setXVel(0);
	setYVel(0);

	setType(DWARF);
}

void Dwarf::setPosition(double x, double y)
{
	setXPos(x * 10000000000);
	setYPos(y * 10000000000);
}
