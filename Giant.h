#ifndef GIANT_H
#define GIANT_H

#include "celestialagentmodel.h"
#include "Celestial.h"
#include "Star.h"

//immovable Star inherited from Celestial
class Giant : public Star
{

public:
	Giant();
	void setPosition(double x, double y);
};

#endif
