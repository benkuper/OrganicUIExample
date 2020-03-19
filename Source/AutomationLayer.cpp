/*
  ==============================================================================

    AutomationLayer.cpp
    Created: 4 Dec 2019 12:45:51pm
    Author:  bkupe

  ==============================================================================
*/

#include "AutomationLayer.h"


#include "AutomationLayer.h"
#include "AutomationTimeline.h"

AutomationLayer::AutomationLayer(Sequence* s, var params) :
	SequenceLayer(s, getTypeString()),
	automation("Automation", params.getProperty("dimensions",1))
{
	saveAndLoadRecursiveData = true;

	itemDataType = "Automation";
	automation.setLength(s->totalTime->floatValue()); 
	addChildControllableContainer(&automation);
	uiHeight->setValue(100);
}

AutomationLayer::~AutomationLayer()
{
}

SequenceLayerTimeline* AutomationLayer::getTimelineUI()
{
	return new AutomationTimeline(this);
}

void AutomationLayer::selectAll(bool addToSelection)
{
	//deselectThis(false);
	//automation.askForSelectAllItems(addToSelection);
}

void AutomationLayer::sequenceCurrentTimeChanged(Sequence* s, float prevTime, bool seeking)
{
	automation.position->setValue(s->currentTime->floatValue());
}

void AutomationLayer::sequenceTotalTimeChanged(Sequence* s)
{
	automation.setLength(s->totalTime->floatValue());
}
