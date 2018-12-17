/*
  ==============================================================================

    AutomationLayerTimeline.h
    Created: 25 Oct 2018 10:24:57am
    Author:  Ben

  ==============================================================================
*/

#pragma once

#include "AutomationLayer.h"

class AutomationLayerTimeline :
	public SequenceLayerTimeline
{
public:
	AutomationLayerTimeline(AutomationLayer * layer);
	~AutomationLayerTimeline();

	AutomationLayer * automationLayer;
	AutomationUI automationUI;

	void resized();
	void updateContent() override;

};