#include "Thread.h"

Thread::Thread(int newAction, System * newSystem, SystemVirtual * newSystemVirtual, QGraphicsScene * newScene, QTimer * newTimer)
{
	action = newAction;
	system = newSystem;
	systemVirtual = newSystemVirtual;
	scene = newScene;
}

void Thread::run()
{
	QMutex mutex;
	if (action == 1) //detect for any collisions between widgets and mark accordingly as destroyed
	{
		mutex.lock();
		system->detectCollision(systemVirtual, scene);
		//wait();
		mutex.unlock();
		//msleep(1);
	}
	if (action == 2) //process and calculate new acceleration for every Celestial Object based off distance from every other Object
	{
		mutex.lock();
		system->process();
		mutex.unlock();
	}
	else if (action == 3) //traverse through Celestial Object linked list and update position and velocity of each object
	{
		mutex.lock();
		system->traverse();
		mutex.unlock();
	}
	else if (action == 4) //error correct Orbit object's orbital path, allow to leave orbit if error is too great
	{
		mutex.lock();
		system->adjust(); 
		mutex.unlock();
	}
	else if (action == 5) //update the position of each Object's graphical position in virtual system based off its actual position in system
	{
		mutex.lock();
		system->transfer(systemVirtual);
		mutex.unlock();
	}
}
