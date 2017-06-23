#ifndef ATTRINUTE_H
#define ATTRINUTE_H

#include "Node.h"

class Attribute : public Node
{
private:
	bool primary;
public:
	Attribute(string name = "");
	bool getPrimary();
	void setPrimary(bool);
	void connectTo(Component*);
};

#endif