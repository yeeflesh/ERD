#include "stdafx.h"
#include "Node.h"

Node::Node(char type, string name) :Component(type, name){}
vector<Connector*>Node::getConnectors(){ return this->connectors; }
void Node::addConnectors(Connector* connector){ this->connectors.push_back(connector); }
//void Node::connectTo(Component* c1){}

/*two Nodes's connection should be diff type
* e.g. Entity <--> Entity = false
*	    Entity <--> Attribute = true
*/
bool Node::canConnectTo(Component* component1){
	int tId = this->getId();
	int cId = component1->getId();

	if (tId == cId){ //itself
		printf("The node '%d' cannot be connected to itself.\n", tId);
		return false;
	}
	else {
		if (this->getType() == component1->getType()){ //same type
			printf("The node '%d' cannot be connected by the node '%d'.\n", tId, cId);
			return false;
		}
		else{ //has already been connected
			int sId = min(tId, cId);
			int bId = max(tId, cId);
			for (Connector* connector : this->connectors){
				Component* conn0 = connector->getConnection()[0];
				Component* conn1 = connector->getConnection()[1];
				if (conn0->getId() == sId && conn1->getId() == bId) {//increasing
					printf("The node '%d' has already been connected to component '%d'.\n", tId, cId);
					return false; 
				}
				//if (conn1->getId() == tId && conn0->getId() == cId) return false; //decreasing
			}
		}
	}
	return true;
}