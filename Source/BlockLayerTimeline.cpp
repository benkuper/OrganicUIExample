/*
  ==============================================================================

    BlockLayerTimeline.cpp
    Created: 20 Jul 2019 7:35:49am
    Author:  bkupe

  ==============================================================================
*/

#include "BlockLayerTimeline.h"

BlockLayerTimeline::BlockLayerTimeline(BlockLayer* layer) :
	SequenceLayerTimeline(layer),
	managerUI(this,&layer->manager)
{
	addAndMakeVisible(&managerUI);
	needle.toFront(false);
	resized();
}

void BlockLayerTimeline::resized()
{
	SequenceLayerTimeline::resized();
	managerUI.setBounds(getLocalBounds());
}

void BlockLayerTimeline::updateContent()
{
	managerUI.updateContent();
}
