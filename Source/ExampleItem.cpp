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
	BaseItem("Example Item",true,true)
{
	saveAndLoadRecursiveData = true;

	manager.reset(new ExampleManager());
	manager->setNiceName("Nested manager");
	addChildControllableContainer(manager.get());
	manager->showInspectorOnSelect = false;
	manager->selectItemWhenCreated = false;
	manager->itemsAreSelectable = false;
	
	exampleTrigger = addTrigger("Example Trigger", "This is an example trigger");
	boolParam = addBoolParameter("Bool Param", "Bool Param", false);
	param1 = addFloatParameter("Parameter 1", "Param 1", 0, 0, 1);
	param2 = addFloatParameter("Parameter 2", "Param 2", 0, 0, 10);
	param3 = addFloatParameter("Parameter 3", "Param 3", 0);
	intParam = addIntParameter("Int Param", "Int Param", 0, 0, 10);
	strParam = addStringParameter("String Param", "String param", "Super cool");
	colorParam = addColorParameter("Color Param", "Color Param", Colours::red);
	targetParam = addTargetParameter("Target param", "Target Param");


	addChildControllableContainer(&curve);
}

ExampleItem::~ExampleItem()
{
}
