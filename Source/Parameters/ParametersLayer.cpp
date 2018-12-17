/*
  ==============================================================================

    ParametersLayer.cpp
    Created: 8 Nov 2018 2:43:52pm
    Author:  Ben

  ==============================================================================
*/

#include "ParametersLayer.h"
#include "ui/ParametersLayerTimeline.h"
#include "ui/ParametersLayerPanel.h"
#include "AnimatedParameter/Block/ParametersLayerBlockManager.h"

ParametersLayer::ParametersLayer(Sequence * s, var params) :
	SequenceLayer(s, getTypeString())
{
	uiHeight->defaultValue = 120;
	uiHeight->resetValue();
	addChildControllableContainer(&apcm);

	blockManager = new ParametersLayerBlockManager(this);
	addChildControllableContainer(blockManager);
}

ParametersLayer::~ParametersLayer()
{
}

SequenceLayerPanel * ParametersLayer::getPanel()
{
	return new ParametersLayerPanel(this);
}

SequenceLayerTimeline * ParametersLayer::getTimelineUI()
{
	return new ParametersLayerTimeline(this);
}

void ParametersLayer::sequenceCurrentTimeChanged(Sequence *, float prevTime, bool evaluatedSkippedData)
{
}

void ParametersLayer::sequenceTotalTimeChanged(Sequence *)
{
}

void ParametersLayer::sequencePlayStateChanged(Sequence *)
{
}
