#ifndef INPUTBOX_H
#define INPUTBOX_H

#include "celestialagentmodel.h"

class InputBox //class for debugging and application development
{
public:
	InputBox();

	int getMarker();

	int getMass();

public slots:

	void setMarker();

	void setMass();
	
	/*QWidget window;
	QPushButton ok;

	void close();
	void okClicked();

signals:
	void clicked();*/

private:
	QWidget window;
	QGridLayout layout;

	QLabel massLabel;
	QLabel xPosLabel;
	QLabel yPosLabel;
	QLabel xVelLabel;
	QLabel yVelLabel;

	QSpinBox massBox;
	QSpinBox xPosBox;
	QSpinBox yPosBox;
	QSpinBox xVelBox;
	QSpinBox yVelBox;

	QPushButton ok;

	int marker;
	int mass;
};

#endif
