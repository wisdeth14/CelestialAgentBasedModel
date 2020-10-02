#include "System.h"

System::System()
{
	pHead = NULL;
	count = 0;
	destroyedCount = 0;
}

Celestial * System::getPHead()
{
	return pHead;
}

void System::setPHead(Celestial * newPHead)
{
	pHead = newPHead;
}

void System::addCelestial(Celestial * celestial) //add new Celestial ojbect to linked list
{
	if (count < 20) //limit of 20 ojbects in system to avoid processing overload
	{
		celestial->setPNext(pHead); //celestial->pNext = pHead;
		pHead = celestial;
		count++;
	}
}

void System::findStar(Orbit * celestial) //determines Star/Giant that Orbit type Celestial ojbect should begin to orbit based off nearest distance, , called when Orbit object is created
{
	//first determine if there is a star present, if so temporarily assign orbit and save distance for future comparisons
	Celestial * pTemp;
	pTemp = pHead;
	double distance = -1;
	double smallestDistance;
	bool starExists = false;
	while (!starExists && pTemp != NULL)
	{
		if (pTemp->getType() == STAR || pTemp->getType() == GIANT) //if a star, calculate and set distance
		{
			distance = sqrt(pow(pTemp->getXPos() - celestial->getXPos(), 2) + pow(pTemp->getYPos() - celestial->getYPos(), 2));
			starExists = true;
			qDebug() << distance;
			celestial->setStar((Star *)pTemp); //assign star as Celestial object which is orbitted
		}
		pTemp = pTemp->getPNext();
	}

	//if there is a Star in the system, find and assign nearest Star to Orbit and mark InOrbit to true
	if (starExists)
	{
		celestial->setInOrbit(true);
		smallestDistance = distance;
		pTemp = pHead;
		//then find closest distance
		while (pTemp != NULL)
		{
			if (pTemp->getType() == STAR || pTemp->getType() == GIANT)
			{
				distance = sqrt(pow(pTemp->getXPos() - celestial->getXPos(), 2) + pow(pTemp->getYPos() - celestial->getYPos(), 2));
				if (distance < smallestDistance)
				{
					smallestDistance = distance;
					qDebug() << distance;
					celestial->setStar((Star *)pTemp);
				}
			}
			pTemp = pTemp->getPNext();
		}
	}	
}

//function from http://www.cs.bu.edu/teaching/cs112/spring-2000/linked-list-delete/
Celestial * System::destroyCelestial(Celestial * celestial, Celestial * pCur) //delete Celestial object from linked list
{
	if (pCur == NULL)
	{
		return NULL;
	}
	if (pCur == celestial)
	{
		Celestial * pTemp = pCur->getPNext(); //preserve link to next Celestial Object before destroying pCur
		delete pCur;
		return pTemp;
	}
	pCur->setPNext(destroyCelestial(celestial, pCur->getPNext()));
	return pCur;
}

int System::getCount()
{
	return count;
}

int System::getDestroyedCount()
{
	return destroyedCount;
}

void System::setDestroyedCount(int newDestroyedCount)
{
	destroyedCount = newDestroyedCount;
}

void System::destroySystem()
{
	QMutex mutex; //object so only this thread can be operating
	mutex.lock();
	destroy(pHead); //iterate through linked list to destroy each Body widget
	pHead = NULL;
	count = 0;
	mutex.unlock();
}

void System::traverse() //traverse through Celestial Object linked list and update position and velocity of each object
{
	qDebug() << "3start";
	Celestial *pTemp;
	pTemp = pHead;
	while (pTemp != NULL)
	{
		pTemp->move();
		pTemp = pTemp->getPNext(); //pTemp = pTemp->pNext
	}
	qDebug() << "3stop";
}

void System::createInput() //function for debugging and application development
{
	QWidget * window = new QWidget;
	window->setWindowTitle("Celestial Properties");
	QGridLayout * layout = new QGridLayout();

	QDoubleSpinBox * massBox = new QDoubleSpinBox();
	QDoubleSpinBox * xPosBox = new QDoubleSpinBox();
	QDoubleSpinBox * yPosBox = new QDoubleSpinBox();
	QDoubleSpinBox * xVelBox = new QDoubleSpinBox();
	QDoubleSpinBox * yVelBox = new QDoubleSpinBox();

	massBox->setMaximum(1000);
	xPosBox->setMaximum(1600);
	yPosBox->setMaximum(900);
	xVelBox->setRange(-1000000, 1000000);
	yVelBox->setRange(-1000000, 1000000);

	massBox->setSuffix(" x 10^30 kg");
	xPosBox->setSuffix(" million km");
	yPosBox->setSuffix(" million km");

	QLabel * massLabel = new QLabel("Enter mass:");
	QLabel * xPosLabel = new QLabel("Enter x position:");
	QLabel * yPosLabel = new QLabel("Enter y position:");
	QLabel * xVelLabel = new QLabel("Enter x velocity:");
	QLabel * yVelLabel = new QLabel("Enter y velocity:");

	QPushButton * ok = new QPushButton("OK");

	layout->addWidget(massLabel, 0, 0);
	layout->addWidget(xPosLabel, 0, 1);
	layout->addWidget(yPosLabel, 0, 2);
	layout->addWidget(xVelLabel, 0, 3);
	layout->addWidget(yVelLabel, 0, 4);

	layout->addWidget(massBox, 1, 0);
	layout->addWidget(xPosBox, 1, 1);
	layout->addWidget(yPosBox, 1, 2);
	layout->addWidget(xVelBox, 1, 3);
	layout->addWidget(yVelBox, 1, 4);

	layout->addWidget(ok, 2, 4);

	window->setLayout(layout);
	window->show();

	connect(massBox, SIGNAL(valueChanged(double)), this, SLOT(setMass(double)));
	connect(xPosBox, SIGNAL(valueChanged(double)), this, SLOT(setXPos(double)));
	connect(yPosBox, SIGNAL(valueChanged(double)), this, SLOT(setYPos(double)));
	connect(xVelBox, SIGNAL(valueChanged(double)), this, SLOT(setXVel(double)));
	connect(yVelBox, SIGNAL(valueChanged(double)), this, SLOT(setYVel(double)));

	connect(ok, SIGNAL(clicked()), window, SLOT(close()));
	connect(ok, SIGNAL(clicked()), this, SLOT(makeCelestial()));
}

void System::transfer(SystemVirtual * system) //update the position of each Object's graphical position in virtual system based off its actual position in system
{
	qDebug() << "5start";
	Celestial * pTemp;
	pTemp = pHead;
	while (pTemp != NULL)
	{
		pTemp->getBuddy()->setXPos(pTemp->getXPos());
		pTemp->getBuddy()->setYPos(pTemp->getYPos());
		pTemp = pTemp->getPNext();
	}
	qDebug() << "5stop";
}

void System::detectCollision(SystemVirtual * systemVirtual, QGraphicsScene * scene)
{
	using std::chrono::duration_cast;
	using std::chrono::milliseconds;
	typedef std::chrono::high_resolution_clock clock;

	auto start = clock::now();


	QMutex mutex;
	mutex.lock();
	
	qDebug() << "1start";
	Celestial *pTemp;
	Celestial *pTempInner;
	pTemp = pHead;
	//nested loop to check every object's position relative to every other object
	while (pTemp != NULL)
	{
		pTempInner = pHead;
		while (pTempInner != NULL)
		{
				//if pTemp and pTempInner occupy the same space and are not the same Object
				if ((pTemp->getBuddy()->collidesWithItem(pTempInner->getBuddy())) && (pTemp != pTempInner)) //collidesWithItem is QGraphicsItem function, QGraphicsItem checks if overlaps with another QGraphicsItem
				{
					//then if pTemp has less than or equal mass than pTempInner, then destroy pTemp
					if (pTemp->getMass() <= pTempInner->getMass())
					{
						qDebug() << "hit";
						//mark Celestial Object and widget as destroyed
						pTemp->setDestroyed(1);
						pTemp->getBuddy()->setDestroyed(1);
						//reduce the count of ojbects/widgets in the system/virtual system
						count--;
						systemVirtual->setCount(systemVirtual->getCount() - 1);
						setDestroyedCount(getDestroyedCount() + 1);

					}
				}
			pTempInner = pTempInner->getPNext();
		}
		pTemp = pTemp->getPNext(); //pTemp = pTemp->pNext		
	}
	jump:
	qDebug() << "1stop";
	mutex.unlock();

	auto end = clock::now();
	qDebug() << duration_cast<milliseconds>(end - start).count() << "ms\n";
}

void System::destroy(Celestial * celestial)
{
	if (celestial != NULL)
	{
		destroy(celestial->getPNext());
		celestial->setBuddy(NULL);
		//delete celestial->getBuddy();
		delete celestial;
	}
}

void System::process() //process and calculate new acceleration for every Celestial Object based off distance from every other Object
{
	qDebug() << "2start";
	Celestial *pTemp;
	Celestial *pTempInner;
	pTemp = pHead;
	//double loop to process every Celestial object with respect to every other celestial object
	//marker variable used so no Celestial object is processed against itself with the double loop
	while (pTemp != NULL)
	{
		pTemp->setMarker(1);
		//reset acceleration to 0
		pTemp->setXAcc(0);
		pTemp->setYAcc(0);
		pTempInner = pHead;
		while (pTempInner != NULL)
		{
			if (pTempInner->getMarker() != 1)
			{
				pTemp->calculate(pTempInner); //calculate every pTempInner's acceleration relative to pTemp
			}
			pTempInner = pTempInner->getPNext();
		}
		pTemp->setMarker(0);
		pTemp = pTemp->getPNext(); //pTemp = pTemp->pNext		
	}
	qDebug() << "2stop";
}

void System::adjust() //error correct Orbit object's orbital path, allow to leave orbit if error is too great
{
	qDebug() << "4start";
	Orbit *pTemp;
	pTemp = (Orbit *) pHead;
	while (pTemp != NULL)
	{
		if (pTemp->getType() == ORBIT)
		{
			//if InOrbit is true (object should still be orbitting), check distance and angle from star
			if (pTemp->getStar() != NULL && pTemp->getInOrbit()) //and orbit is true
			{
				double distance = sqrt(pow(pTemp->getStar()->getXPos() - pTemp->getXPos(), 2) + pow(pTemp->getStar()->getYPos() - pTemp->getYPos(), 2));
				double theta = atan2(pTemp->getYPos() - pTemp->getStar()->getYPos(), pTemp->getXPos() - pTemp->getStar()->getXPos());
				double displacement = distance - pTemp->getRadius(); //degree of error in distance from orbital path
				double velocityMagnitude = sqrt((6.674 * pow(10, -11) * pTemp->getStar()->getMass()) / distance);
				double accelerationMagnitude = sqrt(pow(pTemp->getXAcc(), 2) + pow(pTemp->getYAcc(), 2));

				//if actual acceleration is within 10% error
				if (accelerationMagnitude <= 1.1 * pTemp->getAcc() && accelerationMagnitude >= .9 * pTemp->getAcc()) //was using 10% error (0.1)
				{
					//adjust actual position by displacement from orbital path
					pTemp->setXPos(pTemp->getXPos() - (displacement * cos(theta)));
					pTemp->setYPos(pTemp->getYPos() - (displacement * sin(theta)));
					//reset velocity based off current angle from the Star
					pTemp->setXVel(cos((PI / 2) - theta) * velocityMagnitude);
					pTemp->setYVel(sin((PI / 2) - theta) * -1 * velocityMagnitude);
				}
				//otherwise, if actual acceleration is greater than 10% error, allow Orbit object to break from orbital path and behave on it's own
				else
				{
					pTemp->setInOrbit(false);
				}
				
			}
		}
		pTemp = (Orbit *) pTemp->getPNext();
	}
	qDebug() << "4start";
}
