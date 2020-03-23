/*
  ==============================================================================

    Mapping2DLayer.cpp
    Created: 23 Mar 2020 5:17:47pm
    Author:  bkupe

  ==============================================================================
*/

#include "Mapping2DLayer.h"
#include "ui/Mapping2DLayerTimeline.h"

Mapping2DLayer::Mapping2DLayer(Sequence* s, var params) :
	SequenceLayer(s, getTypeString())
{
	saveAndLoadRecursiveData = true;

	itemDataType = "Mapping2D";

	addChildControllableContainer(&curve);
	curve.length->setValue(s->totalTime->floatValue());
	curve.setControlMode(Curve2D::AUTOMATION);
	automation = (Automation *)curve.position->automation->automationContainer;
	uiHeight->setValue(100);
}

Mapping2DLayer::~Mapping2DLayer()
{
}

SequenceLayerTimeline* Mapping2DLayer::getTimelineUI()
{
	return new Mapping2DTimeline(this);
}

void Mapping2DLayer::selectAll(bool addToSelection)
{
	//deselectThis(false);
	//automation.askForSelectAllItems(addToSelection);
}

void Mapping2DLayer::sequenceCurrentTimeChanged(Sequence* s, float prevTime, bool seeking)
{
	automation->position->setValue(s->currentTime->floatValue());
}

void Mapping2DLayer::sequenceTotalTimeChanged(Sequence* s)
{
	automation->length->setValue(s->totalTime->floatValue());
}
