/*
  ==============================================================================

    ParametersLayerBlock.cpp
    Created: 8 Nov 2018 2:49:26pm
    Author:  Ben

  ==============================================================================
*/

#include "ParametersLayerBlock.h"
#include "../../ParametersLayer.h"

ParametersLayerBlock::ParametersLayerBlock(float _time, ParametersLayer * layer) :
	BaseItem("Block"),
	layer(layer),
	isCurrent(false),
	blockAsyncNotifier(10)
{
	itemDataType = "ParameterBlock";

	time = addFloatParameter("Start Time", "Time of the start of the clip", _time, 0, 3600);
	time->defaultUI = FloatParameter::TIME;

	blockLength = addFloatParameter("Length", "Length of the clip (in seconds)", 10, .1f, 3600);
	blockLength->defaultUI = FloatParameter::TIME;

	syncTracks();
}

ParametersLayerBlock::~ParametersLayerBlock()
{
}

void ParametersLayerBlock::syncTracks()
{
	Array<AnimatedParameterContainerTrack *> tracksToRemove;

	for (auto &ct : containerTracks)
	{
		if (!layer->apcm.items.contains(ct->container)) tracksToRemove.add(ct);
	}

	for (auto &tr : tracksToRemove) removeContainerTrack(tr);

	Array<AnimatedParameterContainer *> containersToAdd;
	for (auto &c : layer->apcm.items)
	{
		bool found = false;
		for (auto &ct : containerTracks)
		{
			if (ct->container == c)
			{
				found = true;
				break;
			}
		}
		if (!found) containersToAdd.add(c);
	}

	for (auto &c : containersToAdd) addTrackForContainer(c);
}

void ParametersLayerBlock::addTrackForContainer(AnimatedParameterContainer * container)
{
	AnimatedParameterContainerTrack * t = new AnimatedParameterContainerTrack(container, blockLength->floatValue());
	containerTracks.add(t); 
	addChildControllableContainer(t);
}

void ParametersLayerBlock::removeContainerTrack(AnimatedParameterContainerTrack * containerTrack)
{
	removeChildControllableContainer(containerTrack);
	containerTracks.removeObject(containerTrack);
}

void ParametersLayerBlock::onContainerParameterChangedInternal(Parameter * p)
{
	BaseItem::onContainerParameterChangedInternal(p);
	if (p == blockLength)
	{
		for (auto &ct : containerTracks)
		{
			ct->setLength(blockLength->floatValue());
		}
	}
}

void ParametersLayerBlock::setIsCurrent(bool value)
{
	if (isCurrent == value) return;
	isCurrent = value;

	blockAsyncNotifier.addMessage(new BlockEvent(BlockEvent::BLOCK_IS_CURRENT_CHANGED, this));
}

bool ParametersLayerBlock::isInRange(float _time)
{
	return (_time >= time->floatValue() && _time <= time->floatValue() + blockLength->floatValue());
}