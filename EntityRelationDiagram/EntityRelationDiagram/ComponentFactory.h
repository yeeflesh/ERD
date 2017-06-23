#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include "Component.h"
const int COMPONENT_ENTITY = 0x01;
const int COMPONENT_ATTRIBUTE = 0x02;
const int COMPONENT_RELATIONSHIP = 0x03;

class ComponentFactory
{
public:
	Component * createComponent(int);
};

#endif