#include "stdafx.h"
#include "Attribute.h"

Attribute::Attribute(string name) :Node('A', name){}
bool Attribute::getPrimary(){ return this->primary; }
void Attribute::setPrimary(bool primary) { this->primary = primary; }

void Attribute::connectTo(Component* node1){
	if (this->canConnectTo(node1)){
		//make linked
		Connector* connector = new Connector();
		connector->connectTo(this);	connector->connectTo(node1);
		this->addConnectors(connector);	((Node*)node1)->addConnectors(connector);

		printf("The node '%d' has been connected to the node '%d'.\n", this->getId(), node1->getId());
		//drawConnection(connector);
	}
}