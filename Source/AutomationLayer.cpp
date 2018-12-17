/*
  ==============================================================================

    AutomationLayer.cpp
    Created: 25 Oct 2018 10:18:28am
    Author:  Ben

  ==============================================================================
*/

#include "AutomationLayer.h"
#include "AutomationLayerTimeline.h"

AutomationLayer::AutomationLayer(Sequence * s, var params) :
	SequenceLayer(s, getTypeString())
{
	addChildControllableContainer(&automation);
	automation.length->setValue(sequence->totalTime->floatValue());
}

AutomationLayer::~AutomationLayer()
{
}

SequenceLayerPanel * AutomationLayer::getPanel()
{
	return new SequenceLayerPanel(this);
}

SequenceLayerTimeline * AutomationLayer::getTimelineUI()
{
	return new AutomationLayerTimeline(this);
}

void AutomationLayer::sequenceCurrentTimeChanged(Sequence *, float prevTime, bool evaluatedSkippedData)
{
	automation.position->setValue(sequence->currentTime->floatValue());
}

void AutomationLayer::sequenceTotalTimeChanged(Sequence *)
{
	automation.length->setValue(sequence->totalTime->floatValue());
}

void AutomationLayer::sequencePlayStateChanged(Sequence *)
{
}
