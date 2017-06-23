#ifndef ERMODEL_H
#define ERMODEL_H

#include "Component.h"

class ERModel
{
private:
	map<int, Component*> components;
public:
	void addComponent();
	map<int,  Component*>& getComponents();
	void drawComponent();
	void drawConnections();	
	void drawTable();
};

#endif