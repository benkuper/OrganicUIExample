/*
  ==============================================================================

    ExampleEngine.h
    Created: 1 Jun 2018 12:48:01pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
class ExampleEngine :
	public Engine
{
public:
	ExampleEngine();
	~ExampleEngine();

	Factory<Sequence> sequenceFactory;

	var getJSONData() override;
	void loadJSONDataInternalEngine(var data, ProgressTask *) override;
};