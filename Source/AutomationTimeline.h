/*
  ==============================================================================

    AutomationTimeline.h
    Created: 4 Dec 2019 12:51:22pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once
#include "AutomationLayer.h"

class AutomationTimeline :
	public SequenceLayerTimeline
{
public:
	AutomationTimeline(AutomationLayer * layer);
	~AutomationTimeline() {}

	AutomationUI automationUI;

	void resized() override;
	void updateContent() override;
	bool keyPressed(const KeyPress &e) override;
};