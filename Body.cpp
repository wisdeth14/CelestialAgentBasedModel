#include "Body.h"

Body::Body(CelestialKind type)
{
	pNext = NULL;
	xPos = 0;
	yPos = 0;
	destroyed = 0;

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	
	//randomly set color of widget based off Celestial type
	if (type == DWARF)
	{
		int num = rand() % 3;
		if (num == 0)
			brush.setColor(Qt::white);
		if (num == 1)
			brush.setColor(Qt::gray);
		if (num == 2)
			brush.setColor(Qt::darkGray);
	}

	if (type == PLANET)
	{
		int num = rand() % 4;
		if (num == 0)
			brush.setColor(Qt::blue);
		if (num == 1)
			brush.setColor(Qt::green);
		if (num == 2)
			brush.setColor(Qt::darkGreen);
		if (num == 3)
			brush.setColor(Qt::darkRed);
	}

	if (type == ORBIT)
	{
		int num = rand() % 4;
		if (num == 0)
			brush.setColor(Qt::blue);
		if (num == 1)
			brush.setColor(Qt::green);
		if (num == 2)
			brush.setColor(Qt::darkGreen);
		if (num == 3)
			brush.setColor(Qt::darkRed);
	}

	if (type == STAR)
	{
		int num = rand() % 3;
		if (num == 0)
			brush.setColor(Qt::yellow);
		if (num == 1)
			brush.setColor(Qt::red);
		if (num == 2)
			brush.setColor(Qt::magenta);
	}

	if (type == GIANT)
	{
		brush.setColor(Qt::cyan);
	}

	setBrush(brush);
}

Body * Body::getPNext()
{
	return pNext;
}

void Body::setPNext(Body * newPNext)
{
	pNext = newPNext;

}

void Body::setXPos(double newXPos)
{
	xPos = newXPos;
}

void Body::setYPos(double newYPos)
{
	yPos = newYPos;
}

double Body::getXPos()
{
	return xPos;
}

double Body::getYPos()
{
	return yPos;
}

int Body::getDestroyed()
{
	return destroyed;
}

void Body::setDestroyed(int newDestroyed)
{
	destroyed = newDestroyed;
}

void Body::move()
{
	QRectF r((int)(xPos / 10000000000) - (rect().width() /2), (int)(yPos / 10000000000) - (rect().height() /2), rect().width(), rect().height());
	setRect(r);
}

//Celestial * Body::getBuddy()
//{
//	return buddy;
//}
//
//void Body::setBuddy(Celestial * newBuddy)
//{
//	buddy = newBuddy;
//}
