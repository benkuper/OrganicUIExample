/*
  ==============================================================================

	AnimatedParameterContainerTrackUI.cpp
	Created: 8 Nov 2018 2:59:27pm
	Author:  Ben

  ==============================================================================
*/

#include "AnimatedParameterContainerTrackUI.h"

AnimatedParameterContainerTrackUI::AnimatedParameterContainerTrackUI(AnimatedParameterContainerTrack * containerTrack) :
	containerTrack(containerTrack)
{
}

AnimatedParameterContainerTrackUI::~AnimatedParameterContainerTrackUI()
{
}

void AnimatedParameterContainerTrackUI::paint(Graphics & g)
{
	g.fillAll(Colours::purple.withAlpha(.5f));
}
