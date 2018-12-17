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
	parameter(parameter)
{
}

AnimatedParameterTrack::~AnimatedParameterTrack()
{
}
