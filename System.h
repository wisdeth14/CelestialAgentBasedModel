#ifndef SYSTEM_H
#define SYSTEM_H

#include "celestialagentmodel.h"
#include "Celestial.h"
#include "Planet.h"
#include "Orbit.h"
#include "Star.h"
#include "Dwarf.h"
#include "Giant.h"
#include "Button.h"
#include "InputBox.h"
#include "SystemVirtual.h"

class System : public QObject
{
	Q_OBJECT

public:
	System();
	
	Celestial * getPHead(); 
	void setPHead(Celestial * newPHead);

	void addCelestial(Celestial * celestial); //add new Celestial ojbect to linked list
	void findStar(Orbit * celestial); //determines Star/Giant that Orbit type Celestial ojbect should begin to orbit based off nearest distance, called when Orbit object is created
	Celestial * destroyCelestial(Celestial * celestial, Celestial * pCur); //delete Celestial object from linked list

	int getCount();

	int getDestroyedCount();
	void setDestroyedCount(int newDestroyedCount);


public slots :

	void detectCollision(SystemVirtual * systemVirtual, QGraphicsScene * scene); //detect for any collisions between widgets and mark accordingly as destroyed
	void process(); //process and calculate new acceleration for every Celestial Object based off distance from every other Object
	void traverse(); //traverse through Celestial Object linked list and update position and velocity of each object
	void adjust(); //error correct Orbit object's orbital path, allow to leave orbit if error is too great
	void transfer(SystemVirtual * systemVirtual); //update the position of each Object's graphical position in virtual system based off its actual position in system
	
	void destroySystem(); //calls destroy to destroy whole system
	void destroy(Celestial * celestial); //iterate through linked list to destroy each Body widget WHY IS THIS A SLOT?

	void createInput(); //function for debugging and application development

private:
	QGraphicsScene * scene = new QGraphicsScene(); //create scene
	QGraphicsView * view = new QGraphicsView(scene); //create view for the scene

	Celestial *pHead; //pointer to head of Celestial linked list

	int count; //number of Celestial objects in the system
	int destroyedCount; //track the number of ojbects that have been destroyed and need to be removed

};

#endif
