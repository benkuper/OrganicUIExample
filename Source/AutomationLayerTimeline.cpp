/*
  ==============================================================================

    AutomationLayerTimeline.cpp
    Created: 25 Oct 2018 10:24:57am
    Author:  Ben

  ==============================================================================
*/

#include "AutomationLayerTimeline.h"

AutomationLayerTimeline::AutomationLayerTimeline(AutomationLayer * layer) :
	SequenceLayerTimeline(layer),
	automationLayer(layer),
	automationUI(&layer->automation)
{
	addAndMakeVisible(&automationUI);
}

AutomationLayerTimeline::~AutomationLayerTimeline()
{
}

void AutomationLayerTimeline::resized()
{
	automationUI.setBounds(getLocalBounds());
}

void AutomationLayerTimeline::updateContent()
{
	automationUI.setViewRange(automationLayer->sequence->viewStartTime->floatValue(), automationLayer->sequence->viewEndTime->floatValue());
}
