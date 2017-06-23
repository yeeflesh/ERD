#include "stdafx.h"
#include "Component.h"

Component::Component(char type, string name) :type(type), name(name){
	static int nextId = 0;
	this->id = nextId++;
}
//Component::Component(int id, char type, string name) :id(id), type(type), name(name){}
int Component::getId(){ return this->id; }
char Component::getType(){ return this->type; }
string Component::getName(){ return this->name; }
//void Component::setType(char type){ this->type = type; }
//vector<Component*> Component::getConnetions(){ return this->connections; }
