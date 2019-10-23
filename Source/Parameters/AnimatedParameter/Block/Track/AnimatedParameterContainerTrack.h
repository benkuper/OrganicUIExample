/*
  ==============================================================================

    AnimatedParameterContainerTrack.h
    Created: 8 Nov 2018 2:50:05pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

#include "AnimatedParameterTrack.h"
#include "../../AnimatedParameterContainer.h"

class AnimatedParameterContainerTrack :
	public ControllableContainer
{
public:
	AnimatedParameterContainerTrack(AnimatedParameterContainer * container, float length);
	virtual ~AnimatedParameterContainerTrack();

	AnimatedParameterContainer * container;
	OwnedArray<AnimatedParameterTrack> tracks;

	float length;

	void setLength(float value);

	void syncTracks();
	void addTrackForParameter(AnimatedParameter * parameter);
	void removeParameterTrack(AnimatedParameterTrack * parameterTrack);
};