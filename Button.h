#ifndef BUTTON_H
#define BUTTON_H

#include "celestialagentmodel.h"

class Button : public QObject, public QGraphicsRectItem //custom QObject widget class for click-responsive buttons
{
	Q_OBJECT

public:
	Button(QString name, int x, int y, enum Qt::GlobalColor newActiveColor, enum Qt::GlobalColor newInactiveColor); //define position, size, color, text of button
	
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	/*void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);*/

public slots:
	void setActiveColor(); //change to bright color when clicked
	void setInactiveColor(); //change to dark color when other buttons are clicked

signals:
	void clicked(); //emit signal when button is clicked

private:
	QGraphicsTextItem * text; //text to be displayed in QGraphicsScene
	QBrush brush; //class defines pattern fill of shapes drawn by QPainter, used to color the button
	//two types of colors for each button, based off what was last clicked
	enum Qt::GlobalColor activeColor;
	enum Qt::GlobalColor inactiveColor;


};

#endif
