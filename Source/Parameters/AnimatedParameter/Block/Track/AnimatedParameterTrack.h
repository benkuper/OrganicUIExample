/*
  ==============================================================================

    AnimatedParameterTrack.h
    Created: 8 Nov 2018 2:50:20pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "../../AnimatedParameter.h"

class AnimatedParameterTrack :
	public ControllableContainer
{
public:
	AnimatedParameterTrack(AnimatedParameter * parameter);
	virtual ~AnimatedParameterTrack();

	AnimatedParameter * parameter;
	Automation automation;

	void setLength(float value);
};