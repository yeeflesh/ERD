#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "Component.h"

class Connector : public Component
{
private:
	Component* connection[2];
public:
	Connector(string name = "");
	Component** getConnection();
	bool canConnectTo(Component*);
	void connectTo(Component*);
};

#endif