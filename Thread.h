#ifndef THREAD_H
#define THREAD_H

#include "celestialagentmodel.h"
#include "System.h"
#include "SystemVirtual.h"

class Thread : public QThread
{
	//Q_OBJECT

public:
	Thread(int newAction, System * newSystem, SystemVirtual * newSystemVirtual, QGraphicsScene * newScene, QTimer * newTimer);
	void run(); //default function of QThread class that user defines, function will be defined based off action

private:
	int action;
	System * system;
	SystemVirtual * systemVirtual;
	QGraphicsScene * scene;
	QTimer * timer;

};

#endif
