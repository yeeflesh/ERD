#ifndef NODE_H
#define NODE_H

#include "Component.h"
#include "Connector.h"

class Node : public Component
{
private:
	vector<Connector*> connectors;
public:
	Node(char type, string name = "");
	vector<Connector*> getConnectors();
	void addConnectors(Connector*);
	bool canConnectTo(Component*);
	virtual void connectTo(Component*) = 0;
	//void connectTo(Component*);
};

#endif