#ifndef RELATIONSHIP_H
#define RELATIONSHIP_H

#include "Node.h"

class Relationship : public Node
{
public:
	Relationship(string name = "");
	void connectTo(Component*);
};

#endif