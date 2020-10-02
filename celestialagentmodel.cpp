#include "celestialagentmodel.h"

CelestialAgentModel::CelestialAgentModel(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QGraphicsScene * scene = new QGraphicsScene(); //create scene
	//QGraphicsView * view = new QGraphicsView(scene); //allows visualization of scene
	

	QPushButton * addButton = new QPushButton("Add");
	scene->addWidget(addButton);
}

CelestialAgentModel::~CelestialAgentModel()
{

}
