/*
  ==============================================================================

	AnimatedParameterTrack.cpp
	Created: 8 Nov 2018 2:50:20pm
	Author:  Ben

  ==============================================================================
*/

#include "AnimatedParameterTrack.h"

AnimatedParameterTrack::AnimatedParameterTrack(AnimatedParameter * parameter) :
	ControllableContainer(parameter->niceName),
	parameter(parameter),
	automation("Keyframes",nullptr,false,false)
{
	addChildControllableContainer(&automation);
	automation.hideInEditor = true;
}

AnimatedParameterTrack::~AnimatedParameterTrack()
{
}

void AnimatedParameterTrack::setLength(float value)
{
	automation.length->setValue(value);
}
