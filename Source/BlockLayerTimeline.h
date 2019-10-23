/*
  ==============================================================================

    BlockLayerTimeline.h
    Created: 20 Jul 2019 7:35:49am
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "BlockLayer.h"

class BlockLayerTimeline :
	public SequenceLayerTimeline
{
public:
	BlockLayerTimeline(BlockLayer* layer);
	~BlockLayerTimeline() {}

	LayerBlockManagerUI managerUI;

	void resized() override;
	void updateContent() override;
};