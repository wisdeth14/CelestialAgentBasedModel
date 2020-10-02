#ifndef CELESTIAL_H
#define CELESTIAL_H

#include "celestialagentmodel.h"
#include "Body.h"

class Celestial
{

public:
	Celestial();

	double getMass();
	double getXPos();
	double getYPos();
	double getXAcc();
	double getYAcc();
	CelestialKind getType();

	void setMass(double newMass);
	void setXPos(double newXPos);
	void setYPos(double newYPos);
	void setXVel(double newXVel);
	void setYVel(double newYVel);
	void setXAcc(double newXAcc);
	void setYAcc(double newYAcc);
	void setType(CelestialKind newType);

	Celestial * getPNext();
	void setPNext(Celestial *newPNext);
	int getMarker();
	void setMarker(int newMarker);
	int getDestroyed();
	void setDestroyed(int newDestroyed);

	void calculate(Celestial * other);

	void move();

	Body * getBuddy();
	void setBuddy(Body * newBuddy);

protected:
	//mass, velocity, and acceleration values
	double mass;
	double xPos;
	double yPos;
	double xVel;
	double yVel;
	double xAcc;
	double yAcc;

	Celestial *pNext; //pointer to next Celestial object in the linked list
	int marker;
	CelestialKind type; //Celestial object enumerated type 
	int destroyed; //value to check if Celestial Object should be destroyed

	Body * buddy; //pointer to the graphical widget associated with each Celestial ojbect in the system
};

#endif
