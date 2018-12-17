/*
  ==============================================================================

    ParametersLayerBlockManager.h
    Created: 8 Nov 2018 2:49:43pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "ParametersLayerBlock.h"

class ParametersLayerBlockManager :
	public BaseManager<ParametersLayerBlock>
{
public:
	ParametersLayerBlockManager(ParametersLayer * layer);
	virtual ~ParametersLayerBlockManager();

	ParametersLayer * layer;

	ParametersLayerBlock * createItem() override;
	ParametersLayerBlock * addBlockAt(float time);
	ParametersLayerBlock * getBlockAtTime(float time);
};