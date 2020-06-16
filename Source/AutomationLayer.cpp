/*
  ==============================================================================

    AutomationLayer.cpp
    Created: 4 Dec 2019 12:45:51pm
    Author:  bkupe

  ==============================================================================
*/

#include "AutomationLayer.h"
#include "AutomationTimeline.h"

AutomationLayer::AutomationLayer(Sequence* s, var params) :
	SequenceLayer(s, getTypeString()),
	automation("Automation", &recorder)
{
	saveAndLoadRecursiveData = true;

	automation.setLength(s->totalTime->floatValue()); 
	addChildControllableContainer(&automation);
	automation.hideInEditor = true;

	addChildControllableContainer(&recorder);

	uiHeight->setValue(100);
}

AutomationLayer::~AutomationLayer()
{
}

SequenceLayerTimeline* AutomationLayer::getTimelineUI()
{
	return new AutomationTimeline(this);
}

Array<Inspectable *> AutomationLayer::selectAllItemsBetweenInternal(float start, float end)
{
	Array<Inspectable*> result;
	Array<AutomationKey *> keys = automation.getKeysBetweenPositions(start, end);
	result.addArray(keys);
	return result;
}

Array<UndoableAction*> AutomationLayer::getRemoveAllItemsBetweenInternal(float start, float end)
{
	return automation.getRemoveItemsUndoableAction(automation.getKeysBetweenPositions(start, end));
}

Array<UndoableAction*> AutomationLayer::getInsertTimespanInternal(float start, float length)
{
	return automation.getMoveKeysBy(start, length);
}

Array<UndoableAction*> AutomationLayer::getRemoveTimespanInternal(float start, float end)
{
	return automation.getRemoveTimespan(start, end);
}


bool AutomationLayer::paste()
{
	if (!automation.addItemsFromClipboard(false).isEmpty()) return true;
	return SequenceLayer::paste();
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
