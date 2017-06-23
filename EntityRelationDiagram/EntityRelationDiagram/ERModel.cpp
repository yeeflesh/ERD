#include "stdafx.h"
#include "ERModel.h"
#include "ComponentFactory.h"
#include "Connector.h"
#include "Entity.h"
#include "Attribute.h"

void ERModel::addComponent(){
	//set type
	cout << "\nWhat kind of node do you want to add?\n";
	cout << "[A]Attribute [E]Entity [R]Relation\n";
	cout << "> ";
	char inputType;
	while (inputType = _getche(), (inputType != 'A' && inputType != 'E' && inputType != 'R')){
		cout << "\nYou entered an invalid node. Please enter a valid one again.\n";
		cout << "[A]Attribute [E]Entity [R]Relation\n";
		cout << "> ";
	}
	
	//set current type & type name
	int type;
	string typeName;
	switch (inputType)
	{
	case 'E':
		type = COMPONENT_ENTITY;
		typeName = "Entity";
		break;
	case 'A':
		type = COMPONENT_ATTRIBUTE;
		typeName = "Attribute";
		break;
	case 'R':
		type = COMPONENT_RELATIONSHIP;
		typeName = "Relation";
		break;
	}

	//create node
	ComponentFactory factory;
	Component* node = factory.createComponent(type);
	printf("A node [%s] has been added. ID: %d, Name: \"%s\"\n", typeName.c_str(), node->getId(), node->getName().c_str());
	this->components[node->getId()] = node;

	//draw component
	//cout << "Nodes:\n";
	drawComponent();
}
map<int, Component*>& ERModel::getComponents(){ return this->components; }
void ERModel::drawComponent(){
	if (this->components.empty()) cout << "\nIt has no node to display.\n";
	else{
		cout << "\nNodes:\n";
		cout << "------------------------------------\n";
		cout << " Type |  ID  |  Name\n";
		cout << "------+------+---------------------- \n";
		for (auto erMap : this->components){
			Component* node = erMap.second;
			cout << "  " << left << setw(4) << setfill(' ') << node->getType(); //type
			cout << "|  " << left << setw(4) << setfill(' ') << node->getId(); //id
			cout << "|  " << node->getName() << endl; //name
		}
		cout << "------------------------------------\n";
	}
}
void ERModel::drawConnections(){
	int connetorCount = 0;
	for (auto erMap : this->components){
		Component* node = erMap.second;
		if (node->getType() == 'C'){
			connetorCount++;
		}
	}
	if (!connetorCount) cout << "\nIt has no connection to display.\n";
	else{
		cout << "\nConnections:\n";
		cout << "--------------------------\n";
		cout << "Connection | node | node \n";
		cout << "-----------+------+-------\n";
		for (auto erMap : this->components){
			Component* node = erMap.second;
			if (node->getType() == 'C'){
				cout << "     " << left << setw(6) << setfill(' ') << node->getId(); //connection
				cout << "|  " << left << setw(4) << setfill(' ') << ((Connector*)node)->getConnection()[0]->getId(); //node1
				cout << "|  " << ((Connector*)node)->getConnection()[1]->getId() << endl; //node2
			}			
		}
		cout << "--------------------------\n";
	}
}
void ERModel::drawTable(){
	if (this->components.empty()) cout << "\nIt has no table to display.\n";
	else{
		int connectionCount = 0;
		for (auto erMap : this->components){
			Component* node = erMap.second;
			if (node->getType() == 'C' && node->getName() == ""){
				connectionCount++;
			}
		}
		if (!connectionCount) cout << "\nIt has no entity-attribute connection.\n";
		else{
			cout << "\nTables:\n";
			cout << "------------------------------------------------------------\n";
			cout << " Entity     |  Attribute\n";
			cout << "------------+-----------------------------------------------\n";
			for (auto erMap : this->components){
				Component* node = erMap.second;
				if (node->getType() == 'E'){
					cout << " " << left << setw(11) << setfill(' ') << node->getName(); //entity
					vector<string> pk;
					vector<string> attr;
					//vector<string> fk;	
					for (Connector* conn : ((Entity*)node)->getConnectors()){
						if (conn->getName() == ""){//take attribute
							Component** attConn = conn->getConnection();
							for (int i = 0; i < 2; i++){
								if (attConn[i]->getType() == 'A'){
									//Component* currentAttr = attConn[i];
									if (((Attribute*)attConn[i])->getPrimary()){ pk.push_back(attConn[i]->getName()); }
									else attr.push_back(attConn[i]->getName());
								}
							}
						}
					}
					//current attrbute set
					string currentAttribute;
					//process pk string
					string strPk = "PK( ";
					if (pk.size()){
						for (int i = 0; i < pk.size(); i++){
							if (i) strPk += ", " + pk[i];
							else strPk += pk[i];
						}
						strPk += " )";
					}
					else strPk = "";
					currentAttribute += (strPk != "" &&  attr.size()) ? strPk + ", " : strPk;
					//process attr string
					string strAttr = "";
					if (attr.size())
						for (int i = 0; i < attr.size(); i++){
							if (i) strAttr += ", " + attr[i];
							else strAttr += attr[i];
						}
					currentAttribute += strAttr;
					//currentAttribute += (strAttr != "" &&  fk.size()) ? strAttr + ", " : strAttr;
					cout << "|  " << currentAttribute << endl;
				}
			}
			cout << "------------------------------------------------------------\n";
		}
	}
}