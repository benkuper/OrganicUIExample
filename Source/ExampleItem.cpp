/*
  ==============================================================================

    ExampleItem.cpp
    Created: 1 Jun 2018 12:48:12pm
    Author:  Ben

  ==============================================================================
*/

#include "ExampleItem.h"
#include "ExampleManager.h"

ExampleItem::ExampleItem() :
	BaseItem("Example Item")
{
	/*
	manager = new ExampleManager();
	manager->setNiceName("Nested manager");
	addChildControllableContainer(manager);
	manager->showInspectorOnSelect = false;
	manager->selectItemWhenCreated = false;
	manager->itemsAreSelectable = false;
	*/

	param1 = addFloatParameter("Parameter 1", "Param 1", 0, 0, 1);
	param2 = addFloatParameter("Parameter 2", "Param 2", 0, 0, 10);
	param3 = addFloatParameter("Parameter 3", "Param 3", 0);
	
}

ExampleItem::~ExampleItem()
{
}


var ExampleItem::getJSONData()
{
	var data = BaseItem::getJSONData();
	//data.getDynamicObject()->setProperty("manager", manager->getJSONData());
	return data;
}

void ExampleItem::loadJSONDataInternal(var data)
{
	BaseItem::loadJSONDataInternal(data);
	//manager->loadJSONData(data.getProperty("manager", var()));
}

