// EntityRelationDiagram.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "TextUI.h"

int _tmain(int argc, _TCHAR* argv[])
{
	TextUI textUI;
	textUI.processCommand();
	/*
	// *test
	ERModel erModel;
	erModel.addComponent();
	
	/*
	for (auto com : erModel.getComponents()){
		cout << "id:" << com.second->getId() << " name:" << com.second->getName();
	}
	erModel.addComponent();*/

	return 0;
}

