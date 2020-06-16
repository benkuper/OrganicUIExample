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
	public Sequence,
	public SequenceLayerManager::ManagerListener
{
public:
	ExampleSequence();
	~ExampleSequence() {}

	void itemAdded(SequenceLayer* layer) override;
	void itemsAdded(Array<SequenceLayer*> layers) override;

	String getTypeString() const override { return "Sequence"; }
	static ExampleSequence* create(var params) { return new ExampleSequence(); }
};