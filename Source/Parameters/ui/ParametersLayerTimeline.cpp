/*
  ==============================================================================

    ParametersLayerTimeline.cpp
    Created: 8 Nov 2018 3:02:46pm
    Author:  Ben

  ==============================================================================
*/

#include "ParametersLayerTimeline.h"

ParametersLayerTimeline::ParametersLayerTimeline(ParametersLayer * layer) :
	SequenceLayerTimeline(layer),
	parametersLayer(layer)
{
	bgColor = bgColor.darker();

	bmUI = new ParametersLayerBlockManagerUI(this, layer->blockManager);
	addAndMakeVisible(bmUI);

	updateContent();
}

ParametersLayerTimeline::~ParametersLayerTimeline()
{
}

void ParametersLayerTimeline::resized()
{
	bmUI->setBounds(getLocalBounds());
}

void ParametersLayerTimeline::updateContent()
{
	bmUI->updateContent();
}
