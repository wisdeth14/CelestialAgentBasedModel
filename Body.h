#ifndef BODY_H
#define BODY_H

#include "celestialagentmodel.h"
//#include "Celestial.h"

//circular graphical represenation of every Celestial object in the system
class Body : public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT

public:
	Body(CelestialKind type);

	Body * getPNext();
	void setPNext(Body *newPNext);
	void setXPos(double newXPos);
	void setYPos(double newYPos);

	double getXPos();
	double getYPos();

	int getDestroyed();
	void setDestroyed(int newDestroyed);

	void move();

	/*Celestial * getBuddy();
	void setBuddy(Celestial * newBuddy);*/


private:
	Body *pNext; //pointer to next widget in the linked list
	double xPos;
	double yPos;
	int destroyed;

	//Celestial * buddy;
};

#endif
