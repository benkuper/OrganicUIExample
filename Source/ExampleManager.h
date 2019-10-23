/*
  ==============================================================================

    ExampleManager.h
    Created: 1 Jun 2018 12:48:08pm
    Author:  Ben

  ==============================================================================
*/

#pragma once
#include "ExampleItem.h"

class ExampleManager :
	public BaseManager<ExampleItem>
{
public:
	juce_DeclareSingleton(ExampleManager, true);
	ExampleManager();
	~ExampleManager();

	//Factory<ExampleItem> factory;

	bool itemsAreSelectable;

	ExampleItem * createItem() override;
};