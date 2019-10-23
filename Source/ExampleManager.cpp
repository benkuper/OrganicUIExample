/*
  ==============================================================================

    ExampleManager.cpp
    Created: 1 Jun 2018 12:48:08pm
    Author:  Ben

  ==============================================================================
*/

#include "ExampleManager.h"

juce_ImplementSingleton(ExampleManager)

ExampleManager::ExampleManager() :
	BaseManager("Example Manager"),
	itemsAreSelectable(true)
{
	//managerFactory = &factory;
}

ExampleManager::~ExampleManager()
{
}

ExampleItem * ExampleManager::createItem()
{
	ExampleItem * i = new ExampleItem();
	if(!itemsAreSelectable) i->showInspectorOnSelect = false;
	return i;
}
