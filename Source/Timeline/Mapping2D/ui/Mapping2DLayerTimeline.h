/*
  ==============================================================================

    Mapping2DLayerTimeline.h
    Created: 23 Mar 2020 5:18:10pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "../Mapping2DLayer.h"

class Mapping2DTimeline :
	public SequenceLayerTimeline
{
public:
	Mapping2DTimeline(Mapping2DLayer* layer);
	~Mapping2DTimeline() {}

	Mapping2DLayer* mapping2DLayer;
	AutomationUI automationUI;

	void paint(Graphics& g) override;
	void resized() override;
	void updateContent() override;
	bool keyPressed(const KeyPress& e) override;
};