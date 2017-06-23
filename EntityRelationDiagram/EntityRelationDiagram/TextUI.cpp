#include "stdafx.h"
#include "TextUI.h"
#include "ERModel.h"
#include "Entity.h"
#include "Attribute.h"

const char ADD = '1';
const char CONNECT = '2';
const char DIAGRAM = '3';
const char PK = '4';
const char TABLE = '5';
const char EXIT = '6';
void TextUI::displayMenu(){
	cout << "1. Add a node\n";
	cout << "2. Connect two nodes\n";
	cout << "3. Display the current diagram\n";
	cout << "4. Set a primary key\n";
	cout << "5. Display the table\n";
	cout << "6. Exit\n";
	cout << "> ";
}
string addIdInput(string sequence){
	cout << "\nPlease enter the " + sequence + " node ID\n";
	cout << "> ";
	string strId;
	cin >> strId;
	for (size_t i = 0; i < strId.length(); i++){
		if (!isdigit(strId[i])){
			cout << "\nPlease enter a number\n";
			cout << "Please enter the " + sequence + " node ID\n";
			cout << "> ";
			cin >> strId;
		}
	}
	return strId;
}

int checkAndGetId(ERModel erModel, string sequence){
	int id;
	while (id = atoi(addIdInput(sequence).c_str()), id  > erModel.getComponents().size() - 1){ // not find
		cout << "\nThe node ID you entered does not exist. Please enter a valid one again.\n";
		//cout << "> ";
	}
	return id;
}

string entityIdInput(){
	cout << "Enter the ID of the entity :\n";
	cout << "> ";
	string strEntityId;
	cin >> strEntityId;
	for (size_t i = 0; i < strEntityId.length(); i++){
		if (!isdigit(strEntityId[i])){
			cout << "\nThe node ID you entered does not exist. Please enter a valid one again.\n";
			cout << "> ";
			cin >> strEntityId;
		}
	}
	return strEntityId;
}

int checkAndGetEntityId(ERModel erModel){
	int id;
	while (id = atoi(entityIdInput().c_str()), id  > erModel.getComponents().size() - 1){ // not find
		cout << "The node ID you entered does not exist. Please enter a valid one again.\n";
		cout << "> ";
	}
	return id;
}

vector<int> &split(const string &s, char delim, vector<int> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(atoi(item.c_str()));
	}
	return elems;
}

vector<int> split(const string &s, char delim) {
	vector<int> elems;
	split(s, delim, elems);
	return elems;
}

bool checkPrimary(int entityId, vector<int> attributesId, vector<int> primaryToken){
	for (int primary : primaryToken){
		if (find(attributesId.begin(), attributesId.end(), primary) == attributesId.end()){
			printf("\nThe node '%d' does not belong to Entity '%d'. Please enter a valid one again.\n", primary, entityId);
			cout << "> ";
			return false;
		}
	}
	return true;
}

void TextUI::processCommand(){
	ERModel erModel;
	while (true){
		displayMenu();
		char command;
		while (command = _getche(), (command > '6' || command < '1')){
			cout << "\nplease enter '1' ~ '6' thanks.\n";
			displayMenu();
		}
		
		if (command == ADD){
			erModel.addComponent();

			continue;
		}

		if (command == CONNECT){
			if (erModel.getComponents().size() <= 1) cout << "\nIt has not enough node to connect.\n";
			else {
				//set id		
				int firstId;
				int secondId;
				while ((firstId = checkAndGetId(erModel, "first")) >= 0, erModel.getComponents()[firstId]->getType() == 'C') {
					cout << "\nThis node can not connect.";
				}
				while ((secondId = checkAndGetId(erModel, "second")) >= 0, erModel.getComponents()[secondId]->getType() == 'C') {
					cout << "\nThis node can not connect.";
				}
				//connect
				erModel.getComponents()[firstId]->connectTo(erModel.getComponents()[secondId]);
				if (!((Node*)erModel.getComponents()[firstId])->getConnectors().empty()){
					Connector* connector = ((Node*)erModel.getComponents()[firstId])->getConnectors().back();
					erModel.getComponents()[connector->getId()] = connector;
					erModel.drawConnections();
				}
			}
			continue;
		}

		if (command == DIAGRAM){
			//cout << "Nodes:\n";
			erModel.drawComponent();
			erModel.drawConnections();

			continue;
		}

		if (command == PK){
			int connectionCount = 0;
			for (auto erMap : erModel.getComponents()){
				Component* node = erMap.second;
				if (node->getType() == 'C' && node->getName() == ""){
					connectionCount++;
				}
			}
			if (!connectionCount) cout << "\nIt has no entity-attribute connection.\n";
			else{
				cout << "\nEntities :\n";
				cout << "-------------------------\n";
				cout << " Type |  ID  |  Name\n";
				cout << "------+------+-----------\n";
				for (auto erMap : erModel.getComponents()){
					Component* node = erMap.second;
					if (node->getType() == 'E'){
						cout << "  " << left << setw(4) << setfill(' ') << node->getType(); //type
						cout << "|  " << left << setw(4) << setfill(' ') << node->getId(); //id
						cout << "|  " << node->getName() << endl; //name
					}
				}
				cout << "-------------------------\n";
				//input entity id
				int entityId;
				while ((entityId = checkAndGetEntityId(erModel)) >= 0, erModel.getComponents()[entityId]->getType() != 'E'){
					printf("The node '%d' is not an entity. Please enter a valid one again.\n", entityId);
					//cout << "> ";
				}
				Entity* currentEntity = (Entity*)erModel.getComponents()[entityId];
				if (currentEntity->getConnectors().empty()) cout << "It has no attribute.\n";
				else{
					printf("Attributes of the entity '%d'\n", entityId);
					cout << "------------------------------------\n";
					cout << " Type |  ID  |  Name\n";
					cout << "------+------+----------------------\n";
					vector<int> attributesId;
					for (Connector* connector : currentEntity->getConnectors()){
						if (connector->getName() == ""){
							Component** connection = connector->getConnection();
							for (int i = 0; i < 2; i++){
								if (connection[i]->getType() == 'A'){
									Component* node = connection[i];
									cout << "  " << left << setw(4) << setfill(' ') << node->getType(); //type
									cout << "|  " << left << setw(4) << setfill(' ') << node->getId(); //id
									cout << "|  " << node->getName() << endl; //name
									attributesId.push_back(node->getId());
								}
							}
						}
					}

					cout << "Enter the IDs of the attributes(use a comma to separate two attributes) :\n";
					cout << "> ";
					string primaryInput; cin >> primaryInput;
					vector<int> primaryToken = split(primaryInput, ',');
					while (!checkPrimary(entityId, attributesId, primaryToken)) {
						cin >> primaryInput;
						primaryToken = split(primaryInput, ',');
					}
					string primarySet = "( ";
					for (int i = 0; i < primaryToken.size(); i++){
						int primary = primaryToken[i];
						((Attribute*)erModel.getComponents()[primary])->setPrimary(true);

						if (i) primarySet += "," + to_string(primary);
						else primarySet += to_string(primary);
					}
					primarySet += " )";

					if (primaryToken.size() == 1) 	primarySet = to_string(primaryToken[0]);
					printf("The entity '%d' has the primary key %s.\n", entityId, primarySet.c_str());
				}
			}
				continue;
		}

		if (command == TABLE){
			erModel.drawTable();
			continue;
		}

		if (command == EXIT){
			cout << "\nGoodbye!\n";
			break;
		}
	}
}