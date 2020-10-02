#include "SystemVirtual.h"

SystemVirtual::SystemVirtual()
{
	pHead = NULL;
	count = 0;
}

Body * SystemVirtual::getPHead()
{
	return pHead;
}

void SystemVirtual::setPHead(Body * newPHead)
{
	pHead = newPHead;
}

int SystemVirtual::getCount()
{
	return count;
}

void SystemVirtual::setCount(int newCount)
{
	count = newCount;
}

void SystemVirtual::addBody(Body * body) //add new widget to linked list
{
	if (count < 20)
	{
		body->setPNext(pHead); //celestial->pNext = pHead;
		pHead = body;
		count++;
	}
}

void SystemVirtual::traverse()
{
	QMutex mutex;
	mutex.lock();
	//qDebug() << "5start"; //really 6 start
	Body *pTemp;
	pTemp = pHead;
	while (pTemp != NULL)
	{
		pTemp->move();
		pTemp = pTemp->getPNext(); //pTemp = pTemp->pNext
	}
	mutex.unlock();
	//qDebug() << "5stop";
}

void SystemVirtual::destroySystem()
{
	QMutex mutex;
	mutex.lock();
	QThread::yieldCurrentThread(); //"Yields execution of the current thread to another runnable thread, if any. Note that the operating system decides to which thread to switch."
	destroy(pHead);
	pHead = NULL;
	count = 0;
	mutex.unlock();
}

void SystemVirtual::destroy(Body * body) //iterate through linked list to destroy each Body widget
{
	if (body != NULL)
	{
		destroy(body->getPNext());
		delete body;
	}
}

Body * SystemVirtual::destroyBody(Body * body, Body * pCur) //delete Body widget from linked list
{
	if (pCur == NULL)
	{
		return NULL;
	}
	if (pCur == body)
	{
		Body * pTemp = pCur->getPNext();
		delete pCur;
		return pTemp;
	}
	pCur->setPNext(destroyBody(body, pCur->getPNext()));
	return pCur;
}