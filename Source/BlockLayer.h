/*
  ==============================================================================

    BlockLayer.h
    Created: 20 Jul 2019 7:33:27am
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class BlockLayer :
	public SequenceLayer
{
public:
	BlockLayer(Sequence * s, var params);
	~BlockLayer();

	LayerBlockManager manager;

	SequenceLayerTimeline* getTimelineUI() override;

	void selectAll(bool addToSelection = false) override;

	String getTypeString() const override { return "Blocks"; }
	static BlockLayer * create(Sequence* s, var params) { return new BlockLayer(s, params); }
};