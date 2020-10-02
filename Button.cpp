#include "Button.h"

Button::Button(QString name, int x, int y, enum Qt::GlobalColor newActiveColor, enum Qt::GlobalColor newInactiveColor) //define position, size, color, text of button
{
	activeColor = newActiveColor;
	inactiveColor = newInactiveColor;

	setRect(x, y, 100, 25);
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(newInactiveColor);
	setBrush(brush);

	text = new QGraphicsTextItem(name, this);
	//center text in middle of button
	int xPos = rect().width() / 2 - text->boundingRect().width() / 2;
	int yPos = rect().height() / 2 - text->boundingRect().height() / 2;
	text->setPos(xPos + x, yPos + y);

	//setAcceptHoverEvents(true);
}

void Button::setActiveColor() //change to bright color when clicked
{
	brush.setColor(activeColor);
	setBrush(brush);
}

void Button::setInactiveColor() //change to dark color when other buttons are clicked
{
	brush.setColor(inactiveColor);
	setBrush(brush);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent * event) //emit signal when button is clicked
{
	emit clicked();
}

//void Button::hoverEnterEvent(QGraphicsSceneHoverEvent * event)
//{
//	QBrush brush;
//	brush.setStyle(Qt::SolidPattern);
//	brush.setColor(Qt::cyan);
//	setBrush(brush);
//}
//
//void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent * event)
//{
//	QBrush brush;
//	brush.setStyle(Qt::SolidPattern);
//	brush.setColor(Qt::darkCyan);
//	setBrush(brush);
//}
