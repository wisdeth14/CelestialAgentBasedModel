#ifndef DWARF_H
#define DWARF_H

#include "celestialagentmodel.h"
#include "Celestial.h"

//small planet inherited from Celestial
class Dwarf : public Celestial
{

public:
	Dwarf();
	void setPosition(double x, double y);
};

#endif
