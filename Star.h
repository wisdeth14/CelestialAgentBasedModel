#ifndef STAR_H
#define STAR_H

#include "celestialagentmodel.h"
#include "Celestial.h"

//star inherited from Celestial
class Star : public Celestial
{

public:
	Star();
	void setPosition(double x, double y);
};

#endif
