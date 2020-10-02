#ifndef GUI_H
#define GUI_H

#include "celestialagentmodel.h"
#include "InputBox.h"
#include "System.h"
#include "SystemVirtual.h"
#include "Thread.h"
#include "Body.h"

class GUI : public QWidget, public QGraphicsRectItem //was using QObject
{
	Q_OBJECT //QObject allows communication of objects through connected slots and signals

public:
	GUI(); //GUI initialization

	void mousePressEvent(QGraphicsSceneMouseEvent *event); //when mouse (scene) is clicked, create Object/widget, set initial positions, add some Objects/widgets based off Celestial type
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event); //when mouse is dragged, move line to represent initial velocity
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event); //when mouse is released, set initial velocities and add rest of Objects/widgets

	void setCreation(Celestial * newCreation);
	void setBody(Body * newBody);
	Celestial * getCreation();
	Body * getBody();

	void setLine(QGraphicsLineItem * newLine);
	QGraphicsLineItem * getLine();

public slots:
	//set action for when button is clicked
	void setActionDwarf();
	void setActionPlanet();
	void setActionOrbit();
	void setActionStar();
	void setActionGiant();

	void removeItems(); //destroy entire system/virtual system when reset is selected
	void removeSpecificItems(); //destroy Celestial objects and their widgets which are marked as destoryed at the output of the timer
	
private:
	QGraphicsScene * scene = new QGraphicsScene(); //class provides surface for managing all objects
	QGraphicsView * view = new QGraphicsView(scene); //class provides means of displaying objects from a QGraphicsScene
	QDrag * drag = new QDrag(this); //class for click and drag functionality

	System system; //this class holds dynamic linked list of all Celestial objects in the system
	SystemVirtual systemVirtual; //this class holds dynamic linked list of the graphical widget of all Celestial objects in the system
	CelestialKind action; //stores what Celestial Object type is currently selected, in event user clicks then this Object type will appear
	Celestial * creation; //stores pointer to the Celestial object that is currently being added to the system
	Body * body; //stores pointer to the Celestial object widget that is currently being added to the scene
	QGraphicsLineItem * line; //QObject line for when objects are added with initial velocities

	QTimer * timer = new QTimer(); //timer class that emits signal and specified intervals, controls frequency of processing events in the system

};

#endif
