#ifndef PLANET_H
#define PLANET_H

#include "celestialagentmodel.h"
#include "Celestial.h"

//normal planet inherited from Celestial
class Planet : public Celestial
{

public:
	Planet();
	void setPosition(double x, double y);
};

#endif
