/*
  ==============================================================================

    ExampleItem.h
    Created: 1 Jun 2018 12:48:12pm
    Author:  Ben

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class ExampleManager;

class ExampleItem :
	public BaseItem
{
public:
	ExampleItem();
	~ExampleItem();

	FloatParameter * param1;
	FloatParameter * param2;
	FloatParameter * param3;

	//ScopedPointer<ExampleManager> manager;

	var getJSONData() override;
	void loadJSONDataInternal(var data) override;
};