/*
  ==============================================================================

    ParametersLayerBlock.h
    Created: 8 Nov 2018 2:49:26pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

#include "Track/AnimatedParameterContainerTrack.h"

class ParametersLayer;

class ParametersLayerBlock :
	public BaseItem
{
public:
	ParametersLayerBlock(float time = 0, ParametersLayer * layer = nullptr);
	virtual ~ParametersLayerBlock();

	FloatParameter * time;
	FloatParameter * clipLength;

	ParametersLayer * layer;

	OwnedArray<AnimatedParameterContainerTrack> containerTracks;
	
	void syncTracks();

	void addTrackForContainer(AnimatedParameterContainer * container);
	void removeContainerTrack(AnimatedParameterContainerTrack * containerTrack);

	bool isCurrent;
	void setIsCurrent(bool value);
	bool isInRange(float time);

	class BlockEvent {
	public:
		enum Type {BLOCK_IS_CURRENT_CHANGED};
		BlockEvent(Type type, ParametersLayerBlock * b) : type(type), block(b) {}
		Type type;
		ParametersLayerBlock *block;
	};

	QueuedNotifier<BlockEvent> blockAsyncNotifier;
	typedef QueuedNotifier<BlockEvent>::Listener AsyncListener;

	void addAsyncBlockListener(AsyncListener* newListener) { blockAsyncNotifier.addListener(newListener); }
	void addAsyncCoalescedBlockListener(AsyncListener* newListener) { blockAsyncNotifier.addAsyncCoalescedListener(newListener); }
	void removeAsyncBlockListener(AsyncListener* listener) { blockAsyncNotifier.removeListener(listener); }

};