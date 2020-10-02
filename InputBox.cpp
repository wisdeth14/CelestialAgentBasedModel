#include "InputBox.h"

InputBox::InputBox()
{
	marker = 0;
	window.setWindowTitle("Celestial Properties");

	massBox.setMaximum(1000);
	xPosBox.setMaximum(1600);
	yPosBox.setMaximum(900);
	xVelBox.setMaximum(300);
	xVelBox.setMaximum(300);

	massBox.setSuffix(" kg");

	massLabel.setText("Enter mass:");
	xPosLabel.setText("Enter x position:");
	yPosLabel.setText("Enter y position:");
	xVelLabel.setText("Enter x velocity:");
	yVelLabel.setText("Enter y velocity:");

	ok.setText("OK");

	layout.addWidget(&massLabel, 0, 0);
	layout.addWidget(&xPosLabel, 0, 1);
	layout.addWidget(&yPosLabel, 0, 2);
	layout.addWidget(&xVelLabel, 0, 3);
	layout.addWidget(&yVelLabel, 0, 4);

	layout.addWidget(&massBox, 1, 0);
	layout.addWidget(&xPosBox, 1, 1);
	layout.addWidget(&yPosBox, 1, 2);
	layout.addWidget(&xVelBox, 1, 3);
	layout.addWidget(&yVelBox, 1, 4);

	layout.addWidget(&ok, 2, 4);

	window.setLayout(&layout);
	window.show();


	QObject::connect(&ok, SIGNAL(clicked()), &window, SLOT(close()));



	//delete window;
}

void InputBox::setMarker()
{
	marker = 1;
}

void InputBox::setMass()
{
	mass = massBox.value();
}

int InputBox::getMarker()
{
	return marker;
}

int InputBox::getMass()
{
	return mass;
}

//void InputBox::close()
//{
//	window.close();
//}
//
//void InputBox::okClicked()
//{
//
//}
