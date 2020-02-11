/*
  ==============================================================================

    AutomationTimeline.cpp
    Created: 4 Dec 2019 12:51:22pm
    Author:  bkupe

  ==============================================================================
*/

#include "AutomationTimeline.h"

AutomationTimeline::AutomationTimeline(AutomationLayer * layer) :
	SequenceLayerTimeline(layer),
	automationUI(&layer->automation)
{
	addAndMakeVisible(&automationUI);
	needle.toFront(false);
	resized();
}

void AutomationTimeline::resized()
{
	SequenceLayerTimeline::resized();
	automationUI.setBounds(getLocalBounds());
}

void AutomationTimeline::updateContent()
{
	//automationUI.updateContent();
}

bool AutomationTimeline::keyPressed(const KeyPress& e)
{
	if (automationUI.keyPressed(e)) return true;
	return SequenceLayerTimeline::keyPressed(e);
}
