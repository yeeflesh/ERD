#ifndef ENTITY_H
#define ENTITY_H

#include "Node.h"

class Entity : public Node
{
public:
	Entity(string name = "");
	void connectTo(Component*);
};

#endif