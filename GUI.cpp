#include "GUI.h"

GUI::GUI() //GUI initialization
{
	action = NONE; //no Celestial objects initially selected
	//set color and size of GUI QObject, add GUI to scene, display full scene to view
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::black);
	setBrush(brush);
	setRect(0, 0, 900, 900);
	scene->addItem(this);
	view->show();
	view->setFixedSize(900, 900);
	scene->setSceneRect(0, 0, 900, 900);
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	//establish all the buttons within the GUI
	Button * dwarf = new Button(QString("Dwarf"), 0, 875, Qt::cyan, Qt::darkCyan);
	Button * planet = new Button(QString("Planet"), 100, 875, Qt::cyan, Qt::darkCyan);
	Button * orbit = new Button(QString("Orbit"), 200, 875, Qt::cyan, Qt::darkCyan);
	Button * star = new Button(QString("Star"), 300, 875, Qt::cyan, Qt::darkCyan);
	Button * giant = new Button(QString("Blue Giant"), 400, 875, Qt::cyan, Qt::darkCyan);	

	Button * reset = new Button(QString("Reset"), 600, 875, Qt::white, Qt::white);
	Button * start = new Button(QString("Start"), 700, 875, Qt::green, Qt::darkGreen);
	Button * stop = new Button(QString("Stop"), 800, 875, Qt::red, Qt::darkRed);
	
	//add all buttons to the scene
	start->setActiveColor();
	scene->addItem(dwarf);
	scene->addItem(planet);
	scene->addItem(orbit);
	scene->addItem(star);
	scene->addItem(giant);	

	scene->addItem(reset);
	scene->addItem(start);
	scene->addItem(stop);

	timer->start(25); //timer begins to run and emits signal every 25ms

	//create threads to independently handle different processes
	//allow the scene, system, virtual system to be managed by the thread, the timer to control the thread, and assign each thread a different action value
	Thread * thread1 = new Thread(1, &system, &systemVirtual, scene, timer); //detect for any collisions between widgets and mark accordingly as destroyed
	Thread * thread2 = new Thread(2, &system, &systemVirtual, scene, timer); //process and calculate new acceleration for every Celestial Object based off distance from every other Object
	Thread * thread3 = new Thread(3, &system, &systemVirtual, scene, timer); //traverse through Celestial Object linked list and update position and velocity of each object
	Thread * thread4 = new Thread(4, &system, &systemVirtual, scene, timer); //error correct Orbit object's orbital path, allow to leave orbit if error is too great
	Thread * thread5 = new Thread(5, &system, &systemVirtual, scene, timer); //update the position of each Object's graphical position in virtual system based off its actual position in system, still need to use setRect to change actual display of the widget
	
	connect(timer, SIGNAL(timeout()), thread1, SLOT(start()));
	connect(timer, SIGNAL(timeout()), thread2, SLOT(start()));
	connect(timer, SIGNAL(timeout()), thread3, SLOT(start()));
	connect(timer, SIGNAL(timeout()), thread4, SLOT(start()));
	connect(timer, SIGNAL(timeout()), thread5, SLOT(start()));
	connect(timer, SIGNAL(timeout()), &systemVirtual, SLOT(traverse())); //complete actions from thread 5 and move Widgets through setRect
	connect(timer, SIGNAL(timeout()), this, SLOT(removeSpecificItems())); //remove items marked as destroyed

	connect(reset, SIGNAL(clicked()), timer, SLOT(stop())); //stop timer when reset is clicked to allow for proper processing without interference from threads
	connect(reset, SIGNAL(clicked()), this, SLOT(removeItems())); //completely remove all objects within the system
	//reset removeItems functions stops then starts timer
	connect(reset, SIGNAL(clicked()), start, SLOT(setActiveColor()));
	connect(reset, SIGNAL(clicked()), stop, SLOT(setInactiveColor()));

	//clicking start and stop will turn on and off the timer, this will turn and off threads and other proccessing actions
	connect(start, SIGNAL(clicked()), timer, SLOT(start()));
	connect(stop, SIGNAL(clicked()), timer, SLOT(stop()));

	//set action for when button is clicked
	connect(dwarf, SIGNAL(clicked()), this, SLOT(setActionDwarf()));
	connect(planet, SIGNAL(clicked()), this, SLOT(setActionPlanet()));
	connect(orbit, SIGNAL(clicked()), this, SLOT(setActionOrbit()));
	connect(star, SIGNAL(clicked()), this, SLOT(setActionStar()));
	connect(giant, SIGNAL(clicked()), this, SLOT(setActionGiant()));

	//change color of buttons
	connect(dwarf, SIGNAL(clicked()), dwarf, SLOT(setActiveColor()));
	connect(dwarf, SIGNAL(clicked()), planet, SLOT(setInactiveColor()));
	connect(dwarf, SIGNAL(clicked()), orbit, SLOT(setInactiveColor()));
	connect(dwarf, SIGNAL(clicked()), star, SLOT(setInactiveColor()));
	connect(dwarf, SIGNAL(clicked()), giant, SLOT(setInactiveColor()));

	connect(planet, SIGNAL(clicked()), dwarf, SLOT(setInactiveColor()));
	connect(planet, SIGNAL(clicked()), planet, SLOT(setActiveColor()));
	connect(planet, SIGNAL(clicked()), orbit, SLOT(setInactiveColor()));
	connect(planet, SIGNAL(clicked()), star, SLOT(setInactiveColor()));
	connect(planet, SIGNAL(clicked()), giant, SLOT(setInactiveColor()));

	connect(orbit, SIGNAL(clicked()), dwarf, SLOT(setInactiveColor()));
	connect(orbit, SIGNAL(clicked()), planet, SLOT(setInactiveColor()));
	connect(orbit, SIGNAL(clicked()), orbit, SLOT(setActiveColor()));
	connect(orbit, SIGNAL(clicked()), star, SLOT(setInactiveColor()));
	connect(orbit, SIGNAL(clicked()), giant, SLOT(setInactiveColor()));

	connect(star, SIGNAL(clicked()), dwarf, SLOT(setInactiveColor()));
	connect(star, SIGNAL(clicked()), planet, SLOT(setInactiveColor()));
	connect(star, SIGNAL(clicked()), orbit, SLOT(setInactiveColor()));
	connect(star, SIGNAL(clicked()), star, SLOT(setActiveColor()));
	connect(star, SIGNAL(clicked()), giant, SLOT(setInactiveColor()));

	connect(giant, SIGNAL(clicked()), dwarf, SLOT(setInactiveColor()));
	connect(giant, SIGNAL(clicked()), planet, SLOT(setInactiveColor()));
	connect(giant, SIGNAL(clicked()), orbit, SLOT(setInactiveColor()));
	connect(giant, SIGNAL(clicked()), star, SLOT(setInactiveColor()));
	connect(giant, SIGNAL(clicked()), giant, SLOT(setActiveColor()));	

	connect(start, SIGNAL(clicked()), start, SLOT(setActiveColor()));
	connect(start, SIGNAL(clicked()), stop, SLOT(setInactiveColor()));
	connect(stop, SIGNAL(clicked()), stop, SLOT(setActiveColor()));
	connect(stop, SIGNAL(clicked()), start, SLOT(setInactiveColor()));
}

void GUI::mousePressEvent(QGraphicsSceneMouseEvent *event) //when mouse (scene) is clicked, create Object/widget, set initial positions, add some Objects/widgets based off Celestial type
{
	//QPointF position = event->pos();
	//save position of mouse in the scene when it is clicked
	int x = event->pos().x();
	int y = event->pos().y();

	//created dashed white line which is added to the scene
	QPen pen;
	pen.setColor(Qt::white);
	pen.setStyle(Qt::DashLine);
	QGraphicsLineItem * line = new QGraphicsLineItem();
	line->setPen(pen);
	scene->addItem(line);
	setLine(line);

	//QMutex mutex;
	//mutex.lock();

	if (system.getCount() < 20)
	{
		//for each Celestial Object type, create new Ojbect, create new graphics widget for that Object, and link object to the widget
		//then set the position of the Object, define it's shape based off Celestial type, and add the widget to the scene
		//for Orbit and Giant type, immediately add to Object and Widget to linked lists as they cannot be given initial velocities (other types to be added upon mouse release)
		//lastly mark the pointer to the current Celestial Object and widget being operated on for future mouse processing
		if (action == DWARF)
		{
			Dwarf * celestial = new Dwarf();
			Body * body = new Body(DWARF);
			//body->setBuddy(celestial);
			celestial->setBuddy(body);

			body->setRect(x - 3, y - 3, 6, 6); //sets size of widget based off Celestial type
			celestial->setXPos(x * 10000000000);
			celestial->setYPos(y * 10000000000);

			scene->addItem(body);

			setCreation(celestial);
			setBody(body);
		}

		if (action == PLANET)
		{
			Planet * celestial = new Planet();
			Body * body = new Body(PLANET);
			//body->setBuddy(celestial);
			celestial->setBuddy(body);

			body->setRect(x - 5, y - 5, 10, 10);
			celestial->setXPos(x * 10000000000);
			celestial->setYPos(y * 10000000000);

			scene->addItem(body);

			setCreation(celestial);
			setBody(body);
		}

		if (action == ORBIT)
		{
			Orbit * celestial = new Orbit();
			Body * body = new Body(ORBIT);
			//body->setBuddy(celestial);
			celestial->setBuddy(body);

			body->setRect(x - 5, y - 5, 10, 10);
			celestial->setXPos(x * 10000000000);
			celestial->setYPos(y * 10000000000);


			system.addCelestial(celestial);
			systemVirtual.addBody(body);
			scene->addItem(body);

			system.findStar(celestial); //find nearest star in system for Orbit type to begin orbitting
			celestial->calculateVelocity(); //establishes initial velocity of Orbit type based off distance from Star/Giant
		}

		if (action == STAR)
		{
			Star * celestial = new Star();
			Body * body = new Body(STAR);
			//body->setBuddy(celestial);
			celestial->setBuddy(body);

			body->setRect(x - 10, y - 10, 20, 20);
			celestial->setXPos(x * 10000000000);
			celestial->setYPos(y * 10000000000);

			scene->addItem(body);

			setCreation(celestial);
			setBody(body);
		}

		if (action == GIANT)
		{
			Giant * celestial = new Giant();
			Body * body = new Body(GIANT);
			//body->setBuddy(celestial);
			celestial->setBuddy(body);

			body->setRect(x - 13, y - 13, 26, 26);
			celestial->setXPos(x * 10000000000);
			celestial->setYPos(y * 10000000000);

			system.addCelestial(celestial);
			systemVirtual.addBody(body);
			scene->addItem(body);
		}
	}
	//mutex.unlock();
}

void GUI::mouseMoveEvent(QGraphicsSceneMouseEvent * event) //when mouse is dragged, move line to represent initial velocity
{
	//ADD LINE MEMBER TO DWARF PLANET AND STAR
	if ((action == DWARF || action == PLANET || action == STAR) && system.getCount() < 20) //only these Celestial objects can be given initial velocities
	{
		Celestial * celestial = getCreation(); //get Object currently being added to reference it's position which was set when mouse was clicked
		QPointF position = event->pos(); //a Qt vector
		//set the line from the point where mouse was clicked to point opposite of where mouse is being dragged
		int x1 = celestial->getXPos() / 10000000000;
		int y1 = celestial->getYPos() / 10000000000;
		int x2 = (celestial->getXPos() / 10000000000) - (position.x() - (celestial->getXPos() / 10000000000));
		int y2 = (celestial->getYPos() / 10000000000) - (position.y() - (celestial->getYPos() / 10000000000));

		getLine()->setLine(x1, y1, x2, y2);
	}
}

void GUI::mouseReleaseEvent(QGraphicsSceneMouseEvent * event) //when mouse is released, set initial velocities and add rest of Objects/widgets
{
	QMutex mutex;
	if ((action == DWARF || action == PLANET || action == STAR) && system.getCount() < 20)
	{
		mutex.lock();
		QPointF position = event->pos();
		Celestial * celestial = getCreation();
		Body * body = getBody();
		celestial->setXVel(.0000001 * (celestial->getXPos() - (double)(position.x() * 10000000000)));
		celestial->setYVel(.0000001 * (celestial->getYPos() - (double)(position.y() * 10000000000)));
		system.addCelestial(celestial);
		systemVirtual.addBody(body);

		scene->removeItem(line);
		delete line;
		mutex.unlock();
	}
}

void GUI::setCreation(Celestial * newCreation)
{
	creation = newCreation;
}

void GUI::setBody(Body * newBody)
{
	body = newBody;
}

Celestial * GUI::getCreation()
{
	return creation;
}

Body * GUI::getBody()
{
	return body;
}

void GUI::setLine(QGraphicsLineItem * newLine)
{
	line = newLine;
}

QGraphicsLineItem * GUI::getLine()
{
	return line;
}


void GUI::setActionDwarf()
{
	action = DWARF;
}

void GUI::setActionPlanet()
{
	action = PLANET;
}

void GUI::setActionOrbit()
{
	action = ORBIT;
}

void GUI::setActionStar()
{
	action = STAR;
}

void GUI::setActionGiant()
{
	action = GIANT;
}

void GUI::removeItems() //destroy entire system/virtual system when reset is selected
{
	QMutex mutex;
	mutex.lock();
	Sleep(50);
	Body * pTemp = systemVirtual.getPHead();
	while (pTemp != NULL)
	{
		scene->removeItem(pTemp);
		pTemp = pTemp->getPNext(); //pTemp = pTemp->pNext
	}
	systemVirtual.destroySystem();
	system.destroySystem();
	system.setDestroyedCount(0);
	timer->start();

	mutex.unlock();
}

void GUI::removeSpecificItems() //destroy Celestial objects and their widgets which are marked as destroyed at the output of the timer
{
	qDebug() << "destroyed count: " << system.getDestroyedCount();
	QMutex mutex;
	mutex.lock();
	jump:
	if (system.getDestroyedCount() != 0)
	{
		timer->stop();
		Sleep(50); //pause to ensure no interference with threads when removing from system
		Celestial *pTemp;
		pTemp = system.getPHead();
		while (pTemp != NULL)
		{
			if (pTemp->getDestroyed() == 1)
			{
				scene->removeItem(pTemp->getBuddy());
				systemVirtual.setPHead(systemVirtual.destroyBody(pTemp->getBuddy(), systemVirtual.getPHead())); //destroys Body widget
				system.setPHead(system.destroyCelestial(pTemp, system.getPHead())); //destroy Celestial object
				system.setDestroyedCount(system.getDestroyedCount() - 1); //update amount of Objects that still need to be destroyed
				goto jump;
			}
			pTemp = pTemp->getPNext();
		}
		qDebug() << " ";

	}
	timer->start();
	mutex.unlock();
}
