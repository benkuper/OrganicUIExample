/*
  ==============================================================================

    ParametersLayerBlockManager.cpp
    Created: 8 Nov 2018 2:49:43pm
    Author:  Ben

  ==============================================================================
*/

#include "ParametersLayerBlockManager.h"

ParametersLayerBlockManager::ParametersLayerBlockManager(ParametersLayer * layer) :
	BaseManager("Blocks"),
	layer(layer)
{
}

ParametersLayerBlockManager::~ParametersLayerBlockManager()
{

}

ParametersLayerBlock * ParametersLayerBlockManager::createItem()
{
	return new ParametersLayerBlock(0, layer);
}

ParametersLayerBlock * ParametersLayerBlockManager::addBlockAt(float time)
{
	ParametersLayerBlock * t = new ParametersLayerBlock(time, layer);
	BaseManager::addItem(t);
	return t;
}

ParametersLayerBlock * ParametersLayerBlockManager::getBlockAtTime(float time)
{
	for (auto &c : items) if (c->isInRange(time)) return c;
	return nullptr;
}
