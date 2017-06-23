#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
private:
	int id;
	char type;
	string name;
	//vector<Component*> connections;
public:
	Component(char type = 'E', string name = "");
	//Component(int id = 0, char type = 'E', string name = "");	
	//void setType(char);
	int getId();
	char getType();
	string getName();
	//vector<Component*> getConnetions();
	virtual bool canConnectTo(Component*) = 0;
	virtual void connectTo(Component*) = 0;
};

#endif