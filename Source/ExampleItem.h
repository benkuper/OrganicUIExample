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

	Trigger* exampleTrigger;
	BoolParameter* boolParam;
	IntParameter* intParam;
	FloatParameter * param1;
	FloatParameter * param2;
	FloatParameter * param3;
	StringParameter* strParam;
	TargetParameter * targetParam;
	ColorParameter* colorParam;

	Curve2D curve;

	std::unique_ptr<ExampleManager> manager;

};
