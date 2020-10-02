#ifndef ORBIT_H
#define ORBIT_H

#include "celestialagentmodel.h"
#include "Celestial.h"
#include "Star.h"

//Orbit is the most unique Celestial type (inherited from Celestial)
//when placed in the system, it automatically finds the nearest Star to orbit, and sets its initial velocity accordingly so that it will perfectly orbit that Star in a circle
//however, due to real-time processing limitations, the Orbit object will not stay in perfect orbit, despite having the proper initial velocity
//to overcome this, a Thread is used to constantly check the position/velocity of the Orbit object and force it back into its orbital path
//since we still want the Orbit object to break its orbital path if a dominant force is introduced into the system, if the Orbit object's error from its orbital path exceeds a certain threshold it will no longer be forced into orbit
class Orbit : public Celestial
{

public:
	Orbit();
	void setPosition(double x, double y);
	void setRadius(double newRadius);
	void setAcc(double newAcc);
	void setError(double newError);
	void setInOrbit(bool newInOrbit);

	double getRadius();
	double getAcc();
	double getError();
	bool getInOrbit();
	Star * getStar();

	void setStar(Star * newStar);
	void calculateVelocity(); //establishes initial velocity of Orbit type based off distance from Star/Giant

private:
	Star * star; //pointer to start the Orbit object is orbiting
	double radius; //radius of orbit from the Star
	double acc; //acceleration magnitude that Orbit should constantly have with respect to Star it orbits
	double error; //degree of error of actual acceleration vs orbital acceleration
	bool inOrbit; //boolean to state whether or not Orbit object should stay in orbit of star
};

#endif
