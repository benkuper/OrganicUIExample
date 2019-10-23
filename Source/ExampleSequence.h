/*
  ==============================================================================

    ExampleSequence.h
    Created: 17 Jul 2019 7:07:45pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class ExampleSequence :
	public Sequence
{
public:
	ExampleSequence();
	~ExampleSequence() {}

	String getTypeString() const override { return "Sequence"; }
	static ExampleSequence* create(var params) { return new ExampleSequence(); }
};