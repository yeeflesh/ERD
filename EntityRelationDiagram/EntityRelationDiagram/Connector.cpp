#include "stdafx.h"
#include "Connector.h"

Connector::Connector(string name) :Component('C', name){
	connection[0] = NULL;
	connection[1] = NULL;
}
Component** Connector::getConnection(){ return this->connection; }

bool Connector::canConnectTo(Component* component1){
	//has been connected
	if (this->connection[0] != NULL && this->connection[1] != NULL){ return false; }
	//same type
	else if (this->getType() == component1->getType()){ return false; }
	else return true;
}

/*       Entity <--> Atrribute
 *connection[0] <--> connection[1]
 */
void Connector::connectTo(Component* component1){
	if (canConnectTo(component1)){
		if (this->connection[0] == NULL){
			connection[0] = component1;
		}
		else {
			connection[1] = component1;
			if (connection[0]->getId() > component1->getId()){
				swap(connection[0], connection[1]);
			}
			
		}
	}
}