#include "stdafx.h"
#include "Entity.h"

Entity::Entity(string name) :Node('E', name){}

void Entity::connectTo(Component* node1){
	if (this->canConnectTo(node1)){
		if (node1->getType() == 'A'){//Attribute
			//make linked
			Connector* connector = new Connector();
			connector->connectTo(this);	connector->connectTo(node1);
			this->addConnectors(connector);	((Node*)node1)->addConnectors(connector);

			printf("The node '%d' has been connected to the node '%d'.\n", this->getId(), node1->getId());
			//drawConnection(connector);
		}
		else{//Relationship
			cout << "Enter the type of the cardinality:\n";
			cout << "[0]1 [1]N\n";
			cout << "> ";
			char inputCardinality;
			while (inputCardinality = _getche(),(inputCardinality != '0' && inputCardinality != '1')){
				cout << "\nplease enter '0' or '1' thanks.\n";		
				cout << "[0]1 [1]N\n";
				cout << "> ";
			}
			string cardinality = (inputCardinality == '0') ? "1" : "N";
			//make linked
			
			Connector* connector = new Connector(cardinality);
			connector->connectTo(this);	connector->connectTo(node1);
			this->addConnectors(connector);	((Node*)node1)->addConnectors(connector);

			printf("\nThe node '%d' has been connected to the node '%d'.\n", this->getId(), node1->getId());
			printf("Its cardinality of the relationship is '%s'.\n", cardinality.c_str());
		}
	}
}