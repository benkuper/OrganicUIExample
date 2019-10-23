/*
  ==============================================================================

    BlockLayer.cpp
    Created: 20 Jul 2019 7:33:27am
    Author:  bkupe

  ==============================================================================
*/

#include "BlockLayer.h"
#include "BlockLayerTimeline.h"

BlockLayer::BlockLayer(Sequence* s, var params) :
	SequenceLayer(s, "Blocks"),
	manager(this)
{
	itemDataType = "Blocks";
	addChildControllableContainer(&manager);
}

BlockLayer::~BlockLayer()
{
}

SequenceLayerTimeline* BlockLayer::getTimelineUI()
{
	return new BlockLayerTimeline(this);
}

void BlockLayer::selectAll(bool addToSelection)
{
	deselectThis(false);
	manager.askForSelectAllItems(addToSelection);
}