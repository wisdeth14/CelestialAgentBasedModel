/*
Celestial Agent Model
Designed by Ethan Wisdom
Summer 2016 Programming Project

Resources:
Abdullah Aghazadah (YouTube) C++ Qt Game Tutorial
Programming for Newbies (YouTube) Introduction to Qt C++ framework for Visual Studio 
VoidRealms (YouTube) C++ Qt Programming
Qt Documentation
*/

#include "celestialagentmodel.h"
#include "Celestial.h"
#include "System.h"
#include "GUI.h"
#include <chrono>

int main(int argc, char *argv[])
{
	srand((unsigned int) time (NULL));
	QApplication a(argc, argv);
	
	GUI gui;



	/*CelestialAgentModel w;
	w.show();*/
	return a.exec();
}
