#ifndef CELESTIALAGENTMODEL_H
#define CELESTIALAGENTMODEL_H

#include "ui_celestialagentmodel.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QObject>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <time.h>
#include <QPushButton>
#include <QGridLayout>
#include <QSpinBox>
#include <QLabel>
#include <QMouseEvent>
#include <QDrag>
#include <QGraphicsLineItem>
#include <QPen>
#include <QLinkedList>
#include <QThread>
#include <QMutex>
#include <QMetaType>
#include <QRectF>

#include <chrono>
#include <windows.h>

#define PI 3.141592

typedef enum CelestialKind //enumerated type for the 5 types of Celestial objects that can be created
{
	NONE, DWARF, PLANET, ORBIT, STAR, GIANT
} CelestialKind;

class CelestialAgentModel : public QMainWindow
{
	Q_OBJECT

public:
	CelestialAgentModel(QWidget *parent = 0);
	~CelestialAgentModel();

private:
	Ui::CelestialAgentModelClass ui;
};

#endif // CELESTIALAGENTMODEL_H
