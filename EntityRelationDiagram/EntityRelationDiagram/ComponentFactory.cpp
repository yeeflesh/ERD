#include "stdafx.h"
#include "ComponentFactory.h"
#include "Entity.h"
#include "Attribute.h"
#include "Relationship.h"

Component* ComponentFactory::createComponent(int type){
	//set name
	cout << "\nEnter the name of this node:\n";
	cout << "> ";
	string name; cin >> name;

	Component* com = NULL;
	switch (type)
	{
	case COMPONENT_ENTITY:
		com = new Entity(name);
		break;
	case COMPONENT_ATTRIBUTE:
		com = new Attribute(name);
		break;
	case COMPONENT_RELATIONSHIP:
		com = new Relationship(name);
		break;
	}
	return com;
}