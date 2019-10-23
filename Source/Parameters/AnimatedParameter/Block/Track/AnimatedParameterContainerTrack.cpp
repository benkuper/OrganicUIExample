/*
  ==============================================================================

    AnimatedParameterContainerTrack.cpp
    Created: 8 Nov 2018 2:50:05pm
    Author:  Ben

  ==============================================================================
*/

#include "AnimatedParameterContainerTrack.h"

AnimatedParameterContainerTrack::AnimatedParameterContainerTrack(AnimatedParameterContainer * container, float length) :
	ControllableContainer(container->niceName),
	container(container),
	length(length)
{
	syncTracks();
}

AnimatedParameterContainerTrack::~AnimatedParameterContainerTrack()
{
}

void AnimatedParameterContainerTrack::setLength(float value)
{
	if (length == value) return;
	length = value;
	for (auto &t : tracks) t->setLength(length);
}

void AnimatedParameterContainerTrack::syncTracks()
{
	Array<AnimatedParameterTrack *> tracksToRemove;

	for (auto &t : tracks)
	{
		if (!container->parameterManager.items.contains(t->parameter)) tracksToRemove.add(t);
	}

	for (auto &t : tracksToRemove) removeParameterTrack(t);

	Array<AnimatedParameter*> parametersToAdd;
	for (auto &p : container->parameterManager.items)
	{
		bool found = false;
		for (auto &t : tracks)
		{
			if (t->parameter == p)
			{
				found = true;
				break;
			}
		}
		if (!found) parametersToAdd.add(p);
	}

	for (auto &p : parametersToAdd) addTrackForParameter(p);
}

void AnimatedParameterContainerTrack::addTrackForParameter(AnimatedParameter * parameter)
{
	AnimatedParameterTrack * t = new AnimatedParameterTrack(parameter);
	tracks.add(t);
	t->setLength(length);
	addChildControllableContainer(t);
}

void AnimatedParameterContainerTrack::removeParameterTrack(AnimatedParameterTrack * parameterTrack)
{
	removeChildControllableContainer(parameterTrack);
	tracks.removeObject(parameterTrack);
}
