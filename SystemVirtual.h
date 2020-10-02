#ifndef SYSTEMVIRTUAL_H
#define SYSTEMVIRTUAL_H

#include "celestialagentmodel.h"
#include "Celestial.h"
#include "Planet.h"
#include "Orbit.h"
#include "Star.h"
#include "Dwarf.h"
#include "Giant.h"
#include "Button.h"
#include "InputBox.h"
#include "Body.h"
//#include "System.h"

class SystemVirtual : public QObject
{
	Q_OBJECT

public:
	SystemVirtual();

	Body * getPHead();
	void setPHead(Body * newPHead);

	int getCount();
	void setCount(int newCount);

	void addBody(Body * body); //add new widget to linked list

	Body * destroyBody(Body * body, Body * pCur); //delete Body widget from linked list

public slots:
	void traverse();

	void destroySystem(); //calls destroy to destroy whole system
	void destroy(Body * body); //iterate through linked list to destroy each Body widget


private:
	Body *pHead;
	int count;
};

#endif
